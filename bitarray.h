/*******************************************************************
*
*    Author: Kareem Omar
*    kareem.h.omar@gmail.com
*    https://github.com/komrad36
*
*    Last updated Sept 20, 2021
*******************************************************************/

#pragma once

#include "bitops.h"

#define ENABLE_ASSERTS

#if !defined(__clang__) && !defined(__GNUC__) && defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4146 )
#define DEBUG_BREAK __debugbreak()
#else
#define DEBUG_BREAK __asm__ volatile("int $0x03")
#endif

#if defined(ENABLE_ASSERTS)
#include <cstdio>
#define ASSERT(a) do { if (!(a)) { printf("ASSERT FAILED: %s\n", #a); DEBUG_BREAK; } } while (0)
#else
#define ASSERT(a) do {} while (0)
#endif

template <uint64_t kNBits>
class BitArray
{
public:
    static constexpr uint64_t kNumBits = kNBits;
    static constexpr uint64_t kNumBlocks = (kNumBits + 63ULL) >> 6ULL;

    // Repeat value into every block.
    void Rep(uint64_t value)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
            m_block[i] = value;
    }

    // Assign value to all bits.
    void AssignAll(bool value)
    {
        Rep(value ? uint64_t(-1) : uint64_t(0));
    }

    // Set all bits.
    void SetAll()
    {
        AssignAll(true);
    }

    // Clear all bits.
    void ClearAll()
    {
        AssignAll(false);
    }

    // Set a bit.
    void SetBit(uint64_t index)
    {
        ASSERT(index < kNumBits);
        m_block[index >> 6ULL] |= 1ULL << (index & 63ULL);
    }

    // Clear a bit.
    void ClearBit(uint64_t index)
    {
        ASSERT(index < kNumBits);
        m_block[index >> 6ULL] &= ~(1ULL << (index & 63ULL));
    }

    // Invert a bit.
    void XorBit(uint64_t index)
    {
        ASSERT(index < kNumBits);
        m_block[index >> 6ULL] ^= 1ULL << (index & 63ULL);
    }

    // Assign a value to a single bit.
    void AssignBit(uint64_t index, bool value)
    {
        ASSERT(index < kNumBits);
        m_block[index >> 6ULL] = AssignBit_U64(m_block[index >> 6ULL], index & 63ULL, value);
    }

    // Check if a bit is set.
    bool IsBitSet(uint64_t index) const
    {
        ASSERT(index < kNumBits);
        return m_block[index >> 6ULL] & (1ULL << (index & 63ULL));
    }

    // Return the total number of set bits.
    uint64_t CountSetBits() const
    {
        uint64_t count = 0;

        for (uint64_t iBlock = 0; iBlock < kNumBlocks - 1; ++iBlock)
            count += CountSetBits_U64(m_block[iBlock]);

        count += CountSetBits_U64(m_block[kNumBlocks - 1] & LastBlockMask());

        return count;
    }

    // Return true if all bits are set.
    bool AreAllBitsSet() const
    {
        for (uint64_t iBlock = 0; iBlock < kNumBlocks - 1; ++iBlock)
        {
            if (~m_block[iBlock])
                return false;
        }

        if (~m_block[kNumBlocks - 1] & LastBlockMask())
            return false;

        return true;
    }

    // Return true if all bits are clear.
    bool AreAllBitsClear() const
    {
        for (uint64_t iBlock = 0; iBlock < kNumBlocks - 1; ++iBlock)
        {
            if (m_block[iBlock])
                return false;
        }

        if (m_block[kNumBlocks - 1] & LastBlockMask())
            return false;

        return true;
    }

    // Return the number of set bits between indices [a, b], inclusive.
    uint64_t CountSetBitsInRange(uint64_t a, uint64_t b) const
    {
        ASSERT(a <= b);
        ASSERT(b < kNumBits);

        const uint64_t iBlockA = a >> 6ULL;
        const uint64_t iBlockB = b >> 6ULL;

        if (iBlockA == iBlockB)
            return CountSetBits_U64(m_block[iBlockA] & SetBitRange_U64(a, b));

        uint64_t count = CountSetBits_U64(m_block[iBlockA] & SetBitRange_U64(a, 63ULL));

        for (uint64_t iBlock = iBlockA + 1; iBlock < iBlockB; ++iBlock)
            count += CountSetBits_U64(m_block[iBlock]);

        count += CountSetBits_U64(m_block[iBlockB] & SetBitRange_U64(0, b));

        return count;
    }

    // Set all bits between indices [a, b], inclusive.
    void SetBitsInRange(uint64_t a, uint64_t b)
    {
        ASSERT(a <= b);
        ASSERT(b < kNumBits);

        const uint64_t iBlockA = a >> 6ULL;
        const uint64_t iBlockB = b >> 6ULL;

        if (iBlockA == iBlockB)
        {
            m_block[iBlockA] |= SetBitRange_U64(a, b);
        }
        else
        {
            m_block[iBlockA] |= SetBitRange_U64(a, 63ULL);

            for (uint64_t iBlock = iBlockA + 1; iBlock < iBlockB; ++iBlock)
                m_block[iBlock] = ~0ULL;

            m_block[iBlockB] |= SetBitRange_U64(0, b);
        }
    }

    // Clear all bits between indices [a, b], inclusive.
    void ClearBitsInRange(uint64_t a, uint64_t b)
    {
        ASSERT(a <= b);
        ASSERT(b < kNumBits);

        const uint64_t iBlockA = a >> 6ULL;
        const uint64_t iBlockB = b >> 6ULL;

        if (iBlockA == iBlockB)
        {
            m_block[iBlockA] &= ~SetBitRange_U64(a, b);
        }
        else
        {
            m_block[iBlockA] &= ~SetBitRange_U64(a, 63ULL);

            for (uint64_t iBlock = iBlockA + 1; iBlock < iBlockB; ++iBlock)
                m_block[iBlock] = 0ULL;

            m_block[iBlockB] &= ~SetBitRange_U64(0, b);
        }
    }

    // Return true if all bits are set between indices [a, b], inclusive.
    bool AreAllBitsInRangeSet(uint64_t a, uint64_t b) const
    {
        ASSERT(a <= b);
        ASSERT(b < kNumBits);

        const uint64_t iBlockA = a >> 6ULL;
        const uint64_t iBlockB = b >> 6ULL;

        if (iBlockA == iBlockB)
            return !(~m_block[iBlockA] & SetBitRange_U64(a, b));

        if (~m_block[iBlockA] & SetBitRange_U64(a, 63ULL))
            return false;

        for (uint64_t iBlock = iBlockA + 1; iBlock < iBlockB; ++iBlock)
        {
            if (~m_block[iBlock])
                return false;
        }

        if (~m_block[iBlockB] & SetBitRange_U64(0, b))
            return false;

        return true;
    }

    // Return true if all bits are clear between indices [a, b], inclusive.
    bool AreAllBitsInRangeClear(uint64_t a, uint64_t b) const
    {
        ASSERT(a <= b);
        ASSERT(b < kNumBits);

        const uint64_t iBlockA = a >> 6ULL;
        const uint64_t iBlockB = b >> 6ULL;

        if (iBlockA == iBlockB)
            return !(m_block[iBlockA] & SetBitRange_U64(a, b));

        if (m_block[iBlockA] & SetBitRange_U64(a, 63ULL))
            return false;

        for (uint64_t iBlock = iBlockA + 1; iBlock < iBlockB; ++iBlock)
        {
            if (m_block[iBlock])
                return false;
        }

        if (m_block[iBlockB] & SetBitRange_U64(0, b))
            return false;

        return true;
    }

    // Return the number of leading (last; high index) zeros, or kNumBits if all bits are clear.
    uint64_t CountLeadingZeros() const
    {
        if (const uint64_t block = m_block[kNumBlocks - 1] & LastBlockMask())
            return (kNumBits - 1) - (((kNumBlocks - 1) << 6ULL) + LastSetBitIndex_U64(block));

        for (uint64_t i = kNumBlocks - 2; int64_t(i) >= 0; --i)
        {
            if (const uint64_t block = m_block[i])
                return (kNumBits - 1) - ((i << 6ULL) + LastSetBitIndex_U64(block));
        }

        return kNumBits;
    }

    // Return the number of trailing (first; low index) zeros, or kNumBits if all bits are clear.
    uint64_t CountTrailingZeros() const
    {
        for (uint64_t i = 0; i < kNumBlocks - 1; ++i)
        {
            if (const uint64_t block = m_block[i])
                return (i << 6ULL) + FirstSetBitIndex_U64(block);
        }

        if (const uint64_t block = m_block[kNumBlocks - 1] & LastBlockMask())
            return ((kNumBlocks - 1) << 6ULL) + FirstSetBitIndex_U64(block);

        return kNumBits;
    }

    // Return the index of the first (trailing; lowest index) set bit, or ~0ULL if all bits are clear.
    uint64_t FirstSetBitIndex() const
    {
        for (uint64_t i = 0; i < kNumBlocks - 1; ++i)
        {
            if (const uint64_t block = m_block[i])
                return (i << 6ULL) + FirstSetBitIndex_U64(block);
        }

        if (const uint64_t block = m_block[kNumBlocks - 1] & LastBlockMask())
            return ((kNumBlocks - 1) << 6ULL) + FirstSetBitIndex_U64(block);

        return ~0ULL;
    }

    // Return the index of the first (trailing; lowest index) clear bit, or ~0ULL if all bits are set.
    uint64_t FirstClearBitIndex() const
    {
        for (uint64_t i = 0; i < kNumBlocks - 1; ++i)
        {
            if (const uint64_t block = ~m_block[i])
                return (i << 6ULL) + FirstSetBitIndex_U64(block);
        }

        if (const uint64_t block = ~m_block[kNumBlocks - 1] & LastBlockMask())
            return ((kNumBlocks - 1) << 6ULL) + FirstSetBitIndex_U64(block);

        return ~0ULL;
    }

    // Return the index of the last (leading; highest index) set bit, or ~0ULL if all bits are clear.
    uint64_t LastSetBitIndex() const
    {
        if (const uint64_t block = m_block[kNumBlocks - 1] & LastBlockMask())
            return ((kNumBlocks - 1) << 6ULL) + LastSetBitIndex_U64(block);

        for (uint64_t i = kNumBlocks - 2; int64_t(i) >= 0; --i)
        {
            if (const uint64_t block = m_block[i])
                return (i << 6ULL) + LastSetBitIndex_U64(block);
        }

        return ~0ULL;
    }

    // Return the index of the last (leading; highest index) clear bit, or ~0ULL if all bits are set.
    uint64_t LastClearBitIndex() const
    {
        if (const uint64_t block = ~m_block[kNumBlocks - 1] & LastBlockMask())
            return ((kNumBlocks - 1) << 6ULL) + LastSetBitIndex_U64(block);

        for (uint64_t i = kNumBlocks - 2; int64_t(i) >= 0; --i)
        {
            if (const uint64_t block = ~m_block[i])
                return (i << 6ULL) + LastSetBitIndex_U64(block);
        }

        return ~0ULL;
    }

    // Return the index of the next-lowest-index set bit before and not including i, or ~0ULL if there are no set
    // bits before the ith bit.
    uint64_t PrevSetBitIndex(uint64_t i) const
    {
        ASSERT(i < kNumBits);

        uint64_t iBlock = i >> 6ULL;

        if (const uint64_t block = m_block[iBlock] & ((1ULL << (i & 63ULL)) - 1ULL))
            return (iBlock << 6ULL) + LastSetBitIndex_U64(block);

        for (--iBlock; int64_t(iBlock) >= 0; --iBlock)
        {
            if (const uint64_t block = m_block[iBlock])
                return (iBlock << 6ULL) + LastSetBitIndex_U64(block);
        }

        return ~0ULL;
    }

    // Return the index of the next-lowest-index clear bit before and not including i, or ~0ULL if there are no clear
    // bits before the ith bit.
    uint64_t PrevClearBitIndex(uint64_t i) const
    {
        ASSERT(i < kNumBits);

        uint64_t iBlock = i >> 6ULL;

        if (const uint64_t block = ~m_block[iBlock] & ((1ULL << (i & 63ULL)) - 1ULL))
            return (iBlock << 6ULL) + LastSetBitIndex_U64(block);

        for (--iBlock; int64_t(iBlock) >= 0; --iBlock)
        {
            if (const uint64_t block = ~m_block[iBlock])
                return (iBlock << 6ULL) + LastSetBitIndex_U64(block);
        }

        return ~0ULL;
    }

    // Return the index of the next-highest-index set bit after and not including i, or ~0ULL if there are no set
    // bits after the ith bit.
    uint64_t NextSetBitIndex(uint64_t i) const
    {
        ASSERT(i < kNumBits);

        uint64_t iBlock = i >> 6ULL;

        if (iBlock == kNumBlocks - 1)
        {
            if (const uint64_t block = m_block[kNumBlocks - 1] & ((~1ULL) << (i & 63ULL)) & LastBlockMask())
                return ((kNumBlocks - 1) << 6ULL) + FirstSetBitIndex_U64(block);
        }
        else
        {
            if (const uint64_t block = m_block[iBlock] & ((~1ULL) << (i & 63ULL)))
                return (iBlock << 6ULL) + FirstSetBitIndex_U64(block);

            for (++iBlock; iBlock < kNumBlocks - 1; ++iBlock)
            {
                if (const uint64_t block = m_block[iBlock])
                    return (iBlock << 6ULL) + FirstSetBitIndex_U64(block);
            }

            if (const uint64_t block = m_block[kNumBlocks - 1] & LastBlockMask())
                return ((kNumBlocks - 1) << 6ULL) + FirstSetBitIndex_U64(block);
        }

        return ~0ULL;
    }

    // Return the index of the next-highest-index clear bit after and not including i, or ~0ULL if there are no clear
    // bits after the ith bit.
    uint64_t NextClearBitIndex(uint64_t i) const
    {
        ASSERT(i < kNumBits);

        uint64_t iBlock = i >> 6ULL;

        if (iBlock == kNumBlocks - 1)
        {
            if (const uint64_t block = ~m_block[kNumBlocks - 1] & ((~1ULL) << (i & 63ULL)) & LastBlockMask())
                return ((kNumBlocks - 1) << 6ULL) + FirstSetBitIndex_U64(block);
        }
        else
        {
            if (const uint64_t block = ~m_block[iBlock] & ((~1ULL) << (i & 63ULL)))
                return (iBlock << 6ULL) + FirstSetBitIndex_U64(block);

            for (++iBlock; iBlock < kNumBlocks - 1; ++iBlock)
            {
                if (const uint64_t block = ~m_block[iBlock])
                    return (iBlock << 6ULL) + FirstSetBitIndex_U64(block);
            }

            if (const uint64_t block = ~m_block[kNumBlocks - 1] & LastBlockMask())
                return ((kNumBlocks - 1) << 6ULL) + FirstSetBitIndex_U64(block);
        }

        return ~0ULL;
    }

    // Return the index of the nth set bit, where n starts at 0, or ~0ULL if there are n or fewer set bits.
    uint64_t NthSetBitIndex(uint64_t n) const
    {
        for (uint64_t iBlock = 0; iBlock < kNumBlocks - 1; ++iBlock)
        {
            uint64_t iBit;
            if (NthBitHelper(iBit, n, iBlock, m_block[iBlock]))
                return iBit;
        }

        {
            uint64_t iBit;
            if (NthBitHelper(iBit, n, kNumBlocks - 1, m_block[kNumBlocks - 1] & LastBlockMask()))
                return iBit;
        }

        return ~0ULL;
    }

    // Return the index of the nth clear bit, where n starts at 0, or ~0ULL if there are n or fewer set bits.
    uint64_t NthClearBitIndex(uint64_t n) const
    {
        for (uint64_t iBlock = 0; iBlock < kNumBlocks - 1; ++iBlock)
        {
            uint64_t iBit;
            if (NthBitHelper(iBit, n, iBlock, ~m_block[iBlock]))
                return iBit;
        }

        {
            uint64_t iBit;
            if (NthBitHelper(iBit, n, kNumBlocks - 1, ~m_block[kNumBlocks - 1] & LastBlockMask()))
                return iBit;
        }

        return ~0ULL;
    }

    // Return the index of the start of the first block of n consecutive set bits, or ~0ULL if there is no such block.
    uint64_t FirstBlockOfNSetBits(uint64_t n) const
    {
        ASSERT(n != 0);

        uint64_t iBit = 0;
        for (uint64_t iBlock = 0; iBlock < kNumBlocks - 1; ++iBlock)
        {
            if (FirstBlockOfNBitsHelper(iBit, n, iBlock, ~m_block[iBlock]))
                return iBit;
        }

        if (FirstBlockOfNBitsHelper(iBit, n, kNumBlocks - 1, ~(m_block[kNumBlocks - 1] & LastBlockMask())))
            return iBit;

        return ~0ULL;
    }

    // Return the index of the start of the first block of n consecutive set bits aligned to alignment,
    // or ~0ULL if there is no such block.
    uint64_t FirstAlignedBlockOfNSetBits(uint64_t n, uint64_t alignment) const
    {
        ASSERT(n);
        ASSERT(IsPowerOf2AndNotZero_U64(alignment));

        if (alignment >= 64ULL)
        {
            const uint64_t alignMask = alignment - 1ULL;
            uint64_t iBit = 0;
            for (uint64_t iBlock = 0; iBlock < kNumBlocks - 1; ++iBlock)
            {
                if (FirstHighAlignedBlockOfNBitsHelper(iBit, alignMask, n, iBlock, ~m_block[iBlock]))
                    return iBit;
            }

            if (FirstHighAlignedBlockOfNBitsHelper(iBit, alignMask, n, kNumBlocks - 1, ~(m_block[kNumBlocks - 1] & LastBlockMask())))
                return iBit;
        }
        else
        {
            const uint64_t validBits = AlignmentMask(alignment);
            const uint64_t alignMask = ~(alignment - 1ULL);

            uint64_t iBit = 0;
            for (uint64_t iBlock = 0; iBlock < kNumBlocks - 1; ++iBlock)
            {
                if (FirstLowAlignedBlockOfNBitsHelper(iBit, alignMask, validBits, n, iBlock, ~m_block[iBlock]))
                    return iBit;
            }

            if (FirstLowAlignedBlockOfNBitsHelper(iBit, alignMask, validBits, n, kNumBlocks - 1, ~(m_block[kNumBlocks - 1] & LastBlockMask())))
                return iBit;
        }

        return ~0ULL;
    }

    // Return the index of the start of the first block of n consecutive clear bits, or ~0ULL if there is no such block.
    uint64_t FirstBlockOfNClearBits(uint64_t n) const
    {
        ASSERT(n != 0);

        uint64_t iBit = 0;
        for (uint64_t iBlock = 0; iBlock < kNumBlocks - 1; ++iBlock)
        {
            if (FirstBlockOfNBitsHelper(iBit, n, iBlock, m_block[iBlock]))
                return iBit;
        }

        if (FirstBlockOfNBitsHelper(iBit, n, kNumBlocks - 1, m_block[kNumBlocks - 1] | ~LastBlockMask()))
            return iBit;

        return ~0ULL;
    }

    // Return the index of the start of the first block of n consecutive clear bits aligned to alignment,
    // or ~0ULL if there is no such block.
    uint64_t FirstAlignedBlockOfNClearBits(uint64_t n, uint64_t alignment) const
    {
        ASSERT(n);
        ASSERT(IsPowerOf2AndNotZero_U64(alignment));

        if (alignment >= 64ULL)
        {
            const uint64_t alignMask = alignment - 1ULL;
            uint64_t iBit = 0;
            for (uint64_t iBlock = 0; iBlock < kNumBlocks - 1; ++iBlock)
            {
                if (FirstHighAlignedBlockOfNBitsHelper(iBit, alignMask, n, iBlock, m_block[iBlock]))
                    return iBit;
            }

            if (FirstHighAlignedBlockOfNBitsHelper(iBit, alignMask, n, kNumBlocks - 1, m_block[kNumBlocks - 1] | ~LastBlockMask()))
                return iBit;
        }
        else
        {
            const uint64_t validBits = AlignmentMask(alignment);
            const uint64_t alignMask = ~(alignment - 1ULL);

            uint64_t iBit = 0;
            for (uint64_t iBlock = 0; iBlock < kNumBlocks - 1; ++iBlock)
            {
                if (FirstLowAlignedBlockOfNBitsHelper(iBit, alignMask, validBits, n, iBlock, m_block[iBlock]))
                    return iBit;
            }

            if (FirstLowAlignedBlockOfNBitsHelper(iBit, alignMask, validBits, n, kNumBlocks - 1, m_block[kNumBlocks - 1] | ~LastBlockMask()))
                return iBit;
        }

        return ~0ULL;
    }

    // Mask of the valid (in-use) bits of the last block.
    static constexpr uint64_t LastBlockMask()
    {
        return ~0ULL >> (-kNumBits & 63ULL);
    }

    void operator|=(const BitArray<kNumBits>& __restrict other)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] |= other.m_block[i];
        }
    }

    void OrNot(const BitArray<kNumBits>& __restrict other)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] |= ~other.m_block[i];
        }
    }

    void NotOr(const BitArray<kNumBits>& __restrict other)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] = ~m_block[i] | other.m_block[i];
        }
    }

    void NotOrNot(const BitArray<kNumBits>& __restrict other)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] = ~m_block[i] | ~other.m_block[i];
        }
    }

    void operator^=(const BitArray<kNumBits>& __restrict other)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] ^= other.m_block[i];
        }
    }

    void XorNot(const BitArray<kNumBits>& __restrict other)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] ^= ~other.m_block[i];
        }
    }

    void NotXor(const BitArray<kNumBits>& __restrict other)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] = ~m_block[i] ^ other.m_block[i];
        }
    }

    void NotXorNot(const BitArray<kNumBits>& __restrict other)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] = ~m_block[i] ^ ~other.m_block[i];
        }
    }

    void operator&=(const BitArray<kNumBits>& __restrict other)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] &= other.m_block[i];
        }
    }

    void AndNot(const BitArray<kNumBits>& __restrict other)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] &= ~other.m_block[i];
        }
    }

    void NotAnd(const BitArray<kNumBits>& __restrict other)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] = ~m_block[i] & other.m_block[i];
        }
    }

    void NotAndNot(const BitArray<kNumBits>& __restrict other)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] = ~m_block[i] & ~other.m_block[i];
        }
    }

    void Invert()
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] = ~m_block[i];
        }
    }

    void AssignNot(const BitArray<kNumBits>& __restrict other)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] = ~other.m_block[i];
        }
    }

    // but will it?
    void Blend(const BitArray<kNumBits>& __restrict other, const BitArray<kNumBits>& __restrict mask)
    {
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            m_block[i] = (m_block[i] & ~mask.m_block[i]) | (other.m_block[i] & mask.m_block[i]);
        }
    }

    friend BitArray<kNumBits> operator|(const BitArray<kNumBits>& __restrict a, const BitArray<kNumBits>& __restrict b)
    {
        BitArray<kNumBits> ret;
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            ret.m_block[i] = a.m_block[i] | b.m_block[i];
        }
        return ret;
    }

    friend BitArray<kNumBits> OrNot(const BitArray<kNumBits>& __restrict a, const BitArray<kNumBits>& __restrict b)
    {
        BitArray<kNumBits> ret;
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            ret.m_block[i] = a.m_block[i] | ~b.m_block[i];
        }
        return ret;
    }

    friend BitArray<kNumBits> NotOrNot(const BitArray<kNumBits>& __restrict a, const BitArray<kNumBits>& __restrict b)
    {
        BitArray<kNumBits> ret;
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            ret.m_block[i] = ~a.m_block[i] | ~b.m_block[i];
        }
        return ret;
    }

    friend BitArray<kNumBits> operator^(const BitArray<kNumBits>& __restrict a, const BitArray<kNumBits>& __restrict b)
    {
        BitArray<kNumBits> ret;
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            ret.m_block[i] = a.m_block[i] ^ b.m_block[i];
        }
        return ret;
    }

    friend BitArray<kNumBits> XorNot(const BitArray<kNumBits>& __restrict a, const BitArray<kNumBits>& __restrict b)
    {
        BitArray<kNumBits> ret;
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            ret.m_block[i] = a.m_block[i] ^ ~b.m_block[i];
        }
        return ret;
    }

    friend BitArray<kNumBits> NotXorNot(const BitArray<kNumBits>& __restrict a, const BitArray<kNumBits>& __restrict b)
    {
        BitArray<kNumBits> ret;
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            ret.m_block[i] = ~a.m_block[i] ^ ~b.m_block[i];
        }
        return ret;
    }

    friend BitArray<kNumBits> operator&(const BitArray<kNumBits>& __restrict a, const BitArray<kNumBits>& __restrict b)
    {
        BitArray<kNumBits> ret;
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            ret.m_block[i] = a.m_block[i] & b.m_block[i];
        }
        return ret;
    }

    friend BitArray<kNumBits> AndNot(const BitArray<kNumBits>& __restrict a, const BitArray<kNumBits>& __restrict b)
    {
        BitArray<kNumBits> ret;
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            ret.m_block[i] = a.m_block[i] & ~b.m_block[i];
        }
        return ret;
    }

    friend BitArray<kNumBits> NotAndNot(const BitArray<kNumBits>& __restrict a, const BitArray<kNumBits>& __restrict b)
    {
        BitArray<kNumBits> ret;
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            ret.m_block[i] = ~a.m_block[i] & ~b.m_block[i];
        }
        return ret;
    }

    friend BitArray<kNumBits> operator~(const BitArray<kNumBits>& __restrict other)
    {
        BitArray<kNumBits> ret;
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            ret.m_block[i] = ~other.m_block[i];
        }
        return ret;
    }

    // but will it?
    friend BitArray<kNumBits> Blend(const BitArray<kNumBits>& __restrict a, const BitArray<kNumBits>& __restrict b, const BitArray<kNumBits>& __restrict mask)
    {
        BitArray<kNumBits> ret;
        for (uint64_t i = 0; i < kNumBlocks; ++i)
        {
            ret.m_block[i] = (a.m_block[i] & ~mask.m_block[i]) | (b.m_block[i] & mask.m_block[i]);
        }
        return ret;
    }

    bool operator==(const BitArray<kNumBits>& __restrict other) const
    {
        for (uint64_t i = 0; i < kNumBlocks - 1; ++i)
        {
            if (m_block[i] != other.m_block[i])
                return false;
        }

        if ((m_block[kNumBlocks - 1] & LastBlockMask()) != (other.m_block[kNumBlocks - 1] & LastBlockMask()))
            return false;

        return true;
    }

    bool operator!=(const BitArray<kNumBits>& __restrict other) const
    {
        return !(*this == other);
    }

    // Left shift (note that shift amount is modulo 64).
    void operator<<=(uint64_t s)
    {
        s &= 63ULL;

        if (s == 0)
            return;

        uint64_t prevBlock = m_block[0];
        m_block[0] = prevBlock << s;
        for (uint64_t i = 1; i < kNumBlocks; ++i)
        {
            const uint64_t newBlock = (prevBlock >> (64 - s)) | (m_block[i] << s);
            prevBlock = m_block[i];
            m_block[i] = newBlock;
        }
    }

    // Right shift (note that shift amount is modulo 64).
    void operator>>=(uint64_t s)
    {
        s &= 63ULL;

        if (s == 0)
            return;

        if (kNumBlocks == 1)
        {
            m_block[0] = (m_block[0] & LastBlockMask()) >> s;
        }
        else
        {
            for (uint64_t i = 0; i < kNumBlocks - 2; ++i)
            {
                m_block[i] = (m_block[i + 1] << (64 - s)) | (m_block[i] >> s);
            }

            const uint64_t block = m_block[kNumBlocks - 1] & LastBlockMask();
            m_block[kNumBlocks - 2] = (block << (64 - s)) | (m_block[kNumBlocks - 2] >> s);
            m_block[kNumBlocks - 1] = block >> s;
        }
    }

    // Left shift (note that shift amount is modulo 64).
    friend BitArray<kNumBits> operator<<(const BitArray<kNumBits>& __restrict other, uint64_t s)
    {
        s &= 63ULL;
        if (s == 0)
            return other;

        BitArray<kNumBits> ret;
        ret.m_block[0] = other.m_block[0] << s;
        for (uint64_t i = 1; i < kNumBlocks; ++i)
        {
            ret.m_block[i] = (other.m_block[i - 1] >> (64 - s)) | (other.m_block[i] << s);
        }
        return ret;
    }

    // Right shift (note that shift amount is modulo 64).
    friend BitArray<kNumBits> operator>>(const BitArray<kNumBits>& __restrict other, uint64_t s)
    {
        s &= 63ULL;
        if (s == 0)
            return other;

        BitArray<kNumBits> ret;
        if (kNumBlocks == 1)
        {
            ret.m_block[0] = (other.m_block[0] & LastBlockMask()) >> s;
        }
        else
        {
            for (uint64_t i = 0; i < kNumBlocks - 2; ++i)
            {
                ret.m_block[i] = (other.m_block[i + 1] << (64 - s)) | (other.m_block[i] >> s);
            }

            const uint64_t block = other.m_block[kNumBlocks - 1] & LastBlockMask();
            ret.m_block[kNumBlocks - 2] = (block << (64 - s)) | (other.m_block[kNumBlocks - 2] >> s);
            ret.m_block[kNumBlocks - 1] = block >> s;
        }
        return ret;
    }

    class EndIterator
    {
    };

    class Iterator
    {
    public:
        Iterator(const uint64_t* __restrict v) : m_v(v)
        {
            for (m_iBlock = 0; m_iBlock < kNumBlocks - 1; ++m_iBlock)
            {
                m_block = m_v[m_iBlock];
                if (m_block)
                {
                    m_iBit = (m_iBlock << 6ULL) + FirstSetBitIndex_U64(m_block);
                    return;
                }
            }

            m_block = m_v[kNumBlocks - 1];
            m_iBit = ((kNumBlocks - 1) << 6ULL) + FirstSetBitIndex_U64(m_block);
        }

        uint64_t operator*() const
        {
            return m_iBit;
        }

        Iterator& operator++()
        {
            m_block = ClearFirstSetBit_U64(m_block);
            for (;;)
            {
                if (m_block)
                {
                    m_iBit = (m_iBlock << 6ULL) + FirstSetBitIndex_U64(m_block);
                    return *this;
                }

                if (++m_iBlock >= kNumBlocks)
                {
                    m_iBit = ~0ULL;
                    return *this;
                }

                m_block = m_v[m_iBlock];
            }
        }

        bool operator==(const Iterator& other) const
        {
            return m_iBit == other.m_iBit;
        }

        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }

        bool operator==(const EndIterator&) const
        {
            return m_iBit >= kNumBits;
        }

        bool operator!=(const EndIterator&) const
        {
            return m_iBit < kNumBits;
        }

    private:
        const uint64_t* __restrict m_v;
        uint64_t m_block;
        uint64_t m_iBlock;
        uint64_t m_iBit;
    };

    Iterator begin() const
    {
        return m_block;
    }

    EndIterator end() const
    {
        return {};
    }

private:
    static uint64_t AlignmentMask(uint64_t alignment)
    {
        uint64_t ret = 0xFFFFFFFFFFFFFFFFULL;
        if (alignment == 2)
            ret = 0x5555555555555555ULL;
        if (alignment == 4)
            ret = 0x1111111111111111ULL;
        if (alignment == 8)
            ret = 0x0101010101010101ULL;
        if (alignment == 16)
            ret = 0x0001000100010001ULL;
        if (alignment == 32)
            ret = 0x0000000100000001ULL;
        return ret;
    }

    static bool NthBitHelper(uint64_t& iBit, uint64_t& n, uint64_t iBlock, uint64_t block)
    {
        uint64_t set = CountSetBits_U64(block);
        if (set > n)
        {
            iBit = iBlock << 6ULL;

            set = CountSetBits_U32(uint32_t(block));
            if (set <= n)
            {
                block >>= 32;
                iBit += 32;
                n -= set;
            }

            set = CountSetBits_U32(uint32_t(block) & 0xFFFFU);
            if (set <= n)
            {
                block >>= 16;
                iBit += 16;
                n -= set;
            }

            set = CountSetBits_U32(uint32_t(block) & 0xFFU);
            if (set <= n)
            {
                block >>= 8;
                iBit += 8;
                n -= set;
            }

            do
            {
                n -= uint32_t(block) & 1U;
                block >>= 1;
                ++iBit;
            } while (n != ~0ULL);

            --iBit;

            return true;
        }

        n -= set;

        return false;
    }

    static bool FirstBlockOfNBitsHelper(uint64_t& iStart, uint64_t n, uint64_t iBlock, uint64_t block)
    {
        const uint64_t iBit = iBlock << 6ULL;
        const uint64_t blockStartRun = CountTrailingZeros_U64(block);

        if (iBit + blockStartRun >= iStart + n)
            return true;

        const uint64_t blockEndRun = CountLeadingZeros_U64(block);

        if (int64_t(62ULL - blockStartRun - blockEndRun) >= int64_t(n))
        {
            const uint64_t blockMidRun = FirstNClearBitsIndex_U64(block, uint32_t(n));
            if (blockMidRun < 64ULL)
            {
                iStart = iBit + blockMidRun;
                return true;
            }
        }

        const uint64_t iCandidateStart = iBit + 64ULL - blockEndRun;
        if (blockEndRun < 64ULL)
            iStart = iCandidateStart;

        return false;
    }

    static bool FirstHighAlignedBlockOfNBitsHelper(uint64_t& iStart, uint64_t alignMask, uint64_t n, uint64_t iBlock, uint64_t block)
    {
        const uint64_t iBit = iBlock << 6ULL;
        const uint64_t blockStartRun = CountTrailingZeros_U64(block);
        if (iBit + blockStartRun >= iStart + n)
            return true;
        const uint64_t iCandidateStart = (iBit + 64ULL + alignMask) & ~alignMask;
        if (blockStartRun < 64ULL)
            iStart = iCandidateStart;
        return false;
    }

    static bool FirstLowAlignedBlockOfNBitsHelper(uint64_t& iStart, uint64_t alignMask, uint64_t validBits, uint64_t n, uint64_t iBlock, uint64_t block)
    {
        const uint64_t iBit = iBlock << 6ULL;
        const uint64_t blockStartRun = CountTrailingZeros_U64(block);
        if (iBit + blockStartRun >= iStart + n)
            return true;
        const uint64_t blockEndRun = CountLeadingZeros_U64(block);

        if (int64_t(62ULL - blockStartRun - blockEndRun) >= int64_t(n))
        {
            const uint64_t blockMidRun = FirstNClearBitsIndex_U64(block, uint32_t(n), validBits);
            if (blockMidRun < 64ULL)
            {
                iStart = iBit + blockMidRun;
                return true;
            }
        }

        const uint64_t alignedBlockEndRun = blockEndRun & alignMask;
        const uint64_t iCandidateStart = iBit + 64ULL - alignedBlockEndRun;
        if (alignedBlockEndRun < 64ULL)
            iStart = iCandidateStart;

        return false;
    }

    uint64_t m_block[kNumBlocks];
};

template <class T>
class SmallBitArray
{
    template <class U>
    struct TypeEnforcer
    {
        static constexpr bool kValid = false;
    };

    struct TypeEnforcerValidType
    {
        static constexpr bool kValid = true;
    };

    template <>
    struct TypeEnforcer<uint8_t> : TypeEnforcerValidType {};

    template <>
    struct TypeEnforcer<uint16_t> : TypeEnforcerValidType {};

    template <>
    struct TypeEnforcer<uint32_t> : TypeEnforcerValidType {};

    template <>
    struct TypeEnforcer<uint64_t> : TypeEnforcerValidType {};

    static_assert(TypeEnforcer<T>::kValid, "Only uint[8|16|32|64]_t specializations permitted.");

public:
    static constexpr uint64_t kNumBits = 8 * sizeof(T);

    SmallBitArray<T>() : m_block(T(0))
    {
    }

    explicit SmallBitArray<T>(T block) : m_block(block)
    {
    }

    explicit operator T() const
    {
        return m_block;
    }

    void operator|=(SmallBitArray<T> other)
    {
        m_block |= other.m_block;
    }

    void operator^=(SmallBitArray<T> other)
    {
        m_block ^= other.m_block;
    }

    void operator&=(SmallBitArray<T> other)
    {
        m_block &= other.m_block;
    }

    friend SmallBitArray<T> operator|(SmallBitArray<T> a, SmallBitArray<T> b)
    {
        return SmallBitArray<T>(a.m_block | b.m_block);
    }

    friend SmallBitArray<T> operator^(SmallBitArray<T> a, SmallBitArray<T> b)
    {
        return SmallBitArray<T>(a.m_block ^ b.m_block);
    }

    friend SmallBitArray<T> operator&(SmallBitArray<T> a, SmallBitArray<T> b)
    {
        return SmallBitArray<T>(a.m_block & b.m_block);
    }

    friend SmallBitArray<T> operator~(SmallBitArray<T> other)
    {
        return SmallBitArray<T>(~other.m_block);
    }

    bool operator==(SmallBitArray<T> other) const
    {
        return m_block == other.m_block;
    }

    bool operator!=(SmallBitArray<T> other) const
    {
        return !(*this == other);
    }

    class EndIterator
    {
    };

    class Iterator
    {
    public:
        Iterator(T block) : m_block(block), m_iBit(FirstSetBitIndex_U64(block))
        {
        }

        uint64_t operator*() const
        {
            return m_iBit;
        }

        Iterator& operator++()
        {
            m_block = ClearFirstSetBit(m_block);
            m_iBit = FirstSetBitIndex(m_block);
            return *this;
        }

        bool operator==(const Iterator& other) const
        {
            return m_iBit == other.m_iBit;
        }

        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }

        bool operator==(const EndIterator&) const
        {
            return m_iBit == 8 * sizeof(T);
        }

        bool operator!=(const EndIterator&) const
        {
            return m_iBit != 8 * sizeof(T);
        }

    private:
        static uint8_t ClearFirstSetBit(uint8_t x)
        {
            return ClearFirstSetBit_U8(x);
        }

        static uint16_t ClearFirstSetBit(uint16_t x)
        {
            return ClearFirstSetBit_U16(x);
        }

        static uint32_t ClearFirstSetBit(uint32_t x)
        {
            return ClearFirstSetBit_U32(x);
        }

        static uint64_t ClearFirstSetBit(uint64_t x)
        {
            return ClearFirstSetBit_U64(x);
        }

        static uint32_t FirstSetBitIndex(uint8_t x)
        {
            return FirstSetBitIndex_U8(x);
        }

        static uint32_t FirstSetBitIndex(uint16_t x)
        {
            return FirstSetBitIndex_U16(x);
        }

        static uint32_t FirstSetBitIndex(uint32_t x)
        {
            return FirstSetBitIndex_U32(x);
        }

        static uint64_t FirstSetBitIndex(uint64_t x)
        {
            return FirstSetBitIndex_U64(x);
        }

        uint64_t m_iBit;
        T m_block;
    };

    Iterator begin() const
    {
        return m_block;
    }

    EndIterator end() const
    {
        return {};
    }

private:
    T m_block;
};

#if !defined(__clang__) && !defined(__GNUC__) && defined(_MSC_VER)
#pragma warning( pop )
#endif

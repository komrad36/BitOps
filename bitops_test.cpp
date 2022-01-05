/*******************************************************************
*
*    Author: Kareem Omar
*    kareem.h.omar@gmail.com
*    https://github.com/komrad36
*
*    Last updated Sept 20, 2021
*******************************************************************/

#include <iostream>

#include "bitops.h"

#define ASSERT_TRUE(a) do { if (!(a)) { std::cerr << "FAIL: expected true for " << #a << ", got false\n"; __debugbreak(); } } while (0)
#define ASSERT_FALSE(a) do { if ((a)) { std::cerr << "FAIL: expected false for " << #a << ", got true\n"; __debugbreak(); } } while (0)

template <class T>
static void TestPrintHelper(T x)
{
    std::cout << x;
}

template <>
void TestPrintHelper(uint8_t x)
{
    std::cout << int(x);
}

#define ASSERT_BIN_OP(a, b, op) do {                                                            \
    const auto& va = (a);                                                                       \
    const auto& vb = (b);                                                                       \
    if (!(va op vb))                                                                            \
    {                                                                                           \
        std::cerr << "FAIL: expected " << #a << " " << #op << " " << #b << " (evaluates to ";   \
        TestPrintHelper(va);                                                                    \
        std::cerr << " " << #op << " ";                                                         \
        TestPrintHelper(vb);                                                                    \
        std::cerr << ")\n";                                                                     \
        __debugbreak();                                                                         \
    }                                                                                           \
} while (0)

#define ASSERT_EQ(a, b) ASSERT_BIN_OP(a, b, ==)
#define ASSERT_NE(a, b) ASSERT_BIN_OP(a, b, !=)
#define ASSERT_LT(a, b) ASSERT_BIN_OP(a, b, <)
#define ASSERT_LE(a, b) ASSERT_BIN_OP(a, b, <=)
#define ASSERT_GT(a, b) ASSERT_BIN_OP(a, b, >)
#define ASSERT_GE(a, b) ASSERT_BIN_OP(a, b, >=)

static auto Overload_FirstSetBitMask(uint8_t x)
{
    return FirstSetBitMask_U8(x);
}

static auto Overload_FirstSetBitMask(uint16_t x)
{
    return FirstSetBitMask_U16(x);
}

static auto Overload_FirstSetBitMask(uint32_t x)
{
    return FirstSetBitMask_U32(x);
}

static auto Overload_FirstSetBitMask(uint64_t x)
{
    return FirstSetBitMask_U64(x);
}

static auto Overload_FirstSetBitIndex(uint8_t x)
{
    return FirstSetBitIndex_U8(x);
}

static auto Overload_FirstSetBitIndex(uint16_t x)
{
    return FirstSetBitIndex_U16(x);
}

static auto Overload_FirstSetBitIndex(uint32_t x)
{
    return FirstSetBitIndex_U32(x);
}

static auto Overload_FirstSetBitIndex(uint64_t x)
{
    return FirstSetBitIndex_U64(x);
}

static auto Overload_FirstClearBitMask(uint8_t x)
{
    return FirstClearBitMask_U8(x);
}

static auto Overload_FirstClearBitMask(uint16_t x)
{
    return FirstClearBitMask_U16(x);
}

static auto Overload_FirstClearBitMask(uint32_t x)
{
    return FirstClearBitMask_U32(x);
}

static auto Overload_FirstClearBitMask(uint64_t x)
{
    return FirstClearBitMask_U64(x);
}

static auto Overload_FirstClearBitIndex(uint8_t x)
{
    return FirstClearBitIndex_U8(x);
}

static auto Overload_FirstClearBitIndex(uint16_t x)
{
    return FirstClearBitIndex_U16(x);
}

static auto Overload_FirstClearBitIndex(uint32_t x)
{
    return FirstClearBitIndex_U32(x);
}

static auto Overload_FirstClearBitIndex(uint64_t x)
{
    return FirstClearBitIndex_U64(x);
}

static auto Overload_LastSetBitMask(uint8_t x)
{
    return LastSetBitMask_U8(x);
}

static auto Overload_LastSetBitMask(uint16_t x)
{
    return LastSetBitMask_U16(x);
}

static auto Overload_LastSetBitMask(uint32_t x)
{
    return LastSetBitMask_U32(x);
}

static auto Overload_LastSetBitMask(uint64_t x)
{
    return LastSetBitMask_U64(x);
}

static auto Overload_LastSetBitIndex(uint8_t x)
{
    return LastSetBitIndex_U8(x);
}

static auto Overload_LastSetBitIndex(uint16_t x)
{
    return LastSetBitIndex_U16(x);
}

static auto Overload_LastSetBitIndex(uint32_t x)
{
    return LastSetBitIndex_U32(x);
}

static auto Overload_LastSetBitIndex(uint64_t x)
{
    return LastSetBitIndex_U64(x);
}

static auto Overload_LastClearBitMask(uint8_t x)
{
    return LastClearBitMask_U8(x);
}

static auto Overload_LastClearBitMask(uint16_t x)
{
    return LastClearBitMask_U16(x);
}

static auto Overload_LastClearBitMask(uint32_t x)
{
    return LastClearBitMask_U32(x);
}

static auto Overload_LastClearBitMask(uint64_t x)
{
    return LastClearBitMask_U64(x);
}

static auto Overload_LastClearBitIndex(uint8_t x)
{
    return LastClearBitIndex_U8(x);
}

static auto Overload_LastClearBitIndex(uint16_t x)
{
    return LastClearBitIndex_U16(x);
}

static auto Overload_LastClearBitIndex(uint32_t x)
{
    return LastClearBitIndex_U32(x);
}

static auto Overload_LastClearBitIndex(uint64_t x)
{
    return LastClearBitIndex_U64(x);
}

static auto Overload_ReverseBits(uint8_t x)
{
    return ReverseBits_U8(x);
}

static auto Overload_ReverseBits(uint16_t x)
{
    return ReverseBits_U16(x);
}

static auto Overload_ReverseBits(uint32_t x)
{
    return ReverseBits_U32(x);
}

static auto Overload_ReverseBits(uint64_t x)
{
    return ReverseBits_U64(x);
}

static auto Overload_LogBase2(uint8_t x)
{
    return LogBase2_U8(x);
}

static auto Overload_LogBase2(uint16_t x)
{
    return LogBase2_U16(x);
}

static auto Overload_LogBase2(uint32_t x)
{
    return LogBase2_U32(x);
}

static auto Overload_LogBase2(uint64_t x)
{
    return LogBase2_U64(x);
}

static auto Overload_RoundDownToPowerOf2(uint8_t x)
{
    return RoundDownToPowerOf2_U8(x);
}

static auto Overload_RoundDownToPowerOf2(uint16_t x)
{
    return RoundDownToPowerOf2_U16(x);
}

static auto Overload_RoundDownToPowerOf2(uint32_t x)
{
    return RoundDownToPowerOf2_U32(x);
}

static auto Overload_RoundDownToPowerOf2(uint64_t x)
{
    return RoundDownToPowerOf2_U64(x);
}

static auto Overload_FirstNSetBitsIndex(uint8_t x, uint32_t n)
{
    return FirstNSetBitsIndex_U8(x, n);
}

static auto Overload_FirstNSetBitsIndex(uint16_t x, uint32_t n)
{
    return FirstNSetBitsIndex_U16(x, n);
}

static auto Overload_FirstNSetBitsIndex(uint32_t x, uint32_t n)
{
    return FirstNSetBitsIndex_U32(x, n);
}

static auto Overload_FirstNSetBitsIndex(uint64_t x, uint32_t n)
{
    return FirstNSetBitsIndex_U64(x, n);
}

static auto Overload_FirstNSetBitsIndex(uint8_t x, uint32_t n, uint8_t validBits)
{
    return FirstNSetBitsIndex_U8(x, n, validBits);
}

static auto Overload_FirstNSetBitsIndex(uint16_t x, uint32_t n, uint16_t validBits)
{
    return FirstNSetBitsIndex_U16(x, n, validBits);
}

static auto Overload_FirstNSetBitsIndex(uint32_t x, uint32_t n, uint32_t validBits)
{
    return FirstNSetBitsIndex_U32(x, n, validBits);
}

static auto Overload_FirstNSetBitsIndex(uint64_t x, uint32_t n, uint64_t validBits)
{
    return FirstNSetBitsIndex_U64(x, n, validBits);
}

static auto Overload_LastNSetBitsIndex(uint8_t x, uint32_t n)
{
    return LastNSetBitsIndex_U8(x, n);
}

static auto Overload_LastNSetBitsIndex(uint16_t x, uint32_t n)
{
    return LastNSetBitsIndex_U16(x, n);
}

static auto Overload_LastNSetBitsIndex(uint32_t x, uint32_t n)
{
    return LastNSetBitsIndex_U32(x, n);
}

static auto Overload_LastNSetBitsIndex(uint64_t x, uint32_t n)
{
    return LastNSetBitsIndex_U64(x, n);
}

static auto Overload_LastNSetBitsIndex(uint8_t x, uint32_t n, uint8_t validBits)
{
    return LastNSetBitsIndex_U8(x, n, validBits);
}

static auto Overload_LastNSetBitsIndex(uint16_t x, uint32_t n, uint16_t validBits)
{
    return LastNSetBitsIndex_U16(x, n, validBits);
}

static auto Overload_LastNSetBitsIndex(uint32_t x, uint32_t n, uint32_t validBits)
{
    return LastNSetBitsIndex_U32(x, n, validBits);
}

static auto Overload_LastNSetBitsIndex(uint64_t x, uint32_t n, uint64_t validBits)
{
    return LastNSetBitsIndex_U64(x, n, validBits);
}

static auto Overload_FirstNClearBitsIndex(uint8_t x, uint32_t n)
{
    return FirstNClearBitsIndex_U8(x, n);
}

static auto Overload_FirstNClearBitsIndex(uint16_t x, uint32_t n)
{
    return FirstNClearBitsIndex_U16(x, n);
}

static auto Overload_FirstNClearBitsIndex(uint32_t x, uint32_t n)
{
    return FirstNClearBitsIndex_U32(x, n);
}

static auto Overload_FirstNClearBitsIndex(uint64_t x, uint32_t n)
{
    return FirstNClearBitsIndex_U64(x, n);
}

static auto Overload_FirstNClearBitsIndex(uint8_t x, uint32_t n, uint8_t validBits)
{
    return FirstNClearBitsIndex_U8(x, n, validBits);
}

static auto Overload_FirstNClearBitsIndex(uint16_t x, uint32_t n, uint16_t validBits)
{
    return FirstNClearBitsIndex_U16(x, n, validBits);
}

static auto Overload_FirstNClearBitsIndex(uint32_t x, uint32_t n, uint32_t validBits)
{
    return FirstNClearBitsIndex_U32(x, n, validBits);
}

static auto Overload_FirstNClearBitsIndex(uint64_t x, uint32_t n, uint64_t validBits)
{
    return FirstNClearBitsIndex_U64(x, n, validBits);
}

static auto Overload_LastNClearBitsIndex(uint8_t x, uint32_t n)
{
    return LastNClearBitsIndex_U8(x, n);
}

static auto Overload_LastNClearBitsIndex(uint16_t x, uint32_t n)
{
    return LastNClearBitsIndex_U16(x, n);
}

static auto Overload_LastNClearBitsIndex(uint32_t x, uint32_t n)
{
    return LastNClearBitsIndex_U32(x, n);
}

static auto Overload_LastNClearBitsIndex(uint64_t x, uint32_t n)
{
    return LastNClearBitsIndex_U64(x, n);
}

static auto Overload_LastNClearBitsIndex(uint8_t x, uint32_t n, uint8_t validBits)
{
    return LastNClearBitsIndex_U8(x, n, validBits);
}

static auto Overload_LastNClearBitsIndex(uint16_t x, uint32_t n, uint16_t validBits)
{
    return LastNClearBitsIndex_U16(x, n, validBits);
}

static auto Overload_LastNClearBitsIndex(uint32_t x, uint32_t n, uint32_t validBits)
{
    return LastNClearBitsIndex_U32(x, n, validBits);
}

static auto Overload_LastNClearBitsIndex(uint64_t x, uint32_t n, uint64_t validBits)
{
    return LastNClearBitsIndex_U64(x, n, validBits);
}

template <class T>
static T Overload_SetBitRange(uint32_t a, uint32_t b);

template<>
uint8_t Overload_SetBitRange(uint32_t a, uint32_t b)
{
    return SetBitRange_U8(a, b);
}

template<>
uint16_t Overload_SetBitRange(uint32_t a, uint32_t b)
{
    return SetBitRange_U16(a, b);
}

template<>
uint32_t Overload_SetBitRange(uint32_t a, uint32_t b)
{
    return SetBitRange_U32(a, b);
}

template<>
uint64_t Overload_SetBitRange(uint32_t a, uint32_t b)
{
    return SetBitRange_U64(a, b);
}

template <class T>
static T RefReverseBits(T x)
{
    constexpr uint64_t n = 8 * sizeof(T);
    T ret(0);
    for (uint64_t i = 0; i < n; ++i)
    {
        if (x & (T(1) << i))
            ret |= T(1) << ((n - 1) - i);
    }
    return ret;
}

// simultaneously test [First|Last][Set|Clear]Bit[Mask|Index],
// RoundDownToPowerOf2, and LogBase2.
template <class T>
static void BitTestHelper(T x, uint64_t i)
{
    constexpr uint64_t n = 8 * sizeof(T);
    const T mask = i == n ? T(0) : T(T(1) << i);
    ASSERT_EQ(Overload_FirstSetBitMask(x), mask);
    ASSERT_EQ(Overload_FirstSetBitIndex(x), i);
    ASSERT_EQ(Overload_FirstClearBitMask(T(~x)), mask);
    ASSERT_EQ(Overload_FirstClearBitIndex(T(~x)), i);
    ASSERT_EQ(Overload_LastSetBitMask(Overload_ReverseBits(x)), Overload_ReverseBits(mask));
    ASSERT_EQ(Overload_RoundDownToPowerOf2(Overload_ReverseBits(x)), Overload_ReverseBits(mask));
    ASSERT_EQ(Overload_LastClearBitMask(Overload_ReverseBits(T(~x))), Overload_ReverseBits(mask));
    if (i == n)
    {
        ASSERT_GE(Overload_LastSetBitIndex(Overload_ReverseBits(x)), n);
        ASSERT_GE(Overload_LogBase2(Overload_ReverseBits(x)), n);
        ASSERT_GE(Overload_LastClearBitIndex(Overload_ReverseBits(T(~x))), n);
    }
    else
    {
        ASSERT_EQ(Overload_LastSetBitIndex(Overload_ReverseBits(x)), (n - 1) - i);
        ASSERT_EQ(Overload_LogBase2(Overload_ReverseBits(x)), (n - 1) - i);
        ASSERT_EQ(Overload_LastClearBitIndex(Overload_ReverseBits(T(~x))), (n - 1) - i);
    }
}

// simultaneously test [First|Last]N[Set|Clear]Bits without validity mask.
template <class T>
static void NBitsTestHelper(T x, uint32_t m, uint32_t i)
{
    constexpr uint64_t n = 8 * sizeof(T);
    ASSERT_EQ(Overload_FirstNSetBitsIndex(x, m), i);
    ASSERT_EQ(Overload_FirstNClearBitsIndex(T(~x), m), i);
    if (i == n)
    {
        ASSERT_GE(Overload_LastNSetBitsIndex(Overload_ReverseBits(x), m), n);
        ASSERT_GE(Overload_LastNClearBitsIndex(Overload_ReverseBits(T(~x)), m), n);
    }
    else
    {
        ASSERT_EQ(Overload_LastNSetBitsIndex(Overload_ReverseBits(x), m), (n - 1) - i);
        ASSERT_EQ(Overload_LastNClearBitsIndex(Overload_ReverseBits(T(~x)), m), (n - 1) - i);
    }
}

// simultaneously test [First|Last]N[Set|Clear]Bits with validity mask.
template <class T>
static void NBitsTestHelper(T x, uint32_t m, T validBits, uint32_t i)
{
    constexpr uint64_t n = 8 * sizeof(T);
    ASSERT_EQ(Overload_FirstNSetBitsIndex(x, m, validBits), i);
    ASSERT_EQ(Overload_FirstNClearBitsIndex(T(~x), m, validBits), i);
    if (i == n)
    {
        ASSERT_GE(Overload_LastNSetBitsIndex(Overload_ReverseBits(x), m, Overload_ReverseBits(validBits)), n);
        ASSERT_GE(Overload_LastNClearBitsIndex(Overload_ReverseBits(T(~x)), m, Overload_ReverseBits(validBits)), n);
    }
    else
    {
        ASSERT_EQ(Overload_LastNSetBitsIndex(Overload_ReverseBits(x), m, Overload_ReverseBits(validBits)), (n - 1) - i);
        ASSERT_EQ(Overload_LastNClearBitsIndex(Overload_ReverseBits(T(~x)), m, Overload_ReverseBits(validBits)), (n - 1) - i);
    }
}

// simultaneously test [First|Last]N[Set|Clear]Bits, with and without validity mask.
template <class T>
static void NBitsTestHelper()
{
    constexpr uint64_t n = 8 * sizeof(T);
    // starting at bit i, alternate groups of j set bits and then k clear bits
    for (uint32_t i = 0; i < n; ++i)
    {
        for (uint32_t j = 0; j < n; ++j)
        {
            for (uint32_t k = 1; k < n; ++k)
            {
                T ref(0);
                for (uint32_t m = i;;)
                {
                    if (j)
                        ref |= Overload_SetBitRange<T>(m, m + j - 1 >= n ? n - 1 : m + j - 1);
                    m += j + k;
                    if (m >= n)
                        break;
                }

                // expect to find bit runs <= j at i if not off the end
                for (uint32_t m = 1; m < n; ++m)
                {
                    if (ref && m <= j && i + m <= n)
                    {
                        NBitsTestHelper(ref, m, i);
                        NBitsTestHelper(ref, m, T(0), n);
                        NBitsTestHelper(ref, m, T(-1), i);
                        NBitsTestHelper(ref, m, T(T(1) << i), i);
                        for (uint32_t o = 0; o < n; ++o)
                        {
                            const T p = T(-1) << o;
                            if (o <= i)
                            {
                                NBitsTestHelper(ref, m, p, i);
                            }
                            else
                            {
                                const uint32_t q = (o - i) / (j + k);
                                const uint32_t r = (o - i) % (j + k);
                                if (r < j && j - r >= m)
                                {
                                    NBitsTestHelper(ref, m, p, o + m <= n ? o : n);
                                }
                                else
                                {
                                    // try for start of next bank
                                    const uint32_t s = (q + 1) * (j + k) + i;
                                    NBitsTestHelper(ref, m, p, s + m <= n ? s : n);
                                }
                            }
                        }
                    }
                    else
                    {
                        NBitsTestHelper(ref, m, n);
                        NBitsTestHelper(ref, m, T(0), n);
                        NBitsTestHelper(ref, m, T(-1), n);
                    }
                }
            }
        }
    }
}

void TestBitOps()
{
    // assign bit
    {
        for (const auto x : { 0, 1, 3, 8, 10, 12, 15, 25, 35, 54, 63, 82, 85, 87, 88, 92, 93, 97, 99, 120, 128, 143, 144, 146, 150, 154, 168, 169, 194, 204, 221, 230, 255 })
        {
            for (uint32_t i = 0; i < 8; ++i)
            {
                ASSERT_EQ(AssignBit_U8(uint8_t(x), i, true), x | (uint8_t(1) << i));
                ASSERT_EQ(AssignBit_U8(uint8_t(x), i, false), x & ~(uint8_t(1) << i));
            }
        }
    }

    {
        for (const auto x : { 0, 1, 561, 1555, 7812, 9391, 9603, 9695, 11217, 11983, 21212, 24139, 25322, 25574, 27852, 30248, 30390, 32189, 36048, 46991, 47061, 47375, 49561, 50056, 50858, 52614, 54566, 55227, 55778, 58241, 61845, 63116, 65535 })
        {
            for (uint32_t i = 0; i < 16; ++i)
            {
                ASSERT_EQ(AssignBit_U16(uint16_t(x), i, true), x | (uint16_t(1) << i));
                ASSERT_EQ(AssignBit_U16(uint16_t(x), i, false), x & ~(uint16_t(1) << i));
            }
        }
    }

    {
        for (const auto x : { 0U, 1U, 121355964U, 583664479U, 689620521U, 708868965U, 1302359958U, 1838431887U, 1876920278U, 2080120591U, 2085596828U, 2103419320U, 2213316381U, 2777151632U, 2867950016U, 2954916315U, 3159206577U, 3218425283U, 3224835393U, 3304659855U, 3349972584U, 3527531268U, 3646559839U, 3650458017U, 3714306325U, 3721993123U, 3922188228U, 3984619083U, 4122549376U, 4135605450U, 4174381728U, 4232486730U, 4294967295U })
        {
            for (uint32_t i = 0; i < 32; ++i)
            {
                ASSERT_EQ(AssignBit_U32(uint32_t(x), i, true), x | (uint32_t(1) << i));
                ASSERT_EQ(AssignBit_U32(uint32_t(x), i, false), x & ~(uint32_t(1) << i));
            }
        }
    }

    {
        for (const auto x : { 0ULL, 1ULL, 1786960817022974312ULL, 2425049002781624915ULL, 3435405280726075361ULL, 4976886614525036568ULL, 5128003607746375587ULL, 6137245666376165821ULL, 7164044623269201573ULL, 7743444618495810837ULL, 7861846716777940561ULL, 8109918446058603789ULL, 8261719822741326120ULL, 8307183781656233746ULL, 8396668132838987312ULL, 8898167500217858691ULL, 8932430976418327682ULL, 9317340659163238167ULL, 9690764671846621113ULL, 11503196632009463229ULL, 11687593239772665556ULL, 12328060516207340684ULL, 13043307824879222355ULL, 13072632151264653763ULL, 14048733286625042236ULL, 14116182617975788072ULL, 14135027308327907840ULL, 14666062424071282314ULL, 15969011514599653954ULL, 16710713006078329603ULL, 16922975599666143549ULL, 18175072543214651513ULL, 18446744073709551615ULL })
        {
            for (uint32_t i = 0; i < 64; ++i)
            {
                ASSERT_EQ(AssignBit_U64(uint64_t(x), i, true), x | (uint64_t(1) << i));
                ASSERT_EQ(AssignBit_U64(uint64_t(x), i, false), x & ~(uint64_t(1) << i));
            }
        }
    }

    // assign mask
    {
        for (const auto x : { 0, 1, 3, 8, 10, 12, 15, 25, 35, 54, 63, 82, 85, 87, 88, 92, 93, 97, 99, 120, 128, 143, 144, 146, 150, 154, 168, 169, 194, 204, 221, 230, 255 })
        {
            for (const auto y : { 0, 1, 3, 8, 10, 12, 15, 25, 35, 54, 63, 82, 85, 87, 88, 92, 93, 97, 99, 120, 128, 143, 144, 146, 150, 154, 168, 169, 194, 204, 221, 230, 255 })
            {
                ASSERT_EQ(AssignMask_U8(uint8_t(x), uint8_t(y), true), x | y);
                ASSERT_EQ(AssignMask_U8(uint8_t(x), uint8_t(y), false), x & ~y);
            }
        }
    }

    {
        for (const auto x : { 0, 1, 561, 1555, 7812, 9391, 9603, 9695, 11217, 11983, 21212, 24139, 25322, 25574, 27852, 30248, 30390, 32189, 36048, 46991, 47061, 47375, 49561, 50056, 50858, 52614, 54566, 55227, 55778, 58241, 61845, 63116, 65535 })
        {
            for (const auto y : { 0, 1, 561, 1555, 7812, 9391, 9603, 9695, 11217, 11983, 21212, 24139, 25322, 25574, 27852, 30248, 30390, 32189, 36048, 46991, 47061, 47375, 49561, 50056, 50858, 52614, 54566, 55227, 55778, 58241, 61845, 63116, 65535 })
            {
                ASSERT_EQ(AssignMask_U16(uint16_t(x), uint16_t(y), true), x | y);
                ASSERT_EQ(AssignMask_U16(uint16_t(x), uint16_t(y), false), x & ~y);
            }
        }
    }

    {
        for (const auto x : { 0U, 1U, 121355964U, 583664479U, 689620521U, 708868965U, 1302359958U, 1838431887U, 1876920278U, 2080120591U, 2085596828U, 2103419320U, 2213316381U, 2777151632U, 2867950016U, 2954916315U, 3159206577U, 3218425283U, 3224835393U, 3304659855U, 3349972584U, 3527531268U, 3646559839U, 3650458017U, 3714306325U, 3721993123U, 3922188228U, 3984619083U, 4122549376U, 4135605450U, 4174381728U, 4232486730U, 4294967295U })
        {
            for (const auto y : { 0U, 1U, 121355964U, 583664479U, 689620521U, 708868965U, 1302359958U, 1838431887U, 1876920278U, 2080120591U, 2085596828U, 2103419320U, 2213316381U, 2777151632U, 2867950016U, 2954916315U, 3159206577U, 3218425283U, 3224835393U, 3304659855U, 3349972584U, 3527531268U, 3646559839U, 3650458017U, 3714306325U, 3721993123U, 3922188228U, 3984619083U, 4122549376U, 4135605450U, 4174381728U, 4232486730U, 4294967295U })
            {
                ASSERT_EQ(AssignMask_U32(uint32_t(x), uint32_t(y), true), x | y);
                ASSERT_EQ(AssignMask_U32(uint32_t(x), uint32_t(y), false), x & ~y);
            }
        }
    }

    {
        for (const auto x : { 0ULL, 1ULL, 1786960817022974312ULL, 2425049002781624915ULL, 3435405280726075361ULL, 4976886614525036568ULL, 5128003607746375587ULL, 6137245666376165821ULL, 7164044623269201573ULL, 7743444618495810837ULL, 7861846716777940561ULL, 8109918446058603789ULL, 8261719822741326120ULL, 8307183781656233746ULL, 8396668132838987312ULL, 8898167500217858691ULL, 8932430976418327682ULL, 9317340659163238167ULL, 9690764671846621113ULL, 11503196632009463229ULL, 11687593239772665556ULL, 12328060516207340684ULL, 13043307824879222355ULL, 13072632151264653763ULL, 14048733286625042236ULL, 14116182617975788072ULL, 14135027308327907840ULL, 14666062424071282314ULL, 15969011514599653954ULL, 16710713006078329603ULL, 16922975599666143549ULL, 18175072543214651513ULL, 18446744073709551615ULL })
        {
            for (const auto y : { 0ULL, 1ULL, 1786960817022974312ULL, 2425049002781624915ULL, 3435405280726075361ULL, 4976886614525036568ULL, 5128003607746375587ULL, 6137245666376165821ULL, 7164044623269201573ULL, 7743444618495810837ULL, 7861846716777940561ULL, 8109918446058603789ULL, 8261719822741326120ULL, 8307183781656233746ULL, 8396668132838987312ULL, 8898167500217858691ULL, 8932430976418327682ULL, 9317340659163238167ULL, 9690764671846621113ULL, 11503196632009463229ULL, 11687593239772665556ULL, 12328060516207340684ULL, 13043307824879222355ULL, 13072632151264653763ULL, 14048733286625042236ULL, 14116182617975788072ULL, 14135027308327907840ULL, 14666062424071282314ULL, 15969011514599653954ULL, 16710713006078329603ULL, 16922975599666143549ULL, 18175072543214651513ULL, 18446744073709551615ULL })
            {
                ASSERT_EQ(AssignMask_U64(uint64_t(x), uint64_t(y), true), x | y);
                ASSERT_EQ(AssignMask_U64(uint64_t(x), uint64_t(y), false), x & ~y);
            }
        }
    }

    // set bit range
    {
        auto n = 8U;
        using T = uint8_t;
        auto f = SetBitRange_U8;
        auto ref = [n](uint32_t a, uint32_t b) {
            T ret(0);
            for (uint32_t i = 0; i < n; ++i)
                if (i >= a && i <= b)
                    ret |= T(1) << i;
            return ret;
        };
        for (uint32_t i = 0; i < n; ++i)
            for (uint32_t j = 0; j < n; ++j)
                ASSERT_EQ(f(i, j), ref(i, j));
    }

    {
        auto n = 16U;
        using T = uint16_t;
        auto f = SetBitRange_U16;
        auto ref = [n](uint32_t a, uint32_t b) {
            T ret(0);
            for (uint32_t i = 0; i < n; ++i)
                if (i >= a && i <= b)
                    ret |= T(1) << i;
            return ret;
        };
        for (uint32_t i = 0; i < n; ++i)
            for (uint32_t j = 0; j < n; ++j)
                ASSERT_EQ(f(i, j), ref(i, j));
    }

    {
        auto n = 32U;
        using T = uint32_t;
        auto f = SetBitRange_U32;
        auto ref = [n](uint32_t a, uint32_t b) {
            T ret(0);
            for (uint32_t i = 0; i < n; ++i)
                if (i >= a && i <= b)
                    ret |= T(1) << i;
            return ret;
        };
        for (uint32_t i = 0; i < n; ++i)
            for (uint32_t j = 0; j < n; ++j)
                ASSERT_EQ(f(i, j), ref(i, j));
    }

    {
        auto n = 64U;
        using T = uint64_t;
        auto f = SetBitRange_U64;
        auto ref = [n](uint32_t a, uint32_t b) {
            T ret(0);
            for (uint32_t i = 0; i < n; ++i)
                if (i >= a && i <= b)
                    ret |= T(1) << i;
            return ret;
        };
        for (uint32_t i = 0; i < n; ++i)
            for (uint32_t j = 0; j < n; ++j)
                ASSERT_EQ(f(i, j), ref(i, j));
    }

    // count set bits
    {
        auto n = 8U;
        using T = uint8_t;
        auto f = CountSetBits_U8;
        ASSERT_EQ(f(0), 0U);
        ASSERT_EQ(f(T(-1)), n);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), 1U);
        for (uint32_t i = 0; i < n; ++i)
            for (uint32_t j = 0; j < n; ++j)
                ASSERT_EQ(f(T((1U << i) | (1U << j))), 1U + (i != j));
        ASSERT_EQ(f(T(0b01101000)), 3U);
        ASSERT_EQ(f(T(0b11101111)), 7U);
    }

    {
        auto n = 16U;
        using T = uint16_t;
        auto f = CountSetBits_U16;
        ASSERT_EQ(f(0), 0U);
        ASSERT_EQ(f(T(-1)), n);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), 1U);
        for (uint32_t i = 0; i < n; ++i)
            for (uint32_t j = 0; j < n; ++j)
                ASSERT_EQ(f(T((1U << i) | (1U << j))), 1U + (i != j));
        ASSERT_EQ(f(T(0b01101000)), 3U);
        ASSERT_EQ(f(T(0b0010100000001000)), 3U);
        ASSERT_EQ(f(T(0b1010101101001001)), 8U);
        ASSERT_EQ(f(T(0b1111111101111101)), 14U);
        ASSERT_EQ(f(T(0b1111111111111101)), 15U);
    }

    {
        auto n = 32U;
        using T = uint32_t;
        auto f = CountSetBits_U32;
        ASSERT_EQ(f(0), 0U);
        ASSERT_EQ(f(T(-1)), n);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), 1U);
        for (uint32_t i = 0; i < n; ++i)
            for (uint32_t j = 0; j < n; ++j)
                ASSERT_EQ(f(T((1U << i) | (1U << j))), 1U + (i != j));
        ASSERT_EQ(f(T(0b01101000)), 3U);
        ASSERT_EQ(f(T(0b0010100000001000)), 3U);
        ASSERT_EQ(f(T(0b1010101101001001)), 8U);
        ASSERT_EQ(f(T(0b1111111101111101)), 14U);
        ASSERT_EQ(f(T(0b1111111111111101)), 15U);
        ASSERT_EQ(f(T(0b01101000000000000000000000000000)), 3U);
        ASSERT_EQ(f(T(0b01001000000000000000000000000001)), 3U);
        ASSERT_EQ(f(T(0b10101011010010010000000000000000)), 8U);
        ASSERT_EQ(f(T(0b10101011010010000000000000000100)), 8U);
        ASSERT_EQ(f(T(0b01000101101110000010011100110001)), 14U);
        ASSERT_EQ(f(T(0b01000101101110000010111100110001)), 15U);
        ASSERT_EQ(f(T(0b01011101101110000010011100110001)), 16U);
        ASSERT_EQ(f(T(0b01011101101111111010011111111101)), 24U);
        ASSERT_EQ(f(T(0b11111111111111111111100111111111)), 30U);
        ASSERT_EQ(f(T(0b11111111111111111111101111111111)), 31U);
    }


    {
        auto n = 64U;
        using T = uint64_t;
        auto f = CountSetBits_U64;
        ASSERT_EQ(f(0), 0U);
        ASSERT_EQ(f(T(-1)), n);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1ULL << i)), 1U);
        for (uint32_t i = 0; i < n; ++i)
            for (uint32_t j = 0; j < n; ++j)
                ASSERT_EQ(f(T((1ULL << i) | (1ULL << j))), 1U + (i != j));
        ASSERT_EQ(f(T(0b01101000)), 3U);
        ASSERT_EQ(f(T(0b0010100000001000)), 3U);
        ASSERT_EQ(f(T(0b1010101101001001)), 8U);
        ASSERT_EQ(f(T(0b1111111101111101)), 14U);
        ASSERT_EQ(f(T(0b1111111111111101)), 15U);
        ASSERT_EQ(f(T(0b01101000000000000000000000000000)), 3U);
        ASSERT_EQ(f(T(0b01001000000000000000000000000001)), 3U);
        ASSERT_EQ(f(T(0b10101011010010010000000000000000)), 8U);
        ASSERT_EQ(f(T(0b10101011010010000000000000000100)), 8U);
        ASSERT_EQ(f(T(0b01000101101110000010011100110001)), 14U);
        ASSERT_EQ(f(T(0b01000101101110000010111100110001)), 15U);
        ASSERT_EQ(f(T(0b01011101101110000010011100110001)), 16U);
        ASSERT_EQ(f(T(0b01011101101111111010011111111101)), 24U);
        ASSERT_EQ(f(T(0b11111111111111111111100111111111)), 30U);
        ASSERT_EQ(f(T(0b11111111111111111111101111111111)), 31U);
        ASSERT_EQ(f(T(0b11111111111111111111111111111111)), 32U);
        ASSERT_EQ(f(T(0b1111111111111111111111111111111101101000000000000000000000000000)), 35U);
        ASSERT_EQ(f(T(0b0111111111111111111111111111111101101000000011001000111101101001)), 45U);
        ASSERT_EQ(f(T(0b0111111111111111111111111111111101101111111111001011111111101001)), 55U);
        ASSERT_EQ(f(T(0b1111111111111111111111111111111111111111111111111111111111101111)), 63U);
    }

    // count leading zeros
    {
        auto n = 8U;
        using T = uint8_t;
        auto f = CountLeadingZeros_U8;
        ASSERT_EQ(f(0), n);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), (n - 1) - i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T((1U << i) | 1U)), (n - 1) - i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) >> i), i);
    }

    {
        auto n = 16U;
        using T = uint16_t;
        auto f = CountLeadingZeros_U16;
        ASSERT_EQ(f(0), n);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), (n - 1) - i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T((1U << i) | 1U)), (n - 1) - i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) >> i), i);
    }

    {
        auto n = 32U;
        using T = uint32_t;
        auto f = CountLeadingZeros_U32;
        ASSERT_EQ(f(0), n);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), (n - 1) - i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T((1U << i) | 1U)), (n - 1) - i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) >> i), i);
    }

    {
        auto n = 64U;
        using T = uint64_t;
        auto f = CountLeadingZeros_U64;
        ASSERT_EQ(f(0), n);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1ULL << i)), (n - 1) - i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T((1ULL << i) | 1ULL)), (n - 1) - i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) >> i), i);
    }

    // count trailing zeros
    {
        auto n = 8U;
        using T = uint8_t;
        auto f = CountTrailingZeros_U8;
        ASSERT_EQ(f(0), n);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T((1U << i) | (1U << (n - 1)))), i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) << i), i);
    }

    {
        auto n = 16U;
        using T = uint16_t;
        auto f = CountTrailingZeros_U16;
        ASSERT_EQ(f(0), n);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T((1U << i) | (1U << (n - 1)))), i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) << i), i);
    }

    {
        auto n = 32U;
        using T = uint32_t;
        auto f = CountTrailingZeros_U32;
        ASSERT_EQ(f(0), n);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T((1U << i) | (1U << (n - 1)))), i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) << i), i);
    }

    {
        auto n = 64U;
        using T = uint64_t;
        auto f = CountTrailingZeros_U64;
        ASSERT_EQ(f(0), n);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1ULL << i)), i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T((1ULL << i) | (1ULL << (n - 1)))), i);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) << i), i);
    }

    // simultaneously test [First|Last][Set|Clear]Bit[Mask|Index]
    {
        auto n = 8U;
        using T = uint8_t;
        BitTestHelper<T>(T(0), n);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T(1U << i), i);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T((1U << i) | (1U << (n - 1))), i);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T(-1) << i, i);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T(-1) >> i, 0U);
    }

    {
        auto n = 16U;
        using T = uint16_t;
        BitTestHelper<T>(T(0), n);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T(1U << i), i);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T((1U << i) | (1U << (n - 1))), i);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T(-1) << i, i);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T(-1) >> i, 0U);
    }

    {
        auto n = 32U;
        using T = uint32_t;
        BitTestHelper<T>(T(0), n);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T(1U << i), i);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T((1U << i) | (1U << (n - 1))), i);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T(-1) << i, i);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T(-1) >> i, 0U);
    }

    {
        auto n = 64U;
        using T = uint64_t;
        BitTestHelper<T>(T(0), n);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T(1ULL << i), i);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T((1ULL << i) | (1ULL << (n - 1))), i);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T(-1) << i, i);
        for (uint32_t i = 0; i < n; ++i)
            BitTestHelper<T>(T(-1) >> i, 0ULL);
    }

    // clear first set bit
    {
        auto n = 8U;
        using T = uint8_t;
        auto f = ClearFirstSetBit_U8;
        ASSERT_EQ(f(T(0)), T(0));
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), T(0));
        for (uint32_t i = 1; i < n; ++i)
            ASSERT_EQ(f(T(1U << i) | 1U), 1U << i);
        for (uint32_t i = 0; i < n - 1; ++i)
            ASSERT_EQ(f(T(1U << i) | (1U << (n - 1))), 1U << (n - 1));
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) << i), T((T(-1) << i) << 1));
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) >> i), T((T(-1) >> i) & ~1U));
    }

    {
        auto n = 16U;
        using T = uint16_t;
        auto f = ClearFirstSetBit_U16;
        ASSERT_EQ(f(T(0)), T(0));
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), T(0));
        for (uint32_t i = 1; i < n; ++i)
            ASSERT_EQ(f(T(1U << i) | 1U), 1U << i);
        for (uint32_t i = 0; i < n - 1; ++i)
            ASSERT_EQ(f(T(1U << i) | (1U << (n - 1))), 1U << (n - 1));
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) << i), T((T(-1) << i) << 1));
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) >> i), T((T(-1) >> i) & ~1U));
    }

    {
        auto n = 32U;
        using T = uint32_t;
        auto f = ClearFirstSetBit_U32;
        ASSERT_EQ(f(T(0)), T(0));
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), T(0));
        for (uint32_t i = 1; i < n; ++i)
            ASSERT_EQ(f(T(1U << i) | 1U), 1U << i);
        for (uint32_t i = 0; i < n - 1; ++i)
            ASSERT_EQ(f(T(1U << i) | (1U << (n - 1))), 1U << (n - 1));
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) << i), T((T(-1) << i) << 1));
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) >> i), T((T(-1) >> i) & ~1U));
    }

    {
        auto n = 64U;
        using T = uint64_t;
        auto f = ClearFirstSetBit_U64;
        ASSERT_EQ(f(T(0)), T(0));
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1ULL << i)), T(0));
        for (uint32_t i = 1; i < n; ++i)
            ASSERT_EQ(f(T(1ULL << i) | 1ULL), 1ULL << i);
        for (uint32_t i = 0; i < n - 1; ++i)
            ASSERT_EQ(f(T(1ULL << i) | (1ULL << (n - 1))), 1ULL << (n - 1));
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) << i), T((T(-1) << i) << 1));
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(-1) >> i), T((T(-1) >> i) & ~1ULL));
    }

    // reverse bytes
    {
        for (uint32_t i = 0; i < 256; ++i)
        {
            ASSERT_EQ(ReverseBytes_U8(uint8_t(i)), uint8_t(i));
        }
    }

    {
        for (const uint32_t a : {0, 12, 50, 100, 200, 222, 250, 255})
        {
            for (const uint32_t b : {0, 12, 50, 100, 200, 222, 250, 255})
            {
                const uint16_t ab = uint16_t((a << 8) | b);
                const uint16_t ba = uint16_t((b << 8) | a);
                ASSERT_EQ(ReverseBytes_U16(ab), ba);
                ASSERT_EQ(ReverseBytes_U16(ba), ab);
            }
        }
    }

    {
        for (const uint32_t a : {0, 12, 50, 100, 200, 222, 250, 255})
        {
            for (const uint32_t b : {0, 12, 50, 100, 200, 222, 250, 255})
            {
                for (const uint32_t c : {0, 12, 50, 100, 200, 222, 250, 255})
                {
                    for (const uint32_t d : {0, 12, 50, 100, 200, 222, 250, 255})
                    {
                        const uint32_t abcd = (a << 24) | (b << 16) | (c << 8) | d;
                        const uint32_t dcba = (d << 24) | (c << 16) | (b << 8) | a;
                        ASSERT_EQ(ReverseBytes_U32(abcd), dcba);
                        ASSERT_EQ(ReverseBytes_U32(dcba), abcd);
                    }
                }
            }
        }
    }

    {
        for (const uint64_t a : {0, 12, 200, 255})
        {
            for (const uint64_t b : {0, 12, 200, 255})
            {
                for (const uint64_t c : {0, 12, 200, 255})
                {
                    for (const uint64_t d : {0, 12, 200, 255})
                    {
                        for (const uint64_t e : {0, 12, 200, 255})
                        {
                            for (const uint64_t f : {0, 12, 200, 255})
                            {
                                for (const uint64_t g : {0, 12, 200, 255})
                                {
                                    for (const uint64_t h : {0, 12, 200, 255})
                                    {
                                        const uint64_t p = (a << 56) | (b << 48) | (c << 40) | (d << 32) | (e << 24) | (f << 16) | (g << 8) | h;
                                        const uint64_t q = (h << 56) | (g << 48) | (f << 40) | (e << 32) | (d << 24) | (c << 16) | (b << 8) | a;
                                        ASSERT_EQ(ReverseBytes_U64(p), q);
                                        ASSERT_EQ(ReverseBytes_U64(q), p);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // reverse bits in bytes M128
    {
        static constexpr uint8_t p[] = { 0, 12, 200, 255, 35, 77, 120, 128, 200, 0, 2, 42, 46, 93, 33, 255, 255, 101, 147, 44, 50, 0, 0, 0, 1, 12, 15, 16 };
        uint8_t q[sizeof(p)];
        for (uint64_t i = 0; i < sizeof(p); ++i)
            q[i] = RefReverseBits(p[i]);
        for (uint64_t i = 0; i <= sizeof(p) - 16; ++i)
        {
            {
                __m128i m = ReverseBitsInBytes_M128(_mm_loadu_si128(reinterpret_cast<const __m128i*>(p + i)));
                uint8_t r[sizeof(p)];
                _mm_storeu_si128(reinterpret_cast<__m128i*>(r), m);
                for (uint64_t j = 0; j < 16; ++j)
                {
                    ASSERT_EQ(r[j], q[i + j]);
                }
            }

            {
                __m128i m = ReverseBitsInBytes_M128(_mm_loadu_si128(reinterpret_cast<const __m128i*>(q + i)));
                uint8_t r[sizeof(p)];
                _mm_storeu_si128(reinterpret_cast<__m128i*>(r), m);
                for (uint64_t j = 0; j < 16; ++j)
                {
                    ASSERT_EQ(r[j], p[i + j]);
                }
            }
        }
    }

    // reverse bits
    {
        for (const auto x : { 0, 1, 3, 8, 10, 12, 15, 25, 35, 54, 63, 82, 85, 87, 88, 92, 93, 97, 99, 120, 128, 143, 144, 146, 150, 154, 168, 169, 194, 204, 221, 230, 255 })
        {
            ASSERT_EQ(ReverseBits_U8(uint8_t(x)), RefReverseBits(uint8_t(x)));
        }
    }

    {
        for (const auto x : { 0, 1, 561, 1555, 7812, 9391, 9603, 9695, 11217, 11983, 21212, 24139, 25322, 25574, 27852, 30248, 30390, 32189, 36048, 46991, 47061, 47375, 49561, 50056, 50858, 52614, 54566, 55227, 55778, 58241, 61845, 63116, 65535 })
        {
            ASSERT_EQ(ReverseBits_U16(uint16_t(x)), RefReverseBits(uint16_t(x)));
        }
    }

    {
        for (const auto x : { 0U, 1U, 121355964U, 583664479U, 689620521U, 708868965U, 1302359958U, 1838431887U, 1876920278U, 2080120591U, 2085596828U, 2103419320U, 2213316381U, 2777151632U, 2867950016U, 2954916315U, 3159206577U, 3218425283U, 3224835393U, 3304659855U, 3349972584U, 3527531268U, 3646559839U, 3650458017U, 3714306325U, 3721993123U, 3922188228U, 3984619083U, 4122549376U, 4135605450U, 4174381728U, 4232486730U, 4294967295U })
        {
            ASSERT_EQ(ReverseBits_U32(uint32_t(x)), RefReverseBits(uint32_t(x)));
        }
    }

    {
        for (const auto x : { 0ULL, 1ULL, 1786960817022974312ULL, 2425049002781624915ULL, 3435405280726075361ULL, 4976886614525036568ULL, 5128003607746375587ULL, 6137245666376165821ULL, 7164044623269201573ULL, 7743444618495810837ULL, 7861846716777940561ULL, 8109918446058603789ULL, 8261719822741326120ULL, 8307183781656233746ULL, 8396668132838987312ULL, 8898167500217858691ULL, 8932430976418327682ULL, 9317340659163238167ULL, 9690764671846621113ULL, 11503196632009463229ULL, 11687593239772665556ULL, 12328060516207340684ULL, 13043307824879222355ULL, 13072632151264653763ULL, 14048733286625042236ULL, 14116182617975788072ULL, 14135027308327907840ULL, 14666062424071282314ULL, 15969011514599653954ULL, 16710713006078329603ULL, 16922975599666143549ULL, 18175072543214651513ULL, 18446744073709551615ULL })
        {
            ASSERT_EQ(ReverseBits_U64(uint64_t(x)), RefReverseBits(uint64_t(x)));
        }
    }

    // is power of 2
    {
        auto n = 8U;
        using T = uint8_t;
        auto f1 = IsPowerOf2AndNotZero_U8;
        auto f2 = IsPowerOf2OrZero_U8;
        ASSERT_FALSE(f1(0));
        ASSERT_TRUE(f2(0));
        ASSERT_FALSE(f1(T(-1)));
        ASSERT_FALSE(f2(T(-1)));
        for (uint32_t i = 0; i < n; ++i)
        {
            ASSERT_TRUE(f1(T(1U << i)));
            ASSERT_TRUE(f2(T(1U << i)));
        }
        for (uint32_t i = 0; i < n; ++i)
        {
            for (uint32_t j = 0; j < n; ++j)
            {
                ASSERT_EQ(f1(T((1U << i) | (1U << j))), i == j);
                ASSERT_EQ(f2(T((1U << i) | (1U << j))), i == j);
            }
        }
        ASSERT_FALSE(f1(T(0b01101000)));
        ASSERT_FALSE(f2(T(0b01101000)));
        ASSERT_FALSE(f1(T(0b11101111)));
        ASSERT_FALSE(f2(T(0b11101111)));
    }

    {
        auto n = 16U;
        using T = uint16_t;
        auto f1 = IsPowerOf2AndNotZero_U16;
        auto f2 = IsPowerOf2OrZero_U16;
        ASSERT_FALSE(f1(0));
        ASSERT_TRUE(f2(0));
        ASSERT_FALSE(f1(T(-1)));
        ASSERT_FALSE(f2(T(-1)));
        for (uint32_t i = 0; i < n; ++i)
        {
            ASSERT_TRUE(f1(T(1U << i)));
            ASSERT_TRUE(f2(T(1U << i)));
        }
        for (uint32_t i = 0; i < n; ++i)
        {
            for (uint32_t j = 0; j < n; ++j)
            {
                ASSERT_EQ(f1(T((1U << i) | (1U << j))), i == j);
                ASSERT_EQ(f2(T((1U << i) | (1U << j))), i == j);
            }
        }
        ASSERT_FALSE(f1(T(0b01101000)));
        ASSERT_FALSE(f2(T(0b01101000)));
        ASSERT_FALSE(f1(T(0b0010000010000000)));
        ASSERT_FALSE(f2(T(0b0010000010000000)));
        ASSERT_FALSE(f1(T(0b1100000000000000)));
        ASSERT_FALSE(f2(T(0b1100000000000000)));
    }

    {
        auto n = 32U;
        using T = uint32_t;
        auto f1 = IsPowerOf2AndNotZero_U32;
        auto f2 = IsPowerOf2OrZero_U32;
        ASSERT_FALSE(f1(0));
        ASSERT_TRUE(f2(0));
        ASSERT_FALSE(f1(T(-1)));
        ASSERT_FALSE(f2(T(-1)));
        for (uint32_t i = 0; i < n; ++i)
        {
            ASSERT_TRUE(f1(T(1U << i)));
            ASSERT_TRUE(f2(T(1U << i)));
        }
        for (uint32_t i = 0; i < n; ++i)
        {
            for (uint32_t j = 0; j < n; ++j)
            {
                ASSERT_EQ(f1(T((1U << i) | (1U << j))), i == j);
                ASSERT_EQ(f2(T((1U << i) | (1U << j))), i == j);
            }
        }
        ASSERT_FALSE(f1(T(0b01101000)));
        ASSERT_FALSE(f2(T(0b01101000)));
        ASSERT_FALSE(f1(T(0b0010000010000000)));
        ASSERT_FALSE(f2(T(0b0010000010000000)));
        ASSERT_FALSE(f1(T(0b00100000000000000000000000000001)));
        ASSERT_FALSE(f2(T(0b00100000000000000000000000000001)));
        ASSERT_FALSE(f1(T(0b00110000000000000000000000000000)));
        ASSERT_FALSE(f2(T(0b00110000000000000000000000000000)));
    }

    {
        auto n = 64U;
        using T = uint64_t;
        auto f1 = IsPowerOf2AndNotZero_U64;
        auto f2 = IsPowerOf2OrZero_U64;
        ASSERT_FALSE(f1(0));
        ASSERT_TRUE(f2(0));
        ASSERT_FALSE(f1(T(-1)));
        ASSERT_FALSE(f2(T(-1)));
        for (uint32_t i = 0; i < n; ++i)
        {
            ASSERT_TRUE(f1(T(1ULL << i)));
            ASSERT_TRUE(f2(T(1ULL << i)));
        }
        for (uint32_t i = 0; i < n; ++i)
        {
            for (uint32_t j = 0; j < n; ++j)
            {
                ASSERT_EQ(f1(T((1ULL << i) | (1ULL << j))), i == j);
                ASSERT_EQ(f2(T((1ULL << i) | (1ULL << j))), i == j);
            }
        }
        ASSERT_FALSE(f1(T(0b01101000)));
        ASSERT_FALSE(f2(T(0b01101000)));
        ASSERT_FALSE(f1(T(0b0010000010000000)));
        ASSERT_FALSE(f2(T(0b0010000010000000)));
        ASSERT_FALSE(f1(T(0b00100000000000000000000000000001)));
        ASSERT_FALSE(f2(T(0b00100000000000000000000000000001)));
        ASSERT_FALSE(f1(T(0b00110000000000000000000000000000)));
        ASSERT_FALSE(f2(T(0b00110000000000000000000000000000)));
        ASSERT_FALSE(f1(T(0b0010000000000000000000000000000100000000000000000000000000000001)));
        ASSERT_FALSE(f2(T(0b0010000000000000000000000000000100000000000000000000000000000001)));
        ASSERT_FALSE(f1(T(0b0001000000000000000000000000000000000000000000000000000100000000)));
        ASSERT_FALSE(f2(T(0b0001000000000000000000000000000000000000000000000000000100000000)));
    }

    // round up to power of 2
    {
        auto n = 8U;
        using T = uint8_t;
        auto f = RoundUpToPowerOf2_U8;

        ASSERT_EQ(f(0U), 0U);
        ASSERT_EQ(f((1U << (n - 1)) | 1U), 0U);
        ASSERT_EQ(f((1U << (n - 1)) | 2U), 0U);
        ASSERT_EQ(f((1U << (n - 1)) | 3U), 0U);
        ASSERT_EQ(f((1U << (n - 1)) | 4U), 0U);
        ASSERT_EQ(f(0b11U << (n - 2)), 0U);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), T(1U << i));
        for (uint32_t i = 1; i < n - 1; ++i)
            ASSERT_EQ(f(T(1U << i) | 1U), T(1U << (i + 1)));
        for (uint32_t i = 1; i < n - 1; ++i)
            ASSERT_EQ(f(T(1U << i) | 1U), T(1U << (i + 1)));
        for (uint32_t i = 1; i < n - 1; ++i)
            ASSERT_EQ(f(T(-1) >> i), T(1U << (n - i)));
    }

    {
        auto n = 16U;
        using T = uint16_t;
        auto f = RoundUpToPowerOf2_U16;

        ASSERT_EQ(f(0U), 0U);
        ASSERT_EQ(f((1U << (n - 1)) | 1U), 0U);
        ASSERT_EQ(f((1U << (n - 1)) | 2U), 0U);
        ASSERT_EQ(f((1U << (n - 1)) | 3U), 0U);
        ASSERT_EQ(f((1U << (n - 1)) | 4U), 0U);
        ASSERT_EQ(f(0b11U << (n - 2)), 0U);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), T(1U << i));
        for (uint32_t i = 1; i < n - 1; ++i)
            ASSERT_EQ(f(T(1U << i) | 1U), T(1U << (i + 1)));
        for (uint32_t i = 1; i < n - 1; ++i)
            ASSERT_EQ(f(T(1U << i) | 1U), T(1U << (i + 1)));
        for (uint32_t i = 1; i < n - 1; ++i)
            ASSERT_EQ(f(T(-1) >> i), T(1U << (n - i)));
    }

    {
        auto n = 32U;
        using T = uint32_t;
        auto f = RoundUpToPowerOf2_U32;

        ASSERT_EQ(f(0U), 0U);
        ASSERT_EQ(f((1U << (n - 1)) | 1U), 0U);
        ASSERT_EQ(f((1U << (n - 1)) | 2U), 0U);
        ASSERT_EQ(f((1U << (n - 1)) | 3U), 0U);
        ASSERT_EQ(f((1U << (n - 1)) | 4U), 0U);
        ASSERT_EQ(f(0b11U << (n - 2)), 0U);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1U << i)), T(1U << i));
        for (uint32_t i = 1; i < n - 1; ++i)
            ASSERT_EQ(f(T(1U << i) | 1U), T(1U << (i + 1)));
        for (uint32_t i = 1; i < n - 1; ++i)
            ASSERT_EQ(f(T(1U << i) | 1U), T(1U << (i + 1)));
        for (uint32_t i = 1; i < n - 1; ++i)
            ASSERT_EQ(f(T(-1) >> i), T(1U << (n - i)));
    }

    {
        auto n = 64U;
        using T = uint64_t;
        auto f = RoundUpToPowerOf2_U64;

        ASSERT_EQ(f(0ULL), 0U);
        ASSERT_EQ(f((1ULL << (n - 1)) | 1U), 0U);
        ASSERT_EQ(f((1ULL << (n - 1)) | 2U), 0U);
        ASSERT_EQ(f((1ULL << (n - 1)) | 3U), 0U);
        ASSERT_EQ(f((1ULL << (n - 1)) | 4U), 0U);
        ASSERT_EQ(f(0b11ULL << (n - 2)), 0U);
        for (uint32_t i = 0; i < n; ++i)
            ASSERT_EQ(f(T(1ULL << i)), T(1ULL << i));
        for (uint32_t i = 1; i < n - 1; ++i)
            ASSERT_EQ(f(T(1ULL << i) | 1U), T(1ULL << (i + 1)));
        for (uint32_t i = 1; i < n - 1; ++i)
            ASSERT_EQ(f(T(1ULL << i) | 1U), T(1ULL << (i + 1)));
        for (uint32_t i = 1; i < n - 1; ++i)
            ASSERT_EQ(f(T(-1) >> i), T(1ULL << (n - i)));
    }

    // simultaneously test [First|Last]N[Set|Clear]Bits
    NBitsTestHelper<uint8_t>();
    NBitsTestHelper<uint16_t>();
    NBitsTestHelper<uint32_t>();
    NBitsTestHelper<uint64_t>();
}

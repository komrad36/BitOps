/*******************************************************************
*
*    Author: Kareem Omar
*    kareem.h.omar@gmail.com
*    https://github.com/komrad36
*
*    Last updated Sept 20, 2021
*******************************************************************/

#pragma once

#include <cstdint>
#include <immintrin.h>

#if defined(_MSC_VER) && !defined(__clang__) && !defined(__GNUC__)
#pragma warning (push)
#pragma warning (disable:4146)
#endif

// If cond, set bit i in x.
// Otherwise, clear bit i in x.
[[nodiscard]] static inline uint8_t AssignBit_U8(uint8_t x, uint32_t i, bool cond)
{
	const uint32_t mFalse = x & ~(1U << i);
	const uint32_t mTrue = x | (1U << i);
	return uint8_t(cond ? mTrue : mFalse);
}

// If cond, set bit i in x.
// Otherwise, clear bit i in x.
[[nodiscard]] static inline uint16_t AssignBit_U16(uint16_t x, uint32_t i, bool cond)
{
	const uint32_t mFalse = x & ~(1U << i);
	const uint32_t mTrue = x | (1U << i);
	return uint16_t(cond ? mTrue : mFalse);
}

// If cond, set bit i in x.
// Otherwise, clear bit i in x.
[[nodiscard]] static inline uint32_t AssignBit_U32(uint32_t x, uint32_t i, bool cond)
{
	const uint32_t mFalse = x & ~(1U << i);
	const uint32_t mTrue = x | (1U << i);
	return cond ? mTrue : mFalse;
}

// If cond, set bit i in x.
// Otherwise, clear bit i in x.
[[nodiscard]] static inline uint64_t AssignBit_U64(uint64_t x, uint64_t i, bool cond)
{
	const uint64_t mFalse = x & ~(1ULL << i);
	const uint64_t mTrue = x | (1ULL << i);
	return cond ? mTrue : mFalse;
}

// If cond, set all the bits in x that correspond to set bits in mask.
// Otherwise, clear all the bits in x that correspond to set bits in mask.
[[nodiscard]] static inline uint8_t AssignMask_U8(uint8_t x, uint8_t mask, bool cond)
{
	const uint8_t mTrue = x | mask;
	const uint8_t mFalse = x & ~mask;
	return cond ? mTrue : mFalse;
}

// If cond, set all the bits in x that correspond to set bits in mask.
// Otherwise, clear all the bits in x that correspond to set bits in mask.
[[nodiscard]] static inline uint16_t AssignMask_U16(uint16_t x, uint16_t mask, bool cond)
{
	const uint16_t mTrue = x | mask;
	const uint16_t mFalse = x & ~mask;
	return cond ? mTrue : mFalse;
}

// If cond, set all the bits in x that correspond to set bits in mask.
// Otherwise, clear all the bits in x that correspond to set bits in mask.
[[nodiscard]] static inline uint32_t AssignMask_U32(uint32_t x, uint32_t mask, bool cond)
{
	const uint32_t mTrue = x | mask;
	const uint32_t mFalse = x & ~mask;
	return cond ? mTrue : mFalse;
}

// If cond, set all the bits in x that correspond to set bits in mask.
// Otherwise, clear all the bits in x that correspond to set bits in mask.
[[nodiscard]] static inline uint64_t AssignMask_U64(uint64_t x, uint64_t mask, bool cond)
{
	const uint64_t mTrue = x | mask;
	const uint64_t mFalse = x & ~mask;
	return cond ? mTrue : mFalse;
}

// Return a mask with bits set between indices a and b, inclusive.
[[nodiscard]] static inline uint8_t SetBitRange_U8(uint32_t a, uint32_t b)
{
	return uint8_t((~0U << (a & 31U)) & (~0U >> (~b & 31U)));
}

// Return a mask with bits set between indices a and b, inclusive.
[[nodiscard]] static inline uint16_t SetBitRange_U16(uint32_t a, uint32_t b)
{
	return uint16_t((~0U << (a & 31U)) & (~0U >> (~b & 31U)));
}

// Return a mask with bits set between indices a and b, inclusive.
[[nodiscard]] static inline uint32_t SetBitRange_U32(uint32_t a, uint32_t b)
{
	return uint32_t((~0U << (a & 31U)) & (~0U >> (~b & 31U)));
}

// Return a mask with bits set between indices a and b, inclusive.
[[nodiscard]] static inline uint64_t SetBitRange_U64(uint64_t a, uint64_t b)
{
	return uint64_t((~0ULL << (a & 63ULL)) & (~0ULL >> (~b & 63ULL)));
}

// Return the number of bits set in x.
[[nodiscard]] static inline uint32_t CountSetBits_U8(uint8_t x)
{
	return uint32_t(_mm_popcnt_u32(x));
}

// Return the number of bits set in x.
[[nodiscard]] static inline uint32_t CountSetBits_U16(uint16_t x)
{
	return uint32_t(_mm_popcnt_u32(x));
}

// Return the number of bits set in x.
[[nodiscard]] static inline uint32_t CountSetBits_U32(uint32_t x)
{
	return uint32_t(_mm_popcnt_u32(x));
}

// Return the number of bits set in x.
[[nodiscard]] static inline uint64_t CountSetBits_U64(uint64_t x)
{
	return uint64_t(_mm_popcnt_u64(x));
}

// Return the number of leading (most significant) zero bits.
// Returns 8 when x is 0.
[[nodiscard]] static inline uint32_t CountLeadingZeros_U8(uint8_t x)
{
	return _lzcnt_u32(x) - 24U;
}

// Return the number of leading (most significant) zero bits.
// Returns 16 when x is 0.
[[nodiscard]] static inline uint32_t CountLeadingZeros_U16(uint16_t x)
{
	return _lzcnt_u32(x) - 16U;
}

// Return the number of leading (most significant) zero bits.
// Returns 32 when x is 0.
[[nodiscard]] static inline uint32_t CountLeadingZeros_U32(uint32_t x)
{
	return _lzcnt_u32(x);
}

// Return the number of leading (most significant) zero bits.
// Returns 64 when x is 0.
[[nodiscard]] static inline uint64_t CountLeadingZeros_U64(uint64_t x)
{
	return _lzcnt_u64(x);
}

// Return the number of trailing (least significant) zero bits.
// Returns 8 when x is 0.
[[nodiscard]] static inline uint32_t CountTrailingZeros_U8(uint8_t x)
{
	return _tzcnt_u32(uint32_t(x) | (1U << 8));
}

// Return the number of trailing (least significant) zero bits.
// Returns 16 when x is 0.
[[nodiscard]] static inline uint32_t CountTrailingZeros_U16(uint16_t x)
{
	return _tzcnt_u32(uint32_t(x) | (1U << 16));
}

// Return the number of trailing (least significant) zero bits.
// Returns 32 when x is 0.
[[nodiscard]] static inline uint32_t CountTrailingZeros_U32(uint32_t x)
{
	return _tzcnt_u32(x);
}

// Return the number of trailing (least significant) zero bits.
// Returns 64 when x is 0.
[[nodiscard]] static inline uint64_t CountTrailingZeros_U64(uint64_t x)
{
	return _tzcnt_u64(x);
}

// Return a mask consisting of the first (least significant) set bit.
// Returns 0 when x is 0.
[[nodiscard]] static inline uint8_t FirstSetBitMask_U8(uint8_t x)
{
	return uint8_t(x & -x);
}

// Return a mask consisting of the first (least significant) set bit.
// Returns 0 when x is 0.
[[nodiscard]] static inline uint16_t FirstSetBitMask_U16(uint16_t x)
{
	return uint16_t(x & -x);
}

// Return a mask consisting of the first (least significant) set bit.
// Returns 0 when x is 0.
[[nodiscard]] static inline uint32_t FirstSetBitMask_U32(uint32_t x)
{
	return x & -x;
}

// Return a mask consisting of the first (least significant) set bit.
// Returns 0 when x is 0.
[[nodiscard]] static inline uint64_t FirstSetBitMask_U64(uint64_t x)
{
	return x & -x;
}

// Return the index of the first (least significant) set bit.
// Returns 8 when x is 0.
[[nodiscard]] static inline uint32_t FirstSetBitIndex_U8(uint8_t x)
{
	return CountTrailingZeros_U8(x);
}

// Return the index of the first (least significant) set bit.
// Returns 16 when x is 0.
[[nodiscard]] static inline uint32_t FirstSetBitIndex_U16(uint16_t x)
{
	return CountTrailingZeros_U16(x);
}

// Return the index of the first (least significant) set bit.
// Returns 32 when x is 0.
[[nodiscard]] static inline uint32_t FirstSetBitIndex_U32(uint32_t x)
{
	return CountTrailingZeros_U32(x);
}

// Return the index of the first (least significant) set bit.
// Returns 64 when x is 0.
[[nodiscard]] static inline uint64_t FirstSetBitIndex_U64(uint64_t x)
{
	return CountTrailingZeros_U64(x);
}

// Return a mask consisting of the first (least significant) clear bit.
// Returns 0 when x is all ones.
[[nodiscard]] static inline uint8_t FirstClearBitMask_U8(uint8_t x)
{
	return FirstSetBitMask_U8(~x);
}

// Return a mask consisting of the first (least significant) clear bit.
// Returns 0 when x is all ones.
[[nodiscard]] static inline uint16_t FirstClearBitMask_U16(uint16_t x)
{
	return FirstSetBitMask_U16(~x);
}

// Return a mask consisting of the first (least significant) clear bit.
// Returns 0 when x is all ones.
[[nodiscard]] static inline uint32_t FirstClearBitMask_U32(uint32_t x)
{
	return FirstSetBitMask_U32(~x);
}

// Return a mask consisting of the first (least significant) clear bit.
// Returns 0 when x is all ones.
[[nodiscard]] static inline uint64_t FirstClearBitMask_U64(uint64_t x)
{
	return FirstSetBitMask_U64(~x);
}

// Return the index of the first (least significant) clear bit.
// Returns 8 when x is all ones.
[[nodiscard]] static inline uint32_t FirstClearBitIndex_U8(uint8_t x)
{
	return CountTrailingZeros_U32(~uint32_t(x));
}

// Return the index of the first (least significant) clear bit.
// Returns 16 when x is all ones.
[[nodiscard]] static inline uint32_t FirstClearBitIndex_U16(uint16_t x)
{
	return CountTrailingZeros_U32(~uint32_t(x));
}

// Return the index of the first (least significant) clear bit.
// Returns 32 when x is all ones.
[[nodiscard]] static inline uint32_t FirstClearBitIndex_U32(uint32_t x)
{
	return CountTrailingZeros_U32(~x);
}

// Return the index of the first (least significant) clear bit.
// Returns 64 when x is all ones.
[[nodiscard]] static inline uint64_t FirstClearBitIndex_U64(uint64_t x)
{
	return CountTrailingZeros_U64(~x);
}

// Return a mask consisting of the last (most significant) set bit.
// Returns 0 when x is 0.
[[nodiscard]] static inline uint8_t LastSetBitMask_U8(uint8_t x)
{
	return uint8_t((1U << 15) >> CountLeadingZeros_U16(x));
}

// Return a mask consisting of the last (most significant) set bit.
// Returns 0 when x is 0.
[[nodiscard]] static inline uint16_t LastSetBitMask_U16(uint16_t x)
{
	return uint16_t((1U << 31) >> (CountLeadingZeros_U32(x) & 31U));
}

// Return a mask consisting of the last (most significant) set bit.
// Returns 0 when x is 0.
[[nodiscard]] static inline uint32_t LastSetBitMask_U32(uint32_t x)
{
	return uint32_t((1ULL << 31) >> CountLeadingZeros_U32(x));
}

// Return a mask consisting of the last (most significant) set bit.
// Returns 0 when x is 0.
[[nodiscard]] static inline uint64_t LastSetBitMask_U64(uint64_t x)
{
	return x & ((1ULL << 63) >> (CountLeadingZeros_U64(x) & 63ULL));
}

// Return the index of the last (most significant) set bit.
// Returns an implementation-defined value that is >= 8 when x is 0.
[[nodiscard]] static inline uint32_t LastSetBitIndex_U8(uint8_t x)
{
	return CountLeadingZeros_U32(x) ^ 31U;
}

// Return the index of the last (most significant) set bit.
// Returns an implementation-defined value that is >= 16 when x is 0.
[[nodiscard]] static inline uint32_t LastSetBitIndex_U16(uint16_t x)
{
	return CountLeadingZeros_U32(x) ^ 31U;
}

// Return the index of the last (most significant) set bit.
// Returns an implementation-defined value that is >= 32 when x is 0.
[[nodiscard]] static inline uint32_t LastSetBitIndex_U32(uint32_t x)
{
	return CountLeadingZeros_U32(x) ^ 31U;
}

// Return the index of the last (most significant) set bit.
// Returns an implementation-defined value that is >= 64 when x is 0.
[[nodiscard]] static inline uint64_t LastSetBitIndex_U64(uint64_t x)
{
	return CountLeadingZeros_U64(x) ^ 63ULL;
}

// Return a mask consisting of the last (most significant) clear bit.
// Returns 0 when x is all ones.
[[nodiscard]] static inline uint8_t LastClearBitMask_U8(uint8_t x)
{
	return LastSetBitMask_U8(~x);
}

// Return a mask consisting of the last (most significant) clear bit.
// Returns 0 when x is all ones.
[[nodiscard]] static inline uint16_t LastClearBitMask_U16(uint16_t x)
{
	return LastSetBitMask_U16(~x);
}

// Return a mask consisting of the last (most significant) clear bit.
// Returns 0 when x is all ones.
[[nodiscard]] static inline uint32_t LastClearBitMask_U32(uint32_t x)
{
	return LastSetBitMask_U32(~x);
}

// Return a mask consisting of the last (most significant) clear bit.
// Returns 0 when x is all ones.
[[nodiscard]] static inline uint64_t LastClearBitMask_U64(uint64_t x)
{
	return LastSetBitMask_U64(~x);
}

// Return the index of the last (most significant) clear bit.
// Returns an implementation-defined value that is >= 8 when x is all ones.
[[nodiscard]] static inline uint32_t LastClearBitIndex_U8(uint8_t x)
{
	return LastSetBitIndex_U8(~x);
}

// Return the index of the last (most significant) clear bit.
// Returns an implementation-defined value that is >= 16 when x is all ones.
[[nodiscard]] static inline uint32_t LastClearBitIndex_U16(uint16_t x)
{
	return LastSetBitIndex_U16(~x);
}

// Return the index of the last (most significant) clear bit.
// Returns an implementation-defined value that is >= 32 when x is all ones.
[[nodiscard]] static inline uint32_t LastClearBitIndex_U32(uint32_t x)
{
	return LastSetBitIndex_U32(~x);
}

// Return the index of the last (most significant) clear bit.
// Returns an implementation-defined value that is >= 64 when x is all ones.
[[nodiscard]] static inline uint64_t LastClearBitIndex_U64(uint64_t x)
{
	return LastSetBitIndex_U64(~x);
}

// Clear the first (least significant) set bit.
[[nodiscard]] static inline uint8_t ClearFirstSetBit_U8(uint8_t x)
{
	return uint8_t(x & (x - 1U));
}

// Clear the first (least significant) set bit.
[[nodiscard]] static inline uint16_t ClearFirstSetBit_U16(uint16_t x)
{
	return uint16_t(x & (x - 1U));
}

// Clear the first (least significant) set bit.
[[nodiscard]] static inline uint32_t ClearFirstSetBit_U32(uint32_t x)
{
	return x & (x - 1U);
}

// Clear the first (least significant) set bit.
[[nodiscard]] static inline uint64_t ClearFirstSetBit_U64(uint64_t x)
{
	return x & (x - 1ULL);
}

// Reverse byte order, while leaving bits within bytes unmodified.
[[nodiscard]] static inline uint8_t ReverseBytes_U8(uint8_t x)
{
	return x;
}

// Reverse byte order, while leaving bits within bytes unmodified.
[[nodiscard]] static inline uint16_t ReverseBytes_U16(uint16_t x)
{
#if defined(_MSC_VER) && !defined(__clang__) && !defined(__GNUC__)
	return _byteswap_ushort(x);
#else
	return __builtin_bswap16(x);
#endif
}

// Reverse byte order, while leaving bits within bytes unmodified.
[[nodiscard]] static inline uint32_t ReverseBytes_U32(uint32_t x)
{
#if defined(_MSC_VER) && !defined(__clang__) && !defined(__GNUC__)
	return _byteswap_ulong(x);
#else
	return __builtin_bswap32(x);
#endif
}

// Reverse byte order, while leaving bits within bytes unmodified.
[[nodiscard]] static inline uint64_t ReverseBytes_U64(uint64_t x)
{
#if defined(_MSC_VER) && !defined(__clang__) && !defined(__GNUC__)
	return _byteswap_uint64(x);
#else
	return __builtin_bswap64(x);
#endif
}

// Reverse bit order within each byte, while leaving byte order unmofidied.
[[nodiscard]] static inline __m128i ReverseBitsInBytes_M128(__m128i v)
{
	const __m128i hMask = _mm_set_epi64x(0x0F070B030D050901LL, 0x0E060A020C040800LL);
	const __m128i lMask = _mm_set_epi64x(0xF070B030D0509010LL, 0xE060A020C0408000LL);
	const __m128i L = _mm_and_si128(v, _mm_set1_epi8(0xF));
	const __m128i H = _mm_and_si128(_mm_srli_epi32(v, 4), _mm_set1_epi8(0xF));
	return _mm_or_si128(_mm_shuffle_epi8(lMask, L), _mm_shuffle_epi8(hMask, H));
}

// Reverse bit order.
[[nodiscard]] static inline uint8_t ReverseBits_U8(uint8_t x)
{
	//                                            abcd efgh
	// *  0000 0000 1000 0000 0010 0000 0000 1000 0000 0010
	// ----------------------------------------------------
	//    0abc defg h00a bcde fgh0 0abc defg h00a bcde fgh0
	// &  0000 1000 1000 0100 0100 0010 0010 0001 0001 0000
	// ----------------------------------------------------
	//    0000 d000 h000 0c00 0g00 00b0 00f0 000a 000e 0000
	// *  0000 0001 0000 0001 0000 0001 0000 0001 0000 0001
	// ----------------------------------------------------
	//    hgfe dcba hgfe 0cba 0gfe 00ba 00fe 000a 000e 0000
	// >> 32
	// ----------------------------------------------------
	//                                            hgfe dcba

	return uint8_t((((x * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL) >> 32U);
}

// Reverse bit order.
[[nodiscard]] static inline uint16_t ReverseBits_U16(uint16_t x)
{
	return ReverseBytes_U16(uint16_t(_mm_cvtsi128_si32(ReverseBitsInBytes_M128(_mm_cvtsi32_si128(x)))));
}

// Reverse bit order.
[[nodiscard]] static inline uint32_t ReverseBits_U32(uint32_t x)
{
	return ReverseBytes_U32(uint32_t(_mm_cvtsi128_si32(ReverseBitsInBytes_M128(_mm_cvtsi32_si128(int32_t(x))))));
}

// Reverse bit order.
[[nodiscard]] static inline uint64_t ReverseBits_U64(uint64_t x)
{
	return ReverseBytes_U64(uint64_t(_mm_cvtsi128_si64(ReverseBitsInBytes_M128(_mm_cvtsi64_si128(int64_t(x))))));
}

// Return true if x is a power of 2. To avoid ambiguity: this excludes 0.
[[nodiscard]] static inline bool IsPowerOf2AndNotZero_U8(uint8_t x)
{
	return CountSetBits_U32(x) == 1;
}

// Return true if x is a power of 2. To avoid ambiguity: this excludes 0.
[[nodiscard]] static inline bool IsPowerOf2AndNotZero_U16(uint16_t x)
{
	return CountSetBits_U32(x) == 1;
}

// Return true if x is a power of 2. To avoid ambiguity: this excludes 0.
[[nodiscard]] static inline bool IsPowerOf2AndNotZero_U32(uint32_t x)
{
	return CountSetBits_U32(x) == 1;
}

// Return true if x is a power of 2. To avoid ambiguity: this excludes 0.
[[nodiscard]] static inline bool IsPowerOf2AndNotZero_U64(uint64_t x)
{
	return CountSetBits_U64(x) == 1;
}

// Return true if x is a power of 2. To avoid ambiguity: this includes 0.
[[nodiscard]] static inline bool IsPowerOf2OrZero_U8(uint8_t x)
{
	return !(x & (x - 1U));
}

// Return true if x is a power of 2. To avoid ambiguity: this includes 0.
[[nodiscard]] static inline bool IsPowerOf2OrZero_U16(uint16_t x)
{
	return !(x & (x - 1U));
}

// Return true if x is a power of 2. To avoid ambiguity: this includes 0.
[[nodiscard]] static inline bool IsPowerOf2OrZero_U32(uint32_t x)
{
	return !(x & (x - 1U));
}

// Return true if x is a power of 2. To avoid ambiguity: this includes 0.
[[nodiscard]] static inline bool IsPowerOf2OrZero_U64(uint64_t x)
{
	return !(x & (x - 1ULL));
}

// Round up to next highest power of 2.
// Returns powers of 2 unchanged.
// Returns 0 when x is 0 or if rounding up to power of 2 would overflow.
[[nodiscard]] static inline uint8_t RoundUpToPowerOf2_U8(uint8_t x)
{
	return uint8_t(0x10000U >> CountLeadingZeros_U16(x - 1));
}

// Round up to next highest power of 2.
// Returns powers of 2 unchanged.
// Returns 0 when x is 0 or if rounding up to power of 2 would overflow.
[[nodiscard]] static inline uint16_t RoundUpToPowerOf2_U16(uint16_t x)
{
	return uint16_t(0x100000000ULL >> CountLeadingZeros_U32(x - 1));
}

// Round up to next highest power of 2.
// Returns powers of 2 unchanged.
// Returns 0 when x is 0 or if rounding up to power of 2 would overflow.
[[nodiscard]] static inline uint32_t RoundUpToPowerOf2_U32(uint32_t x)
{
	return uint32_t(0x100000000ULL >> CountLeadingZeros_U32(x - 1));
}

// Round up to next highest power of 2.
// Returns powers of 2 unchanged.
// Returns 0 when x is 0 or if rounding up to power of 2 would overflow.
[[nodiscard]] static inline uint64_t RoundUpToPowerOf2_U64(uint64_t x)
{
	const uint64_t z = -CountLeadingZeros_U64(x - 1);
	return (z ? 1ULL : 0ULL) << (z & 63ULL);
}

// Round down to next lowest power of 2.
// Returns powers of 2 unchanged.
// Returns 0 when x is 0.
[[nodiscard]] static inline uint8_t RoundDownToPowerOf2_U8(uint8_t x)
{
	return LastSetBitMask_U8(x);
}

// Round down to next lowest power of 2.
// Returns powers of 2 unchanged.
// Returns 0 when x is 0.
[[nodiscard]] static inline uint16_t RoundDownToPowerOf2_U16(uint16_t x)
{
	return LastSetBitMask_U16(x);
}

// Round down to next lowest power of 2.
// Returns powers of 2 unchanged.
// Returns 0 when x is 0.
[[nodiscard]] static inline uint32_t RoundDownToPowerOf2_U32(uint32_t x)
{
	return LastSetBitMask_U32(x);
}

// Round down to next lowest power of 2.
// Returns powers of 2 unchanged.
// Returns 0 when x is 0.
[[nodiscard]] static inline uint64_t RoundDownToPowerOf2_U64(uint64_t x)
{
	return LastSetBitMask_U64(x);
}

// Log (base 2).
// Returns an implementation-defined value that is >= 8 when x is 0.
[[nodiscard]] static inline uint32_t LogBase2_U8(uint8_t x)
{
	return LastSetBitIndex_U8(x);
}

// Log (base 2).
// Returns an implementation-defined value that is >= 16 when x is 0.
[[nodiscard]] static inline uint32_t LogBase2_U16(uint16_t x)
{
	return LastSetBitIndex_U16(x);
}

// Log (base 2).
// Returns an implementation-defined value that is >= 32 when x is 0.
[[nodiscard]] static inline uint32_t LogBase2_U32(uint32_t x)
{
	return LastSetBitIndex_U32(x);
}

// Log (base 2).
// Returns an implementation-defined value that is >= 64 when x is 0.
[[nodiscard]] static inline uint64_t LogBase2_U64(uint64_t x)
{
	return LastSetBitIndex_U64(x);
}

// Return the index of the first (least significant) run of n set bits.
// Returns 8 when x is 0.
[[nodiscard]] static inline uint32_t FirstNSetBitsIndex_U8(uint8_t x, uint32_t n)
{
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	return FirstSetBitIndex_U8(x);
}

// Return the index of the first (least significant) run of n set bits.
// Returns 16 when x is 0.
[[nodiscard]] static inline uint32_t FirstNSetBitsIndex_U16(uint16_t x, uint32_t n)
{
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	return FirstSetBitIndex_U16(x);
}

// Return the index of the first (least significant) run of n set bits.
// Returns 32 when x is 0.
[[nodiscard]] static inline uint32_t FirstNSetBitsIndex_U32(uint32_t x, uint32_t n)
{
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	return FirstSetBitIndex_U32(x);
}

// Return the index of the first (least significant) run of n set bits.
// Returns 64 when x is 0.
[[nodiscard]] static inline uint64_t FirstNSetBitsIndex_U64(uint64_t x, uint32_t n)
{
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	return FirstSetBitIndex_U64(x);
}

// Return the index of the first (least significant) run of n set bits,
// but runs can only start on bits set in validBits.
// Returns 8 when x is 0.
[[nodiscard]] static inline uint32_t FirstNSetBitsIndex_U8(uint8_t x, uint32_t n, uint8_t validBits)
{
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	return FirstSetBitIndex_U8(x & validBits);
}

// Return the index of the first (least significant) run of n set bits,
// but runs can only start on bits set in validBits.
// Returns 16 when x is 0.
[[nodiscard]] static inline uint32_t FirstNSetBitsIndex_U16(uint16_t x, uint32_t n, uint16_t validBits)
{
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	return FirstSetBitIndex_U16(x & validBits);
}

// Return the index of the first (least significant) run of n set bits,
// but runs can only start on bits set in validBits.
// Returns 32 when x is 0.
[[nodiscard]] static inline uint32_t FirstNSetBitsIndex_U32(uint32_t x, uint32_t n, uint32_t validBits)
{
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	return FirstSetBitIndex_U32(x & validBits);
}

// Return the index of the first (least significant) run of n set bits,
// but runs can only start on bits set in validBits.
// Returns 64 when x is 0.
[[nodiscard]] static inline uint64_t FirstNSetBitsIndex_U64(uint64_t x, uint32_t n, uint64_t validBits)
{
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	n -= (n >> 1);
	x &= x >> (n >> 1);
	return FirstSetBitIndex_U64(x & validBits);
}

// Return the index of the last (most significant) run of n set bits.
// Returns 8 when x is 0.
[[nodiscard]] static inline uint32_t LastNSetBitsIndex_U8(uint8_t x, uint32_t n)
{
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	return LastSetBitIndex_U8(x);
}

// Return the index of the last (most significant) run of n set bits.
// Returns 16 when x is 0.
[[nodiscard]] static inline uint32_t LastNSetBitsIndex_U16(uint16_t x, uint32_t n)
{
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	return LastSetBitIndex_U16(x);
}

// Return the index of the last (most significant) run of n set bits.
// Returns 32 when x is 0.
[[nodiscard]] static inline uint32_t LastNSetBitsIndex_U32(uint32_t x, uint32_t n)
{
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	return LastSetBitIndex_U32(x);
}

// Return the index of the last (most significant) run of n set bits.
// Returns 64 when x is 0.
[[nodiscard]] static inline uint64_t LastNSetBitsIndex_U64(uint64_t x, uint32_t n)
{
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	return LastSetBitIndex_U64(x);
}

// Return the index of the last (most significant) run of n set bits,
// but runs can only start on bits set in validBits.
// Returns 8 when x is 0.
[[nodiscard]] static inline uint32_t LastNSetBitsIndex_U8(uint8_t x, uint32_t n, uint8_t validBits)
{
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	return LastSetBitIndex_U8(x & validBits);
}

// Return the index of the last (most significant) run of n set bits,
// but runs can only start on bits set in validBits.
// Returns 16 when x is 0.
[[nodiscard]] static inline uint32_t LastNSetBitsIndex_U16(uint16_t x, uint32_t n, uint16_t validBits)
{
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	return LastSetBitIndex_U16(x & validBits);
}

// Return the index of the last (most significant) run of n set bits,
// but runs can only start on bits set in validBits.
// Returns 32 when x is 0.
[[nodiscard]] static inline uint32_t LastNSetBitsIndex_U32(uint32_t x, uint32_t n, uint32_t validBits)
{
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	return LastSetBitIndex_U32(x & validBits);
}

// Return the index of the last (most significant) run of n set bits,
// but runs can only start on bits set in validBits.
// Returns 64 when x is 0.
[[nodiscard]] static inline uint64_t LastNSetBitsIndex_U64(uint64_t x, uint32_t n, uint64_t validBits)
{
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	n -= (n >> 1);
	x &= x << (n >> 1);
	return LastSetBitIndex_U64(x & validBits);
}

// Return the index of the first (least significant) run of n clear bits.
// Returns 8 when x is 0.
[[nodiscard]] static inline uint32_t FirstNClearBitsIndex_U8(uint8_t x, uint32_t n)
{
	return FirstNSetBitsIndex_U8(~x, n);
}

// Return the index of the first (least significant) run of n clear bits.
// Returns 16 when x is 0.
[[nodiscard]] static inline uint32_t FirstNClearBitsIndex_U16(uint16_t x, uint32_t n)
{
	return FirstNSetBitsIndex_U16(~x, n);
}

// Return the index of the first (least significant) run of n clear bits.
// Returns 32 when x is 0.
[[nodiscard]] static inline uint32_t FirstNClearBitsIndex_U32(uint32_t x, uint32_t n)
{
	return FirstNSetBitsIndex_U32(~x, n);
}

// Return the index of the first (least significant) run of n clear bits.
// Returns 64 when x is 0.
[[nodiscard]] static inline uint64_t FirstNClearBitsIndex_U64(uint64_t x, uint32_t n)
{
	return FirstNSetBitsIndex_U64(~x, n);
}

// Return the index of the first (least significant) run of n clear bits,
// but runs can only start on bits set in validBits.
// Returns 8 when x is 0.
[[nodiscard]] static inline uint32_t FirstNClearBitsIndex_U8(uint8_t x, uint32_t n, uint8_t validBits)
{
	return FirstNSetBitsIndex_U8(~x, n, validBits);
}

// Return the index of the first (least significant) run of n clear bits,
// but runs can only start on bits set in validBits.
// Returns 16 when x is 0.
[[nodiscard]] static inline uint32_t FirstNClearBitsIndex_U16(uint16_t x, uint32_t n, uint16_t validBits)
{
	return FirstNSetBitsIndex_U16(~x, n, validBits);
}

// Return the index of the first (least significant) run of n clear bits,
// but runs can only start on bits set in validBits.
// Returns 32 when x is 0.
[[nodiscard]] static inline uint32_t FirstNClearBitsIndex_U32(uint32_t x, uint32_t n, uint32_t validBits)
{
	return FirstNSetBitsIndex_U32(~x, n, validBits);
}

// Return the index of the first (least significant) run of n clear bits,
// but runs can only start on bits set in validBits.
// Returns 64 when x is 0.
[[nodiscard]] static inline uint64_t FirstNClearBitsIndex_U64(uint64_t x, uint32_t n, uint64_t validBits)
{
	return FirstNSetBitsIndex_U64(~x, n, validBits);
}

// Return the index of the last (most significant) run of n clear bits.
// Returns 8 when x is 0.
[[nodiscard]] static inline uint32_t LastNClearBitsIndex_U8(uint8_t x, uint32_t n)
{
	return LastNSetBitsIndex_U8(~x, n);
}

// Return the index of the last (most significant) run of n clear bits.
// Returns 16 when x is 0.
[[nodiscard]] static inline uint32_t LastNClearBitsIndex_U16(uint16_t x, uint32_t n)
{
	return LastNSetBitsIndex_U16(~x, n);
}

// Return the index of the last (most significant) run of n clear bits.
// Returns 32 when x is 0.
[[nodiscard]] static inline uint32_t LastNClearBitsIndex_U32(uint32_t x, uint32_t n)
{
	return LastNSetBitsIndex_U32(~x, n);
}

// Return the index of the last (most significant) run of n clear bits.
// Returns 64 when x is 0.
[[nodiscard]] static inline uint64_t LastNClearBitsIndex_U64(uint64_t x, uint32_t n)
{
	return LastNSetBitsIndex_U64(~x, n);
}

// Return the index of the last (most significant) run of n set bits,
// but runs can only start on bits set in validBits.
// Returns 8 when x is 0.
[[nodiscard]] static inline uint32_t LastNClearBitsIndex_U8(uint8_t x, uint32_t n, uint8_t validBits)
{
	return LastNSetBitsIndex_U8(~x, n, validBits);
}

// Return the index of the last (most significant) run of n set bits,
// but runs can only start on bits set in validBits.
// Returns 16 when x is 0.
[[nodiscard]] static inline uint32_t LastNClearBitsIndex_U16(uint16_t x, uint32_t n, uint16_t validBits)
{
	return LastNSetBitsIndex_U16(~x, n, validBits);
}

// Return the index of the last (most significant) run of n set bits,
// but runs can only start on bits set in validBits.
// Returns 32 when x is 0.
[[nodiscard]] static inline uint32_t LastNClearBitsIndex_U32(uint32_t x, uint32_t n, uint32_t validBits)
{
	return LastNSetBitsIndex_U32(~x, n, validBits);
}

// Return the index of the last (most significant) run of n set bits,
// but runs can only start on bits set in validBits.
// Returns 64 when x is 0.
[[nodiscard]] static inline uint64_t LastNClearBitsIndex_U64(uint64_t x, uint32_t n, uint64_t validBits)
{
	return LastNSetBitsIndex_U64(~x, n, validBits);
}

#if defined(_MSC_VER) && !defined(__clang__) && !defined(__GNUC__)
#pragma warning (pop)
#endif

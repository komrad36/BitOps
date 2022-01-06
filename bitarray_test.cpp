/*******************************************************************
*
*    Author: Kareem Omar
*    kareem.h.omar@gmail.com
*    https://github.com/komrad36
*
*    Last updated Sept 20, 2021
*******************************************************************/

#include <iostream>

#include "bitarray.h"

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

template <size_t n>
static void SetExcessBits(BitArray<n>& v)
{
    if constexpr ((n & 63ULL) != 0ULL)
    {
        uint64_t* p = reinterpret_cast<uint64_t*>(&v);
        p[BitArray<n>::kNumBlocks - 1] |= ~BitArray<n>::LastBlockMask();
    }
}

template <size_t n>
static void ClearExcessBits(BitArray<n>& v)
{
    if constexpr ((n & 63ULL) != 0ULL)
    {
        uint64_t* p = reinterpret_cast<uint64_t*>(&v);
        p[BitArray<n>::kNumBlocks - 1] &= BitArray<n>::LastBlockMask();
    }
}

template <size_t n>
static void AssignExcessBits(BitArray<n>& v, bool setExcessBits)
{
    if (setExcessBits)
        SetExcessBits<n>(v);
    else
        ClearExcessBits<n>(v);
}

template <size_t n>
static void CheckAllBlocksEqual(BitArray<n>& v, uint64_t x)
{
    uint64_t* p = reinterpret_cast<uint64_t*>(&v);
    for (uint64_t i = 0; i < BitArray<n>::kNumBlocks; ++i)
        ASSERT_EQ(p[i], x);
}

template <class U, class V>
static void SweepArraySizes(U populateFunc, V testFunc)
{
#define SWEEP_ARRAY_SIZE(i)                                                \
    { BitArray<i> v; populateFunc(v); SetExcessBits(v); testFunc(v); }     \
    { BitArray<i> v; populateFunc(v); ClearExcessBits(v); testFunc(v); }
    SWEEP_ARRAY_SIZE(1);
    SWEEP_ARRAY_SIZE(2);
    SWEEP_ARRAY_SIZE(3);
    SWEEP_ARRAY_SIZE(4);
    SWEEP_ARRAY_SIZE(32);
    SWEEP_ARRAY_SIZE(63);
    SWEEP_ARRAY_SIZE(64);
    SWEEP_ARRAY_SIZE(65);
    SWEEP_ARRAY_SIZE(127);
    SWEEP_ARRAY_SIZE(128);
    SWEEP_ARRAY_SIZE(129);
    SWEEP_ARRAY_SIZE(191);
    SWEEP_ARRAY_SIZE(192);
    SWEEP_ARRAY_SIZE(193);
    SWEEP_ARRAY_SIZE(255);
    SWEEP_ARRAY_SIZE(256);
    SWEEP_ARRAY_SIZE(257);
}

template <class U, class V>
static void SweepSmallArrays(U populateFunc, V testFunc)
{
    { SmallBitArray<uint8_t > v; populateFunc(v); testFunc(v); }
    { SmallBitArray<uint16_t> v; populateFunc(v); testFunc(v); }
    { SmallBitArray<uint32_t> v; populateFunc(v); testFunc(v); }
    { SmallBitArray<uint64_t> v; populateFunc(v); testFunc(v); }
}

template <class U, class V, class W>
static void SweepArraySizesPair(U populateFuncA, V populateFuncB, W testFunc)
{
#undef SWEEP_ARRAY_SIZE
#define SWEEP_ARRAY_SIZE(i) { BitArray<i> a, b; populateFuncA(a); populateFuncB(b); testFunc(a, b); }
    SWEEP_ARRAY_SIZE(1);
    SWEEP_ARRAY_SIZE(2);
    SWEEP_ARRAY_SIZE(3);
    SWEEP_ARRAY_SIZE(4);
    SWEEP_ARRAY_SIZE(32);
    SWEEP_ARRAY_SIZE(63);
    SWEEP_ARRAY_SIZE(64);
    SWEEP_ARRAY_SIZE(65);
    SWEEP_ARRAY_SIZE(127);
    SWEEP_ARRAY_SIZE(128);
    SWEEP_ARRAY_SIZE(129);
    SWEEP_ARRAY_SIZE(191);
    SWEEP_ARRAY_SIZE(192);
    SWEEP_ARRAY_SIZE(193);
    SWEEP_ARRAY_SIZE(255);
    SWEEP_ARRAY_SIZE(256);
    SWEEP_ARRAY_SIZE(257);
}

template <class U, class V, class W, class X>
static void SweepArraySizesTriplet(U populateFuncA, V populateFuncB, W populateFuncC, X testFunc)
{
#undef SWEEP_ARRAY_SIZE
#define SWEEP_ARRAY_SIZE(i) { BitArray<i> a, b, c; populateFuncA(a); populateFuncB(b); populateFuncC(c); testFunc(a, b, c); }
    SWEEP_ARRAY_SIZE(1);
    SWEEP_ARRAY_SIZE(2);
    SWEEP_ARRAY_SIZE(3);
    SWEEP_ARRAY_SIZE(4);
    SWEEP_ARRAY_SIZE(32);
    SWEEP_ARRAY_SIZE(63);
    SWEEP_ARRAY_SIZE(64);
    SWEEP_ARRAY_SIZE(65);
    SWEEP_ARRAY_SIZE(127);
    SWEEP_ARRAY_SIZE(128);
    SWEEP_ARRAY_SIZE(129);
    SWEEP_ARRAY_SIZE(191);
    SWEEP_ARRAY_SIZE(192);
    SWEEP_ARRAY_SIZE(193);
    SWEEP_ARRAY_SIZE(255);
    SWEEP_ARRAY_SIZE(256);
    SWEEP_ARRAY_SIZE(257);
}

template <class U>
static void SweepArraySizes(U func)
{
#undef SWEEP_ARRAY_SIZE
#define SWEEP_ARRAY_SIZE(i) { BitArray<i> v; func(v); }
    SWEEP_ARRAY_SIZE(1);
    SWEEP_ARRAY_SIZE(2);
    SWEEP_ARRAY_SIZE(3);
    SWEEP_ARRAY_SIZE(4);
    SWEEP_ARRAY_SIZE(32);
    SWEEP_ARRAY_SIZE(63);
    SWEEP_ARRAY_SIZE(64);
    SWEEP_ARRAY_SIZE(65);
    SWEEP_ARRAY_SIZE(127);
    SWEEP_ARRAY_SIZE(128);
    SWEEP_ARRAY_SIZE(129);
    SWEEP_ARRAY_SIZE(191);
    SWEEP_ARRAY_SIZE(192);
    SWEEP_ARRAY_SIZE(193);
    SWEEP_ARRAY_SIZE(255);
    SWEEP_ARRAY_SIZE(256);
    SWEEP_ARRAY_SIZE(257);
}

template <size_t n>
static void AssignBlocks(BitArray<n>& v, uint64_t x)
{
    v.Rep(x);
}

template <size_t n>
static void AssignAll(BitArray<n>& v, bool x)
{
    v.AssignAll(x);
}

template <size_t n>
static void SetAll(BitArray<n>& v)
{
    v.SetAll();
}

template <size_t n>
static void ClearAll(BitArray<n>& v)
{
    v.ClearAll();
}

template <class T>
static void TestDefaultConstruct()
{
    SmallBitArray<T> v;
    ASSERT_EQ(T(v), T(0));
}

template <class T>
static void TestValueConstruct()
{
    SmallBitArray<T> v(T(0x357cab98bce42045ULL));
    ASSERT_EQ(T(v), T(0x357cab98bce42045ULL));
}

template <class T>
static void TestOr()
{
    SmallBitArray<T> a(T(0x357cab98bce42045ULL));
    SmallBitArray<T> b(T(0x6e751b283bbe6557ULL));
    SmallBitArray<T> r1 = a | b;
    SmallBitArray<T> r2 = a;
    r2 |= b;
    ASSERT_TRUE(r1 == r2);
    ASSERT_EQ(T(r1), T(0x357cab98bce42045ULL | 0x6e751b283bbe6557ULL));
}

template <class T>
static void TestXor()
{
    SmallBitArray<T> a(T(0x357cab98bce42045ULL));
    SmallBitArray<T> b(T(0x6e751b283bbe6557ULL));
    SmallBitArray<T> r1 = a ^ b;
    SmallBitArray<T> r2 = a;
    r2 ^= b;
    ASSERT_TRUE(r1 == r2);
    ASSERT_EQ(T(r1), T(0x357cab98bce42045ULL ^ 0x6e751b283bbe6557ULL));
}

template <class T>
static void TestAnd()
{
    SmallBitArray<T> a(T(0x357cab98bce42045ULL));
    SmallBitArray<T> b(T(0x6e751b283bbe6557ULL));
    SmallBitArray<T> r1 = a & b;
    SmallBitArray<T> r2 = a;
    r2 &= b;
    ASSERT_TRUE(r1 == r2);
    ASSERT_EQ(T(r1), T(0x357cab98bce42045ULL & 0x6e751b283bbe6557ULL));
}

template <class T>
static void TestNot()
{
    SmallBitArray<T> v(T(0x357cab98bce42045ULL));
    SmallBitArray<T> r = ~v;
    ASSERT_EQ(T(r), T(~0x357cab98bce42045ULL));
}

template <class T>
static void TestEq()
{
    SmallBitArray<T> a(T(0x357cab98bce42045ULL));
    SmallBitArray<T> b(T(0x357cab98bce42045ULL));
    ASSERT_TRUE(a == b);
    ASSERT_FALSE(a != b);
    b = SmallBitArray<T>(T(0x6e751b283bbe6557ULL));
    ASSERT_FALSE(a == b);
    ASSERT_TRUE(a != b);
}

template <class T>
static void TestIterator()
{
    for (uint64_t ref : {0x357cab98bce42045ULL, 0x6e751b283bbe6557ULL, 0x23909d5a478b7aefULL, 0ULL, ~0ULL})
    {
        SmallBitArray<T> v{ T(ref) };
        uint64_t iRef = T(FirstSetBitIndex_U64(ref));
        for (const uint64_t i : v)
        {
            ASSERT_EQ(i, iRef);
            ref &= T(~(1ULL << iRef));
            iRef = T(FirstSetBitIndex_U64(ref));
        }
        ASSERT_EQ(ref, T(0));
        ASSERT_EQ(iRef, 64);
    }
}

#define TestSmall(f)  \
{                     \
    f<uint8_t>();     \
    f<uint16_t>();    \
    f<uint32_t>();    \
    f<uint64_t>();    \
}

void TestBitArray()
{
    // Rep, AreAllBitsSet, AreAllBitsClear
    SweepArraySizes([](auto& v) { v.Rep(0ULL); },
        [](auto& v) { ASSERT_TRUE(v.AreAllBitsClear()); ASSERT_FALSE(v.AreAllBitsSet()); }
    );
    SweepArraySizes([](auto& v) { v.Rep(~0ULL); },
        [](auto& v) { ASSERT_TRUE(v.AreAllBitsSet()); ASSERT_FALSE(v.AreAllBitsClear()); }
    );
    SweepArraySizes([](auto& v) { v.Rep(0x123456789ABCDEF0ULL); }, [](auto& v)
        {
            const uint64_t* p = reinterpret_cast<const uint64_t*>(&v);
            for (uint64_t i = 0; i < v.kNumBlocks - 1; ++i)
                ASSERT_EQ(p[i], 0x123456789ABCDEF0ULL);
            ASSERT_EQ(p[v.kNumBlocks - 1] & v.LastBlockMask(), 0x123456789ABCDEF0ULL & v.LastBlockMask());
        });

    // AssignAll, SetAll, ClearAll
    SweepArraySizes([](auto& v) { v.AssignAll(false); },
        [](auto& v) { ASSERT_TRUE(v.AreAllBitsClear()); ASSERT_FALSE(v.AreAllBitsSet()); }
    );
    SweepArraySizes([](auto& v) { v.AssignAll(true); },
        [](auto& v) { ASSERT_FALSE(v.AreAllBitsClear()); ASSERT_TRUE(v.AreAllBitsSet()); }
    );
    SweepArraySizes([](auto& v) { v.SetAll(); },
        [](auto& v) { ASSERT_FALSE(v.AreAllBitsClear()); ASSERT_TRUE(v.AreAllBitsSet()); }
    );
    SweepArraySizes([](auto& v) { v.ClearAll(); },
        [](auto& v) { ASSERT_TRUE(v.AreAllBitsClear()); ASSERT_FALSE(v.AreAllBitsSet()); }
    );

    // SetBit, ClearBit, XorBit, AssignBit, IsBitSet
    SweepArraySizes([](auto& v)
        {
            for (const bool setExcessBits : {true, false})
            {
                v.ClearAll();
                AssignExcessBits(v, setExcessBits);
                for (uint64_t i = 0; i < v.kNumBits; ++i)
                {
                    for (uint64_t j = 0; j < v.kNumBits; ++j)
                    {
                        ASSERT_EQ(v.CountSetBits(), 0);
                        v.SetBit(i);
                        ASSERT_EQ(v.CountSetBits(), 1);
                        v.SetBit(j);
                        ASSERT_EQ(v.CountSetBits(), ((i == j) ? 1 : 2));
                        for (uint64_t k = 0; k < v.kNumBits; ++k)
                            ASSERT_EQ(v.IsBitSet(k), k == i || k == j);
                        v.ClearBit(i);
                        ASSERT_EQ(v.CountSetBits(), ((i == j) ? 0 : 1));
                        v.ClearBit(j);
                        ASSERT_EQ(v.CountSetBits(), 0);
                    }
                }

                v.ClearAll();
                AssignExcessBits(v, setExcessBits);
                for (uint64_t i = 0; i < v.kNumBits; ++i)
                {
                    for (uint64_t j = 0; j < v.kNumBits; ++j)
                    {
                        ASSERT_EQ(v.CountSetBits(), 0);
                        v.AssignBit(i, true);
                        ASSERT_EQ(v.CountSetBits(), 1);
                        v.AssignBit(j, true);
                        ASSERT_EQ(v.CountSetBits(), ((i == j) ? 1 : 2));
                        for (uint64_t k = 0; k < v.kNumBits; ++k)
                            ASSERT_EQ(v.IsBitSet(k), k == i || k == j);
                        v.ClearBit(i);
                        ASSERT_EQ(v.CountSetBits(), ((i == j) ? 0 : 1));
                        v.ClearBit(j);
                        ASSERT_EQ(v.CountSetBits(), 0);
                    }
                }

                v.ClearAll();
                AssignExcessBits(v, setExcessBits);
                for (uint64_t i = 0; i < v.kNumBits; ++i)
                {
                    for (uint64_t j = 0; j < v.kNumBits; ++j)
                    {
                        ASSERT_EQ(v.CountSetBits(), 0);
                        v.XorBit(i);
                        ASSERT_EQ(v.CountSetBits(), 1);
                        v.XorBit(j);
                        ASSERT_EQ(v.CountSetBits(), ((i == j) ? 0 : 2));
                        for (uint64_t k = 0; k < v.kNumBits; ++k)
                            ASSERT_EQ(v.IsBitSet(k), i != j && (k == i || k == j));
                        v.XorBit(i);
                        ASSERT_EQ(v.CountSetBits(), 1);
                        v.XorBit(j);
                        ASSERT_EQ(v.CountSetBits(), 0);
                    }
                }

                v.SetAll();
                AssignExcessBits(v, setExcessBits);
                for (uint64_t i = 0; i < v.kNumBits; ++i)
                {
                    for (uint64_t j = 0; j < v.kNumBits; ++j)
                    {
                        ASSERT_EQ(v.CountSetBits(), v.kNumBits);
                        v.ClearBit(i);
                        ASSERT_EQ(v.CountSetBits(), v.kNumBits - 1);
                        v.ClearBit(j);
                        ASSERT_EQ(v.CountSetBits(), ((i == j) ? v.kNumBits - 1 : v.kNumBits - 2));
                        for (uint64_t k = 0; k < v.kNumBits; ++k)
                            ASSERT_EQ(!v.IsBitSet(k), k == i || k == j);
                        v.SetBit(i);
                        ASSERT_EQ(v.CountSetBits(), ((i == j) ? v.kNumBits : v.kNumBits - 1));
                        v.SetBit(j);
                        ASSERT_EQ(v.CountSetBits(), v.kNumBits);
                    }
                }

                v.SetAll();
                AssignExcessBits(v, setExcessBits);
                for (uint64_t i = 0; i < v.kNumBits; ++i)
                {
                    for (uint64_t j = 0; j < v.kNumBits; ++j)
                    {
                        ASSERT_EQ(v.CountSetBits(), v.kNumBits);
                        v.AssignBit(i, false);
                        ASSERT_EQ(v.CountSetBits(), v.kNumBits - 1);
                        v.AssignBit(j, false);
                        ASSERT_EQ(v.CountSetBits(), ((i == j) ? v.kNumBits - 1 : v.kNumBits - 2));
                        for (uint64_t k = 0; k < v.kNumBits; ++k)
                            ASSERT_EQ(!v.IsBitSet(k), k == i || k == j);
                        v.SetBit(i);
                        ASSERT_EQ(v.CountSetBits(), ((i == j) ? v.kNumBits : v.kNumBits - 1));
                        v.SetBit(j);
                        ASSERT_EQ(v.CountSetBits(), v.kNumBits);
                    }
                }

                v.SetAll();
                AssignExcessBits(v, setExcessBits);
                for (uint64_t i = 0; i < v.kNumBits; ++i)
                {
                    for (uint64_t j = 0; j < v.kNumBits; ++j)
                    {
                        ASSERT_EQ(v.CountSetBits(), v.kNumBits);
                        v.XorBit(i);
                        ASSERT_EQ(v.CountSetBits(), v.kNumBits - 1);
                        v.XorBit(j);
                        ASSERT_EQ(v.CountSetBits(), ((i == j) ? v.kNumBits : v.kNumBits - 2));
                        for (uint64_t k = 0; k < v.kNumBits; ++k)
                            ASSERT_EQ(!v.IsBitSet(k), i != j && (k == i || k == j));
                        v.XorBit(i);
                        ASSERT_EQ(v.CountSetBits(), v.kNumBits - 1);
                        v.XorBit(j);
                        ASSERT_EQ(v.CountSetBits(), v.kNumBits);
                    }
                }
            }
        });

    // CountSetBits
    SweepArraySizes([](auto& v)
        {
            for (const bool setExcessBits : {true, false})
            {
                for (uint64_t i = 1; i < 4; ++i)
                {
                    for (uint64_t j = 0; j < 128; ++j)
                    {
                        v.ClearAll();
                        AssignExcessBits(v, setExcessBits);
                        uint64_t expectedNumBits = 0;
                        for (uint64_t k = j; k < v.kNumBits; k += i)
                        {
                            v.SetBit(k);
                            ++expectedNumBits;
                            ASSERT_EQ(v.CountSetBits(), expectedNumBits);
                        }
                    }
                }
            }
        });

    // CountSetBitsInRange
    SweepArraySizes([](auto& v)
        {
            for (const bool setExcessBits : {true, false})
            {
                v.ClearAll();
                AssignExcessBits(v, setExcessBits);
                for (uint64_t i = 0; i < v.kNumBits; ++i)
                {
                    for (uint64_t j = i; j < v.kNumBits; ++j)
                    {
                        ASSERT_EQ(v.CountSetBitsInRange(i, j), 0);
                    }
                }

                v.SetAll();
                AssignExcessBits(v, setExcessBits);
                for (uint64_t i = 0; i < v.kNumBits; ++i)
                {
                    for (uint64_t j = i; j < v.kNumBits; ++j)
                    {
                        ASSERT_EQ(v.CountSetBitsInRange(i, j), j - i + 1);
                    }
                }
            }
        });

    // SetBitsInRange, ClearBitsInRange, AreAllBitsInRangeSet, AreAllBitsInRangeClear
    SweepArraySizes([](auto& v)
        {
            for (const bool setExcessBits : {true, false})
            {
                for (uint64_t i = 0; i < v.kNumBits; ++i)
                {
                    for (uint64_t j = i; j < v.kNumBits; ++j)
                    {
                        v.ClearAll();
                        AssignExcessBits(v, setExcessBits);
                        v.SetBitsInRange(i, j);
                        ASSERT_EQ(v.CountSetBits(), j - i + 1);
                        if (i != 0)
                            ASSERT_TRUE(v.AreAllBitsInRangeClear(0, i - 1));
                        ASSERT_TRUE(v.AreAllBitsInRangeSet(i, j));
                        if (j != v.kNumBits - 1)
                            ASSERT_TRUE(v.AreAllBitsInRangeClear(j + 1, v.kNumBits - 1));
                    }
                }

                for (uint64_t i = 0; i < v.kNumBits; ++i)
                {
                    for (uint64_t j = i; j < v.kNumBits; ++j)
                    {
                        v.SetAll();
                        AssignExcessBits(v, setExcessBits);
                        v.ClearBitsInRange(i, j);
                        ASSERT_EQ(v.CountSetBits(), v.kNumBits - (j - i + 1));
                        if (i != 0)
                            ASSERT_TRUE(v.AreAllBitsInRangeSet(0, i - 1));
                        ASSERT_TRUE(v.AreAllBitsInRangeClear(i, j));
                        if (j != v.kNumBits - 1)
                            ASSERT_TRUE(v.AreAllBitsInRangeSet(j + 1, v.kNumBits - 1));
                    }
                }
            }
        });

    // FirstSetBitIndex, FirstClearBitIndex, CountTrailingZeros
    SweepArraySizes([](auto& v)
        {
            for (const bool setExcessBits : {true, false})
            {
                v.ClearAll();
                AssignExcessBits(v, setExcessBits);
                ASSERT_EQ(v.FirstSetBitIndex(), ~0ULL);
                ASSERT_EQ(v.CountTrailingZeros(), v.kNumBits);
                ASSERT_EQ(v.FirstClearBitIndex(), 0);
                v.SetBit(0);
                ASSERT_EQ(v.FirstSetBitIndex(), 0);
                ASSERT_EQ(v.CountTrailingZeros(), 0);
                ASSERT_EQ(v.FirstClearBitIndex(), v.kNumBits == 1 ? ~0ULL : 1ULL);
                for (uint64_t i = 1; i < v.kNumBits; ++i)
                {
                    v.ClearBit(i - 1);
                    v.SetBit(i);
                    ASSERT_EQ(v.FirstSetBitIndex(), i);
                    ASSERT_EQ(v.CountTrailingZeros(), i);
                    ASSERT_EQ(v.FirstClearBitIndex(), 0);
                }
                v.ClearBit(v.kNumBits - 1);
                ASSERT_EQ(v.FirstSetBitIndex(), ~0ULL);
                ASSERT_EQ(v.CountTrailingZeros(), v.kNumBits);
                ASSERT_EQ(v.FirstClearBitIndex(), 0);

                v.SetAll();
                AssignExcessBits(v, setExcessBits);
                ASSERT_EQ(v.FirstSetBitIndex(), 0);
                ASSERT_EQ(v.CountTrailingZeros(), 0);
                ASSERT_EQ(v.FirstClearBitIndex(), ~0ULL);
                for (uint64_t i = 0; i < v.kNumBits - 1; ++i)
                {
                    v.ClearBit(i);
                    ASSERT_EQ(v.FirstSetBitIndex(), i + 1);
                    ASSERT_EQ(v.CountTrailingZeros(), i + 1);
                    ASSERT_EQ(v.FirstClearBitIndex(), 0);
                }
                v.ClearBit(v.kNumBits - 1);
                ASSERT_EQ(v.FirstSetBitIndex(), ~0ULL);
                ASSERT_EQ(v.CountTrailingZeros(), v.kNumBits);
                ASSERT_EQ(v.FirstClearBitIndex(), 0);
            }

            for (const bool setExcessBits : {true, false})
            {
                v.SetAll();
                AssignExcessBits(v, setExcessBits);
                ASSERT_EQ(v.FirstClearBitIndex(), ~0ULL);
                ASSERT_EQ(v.FirstSetBitIndex(), 0);
                v.ClearBit(0);
                ASSERT_EQ(v.FirstClearBitIndex(), 0);
                ASSERT_EQ(v.FirstSetBitIndex(), v.kNumBits == 1 ? ~0ULL : 1ULL);
                for (uint64_t i = 1; i < v.kNumBits; ++i)
                {
                    v.SetBit(i - 1);
                    v.ClearBit(i);
                    ASSERT_EQ(v.FirstClearBitIndex(), i);
                    ASSERT_EQ(v.FirstSetBitIndex(), 0);
                }
                v.SetBit(v.kNumBits - 1);
                ASSERT_EQ(v.FirstClearBitIndex(), ~0ULL);
                ASSERT_EQ(v.FirstSetBitIndex(), 0);

                v.ClearAll();
                AssignExcessBits(v, setExcessBits);
                ASSERT_EQ(v.FirstClearBitIndex(), 0);
                ASSERT_EQ(v.FirstSetBitIndex(), ~0ULL);
                for (uint64_t i = 0; i < v.kNumBits - 1; ++i)
                {
                    v.SetBit(i);
                    ASSERT_EQ(v.FirstClearBitIndex(), i + 1);
                    ASSERT_EQ(v.FirstSetBitIndex(), 0);
                }
                v.SetBit(v.kNumBits - 1);
                ASSERT_EQ(v.FirstClearBitIndex(), ~0ULL);
                ASSERT_EQ(v.FirstSetBitIndex(), 0);
            }
        });

    // LastSetBitIndex, LastClearBitIndex, CountLeadingZeros
    SweepArraySizes([](auto& v)
        {
            for (const bool setExcessBits : {true, false})
            {
                v.ClearAll();
                AssignExcessBits(v, setExcessBits);
                ASSERT_EQ(v.LastSetBitIndex(), ~0ULL);
                ASSERT_EQ(v.CountLeadingZeros(), v.kNumBits);
                ASSERT_EQ(v.LastClearBitIndex(), v.kNumBits - 1);
                v.SetBit(v.kNumBits - 1);
                ASSERT_EQ(v.LastSetBitIndex(), v.kNumBits - 1);
                ASSERT_EQ(v.CountLeadingZeros(), 0);
                ASSERT_EQ(v.LastClearBitIndex(), v.kNumBits == 1 ? ~0ULL : v.kNumBits - 2);
                for (uint64_t i = v.kNumBits - 2; int64_t(i) >= 0; --i)
                {
                    v.ClearBit(i + 1);
                    v.SetBit(i);
                    ASSERT_EQ(v.LastSetBitIndex(), i);
                    ASSERT_EQ(v.CountLeadingZeros(), (v.kNumBits - 1) - i);
                    ASSERT_EQ(v.LastClearBitIndex(), v.kNumBits - 1);
                }
                v.ClearBit(0);
                ASSERT_EQ(v.LastSetBitIndex(), ~0ULL);
                ASSERT_EQ(v.CountLeadingZeros(), v.kNumBits);
                ASSERT_EQ(v.LastClearBitIndex(), v.kNumBits - 1);

                v.SetAll();
                AssignExcessBits(v, setExcessBits);
                ASSERT_EQ(v.LastSetBitIndex(), v.kNumBits - 1);
                ASSERT_EQ(v.CountLeadingZeros(), 0);
                ASSERT_EQ(v.LastClearBitIndex(), ~0ULL);
                for (uint64_t i = v.kNumBits - 1; i >= 1; --i)
                {
                    v.ClearBit(i);
                    ASSERT_EQ(v.LastSetBitIndex(), i - 1);
                    ASSERT_EQ(v.CountLeadingZeros(), (v.kNumBits - 1) - (i - 1));
                    ASSERT_EQ(v.LastClearBitIndex(), v.kNumBits - 1);
                }
                v.ClearBit(0);
                ASSERT_EQ(v.LastSetBitIndex(), ~0ULL);
                ASSERT_EQ(v.CountLeadingZeros(), v.kNumBits);
                ASSERT_EQ(v.LastClearBitIndex(), v.kNumBits - 1);
            }

            for (const bool setExcessBits : {true, false})
            {
                v.SetAll();
                AssignExcessBits(v, setExcessBits);
                ASSERT_EQ(v.LastClearBitIndex(), ~0ULL);
                ASSERT_EQ(v.LastSetBitIndex(), v.kNumBits - 1);
                v.ClearBit(v.kNumBits - 1);
                ASSERT_EQ(v.LastClearBitIndex(), v.kNumBits - 1);
                ASSERT_EQ(v.LastSetBitIndex(), v.kNumBits == 1 ? ~0ULL : v.kNumBits - 2);
                for (uint64_t i = v.kNumBits - 2; int64_t(i) >= 0; --i)
                {
                    v.SetBit(i + 1);
                    v.ClearBit(i);
                    ASSERT_EQ(v.LastClearBitIndex(), i);
                    ASSERT_EQ(v.LastSetBitIndex(), v.kNumBits - 1);
                }
                v.SetBit(0);
                ASSERT_EQ(v.LastClearBitIndex(), ~0ULL);
                ASSERT_EQ(v.LastSetBitIndex(), v.kNumBits - 1);

                v.ClearAll();
                AssignExcessBits(v, setExcessBits);
                ASSERT_EQ(v.LastClearBitIndex(), v.kNumBits - 1);
                ASSERT_EQ(v.LastSetBitIndex(), ~0ULL);
                for (uint64_t i = v.kNumBits - 1; i >= 1; --i)
                {
                    v.SetBit(i);
                    ASSERT_EQ(v.LastClearBitIndex(), i - 1);
                    ASSERT_EQ(v.LastSetBitIndex(), v.kNumBits - 1);
                }
                v.SetBit(0);
                ASSERT_EQ(v.LastClearBitIndex(), ~0ULL);
                ASSERT_EQ(v.LastSetBitIndex(), v.kNumBits - 1);
            }
        });

    // PrevSetBitIndex, NextSetBitIndex, NthSetBitIndex
    SweepArraySizes([](auto& v)
        {
            for (const bool setExcessBits : {true, false})
            {
                v.ClearAll();
                AssignExcessBits(v, setExcessBits);
                for (uint64_t i = 0; i < v.kNumBits; ++i)
                {
                    ASSERT_EQ(v.PrevSetBitIndex(i), ~0ULL);
                    ASSERT_EQ(v.NextSetBitIndex(i), ~0ULL);
                }
                for (uint64_t i = 1; i < v.kNumBits; ++i)
                {
                    for (uint64_t j = i + 1; j < v.kNumBits; ++j)
                    {
                        for (uint64_t k = j + 1; k < v.kNumBits - 1; ++k)
                        {
                            v.ClearAll();
                            AssignExcessBits(v, setExcessBits);
                            v.SetBit(i);
                            v.SetBit(j);
                            v.SetBit(k);

                            ASSERT_EQ(v.NthSetBitIndex(0), i);
                            ASSERT_EQ(v.NthSetBitIndex(1), j);
                            ASSERT_EQ(v.NthSetBitIndex(2), k);
                            ASSERT_EQ(v.NthSetBitIndex(3), ~0ULL);

                            ASSERT_EQ(v.PrevSetBitIndex(0), ~0ULL);
                            ASSERT_EQ(v.NextSetBitIndex(0), i);

                            ASSERT_EQ(v.PrevSetBitIndex(i - 1), ~0ULL);
                            ASSERT_EQ(v.PrevSetBitIndex(i), ~0ULL);
                            ASSERT_EQ(v.PrevSetBitIndex(i + 1), i);
                            ASSERT_EQ(v.NextSetBitIndex(i - 1), i);
                            ASSERT_EQ(v.NextSetBitIndex(i), j);
                            ASSERT_EQ(v.NextSetBitIndex(i + 1), i + 1 < j ? j : k);

                            ASSERT_EQ(v.PrevSetBitIndex(j - 1), i < j - 1 ? i : ~0ULL);
                            ASSERT_EQ(v.PrevSetBitIndex(j), i);
                            ASSERT_EQ(v.PrevSetBitIndex(j + 1), j);
                            ASSERT_EQ(v.NextSetBitIndex(j - 1), j);
                            ASSERT_EQ(v.NextSetBitIndex(j), k);
                            ASSERT_EQ(v.NextSetBitIndex(j + 1), j + 1 < k ? k : ~0ULL);

                            ASSERT_EQ(v.PrevSetBitIndex(k - 1), j < k - 1 ? j : i);
                            ASSERT_EQ(v.PrevSetBitIndex(k), j);
                            ASSERT_EQ(v.PrevSetBitIndex(k + 1), k);
                            ASSERT_EQ(v.NextSetBitIndex(k - 1), k);
                            ASSERT_EQ(v.NextSetBitIndex(k), ~0ULL);
                            ASSERT_EQ(v.NextSetBitIndex(k + 1), ~0ULL);

                            ASSERT_EQ(v.PrevSetBitIndex(v.kNumBits - 1), k);
                            ASSERT_EQ(v.NextSetBitIndex(v.kNumBits - 1), ~0ULL);
                        }
                    }
                }
            }
        });

    // PrevClearBitIndex, NextClearBitIndex, NthClearBitIndex
    SweepArraySizes([](auto& v)
        {
            for (const bool setExcessBits : {true, false})
            {
                v.SetAll();
                AssignExcessBits(v, setExcessBits);
                for (uint64_t i = 0; i < v.kNumBits; ++i)
                {
                    ASSERT_EQ(v.PrevClearBitIndex(i), ~0ULL);
                    ASSERT_EQ(v.NextClearBitIndex(i), ~0ULL);
                }
                for (uint64_t i = 1; i < v.kNumBits; ++i)
                {
                    for (uint64_t j = i + 1; j < v.kNumBits; ++j)
                    {
                        for (uint64_t k = j + 1; k < v.kNumBits - 1; ++k)
                        {
                            v.SetAll();
                            AssignExcessBits(v, setExcessBits);
                            v.ClearBit(i);
                            v.ClearBit(j);
                            v.ClearBit(k);

                            ASSERT_EQ(v.NthClearBitIndex(0), i);
                            ASSERT_EQ(v.NthClearBitIndex(1), j);
                            ASSERT_EQ(v.NthClearBitIndex(2), k);
                            ASSERT_EQ(v.NthClearBitIndex(3), ~0ULL);

                            ASSERT_EQ(v.PrevClearBitIndex(0), ~0ULL);
                            ASSERT_EQ(v.NextClearBitIndex(0), i);

                            ASSERT_EQ(v.PrevClearBitIndex(i - 1), ~0ULL);
                            ASSERT_EQ(v.PrevClearBitIndex(i), ~0ULL);
                            ASSERT_EQ(v.PrevClearBitIndex(i + 1), i);
                            ASSERT_EQ(v.NextClearBitIndex(i - 1), i);
                            ASSERT_EQ(v.NextClearBitIndex(i), j);
                            ASSERT_EQ(v.NextClearBitIndex(i + 1), i + 1 < j ? j : k);

                            ASSERT_EQ(v.PrevClearBitIndex(j - 1), i < j - 1 ? i : ~0ULL);
                            ASSERT_EQ(v.PrevClearBitIndex(j), i);
                            ASSERT_EQ(v.PrevClearBitIndex(j + 1), j);
                            ASSERT_EQ(v.NextClearBitIndex(j - 1), j);
                            ASSERT_EQ(v.NextClearBitIndex(j), k);
                            ASSERT_EQ(v.NextClearBitIndex(j + 1), j + 1 < k ? k : ~0ULL);

                            ASSERT_EQ(v.PrevClearBitIndex(k - 1), j < k - 1 ? j : i);
                            ASSERT_EQ(v.PrevClearBitIndex(k), j);
                            ASSERT_EQ(v.PrevClearBitIndex(k + 1), k);
                            ASSERT_EQ(v.NextClearBitIndex(k - 1), k);
                            ASSERT_EQ(v.NextClearBitIndex(k), ~0ULL);
                            ASSERT_EQ(v.NextClearBitIndex(k + 1), ~0ULL);

                            ASSERT_EQ(v.PrevClearBitIndex(v.kNumBits - 1), k);
                            ASSERT_EQ(v.NextClearBitIndex(v.kNumBits - 1), ~0ULL);
                        }
                    }
                }
            }
        });

    // NthSetBitIndex
    SweepArraySizes([](auto& v) { v.SetAll(); },
        [](auto& v)
        {
            for (uint64_t i = 0; i < v.kNumBits; ++i)
            {
                ASSERT_EQ(v.NthSetBitIndex(i), i);
            }
            ASSERT_EQ(v.NthSetBitIndex(v.kNumBits), ~0ULL);
        }
    );

    // NthClearBitIndex
    SweepArraySizes([](auto& v) { v.ClearAll(); },
        [](auto& v)
        {
            for (uint64_t i = 0; i < v.kNumBits; ++i)
            {
                ASSERT_EQ(v.NthClearBitIndex(i), i);
            }
            ASSERT_EQ(v.NthClearBitIndex(v.kNumBits), ~0ULL);
        }
    );

    {
        auto RefFirstBlockOfNSetBits = [](auto& v, uint64_t n)
        {
            uint64_t iStart = 0;
            for (uint64_t i = 0; i < v.kNumBits; ++i)
            {
                if (!v.IsBitSet(i))
                    iStart = i + 1;
                if (i - iStart + 1 == n)
                    return iStart;
            }
            return v.kNumBits - iStart < n ? ~0ULL : iStart;
        };

        auto RefFirstBlockOfNClearBits = [](auto& v, uint64_t n)
        {
            uint64_t iStart = 0;
            for (uint64_t i = 0; i < v.kNumBits; ++i)
            {
                if (v.IsBitSet(i))
                    iStart = i + 1;
                if (i - iStart + 1 == n)
                    return iStart;
            }
            return v.kNumBits - iStart < n ? ~0ULL : iStart;
        };

        auto RefFirstAlignedBlockOfNSetBits = [](auto& v, uint64_t n, uint64_t alignment)
        {
            uint64_t iStart = 0;
            for (uint64_t i = 0; i < v.kNumBits; ++i)
            {
                if (!v.IsBitSet(i))
                    iStart = (i + 1) + (alignment - 1) - (((i + 1) + (alignment - 1)) % alignment);
                if (i - iStart + 1 == n)
                    return iStart;
            }
            return iStart >= v.kNumBits || v.kNumBits - iStart < n ? ~0ULL : iStart;
        };

        auto RefFirstAlignedBlockOfNClearBits = [](auto& v, uint64_t n, uint64_t alignment)
        {
            uint64_t iStart = 0;
            for (uint64_t i = 0; i < v.kNumBits; ++i)
            {
                if (v.IsBitSet(i))
                    iStart = (i + 1) + (alignment - 1) - (((i + 1) + (alignment - 1)) % alignment);
                if (i - iStart + 1 == n)
                    return iStart;
            }
            return iStart >= v.kNumBits || v.kNumBits - iStart < n ? ~0ULL : iStart;
        };

        BitArray<18528 + 128> v;

        // FirstBlockOfNSetBits, FirstAlignedBlockOfNSetBits
        for (const bool setExcessBits : {true, false})
        {
            for (uint64_t iStart = 0; iStart < 256; ++iStart)
            {
                v.ClearAll();
                AssignExcessBits(v, setExcessBits);
                constexpr uint64_t kMaxN = 192;
                uint64_t i = iStart;
                for (uint64_t n = 1; n < kMaxN; ++n)
                {
                    const uint64_t iEnd = i + n - 1;
                    v.SetBitsInRange(i, iEnd < v.kNumBits ? iEnd : v.kNumBits - 1);
                    i += n + 1;
                }
                for (uint64_t n = 1; n < kMaxN; ++n)
                {
                    ASSERT_EQ(RefFirstBlockOfNSetBits(v, n), v.FirstBlockOfNSetBits(n));
                    for (uint64_t align = 1; align <= 256; align *= 2)
                        ASSERT_EQ(RefFirstAlignedBlockOfNSetBits(v, n, align), v.FirstAlignedBlockOfNSetBits(n, align));
                }
            }
        }

        // FirstBlockOfNClearBits, FirstAlignedBlockOfNClearBits
        for (const bool setExcessBits : {true, false})
        {
            for (uint64_t iStart = 0; iStart < 256; ++iStart)
            {
                v.SetAll();
                AssignExcessBits(v, setExcessBits);
                constexpr uint64_t kMaxN = 192;
                uint64_t i = iStart;
                for (uint64_t n = 1; n < kMaxN; ++n)
                {
                    const uint64_t iEnd = i + n - 1;
                    v.ClearBitsInRange(i, iEnd < v.kNumBits ? iEnd : v.kNumBits - 1);
                    i += n + 1;
                }
                for (uint64_t n = 1; n < kMaxN; ++n)
                {
                    ASSERT_EQ(RefFirstBlockOfNClearBits(v, n), v.FirstBlockOfNClearBits(n));
                    for (uint64_t align = 1; align <= 256; align *= 2)
                    {
                        const uint64_t ref = RefFirstAlignedBlockOfNClearBits(v, n, align);
                        const uint64_t test = v.FirstAlignedBlockOfNClearBits(n, align);
                        ASSERT_EQ(ref, test);
                    }
                }
            }
        }
    }

#define TEST_UNARY_OP(op, inplaceOp, scalarOp)                                                                      \
    SweepArraySizes([](auto& v) { v.Rep(0x357cab98bce42045ULL); },                                                  \
    [](auto& v)                                                                                                     \
    {                                                                                                               \
        BitArray<v.kNumBits> r1 = op(v);                                                                            \
        BitArray<v.kNumBits> r2 = v;                                                                                \
        inplaceOp(r2);                                                                                              \
                                                                                                                    \
        ASSERT_TRUE(r1 == r2);                                                                                      \
        for (uint64_t i = 0; i < v.kNumBlocks; ++i)                                                                 \
        {                                                                                                           \
            uint64_t* pV = reinterpret_cast<uint64_t*>(&v);                                                         \
            uint64_t* pR = reinterpret_cast<uint64_t*>(&r1);                                                        \
            ASSERT_EQ(pR[i], scalarOp(pV[i]));                                                                      \
        }                                                                                                           \
    }                                                                                                               \
    );

#define TEST_BINARY_OP(op, inplaceOp, scalarOp)                                                                     \
    SweepArraySizesPair([](auto& v) { v.Rep(0x357cab98bce42045ULL); }, [](auto& v) { v.Rep(0x6e751b283bbe6557); },  \
    [](auto& a, auto& b)                                                                                            \
    {                                                                                                               \
        BitArray<a.kNumBits> r1 = op(a, b);                                                                         \
        BitArray<a.kNumBits> r2 = a;                                                                                \
        inplaceOp(r2, b);                                                                                           \
                                                                                                                    \
        ASSERT_TRUE(r1 == r2);                                                                                      \
        for (uint64_t i = 0; i < a.kNumBlocks; ++i)                                                                 \
        {                                                                                                           \
            uint64_t* pA = reinterpret_cast<uint64_t*>(&a);                                                         \
            uint64_t* pB = reinterpret_cast<uint64_t*>(&b);                                                         \
            uint64_t* pR = reinterpret_cast<uint64_t*>(&r1);                                                        \
            ASSERT_EQ(pR[i], scalarOp(pA[i], pB[i]));                                                               \
        }                                                                                                           \
    }                                                                                                               \
    );

#define TEST_TERNARY_OP(op, inplaceOp, scalarOp)                                                                    \
    SweepArraySizesTriplet(                                                                                         \
    [](auto& v) { v.Rep(0x357cab98bce42045ULL); },                                                                  \
    [](auto& v) { v.Rep(0x6e751b283bbe6557); }, [](auto& v) { v.Rep(0x23909d5a478b7aef); },                         \
    [](auto& a, auto& b, auto& c)                                                                                   \
    {                                                                                                               \
        BitArray<a.kNumBits> r1 = op(a, b, c);                                                                      \
        BitArray<a.kNumBits> r2 = a;                                                                                \
        inplaceOp(r2, b, c);                                                                                        \
                                                                                                                    \
        ASSERT_TRUE(r1 == r2);                                                                                      \
        for (uint64_t i = 0; i < a.kNumBlocks; ++i)                                                                 \
        {                                                                                                           \
            uint64_t* pA = reinterpret_cast<uint64_t*>(&a);                                                         \
            uint64_t* pB = reinterpret_cast<uint64_t*>(&b);                                                         \
            uint64_t* pC = reinterpret_cast<uint64_t*>(&c);                                                         \
            uint64_t* pR = reinterpret_cast<uint64_t*>(&r1);                                                        \
            ASSERT_EQ(pR[i], scalarOp(pA[i], pB[i], pC[i]));                                                        \
        }                                                                                                           \
    }                                                                                                               \
    );

    TEST_BINARY_OP([](auto& a, auto& b) { return a | b; }, [](auto& a, auto& b) { a |= b; },
        [](uint64_t a, uint64_t b) { return a | b; }
    );
    TEST_BINARY_OP([](auto& a, auto& b) { return OrNot(a, b); }, [](auto& a, auto& b) { a.OrNot(b); },
        [](uint64_t a, uint64_t b) { return a | ~b; }
    );
    TEST_BINARY_OP([](auto& a, auto& b) { return OrNot(b, a); }, [](auto& a, auto& b) { a.NotOr(b); },
        [](uint64_t a, uint64_t b) { return ~a | b; }
    );
    TEST_BINARY_OP([](auto& a, auto& b) { return NotOrNot(a, b); }, [](auto& a, auto& b) { a.NotOrNot(b); },
        [](uint64_t a, uint64_t b) { return ~a | ~b; }
    );
    TEST_BINARY_OP([](auto& a, auto& b) { return a ^ b; }, [](auto& a, auto& b) { a ^= b; },
        [](uint64_t a, uint64_t b) { return a ^ b; }
    );
    TEST_BINARY_OP([](auto& a, auto& b) { return XorNot(a, b); }, [](auto& a, auto& b) { a.XorNot(b); },
        [](uint64_t a, uint64_t b) { return a ^ ~b; }
    );
    TEST_BINARY_OP([](auto& a, auto& b) { return XorNot(b, a); }, [](auto& a, auto& b) { a.NotXor(b); },
        [](uint64_t a, uint64_t b) { return ~a ^ b; }
    );
    TEST_BINARY_OP([](auto& a, auto& b) { return NotXorNot(a, b); }, [](auto& a, auto& b) { a.NotXorNot(b); },
        [](uint64_t a, uint64_t b) { return ~a ^ ~b; }
    );
    TEST_BINARY_OP([](auto& a, auto& b) { return a & b; }, [](auto& a, auto& b) { a &= b; },
        [](uint64_t a, uint64_t b) { return a & b; }
    );
    TEST_BINARY_OP([](auto& a, auto& b) { return AndNot(a, b); }, [](auto& a, auto& b) { a.AndNot(b); },
        [](uint64_t a, uint64_t b) { return a & ~b; }
    );
    TEST_BINARY_OP([](auto& a, auto& b) { return AndNot(b, a); }, [](auto& a, auto& b) { a.NotAnd(b); },
        [](uint64_t a, uint64_t b) { return ~a & b; }
    );
    TEST_BINARY_OP([](auto& a, auto& b) { return NotAndNot(a, b); }, [](auto& a, auto& b) { a.NotAndNot(b); },
        [](uint64_t a, uint64_t b) { return ~a & ~b; }
    );

    TEST_UNARY_OP([](auto& v) { return ~v; }, [](auto& v) { v.Invert(); }, [](uint64_t v) { return ~v; });

    TEST_TERNARY_OP(
        [](auto& a, auto& b, auto& c) { return Blend(a, b, c); },
        [](auto& a, auto& b, auto& c) { a.Blend(b, c); },
        [](uint64_t a, uint64_t b, uint64_t c) { return (a & ~c) | (b & c); }
    );

    // operator==, operator!=
    SweepArraySizes([](auto& v) { v.ClearAll(); },
        [](auto& v)
        {
            BitArray<v.kNumBits> w = v;
            for (const bool setExcessBits : {true, false})
            {
                AssignExcessBits(w, setExcessBits);
                ASSERT_TRUE(w == v);
                ASSERT_FALSE(w != v);
                for (uint64_t i = 0; i < v.kNumBits; ++i)
                {
                    v.XorBit(i);
                    ASSERT_FALSE(w == v);
                    ASSERT_TRUE(w != v);
                    v.XorBit(i);
                    ASSERT_TRUE(w == v);
                    ASSERT_FALSE(w != v);
                }
            }
        }
    );

    // shifts
    SweepArraySizes([](auto& v)
        {
            static constexpr uint64_t kRand[] = { 0x357cab98bce42045ULL, 0x6e751b283bbe6557, 0x23909d5a478b7aef };
            for (uint64_t i = 0; i < v.kNumBlocks; ++i)
            {
                uint64_t* pV = reinterpret_cast<uint64_t*>(&v);
                pV[i] = kRand[i % 3];
            }
        },
        [](auto& v)
        {
            // right shifts
            for (uint64_t i = 0; i < (v.kNumBits < 64 ? v.kNumBits : 64); ++i)
            {
                BitArray<v.kNumBits> r1 = v >> i;
                BitArray<v.kNumBits> r2 = v;
                r2 >>= i;
                ASSERT_TRUE(r1 == r2);
                for (uint64_t j = 0; j < v.kNumBits; ++j)
                {
                    ASSERT_EQ(j + i < v.kNumBits ? v.IsBitSet(j + i) : false, r1.IsBitSet(j));
                }
            }

            // left shifts
            for (uint64_t i = 0; i < (v.kNumBits < 64 ? v.kNumBits : 64); ++i)
            {
                BitArray<v.kNumBits> r1 = v << i;
                BitArray<v.kNumBits> r2 = v;
                r2 <<= i;
                ASSERT_TRUE(r1 == r2);
                for (uint64_t j = 0; j < v.kNumBits; ++j)
                {
                    ASSERT_EQ(j < i ? false : v.IsBitSet(j - i), r1.IsBitSet(j));
                }
            }
        }
        );

    // iterator
    SweepArraySizes([](auto& v)
        {
            static constexpr uint64_t kRand[] = { 0x357cab98bce42045ULL, 0x6e751b283bbe6557, 0x23909d5a478b7aef };
            for (uint64_t i = 0; i < v.kNumBlocks; ++i)
            {
                uint64_t* pV = reinterpret_cast<uint64_t*>(&v);
                pV[i] = kRand[i % 3];
            }
        },
        [](auto& v)
        {
            uint64_t iRef = v.FirstSetBitIndex();
            for (const uint64_t i : v)
            {
                ASSERT_EQ(i, iRef);
                iRef = v.NextSetBitIndex(iRef);
            }
            ASSERT_EQ(iRef, ~0ULL);
        }
        );

    SweepArraySizes([](auto& v)
        {
            for (const bool setExcessBits : {true, false})
            {
                for (uint64_t i = 0; i < v.kNumBits; ++i)
                {
                    for (uint64_t j = i; j < v.kNumBits; ++j)
                    {
                        v.ClearAll();
                        AssignExcessBits(v, setExcessBits);
                        v.SetBit(i);
                        v.SetBit(j);

                        uint64_t iRef = v.FirstSetBitIndex();
                        for (const uint64_t k : v)
                        {
                            ASSERT_EQ(k, iRef);
                            iRef = v.NextSetBitIndex(iRef);
                        }
                        ASSERT_EQ(iRef, ~0ULL);
                    }
                }
            }
        });

    SweepArraySizes([](auto& v) { v.ClearAll(); }, [](auto& v)
        {
            uint64_t iRef = v.FirstSetBitIndex();
            for (const uint64_t i : v)
            {
                ASSERT_EQ(i, iRef);
                iRef = v.NextSetBitIndex(iRef);
            }
            ASSERT_EQ(iRef, ~0ULL);
        });

    SweepArraySizes([](auto& v) { v.SetAll(); }, [](auto& v)
        {
            uint64_t iRef = v.FirstSetBitIndex();
            for (const uint64_t i : v)
            {
                ASSERT_EQ(i, iRef);
                iRef = v.NextSetBitIndex(iRef);
            }
            ASSERT_EQ(iRef, ~0ULL);
        });

    // SmallBitArray
    TestSmall(TestDefaultConstruct);
    TestSmall(TestValueConstruct);
    TestSmall(TestOr);
    TestSmall(TestXor);
    TestSmall(TestAnd);
    TestSmall(TestNot);
    TestSmall(TestEq);
    TestSmall(TestIterator);
}

/*  Copyright (C) 2011-2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DETAIL_INSN_BIT_NOT_H
#define LIBSIMDPP_SIMDPP_DETAIL_INSN_BIT_NOT_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/detail/null/foreach.h>
#include <simdpp/detail/null/bitwise.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif
namespace detail {
namespace insn {


inline uint8x16 i_bit_not(uint8x16 a)
{
#if SIMDPP_USE_NULL
    return detail::null::foreach<uint8x16>(a, [](uint64_t a){ return ~a; });
#elif SIMDPP_USE_SSE2
    uint8x16 ones = uint8x16::ones();
    return bit_xor(a, ones);
#elif SIMDPP_USE_NEON
    return vmvnq_u8(a);
#elif SIMDPP_USE_ALTIVEC
    return vec_nor((__vector uint8_t)a, (__vector uint8_t)a);
#endif
}

#if SIMDPP_USE_AVX2
inline uint8x32 i_bit_not(uint8x32 a)
{
    uint8x32 ones = uint8x32::ones();
    return bit_xor(a, ones);
}
#endif

template<unsigned N>
inline uint8<N> i_bit_not(uint8<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(uint8<N>, i_bit_not, a)
}

template<unsigned N>
uint16<N> i_bit_not(uint16<N> a) { return uint16<N>(i_bit_not(uint8<N*2>(a))); }
template<unsigned N>
uint32<N> i_bit_not(uint32<N> a) { return uint32<N>(i_bit_not(uint8<N*4>(a))); }
template<unsigned N>
uint64<N> i_bit_not(uint64<N> a) { return uint64<N>(i_bit_not(uint8<N*8>(a))); }

// -----------------------------------------------------------------------------

inline mask_int8x16 i_bit_not(mask_int8x16 a)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_not_mm(a);
#else
    return (mask_int8x16)i_bit_not(uint8x16(a));
#endif
}

inline mask_int16x8 i_bit_not(mask_int16x8 a)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_not_mm(a);
#else
    return (mask_int16x8)i_bit_not(uint16x8(a));
#endif
}

inline mask_int32x4 i_bit_not(mask_int32x4 a)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_not_mm(a);
#else
    return (mask_int32x4)i_bit_not(uint32x4(a));
#endif
}

inline mask_int64x2 i_bit_not(mask_int64x2 a)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_not_mm(a);
#else
    return (mask_int64x2)i_bit_not(uint64x2(a));
#endif
}

#if SIMDPP_USE_AVX2
inline mask_int8x32  i_bit_not(mask_int8x32 a)  { return i_bit_not(uint8x32(a)); }
inline mask_int16x16 i_bit_not(mask_int16x16 a) { return i_bit_not(uint16x16(a)); }
inline mask_int32x8  i_bit_not(mask_int32x8 a)  { return i_bit_not(uint32x8(a)); }
inline mask_int64x4  i_bit_not(mask_int64x4 a)  { return i_bit_not(uint64x4(a)); }
#endif

template<unsigned N>
inline mask_int8<N> i_bit_not(mask_int8<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(mask_int8<N>, i_bit_not, a)
}
template<unsigned N>
inline mask_int16<N> i_bit_not(mask_int16<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(mask_int16<N>, i_bit_not, a)
}
template<unsigned N>
inline mask_int32<N> i_bit_not(mask_int32<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(mask_int32<N>, i_bit_not, a)
}
template<unsigned N>
inline mask_int64<N> i_bit_not(mask_int64<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(mask_int64<N>, i_bit_not, a)
}

// -----------------------------------------------------------------------------

inline float32x4 i_bit_not(float32x4 a)
{
#if SIMDPP_USE_NULL
    return float32x4(i_bit_not(uint32x4(a)));
#elif SIMDPP_USE_SSE2
    uint32x4 ones = uint32x4::ones();
    return bit_xor(a, ones);
#elif SIMDPP_USE_NEON
    return (float32x4) vmvnq_u32((uint32x4)a);
#elif SIMDPP_USE_ALTIVEC
    return vec_nor((__vector float)a, (__vector float)a);
#endif
}

inline float64x2 i_bit_not(float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return float64x2(i_bit_not(uint64x2(a)));
#elif SIMDPP_USE_SSE2
    uint64x2 ones = uint64x2::ones();
    return bit_xor(a, ones);
#endif
}

#if SIMDPP_USE_AVX
inline float32x8 i_bit_not(float32x8 a)
{
    uint32x8 ones = uint32x8::ones();
    return bit_xor(a, ones);
}
#endif

template<unsigned N>
float32<N> i_bit_not(float32<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(float32<N>, i_bit_not, a)
}

#if SIMDPP_USE_AVX
inline float64x4 i_bit_not(float64x4 a)
{
    uint64x4 ones = uint64x4::ones();
    return bit_xor(a, ones);
}
#endif

template<unsigned N>
float64<N> i_bit_not(float64<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(float64<N>, i_bit_not, a)
}

// -----------------------------------------------------------------------------

inline mask_float32x4 i_bit_not(mask_float32x4 a)
{
#if SIMDPP_USE_NULL
    return detail::null::bit_not_mm(a);
#else
    return (mask_float32x4) i_bit_not(float32x4(a));
#endif
}

inline mask_float64x2 i_bit_not(mask_float64x2 a)
{
#if SIMDPP_USE_NULL || SIMDPP_USE_NEON || SIMDPP_USE_ALTIVEC
    return detail::null::bit_not_mm(a);
#else
    return (mask_float64x2) i_bit_not(float64x2(a));
#endif
}

#if SIMDPP_USE_AVX
inline mask_float32x8 i_bit_not(mask_float32x8 a)
{
    return i_bit_not(float32x8(a));
}
#endif

template<unsigned N>
inline mask_float32<N> i_bit_not(mask_float32<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(mask_float32<N>, i_bit_not, a)
}

#if SIMDPP_USE_AVX
inline mask_float64x4 i_bit_not(mask_float64x4 a)
{
    return i_bit_not(float64x4(a));
}
#endif

template<unsigned N>
inline mask_float64<N> i_bit_not(mask_float64<N> a)
{
    SIMDPP_VEC_ARRAY_IMPL1(mask_float64<N>, i_bit_not, a)
}


} // namespace insn
} // namespace detail
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif


#pragma once

////////////////////////////////////////////////////////////////////////////////
// The MIT License (MIT)
//
// Copyright (c) 2017 Nicholas Frechette & Animation Compression Library contributors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "acl/math/math.h"

namespace acl
{
#if defined(ACL_SSE2_INTRINSICS)
	typedef __m128 Quat_32;
	typedef __m128 Vector4_32;

	struct Quat_64
	{
		__m128d xy;
		__m128d zw;
	};

	struct Vector4_64
	{
		__m128d xy;
		__m128d zw;
	};
#else
	namespace math_impl
	{
		union Converter
		{
			double dbl;
			uint64_t u64;

			constexpr Converter(uint64_t value) : u64(value) {}
			constexpr Converter(double value) : dbl(value) {}
		};

		constexpr double get_mask_value(bool is_true)
		{
			return is_true ? Converter(0xFFFFFFFFFFFFFFFFull).dbl : 0.0;
		}

		constexpr double select(double mask, double if_true, double if_false)
		{
			return Converter(mask).u64 == 0 ? if_false : if_true;
		}
	}

	struct Quat_32
	{
		float x;
		float y;
		float z;
		float w;
	};

	struct Vector4_32
	{
		float x;
		float y;
		float z;
		float w;
	};

	struct Quat_64
	{
		double x;
		double y;
		double z;
		double w;
	};

	struct Vector4_64
	{
		double x;
		double y;
		double z;
		double w;
	};
#endif

	struct Transform_32
	{
		Quat_32		rotation;
		Vector4_32	translation;
	};

	struct Transform_64
	{
		Quat_64		rotation;
		Vector4_64	translation;
	};
}

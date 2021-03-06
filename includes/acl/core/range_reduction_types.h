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

#include "acl/core/enum_utils.h"

#include <stdint.h>

#define ACL_PER_SEGMENT_RANGE_REDUCTION_COMPONENT_BIT_SIZE	8
//#define ACL_PER_SEGMENT_RANGE_REDUCTION_COMPONENT_BIT_SIZE	16
#define ACL_PER_SEGMENT_RANGE_REDUCTION_COMPONENT_BYTE_SIZE (ACL_PER_SEGMENT_RANGE_REDUCTION_COMPONENT_BIT_SIZE / 8)

namespace acl
{
	// BE CAREFUL WHEN CHANGING VALUES IN THIS ENUM
	// The range reduction strategy is serialized in the compressed data, if you change a value
	// the compressed clips will be invalid. If you do, bump the appropriate algorithm versions.
	enum class RangeReductionFlags8 : uint8_t
	{
		None				= 0x00,

		// Flags to determine which tracks have range reduction applied
		Rotations			= 0x01,
		Translations		= 0x02,
		//Scales			= 0x04,		// TODO: Implement this
		//Properties		= 0x08,		// TODO: Implement this
	};

	ACL_IMPL_ENUM_FLAGS_OPERATORS(RangeReductionFlags8)

	//////////////////////////////////////////////////////////////////////////

	// TODO: constexpr
	inline const char* get_range_reduction_name(RangeReductionFlags8 flags)
	{
		// Some compilers have trouble with constexpr operator| with enums in a case switch statement
		if (flags == RangeReductionFlags8::None)
			return "RangeReduction::None";
		else if (flags == RangeReductionFlags8::Rotations)
			return "RangeReduction::Rotations";
		else if (flags == RangeReductionFlags8::Translations)
			return "RangeReduction::Translations";
		else if (flags == (RangeReductionFlags8::Rotations | RangeReductionFlags8::Translations))
			return "RangeReduction::Rotations | RangeReduction::Translations";
		else
			return "<Invalid>";
	}
}

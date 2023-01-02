#pragma once

#include <cmath>
#include <corecrt_math_defines.h>

namespace Math
{
	template<typename T = float>
	inline T Max(const T& a, const T& b)
	{
		if (a > b) return a;
		else return b;

	}
	template<typename T = float>
	inline T Min(const T& a, const T& b)
	{
		if (a < b) return a;
		else return b;
	}

	template <typename T>
	inline T Abs(const T& a)
	{
		return a < 0 ? -a : a;
	}

	template<typename T>
	inline T lerp(const T& start, const T& reach, float factor) { return start + factor * (reach - start); }

	template <typename T>
	inline T Clamp(const T value, const T min, const T max)
	{
		if (value < min)
			return min;
		if (value > max)
			return max;
		return value;
	}
}
#pragma once

#include <cmath>
#include <corecrt_math_defines.h>

namespace Math
{
	const float RAD2DEG = 180.f / (float)M_PI;
	const float DEG2RAD = (float)M_PI / 180.f;

	static constexpr float pi = 3.14159265358979323846264f;
	static constexpr float halfPi = pi / 2.f;
	static constexpr float doublePi = pi * 2.f;
	static constexpr float epsilon = 1e-24f;
	static constexpr float weakEpsilon = 0.00001f;

	template<typename T = float>
	T Max(const T& a, const T& b);

	template<typename T = float>
	T Min(const T& a, const T& b);

	template <typename T>
	T Abs(const T& a);

	template <typename T>
	T lerp(const T& a, const T& b, const float t);

	template <typename T>
	T Clamp(const T value, const T min, const T max);
}

#include "Utils.inl"
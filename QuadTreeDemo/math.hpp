#pragma once


struct vec2
{
	float x{}, y{};
};

struct vec3
{
	float x{}, y{}, z{};
};

static float lerp(float a, float b, float f)
{
	return a * f + b * (1 - f);
}

static float clamp(float a, float b, float v)
{
	if (v < a) return a;
	if (v > b) return b;
	return v;
}
#pragma once

#include <memory>

#include "math.hpp"

struct QuadBounds
{
	float x0{}, y0{}, x1{}, y1{};
	int depth{};
};

class Quad
{
public:
	QuadBounds bounds{};

	std::unique_ptr<Quad> child1{};
	std::unique_ptr<Quad> child2{};
	std::unique_ptr<Quad> child3{};
	std::unique_ptr<Quad> child4{};

	Quad(float x0, float y0, float x1, float y1, int depth) : bounds{ x0,y0,x1,y1, depth },
		child1{ nullptr },
		child2{ nullptr },
		child3{ nullptr },
		child4{ nullptr }
	{}

	bool subdivide();

	inline bool isLeaf() const
	{
		return this->child1 == nullptr && this->child2 == nullptr && this->child3 == nullptr && this->child4 == nullptr;
	}

	inline vec2 getCenter() const
	{
		return { 0.5f * (bounds.x0 + bounds.x1), 0.5f * (bounds.y0 + bounds.y1) };
	}

	inline float getWidth() const
	{
		return bounds.x1 - bounds.x0;
	}
};


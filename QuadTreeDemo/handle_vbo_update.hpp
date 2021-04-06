#pragma once

#include <cmath>
#include <cstdint>
#include <vector>

#include <GL/glew.h>

#include "vertex.hpp"
#include "quad.hpp"



static void generateQuadElement(Quad* q, vec2& loc, float radius2)
{
	float x0 = q->bounds.x0;
	float y0 = q->bounds.y0;
	float x1 = q->bounds.x1;
	float y1 = q->bounds.y1;

	auto in_range = [x0, x1, loc](float x, float y) -> bool {
		float f = 1.0f;
		float xx = x - loc.x;
		float yy = y - loc.y;
		return xx * xx + yy * yy <= f * (x0 - x1) * (x0 - x1);
	};

	auto in_bounds = [x0, y0, x1, y1, loc]() -> bool {
		return loc.x > x0 && loc.x < x1&& loc.y < y0 && loc.y > y1;
	};

	bool c1 = in_range(x0, y0);
	bool c2 = in_range(x1, y0);
	bool c3 = in_range(x0, y1);
	bool c4 = in_range(x1, y1);

	//if (c1 && c2 && c3 && c4) return;
	if (!c1 && !c2 && !c3 && !c4 && !in_bounds())
	{
		return;
	}

	if (!q->subdivide())
		return;

	generateQuadElement(q->child1.get(), loc, radius2);
	generateQuadElement(q->child2.get(), loc, radius2);
	generateQuadElement(q->child3.get(), loc, radius2);
	generateQuadElement(q->child4.get(), loc, radius2);
}

static Quad generateQuad(vec2& loc)
{
	Quad result{ -1, 1, 1, -1, 0 };
	float radius = 0.1f;
	generateQuadElement(&result, loc, radius);
	return result;
}

static void fillQuadList(const Quad * q, std::vector<QuadBounds>& list)
{
	if (q->isLeaf())
	{
		list.push_back(q->bounds);
		return;
	}

	fillQuadList(q->child1.get(), list);
	fillQuadList(q->child2.get(), list);
	fillQuadList(q->child3.get(), list);
	fillQuadList(q->child4.get(), list);
}



static std::vector<QuadBounds> getListOfLeafQuads(const Quad& q)
{
	static std::vector< QuadBounds> result;
	result.clear();

	fillQuadList(&q, result);
	return result;
}

static std::vector<Face> getFaceListFromQuadBoundList(const std::vector<QuadBounds>& bounds)
{
	static std::vector<Face> result;
	result.clear();

	for (const QuadBounds &b : bounds)
	{
		const float d = b.depth;
		const vec3 c = vec3{ 0.1f * d, 0.1f * d, 0.1f * d };
		result.push_back({ b.x0, b.y0, b.x1, b.y1, c.x, c.y, c.z });
	}

	return result;
}

static int regenerateVBO(vec2 loc, GLuint vbo)
{
	const Quad mainQuad = generateQuad(loc);
	const std::vector<QuadBounds> bounds = getListOfLeafQuads(mainQuad);
	const std::vector<Face> faces = getFaceListFromQuadBoundList(bounds);

	const int length = clamp(0, 384,faces.size());
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, length * sizeof(Face), faces.data());
	//glBufferData(GL_ARRAY_BUFFER, faces.size() * sizeof(Face), faces.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	const size_t NUM_OF_TRIANGLES_PER_FACE = 2;
	return faces.size() * NUM_OF_TRIANGLES_PER_FACE;
}
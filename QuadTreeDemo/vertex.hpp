#pragma once

struct Vertex
{
	float x, y, z;
	float r, g, b;
};

struct Triangle
{
	Vertex v0, v1, v2;
};

struct Face
{
	Triangle t1, t2;

	Face(float x0, float y0, float x1, float y1, float r, float g, float b)
		: t1{
				Vertex {x0,y0,0, r, g, b},
				Vertex {x0,y1,0, r, g, b},
				Vertex {x1,y1,0, r, g, b}
	},
		t2{
				Vertex {x1,y1, 0, r, g, b},
				Vertex {x1,y0,0, r, g, b},
				Vertex {x0,y0,0, r, g, b}
	}
	{}
};
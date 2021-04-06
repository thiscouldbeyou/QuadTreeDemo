#include "quad.hpp"


#include "math.hpp"

bool Quad::subdivide()
{

	if (this->bounds.depth >= 9) return false;
	if (!isLeaf())
	{
		this->child1->subdivide();
		this->child2->subdivide();
		this->child3->subdivide();
		this->child4->subdivide();
		return true;
	}
	const float x0 = bounds.x0;
	const float y0 = bounds.y0;
	const float x1 = bounds.x1;
	const float y1 = bounds.y1;
	const float midx = lerp(x0, x1, 0.5f);
	const float midy = lerp(y0, y1, 0.5f);
	this->child1 = std::make_unique<Quad>(x0, y0, midx, midy, bounds.depth + 1);
	this->child2 = std::make_unique<Quad>(midx, y0, x1, midy, bounds.depth + 1);
	this->child3 = std::make_unique<Quad>(x0, midy, midx, y1, bounds.depth + 1);
	this->child4 = std::make_unique<Quad>(midx, midy, x1, y1, bounds.depth + 1);
	return true;
}
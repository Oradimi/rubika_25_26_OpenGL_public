#pragma once

#include "Camera.h"

namespace threshold
{
	struct Vertex
	{
		float position[3];
		float color[3];
		float texCoord[2];
	};

	void init();
	void update();
	void draw(Camera& camera);
	void destroy();
}
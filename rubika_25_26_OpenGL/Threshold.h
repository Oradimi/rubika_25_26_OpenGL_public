#pragma once

namespace threshold
{
	struct Vertex
	{
		float position[3];
		float color[3];
	};

	void init();
	void update();
	void draw();
	void destroy();
}
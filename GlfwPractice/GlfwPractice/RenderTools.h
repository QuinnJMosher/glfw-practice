#ifndef _RenderTools_h_
#define _RenderTools_h_
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GLFW/glfw3.h"
#include "VideoGlobals.h"

namespace rtools {

	struct Vertex
	{
		float fPositions[4];
		float fColours[4];
	};

	void ClearScreen();
	void ClearScreen(float in_r, float in_g, float in_b, float in_a);

	void RenderTriangle(float in_posX, float in_posY, float in_width, float in_height);

	bool NextFrame(GLFWwindow* in_window);
}

#endif
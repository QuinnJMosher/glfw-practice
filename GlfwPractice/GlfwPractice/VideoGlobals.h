#ifndef _VideoGlobals_h_
#define _VideoGlobals_h_

namespace window {
	static float Width = 640;
	static float Height = 480;
	static GLFWwindow* window;
}

namespace rendering {
	static GLuint ProgramFlat;
	static GLuint MatrixIDFlat;
	static float *orthographicProjection;
}

#endif
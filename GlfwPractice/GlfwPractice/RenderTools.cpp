#include "RenderTools.h"

void rtools::ClearScreen() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void rtools::ClearScreen(float in_r, float in_g, float in_b, float in_a) {
	glClearColor(in_r, in_g, in_b, in_a);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool rtools::NextFrame(GLFWwindow* in_window) {
	if (!glfwWindowShouldClose(in_window)) {
		glfwSwapBuffers(in_window);
		glfwPollEvents();

		return false;
	} else {
		return true;
	}
}

void rtools::RenderTriangle(float in_posX, float in_posY, float in_width, float in_height) {
	//create vertices
	Vertex* myShape = new Vertex[3];
	myShape[0].fPositions[0] = in_posX + (in_height / 2);
	myShape[0].fPositions[1] = in_posY;
	myShape[1].fPositions[0] = in_posX - (in_height / 2);
	myShape[1].fPositions[1] = in_posY + (in_width / 2);
	myShape[2].fPositions[0] = in_posX - (in_height / 2);
	myShape[2].fPositions[1] = in_posY - (in_width / 2);
	for (int i = 0; i < 3; i++)
	{
		myShape[i].fPositions[2] = 0.0f;
		myShape[i].fPositions[3] = 1.0f;
		myShape[i].fColours[0] = 0.0f;
		myShape[i].fColours[1] = 0.0f;
		myShape[i].fColours[2] = 0.0f;
		myShape[i].fColours[3] = 0.0f;
	}
	myShape[0].fColours[0] = 1.0f;
	myShape[1].fColours[1] = 1.0f;
	myShape[2].fColours[2] = 1.0f;

	//generate buffer
	GLuint VBO;
	glGenBuffers(1, &VBO);
	GLuint IBO;
	glGenBuffers(1, &IBO);

	//set buffers
	if (VBO != 0)
	{
		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//allocate space for vertices on the graphics card
		glBufferData(GL_ARRAY_BUFFER, sizeof(rtools::Vertex) * 3, NULL, GL_STATIC_DRAW);
		//get pointer to allocated space on the graphics card
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, myShape, sizeof(rtools::Vertex) * 3);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	if (IBO != 0)
	{
		//bind IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		//allocate space for index info on the graphics card
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to newly allocated space on the graphics card
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify the order we'd like to draw our vertices.
		//In this case they are in sequential order
		for (int i = 0; i < 3; i++)
		{
			((char*)iBuffer)[i] = i;
		}
		//unmap and unbind
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	//preform draw
	glUniformMatrix4fv(rendering::MatrixIDFlat, 1, GL_FALSE, rendering::orthographicProjection);
	//enable shaders
	glUseProgram(rendering::ProgramFlat);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	//enable the vertex array states
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(rtools::Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(rtools::Vertex), (void*)(sizeof(float)* 4));

	//draw to the screen
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VBO);
}
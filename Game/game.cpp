#include <iostream>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;

void renderRect(float x, float y, float width, float height) {
	/* Tell GPU to wait for 4 vertices */
	glBegin(GL_QUADS);
	/* Create 4 vertices */
	glVertex2f(x, y);
	glVertex2f(x, y + height);
	glVertex2f(x + width, y + height);
	glVertex2f(x + width, y);
	/* End command */
	glEnd();
}

int main() {
	/* Initiate glfw*/
	glfwInit();
	/* Create window (width, height, title, screen, screen*/
	GLFWwindow* window = glfwCreateWindow(800, 800, "Hello World", 0, 0);
	/* Initiate openGL */
	glfwMakeContextCurrent(window);
	/* Create matrix(grid)(left, right,bottom,top) */
	glm::mat4 matrix = glm::ortho(0.0f, 9.0f, 0.0f, 9.0f);
	/* Camera will use projection specified above */
	glMatrixMode(GL_PROJECTION);
	/* Load the matrix created above */
	glLoadMatrixf(&matrix[0][0]);
	/* Create background color (replace)*/
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	bool running = true;
	while (running) {
		/* Take inputs from OS*/
		glfwPollEvents();
		/* Clear previous frame */
		glClear(GL_COLOR_BUFFER_BIT);

		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				renderRect(x * 3, y * 3, 3, 3);
			}
		}

		renderRect(0, 0, 1, 1);
		/* Swap frames to back frame buffer (create blank slate) */
		glfwSwapBuffers(window);

		if (glfwWindowShouldClose(window)) {
			running = false;
		}
	}
	return(0);
}
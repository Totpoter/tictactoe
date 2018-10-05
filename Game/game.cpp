/* TODO: Announce winner, enable color selecting */
#include <iostream>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

int playerCount = 0;
glm::mat4 matrix;
/* Create structure for the different colors */
struct Cell {
	glm::vec4 color;
	bool selected = false;
};
/* Create input structure for buttons that can be pressed */
struct Input {
	glm::vec2 mousePos;
	bool buttons[8];
};

Input input;
/* Create box colors */
Cell cells[3 * 3] = {
	{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) }, { glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) }, { glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) },
	{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) }, { glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) }, { glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) },
	{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) }, { glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) }, { glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) },
};

void renderRect(float x, float y, float width, float height, glm::vec4 color) {
	/* Tell GPU to wait for 4 vertices */
	glBegin(GL_QUADS);
	/* Create 4 vertices */
	glColor4f(color.r, color.g, color.b, color.a);
	glVertex2f(x, y);
	glVertex2f(x, y + height);
	glVertex2f(x + width, y + height);
	glVertex2f(x + width, y);
	/* End command */
	glEnd();
}
/* Create mouse location variable */
void mousePosCallback(GLFWwindow* window, double xpos, double ypos) {
	//glm::vec4 v = matrix * glm::vec4(xpos, ypos, 0.0f, 0.0f);
	glm::vec3 pos = glm::unProject(glm::vec3(xpos, 800 - ypos, 0.0f), glm::mat4(1.0f), matrix, glm::vec4(0.0f, 0.0f, 800.0f, 800.0f));
	float x = pos.x;
	float y = pos.y;
	/* Print mouse position to console*/
	// printf("Mouse X: %f Y: %f\n", x, y);
	input.mousePos = glm::vec2(x, y);
}
/* When mouse is clicked or released function */
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	input.buttons[button] = action != GLFW_RELEASE;
}
/* Main program */
int main() {
	/* Initiate glfw*/
	glfwInit();
	/* Create window (width, height, title, screen, screen*/
	GLFWwindow* window = glfwCreateWindow(800, 800, "Tic Tac Toe", 0, 0);
	/* Initiate openGL */
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mousePosCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	/* Create matrix(grid)(left, right,bottom,top) */
	matrix = glm::ortho(0.0f, 9.0f, 0.0f, 9.0f);
	/* Camera will use projection specified above */
	glMatrixMode(GL_PROJECTION);
	/* Load the matrix created above */
	glLoadMatrixf(&matrix[0][0]);
	/* Create background color (replace)*/
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	bool wasPressed = false;

	bool running = true;
	while (running) {
		/* Take inputs from OS*/
		glfwPollEvents();
		/* Clear previous frame */
		glClear(GL_COLOR_BUFFER_BIT);
		/* Check if button is pressed and when it's released */
		bool pressed = input.buttons[0];
		if (pressed && !wasPressed) {
			int index = floor(input.mousePos.x / 3.0f) + floor(input.mousePos.y / 3) * 3;
			/* Change colors of boxes when button is pressed */
			if (!cells[index].selected) {
				if (playerCount == 0) {
					cells[index].color = glm::vec4(0.2f, 0.2f, 0.5f, 1.0f);
					cells[index].selected = true;
				}
				else {
					cells[index].color = glm::vec4(0.5f, 0.2f, 0.2f, 1.0f);
					cells[index].selected = true;
				}
				/* Go to next player */
				playerCount++;
				playerCount %= 2;
				printf("playerCount %d\n", playerCount);
			}
		}
		wasPressed = pressed;
		/* Create grid system */
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				Cell cell = cells[x + y * 3];
				renderRect(x * 3 + 0.05f, y * 3 + 0.05f, 2.9f, 2.9f, cell.color);
			}
		}

		/* Swap frames to back frame buffer (create blank slate) */
		glfwSwapBuffers(window);
		/* Close program when window is closed */
		if (glfwWindowShouldClose(window)) {
			running = false;
		}
	}
	return(0);
}
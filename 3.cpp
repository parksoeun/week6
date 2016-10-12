#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"


const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i0 == i1) {
		for (int j = j0; j < j1; j++)
			drawPixel(i0, j, red, green, blue);
		return;
	}

	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}


void drawCircle(const int& i0, const int& j0, const float& red, const float& green, const float& blue) {
	int r = 50;
	for (int i = i0 - r; i < i0 + r; i++) {
		for (int j = j0 - r; j < j0 + r; j++) {
			int n = ((i - i0)*(i - i0) + (j - j0)*(j - j0) - r*r);
			int m = ((i - i0)*(i - i0) + (j - j0)*(j - j0) - (r - 1)*(r - 1));
			if (n < 0 && m>0)
				drawPixel(i, j, 0.0f, 0.0f, 0.0f);
		}
	}
}


class Box
{
public:
	int start_x, start_y;
	int end_x, end_y;

	void draw()
	{
		drawLine(300, 50, 400, 50, 0.0f, 0.0f, 0.0f);
		drawLine(300, 150, 400, 150, 0.0f, 0.0f, 0.0f);
		drawLine(300, 50, 300, 150, 0.0f, 0.0f, 0.0f);
		drawLine(400, 50, 400, 150, 0.0f, 0.0f, 0.0f);
	}
};

class Circle
{
public:

	void draw()
	{
		drawCircle(550, 250, 0.0f, 0.0f, 0.0f);
	}
};


class GeometricObjectInterface
{
public:
	virtual void draw() {};
};


template <class T_OPERATION>
class GeometricObject : public GeometricObjectInterface
{
public:
	void draw()
	{
		T_OPERATION operation;
		operation.draw();
	}
};

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

}

int main()
{


	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

		std::vector<GeometricObjectInterface*> obj_list;
		obj_list.push_back(new GeometricObject<Box>);
		obj_list.push_back(new GeometricObject<Circle>);
		for (auto itr : obj_list)
			itr->draw();

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}
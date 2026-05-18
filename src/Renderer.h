#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Renderer {
public:

	void init();
	void run();
	void clean();


private:

	GLFWwindow* window;
	int width = 1000;
	int height = 600;

};

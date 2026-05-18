#include "Renderer.h"

void Renderer::init() {

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, "CrystalRenderer", nullptr, nullptr);
	if (!window) {
		std::cout << "GLFW window couldn't be made" << std::endl;
	}

	// All the goon vulkan inits here
}

void Renderer::run() {

}

void Renderer::clean() {

	glfwDestroyWindow(window);
	glfwTerminate();
}
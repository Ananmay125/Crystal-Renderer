#include <iostream>
#include "Renderer.h"

int main() {

	Renderer crystalRenderer;

	GLFWwindow* rawWindow = crystalRenderer.getWindow();

	crystalRenderer.init();

	while(!crystalRenderer.shouldClose()) {
		
		glfwPollEvents();
		crystalRenderer.run();
	
	}

	crystalRenderer.clean();
	return 0;
}

#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "graphics/vkDevice.h"
#include "graphics/vkSwapchain.h"
#include "graphics/vkCommands.h"

class Renderer {
public:

	void init();
	void run();
	void clean();

	GLFWwindow* getWindow();
	bool shouldClose();

private:

	GLFWwindow* window;
	int width = 1000;
	int height = 600;

	// vulkan goofy
	vkDevice coreDevice;
	vkSwapchain swapchain;
	vkCommands commands;

	VkSemaphore presentSemaphore, renderSemaphore;
	VkFence renderFence;
};

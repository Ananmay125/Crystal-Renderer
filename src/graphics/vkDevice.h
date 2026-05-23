#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <VkBootstrap.h>

class vkDevice {
public:
	void init(GLFWwindow* window);
	void clean();

	vkb::Instance vkb_inst;
	VkInstance instance;
	VkSurfaceKHR surface;

	vkb::Device vkb_device;
	VkDevice device;
	VkQueue graphicsQueue;
	uint32_t graphicsQueueFamily;
};
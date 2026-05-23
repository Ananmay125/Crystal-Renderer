#pragma once
#include <vulkan/vulkan.h>
#include <VkBootstrap.h>
#include <vector>
#include "vkDevice.h"

class vkSwapchain {
public:
	void init(vkDevice& coreDevice);
	void clean();

	vkb::Swapchain vkb_swapchain;
	VkSwapchainKHR swapchain;
	std::vector<VkImage> swapchainImages;
};
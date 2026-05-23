#pragma once
#include <vulkan/vulkan.h>
#include "vkDevice.h"

class vkCommands {
public:
	void init(vkDevice& coreDevice);
	void clean(vkDevice& coreDevice);

	VkCommandPool commandPool;
	VkCommandBuffer mainCommandBuffer;
};
#include "vkCommands.h"

void vkCommands::init(vkDevice& coreDevice) {
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = coreDevice.graphicsQueueFamily;
	vkCreateCommandPool(coreDevice.device, &poolInfo, nullptr, &commandPool);

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;
	vkAllocateCommandBuffers(coreDevice.device, &allocInfo, &mainCommandBuffer);
}

void vkCommands::clean(vkDevice& coreDevice) {
	vkDestroyCommandPool(coreDevice.device, commandPool, nullptr);
}
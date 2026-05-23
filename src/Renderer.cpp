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
	coreDevice.init(window);
	swapchain.init(coreDevice);
	commands.init(coreDevice);

	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
	vkCreateFence(coreDevice.device, &fenceInfo, nullptr, &renderFence);

	VkSemaphoreCreateInfo semInfo = {};
	semInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	vkCreateSemaphore(coreDevice.device, &semInfo, nullptr, &presentSemaphore);
	vkCreateSemaphore(coreDevice.device, &semInfo, nullptr, &renderSemaphore);
}

void Renderer::run() {
	
	// Draw functions here i think
	vkWaitForFences(coreDevice.device, 1, &renderFence, VK_TRUE, UINT64_MAX);
	vkResetFences(coreDevice.device, 1, &renderFence);

	uint32_t imageIndex;
	vkAcquireNextImageKHR(coreDevice.device, swapchain.swapchain, UINT64_MAX, presentSemaphore, nullptr, &imageIndex);

	vkResetCommandBuffer(commands.mainCommandBuffer, 0);

	VkCommandBufferBeginInfo cmdBeginInfo = {};
	cmdBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	cmdBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	vkBeginCommandBuffer(commands.mainCommandBuffer, &cmdBeginInfo);

	// 2. Transition image layout to receive a color
	VkImageMemoryBarrier barrier = {};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	barrier.image = swapchain.swapchainImages[imageIndex];
	barrier.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
	vkCmdPipelineBarrier(commands.mainCommandBuffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);

	VkClearColorValue clearColor = { {0.1f, 0.1f, 0.3f, 1.0f} };
	vkCmdClearColorImage(commands.mainCommandBuffer, swapchain.swapchainImages[imageIndex], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &clearColor, 1, &barrier.subresourceRange);

	// 3. Transition image layout back to present on screen
	barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	vkCmdPipelineBarrier(commands.mainCommandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);

	vkEndCommandBuffer(commands.mainCommandBuffer);

	// 4. Submit buffer to the graphics queue
	VkSubmitInfo submit = {};
	submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	submit.pWaitDstStageMask = &waitStage;
	submit.waitSemaphoreCount = 1;
	submit.pWaitSemaphores = &presentSemaphore;
	submit.signalSemaphoreCount = 1;
	submit.pSignalSemaphores = &renderSemaphore;
	submit.commandBufferCount = 1;
	submit.pCommandBuffers = &commands.mainCommandBuffer;
	vkQueueSubmit(coreDevice.graphicsQueue, 1, &submit, renderFence);

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.pSwapchains = &swapchain.swapchain;
	presentInfo.swapchainCount = 1;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &renderSemaphore;
	presentInfo.pImageIndices = &imageIndex;
	vkQueuePresentKHR(coreDevice.graphicsQueue, &presentInfo);

	vkDeviceWaitIdle(coreDevice.device);
}

void Renderer::clean() {
	vkDeviceWaitIdle(coreDevice.device);

	vkDestroyFence(coreDevice.device, renderFence, nullptr);
	vkDestroySemaphore(coreDevice.device, renderSemaphore, nullptr);
	vkDestroySemaphore(coreDevice.device, presentSemaphore, nullptr);

	commands.clean(coreDevice);
	swapchain.clean();
	coreDevice.clean();

	glfwDestroyWindow(window);
	glfwTerminate();
}

// Helper functions (helpful really)
GLFWwindow* Renderer::getWindow() {
	return window;
}

bool Renderer::shouldClose() {
	return glfwWindowShouldClose(window);
}
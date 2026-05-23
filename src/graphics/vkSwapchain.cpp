#include "vkSwapchain.h"

void vkSwapchain::init(vkDevice& coreDevice) {
	vkb::SwapchainBuilder swapchainBuilder{ coreDevice.vkb_device };
	vkb_swapchain = swapchainBuilder
		.set_image_usage_flags(VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT)
		.build().value();
	swapchain = vkb_swapchain.swapchain;
	swapchainImages = vkb_swapchain.get_images().value();
}

void vkSwapchain::clean() {
	vkb::destroy_swapchain(vkb_swapchain);
}
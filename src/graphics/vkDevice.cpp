#include "vkDevice.h"

void vkDevice::init(GLFWwindow* window) {
	vkb::InstanceBuilder builder;
	vkb_inst = builder.set_app_name("Crystal").request_validation_layers(true).use_default_debug_messenger().build().value();
	instance = vkb_inst.instance;

	glfwCreateWindowSurface(instance, window, nullptr, &surface);

	vkb::PhysicalDeviceSelector selector{ vkb_inst };
	vkb::PhysicalDevice physicalDevice = selector.set_surface(surface).set_minimum_version(1, 1).select().value();

	vkb::DeviceBuilder deviceBuilder{ physicalDevice };
	vkb_device = deviceBuilder.build().value();
	device = vkb_device.device;

	graphicsQueue = vkb_device.get_queue(vkb::QueueType::graphics).value();
	graphicsQueueFamily = vkb_device.get_queue_index(vkb::QueueType::graphics).value();
}

void vkDevice::clean() {
	vkb::destroy_device(vkb_device);
	vkDestroySurfaceKHR(instance, surface, nullptr);
	vkb::destroy_instance(vkb_inst);
}
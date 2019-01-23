#ifndef VULKANLOADER_H
#define VULKANLOADER_H


#include "VulkanLogicalDevice.h"

#ifndef NDEBUG
const bool DebugMode = true;
#else
const bool DebugMode = false;
#endif

namespace vkr
{
	

	struct VulkanLoaderCreateInfo
	{
		windowExtent size;
		const char* appName = "Vulkan Test";
		const char* engineName = "No Engine";
		version3i appVersion = { 1,0,0 };
		version3i engineVersion = { 1,0,0 };
		std::vector<const char*> requestedInstanceExtensions = {};
		std::vector<const char*> requestedLayers = {};
		VkPhysicalDevice compelledDevice = VK_NULL_HANDLE;
		std::vector<const char*> requestedDeviceExtensions = {};
	};

	struct VulkanState
	{
		pSmartVulkanWindow window;
		pSmartVkInstance instance;
		pSmartVkDebugMsger debugMsger;
		pSmartVkSurfaceKHR surface;
		pSmartVkPhysicalDevice physicalDevice;
		pSmartVkDevice logicalDevice;
	};

	

	class VulkanLoader
	{
	public:
		VulkanLoader();
		~VulkanLoader();
		VulkanState initialize(VulkanLoaderCreateInfo& createInfo);
	private:
		
	};
}
#endif
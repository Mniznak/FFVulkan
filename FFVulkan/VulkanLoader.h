#ifndef VULKANLOADER_H
#define VULKANLOADER_H

#include "VulkanSurface.h"

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
	};

	struct VulkanPlug
	{
		pSmartVkSurfaceKHR surface;
	};

	

	class VulkanLoader
	{
	public:
		VulkanLoader();
		~VulkanLoader();
		VulkanPlug initialize(VulkanLoaderCreateInfo& createInfo);
	private:
		
	};
}
#endif
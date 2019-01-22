#ifndef VULKANCOMMON_H
#define VULKANCOMMON_H


#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

namespace vkr
{
	using VulkanAllocator = VkAllocationCallbacks * ;

	struct version3i
	{
		int major, minor, patch;
	};
}

#endif


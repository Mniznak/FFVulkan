#ifndef VULKANCOMMANDPOOL_H
#define VULKANCOMMANDPOOL_H

#include "VulkanLogicalDevice.h"

namespace vkr
{
	struct smartVkCommandPool
	{
		smartVkCommandPool(VkDevice _logicalDevice, VulkanAllocator _pAllocator = nullptr, VkCommandPool _pHandle = nullptr);
		~smartVkCommandPool();
		VkCommandPool pHandle = nullptr;
		VulkanAllocator pAllocator = nullptr;
		VkDevice logicalDevice = nullptr;
	};
	using pSmartVkCommandPool = std::unique_ptr<smartVkCommandPool>;

	struct VulkanCommandPoolCreateInfo
	{
		const smartVkDevice* logicalDevice = nullptr;
		VulkanAllocator CommandPoolAllocator = nullptr;
		uint32_t QueueFamily;
	};

	class VulkanCommandPool
	{
	public:
		VulkanCommandPool();
		~VulkanCommandPool();
		pSmartVkCommandPool generateCommandPool(VulkanCommandPoolCreateInfo& createInfo);
	};
}
#endif
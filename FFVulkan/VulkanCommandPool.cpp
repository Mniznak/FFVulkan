#include "VulkanCommandPool.h"


namespace vkr
{
	smartVkCommandPool::smartVkCommandPool(VkDevice _logicalDevice, VulkanAllocator _pAllocator, VkCommandPool _pHandle) :
		logicalDevice(_logicalDevice), pAllocator(_pAllocator), pHandle(_pHandle)
	{
	}
	smartVkCommandPool::~smartVkCommandPool()
	{
		if (logicalDevice && pHandle)
			vkDestroyCommandPool(logicalDevice, pHandle, pAllocator);
	}


	VulkanCommandPool::VulkanCommandPool()
	{
	}


	VulkanCommandPool::~VulkanCommandPool()
	{
	}

	pSmartVkCommandPool VulkanCommandPool::generateCommandPool(VulkanCommandPoolCreateInfo & createInfo)
	{
		VkCommandPool state;

		VkCommandPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = createInfo.QueueFamily;

		TEST(vkCreateCommandPool(createInfo.logicalDevice->pHandle, &poolInfo, createInfo.CommandPoolAllocator, &state));

		return std::make_unique<smartVkCommandPool>(createInfo.logicalDevice->pHandle, createInfo.CommandPoolAllocator, state);
	}
	
}
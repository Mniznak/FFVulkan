#ifndef VULKANLOGICALDEVICE_H
#define VULKANLOGICALDEVICE_H

#include "VulkanPhysicalDevice.h"
#include <set>

namespace vkr
{
	struct DeviceQueues
	{
		VkQueue pGraphicsQueue = nullptr;
		VkQueue pPresentQueue = nullptr;
		VkQueue pComputeQueue = nullptr;
		VkQueue pTransferQueue = nullptr;
		bool dedicatedGraphicsQueue() const;
		bool dedicatedPresentQueue() const;
		bool dedicatedComputeQueue() const;
		bool dedicatedTransferQueue() const;
	};

	struct smartVkDevice
	{
		smartVkDevice(VulkanAllocator _pAllocator = nullptr, VkDevice _pHandle = nullptr, DeviceQueues _deviceQueues = {});
		~smartVkDevice();
		VkDevice pHandle = nullptr;
		VulkanAllocator pAllocator = nullptr;
		DeviceQueues deviceQueues = {};
	};
	using pSmartVkDevice = std::unique_ptr<smartVkDevice>;

	struct VulkanLogicalDeviceCreateInfo
	{
		const smartVkPhysicalDevice* physicalDevice = nullptr;
		const std::vector<const char*>* validationLayers = nullptr;
		std::vector<const char*>* deviceExtensions = nullptr;
		VulkanAllocator logicalDeviceAllocator = nullptr;
		bool ValidationEnabled = false;
	};

	class VulkanLogicalDevice
	{
	public:
		VulkanLogicalDevice();
		~VulkanLogicalDevice();
		pSmartVkDevice generateLogicalDevice(VulkanLogicalDeviceCreateInfo& createInfo);
	};
}
#endif
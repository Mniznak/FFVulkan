#include "VulkanLogicalDevice.h"


namespace vkr
{
	bool DeviceQueues::dedicatedGraphicsQueue() const
	{
		std::set<VkQueue> x = { pPresentQueue, pComputeQueue, pTransferQueue };
		auto n = x.size();
		if (pGraphicsQueue)
			x.insert(pGraphicsQueue);
		return n < x.size();
	}

	bool DeviceQueues::dedicatedPresentQueue() const
	{
		std::set<VkQueue> x = { pGraphicsQueue, pComputeQueue, pTransferQueue };
		auto n = x.size();
		if (pPresentQueue)
			x.insert(pPresentQueue);
		return n < x.size();
	}

	bool DeviceQueues::dedicatedComputeQueue() const
	{
		std::set<VkQueue> x = { pPresentQueue, pGraphicsQueue, pTransferQueue };
		auto n = x.size();
		if (pComputeQueue)
			x.insert(pComputeQueue);
		return n < x.size();
	}

	bool DeviceQueues::dedicatedTransferQueue() const
	{
		std::set<VkQueue> x = { pPresentQueue, pComputeQueue, pGraphicsQueue };
		auto n = x.size();
		if (pTransferQueue)
			x.insert(pTransferQueue);
		return n < x.size();
	}

	smartVkDevice::smartVkDevice(VulkanAllocator _pAllocator, VkDevice _pHandle, DeviceQueues _deviceQueues) : pAllocator(_pAllocator), pHandle(_pHandle), deviceQueues(_deviceQueues)
	{
	}
	smartVkDevice::~smartVkDevice()
	{
		if (pHandle)
			vkDestroyDevice(pHandle, pAllocator);
	}

	VulkanLogicalDevice::VulkanLogicalDevice()
	{
	}


	VulkanLogicalDevice::~VulkanLogicalDevice()
	{
	}

	pSmartVkDevice VulkanLogicalDevice::generateLogicalDevice(VulkanLogicalDeviceCreateInfo & createInfo)
	{
		VkDevice logicalDevice;
		//pSmartVkDevice logicalDevice = std::make_unique<smartVkDevice>(createInfo.logicalDeviceAllocator, nullptr);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies;
		if (createInfo.physicalDevice->QFI.graphicsFamily.has_value())
			uniqueQueueFamilies.insert(createInfo.physicalDevice->QFI.graphicsFamily.value());
		if (createInfo.physicalDevice->QFI.presentFamily.has_value())
			uniqueQueueFamilies.insert(createInfo.physicalDevice->QFI.presentFamily.value());
		if (createInfo.physicalDevice->QFI.transferFamily.has_value())
			uniqueQueueFamilies.insert(createInfo.physicalDevice->QFI.transferFamily.value());
		if (createInfo.physicalDevice->QFI.computeFamily.has_value())
			uniqueQueueFamilies.insert(createInfo.physicalDevice->QFI.computeFamily.value());

		float queuePriority = 1.0f;

		for (auto queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures = {};

		VkDeviceCreateInfo cInfo = {};
		cInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		cInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		cInfo.pQueueCreateInfos = queueCreateInfos.data();

		cInfo.pEnabledFeatures = &deviceFeatures;

		cInfo.enabledExtensionCount = static_cast<uint32_t>(createInfo.deviceExtensions->size());
		cInfo.ppEnabledExtensionNames = createInfo.deviceExtensions->data();

		if (createInfo.ValidationEnabled)
		{
			cInfo.enabledLayerCount = static_cast<uint32_t>(createInfo.validationLayers->size());
			cInfo.ppEnabledLayerNames = createInfo.validationLayers->data();
		}
		else
			cInfo.enabledLayerCount = 0;

		TEST(vkCreateDevice(createInfo.physicalDevice->pHandle, &cInfo, createInfo.logicalDeviceAllocator, &logicalDevice));

		DeviceQueues deviceQueues;
		vkGetDeviceQueue(logicalDevice, createInfo.physicalDevice->QFI.graphicsFamily.value(), 0, &deviceQueues.pGraphicsQueue);
		vkGetDeviceQueue(logicalDevice, createInfo.physicalDevice->QFI.presentFamily.value(), 0, &deviceQueues.pPresentQueue);
		vkGetDeviceQueue(logicalDevice, createInfo.physicalDevice->QFI.transferFamily.value(), 0, &deviceQueues.pTransferQueue);
		vkGetDeviceQueue(logicalDevice, createInfo.physicalDevice->QFI.computeFamily.value(), 0, &deviceQueues.pComputeQueue);

		return std::make_unique<smartVkDevice>(createInfo.logicalDeviceAllocator, logicalDevice, deviceQueues);
	}

	

}
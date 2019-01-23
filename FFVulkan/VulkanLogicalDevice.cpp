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

	smartVkDevice::smartVkDevice(VkDevice _pHandle, VulkanAllocator _pAllocator)
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
		pSmartVkDevice state = std::make_unique<smartVkDevice>();

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies;
		if (createInfo.PhysicalDevice->QFI.graphicsFamily.has_value())
			uniqueQueueFamilies.insert(createInfo.PhysicalDevice->QFI.graphicsFamily.value());
		if (createInfo.PhysicalDevice->QFI.presentFamily.has_value())
			uniqueQueueFamilies.insert(createInfo.PhysicalDevice->QFI.presentFamily.value());
		if (createInfo.PhysicalDevice->QFI.transferFamily.has_value())
			uniqueQueueFamilies.insert(createInfo.PhysicalDevice->QFI.transferFamily.value());
		if (createInfo.PhysicalDevice->QFI.computeFamily.has_value())
			uniqueQueueFamilies.insert(createInfo.PhysicalDevice->QFI.computeFamily.value());

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

		TEST(vkCreateDevice(createInfo.PhysicalDevice->pHandle, &cInfo, state->pAllocator, &state->pHandle));

		vkGetDeviceQueue(state->pHandle, createInfo.PhysicalDevice->QFI.graphicsFamily.value(), 0, &state->deviceQueues.pGraphicsQueue);
		vkGetDeviceQueue(state->pHandle, createInfo.PhysicalDevice->QFI.presentFamily.value(), 0, &state->deviceQueues.pPresentQueue);
		vkGetDeviceQueue(state->pHandle, createInfo.PhysicalDevice->QFI.transferFamily.value(), 0, &state->deviceQueues.pTransferQueue);
		vkGetDeviceQueue(state->pHandle, createInfo.PhysicalDevice->QFI.computeFamily.value(), 0, &state->deviceQueues.pComputeQueue);

		return std::move(state);
	}

	

}
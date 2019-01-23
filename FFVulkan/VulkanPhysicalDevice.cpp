#include "VulkanPhysicalDevice.h"


namespace vkr
{
	bool QueueFamilyIndices::isComplete() const
	{
		return graphicsFamily.has_value() && presentFamily.has_value() && transferFamily.has_value();
	}

	smartVkPhysicalDevice::smartVkPhysicalDevice(VkPhysicalDevice _pHandle)
	{
	}

	smartVkPhysicalDevice::~smartVkPhysicalDevice()
	{
	}

	VulkanPhysicalDevice::VulkanPhysicalDevice()
	{
	}

	VulkanPhysicalDevice::~VulkanPhysicalDevice()
	{
	}

	pSmartVkPhysicalDevice VulkanPhysicalDevice::generatePhysicalDevice(VulkanPhysicalDeviceCreateInfo & createInfo)
	{
		pSmartVkPhysicalDevice state = std::make_unique<smartVkPhysicalDevice>();

		uint32_t dCount = 0;
		vkEnumeratePhysicalDevices(createInfo.pInstance->pHandle, &dCount, nullptr);
		std::vector<VkPhysicalDevice> devices(dCount);
		vkEnumeratePhysicalDevices(createInfo.pInstance->pHandle, &dCount, devices.data());

		if (createInfo.compelledDevice != VK_NULL_HANDLE)
		{
			if (isDeviceSuitable(createInfo.compelledDevice, createInfo))
			{
				buildDeviceSignature(state, createInfo);
				//state->pHandle = createInfo.compelledDevice;
				//state->SCSD = querySwapChainSupport(createInfo.compelledDevice, createInfo.pSurface->pHandle);
				//state->QFI = findQueueFamilies(createInfo.compelledDevice, createInfo.pSurface->pHandle);
			}
			else
				for (const auto& device : devices)
				{
					if (isDeviceSuitable(device, createInfo))
					{
						buildDeviceSignature(state, createInfo);
						//state->pHandle = device;
						//state->SCSD = querySwapChainSupport(device, createInfo.pSurface->pHandle);
						//state->QFI = findQueueFamilies(device, createInfo.pSurface->pHandle);
						break;
					}
				}
		}
		TEST(state->pHandle != VK_NULL_HANDLE);

		return std::move(state);
	}

	bool VulkanPhysicalDevice::isDeviceSuitable(VkPhysicalDevice device, VulkanPhysicalDeviceCreateInfo & createInfo)
	{
		QueueFamilyIndices indices = findQueueFamilies(device, createInfo.pSurface->pHandle);

		bool extensionsSupported = checkDeviceExtensionSupport(device, createInfo);
		bool swapChainAdequate = false;

		if (extensionsSupported)
		{
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, createInfo.pSurface->pHandle);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		return indices.isComplete() && extensionsSupported && swapChainAdequate;
	}

	void VulkanPhysicalDevice::buildDeviceSignature(pSmartVkPhysicalDevice& pPhysicalDevice, VulkanPhysicalDeviceCreateInfo & createInfo)
	{
		pPhysicalDevice->pHandle = createInfo.compelledDevice;
		pPhysicalDevice->SCSD = querySwapChainSupport(createInfo.compelledDevice, createInfo.pSurface->pHandle);
		pPhysicalDevice->QFI = findQueueFamilies(createInfo.compelledDevice, createInfo.pSurface->pHandle);
	}

	bool VulkanPhysicalDevice::checkDeviceExtensionSupport(VkPhysicalDevice device, VulkanPhysicalDeviceCreateInfo& createInfo)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(createInfo.deviceExtensions->begin(), createInfo.deviceExtensions->end());

		for (const auto& extension : availableExtensions)
			requiredExtensions.erase(extension.extensionName);

		return requiredExtensions.empty();
	}

	SwapChainSupportDetails VulkanPhysicalDevice::querySwapChainSupport(VkPhysicalDevice device, const VkSurfaceKHR & surface)
	{
		SwapChainSupportDetails details;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

		if (formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	QueueFamilyIndices VulkanPhysicalDevice::findQueueFamilies(VkPhysicalDevice device, const VkSurfaceKHR & surface)
	{
		QueueFamilyIndices indices;

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{

			if (queueFamily.queueCount > 0 &&
				!indices.graphicsFamily.has_value() &&
				queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = i;
			}

			if (queueFamily.queueCount > 0 &&
				!indices.transferFamily.has_value() &&
				queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
			{
				indices.transferFamily = i;
			}

			if (queueFamily.queueCount > 0 &&
				!indices.computeFamily.has_value() &&
				queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
			{
				indices.computeFamily = i;
			}

			if (queueFamily.queueCount > 0 &&
				!(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
				queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
			{
				indices.transferFamily = i;
			}

			if (queueFamily.queueCount > 0 &&
				!(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
				queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
			{
				indices.computeFamily = i;
			}

			if (queueFamily.queueCount > 0 &&
				!(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
				!(queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) &&
				queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
			{
				indices.transferFamily = i;
			}

			if (queueFamily.queueCount > 0 &&
				!(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
				!(queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) &&
				queueFamily.queueFlags == VK_QUEUE_COMPUTE_BIT)
			{
				indices.computeFamily = i;
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

			if (queueFamily.queueCount > 0 && presentSupport && !indices.presentFamily.has_value())
				indices.presentFamily = i;

			i++;
		}
		return indices;
	}

	

}
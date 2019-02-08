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
		smartVkPhysicalDevice state;

		uint32_t dCount = 0;
		vkEnumeratePhysicalDevices(createInfo.pInstance, &dCount, nullptr);
		std::vector<VkPhysicalDevice> devices(dCount);
		vkEnumeratePhysicalDevices(createInfo.pInstance, &dCount, devices.data());

		std::cout << "\nPhysical Device Count: " << dCount << '\n';
		

		if (createInfo.compelledDevice != VK_NULL_HANDLE)
		{
			auto deviceOptional = isDeviceSuitable(createInfo.compelledDevice, createInfo);
			if (deviceOptional.has_value())
				state = deviceOptional.value();
		}

		if (state.pHandle == VK_NULL_HANDLE)
			for (const auto& device : devices)
			{
				auto deviceOptional = isDeviceSuitable(device, createInfo);
				if (deviceOptional.has_value())
				{
					state = deviceOptional.value();
					break;
				}
			}
		
		TEST(state.pHandle != VK_NULL_HANDLE);

		return std::make_unique<smartVkPhysicalDevice>(state);
	}

	std::optional<smartVkPhysicalDevice> VulkanPhysicalDevice::isDeviceSuitable(VkPhysicalDevice device, VulkanPhysicalDeviceCreateInfo & createInfo)
	{
		smartVkPhysicalDevice physicalDevice;

		QueueFamilyIndices indices = findQueueFamilies(device, createInfo.pSurface);

		bool extensionsSupported = checkDeviceExtensionSupport(device, createInfo);
		bool swapChainAdequate = false;

		SwapChainSupportDetails swapChainSupport;

		if (extensionsSupported)
		{
			swapChainSupport = querySwapChainSupport(device, createInfo.pSurface);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		if (indices.isComplete() && extensionsSupported && swapChainAdequate)
		{
			physicalDevice.pHandle = device;
			physicalDevice.SCSD = swapChainSupport;
			physicalDevice.QFI = indices;
			return physicalDevice;
		}
		else
			return std::nullopt;

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

		indices.QueueCount.reserve(queueFamilyCount);
		indices.QueueFlags.reserve(queueFamilyCount);

		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			indices.QueueCount.push_back(queueFamilies[i].queueCount);
			indices.QueueFlags.push_back(queueFamilies[i].queueFlags);

			if (queueFamily.queueCount > 0 &&
				!indices.graphicsFamily.has_value() &&
				queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				setIndices(indices.graphicsFamily, indices.graphicsFamilyQueueCount, i, queueFamily);
			}

			if (queueFamily.queueCount > 0 &&
				!indices.transferFamily.has_value() &&
				queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
			{
				setIndices(indices.transferFamily, indices.transferFamilyQueueCount, i, queueFamily);
			}

			if (queueFamily.queueCount > 0 &&
				!indices.computeFamily.has_value() &&
				queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
			{
				setIndices(indices.computeFamily, indices.computeFamilyQueueCount, i, queueFamily);
			}

			if (queueFamily.queueCount > 0 &&
				!(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
				queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
			{
				setIndices(indices.transferFamily, indices.transferFamilyQueueCount, i, queueFamily);
			}

			if (queueFamily.queueCount > 0 &&
				!(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
				queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
			{
				setIndices(indices.computeFamily, indices.computeFamilyQueueCount, i, queueFamily);
			}

			if (queueFamily.queueCount > 0 &&
				!(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
				!(queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) &&
				queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
			{
				setIndices(indices.transferFamily, indices.transferFamilyQueueCount, i, queueFamily);
			}

			if (queueFamily.queueCount > 0 &&
				!(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
				!(queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) &&
				queueFamily.queueFlags == VK_QUEUE_COMPUTE_BIT)
			{
				setIndices(indices.computeFamily, indices.computeFamilyQueueCount, i, queueFamily);
			}

			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
			if (presentSupport)
				std::cout << "Present Support on Qfamily: " << i << '\n';

			if (queueFamily.queueCount > 0 && presentSupport && !indices.presentFamily.has_value())
				setIndices(indices.presentFamily, indices.presentFamilyQueueCount, i, queueFamily);

			i++;
		}

		std::cout << "\n1: Graphics Bit\n2: Compute Bit\n4: Transfer Bit\n8: Sparse Binding Bit\n\n";

		std::cout << "\nNumber of Queue Families: " << queueFamilies.size() << '\n';
		for (int i = 0; i < queueFamilies.size(); i++)
		{
			std::cout << "Queue Family: " << i << " :: Queues: " << indices.QueueCount[i] << " :: Flags: " << indices.QueueFlags[i] << '\n';
		}
		std::cout << '\n';

		std::cout << "Graphics Family: " << indices.graphicsFamily.value() << " :: Queues: " << indices.graphicsFamilyQueueCount << '\n';
		std::cout << "Presentation Family: " << indices.presentFamily.value() << " :: Queues: " << indices.presentFamilyQueueCount << '\n';
		std::cout << "Transfer Family: " << indices.transferFamily.value() << " :: Queues: " << indices.transferFamilyQueueCount << '\n';
		std::cout << "Compute Family: " << indices.computeFamily.value() << " :: Queues: " << indices.computeFamilyQueueCount << '\n';



		return indices;
	}

	void VulkanPhysicalDevice::setIndices(std::optional<uint32_t> & QFI, uint32_t& QueueCount, const uint32_t QueueFamilyIndex, const VkQueueFamilyProperties & QueueFamilyProperties)
	{
		QFI = QueueFamilyIndex;
		QueueCount = QueueFamilyProperties.queueCount;
	}

	

}
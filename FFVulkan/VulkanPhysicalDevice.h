#ifndef VULKANPHYSICALDEVICE_H
#define VULKANPHYSICALDEVICE_H

#include "VulkanSurface.h"
#include <optional>
#include <set>

namespace vkr
{
	struct QueueFamilyIndices
	{
		std::vector<uint32_t> QueueCount;
		std::vector<VkQueueFlags> QueueFlags;

		std::optional<uint32_t> graphicsFamily = std::nullopt;
		std::optional<uint32_t> presentFamily = std::nullopt;
		std::optional<uint32_t> computeFamily = std::nullopt;
		std::optional<uint32_t> transferFamily = std::nullopt;

		uint32_t graphicsFamilyQueueCount = 0;
		uint32_t presentFamilyQueueCount = 0;
		uint32_t computeFamilyQueueCount = 0;
		uint32_t transferFamilyQueueCount = 0;

		bool isComplete() const;
	};

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities = {};
		std::vector<VkSurfaceFormatKHR> formats = {};
		std::vector<VkPresentModeKHR> presentModes = {};
	};

	struct VulkanPhysicalDeviceCreateInfo
	{
		VkPhysicalDevice compelledDevice = VK_NULL_HANDLE;
		VkInstance pInstance = nullptr;
		VkSurfaceKHR pSurface = nullptr;
		std::vector<const char*>* deviceExtensions = {};
	};

	struct smartVkPhysicalDevice
	{
		smartVkPhysicalDevice(VkPhysicalDevice _pHandle = VK_NULL_HANDLE);
		~smartVkPhysicalDevice();
		VkPhysicalDevice pHandle = VK_NULL_HANDLE;
		SwapChainSupportDetails SCSD = {};
		QueueFamilyIndices QFI = {};
	};
	using pSmartVkPhysicalDevice = std::unique_ptr<smartVkPhysicalDevice>;

	class VulkanPhysicalDevice
	{
	public:
		VulkanPhysicalDevice();
		~VulkanPhysicalDevice();
		pSmartVkPhysicalDevice generatePhysicalDevice(VulkanPhysicalDeviceCreateInfo& createInfo);
	private:
		std::optional<smartVkPhysicalDevice> isDeviceSuitable(VkPhysicalDevice device, VulkanPhysicalDeviceCreateInfo & createInfo);
		void buildDeviceSignature(smartVkPhysicalDevice& pPhysicalDevice, const VkPhysicalDevice& device, const VkSurfaceKHR& surface);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device, VulkanPhysicalDeviceCreateInfo& createInfo);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, const VkSurfaceKHR & surface);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, const VkSurfaceKHR & surface);
		void setIndices(std::optional<uint32_t> & QFI, uint32_t& QueueCount, const uint32_t QueueFamilyIndex, const VkQueueFamilyProperties & QueueFamilyProperties);
	};
}
#endif
#ifndef VULKANPHYSICALDEVICE_H
#define VULKANPHYSICALDEVICE_H

#include "VulkanSurface.h"
#include <optional>
#include <set>

namespace vkr
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> graphicsFamily = std::nullopt;
		std::optional<uint32_t> presentFamily = std::nullopt;
		std::optional<uint32_t> computeFamily = std::nullopt;
		std::optional<uint32_t> transferFamily = std::nullopt;

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
		const smartVkInstance* pInstance = nullptr;
		const smartVkSurfaceKHR* pSurface = nullptr;
		std::vector<const char*>* deviceExtensions = {};
	};

	struct smartVkPhysicalDevice
	{
		smartVkPhysicalDevice(VkPhysicalDevice _pHandle = VK_NULL_HANDLE);
		~smartVkPhysicalDevice();
		VkPhysicalDevice pHandle = VK_NULL_HANDLE;
		SwapChainSupportDetails SCSD = {};
		QueueFamilyIndices QFI = {};
		//std::vector<const char*> deviceExtensions = {};
	};
	using pSmartVkPhysicalDevice = std::unique_ptr<smartVkPhysicalDevice>;

	class VulkanPhysicalDevice
	{
	public:
		VulkanPhysicalDevice();
		~VulkanPhysicalDevice();
		pSmartVkPhysicalDevice generatePhysicalDevice(VulkanPhysicalDeviceCreateInfo& createInfo);
	private:
		bool isDeviceSuitable(VkPhysicalDevice device, VulkanPhysicalDeviceCreateInfo & createInfo);
		void buildDeviceSignature(pSmartVkPhysicalDevice& pPhysicalDevice, const VkPhysicalDevice& device, const VkSurfaceKHR& surface);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device, VulkanPhysicalDeviceCreateInfo& createInfo);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, const VkSurfaceKHR & surface);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, const VkSurfaceKHR & surface);
	};
}
#endif
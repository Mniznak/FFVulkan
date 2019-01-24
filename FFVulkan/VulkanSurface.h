#ifndef VULKANSURFACE_H
#define VULKANSURFACE_H

#include "VulkanInstance.h"
#include "VulkanWindow.h"

namespace vkr
{
	struct smartVkSurfaceKHR
	{
		smartVkSurfaceKHR(const VkInstance _pInstance, VulkanAllocator _pAllocator = nullptr, VkSurfaceKHR _pHandle = nullptr);
		~smartVkSurfaceKHR();
		VkSurfaceKHR pHandle = nullptr;
		VulkanAllocator pAllocator = nullptr;
		const VkInstance pInstance = nullptr;
	};
	using pSmartVkSurfaceKHR = std::unique_ptr<smartVkSurfaceKHR>;

	struct VulkanSurfaceCreateInfo
	{
		const smartVkInstance* pInstance = nullptr;
		const smartVulkanWindow* pWindow = nullptr;
		VulkanAllocator SurfaceAllocator = nullptr;
	};

	class VulkanSurface
	{
	public:
		VulkanSurface();
		~VulkanSurface();
		pSmartVkSurfaceKHR generateSurface(VulkanSurfaceCreateInfo& createInfo);
	};
}
#endif
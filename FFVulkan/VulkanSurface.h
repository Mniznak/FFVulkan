#ifndef VULKANSURFACE_H
#define VULKANSURFACE_H

#include "VulkanInstance.h"
#include "VulkanWindow.h"

namespace vkr
{
	struct smartVkSurfaceKHR
	{
		smartVkSurfaceKHR(const smartVkInstance* _pInstance, VkSurfaceKHR _pHandle = nullptr, VulkanAllocator _pAllocator = nullptr);
		~smartVkSurfaceKHR();
		VkSurfaceKHR pHandle = nullptr;
		VulkanAllocator pAllocator = nullptr;
		const smartVkInstance* pInstance = nullptr;
	};
	using pSmartVkSurfaceKHR = std::unique_ptr<smartVkSurfaceKHR>;

	struct VulkanSurfaceCreateInfo
	{
		pSmartVkSurfaceKHR Surface;
		const smartVkInstance* pInstance;
		const smartVulkanWindow* pWindow;
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
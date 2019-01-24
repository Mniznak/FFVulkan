#include "VulkanSurface.h"


namespace vkr
{

	smartVkSurfaceKHR::smartVkSurfaceKHR(const VkInstance _pInstance, VulkanAllocator _pAllocator, VkSurfaceKHR _pHandle) :
		pInstance(_pInstance), pAllocator(_pAllocator), pHandle(_pHandle)
	{
	}
	smartVkSurfaceKHR::~smartVkSurfaceKHR()
	{
		if (pHandle && pInstance)
			vkDestroySurfaceKHR(pInstance, pHandle, pAllocator);
	}

	VulkanSurface::VulkanSurface()
	{
	}


	VulkanSurface::~VulkanSurface()
	{
	}

	pSmartVkSurfaceKHR VulkanSurface::generateSurface(VulkanSurfaceCreateInfo& createInfo)
	{
		VkSurfaceKHR surface;

		TEST(glfwCreateWindowSurface(createInfo.pInstance->pHandle, createInfo.pWindow->pHandle, createInfo.SurfaceAllocator, &surface));

		return std::make_unique<smartVkSurfaceKHR>(createInfo.pInstance->pHandle, createInfo.SurfaceAllocator, surface);
	}
	
}
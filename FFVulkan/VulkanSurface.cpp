#include "VulkanSurface.h"


namespace vkr
{

	smartVkSurfaceKHR::smartVkSurfaceKHR(const smartVkInstance * _pInstance, VkSurfaceKHR _pHandle, VulkanAllocator _pAllocator) :
		pInstance(_pInstance), pHandle(_pHandle), pAllocator(_pAllocator)
	{
	}
	smartVkSurfaceKHR::~smartVkSurfaceKHR()
	{
		if (pHandle && pInstance)
			vkDestroySurfaceKHR(pInstance->pHandle, pHandle, pAllocator);
	}

	VulkanSurface::VulkanSurface()
	{
	}


	VulkanSurface::~VulkanSurface()
	{
	}

	pSmartVkSurfaceKHR VulkanSurface::generateSurface(VulkanSurfaceCreateInfo& createInfo)
	{
		pSmartVkSurfaceKHR state = std::make_unique<smartVkSurfaceKHR>(createInfo.pInstance, nullptr, nullptr);

		TEST(glfwCreateWindowSurface(state->pInstance->pHandle, createInfo.pWindow->pHandle, state->pAllocator, &state->pHandle));

		return state;
	}
	
}
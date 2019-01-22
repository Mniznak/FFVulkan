#ifndef VULKANWINDOW_H
#define VULKANWINDOW_H

#include "VulkanUtilities.h"

namespace vkr
{
	struct windowExtent
	{
		int width, height;
	};

	struct smartVulkanWindow
	{
		smartVulkanWindow(GLFWwindow* _pHandle, windowExtent _extent, const char* _name);
		~smartVulkanWindow();
		GLFWwindow* pHandle = nullptr;
		windowExtent extent = { 0, 0 };
		const char* name = "Vulkan";
		bool frameBufferResize = false;
	private:
		static void framebufferResizeCallback(GLFWwindow*window, int width, int height);
	};
	using pSmartVulkanWindow = std::unique_ptr<smartVulkanWindow>;

	struct VulkanWindowCreateInfo
	{
		windowExtent extent = { 0, 0 };
		const char* name = "Vulkan";
	};

	class VulkanWindow
	{
	public:
		VulkanWindow();
		~VulkanWindow();
		pSmartVulkanWindow generateWindow(VulkanWindowCreateInfo& createInfo);
		std::vector<const char*> getRequiredInstanceExt();
	private:
		
	};
}
#endif
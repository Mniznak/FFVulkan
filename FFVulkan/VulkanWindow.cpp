#include "VulkanWindow.h"


namespace vkr
{

	smartVulkanWindow::smartVulkanWindow(GLFWwindow * _pHandle = {}, windowExtent _extent = {}, const char * _name = {}) : pHandle(_pHandle), extent(_extent), name(_name)
	{
		glfwSetWindowUserPointer(pHandle, this);
		glfwSetFramebufferSizeCallback(pHandle, framebufferResizeCallback);
	}

	smartVulkanWindow::~smartVulkanWindow()
	{
		if (pHandle)
			glfwDestroyWindow(pHandle);
	}

	void smartVulkanWindow::framebufferResizeCallback(GLFWwindow * window, int width, int height)
	{
		auto windowPtr = reinterpret_cast<smartVulkanWindow*>(glfwGetWindowUserPointer(window));
		windowPtr->frameBufferResize = true;
		windowPtr->extent = { width, height };
	}

	vkr::VulkanWindow::VulkanWindow()
	{
	}

	VulkanWindow::~VulkanWindow()
	{
	}

	pSmartVulkanWindow VulkanWindow::generateWindow(VulkanWindowCreateInfo & createInfo)
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		auto rawWindow = glfwCreateWindow(createInfo.extent.width, createInfo.extent.height, createInfo.name, nullptr, nullptr);
		TEST(rawWindow != nullptr);

		return std::make_unique<smartVulkanWindow>(rawWindow, createInfo.extent, createInfo.name);
	}

	std::vector<const char*> VulkanWindow::getRequiredInstanceExt()
	{
		uint32_t extensionCount = 0;
		const char** Extensions = glfwGetRequiredInstanceExtensions(&extensionCount);

		std::vector<const char*> retExtensions;
		retExtensions.reserve(extensionCount);
		retExtensions.insert(retExtensions.end(), Extensions, Extensions + extensionCount);

		return retExtensions;
	}

	
}
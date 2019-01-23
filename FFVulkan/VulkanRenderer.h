#ifndef VULKANRENDERER_H
#define VULKANRENDERER_H

#include "VulkanLoader.h"

namespace vkr
{
	struct VulkanRendererRequiredInfo
	{
		const char* appName = "Vulkan Test";
		version3i appVersion = { 1,0,0 };
		windowExtent windowSize = { 800, 600 };
	};

	struct VulkanRendererOptionalInfo
	{
		const char* engineName = "No Engine";
		version3i engineVersion = { 1,0,0 };
		std::vector<const char*> requestedInstanceExtensions = {};
		std::vector<const char*> requestedLayers = {};
		std::vector<const char*> requestedDeviceExtensions = {};
		VkPhysicalDevice requestedPhysicalDevice = VK_NULL_HANDLE;
		bool ValidationEnabled = false;
	};

	struct VulkanRendererCreateInfo
	{
		VulkanRendererRequiredInfo requiredInformation = {};
		VulkanRendererOptionalInfo optionalInformation = {};
	};

	class VulkanRenderer
	{
	public:
		VulkanRenderer(VulkanRendererCreateInfo& createInfo);
		VulkanRenderer(VulkanRenderer& moveState);
		VulkanRenderer(VulkanState& moveState);
		~VulkanRenderer();
		const VulkanState& getState() const;
	private:
		VulkanState state;
	};
}
#endif
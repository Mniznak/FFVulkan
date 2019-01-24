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

	struct VulkanRendererOptionalInstance
	{
		const char* engineName = "No Engine";
		version3i engineVersion = { 1,0,0 };
		std::vector<const char*> requestedInstanceExtensions = {};
		std::vector<const char*> requestedLayers = {};
		VulkanAllocator instanceAllocator = nullptr;
		VulkanAllocator debugAllocator = nullptr;
	};

	struct VulkanRendererOptionalSurface
	{
		VulkanAllocator logicalSurfaceAllocator = nullptr;
	};

	struct VulkanRendererOptionalDevice
	{
		std::vector<const char*> requestedDeviceExtensions = {};
		VkPhysicalDevice requestedPhysicalDevice = VK_NULL_HANDLE;
		VulkanAllocator logicalDeviceAllocator = nullptr;
	};

	struct VulkanRendererOptionalInfo
	{
		VulkanRendererOptionalInstance optionalInstanceInfo = {};
		VulkanRendererOptionalSurface optionalSurfaceInfo = {};
		VulkanRendererOptionalDevice optionalDeviceInfo = {};
		
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
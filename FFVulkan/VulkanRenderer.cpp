#include "VulkanRenderer.h"


namespace vkr
{



	VulkanRenderer::VulkanRenderer(VulkanRendererCreateInfo & createInfo)
	{
		VulkanLoader loader;

		VulkanLoaderCreateInfo lCreateInfo;
		lCreateInfo.appName = createInfo.requiredInformation.appName;
		lCreateInfo.appVersion = createInfo.requiredInformation.appVersion;
		lCreateInfo.size = createInfo.requiredInformation.windowSize;
		lCreateInfo.engineName = createInfo.optionalInformation.optionalInstanceInfo.engineName;
		lCreateInfo.engineVersion = createInfo.optionalInformation.optionalInstanceInfo.engineVersion;
		lCreateInfo.instanceAllocator = createInfo.optionalInformation.optionalInstanceInfo.instanceAllocator;
		lCreateInfo.debugAllocator = createInfo.optionalInformation.optionalInstanceInfo.debugAllocator;
		lCreateInfo.requestedInstanceExtensions = createInfo.optionalInformation.optionalInstanceInfo.requestedInstanceExtensions;
		lCreateInfo.requestedLayers = createInfo.optionalInformation.optionalInstanceInfo.requestedLayers;
		lCreateInfo.surfaceAllocator = createInfo.optionalInformation.optionalSurfaceInfo.logicalSurfaceAllocator;
		lCreateInfo.logicalDeviceAllocator = createInfo.optionalInformation.optionalDeviceInfo.logicalDeviceAllocator;
		lCreateInfo.requestedDeviceExtensions = createInfo.optionalInformation.optionalDeviceInfo.requestedDeviceExtensions;
		lCreateInfo.requestedPhysicalDevice = createInfo.optionalInformation.optionalDeviceInfo.requestedPhysicalDevice;
		lCreateInfo.ValidationEnabled = createInfo.optionalInformation.ValidationEnabled;

		state = loader.initialize(lCreateInfo);
	}

	VulkanRenderer::VulkanRenderer(VulkanRenderer & moveState)
	{
		state = std::move(moveState.state);
	}

	VulkanRenderer::VulkanRenderer(VulkanState & moveState)
	{
		state = std::move(moveState);
	}

	VulkanRenderer::~VulkanRenderer()
	{
	}

	const VulkanState & VulkanRenderer::getState() const
	{
		return state;
	}
}
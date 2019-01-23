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
		lCreateInfo.engineName = createInfo.optionalInformation.engineName;
		lCreateInfo.engineVersion = createInfo.optionalInformation.engineVersion;
		lCreateInfo.requestedDeviceExtensions = createInfo.optionalInformation.requestedDeviceExtensions;
		lCreateInfo.requestedInstanceExtensions = createInfo.optionalInformation.requestedInstanceExtensions;
		lCreateInfo.requestedLayers = createInfo.optionalInformation.requestedLayers;
		lCreateInfo.requestedPhysicalDevice = createInfo.optionalInformation.requestedPhysicalDevice;
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
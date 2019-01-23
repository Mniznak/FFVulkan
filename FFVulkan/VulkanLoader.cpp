#include "VulkanLoader.h"


namespace vkr
{
	VulkanLoader::VulkanLoader()
	{
	}


	VulkanLoader::~VulkanLoader()
	{
	}
	VulkanState VulkanLoader::initialize(VulkanLoaderCreateInfo & createInfo)
	{
		VulkanWindow windowFactory;

		VulkanWindowCreateInfo wCreateInfo;
		wCreateInfo.extent = createInfo.size;
		wCreateInfo.name = createInfo.appName;

		auto pWindow = windowFactory.generateWindow(wCreateInfo);
		auto requiredInstanceExt = windowFactory.getRequiredInstanceExt();

		VulkanInstance instanceFactory;

		std::vector<const char*> validationLayers = createInfo.requestedLayers;

		VulkanInstanceCreateInfo iCreateInfo;
		iCreateInfo.appInfo = instanceFactory.ApplicationInfo(createInfo.appName, createInfo.appVersion, createInfo.engineName, createInfo.engineVersion);
		iCreateInfo.instanceExtensions = &requiredInstanceExt;
		if (createInfo.requestedInstanceExtensions.size() > 0)
		{
			iCreateInfo.instanceExtensions->reserve(iCreateInfo.instanceExtensions->size() + createInfo.requestedInstanceExtensions.size());
			iCreateInfo.instanceExtensions->insert(iCreateInfo.instanceExtensions->end(), createInfo.requestedInstanceExtensions.begin(), createInfo.requestedInstanceExtensions.end());
		}
		iCreateInfo.validationLayers = &validationLayers;
		if (createInfo.ValidationEnabled)
		{
			iCreateInfo.validationEnabled = createInfo.ValidationEnabled;
			iCreateInfo.validationInfo = 
			{
				instanceFactory.debugInfo() 
			};
			iCreateInfo.validationLayers->emplace_back("VK_LAYER_LUNARG_standard_validation");
			iCreateInfo.instanceExtensions->emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		auto instancePair = instanceFactory.generateInstance(iCreateInfo);

		VulkanSurface surfaceFactory;

		VulkanSurfaceCreateInfo sCreateInfo;
		sCreateInfo.pInstance = instancePair.instance.get();
		sCreateInfo.pWindow = pWindow.get();

		auto pSurface = surfaceFactory.generateSurface(sCreateInfo);

		VulkanPhysicalDevice pDeviceFactory;

		VulkanPhysicalDeviceCreateInfo pdCreateInfo;
		pdCreateInfo.compelledDevice = createInfo.requestedPhysicalDevice;
		pdCreateInfo.pInstance = instancePair.instance.get();
		pdCreateInfo.pSurface = pSurface.get();
		pdCreateInfo.deviceExtensions = &createInfo.requestedDeviceExtensions;

		auto pPhysicalDevice = pDeviceFactory.generatePhysicalDevice(pdCreateInfo);

		VulkanLogicalDevice lDeviceFactory;

		VulkanLogicalDeviceCreateInfo ldCreateInfo;
		ldCreateInfo.ValidationEnabled = createInfo.ValidationEnabled;
		ldCreateInfo.PhysicalDevice = pPhysicalDevice.get();
		ldCreateInfo.deviceExtensions = &createInfo.requestedDeviceExtensions;
		ldCreateInfo.validationLayers = &validationLayers;

		auto pLogicalDevice = lDeviceFactory.generateLogicalDevice(ldCreateInfo);
		
		return { 
			std::move(pWindow), 
			std::move(instancePair.instance), 
			std::move(instancePair.debugMsger), 
			std::move(pSurface), 
			std::move(pPhysicalDevice), 
			std::move(pLogicalDevice) 
		}; 
	}
	
}
#include "VulkanLoader.h"


namespace vkr
{
	VulkanLoader::VulkanLoader()
	{
	}


	VulkanLoader::~VulkanLoader()
	{
	}
	VulkanPlug VulkanLoader::initialize(VulkanLoaderCreateInfo & createInfo)
	{
		VulkanWindow windowFactory;

		VulkanWindowCreateInfo wCreateInfo;
		wCreateInfo.extent = createInfo.size;
		wCreateInfo.name = createInfo.appName;

		auto pWindow = windowFactory.generateWindow(wCreateInfo);
		auto reqInstanceExt = windowFactory.getRequiredInstanceExt();

		VulkanInstance instanceFactory;

		VulkanInstanceCreateInfo iCreateInfo;
		iCreateInfo.appInfo = instanceFactory.ApplicationInfo(createInfo.appName, createInfo.appVersion, createInfo.engineName, createInfo.engineVersion);
		iCreateInfo.instanceExtensions = &reqInstanceExt;
		if (DebugMode)
		{
			iCreateInfo.validationEnabled;
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

		




		return VulkanPlug();
	}
	
}
#include "VulkanInstance.h"

namespace vkr
{
	smartVkInstance::smartVkInstance()
	{
	}

	smartVkInstance::smartVkInstance(VkInstance _pHandle, VulkanAllocator _pAllocator) : pHandle(_pHandle), pAllocator(_pAllocator)
	{
	}

	smartVkInstance::~smartVkInstance()
	{
		if (pHandle)
			vkDestroyInstance(pHandle, pAllocator);
	}

	smartVkDebugMsger::smartVkDebugMsger(const smartVkInstance * _pInstance) : pInstance(_pInstance)
	{
	}

	smartVkDebugMsger::smartVkDebugMsger(VkDebugUtilsMessengerEXT _pHandle, VulkanAllocator _pAllocator, const smartVkInstance * _pInstance) :
		pHandle(_pHandle), pAllocator(_pAllocator), pInstance(_pInstance)
	{
	}

	smartVkDebugMsger::~smartVkDebugMsger()
	{
		if (pHandle && pInstance)
		{
			auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(pInstance->pHandle, "vkDestroyDebugUtilsMessengerEXT");
			if (func != nullptr)
				func(pInstance->pHandle, pHandle, pAllocator);
		}
	}	

	VulkanInstance::VulkanInstance()
	{
	}

	VulkanInstance::~VulkanInstance()
	{
	}

	GeneratedInstance VulkanInstance::generateInstance(VulkanInstanceCreateInfo & createInfo)
	{
		pSmartVkInstance instance = std::make_unique<smartVkInstance>();
		pSmartVkDebugMsger debugMsger;

		VkInstanceCreateInfo instInfo = {};
		instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instInfo.pApplicationInfo = &createInfo.appInfo;
		instInfo.enabledLayerCount = static_cast<uint32_t>(createInfo.validationLayers->size());
		instInfo.ppEnabledLayerNames = createInfo.validationLayers->data();
		instInfo.enabledExtensionCount = static_cast<uint32_t>(createInfo.instanceExtensions->size());
		instInfo.ppEnabledExtensionNames = createInfo.instanceExtensions->data();

		TEST(vkCreateInstance(&instInfo, instance->pAllocator, &instance->pHandle));

		if (createInfo.validationEnabled)
		{
			debugMsger = std::make_unique<smartVkDebugMsger>(instance->pHandle);

			if (!createInfo.validationInfo.debugUtilCreateInfo.pfnUserCallback)
				createInfo.validationInfo.debugUtilCreateInfo.pfnUserCallback = debugCallback;

			TEST(CreateDebugUtilsMessengerEXT(instance->pHandle, &createInfo.validationInfo.debugUtilCreateInfo, debugMsger->pAllocator, &debugMsger->pHandle));
		}

		return { std::move(instance), std::move(debugMsger) };
	}

	VkApplicationInfo VulkanInstance::ApplicationInfo(const char* appName, version3i appVersion, const char* engineName, version3i engineVersion)
	{
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = appName;
		appInfo.applicationVersion = VK_MAKE_VERSION(appVersion.major, appVersion.minor, appVersion.patch);
		appInfo.pEngineName = engineName;
		appInfo.engineVersion = VK_MAKE_VERSION(engineVersion.major, engineVersion.minor, engineVersion.patch);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		return appInfo;
	}

	VkDebugUtilsMessengerCreateInfoEXT VulkanInstance::debugInfo(PFN_vkDebugUtilsMessengerCallbackEXT callback)
	{
		VkDebugUtilsMessengerCreateInfoEXT createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = callback;

		return createInfo;
	}

	VkResult VulkanInstance::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT * pCreateInfo, const VkAllocationCallbacks * pAllocator, VkDebugUtilsMessengerEXT * pCallback)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
		if (func != nullptr)
		{
			func(instance, pCreateInfo, pAllocator, pCallback);
			return VK_SUCCESS;
		}
		else
			return VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanInstance::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData, void * pUserData)
	{
		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl; //Can be replaced with logging function.

		return VK_FALSE;
	}


	

}



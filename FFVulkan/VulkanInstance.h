#ifndef VULKANINSTANCE_H
#define VULKANINSTANCE_H

#include "VulkanUtilities.h"
#include <memory>

namespace vkr
{

	struct smartVkInstance
	{
		smartVkInstance();
		smartVkInstance(VkInstance _pHandle, VulkanAllocator _pAllocator);
		~smartVkInstance();
		VkInstance pHandle = nullptr;
		VulkanAllocator pAllocator = nullptr;
	};
	using pSmartVkInstance = std::unique_ptr<smartVkInstance>;

	struct smartVkDebugMsger
	{
		smartVkDebugMsger(const smartVkInstance* _pInstance);
		smartVkDebugMsger(VkDebugUtilsMessengerEXT _pHandle, VulkanAllocator _pAllocator, const smartVkInstance* _pInstance);
		~smartVkDebugMsger();
		VkDebugUtilsMessengerEXT pHandle = nullptr;
		VulkanAllocator pAllocator = nullptr;
		const smartVkInstance* pInstance = nullptr;
	};
	using pSmartVkDebugMsger = std::unique_ptr<smartVkDebugMsger>;

	struct ValidationLayerCreateInfo
	{
		VkDebugUtilsMessengerCreateInfoEXT debugUtilCreateInfo = {};
	};

	struct VulkanInstanceCreateInfo
	{
		VkApplicationInfo appInfo = {};
		std::vector<const char *>* instanceExtensions;
		std::vector<const char *>* validationLayers;
		ValidationLayerCreateInfo validationInfo = {};
		bool validationEnabled = false;
	};

	struct GeneratedInstance
	{
		pSmartVkInstance instance = nullptr;
		pSmartVkDebugMsger debugMsger = nullptr;
	};

	class VulkanInstance
	{
	public:
		VulkanInstance();
		~VulkanInstance();
		GeneratedInstance generateInstance(VulkanInstanceCreateInfo& createInfo);
		VkApplicationInfo ApplicationInfo(const char* appName, version3i appVersion, const char* engineName, version3i engineVersion);
		VkDebugUtilsMessengerCreateInfoEXT debugInfo(PFN_vkDebugUtilsMessengerCallbackEXT callback = nullptr);
	private:
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator,
			VkDebugUtilsMessengerEXT* pCallback);
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
	};
}

#endif
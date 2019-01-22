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
		const smartVkInstance* pInstance = nullptr;
		VkDebugUtilsMessengerCreateInfoEXT debugUtilCreateInfo = {};
	};

	struct VulkanInstanceCreateInfo
	{
		VkApplicationInfo appInfo = {};
		std::vector<const char *>* instanceExtensions;
		std::vector<const char *>* validationLayers;
		ValidationLayerCreateInfo ValidationInfo = {};
		bool ValidationEnabled = false;
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
	private:
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator,
			VkDebugUtilsMessengerEXT* pCallback);
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
	};
}

#endif
#ifndef GLFWINTERFACE_H
#define GLFWINTERFACE_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#include <vector>

namespace vkr
{
	class GLFWinterface
	{
	public:
		GLFWinterface() = delete;
		~GLFWinterface() = delete;
		inline static void SetWindowUserPointer(GLFWwindow* _window, void* _pUserPointer)
		{
			glfwSetWindowUserPointer(_window, _pUserPointer);
		}


		inline static void GetWindowUserPointer(GLFWwindow* _window, void* _pUserPointer) 
		{
			_pUserPointer = glfwGetWindowUserPointer(_window);
		}


		inline static void SetFramebufferSizeCallback(GLFWwindow* _window, GLFWframebuffersizefun& _cbfun)
		{
			glfwSetFramebufferSizeCallback(_window, _cbfun);
		}


		inline static GLFWwindow* CreateWindow(int _width, int _height, const char* _title)
		{
			return glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
		}


		inline static std::vector<const char*> GetRequiredInstanceExtensions()
		{
			uint32_t extensionCount = 0;
			const char** Extensions = glfwGetRequiredInstanceExtensions(&extensionCount);

			std::vector<const char*> retExtensions;
			retExtensions.reserve(extensionCount);
			retExtensions.insert(retExtensions.end(), Extensions, Extensions + extensionCount);

			return retExtensions;
		}


	};
}
#endif
#ifndef VULKANUTILITIES_H
#define VULKANUTILITIES_H

#pragma warning(disable : 4805)

#include <fstream>
#include <iostream>
#include <vector>
#include "VulkanCommon.h"

#include <type_traits>



#define S(x) #x
#define S_(x) S(x)
#define S__LINE__ S_(__LINE__)

#ifndef NDEBUG	
#define BadResult(f) throw std::runtime_error("Test: " #f "\n\tat line: " S__LINE__ "\n\tin: " __FILE__ "\n");
#else																										
#define BadResult(f) std::cout << "Test: " <<  #f << "\n\tat: " << S__LINE__ << "\n\tin: " << __FILE__ << '\n';
#endif

#define TEST(f)																								\
{																											\
		decltype(auto) res = (f);																			\
		if (																								\
			(std::is_same<decltype(res), VkResult>::value && res != VK_SUCCESS) ||							\
			(std::is_same<decltype(res), bool>::value && res != true)										\
			)																								\
			BadResult(f)																					\
}


namespace vkr
{
	namespace utilities
	{


		static std::vector<char> readFile(const std::string& filename, bool binary = false)
		{
			std::ifstream file(filename, binary ? std::ios::ate | std::ios::binary : std::ios::ate);

			if (!file.is_open()) {
				throw std::runtime_error("failed to open file");
			}

			size_t fileSize = (size_t)file.tellg();
			std::vector<char> buffer(fileSize);

			file.seekg(0);
			file.read(buffer.data(), fileSize);

			file.close();

			return buffer;
		}
	}
}
#endif
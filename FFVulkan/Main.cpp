#include "VulkanRenderer.h"



#ifdef DEBUG
const bool DebugMode = false;
#else
const bool DebugMode = true;
#endif


int main()
{
	try
	{
		vkr::VulkanRendererCreateInfo vrci;
		vrci.requiredInformation.appName = "TestApplication";
		vrci.requiredInformation.appVersion = { 1, 0, 0 };
		vrci.requiredInformation.windowSize = { 800, 600 };
		vrci.optionalInformation.ValidationEnabled = DebugMode;

		vkr::VulkanRenderer renderer(vrci);

		while (!glfwWindowShouldClose(renderer.getState().window->pHandle))
		{
			glfwPollEvents();
		}
	}

	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;

	}



	system("pause");
	return 0;
}
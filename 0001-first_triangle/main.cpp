#include <iostream>
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

using namespace std;

class Application
{
	public:
		void run()
		{
			initWindow();
			initVulkan();
			mainLoop();
			cleanUp();
		}
	private:
		void initWindow()
		{
			glfwInit();
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
			window_ = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", 0, 0);

		}
		void initVulkan()
		{
			createInstance();
		}
		
		void mainLoop()
		{
			while(!glfwWindowShouldClose(window_))
				glfwPollEvents();
		}

		void cleanUp()
		{
			vkDestroyInstance(instance_, 0);
			glfwDestroyWindow(window_);
			glfwTerminate();
		}

		void createInstance()
		{
			VkApplicationInfo appInfo {};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Hello Triangle";
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.pEngineName = "No Engine";
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_0;

			VkInstanceCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			createInfo.pApplicationInfo = &appInfo;

			uint32_t glfwExtensionCount = 0;
			const char ** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
			createInfo.enabledExtensionCount = glfwExtensionCount;
			createInfo.ppEnabledExtensionNames = glfwExtensions;
			createInfo.enabledLayerCount = 0;
			VkResult result = vkCreateInstance(&createInfo, nullptr, &instance_);
			if (result != VK_SUCCESS)
				throw std::runtime_error("failed to create instance");
		}

	private:
		const uint32_t WIDTH = 800;
		const uint32_t HEIGHT = 600;
		GLFWwindow* window_ = 0;
		VkInstance instance_ = 0;
};

int main(int argc, char** argv)
{
	Application app;
	try
	{
		app.run();
	}
	catch(const std::exception& e)
	{
		cerr << e.what() << endl;
		return EXIT_FAILURE;
	}
	return 0;
}

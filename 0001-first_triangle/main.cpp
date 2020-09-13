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

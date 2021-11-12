#include <iostream>
#include <vector>

#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

using namespace std;

const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

#ifdef NODEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr)
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	else
		return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{ 
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessagerEXT");
	if (func != nullptr)
		func(instance, debugMessenger, pAllocator);

}

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
			setupDebugMessager();
		}
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
		{
			//createInfo = {};
			//createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_MESSENGER_CREATE_INFO_EXT;
			//createInfo.messageSeverity = VK_DEBUG_MESSAGE_TYPE_GENERAL_BIT_EXT|VK_DEBUG_MESSAGE_TYPE_VALIDATION_BIT_EXT|VK_DEBUG_MESSAGE_TYPE_PERFORMENCE_BIT_EXT;
			//createInfo.pfnUserCallback = debugCallback;
		}
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
				VkDebugUtilsMessageTypeFlagsEXT messageType,
				const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
				void* pUserData)
		{
			std::cerr << "validation layer:" << pCallbackData->pMessage << std::endl;
			return VK_FALSE;
		}

		void setupDebugMessager()
		{
			if (!enableValidationLayers)
				return;
			VkDebugUtilsMessengerCreateInfoEXT createInfo;
			populateDebugMessengerCreateInfo(createInfo);
			if (CreateDebugUtilsMessengerEXT(instance_, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
				throw std::runtime_error("faild to set up debug messenger");
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
		VkDebugUtilsMessengerEXT debugMessenger = 0;
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

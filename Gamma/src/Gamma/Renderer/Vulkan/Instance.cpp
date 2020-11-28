#include "Instance.h"
#include <SDL_vulkan.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <iostream>

namespace Gamma {

	namespace Vulkan {

		VkInstance Instance = nullptr; 
		std::vector<const char*> SupportedRequestedLayers;

		void Gamma_Graphics_API_Init(void) {
			// TODO: Find a better way to do this without using 10000 vectors and allocations 
			const std::vector<const char*> DefaultLayers = {
			#ifdef GAMMA_DEBUG
				"VK_LAYER_KHRONOS_validation",
				"VK_LAYER_LUNARG_standard_validation",
			#endif
			};
			// TODO: Add the exts for other platforms 
			// The Reason why I hardcode the window exts is because the exts returned by SDL2 are hardcoded as well
			// However SDL2 won't return the values unless you have created a window and stuff and it became a debugging nightmare
			// I may go through the SDL_(platform)vulkan.c files to get the platform specific surface exts 
			const char* DefaultExtensions[] = {
				"VK_KHR_surface",
#if defined(GAMMA_PLATFORM_WINDOWS)
				"VK_KHR_win32_surface",
#elif defined(GAMMA_PLATFORM_MACOS)
#elif defined(GAMMA_PLATFORM_LINUX)
#endif
			};
			uint32_t SupportedLayerCount = 0;
			vkEnumerateInstanceLayerProperties(&SupportedLayerCount, nullptr);
			std::vector<VkLayerProperties> SupportedLayers(SupportedLayerCount);
			vkEnumerateInstanceLayerProperties(&SupportedLayerCount, SupportedLayers.data());
			for (const char* RequestedLayer : DefaultLayers) {
				for (VkLayerProperties SupportedLayer : SupportedLayers) {
					if (!strcmp(RequestedLayer, SupportedLayer.layerName)) {
						SupportedRequestedLayers.push_back(RequestedLayer);
						break;
					}
				}
			}
			for (int index = 0; index < ARRAY_SIZE(DefaultExtensions); index++) {
				printf("%s\n", DefaultExtensions[index]);
			}
			VkApplicationInfo ApplicationInfo = {};
			ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			ApplicationInfo.pNext = nullptr;
			ApplicationInfo.apiVersion = VK_API_VERSION_1_0;
			ApplicationInfo.pEngineName = "Gamma Engine";
			ApplicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			ApplicationInfo.pApplicationName = nullptr;
			ApplicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
			VkInstanceCreateInfo InstanceCreateInfo = {};
			InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			InstanceCreateInfo.pNext = nullptr;
			InstanceCreateInfo.pApplicationInfo = &ApplicationInfo;
			InstanceCreateInfo.enabledExtensionCount = ARRAY_SIZE(DefaultExtensions);
			InstanceCreateInfo.ppEnabledLayerNames = DefaultExtensions;
			InstanceCreateInfo.enabledLayerCount = SupportedRequestedLayers.size();
			InstanceCreateInfo.ppEnabledLayerNames = SupportedRequestedLayers.data();
			vkCreateInstance(&InstanceCreateInfo, nullptr, &Instance);
		}

		void Gamma_Graphics_API_Quit(void) {
			vkDestroyInstance(Instance, nullptr);
		}

	}

}
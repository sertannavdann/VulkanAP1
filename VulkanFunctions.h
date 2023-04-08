#pragma once

#include <vulkan.h>

namespace VulkanCookbook {

	#define EXPORTED_VULKAN_FUNCTION( name )
	#define GLOBAL_LEVEL_VULKAN_FUNCTION(vkEnumerateInstanceExtensionProperties)
	#define GLOBAL_LEVEL_VULKAN_FUNCTION(vkEnumerateInstanceLayerProperties)
	#define GLOBAL_LEVEL_VULKAN_FUNCTION(vkCreateInstance)
	#define INSTANCE_LEVEL_VULKAN_FUNCTION( name )
	#define INSTANCE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION( name, extension )
	#define DEVICE_LEVEL_VULKAN_FUNCTION( name )
	#define DEVICE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION( name, extension )

	#include "ListOfVulkanFunctions.inl"

} // namespace VulkanCookbook

#include "VulkanFunctions.h"
#include <iostream>
#include <Windows.h>
#include <memory>

// Function pointers structure
struct VulkanFunctionPointers {
    PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
    PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;
    PFN_vkEnumerateInstanceLayerProperties vkEnumerateInstanceLayerProperties;
    PFN_vkCreateInstance vkCreateInstance;
};

// Deleter for Vulkan library
struct VulkanLibraryDeleter {
    void operator()(HMODULE vulkan_library) const {
        if (vulkan_library) {
            FreeLibrary(vulkan_library);
        }
    }
};

// Unique pointer type for Vulkan library
using VulkanLibraryPtr = std::unique_ptr<std::remove_pointer<HMODULE>::type, VulkanLibraryDeleter>;

// Vulkan library management class
class VulkanLibrary {
public:
    VulkanLibrary() : vulkan_library_(nullptr) {}
    ~VulkanLibrary() { Unload(); }

    bool Load() {
        HMODULE vulkan_library = LoadLibraryW(L"vulkan-1.dll");
        if (vulkan_library == nullptr) {
            std::cout << "Could not connect with a Vulkan Runtime library." << std::endl;
            return false;
        }
        vulkan_library_.reset(vulkan_library);

        vulkanFunctions_.vkGetInstanceProcAddr = 
            reinterpret_cast<PFN_vkGetInstanceProcAddr>(
                GetProcAddress(vulkan_library_.get(), "vkGetInstanceProcAddr")
        );

        if (vulkanFunctions_.vkGetInstanceProcAddr == nullptr) {
            std::cout << "Failed to load vkGetInstanceProcAddr" << std::endl;
            return false;
        }

        vulkanFunctions_.vkEnumerateInstanceExtensionProperties = 
            reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(
                vulkanFunctions_.vkGetInstanceProcAddr(
                    nullptr, "vkEnumerateInstanceExtensionProperties")
            );
        
        vulkanFunctions_.vkEnumerateInstanceLayerProperties = 
            reinterpret_cast<PFN_vkEnumerateInstanceLayerProperties>(
                vulkanFunctions_.vkGetInstanceProcAddr(
                    nullptr, "vkEnumerateInstanceLayerProperties")
            );

        vulkanFunctions_.vkCreateInstance = 
            reinterpret_cast<PFN_vkCreateInstance>(
                vulkanFunctions_.vkGetInstanceProcAddr(
                    nullptr, "vkCreateInstance")
            );

        if (!LoadGlobalLevelFunctions()) {
            std::cout << "Failed to load global-level Vulkan functions" << std::endl;
            return false;
        }

        return true;
    }

    void Unload() {
        vulkan_library_.reset();
    }

    VulkanFunctionPointers& GetFunctions() { return vulkanFunctions_; }

private:
    bool LoadGlobalLevelFunctions() {
#define GLOBAL_LEVEL_VULKAN_FUNCTION( name )                      \
            vulkanFunctions_.name = (PFN_##name)vulkanFunctions_.vkGetInstanceProcAddr( nullptr, #name ); \
            if( vulkanFunctions_.name == nullptr ) {                                           \
              std::cout << "Could not load global-level function named: "     \
                #name << std::endl;                                           \
              return false;                                                   \
            } 

#include "ListOfVulkanFunctions.inl" 
        return true;
    }

    VulkanLibraryPtr vulkan_library_;
    VulkanFunctionPointers vulkanFunctions_;
};

int main() {
    VulkanLibrary vulkan_library;

    if (!vulkan_library.Load()) {
        std::cout << "Failed to load Vulkan library" << std::endl;
        return 1;
    }

    // Do something with the Vulkan library

    return 0;
}

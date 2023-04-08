# Vulkan Library Manager

This code demonstrates how to load and manage the Vulkan library and its functions at runtime. It provides a clean interface for working with the Vulkan API and ensures proper resource management. The main components of the code are:</br>

1. **VulkanFunctionPointers**: Structure to hold function pointers for the Vulkan functions that will be loaded dynamically. </br> </br>
2. **VulkanLibraryDeleter**: Custom deleter to properly free the Vulkan library handle (HMODULE) when the `unique_ptr` managing it goes out of scope or is reset. </br> </br>
3. **VulkanLibraryPtr**: Type alias for `unique_ptr` that manages the Vulkan library handle and uses the custom deleter `VulkanLibraryDeleter`. </br> </br>
4. **VulkanLibrary class**: Encapsulates functionality related to loading and unloading the Vulkan library, and managing the Vulkan function pointers. 
   - Constructor & Destructor: Initialize the `unique_ptr` and ensure the Vulkan library is properly unloaded when the class instance is destroyed. </br>
   - Load: Load the Vulkan library, retrieve function pointers, and load global-level Vulkan functions. </br>
   - Unload: Release the Vulkan library handle by resetting the `unique_ptr`. </br>
   - GetFunctions: Provide access to the loaded Vulkan function pointers. </br>
   - LoadGlobalLevelFunctions (private): Helper function to load global-level Vulkan functions. </br>
5. **main function**: Demonstrates usage of the `VulkanLibrary` class to load and work with the Vulkan library and functions. </br>
</br> </br>
The code is designed to make the management of the Vulkan library and its functions more straightforward, providing an organized and clean interface for working with the Vulkan API. The use of custom deleters, unique pointers, and a class-based approach ensures that resources are properly managed.

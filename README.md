# Architect

Architect is a 64-bit Game engine for 2D games, still in its early stage.
For the time being OpenGl is supported, but in the future DirectX and Vulkan support will be added.
The main focus odf this project is to provide an engine, API and editor for 2D games that is comprehensive and easy to handle 

# Preprocessor statements used
_DEBUG\n
_CONSOLE
_CRT_SECURE_NO_WARNINGS
GLEW_STATIC
_USE_MATH_DEFINES
GLM_FORCE_RADIANS
PLATFORM_WINDOWS (only a very small piece of code relies on the windows header, which easily can be rewritten for MacOs and Linux)

The engine relies on the following liabrary dependencies and have to be placed in 
the specified folders (if you don't want to chnage dependency and library directories in the project settings)
[library , include folder , library folder]
GLFW      $(ProjectDir)/vendor/glfw/include/GLFW          $(ProjectDir)/vendor/glfw/lib-vc2022
GLEW      $(ProjectDir)/vendor/glew/include/GL            $(ProjectDir)/vendor/glew/lib/Release/x64
glm       $(ProjectDir)/vendor/glm/glm
ImGui     $(ProjectDir)/vendor/imgui
OpenAl    $(ProjectDir)/vendor/openal/include/AL          $(ProjectDir)/vendor/openal/libs/Win64 / $(ProjectDir)/vendor/openal/libs/Win64/EFX-Util_MT
entt      $(ProjectDir)/vendor/entt/include
assimp    $(ProjectDir)/vendor/assimp/include/assimp      $(ProjectDir)/vendor/assimp/lib/x64

Library .lib file names
opengl32.lib
assimp.lib
glew32s.lib
glfw3.lib
OpenAL32.lib
EFX-Util.lib

If you decide to link glew dynamicaly just remove the GLEW_STATIC preprocessor statement and replace glew32s.lib with glew32.lib

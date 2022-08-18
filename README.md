# Architect

Architect is a 64-bit Game engine for 2D games, still in its early stage.
For the time being OpenGl is supported, but in the future DirectX and Vulkan support will be added.
The main focus odf this project is to provide an engine, API and editor for 2D games that is comprehensive and easy to handle 

# Preprocessor statements used
_DEBUG<br />
_CONSOLE<br />
_CRT_SECURE_NO_WARNINGS<br />
GLEW_STATIC<br />
_USE_MATH_DEFINES<br />
GLM_FORCE_RADIANS<br />
PLATFORM_WINDOWS (only a very small piece of code relies on the windows header, which easily can be rewritten for MacOs and Linux)<br />

The engine relies on the following liabrary dependencies and have to be placed in 
the specified folders (if you don't want to chnage dependency and library directories in the project settings)
[library , include folder , library folder]<br />
GLFW      $(ProjectDir)/vendor/glfw/include/GLFW          $(ProjectDir)/vendor/glfw/lib-vc2022<br />
GLEW      $(ProjectDir)/vendor/glew/include/GL            $(ProjectDir)/vendor/glew/lib/Release/x64<br />
glm       $(ProjectDir)/vendor/glm/glm<br />
ImGui     $(ProjectDir)/vendor/imgui<br />
OpenAl    $(ProjectDir)/vendor/openal/include/AL          $(ProjectDir)/vendor/openal/libs/Win64 / $(ProjectDir)/vendor/openal/libs/Win64/EFX-Util_MT<br />
entt      $(ProjectDir)/vendor/entt/include<br />
assimp    $(ProjectDir)/vendor/assimp/include/assimp      $(ProjectDir)/vendor/assimp/lib/x64<br />

Library .lib file names<br />
opengl32.lib<br />
assimp.lib<br />
glew32s.lib<br />
glfw3.lib<br />
OpenAL32.lib<br />
EFX-Util.lib<br />

If you decide to link glew dynamicaly just remove the GLEW_STATIC preprocessor statement and replace glew32s.lib with glew32.lib

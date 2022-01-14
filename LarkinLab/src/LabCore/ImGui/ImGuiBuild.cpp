// Contains parts of ImGui we want to compile and include

#include "llpch.h"

#include <glad/glad.h>
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM 
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "backends/imgui_impl_opengl3.cpp"
#include "backends/imgui_impl_glfw.cpp"
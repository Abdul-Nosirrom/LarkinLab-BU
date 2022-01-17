#include "llpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace LarkinLab
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_windowHandle(windowHandle)
	{
		LL_CORE_ASSERT(windowHandle, "Window is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		// Once GL Context is created, load GLAD //
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LL_CORE_ASSERT(status, "GLAD Failed to initialize");

		LL_CORE_INFO("OpenGL Info:");
		LL_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		LL_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		LL_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}

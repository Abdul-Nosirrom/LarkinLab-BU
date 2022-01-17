#pragma once
#include "LabCore/Renderer/RenderingContext.h"

struct GLFWwindow; // Forward declaration 

namespace LarkinLab
{

	class OpenGLContext : public RenderingContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};
}

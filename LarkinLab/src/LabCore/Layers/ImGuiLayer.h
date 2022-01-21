#pragma once

#include "LabCore/Layers/Layer.h"


#include "LabCore/Events/MouseEvent.h"
#include "LabCore/Events/KeyEvent.h"
#include "LabCore/Events/ApplicationEvent.h"

#include "Platform/OpenGL/OpenGLTexture.h"

#include "imgui.h"

namespace LarkinLab
{
	class LL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}

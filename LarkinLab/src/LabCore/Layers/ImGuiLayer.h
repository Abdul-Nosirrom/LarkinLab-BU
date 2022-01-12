#pragma once

#include "Layer.h"

namespace LarkinLab
{
	class LL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();

		void OnUpdate();
		void OnEvent(Event& event);
	protected:
		float m_Time = 0.0f;
	};
}

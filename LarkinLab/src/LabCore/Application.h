#pragma once

#include "Core.h"
#include "Window.h"
#include "LabCore/Layers/LayerStack.h"
#include "LabCore/Events/Event.h"
#include "LabCore/Events/ApplicationEvent.h"

namespace LarkinLab
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	class LL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;

	};

	// To be defined in client code
	Application* CreateApplication();

}


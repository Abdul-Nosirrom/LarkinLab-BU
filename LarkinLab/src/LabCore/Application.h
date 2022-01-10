#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

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
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	};

	// To be defined in client code
	Application* CreateApplication();

}


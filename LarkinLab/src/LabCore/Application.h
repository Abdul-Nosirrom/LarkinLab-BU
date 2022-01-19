#pragma once

#include "Core.h"
#include "Window.h"
#include "LabCore/Layers/LayerStack.h"
#include "LabCore/Layers/ImGuiLayer.h"
#include "LabCore/Events/Event.h"
#include "LabCore/Events/ApplicationEvent.h"

namespace LarkinLab
{

	class LL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Close();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;

		static Application* s_Instance;

	};

	// To be defined in client code
	Application* CreateApplication();

}


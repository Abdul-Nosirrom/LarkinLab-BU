#pragma once

#include "llpch.h"

#include "LabCore/Core.h"
#include "LabCore/Events/Event.h"

namespace LarkinLab
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Lab Tools",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	/// <summary>
	/// Interface representing a desktop system based windows for each platform to implement
	/// </summary>
	class LL_API Window
	{
	public:
		// Event call back function
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		inline virtual void* GetNativeWindow() const = 0;	// WindowGetter

		static Window* Create(const WindowProps& props = WindowProps());
	};
}

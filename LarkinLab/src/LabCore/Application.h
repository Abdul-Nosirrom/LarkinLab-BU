#pragma once
#include "Core.h"

namespace LarkinLab
{

	class LL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	};

	// To be defined in client code
	Application* CreateApplication();

}


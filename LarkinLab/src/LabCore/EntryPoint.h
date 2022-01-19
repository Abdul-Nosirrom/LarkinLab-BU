#pragma once
#include "LabCore/Core.h"
#include "LabCore/Application.h"

#ifdef LL_PLATFORM_WINDOWS

extern LarkinLab::Application* LarkinLab::CreateApplication();

int main(int argc, char** argv)
{
	LarkinLab::Log::Init();
	LL_INFO("Initialized Log!");

	auto app = LarkinLab::CreateApplication();
	app->Run();
	delete app;
}

#endif

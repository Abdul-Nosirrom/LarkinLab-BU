#pragma once

#ifdef LL_PLATFORM_WINDOWS

extern LarkinLab::Application* LarkinLab::CreateApplication();

int main(int argc, char** argv)
{
	LarkinLab::Log::Init();
	LL_CORE_WARN("Initialized Log!");
	LL_INFO("Welcome\n");

	auto app = LarkinLab::CreateApplication();
	app->Run();
	delete app;
}

#endif

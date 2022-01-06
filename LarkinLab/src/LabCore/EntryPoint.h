#pragma once

#ifdef LL_PLATFORM_WINDOWS

extern LarkinLab::Application* LarkinLab::CreateApplication();

int main(int argc, char** argv)
{
	auto app = LarkinLab::CreateApplication();
	app->Run();
	delete app;
}

#endif

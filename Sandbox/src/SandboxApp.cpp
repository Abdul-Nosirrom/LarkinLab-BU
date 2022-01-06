#include <LarkinLab.h>

class Sandbox : public LarkinLab::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

LarkinLab::Application* LarkinLab::CreateApplication()
{
	return new Sandbox();
}
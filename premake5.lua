workspace "LarkinLab"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "LarkinLab/vendor/GLFW/include"
IncludeDir["Glad"] = "LarkinLab/vendor/Glad/include"
IncludeDir["ImGui"] = "LarkinLab/vendor/imgui"

include "LarkinLab/vendor/GLFW"
include "LarkinLab/vendor/Glad"
include "LarkinLab/vendor/imgui"

project "LarkinLab"
	location "LarkinLab"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "llpch.h"
	pchsource "LarkinLab/src/llpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	defines
	{
		"GLFW_INCLUDE_NONE" -- To avoid GLAD and GLFW both including openGL
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"LL_PLATFORM_WINDOWS",
			"LL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "LL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "LL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "LL_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"LarkinLab/vendor/spdlog/include",
		"LarkinLab/src"
	}

	links
	{
		"LarkinLab"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"LL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "LL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "LL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "LL_DIST"
		runtime "Release"
		optimize "On"


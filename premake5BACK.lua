workspace "LarkinLab"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"	
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {} 
IncludeDir["GLFW"] = "LarkinLab/vendor/GLFW/include"

include "LarkinLab/vendor/GLFW"

--------------------------------------------------------------------

project "LarkinLab"
	location "LarkinLab"
	kind "SharedLib" -- Because project produces a dll
	language "C++"

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
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW", --Static library
		"opengl32.lib"
	}

	-- Multiplatform filters
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On" -- Linking runtime libraries statically 
		systemversion "latest"

		defines
		{
			"LL_PLATFORM_WINDOWS",
			"LL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "LL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "LL_RELEASE"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"LarkinLab/src",
		"LarkinLab/vendor/spdlog/include"
	}

	links
	{
		"LarkinLab"
	}

	-- Multiplatform filters
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on" -- Linking runtime libraries statically 
		systemversion "latest"

		defines
		{
			"LL_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "LL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "LL_RELEASE"
		optimize "On"



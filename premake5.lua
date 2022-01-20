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
IncludeDir["glm"] = "LarkinLab/vendor/glm"
IncludeDir["FileDialog"] = "LarkinLab/vendor/tinyfiledialogs"
--IncludeDir["OpenCV"] = "../opencv/build/install/include"

--LibraryDir = {}
--LibraryDir["OpenCV"] = "../opencv/build/install/x64/vc16/lib"

include "LarkinLab/vendor/GLFW"
include "LarkinLab/vendor/Glad"
include "LarkinLab/vendor/imgui"

project "LarkinLab"
	location "LarkinLab"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "llpch.h"
	pchsource "LarkinLab/src/llpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/tinyfiledialogs/**.c",
		"%{prj.name}/vendor/tinyfiledialogs/**.h"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/stdb",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.FileDialog}"
		--"%{IncludeDir.OpenCV}"
	}

	libdirs
	{
		--"{%LibraryDir.OpenCV}"
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
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE" -- To avoid GLAD and GLFW both including openGL
	}

	filter "system:windows"
		--cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"LL_PLATFORM_WINDOWS",
			"LL_BUILD_DLL"
		}

		--postbuildcommands
		--{
		--	("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		--}

	filter "system:linux"
		pic "On"
		cppdialect "C++17"
		systemversion "latest"

		links 
		{ 
			"Xrandr",
			"Xi",
			"GLEW",
			"GLU",
			"GL",
			"X11"
		}

		defines
		{
			"LL_PLATFORM_LINUX"
		}

	filter "configurations:Debug"
		defines "LL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LL_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"LarkinLab/src",
		"LarkinLab/vendor",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.FileDialog}"
		--"%{IncludeDir.OpenCV}"
	}

	libdirs
	{
		--"{%LibraryDir.OpenCV}"
	}

	links
	{
		"LarkinLab"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"LL_PLATFORM_WINDOWS"
		}

	filter "system:linux"
		systemversion "latest"

		defines
		{
			"LL_PLATFORM_LINUX"
		}

		links
		{
			"GLFW",
			"Glad",
			"ImGui",
			"Xrandr",
			"Xi",
			"dl",
			"pthread"
		}

	filter "configurations:Debug"
		defines "LL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LL_DIST"
		runtime "Release"
		optimize "on"


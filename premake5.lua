workspace "LarkinLab"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"	
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "LarkinLab"
	location "LarkinLab"
	kind "SharedLib" -- Because project produces a dll
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
		"%{prj.name}/vendor/spdlog/include"
	}

	-- Multiplatform filters
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on" -- Linking runtime libraries statically 
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
		"%{prj.name}/vendor/spdlog/include"
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



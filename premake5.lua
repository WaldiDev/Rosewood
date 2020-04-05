workspace "Rosewood"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Shipping"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Rosewood"
	location "Rosewood"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Pch.h"
	pchsource "%{prj.name}/Source/Pch.cpp"

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/Source",
		"%{prj.name}/Vendor/spdlog/include"
	}

	filter "system:windows"		
		systemversion "latest"

		defines
		{
			"RW_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RW_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RW_RELEASE"
		runtime "Release"		
		optimize "on"

	filter "configurations:Shipping"
		defines "RW_SHIPPING"
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
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"Rosewood/Vendor/spdlog/include",
		"Rosewood/Source"
	}

	links
	{
		"Rosewood"
	}

	filter "system:windows"		
		systemversion "latest"

		defines
		{
			"RW_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RW_DEBUG"
		runtime "Debug"		
		symbols "on"

	filter "configurations:Release"
		defines "RW_RELEASE"
		runtime "Release"		
		optimize "on"

	filter "configurations:Shipping"
		defines "RW_SHIPPING"
		runtime "Release"		
		optimize "on"
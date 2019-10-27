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
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RW_PLATFORM_WINDOWS",
			"RW_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "RW_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "RW_RELEASE"
		runtime "Release"		
		optimize "On"

	filter "configurations:Shipping"
		defines "RW_SHIPPING"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

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
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"RW_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RW_DEBUG"
		runtime "Debug"		
		symbols "On"

	filter "configurations:Release"
		defines "RW_RELEASE"
		runtime "Release"		
		optimize "On"

	filter "configurations:Shipping"
		defines "RW_SHIPPING"
		runtime "Release"		
		optimize "On"
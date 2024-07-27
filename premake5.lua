workspace "Grape"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Grape/thirdparty/GLFW/include"

include "Grape/thirdparty/GLFW"

project "Grape"
	location "Grape"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	pchheader "gppch.h"
	pchsource "Grape/src/gppch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/thirdparty/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GP_PLATFORM_WINDOWS",
			"GP_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "GP_DEBUG"
		optimize "On"

	filter "configurations:Release"
		defines "GP_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GP_Dist"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Grape/thirdparty/spdlog/include",
		"Grape/src"
	}

	links
	{
		"Grape"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GP_DEBUG"
		optimize "On"

	filter "configurations:Release"
		defines "GP_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GP_Dist"
		optimize "On"


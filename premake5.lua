workspace "Grape"
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
IncludeDir["GLFW"] = "Grape/thirdparty/GLFW/include"
IncludeDir["Glad"] = "Grape/thirdparty/Glad/include"
IncludeDir["ImGui"] = "Grape/thirdparty/imgui"
IncludeDir["glm"] = "Grape/thirdparty/glm"

include "Grape/thirdparty/GLFW"
include "Grape/thirdparty/Glad"
include "Grape/thirdparty/imgui"

project "Grape"
	location "Grape"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	pchheader "gppch.h"
	pchsource "Grape/src/gppch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/thirdparty/glm/glm/**.hpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/thirdparty/spdlog/include",
		"%{prj.name}/thirdparty",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GP_PLATFORM_WINDOWS",
			"GP_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		defines "GP_DEBUG"
		buildoptions "/MDd" -- 多线程调式
		symbols "on"

	filter "configurations:Release"
		defines "GP_RELEASE"
		buildoptions "/MD"  -- 多线程
		optimize "on"

	filter "configurations:Dist"
		defines "GP_Dist"
		buildoptions "/MD"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Grape/src",
		"Grape/thirdparty",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Grape"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GP_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GP_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "GP_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "GP_Dist"
		buildoptions "/MD"
		optimize "on"


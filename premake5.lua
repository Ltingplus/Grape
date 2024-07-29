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
		"%{prj.name}/thirdparty/glm/glm/**.hpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/thirdparty/spdlog/include",
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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GP_PLATFORM_WINDOWS",
			"GP_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "GP_DEBUG"
		buildoptions "/MDd" -- 多线程调式
		symbols "On"

	filter "configurations:Release"
		defines "GP_RELEASE"
		buildoptions "/MD"  -- 多线程
		optimize "On"

	filter "configurations:Dist"
		defines "GP_Dist"
		buildoptions "/MD"
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
		"Grape/src",
		"%{IncludeDir.glm}"
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
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "GP_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "GP_Dist"
		buildoptions "/MD"
		optimize "On"


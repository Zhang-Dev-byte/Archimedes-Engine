workspace "Archimedes"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Archimedes/vendor/GLFW/include"
IncludeDir["Glad"] = "Archimedes/vendor/Glad/include"
IncludeDir["glm"] = "Archimedes/vendor/glm"

include "Archimedes/vendor/GLFW"
include "Archimedes/vendor/Glad"

project "Archimedes"
	location "Archimedes"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"AC_PLATFORM_WINDOWS",
			"AC_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "AC_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AC_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "AC_DIST"
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
		"Archimedes/vendor/spdlog/include",
		"Archimedes/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Archimedes",
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"AC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "AC_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AC_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "AC_DIST"
		optimize "On"
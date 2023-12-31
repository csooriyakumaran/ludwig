workspace "ludwig"
    architecture "x64" 
    configurations {"Debug", "Release", "Dist"} 
    startproject "ludwig"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

IncludeDirs = {}
IncludeDirs["vk"]      = "libs/vk/include"
-- external
-- includedir["cgns"] = "%{cgns_sdk}/include"

LibraryDirs = {}
LibraryDirs["vk"]      = "libs/vk/bin/" .. outputdir .. "/vk"
-- external
-- LibraryDirs["cgns"]    = "%{cgns_sdk}/lib"

Library = {}
Library["vk"]          = "%{LibraryDirs.vk}/vk" 

group "Core"
    include "libs/vk/build-vk.lua"
group ""

project "ludwig" 
    kind "StaticLib" 
    language "C++" 
    cppdialect "C++20" 
    staticruntime "off"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/" .. outputdir .. "/%{prj.name}")

    files { "src/**.h", "src/**.cpp" }

    includedirs {
        "%{IncludeDirs.vk}",
    }
    links {
        "%{Library.vk}",
    }

    defines {

    }

    filter "system:windows" 
        systemversion "latest" 
        defines { "LW_PLATFORM_WINDOWS" }

    filter "configurations:Debug" 
        defines { "LW_DEBUG" }
        runtime "Debug" 
        symbols "On" 

    filter "configurations:Release" 
        defines { "LW_RELEASE" }
        runtime "Release" 
        optimize "On" 
        symbols "On" 

    filter "configurations:Dist" 
        defines { "LW_DIST" }
        runtime "Release" 
        optimize "On" 
        symbols "Off"

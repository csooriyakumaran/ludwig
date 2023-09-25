workspace "ludwig"
    architecture "x64" 
    configurations {"Debug", "Release", "Dist"} 
    startproject "ludwig"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

project "ludwig" 
    kind "ConsoleApp" 
    language "C++" 
    cppdialect "C++20" 
    staticruntime "off"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/" .. outputdir .. "/%{prj.name}")

    files { "src/**.h", "src/**.cpp" }

    includedirs { "src" }
    links { }

    filter "system:windows" 
        systemversion "latest" 
        defines { "PLATFORM_WINDOWS" }

    filter "configurations:Debug" 
        defines { "DEBUG" }
        runtime "Debug" 
        symbols "On" 

    filter "configurations:Release" 
        defines { "RELEASE" }
        runtime "Release" 
        optimize "On" 
        symbols "On" 

    filter "configurations:Dist" 
        defines { "DIST" }
        runtime "Release" 
        optimize "On" 
        symbols "Off"

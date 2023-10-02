workspace "ludwig"
    architecture "x64" 
    configurations {"Debug", "Release", "Dist"} 
    startproject "ludwig"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 
CGNS_SDK = os.getenv("CGNS_SDK")

IncludeDir = {}
IncludeDir["CGNS"] = "%{CGNS_SDK}/include"

LibraryDir = {}
LibraryDir["CGNS"] = "%{CGNS_SDK}/lib"

Library = {}
Library["CGNS"] = "%{LibraryDir.CGNS}/cgns"

print(CGNS_SDK)

project "ludwig" 
    kind "ConsoleApp" 
    language "C++" 
    cppdialect "C++20" 
    staticruntime "off"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/" .. outputdir .. "/%{prj.name}")

    files { "src/**.h", "src/**.cpp" }

    includedirs {
        "src",
        "%{IncludeDir.CGNS}",
    }
    links {
        "%{Library.CGNS}",
    }

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

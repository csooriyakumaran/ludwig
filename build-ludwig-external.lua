
project "ludwig" 
    kind "StaticLib" 
    language "C++" 
    cppdialect "C++20" 
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/" .. outputdir .. "/%{prj.name}")

    pchheader "src/lwpch.h"
    pchsource "src/lwpch.cpp"

    files { "src/**.h", "src/**.cpp" }

    includedirs {
        "src",
        "%{IncludeDirs.vk}",
    }
    links {
        "%{Library.vk}",
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

flags 
{
	"MultiProcessorCompile"
}

workspace "addqt2vs"
	location "build"
	targetdir "bin"
	configurations {"Debug", "Release"}
	platforms { "Win32", "x64"}
	
	language "C++"
	characterset "MBCS"
	implibdir "$(SolutionDir)../lib"
	objdir "$(SolutionDir)obj/%{prj.name}/%{cfg.platform}/%{cfg.buildcfg}"
	
	includedirs
	{
		"./3rd/boost/include",
		"./3rd/pugixml/src/",
	}
	
	filter "configurations:Release" 
		runtime "Release"
		optimize "Speed"
		flags {"Symbols"}
	filter {}

	filter "configurations:Debug" 
		defines {"_DEBUG", "DEBUG"}
		runtime "Debug"
		optimize "Off"
		flags {"Symbols"}
	filter {}
		
	filter { "platforms:x64" }	
		libdirs
		{	
			"./3rd/boost/lib/x64",
		}
	filter {}
	
	filter { "platforms:Win32" }	
		libdirs
		{	
			"./3rd/boost/lib",
		}
	filter {}
	
project("addqt2vs")
	kind "ConsoleApp"
	targetname "addqt2vs"
	
	includedirs
	{
		"./src",
	}
	
	files
	{
		"./src/**.cpp",
		"./src/**.hpp",
		"./src/**.h",
		"./3rd/pugixml/src/**.h",
		"./3rd/pugixml/src/**.hpp",
		"./3rd/pugixml/src/**.cpp",
	}
	
	filter {"Debug", "platforms:Win32"}
		links
		{
			"libboost_filesystem-vc120-mt-gd-x32-1_70.lib",
			"libboost_regex-vc120-mt-gd-x32-1_70.lib",
			"libboost_program_options-vc120-mt-gd-x32-1_70.lib",
		}
	filter {}
	
	filter {"Debug", "platforms:x64"}
		links
		{
			"libboost_filesystem-vc120-mt-gd-x64-1_70.lib",
			"libboost_regex-vc120-mt-gd-x64-1_70.lib",
			"libboost_program_options-vc120-mt-gd-x64-1_70.lib",
		}
	filter {}
		
	filter {"Release", "platforms:Win32"}
		links
		{
			"libboost_filesystem-vc120-mt-x32-1_70.lib",
			"libboost_regex-vc120-mt-x32-1_70.lib",
			"libboost_program_options-vc120-mt-x32-1_70.lib",
		}
	filter {}
	
	filter {"Release", "platforms:x64"}
		links
		{
			"libboost_filesystem-vc120-mt-x64-1_70.lib",
			"libboost_regex-vc120-mt-x64-1_70.lib",
			"libboost_program_options-vc120-mt-x64-1_70.lib",
		}
	filter {}
		
	vpaths
	{
		['include'] = {"**.h", "**.hpp"},
		['src'] = {"**.c", "**.cpp"},
	}
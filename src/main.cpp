#include "pugixml.hpp"

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.h>
#include <boost/regex.hpp>

namespace po = boost::program_options;

void AddQt2Vs(const std::string &filePath)
{

}

bool ConvertVcxproj2Qt(const std::string &pathStr)
{
	boost::filesystem::directory_iterator endIt;
	for (boost::filesystem::directory_iterator pathIt(pathStr.c_str()); pathIt != endIt; ++pathIt)
	{
		if (boost::filesystem::is_directory(pathIt->path()))
		{
			ConvertVcxproj2Qt(pathIt->path().string());
		}
		else if (boost::regex_match(pathIt->path().filename().string(), boost::regex("*.vcxproj")))
		{
			AddQt2Vs(pathIt->path().string());
		}
	}

	return false;
}

int main(int argc, char **argv)
{
	boost::program_options::options_description opts("demo options");
	opts.add_options()
		("help,h", "show help")
		("file,f", boost::program_options::value<std::string>(), "path of vcxproj file")
		("directory,d", boost::program_options::value<std::string>(), "path of vcxproj files directory");
	
	boost::program_options::variables_map valueMap;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, opts), valueMap);

	if (valueMap.size() == 0 || valueMap.count("help")){
		std::cout << opts << std::endl;
		return 0;
	}

	if (valueMap.count("file")){
		ConvertVcxproj2Qt(valueMap["filename"].as<std::string>());
	}
	else if (valueMap.count("directory")){
		ConvertVcxproj2Qt(valueMap["directory"].as<std::string>());
	}
	else
	{
		std::cout << opts << std::endl;
	}

	return 0;
}
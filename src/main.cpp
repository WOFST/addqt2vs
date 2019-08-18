#include "pugixml.hpp"

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.h>
#include <boost/regex.hpp>

namespace po = boost::program_options;
std::string gQtVersion;
std::string gQtGeneratedDir;

void AddQt2Vs(const std::string &filePath)
{
	using namespace pugi;

	xml_document doc;
	if (!doc.load_file(filePath.c_str(), pugi::parse_default, pugi::encoding_utf8))
	{
		std::cout << "load file '" << filePath.c_str() << "' failed."<< std::endl;
		return ;
	}

	xml_node projNode = doc.child("Project");
	if (!projNode)
	{
		return;
	}

	xpath_node globalsPropNode = doc.select_single_node("/Project/PropertyGroup[@Label='Globals']");
	if (!globalsPropNode)
	{
		std::cout << "file: " << filePath.c_str() << "add qt to vs failed, detail: /Project/PropertyGroup/[@Label = 'Globals'] not exit!"
			<< std::endl;
		return;
	}
	
	globalsPropNode.node().remove_child("Keyword");
	globalsPropNode.node().append_child("Keyword").append_child(pugi::node_pcdata).set_value("Qt4VSv1.0");

	xml_node projExtNode = projNode.child("ProjectExtensions");
	if (!projExtNode)
	{
		projExtNode = projNode.append_child("ProjectExtensions");
	}

	xml_node projExtVsNode = projExtNode.child("VisualStudio");
	if (!projExtVsNode)
	{
		projExtVsNode = projExtNode.append_child("VisualStudio");
	}

 	projExtVsNode.remove_child("UserProperties");
	xml_node projExtVsUserPropNode = projExtVsNode.append_child("UserProperties");
	
	projExtVsUserPropNode.append_attribute("UicDir").set_value(gQtGeneratedDir.c_str());
	projExtVsUserPropNode.append_attribute("MocDir").set_value(gQtGeneratedDir.c_str());
	projExtVsUserPropNode.append_attribute("RccDir").set_value(gQtGeneratedDir.c_str());

	projExtVsUserPropNode.append_attribute("Qt5Version_x0020_Win32").set_value(gQtVersion.c_str());
	projExtVsUserPropNode.append_attribute("Qt5Version_x0020_x64").set_value(gQtVersion.c_str());

	doc.save_file(filePath.c_str());
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
		else if (boost::regex_match(pathIt->path().filename().string().c_str(), boost::regex(".*.vcxproj")))
		{
			AddQt2Vs(pathIt->path().string());
		}
	}

	return false;
}

int main(int argc, char **argv)
{
	po::options_description opts("support options");
	opts.add_options()
		("help,h", "show help")
		("file,f", po::value<std::string>(), "path of vcxproj file")
		("directory,d", po::value<std::string>(), "path of vcxproj files directory")
		("version,v", po::value<std::string>()->default_value("5.10.0"), "qt version")
		("generatedDir,g", po::value<std::string>()->default_value("./GeneratedFiles/$(ProjectName)/$(ConfigurationName)"), "qt moc director");

	po::variables_map valueMap;
	po::store(po::parse_command_line(argc, argv, opts), valueMap);

	if (valueMap.size() == 0 || valueMap.count("help")){
		std::cout << opts << std::endl;
		return 0;
	}

	gQtVersion = valueMap["version"].as<std::string>();
	gQtGeneratedDir = valueMap["generatedDir"].as<std::string>();

	if (valueMap.count("file")){
		AddQt2Vs(valueMap["file"].as<std::string>());
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
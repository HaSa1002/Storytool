#pragma once
#include <AF/xml.hpp>
#include <string>
#include <unordered_map>


namespace st {
	using sts = std::string;
	using name = std::string;
	using id = std::string;
	using xmlData = af::XML::Structure;
	using GlobalVars = std::unordered_map<name, double>;
	
	//Program Version
	constexpr auto VERSION = "1.0-DEV";
	/*
		M = Major
		m = Minor
		T = Type
			0  = Development (-DEV)
			1  = Pre-Release (-PRE)
			2  = Public ()
			2+ = Hotfixes (-2+) (i.e: -3, -5, ...)
		Format: MMmmT
	*/
	constexpr auto VERSION_NUM = 01000;
	
	//File Format
	constexpr auto FILE_VERSION = 1;
	constexpr auto MIN_FILE_VER = 1;

}

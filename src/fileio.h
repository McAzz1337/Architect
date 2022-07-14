#pragma once
#include <string>


namespace archt {


	void readFile(const std::string& path, std::string& dst);
	void extractFileName(const std::string& path, std::string& dst);



}
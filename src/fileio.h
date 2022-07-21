#pragma once
#include <string>
#include <vector>

namespace archt {


	void readFile(const std::string& path, std::string& dst, bool log = false);
	void readFileSplit(const std::string& path, std::vector<std::string>& dst, bool log = false);

	void extractFileName(const std::string& path, std::string& dst);

	uint64_t requestFileSize(const std::string& path);

}
#include "fileio.h"
#include <fstream>


namespace archt {


	void readFile(const std::string& path, std::string& dst) {

		std::ifstream in(path);

		if (!in.is_open()) {
			printf("failed to open file: %s\n", path.c_str());
			dst = "";
			return;
		}

		std::string line;
		while (getline(in, line)) {
			dst += line + "\n";
		}
	}

	void extractFileName(const std::string& path, std::string& dst) {
		int start = path.find_last_of('/');

		if (start != std::string::npos)
			dst = path.substr(start + 1);
	}



}
#include "fileio.h"
#include <ios>
#include <iostream>
#include <fstream>


namespace archt {


	void readFile(const std::string& path, std::string& dst, bool log) {

		std::ifstream in(path);

		if (!in.is_open()) {
			
			if (log)
				printf("failed to open file: %s\n", path.c_str());
			
			dst = "";
			return;
		}

		std::string line;
		while (getline(in, line)) {
			dst += line + "\n";
		}

		in.close();
	}

	void readFileSplit(const std::string& path, std::vector<std::string>& dst, bool log) {

		std::ifstream in(path);
		
		if (in.is_open()) {
			
			if (log)
				printf("failed to open file: %s\n", path.c_str());
			
			return;
		}
		

		std::string line;
		while (getline(in, line)) {
			dst.push_back(line);
		}

		in.close();
	}


	void extractFileName(const std::string& path, std::string& dst) {
		int start = path.find_last_of('/');

		if (start != std::string::npos)
			dst = path.substr(start + 1);
	}


	uint64_t requestFileSize(const std::string& path) {
		
		uint64_t begin;
		uint64_t end;

		std::ifstream in(path);
		begin = in.tellg();
		
		in.seekg(0, std::ios::end);
		end = in.tellg();
		
		in.close();

		return end - begin;
	}

}
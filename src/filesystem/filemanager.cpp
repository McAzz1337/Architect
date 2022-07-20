#include "filemanager.h"



namespace archt {
#define MAKE_ENTRY_STATIC(path, type) std::make_pair(path, std::make_pair(type(path), 1))
#define MAKE_ENTTRY_DYNAMIC(path, type) std::make_pair(path, std::make_pair(new type(path), 1))

	FileManager FileManager::instance;


	FileManager::FileManager() {
	}

	FileManager::~FileManager() {

	}



	void* FileManager::loadFile(const std::string& path, FileType type) {

		void* ref = nullptr;
		switch (type) {
			
			case GL_SHADER_T: 
			if (!shaderFiles.contains(path)) {
				shaderFiles.insert(MAKE_ENTRY_STATIC(path, GLShader));
				//shaderFiles.insert(std::make_pair(path, std::make_pair(GLShader(path), 1)));
			}
			else {
				shaderFiles[path].second++;
			}
			ref = (void*) &shaderFiles[path].first;
			break;
			
			case GL_TEXTURE_T: 
			if (!textureFiles.contains(path)) {
				textureFiles.insert(MAKE_ENTTRY_DYNAMIC(path, GLTexture));
			}
			else {
				textureFiles[path].second++;
			}
			ref = (void*) textureFiles[path].first;
			break;

		}

		return ref;
	}

	void FileManager::deleteFile(const std::string& path, FileType type) {
		
		switch (type) {
			
			case GL_SHADER_T:
			if (shaderFiles.contains(path)) {
				if (shaderFiles[path].second == 1) {
					shaderFiles.erase(path);
				}
				else {
					shaderFiles[path].second--;
				}
			}
			break;

			case GL_TEXTURE_T:
			if (textureFiles.contains(path)) {
				if (textureFiles[path].second == 1) {
					textureFiles.erase(path);
				}
				else {
					textureFiles[path].second--;
				}
			}
			break;
		}
	}

	void FileManager::deleteAllFiles() {
		
		shaderFiles.erase(shaderFiles.begin(), shaderFiles.end());
		
		textureFiles.erase(textureFiles.begin(), textureFiles.end());
	}


}
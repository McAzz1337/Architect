#include "filemanager.h"
#include "../fileio.h"


namespace archt {
#define MAKE_ENTRY_STATIC(path, type) std::make_pair(path, std::make_pair(type(path), 1))
#define MAKE_ENTTRY_DYNAMIC(path, type) std::make_pair(path, std::make_pair(new type(path), 1))

#define TRACK_ALLOCATED_MEMORY
#ifdef TRACK_ALLOCATED_MEMORY

#define INCREASE_ALLOCATED_MEMORY(ref, path) if (ref)\
												allocatedMemory += requestFileSize(path)

#define DECREASE_ALLOCATED_MEMORY(ref, path) if (ref)\
												allocatedMemory -= requestFileSize(path)

#else

#define INCREASE_ALLOCATED_MEMORY(ref, path)
#define DECREASE_ALLOCATED_MEMORY(ref, path)

#endif


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

			default: 
				return ref;

		}

		INCREASE_ALLOCATED_MEMORY(ref, path);


		return ref;
	}

	void FileManager::deleteFile(const std::string& path, FileType type) {
		
		void* ref = nullptr;
		switch (type) {
			
			case GL_SHADER_T:
			if (shaderFiles.contains(path)) {
				if (shaderFiles[path].second == 1) {
					ref = &shaderFiles[path].first;
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
					ref = &textureFiles[path].first;
					textureFiles.erase(path);
				}
				else {
					textureFiles[path].second--;
				}
			}
			break;
		}

		DECREASE_ALLOCATED_MEMORY(ref, path);
	}

	void FileManager::deleteAllFiles() {
		
		shaderFiles.erase(shaderFiles.begin(), shaderFiles.end());
		
		textureFiles.erase(textureFiles.begin(), textureFiles.end());
	}

	void FileManager::logAllocateMemory(DataType type) const {
		
		printf("Total allocated memory from files : ");

		switch (type) {
			case BYTES:
			{
				printf("%ui bytes\n", (uint32_t)allocatedMemory);
				break;
			}
			case KILO_BYTES: {
				double size = allocatedMemory / 1000.0;
				printf("%f kilobytes\n", size);
				break;
			}
			case MEGA_BYTES: {
				double size = allocatedMemory / 1000000.0f;
				printf("%f megabytes\n", size);
				break;
			}
			case GIGA_BYTES: {
				double size = allocatedMemory / 1000000000.0f;
				printf("%f gigabytes\n", size);
				break;
			}
		}
	}


}
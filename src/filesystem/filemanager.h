#pragma once
#include <string>
#include <unordered_map>

#include "../gfx/opengl/glshader.h"
#include "../gfx/opengl/gltexture.h"

namespace archt {

	class FileManager {

	public:
		enum FileType {
			GL_SHADER_T,
			GL_TEXTURE_T,
			NONE
		};

		static FileManager instance;

	private:

		std::unordered_map<std::string, std::pair<GLShader, int>> shaderFiles;
		std::unordered_map<std::string, std::pair<GLTexture*, int>> textureFiles;

	public:
		FileManager();
		~FileManager();

		void* loadFile(const std::string& path, FileType type);
		void deleteFile(const std::string& path, FileType type);
		
		void deleteAllFiles();
	};



}
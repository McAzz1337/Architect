#pragma once

#include <typeindex>
#include <string>

#include <glm/mat4x4.hpp>

namespace archt {

	class GLShader {

		static const std::string VS_EXT;
		static const std::string GS_EXT;
		static const std::string FS_EXT;


		uint32_t id = 0;
		std::string file;
		std::string vsrc;
		std::string gsrc;
		std::string fsrc;

	public:
		GLShader();
		GLShader(const std::string& path);
		GLShader(const std::string& vsrc, const std::string& gsrc, const std::string& fsrc);
		~GLShader();
		
		void bind() const;
	
		int getLocation(const char* name) const;


		void setUniformfv(const char* name, float* uniform, int count) const;
		void setUniform4f(const char* name, float* uniform) const;
		void setUniform1f(const char* name, float uniform) const;
		void setUniform1i(const char* name, int uniform) const;
		void setUniform1iv(const char* name, int count, int* uniforms) const;
		void setUniform1ui(const char* name, unsigned int uniform) const;

		void setMat4(const char* name, const glm::mat4& matrix) const;


		void logShaderSource() const;

	private:
		static void compileShader(const std::string& src, int type, int& id);
		static void createProgram(uint32_t& id, uint32_t vertex, uint32_t geometry, uint32_t fragment);
	};
}
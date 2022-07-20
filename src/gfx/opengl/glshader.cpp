#include "glshader.h"

#include "glinclude.h"
#include "../../fileio.h"

#include <glm/mat4x4.hpp>

#include <iostream>

#include "glrenderapi.h"
#include "glshaderconstants.h"
#include "gldebug.h"

namespace archt {

	const std::string GLShader::VS_EXT = ".vert";
	const std::string GLShader::GS_EXT = ".geom";
	const std::string GLShader::FS_EXT = ".frag";

	GLShader::GLShader() {}

	GLShader::GLShader(const std::string& path) : file(path) {
		readFile(path + VS_EXT, vsrc);
		readFile(path + GS_EXT, gsrc);
		readFile(path + FS_EXT, fsrc);

		
		GLShaderConstants::modifySahderSource(vsrc);
		if (gsrc.length() > 0)
			GLShaderConstants::modifySahderSource(gsrc);
		GLShaderConstants::modifySahderSource(fsrc);
		
		logShaderSource();

		int vid = 0;
		int gid = 0;
		int fid = 0;
		compileShader(vsrc, GL_VERTEX_SHADER, vid);
		if (gsrc.length() > 0)
			compileShader(gsrc, GL_GEOMETRY_SHADER, gid);
		compileShader(fsrc, GL_FRAGMENT_SHADER, fid);

		createProgram(id, vid, gid, fid);

		
		
		int maxTextures = GLRenderAPI::getMaxTextureCount();
		int* texIndeces = new int[maxTextures];
		for (int i = 0; i < maxTextures; i++)
			texIndeces[i] = i;

		setUniform1iv("tex", maxTextures, texIndeces);
		delete[] texIndeces;

	}


	GLShader::GLShader(const std::string& vsrc, const std::string& gsrc, const std::string& fsrc)
		: vsrc(vsrc), gsrc(gsrc), fsrc(fsrc) {
	
	
		int vid = 0;
		int gid = 0;
		int fid = 0;
		compileShader(vsrc, GL_VERTEX_SHADER, vid);
		if (gsrc.length() > 0)	
			compileShader(gsrc, GL_GEOMETRY_SHADER, gid);
		compileShader(fsrc, GL_FRAGMENT_SHADER, fid);

		createProgram(id, vid, gid, fid);
	}
	
	GLShader::~GLShader() {
		glDeleteProgram(id);
	}

	void GLShader::bind() const {
		glUseProgram(id);
	}

	int GLShader::getLocation(const char* name) const {
		bind();
		int location = glGetUniformLocation(id, name);
		if (location == -1) {
			std::string fileName;
			extractFileName(file, fileName);
			printf("failed to retrieve uniform location of variable [%s] in shader [%s]\n", name, fileName.c_str());
		}
		return location;
	}

	void GLShader::setUniformfv(const char* name, float* uniform, int count) const {
		int location = getLocation(name);
		if (location > -1)
			glUniform1fv(location, count, uniform);
	}

	void GLShader::setUniform4f(const char* name, float* uniform) const {
		int location = getLocation(name);
		if (location > -1)
			glUniform4f(location, uniform[0], uniform[1], uniform[2], uniform[3]);
	}

	void GLShader::setUniform1f(const char* name, float uniform) const {
		int location = getLocation(name);
		if (location > -1)
			glUniform1f(location, uniform);
	}

	void GLShader::setUniform1i(const char* name, int uniform) const {
		int location = getLocation(name);
		if (location > -1)
			glUniform1i(location, uniform);
	}

	void GLShader::setUniform1iv(const char* name, int count, int* uniforms) const {
		int location = getLocation(name);
		if (location > -1)
			glUniform1iv(location, count, uniforms);
	}

	void GLShader::setUniform1ui(const char* name, unsigned int uniform) const {
		int location = getLocation(name);
		if (location > -1)
			glUniform1ui(location, uniform);
	}
	
	void GLShader::setMat4(const char* name, const glm::mat4& matrix) const {
		int location = getLocation(name);
		if (location > -1)
			glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	}

	void GLShader::setMatrixf4v(const char* name, glm::mat4* matrices, int count) const {
		int location = getLocation(name);
		if (location > -1)
			CALL(glUniformMatrix4fv(location, count, GL_FALSE, (const float*) matrices));
	}


	void GLShader::logShaderSource() const {
		printf("Vertex shader source:\n%s\n", vsrc.c_str());
		printf("Geometry shader source:\n%s\n", gsrc.c_str());
		printf("Fragment shader source:\n%s\n", fsrc.c_str());

	}


	void GLShader::compileShader(const std::string& src, int type, int& id) {
		id = glCreateShader(type);
		const char* temp = src.c_str();
		glShaderSource(id, 1, &temp, NULL);
		glCompileShader(id);
		int isCompiled = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
		
		if (isCompiled == GL_FALSE) {
			int maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			char* infoLog = new char[maxLength];
			int length = 0;
			glGetShaderInfoLog(id, maxLength, &length, infoLog);

			glDeleteShader(id);

			switch (type) {
				case GL_VERTEX_SHADER:		std::cout << "Vertex ";		break;
				case GL_GEOMETRY_SHADER:	std::cout << "Geometry ";	break;
				case GL_FRAGMENT_SHADER:	std::cout << "Fragment ";	break;

			}
			std::cout << "shader compilation failure!" << std::endl << infoLog << std::endl;

			__debugbreak();
		}
	}
	
	void GLShader::createProgram(uint32_t& id, uint32_t vertex, uint32_t geometry, uint32_t fragment) {
		id = glCreateProgram();
		glAttachShader(id, vertex);
		if (geometry != 0)
			glAttachShader(id, geometry);
		glAttachShader(id, fragment);

		glLinkProgram(id);
		int isLinked = 0;
		glGetProgramiv(id, GL_LINK_STATUS, &isLinked);

		if (isLinked == GL_FALSE) {
			int maxLength = 0;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			char* infoLog = new char[maxLength];
			int length = 0;
			glGetProgramInfoLog(id, maxLength, &length, infoLog);

			// We don't need the program anymore.
			glDeleteProgram(id);
			// Don't leak shaders either.
			glDeleteShader(vertex);
			if (geometry != 0) glDeleteShader(geometry);
			glDeleteShader(fragment);

			std::cout << "Shader link failure!" << std::endl;
			std::cout << infoLog << std::endl;

			__debugbreak();
		}


		glDeleteShader(vertex);
		if (geometry > 0)
			glDeleteShader(geometry);
		glDeleteShader(fragment);

	}

}
#include "glshader.h"

#include "glinclude.h"
#include "../../fileio.h"

#include <glm/mat4x4.hpp>

#include <iostream>

namespace archt {

	const std::string GLShader::VS_EXT = ".vert";
	const std::string GLShader::GS_EXT = ".geom";
	const std::string GLShader::FS_EXT = ".frag";

	GLShader::GLShader() {}

	GLShader::GLShader(const std::string& path) {
		extractFileName(path, file);
		readFile(path + VS_EXT, vsrc);
		readFile(path + GS_EXT, gsrc);
		readFile(path + FS_EXT, fsrc);

		int vid = 0;
		int gid = 0;
		int fid = 0;
		
		compileShader(vsrc, GL_VERTEX_SHADER, vid);
		if (gsrc.length() > 0)
			compileShader(gsrc, GL_GEOMETRY_SHADER, gid);
		compileShader(fsrc, GL_FRAGMENT_SHADER, fid);

		id = glCreateProgram();
		glAttachShader(id, vid);
		if (gid != 0)
			glAttachShader(id, gid);
		glAttachShader(id, fid);

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
			glDeleteShader(vid);
			if (gid != 0) glDeleteShader(gid);
			glDeleteShader(fid);

			std::cout << "Shader link failure!" << std::endl;
			std::cout << infoLog << std::endl;

			__debugbreak();
		}


		glDeleteShader(vid);
		if (gid > 0)
			glDeleteShader(gid);
		glDeleteShader(fid);

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
		return glGetUniformLocation(id, name);
	}


	void GLShader::setMat4(const char* name, const glm::mat4& matrix) const {
		int location = getLocation(name);
		if (location > -1)
			glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
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
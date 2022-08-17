#pragma once


#include "../gfx/opengl/buffers.h"
#include "../gfx/opengl/gltexture.h"
#include "../gfx/opengl/glshader.h"

#include "../entity/component/material/uniform.h"

#include <glm/mat4x4.hpp>

#include <string>

namespace archt {
	
	struct Transform_s {

		glm::mat4 transform = glm::mat4(1.0f);

		Transform_s();
		Transform_s(const Transform_s& other) = default;
		~Transform_s();

	};

	struct Mesh_s {

		VBO vbo;
		IBO ibo;

		Mesh_s();
		Mesh_s(Vertex* verteces, uint32_t vSize, uint32_t* indeces, uint32_t iSize);
		~Mesh_s();
	};

	

	struct Material_s {

		GLTexture tex;
		Uniform* uniforms = nullptr;
		GLShader shader;

		Material_s();
		Material_s(const std::string& texturePath, const std::string& uniformsPath, const std::string& shaderPath);
		~Material_s();


	};

	struct Tag {

		std::string tag;

		Tag();
		Tag(const std::string& tag);
		~Tag();

	};

}
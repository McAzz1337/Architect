#include "component_s.h"

#include "../fileio.h"

namespace archt {




	Transform_s::Transform_s() {}

	Transform_s::~Transform_s() {}




	Mesh_s::Mesh_s() {}

	Mesh_s::Mesh_s(Vertex* verteces, uint32_t vSize, uint32_t* indeces, uint32_t iSize)
		: vbo(verteces, vSize), ibo(indeces, iSize) {}

	Mesh_s::~Mesh_s() {}





	Material_s::Material_s() {}

	Material_s::Material_s(const std::string& texturePath, const std::string& uniformsPath, const std::string& shaderPath)
		: tex(texturePath), shader(shaderPath) {

		std::vector<std::string> uniformsRaw;
		readFileSplit(uniformsPath, uniformsRaw, true);
		
		if (uniformsRaw.size() == 0)
			return;

		uniforms = new Uniform[uniformsRaw.size()];

		for (int i = 0; i < uniformsRaw.size(); i++) {
			std::string components[2];
			split(uniformsRaw[i], '=', components, 2);
			std::vector<std::string> values;
			split(components[1], values, ',');

			switch (values.size()) {
				case 1:
					uniforms[i] = UniformFloat1(components[0], std::stof(values[0]));
					break;
				case 2: {
					glm::vec2 v = { std::stof(values[0]), std::stof(values[1]) };
					uniforms[i] = UniformFloat2(components[0], v);
					break;
				}
				case 3: {
					glm::vec3 v = { std::stof(values[0]), std::stof(values[1]), std::stof(values[2]) };
					uniforms[i] = UniformFloat3(components[0], v);
					break;
				}
				case 4: {
					glm::vec4 v = { std::stof(values[0]), std::stof(values[1]), std::stof(values[2]), std::stof(values[3]) };
					uniforms[i] = UniformFloat4(components[0], v);
					break;
				}
			}

		}

	}

	Material_s::~Material_s() {
		delete[] uniforms;
	}

	
	
	
	
	Tag::Tag() {}

	Tag::Tag(const std::string& tag) : tag(tag) {}

	Tag::~Tag() {}

}
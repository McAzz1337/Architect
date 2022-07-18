#include "glshaderconstants.h"
#include <iostream>

namespace archt {


	uint32_t GLShaderConstants::v_maxTextures = 0;

	const std::string GLShaderConstants::HASH_DEFINE = "#define ";


	const std::string GLShaderConstants::MAX_TEXTURES = HASH_DEFINE + "MAX_TEXTURES";
	
	
	
	
	
	void GLShaderConstants::setConstant(const std::string& name, void* value) {
		
		if (name == MAX_TEXTURES) {
			v_maxTextures = *((uint32_t*) value);
		}
	}

	void GLShaderConstants::modifySahderSource(std::string& src) {
		
		int index = src.find(MAX_TEXTURES);
		if (index != std::string::npos) {
			index += MAX_TEXTURES.length() + 1;
			int end = src.find("\n", index);
			src.replace(src.begin() + index, src.begin() + end, std::to_string(v_maxTextures).c_str());
		}
	}

}
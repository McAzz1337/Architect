#include "glshaderconstants.h"
#include <iostream>

namespace archt {


	uint32_t GLShaderConstants::v_supportedTextures = 0;

	const std::string GLShaderConstants::SUPPORTED_TEXTURES = "supportedTextures";
	
	
	
	
	
	void GLShaderConstants::setConstant(const std::string& name, void* value) {
		
		if (name == SUPPORTED_TEXTURES) {
			v_supportedTextures = *((uint32_t*) value);
		}
	}

	void GLShaderConstants::modifySahderSource(std::string& src) {
		
		int index = src.find(SUPPORTED_TEXTURES);
		while (index != std::string::npos) {
			src.replace(src.begin() + index, src.begin() + index + (SUPPORTED_TEXTURES.length()), std::to_string(v_supportedTextures).c_str());
			index = src.find(SUPPORTED_TEXTURES, index);
		}
	}

}
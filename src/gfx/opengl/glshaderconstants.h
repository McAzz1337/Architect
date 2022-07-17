#pragma once
#include <string>

namespace archt {

	class GLShaderConstants {
		
		static uint32_t v_supportedTextures;
		
	public:
		static const std::string SUPPORTED_TEXTURES;
		
		
		
		GLShaderConstants() = delete;


		static void setConstant(const std::string& name, void* value);

		static void modifySahderSource(std::string& src);
	};
}
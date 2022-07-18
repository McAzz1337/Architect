#pragma once
#include <string>

namespace archt {

	class GLShaderConstants {
		
		static uint32_t v_maxTextures;
		
		static const std::string HASH_DEFINE;

	public:
		static const std::string MAX_TEXTURES;
		
		
		
		GLShaderConstants() = delete;


		static void setConstant(const std::string& name, void* value);

		static void modifySahderSource(std::string& src);
	};
}
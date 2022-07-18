#pragma once

#include <string>

namespace archt {

	class GLTexture {

		uint32_t id = 0;
		int w = 0;
		int h = 0;

	public:
		GLTexture();
		GLTexture(const std::string& path);
		~GLTexture();

		void bind(int index) const;

		static void createEmptyTexture(GLTexture* tex, int width, int height);
		static void createTextureFromData(GLTexture* tex, const unsigned char* data, int width, int height);
		static void flipImage(const unsigned char* src, int width, int height, int comp, unsigned char* dst);
	};



}

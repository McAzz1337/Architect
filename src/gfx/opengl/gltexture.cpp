#include "gltexture.h"

#include "glinclude.h"
#include "gldebug.h"

#include "../stb/stb/stb_image.h"

namespace archt {


	GLTexture::GLTexture() {
	}

	GLTexture::GLTexture(const GLTexture& other) : id(other.id), w(other.w), h(other.h) {

	}

	GLTexture::GLTexture(const std::string& path) : file(path) {

		int comp = 0;
		unsigned char* data = nullptr;
		
		{
			unsigned char* src = stbi_load(path.c_str(), &w, &h, &comp, STBI_rgb_alpha);
			data = new unsigned char[w * comp * h];
			flipImage(src, w, h, comp, data);
			stbi_image_free(src);
		}

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
	

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	
		delete[] data;
	}

	GLTexture::~GLTexture() {
		if (id != 0)
			glDeleteTextures(1, &id);
	}

	void GLTexture::bind(int index) const {
		CALL(glActiveTexture(GL_TEXTURE0 + index));
		CALL(glBindTextureUnit(index, id));
		printf("texture bound at index : %i\n", index);
	}

	void GLTexture::createEmptyTexture(GLTexture* tex, int width, int height) {

		tex->w = width;
		tex->h = height;

		int length = height * width;
		unsigned char* data = new unsigned char[length];
		for (int i = 0; i < length; i++) {
			data[i] = 0;
		}

		glGenTextures(1, &tex->id);
		glBindTexture(GL_TEXTURE_2D, tex->id);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		delete[] data;
	}

	
	void GLTexture::createTextureFromData(GLTexture * tex, const unsigned char* data, int width, int height) {
		
		tex->w = width;
		tex->h = height;

		glGenTextures(1, &tex->id);
		glBindTexture(GL_TEXTURE_2D, tex->id);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	void GLTexture::flipImage(const unsigned char* src, int width, int height, int comp, unsigned char* dst) {
		
		width *= comp;

		for (int y = 0; y < height; y++) {
			int srcI = y * width;
			int dstI = width * height - (y + 1) * width;
			memcpy_s(&dst[dstI], width, &src[srcI], width);
		}
		
	}

}
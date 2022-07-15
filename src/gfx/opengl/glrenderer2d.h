#pragma once

#include "glmesh.h"
#include "buffers.h"
#include "glvertexarray.h"
#include "camera.h"

#include <typeindex>

namespace archt {

	class GLRenderer2D {

		const static int MAX_QUADS;
		const static int MAX_VERTECES ;
		const static int MAX_INDECES;

		static uint32_t currentVertex;
		static uint32_t currentIndex;


		static bool inScene;
		static VBO* vbo;
		static IBO* ibo;
		static GLVertexarray* vao;
		static Camera* cam;
		static GLTexture* texture;

	public:
		GLRenderer2D() = delete;
		static void init();
		static void terminate();

		static void beginScene(Camera* camera);
		static void endScene();

		static void submit(GLMesh* meh);

		static void clear();
		static void render();
		static void flush();


	};


}
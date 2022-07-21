#pragma once

#include "glmesh.h"
#include "buffers.h"
#include "glvertexarray.h"
#include "camera.h"

#include <glm/mat4x4.hpp>

#include <vector>
#include <typeindex>

namespace archt {

	class GLRenderer2D {

		const static int MAX_OBJECTS;
		const static int MAX_VERTECES;
		const static int MAX_INDECES;


		static uint32_t currentVertex;
		static uint32_t currentIndex;
		static int currentTexture;
		static uint32_t currentMatrix;
		static uint32_t currentMesh;

		static GLShader* activeShader;

		static bool inScene;
		static VBO* vbo;
		static IBO* ibo;
		static GLVertexarray* vao;
		static Camera* cam;
		static std::vector<GLMesh*> meshes;
		static std::vector<glm::mat4> matrices;
		static std::vector<GLTexture*> textures;

	public:
		GLRenderer2D() = delete;
		static void init();
		static void terminate();

		static void beginScene(Camera* camera);
		static void endScene();

		static void submit(GLMesh* meh);

		static void clear();
		static void startBatch();
		static void endBatch();

		static void sort();
		static void render();
		static void draw();
		static void flush();

		static int fetchTextureIndex(GLTexture* tex);


	};


}
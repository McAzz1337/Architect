#pragma once

#include "../../ptr.h"
#include "../../entity/entity.h"
#include "../../entity/component/camera_new.h"

#include "../opengl/glvertexarray.h"

namespace archt {

	class Renderer{

		GLVertexarray* vao = nullptr;

	public:
		Renderer();
		~Renderer();

		void clear();
		void render(ptr<Entity> entity, ptr<Camera_new> cam);

	};

}
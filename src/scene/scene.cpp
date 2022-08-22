#include "scene.h"

#include "entity_s.h"

#include "../gfx/opengl/glshader.h"
#include "component_s.h"

namespace archt {



	Scene::Scene() {
		
	}

	Scene::~Scene() {
		printf("Deleted Scene\n");
	}

	Entity_s Scene::createEntity() {
		return Entity_s(registry.create(), this);
	}

	void Scene::deleteEntity(Entity_s entity) {

	}
	

}
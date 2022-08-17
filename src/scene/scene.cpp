#include "scene.h"


namespace archt {



	Scene::Scene() {
	
	}

	Scene::~Scene() {
	
	}

	Entity_s Scene::createEntity() {
		return Entity_s(registry.create());
	}

	void Scene::deleteEntity(const Entity_s& entity) {
		registry.destroy(entity);
	}

}
#pragma once

#include <entt/entt.hpp>
#include "entity_s.h"

namespace archt {

	class Scene {

		entt::registry registry;

	public:
		Scene();
		~Scene();

		Entity_s createEntity();
		void deleteEntity(const Entity_s& entity);

		template<typename T>
		void addComponent(Entity_s entity) {
			registry.emplace<T>(entity);
		}
	};


}
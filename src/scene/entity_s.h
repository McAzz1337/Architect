#pragma once

#include <entt/entt.hpp>

namespace archt {

	class Scene;

	class Entity_s {

		entt::entity id;
		
	public:
		Entity_s();
		Entity_s(entt::entity id);
		~Entity_s();

		inline operator entt::entity() { return id; }
		inline operator const entt::entity() const { return id; }
	};

}
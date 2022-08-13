#include "component.h"

#include "component/camera_new.h"
#include "component/buffers_new.h"

namespace archt {


	void test() {

		std::shared_ptr<Component> c = std::make_shared<Component>();
		
		std::shared_ptr<VBO_new> vbo = std::make_shared<VBO_new>(nullptr, 0);
		std::shared_ptr<IBO_new> ibo = std::make_shared<IBO_new>(nullptr, 0);

		c->addComponent(vbo);
		c->addComponent(ibo);

	}


	Component::Component() {
	}

	Component::~Component() {
	}




}
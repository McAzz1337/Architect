#pragma once

#include <memory>
#include <vector>



namespace archt {


	class Component {

		std::shared_ptr<Component> parent = nullptr;
		std::vector<std::shared_ptr<Component>> children;

	public:
		Component();
		~Component();

		template<class T>
		void addComponent(std::shared_ptr<T> component) {
			if (std::shared_ptr<Component>  c = std::dynamic_pointer_cast<Component>(component)) {
				children.push_back(c);
			}
		}

		template<class T>
		void removeComponent(std::shared_ptr<T> component) {
			if (std::shared_ptr<Component>  c = std::dynamic_pointer_cast<Component>(component)) {
				int size = children.size();
				for (int i = 0; i < size; i++) {
					if (children[i].get() == c.get()) {
						children.erase(children.begin() + i);
						return;
					}
				}
			}

		}





























		template<class T>
		std::shared_ptr<T> getComponent() {
			
			int size = children.size();
			for (int i = 0; i < size; i++) {
				if (std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(children[i])) {
					return t;
				}
			}
			return nullptr;
		}

		template<class T>
		std::vector<std::shared_ptr<T>> getComponents() {
		
			std::vector<std::shared_ptr<T>> list;
			int size = children.size();
			for (int i = 0; i < size; i++) {
				if (std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(children[i])) {
					return t;
				}
			}
			return list;
		}
	};


}
#pragma once
#include <typeindex>

#include "buffers.h"
namespace archt {


	class GLVertexarray {
		uint32_t id = 0;

	public:
		GLVertexarray();
		GLVertexarray(VBO* vbo, IBO* ibo);
		~GLVertexarray();

		void bind() const;

	};





}
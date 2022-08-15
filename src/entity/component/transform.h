#pragma once

#include "../component.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace archt {

	class Transform : public Component {

		glm::mat4 matrix;

	public:
		Transform();
		Transform(float f);
		Transform(const glm::mat4& matrix);
		~Transform();

		void translate(const glm::vec3& t);
		void rotate(float angle, const glm::vec3& axis);
		void scale(const glm::vec3& s);

		void reset();
		Transform inverse() const;

		Transform operator*(const Transform other) const;
		void operator*=(const Transform other);
		void operator<<(const Transform other);

		glm::vec4 operator*(const glm::vec3& v) const ;
		void operator*=(const glm::vec3& v);

		inline const glm::mat4& getMatrix() const { return matrix; }

	};

}
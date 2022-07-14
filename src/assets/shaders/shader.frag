#version 450 core


in vec3 _normal;
in vec2 _uv;


out vec4 color;

void main() {
	color = vec4((_normal.x + 0.5), (_normal.y + 0.5), _normal.z, 1.0);
}
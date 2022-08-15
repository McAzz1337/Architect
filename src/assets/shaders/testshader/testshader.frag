#version 450 core

in vec3 _pos;
in vec3 _normal;
in vec2 _uv;
in int _texId;
in int _matrixId;


out vec4 _out;

void main() {
	_out = vec4(1.0, 1.0, 1.0, 1.0);
}
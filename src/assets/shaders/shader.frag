#version 450 core


in vec3 _normal;
in vec2 _uv;
in unsigned int _texId;

uniform vec4 tint;

uniform sampler2D tex;


out vec4 _out;


void main() {
	
	vec4 color = texture(tex, _uv);
	_out = color * tint;
	//_out = texture(tex, _uv);
}
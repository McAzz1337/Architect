#version 450 core

#define MAX_TEXTURES 32

in vec3 _normal;
in vec2 _uv;
in float _texId;


uniform vec4 tint = vec4(1, 1, 1, 1);
uniform sampler2D tex[MAX_TEXTURES];


out vec4 _out;


void main() {
	highp int index = int(_texId);
	vec4 color = texture(tex[index], _uv);
	
	_out = color * tint;
	//_out = vec4(_texId, _texId, _texId, 1.0);
}
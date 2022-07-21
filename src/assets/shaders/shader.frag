#version 450 core

#define MAX_TEXTURES 32

in vec3 _normal;
in vec2 _uv;
in float _texId;
in float _matrixId;


uniform vec4 tint = vec4(1, 1, 1, 1);
uniform sampler2D tex[MAX_TEXTURES];


out vec4 _out;


void main() {
	highp int index = int(_texId);
	vec4 color = texture2D(tex[index], _uv);
	
	if (color.w == 0.0) {
		discard;
	}
	
	_out = color * tint;
}
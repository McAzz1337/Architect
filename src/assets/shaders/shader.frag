#version 450 core


in vec3 _normal;
in vec2 _uv;
in flat unsigned int _texId;

uniform vec4 tint = vec4(1, 1, 1, 1);
uniform sampler2D tex[supportedTextures];


out vec4 _out;


void main() {
	vec4 color = texture(tex[_texId], _uv);
	_out = color * tint;
	//_out = texture(tex, _uv);
}
#version 450 core


layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in unsigned int texId;

uniform mat4 mvp;

out vec3 _normal;
out vec2 _uv;
out flat unsigned int _texId;


void main() {

	gl_Position = mvp * vec4(pos, 1.0);

	_normal  = normal;
	_uv = uv;
	_texId = texId;
}




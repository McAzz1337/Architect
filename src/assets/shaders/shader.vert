#version 450 core


layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in float texId;

uniform mat4 mvp;
uniform mat4 mvp2;

out vec3 _normal;
out vec2 _uv;
out float _texId;


void main() {

	if (texId == 1) {
		gl_Position = mvp2 * vec4(pos, 1.0);
	}
	else {
		gl_Position = mvp * vec4(pos, 1.0);
	}

	_normal  = normal;
	_uv = uv;
	_texId = texId;
}




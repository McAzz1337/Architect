#version 450 core


in vec3 _normal;
in vec2 _uv;


out vec4 color;


void main() {
	color = vec4(gl_FragCoord.x / 1080.0, gl_FragCoord.y / 720.0, 0.0, 1.0);
}
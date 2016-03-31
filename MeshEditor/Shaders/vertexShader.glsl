#version 330 core

layout(location = 0) in vec4 vertex_modelspace;
layout(location = 1) in vec3 normal_modelspace;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform vec4 vertex_color;

out vec4 normal;
out vec4 position;
out vec4 color;

void main() {
    gl_Position = projection_matrix * view_matrix * vertex_modelspace; 
	position = view_matrix * vertex_modelspace;
	normal = /*projection_matrix * */view_matrix * vec4(normal_modelspace, 0);
	color = vertex_color;
}

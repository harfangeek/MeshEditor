#version 330 core

layout(location = 0) in vec4 vertex_modelspace;
layout(location = 1) in vec3 normal_modelspace;

uniform mat4 myprojection_matrix;
uniform mat4 myview_matrix;
uniform vec4 vertex_color;

out vec4 normal;
out vec4 position;
out vec4 color;

void main() {
    gl_Position = myprojection_matrix * myview_matrix * vertex_modelspace; 
	position = vertex_modelspace;
	normal = /*myprojection_matrix * */myview_matrix * vec4(normal_modelspace, 0);
	color = vertex_color;
}

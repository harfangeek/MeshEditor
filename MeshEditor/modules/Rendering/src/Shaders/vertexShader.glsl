#version 330 core

layout(location = 0) in vec4 vertex_modelspace;
layout(location = 1) in vec3 normal_modelspace;
layout(location = 2) in int vertex_selected;
layout(location = 3) in int edge_selected;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;

out vec4 normal;
out vec4 position;
flat out int selected;

void main() {
    gl_Position = projection_matrix * view_matrix * model_matrix * vertex_modelspace; 
	position = view_matrix * model_matrix * vertex_modelspace;
	normal = /*projection_matrix * */view_matrix * model_matrix * vec4(normal_modelspace, 0);
	
	//if(vertex_selected != 0 || edge_selected != 0) 
	//{
	//	gl_PointSize = 20.0f;
	//	selected = 1;
	//}
	//else
	//	gl_PointSize = 5.0f;
		
}

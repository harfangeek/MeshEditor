#version 330 core

layout(location = 0) in vec4 vertex_modelspace; // position du vertex dans le monde (=environnement = la scène)
layout(location = 1) in vec3 normal_modelspace;

uniform mat4 myprojection_matrix; //c'est juste la projection ex perspective cavalière
uniform mat4 myview_matrix; // matrice de transformation de la position selon la caméra (ex si la camera doit tourner, myview_matric contient cette rotation) 
//uniform mat3 mynormal_matrix; //normal_matrix

out vec3 normal;
out vec4 position;

void main() {
    gl_Position = myprojection_matrix * myview_matrix * vertex_modelspace; 
	position = vertex_modelspace;
	normal = normal_modelspace;
}

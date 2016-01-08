#version 330 core

void main(void)
{
	const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),
									 vec4(-0.25, -0.25, 0.5, 1.0),
									 vec4(0.25, 0.25, 0.5, 1.0));

	gl_Position = vertices[gl_VertexID];
}
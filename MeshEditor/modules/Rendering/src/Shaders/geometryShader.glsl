#version 330 core

layout(points) in;
layout(points, max_vertices = 2) out;

void main()
{
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    EndPrimitive();

	gl_Position = gl_in[0].gl_Position + vec4(1.0f, 1.0f, 1.0f, 1.0f);
	EmitVertex();
    EndPrimitive();
}

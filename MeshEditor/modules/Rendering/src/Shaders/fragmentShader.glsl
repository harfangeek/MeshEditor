#version 330 core

uniform vec4 mesh_color;
uniform uint material_type;
uniform uint light_type;
uniform vec4 light_color;
uniform vec3 light_position;	// For point/directionnal/spot light
uniform vec3 light_direction;	// For directionnal/spot light
uniform float light_angle;		// For spot light

in vec4 normal;
in vec4 position;
flat in int selected;

out vec4 out_color;

void main (void) 
{    
	if(light_type == uint(0) || material_type == uint(1)) // Ambiant light or material without light interaction
	{
		out_color = mesh_color;	
	}
	else if(light_type == uint(1)) // Point light
	{
		vec3 eye_pos = vec3(0,0,0);
		vec3 frag_pos = position.xyz;
		vec3 normal3 = normalize(normal.xyz);
		vec3 eye_dir = normalize(eye_pos - frag_pos);
		vec3 light_dir = normalize (light_position - frag_pos);

		vec3 reflect_dir = normalize(reflect(-light_dir, normal3));
		out_color =  mesh_color * light_color * max(dot(light_dir, normal3), 0.0) +
					 mesh_color * light_color * pow(max(dot(reflect_dir, eye_dir), 0.0), 60);
	}
	else if(light_type == uint(2)) // Directionnal
	{
		vec3 eye_pos = vec3(0,0,0);
		vec3 frag_pos = position.xyz;
		vec3 normal3 = normalize(normal.xyz);
		vec3 eye_dir = normalize(eye_pos - frag_pos);
		vec3 light_dir = normalize (light_position - frag_pos);

		vec3 reflect_dir = normalize(reflect(-light_dir, normal3));
		out_color =  mesh_color * light_color * max(dot(light_dir, normal3), 0.0) +
					 mesh_color * light_color * pow(max(dot(reflect_dir, eye_dir), 0.0), 60);
	}
	else if(light_type == uint(3)) // Spot light : à refaire
	{
		vec3 eye_pos = vec3(0,0,0);
		vec3 frag_pos = position.xyz;
		vec3 normal3 = normalize(normal.xyz);
		vec3 eye_dir = normalize(eye_pos - frag_pos);
		vec3 light_dir = normalize (light_position - frag_pos);

		vec3 reflect_dir = normalize(reflect(-light_dir, normal3));
		out_color =  vec4(0.1,0.1,0.1,0) + 
					 mesh_color * light_color * pow(max(dot(light_dir, normal3), 0.0), 10) +
					 mesh_color * light_color * pow(max(dot(reflect_dir, eye_dir), 0.0), 60);
	}
	else if(light_type == uint(4)) // Silouhette
	{
		vec3 eye_pos = vec3(0,0,0);
		vec3 frag_pos = position.xyz;
		vec3 normal3 = normalize(normal.xyz);
		vec3 eye_dir = normalize(eye_pos - frag_pos);

		float dot_prd = dot(normal3, eye_dir);
		if(abs(dot_prd) < 0.2)
			out_color = mesh_color;
		else
			out_color = vec4(0.0, 0.0, 0.0, 0.0);
	}

	if(selected != 0)
	{
		out_color = vec4(1.0, 1.0, 1.0, 1.0);
	}
}

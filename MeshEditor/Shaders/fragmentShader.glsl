#version 330 core

uniform uint light_type;

in vec4 normal;
in vec4 position;
in vec4 color;

out vec4 out_color;

void main (void) 
{    
	if(light_type == uint(1))
	{
		vec3 eye_pos = vec3(0,0,0);
		vec3 frag_pos = position.xyz;
		vec3 light_pos = vec3(0,0,4);
		vec4 light_color = vec4(1,1,1,0);
		vec3 normal3 = normalize(normal.xyz);
		vec3 eye_dir = normalize(eye_pos - frag_pos);
		vec3 light_dir = normalize (light_pos - frag_pos);

		vec3 reflect_dir = normalize(reflect(-light_dir, normal3));
		out_color =  vec4(0.1,0.1,0.1,0) + 
					 color * light_color * max(dot(light_dir, normal3), 0.0) +
					 color * light_color * pow(max(dot(reflect_dir, eye_dir), 0.0), 60);
	}
	else if(light_type == uint(2))
	{
		vec3 eye_pos = vec3(0,0,0);
		vec3 frag_pos = position.xyz;
		vec3 normal3 = normalize(normal.xyz);
		vec3 eye_dir = normalize(eye_pos - frag_pos);

		float dot_prd = dot(normal3, eye_dir);
		if(abs(dot_prd) < 0.2)
			out_color = color;
		else
			out_color = vec4(0.0, 0.0, 0.0, 0.0);
	}
	else
	{
		out_color = color;	
	}
}
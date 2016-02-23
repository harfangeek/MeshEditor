#version 330 core

in vec4 normal;
in vec4 position;
in vec4 color;
flat in uint light_type;

out vec4 out_color;

void main (void) 
{    
	if(light_type == 0)
	{
		vec3 eyepos = vec3(0,0,0) ;
		vec3 frag_pos = position.xyz;
		vec3 lightpos = vec3(0,0,4);
		vec4 light_color = vec4(1,1,1,0);
		vec3 normal3 = normalize(normal.xyz);
		vec3 eyedir = normalize(eyepos - frag_pos) ;
		vec3 lightdir = normalize (lightpos - frag_pos);

		vec3 reflectdir = normalize(reflect(-lightdir, normal3));
		out_color =  vec4(0.1,0.1,0.1,0) + 
					 color * light_color * max(dot(lightdir, normal3), 0.0) +
					 color * light_color * pow(max(dot(reflectdir, eyedir), 0.0), 60);
	}
	else
	{
		out_color = color;
	}
}
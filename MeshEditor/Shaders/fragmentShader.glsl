#version 330 core

vec4 light_position = vec4(0,0,4,1);
vec4 light_color = vec4(1,1,1,0);
vec4 frag_color = vec4(0.4, 1.0, 0.4, 0);

in vec3 normal;
in vec4 position;
in vec4 color;

out vec4 out_color;

void main (void) 
{        
	/*vec3 eyepos = vec3(0,0,0) ; 

	vec4 _mypos = gl_ModelViewMatrix * position ; 
    vec3 mypos = _mypos.xyz / _mypos.w ;

	vec4 _lightpos = light_position;
   	vec3 lightpos = _lightpos.xyz / _lightpos.w;

	vec3 normal = normalize(gl_NormalMatrix*normal);

	vec3 eyedir = normalize(eyepos - mypos) ;
	vec3 lightdir = normalize (lightpos - mypos) ;

	//if (dot(normal, eyedir) < -0.1) normal = -normal;

	vec3 reflectdir = normalize( reflect(-lightdir, normal) );

    out_color =  vec4(0.1,0.1,0.1,0) + 
					frag_color * light_color * max( dot(lightdir, normal), 0.0) +
					frag_color * light_color * pow( max( dot(reflectdir, eyedir), 0.0 ), 60 );*/
    //out_color = frag_color;
	out_color = color;
}
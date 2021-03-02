#version 330

uniform sampler2D texture_1;
uniform int type;

layout(location = 0) out vec4 out_color;

in vec3 world_position;
in vec3 world_normal;
uniform vec3 light_directions[64];
uniform vec3 light_intensities[64];
uniform vec3 light_positions[64];
uniform vec3 light_colors[64];
uniform int has_light[64];
uniform int is_spot[64];

uniform vec3 eye_position;

uniform vec3 material_ke;
uniform vec3 material_kd;
uniform vec3 material_ks;
uniform vec3 material_shininess;

uniform float cutOffAngle;

in vec2 tex_coord;

void main()
{
	vec4 color = texture2D(texture_1, tex_coord);

	float amb_intensity = 1;

	if(type == 1)
		color =  vec4(1, 1, 0, 1);


	vec3 emissive_light = material_ke;
	vec3 ambient_light = material_kd *amb_intensity* 0.25;
	color *= vec4(emissive_light + ambient_light, 1);

	vec3 V = normalize(eye_position - world_position);
	
	for(int i = 0; i < 64; i++)
	{
		if(has_light[i] == 0)
			continue;

		vec3 L = normalize(light_positions[i] - world_position);
		vec3 H = normalize(L + V);
		vec3 diffuse_light = amb_intensity * material_kd * light_colors[i] * light_intensities[i] * max(dot(world_normal,L), 0);
		vec3 specular_light = vec3(0);

		if (diffuse_light.x > 0 && diffuse_light.y > 0 && diffuse_light.z > 0)
		{
			specular_light = material_ks * amb_intensity * light_colors[i] * light_intensities[i] *
							vec3(pow(max(dot(world_normal, H), 0), material_shininess.x), pow(max(dot(world_normal, H), 0), material_shininess.y),
								pow(max(dot(world_normal, H), 0), material_shininess.z));
		}

		float attenuation = 1 / (pow(distance(world_position, light_positions[i]), 2) + 1);

		if(is_spot[i] == 1)
		{
			float cut_off = radians(cutOffAngle);
			float spot_light = dot(-L, light_directions[i]);
			float spot_light_limit = cos(cut_off);
			float light_att_factor = 0;

			if (spot_light > cos(cut_off))
			{
				// Quadratic attenuation
				float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
				light_att_factor = pow(linear_att, 2);
			
			}

			attenuation *= light_att_factor;
		}

		color += vec4(attenuation * (diffuse_light + specular_light), 1);
	}

	out_color = color;
}
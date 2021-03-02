#version 330
in vec3 frag_normal;

uniform sampler2D texture_1;

layout(location = 0) out vec4 out_color;

in vec2 tex_coord;

void main()
{
	vec4 color = texture2D(texture_1, tex_coord);

	if (color.w < 0.5) {
		discard;
	}
		
	out_color = color;
}
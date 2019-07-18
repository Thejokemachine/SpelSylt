#version 130

uniform sampler2D normal;
uniform sampler2D albedo;

uniform vec3 lightDir;

out vec4 fragColor;

void main()
{
	vec2 uv = gl_TexCoord[0].xy;

	vec3 normalColor = texture(normal, uv).xyz;
	vec4 albedoColor = texture(albedo, uv);

	vec3 color = albedoColor.rgb;

	normalColor = normalize(normalColor * 2.0 - 1.0);
	float strength = dot(normalize(-lightDir), normalColor);

	fragColor = vec4(color + strength, albedoColor.a);
}
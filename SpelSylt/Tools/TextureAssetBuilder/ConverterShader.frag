uniform sampler2D texture;
uniform float scale;

vec4 CalculateNormal(vec4 InFrag, vec2 TexCoord)
{
	//Get Surrounding Heights (height is stored as equal amount in r, g and b. Using r is arbitrary)
	//[-1,-1][0,-1][1,-1]
	//[-1, 0][0, 0][1, 0]
	//[-1, 1][0, 1][1, 1]
	
	float OriginHeight = InFrag.r;
	
	//Tops
	float TopLeft = textureOffset(texture, TexCoord, ivec2(-1, -1)).x;
	float Top = textureOffset(texture, TexCoord, ivec2(0, -1)).x;
	float TopRight = textureOffset(texture, TexCoord, ivec2(1, -1)).x;
	
	//Mid
	float Left = textureOffset(texture, TexCoord, ivec2(-1, 0)).x;
	float Right = textureOffset(texture, TexCoord, ivec2(1, 0)).x;
	
	//Bots
	float BottomLeft = textureOffset(texture, TexCoord, ivec2(-1, 1)).x;
	float Bottom = textureOffset(texture, TexCoord, ivec2(0, 1)).x;
	float BottomRight = textureOffset(texture, TexCoord, ivec2(1, 1)).x;
	
	vec3 Normal;
	Normal.r = scale * -( BottomRight - BottomLeft + 2 * (Right - Left) + TopRight - TopLeft );
	Normal.g = scale * -( TopLeft - BottomLeft + 2 * ( Top - Bottom ) + TopRight - BottomRight );
	Normal.b = 1.0;
	Normal = normalize(Normal);
	
	return vec4(Normal.rgb, 1);
}

void main()
{
	vec2 TexCoord = gl_TexCoord[0].xy;
	vec4 Frag = texture2D(texture, TexCoord);
	
	gl_FragColor = CalculateNormal(Frag, TexCoord);
}
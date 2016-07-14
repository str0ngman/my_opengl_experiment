#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;
out vec2 reverseCoord;
// Texture samplers
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	reverseCoord = vec2(TexCoord.x,1-TexCoord.y);
	// Linearly interpolate between both textures (second texture is only slightly combined)
	color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, reverseCoord), 0.2);
}
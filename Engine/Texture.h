#pragma once

#include "SDL_image.h"

class Texture
{
public:
	Texture(unsigned int width, unsigned int height, int format);
	Texture();
	~Texture();
	void Bind();
	void UnBind();
	void SetParameter(unsigned int target, unsigned int name, int parameter);
	void Create(void* data);
	void CreateFromImage();
	void GenMipMap();
	unsigned int GetTextureUnit();
	void LoadImage(const char* path);

	void SetResolution(unsigned int width, unsigned int height);
	void SetFormat(int format);

private:
	unsigned int dataTexture;
	unsigned int width;
	unsigned int height;
	int format;
	SDL_Surface* Image;
	const char* path;
};
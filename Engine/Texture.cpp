#include "Texture.h"
#include "glew.h"

Texture::Texture(unsigned int width, unsigned int height, int format)
{
	glGenTextures(1, &dataTexture);
	this->width = width;
	this->height = height;
	this->format = format;
}

Texture::Texture()
{
	glGenTextures(1, &dataTexture);
}

Texture::~Texture()
{
	glDeleteTextures(1, &dataTexture);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, dataTexture);
}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetParameter(unsigned int target, unsigned int name, int parameter)
{
	glTexParameteri(target, name, parameter);
}

void Texture::Create(void* data)
{
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
}

void Texture::CreateFromImage()
{
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, Image->pixels);
}

void Texture::GenMipMap()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}

unsigned int Texture::GetTextureUnit(){ return dataTexture; }

void Texture::LoadImage(const char* path)
{
	this->path = path;
	Image = IMG_Load(path);
	Image = SDL_ConvertSurfaceFormat(Image, SDL_PIXELFORMAT_RGBA32, NULL);
	this->width = Image->w;
	this->height = Image->h;
}

void Texture::SetResolution(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
}
void Texture::SetFormat(int format)
{
	this->format = format;
}


#pragma once

#include "glad/glad.h"

#include <unordered_map>
#include <string>
#include <iostream>

class Texture 
{
public:
	static void LoadTexture(const char* name, const char* file, bool isAlpha);
	static Texture& GetTexture(const char* name);
private:
	static std::unordered_map<std::string, Texture> Textures;

public:
	void Gernerate(unsigned int width, unsigned int height, unsigned char* data);
	void Bind(unsigned int slot=0) const;

private:
	unsigned int m_Id;
	unsigned int width, height;
	unsigned int internal_format;
	unsigned int image_format;
	unsigned int wrap_s;
	unsigned int wrap_t;
	unsigned int filter_min;
	unsigned int filter_max;
};
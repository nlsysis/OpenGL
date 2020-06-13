#pragma once

#include "Renderer.h"

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;    /// local storeage for image
	int m_Width, m_Height, m_BPP;    ///BPP -- bytes per pixel.And in this case is 4 since the texture is RGBA

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;  ///the slot means the number of pictures bind at one time.max in 32 of modern GPU and 8 in phones.
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};
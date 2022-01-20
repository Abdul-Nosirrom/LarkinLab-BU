#pragma once
#define STB_IMAGE_IMPLEMENTATION

namespace LarkinLab
{
	class OpenGLTexture
	{
	public:
		OpenGLTexture(const std::string& path);
		~OpenGLTexture();
		
		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
		uint32_t GetTextureID() const { return m_TextureID; }

	private:
		std::string m_Path;
		bool m_IsLoaded;
		uint32_t m_TextureID;
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_InternalFormat;
		uint32_t m_DataFormat;
	};
}


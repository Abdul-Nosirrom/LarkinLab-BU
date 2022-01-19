#pragma once
#define STB_IMAGE_IMPLEMENTATION
namespace LarkinLab
{
	class OpenGLTexture
	{
	public:
		OpenGLTexture();
		
		bool LoadTextureFromFile(const char* filename);
		uint32_t GetTextureID() { return m_textureID; }
		int GetHeight() { return m_texHeight; }
		int GetWidth() { return m_texWidth; }
		void PrintInfo() { LL_CORE_INFO("Found"); }

	private:
		uint32_t m_textureID;
		int m_texWidth = 0, m_texHeight = 0;
	};
}


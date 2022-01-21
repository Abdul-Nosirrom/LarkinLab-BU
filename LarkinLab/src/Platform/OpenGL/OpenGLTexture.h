#pragma once

namespace LarkinLab
{
	class OpenGLTexture
	{
	public:
		OpenGLTexture(const std::string& path);
		~OpenGLTexture();

		void LoadTexture(unsigned char* data);
		void DeleteTexture();

		void UpdateTexture(unsigned char* data);

		void GenerateMipMap();
		void Bind(uint32_t);
		
		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
		uint32_t GetTextureID() const { return m_TextureID; }

		static void* FileDialogCreateHelper(uint8_t* data, int w, int h, char fmt);
		static void FileDialogDestroyHelper(void* ID);

	private:
		std::string m_Path;
		bool m_IsLoaded;
		uint32_t m_TextureID = NULL;
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_InternalFormat;
		uint32_t m_DataFormat;
	};
}


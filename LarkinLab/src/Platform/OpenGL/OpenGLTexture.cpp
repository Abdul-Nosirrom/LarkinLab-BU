#include "llpch.h"
#include "OpenGLTexture.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include "Utilities/ImageLoader.h"

#include <glad/glad.h>

#ifdef LL_PLATFORM_WINDOWS
#include "Utilities/Log.h"
#endif 

namespace LarkinLab
{

	OpenGLTexture::OpenGLTexture(const std::string& path) : m_Path(path)
	{
		int width, height, channels;
		unsigned char* data = ImageLoader::Load(path.c_str(), &width, &height, &channels, 0);

		if (data)
		{
			m_IsLoaded = true;

			m_Width = width;
			m_Height = height;

			GLenum internalFormat = 0, dataFormat = 0;
			if (channels == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (channels == 3)
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}

			m_InternalFormat = internalFormat;
			m_DataFormat = dataFormat;

			// Guarding against this on linux due to stb_image, including Log.h after stb could work
#ifdef LL_PLATFORM_WINDOWS
			LL_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");
#endif

			LoadTexture(data);
			
			ImageLoader::Free(data);
		}
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLTexture::DeleteTexture()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLTexture::LoadTexture(unsigned char* data)
	{
		if (m_TextureID != NULL) glDeleteTextures(1, &m_TextureID);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // THIS FIXED THE STRETCHING ISSUE

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

	}

	void OpenGLTexture::UpdateTexture(unsigned char* data)
	{
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture::GenerateMipMap()
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void OpenGLTexture::Bind(uint32_t ID)
	{
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	void* OpenGLTexture::FileDialogCreateHelper(uint8_t* data, int w, int h, char fmt)
	{
		GLuint tex;

		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, (fmt == 0) ? GL_BGRA : GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		return (void*)tex;
	}

	void OpenGLTexture::FileDialogDestroyHelper(void* ID)
	{
		GLuint texID = (GLuint)((uintptr_t)ID);
		glDeleteTextures(1, &texID);
	}
}



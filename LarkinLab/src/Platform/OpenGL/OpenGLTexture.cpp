#include "llpch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"
#include <glad/glad.h>

namespace LarkinLab
{

	OpenGLTexture::OpenGLTexture(const std::string& path) : m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

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

			LL_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

			glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
			glTextureStorage2D(m_TextureID, 1, internalFormat, m_Width, m_Height);

			glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_TextureID);
	}
}

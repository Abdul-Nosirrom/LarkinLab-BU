#include "llpch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"
#include <glad/glad.h>

namespace LarkinLab
{
	OpenGLTexture::OpenGLTexture()
	{
	}

	bool OpenGLTexture::LoadTextureFromFile(const char* filename)
	{
		unsigned char* image_data = stbi_load(filename, &m_texWidth, &m_texHeight, NULL, 4);
		if (image_data == NULL) return false;

		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);


		// Setup filtering parameters for display
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_texWidth, m_texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		stbi_image_free(image_data);
		
		return true;
	}

}

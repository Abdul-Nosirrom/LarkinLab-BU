#include "llpch.h"
#include "ImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


unsigned char* ImageLoader::Load(const char* filename, int* x, int* y, int* comp, int req_comp)
{
	return stbi_load(filename, x, y, comp, req_comp);
}

void ImageLoader::Free(void* data)
{
	stbi_image_free(data);
}

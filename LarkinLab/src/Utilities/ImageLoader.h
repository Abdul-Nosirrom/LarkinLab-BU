#pragma once

class ImageLoader
{
public:
	static unsigned char* Load(const char* filename, int* x, int* y, int* comp, int req_comp);
	static void Free(void* data);
};


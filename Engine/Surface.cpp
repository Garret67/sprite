#include "Surface.h"
#include "ChiliWin.h"
#include <fstream>
#include <cassert>

Surface::Surface(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);

	BITMAPFILEHEADER bmFileHeader;
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));
}

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	pPixel(new Color[width * height])
{
}

Surface::Surface(const Surface& rhs)
	:
	Surface(rhs.width, rhs.height)
{
	const int nPixel = width * height;
	for (int i = 0; i < nPixel; i++)
	{
		pPixel[i] = rhs.pPixel[i];
	}
}

Surface::~Surface()
{
	delete[] pPixel;
	pPixel = nullptr;
}

Surface& Surface::operator=(const Surface& rhs)
{
	width = rhs.width;
	height = rhs.height;

	delete[] pPixel;
	pPixel = new Color[width * height];

	const int nPixel = width * height;
	for (int i = 0; i < nPixel; i++)
	{
		pPixel[i] = rhs.pPixel[i];
	}

	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);

	pPixel[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);

	return pPixel[y * width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

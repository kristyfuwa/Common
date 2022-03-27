#pragma once
#include <cstdint>
#include <fstream>
#include <vector>


typedef struct
{
	std::uint8_t	identsize;          // size of ID field that follows 18 byte header (0 usually)
	std::uint8_t	colourmaptype;      // type of colour map 0=none, 1=has palette
	std::uint8_t	imagetype;          // type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed

	short			colourmapstart;     // first colour map entry in palette
	short			colourmaplength;    // number of colours in palette
	std::uint8_t	colourmapbits;      // number of bits per palette entry 15,16,24,32

	short			xstart;             // image x origin
	short			ystart;             // image y origin
	short			width;              // image width in pixels
	short			height;             // image height in pixels
	std::uint8_t	bits;               // image bits per pixel 8,16,24,32
	std::uint8_t	descriptor;         // image descriptor bits (vh flip bits)

	// pixel data follows header

} TGA_HEADER;

class TGAImage
{
public:
	enum Format { GRAYSCALE = 1, RGB = 3, RGBA = 4 };
	TGAImage();

	bool read_tga_data(const char* filename);
	bool read_rle_data(FILE* fp);

	void flip_horizontally();
	void flip_vertically();

private:
	int		m_iWidth;
	int		m_iHeight;
	int		m_iBpp;

	std::vector<std::uint8_t>	m_vData;
};


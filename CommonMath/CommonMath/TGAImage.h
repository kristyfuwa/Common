#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

#pragma pack(push,1)
struct TGAHeader {
	std::uint8_t  idlength{};
	std::uint8_t  colormaptype{};
	std::uint8_t  datatypecode{};
	std::uint16_t colormaporigin{};
	std::uint16_t colormaplength{};
	std::uint8_t  colormapdepth{};
	std::uint16_t x_origin{};
	std::uint16_t y_origin{};
	std::uint16_t width{};
	std::uint16_t height{};
	std::uint8_t  bitsperpixel{};
	std::uint8_t  imagedescriptor{};
};
#pragma pack(pop)

//typedef struct
//{
//	std::uint8_t	identsize;          // size of ID field that follows 18 byte header (0 usually)
//	std::uint8_t	colourmaptype;      // type of colour map 0=none, 1=has palette
//	std::uint8_t	imagetype;          // type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed
//
//	short			colourmapstart;     // first colour map entry in palette
//	short			colourmaplength;    // number of colours in palette
//	std::uint8_t	colourmapbits;      // number of bits per palette entry 15,16,24,32
//
//	short			xstart;             // image x origin
//	short			ystart;             // image y origin
//	short			width;              // image width in pixels
//	short			height;             // image height in pixels
//	std::uint8_t	bits;               // image bits per pixel 8,16,24,32
//	std::uint8_t	descriptor;         // image descriptor bits (vh flip bits)
//
//	// pixel data follows header
//
//} TGA_HEADER;

struct TGAColor 
{
	std::uint8_t bgra[4] = { 0,0,0,0 };
	std::uint8_t bytespp = { 0 };

	TGAColor() = default;
	TGAColor(const std::uint8_t R, const std::uint8_t G, const std::uint8_t B, const std::uint8_t A = 255) : bgra{ B,G,R,A }, bytespp(4) { }
	TGAColor(const std::uint8_t *p, const std::uint8_t bpp) : bytespp(bpp) 
	{
		for (int i = bpp; i--; bgra[i] = p[i]);
	}
	std::uint8_t& operator[](const int i) { return bgra[i]; }
};

class TGAImage
{
public:
	enum Format { GRAYSCALE = 1, RGB = 3, RGBA = 4 };
	TGAImage();
	TGAImage(const int w, const int h, const int bpp);

	bool	 read_tga_data(const char* filename);

	void	 flip_horizontally();
	void	 flip_vertically();

	void	 setColor(int x, int y,const TGAColor& c);
	TGAColor getColor(int x, int y)const;

	int		 width()const;
	int		 height()const;
private:
	bool	 load_rle_data(std::ifstream &in);
	bool	 unload_rle_data(std::ofstream &out) const;

private:
	int		m_iWidth;
	int		m_iHeight;
	int		m_iBpp;

	std::vector<std::uint8_t>	m_data;
};


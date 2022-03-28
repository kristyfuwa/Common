#include "TGAImage.h"
#include <iostream>
#include <cstring>

TGAImage::TGAImage()
{

}

TGAImage::TGAImage(const int w, const int h, const int bpp)
{
	m_iWidth = w;
	m_iHeight = h;
	m_iBpp = bpp;
	m_data = std::vector<std::uint8_t>(w*h*bpp, 0);
}

bool TGAImage::read_tga_data(const char* filename)
{
	std::ifstream in;
	in.open(filename, std::ios::binary);
	if (!in.is_open()) {
		std::cerr << "can't open file " << filename << "\n";
		in.close();
		return false;
	}
	TGAHeader header;
	in.read(reinterpret_cast<char *>(&header), sizeof(header));
	if (!in.good()) {
		in.close();
		std::cerr << "an error occured while reading the header\n";
		return false;
	}
	m_iWidth = header.width;
	m_iHeight = header.height;
	m_iBpp = header.bitsperpixel >> 3;
	if (m_iWidth <= 0 || m_iHeight <= 0 || (m_iBpp != GRAYSCALE && m_iBpp != RGB && m_iBpp != RGBA)) {
		in.close();
		std::cerr << "bad m_iBpp (or width/height) value\n";
		return false;
	}
	size_t nbytes = m_iBpp * m_iWidth*m_iHeight;
	m_data = std::vector<std::uint8_t>(nbytes, 0);
	//0£ºÃ»ÓÐÍ¼ÏñÊý¾Ý 1£ºÎ´Ñ¹ËõµÄÑÕÉ«±íÍ¼Ïñ 2£ºÎ´Ñ¹ËõµÄÕæ²ÊÍ¼Ïñ 3£ºÎ´Ñ¹ËõµÄºÚ°×Í¼Ïñ 9£ºRLEÑ¹ËõµÄÑÕÉ«±íÍ¼Ïñ 10£ºRLEÑ¹ËõµÄÕæ²ÊÍ¼Ïñ 11£ºRLEÑ¹ËõµÄºÚ°×Í¼Ïñ
	if (3 == header.datatypecode || 2 == header.datatypecode)
	{
		in.read(reinterpret_cast<char *>(m_data.data()), nbytes);
		if (!in.good()) {
			in.close();
			std::cerr << "an error occured while reading the data\n";
			return false;
		}
	}
	else if (10 == header.datatypecode || 11 == header.datatypecode) {
		if (!load_rle_data(in)) {
			in.close();
			std::cerr << "an error occured while reading the data\n";
			return false;
		}
	}
	else {
		in.close();
		std::cerr << "unknown file format " << (int)header.datatypecode << "\n";
		return false;
	}
	if (!(header.imagedescriptor & 0x20))
		flip_vertically();
	if (header.imagedescriptor & 0x10)
		flip_horizontally();
	std::cerr << m_iWidth << "x" << m_iHeight << "/" << m_iBpp * 8 << "\n";
	in.close();
	return true;
}

void TGAImage::flip_horizontally()
{
	int half = m_iWidth >> 1;
	for (int i = 0; i < m_iHeight; ++i)
	{
		for (int j = 0; j < half; ++j)
		{
			for(int k=0;k<m_iBpp;++k)
				std::swap(m_data[(i*m_iWidth + j)*m_iBpp+k], m_data[(i*m_iWidth + (m_iWidth - 1 - j))*m_iBpp+k]);
		}
	}
}

void TGAImage::flip_vertically()
{
	int half = m_iHeight >> 1;
	for (int i = 0; i < m_iWidth; ++i)
	{
		for (int j = 0; j < half; ++j)
		{
			for (int k = 0; k < m_iBpp; ++k)
				std::swap(m_data[(i*m_iHeight + j)*m_iBpp + k], m_data[(i*m_iHeight + (m_iHeight - 1 - j) + k)]);
		}
	}
}

void TGAImage::setColor(int x, int y, const TGAColor& c)
{
	if (!m_data.size() || x < 0 || y < 0 || x >= m_iWidth || y <= m_iHeight)
		return;
	memcpy(m_data.data() + (y*m_iWidth + x)*m_iBpp, c.bgra, m_iBpp);
	
}

TGAColor TGAImage::getColor(int x, int y)const
{
	if (!m_data.size() || x < 0 || y < 0 || x >= m_iWidth || y <= m_iHeight)
		return TGAColor();
	return TGAColor(m_data.data() + (y*m_iWidth + x)*m_iBpp, m_iBpp);
}

int TGAImage::width() const
{
	return m_iWidth;
}

int TGAImage::height() const
{
	return m_iHeight;
}

bool TGAImage::load_rle_data(std::ifstream &in)
{
	size_t pixelcount = m_iWidth * m_iHeight;
	size_t currentpixel = 0;
	size_t currentbyte = 0;
	TGAColor colorbuffer;
	do {
		std::uint8_t chunkheader = 0;
		chunkheader = in.get();
		if (!in.good()) {
			std::cerr << "an error occured while reading the data\n";
			return false;
		}
		if (chunkheader < 128) {
			chunkheader++;
			for (int i = 0; i < chunkheader; i++) {
				in.read(reinterpret_cast<char *>(colorbuffer.bgra), m_iBpp);
				if (!in.good()) {
					std::cerr << "an error occured while reading the header\n";
					return false;
				}
				for (int t = 0; t < m_iBpp; t++)
					m_data[currentbyte++] = colorbuffer.bgra[t];
				currentpixel++;
				if (currentpixel > pixelcount) {
					std::cerr << "Too many pixels read\n";
					return false;
				}
			}
		}
		else {
			chunkheader -= 127;
			in.read(reinterpret_cast<char *>(colorbuffer.bgra), m_iBpp);
			if (!in.good()) {
				std::cerr << "an error occured while reading the header\n";
				return false;
			}
			for (int i = 0; i < chunkheader; i++) {
				for (int t = 0; t < m_iBpp; t++)
					m_data[currentbyte++] = colorbuffer.bgra[t];
				currentpixel++;
				if (currentpixel > pixelcount) {
					std::cerr << "Too many pixels read\n";
					return false;
				}
			}
		}
	} while (currentpixel < pixelcount);
	return true;
}

bool TGAImage::unload_rle_data(std::ofstream &out) const
{
	const std::uint8_t max_chunk_length = 128;
	size_t npixels = m_iWidth * m_iHeight;
	size_t curpix = 0;
	while (curpix < npixels) {
		size_t chunkstart = curpix * m_iBpp;
		size_t curbyte = curpix * m_iBpp;
		std::uint8_t run_length = 1;
		bool raw = true;
		while (curpix + run_length < npixels && run_length < max_chunk_length) {
			bool succ_eq = true;
			for (int t = 0; succ_eq && t < m_iBpp; t++)
				succ_eq = (m_data[curbyte + t] == m_data[curbyte + t + m_iBpp]);
			curbyte += m_iBpp;
			if (1 == run_length)
				raw = !succ_eq;
			if (raw && succ_eq) {
				run_length--;
				break;
			}
			if (!raw && !succ_eq)
				break;
			run_length++;
		}
		curpix += run_length;
		out.put(raw ? run_length - 1 : run_length + 127);
		if (!out.good()) {
			std::cerr << "can't dump the tga file\n";
			return false;
		}
		out.write(reinterpret_cast<const char *>(m_data.data() + chunkstart), (raw ? run_length * m_iBpp : m_iBpp));
		if (!out.good()) {
			std::cerr << "can't dump the tga file\n";
			return false;
		}
	}
	return true;
}

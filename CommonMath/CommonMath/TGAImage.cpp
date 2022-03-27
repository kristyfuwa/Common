#include "TGAImage.h"
#include <stdio.h>

TGAImage::TGAImage()
{

}

bool TGAImage::read_tga_data(const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
		return false;
	TGA_HEADER tgaHeader;
	int len = fread(&tgaHeader, sizeof(TGA_HEADER), 1, fp);
	if (len <= 0)
	{
		fclose(fp);
		return false;
	}
	m_iWidth = tgaHeader.width;
	m_iHeight = tgaHeader.height;
	m_iBpp = tgaHeader.bits >> 3;

	if (m_iHeight <= 0 || m_iWidth <= 0 || (m_iBpp != RGB && m_iBpp != GRAYSCALE && m_iBpp != RGBA))
	{
		fclose(fp);
		return false;
	}

	int nbytes = m_iBpp * m_iWidth * m_iHeight;
	m_vData = std::vector<std::uint8_t>(nbytes, 0);
	if (tgaHeader.imagetype == 2 || tgaHeader.imagetype == 3)//0��û��ͼ������ 1��δѹ������ɫ��ͼ�� 2��δѹ�������ͼ�� 3��δѹ���ĺڰ�ͼ�� 9��RLEѹ������ɫ��ͼ�� 10��RLEѹ�������ͼ�� 11��RLEѹ���ĺڰ�ͼ��
	{
		len = fread(&m_vData, nbytes, 1, fp);
		if (len <= 0)
		{
			fclose(fp);
			return false;
		}
	}
	else if (tgaHeader.imagetype == 10 || tgaHeader.imagetype == 11)
	{
		if (!read_rle_data(fp))
		{
			fclose(fp);
			return false;
		}
	}
	else
	{
		fclose(fp);
		return false;
	}

	if (!(tgaHeader.descriptor & 0x20))
		flip_vertically();
	if(tgaHeader.descriptor & 0x10)
		flip_horizontally();
	fclose(fp);
	return true;
}

bool TGAImage::read_rle_data(FILE* fp)
{

}

void TGAImage::flip_horizontally()
{

}

void TGAImage::flip_vertically()
{

}

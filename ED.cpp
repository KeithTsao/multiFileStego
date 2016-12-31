#include "ED.h"
using namespace std;

bool encrypt(string path, string message) {
	// Initialization
	bmp image;
	if (image.loadImage(path))
	{
		cout << "File " << path << " not exists, broken or not BMP24" << endl;
		return false;
	}
	uint32_t size = 0, messagesize = message.size();
	image.getsize(&size);
	if (size <messagesize)
	{
		cout << "File " << path << "cannot embed such long string" << endl;
		return false;
	}
	unsigned char m;
	uint32_t x = 0, y = 0,j=0;
	RGB8 pixel;
	unsigned char judge;
	uint32_t i = 0;
	// Seting lesser bits of img to meaning bits of message
	for (; i <messagesize; i++)
	{
		m = message[i];
		for (j = 0; j < 8;j++)
		{
			image.getPixel(x, &pixel);
			judge = (m & 0x80) + (pixel & 0x01);
			if (judge &&judge!=0x81)
			{
				if (pixel == 0xff)
				{
					pixel--;
				}
				else
				{
					pixel++;
				}
				image.setPixel(x, pixel);
			}
			x ++;
            m=m << 1;
		}
		
	}
	path.append(".bmp");
	if(image.saveImage(path))
	{
		cout << "Error saving Image." << endl;
		return false;
	}
	return true;
}

string decrypt(const char* path, const unsigned char stop_symbol) {
	// Initialization
	string message = "";
	bmp image;
	image.loadImage(path);
	uint32_t x = 0,size=0,j,i;
	unsigned char m;
	RGB8 pixel;
	image.getsize(&size);
	// Geting chars from img to message
	for (i = 0; x<size; i++) {

		m = 0x00;
		for(j=0;j<8;j++)
		{
			m = m << 1;
			image.getPixel(x, &pixel);
			m += pixel & 1;
			x ++;
		}

		if (m == stop_symbol) {
			break;
		}
		message.append(1,(char)m);

	}
    return message;
}

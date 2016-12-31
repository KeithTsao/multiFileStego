#pragma once

#include "dataType.h"
#include <string>
using namespace std;
class bmp
{
    public:
    bmp ( void );
    ~bmp ( void );

    // Load an image from a bmp file
	int loadImage ( string path ) ;
    // Save the current bitmap image in a file
	int saveImage ( string path ) ;

    // Set a pixel with cartesian coordinates ( x, y ) and a RGB8 color
	int setPixel ( uint32_t x,RGB8 pix ) ;
    // Get a pixel with cartesian coordinates ( x, y )
	int getPixel ( uint32_t x , RGB8 *pix  );
	
	int getsize(uint32_t *datasize);


    private:
    void allocImage ();

    RGB8 * image;
    uint32_t size;

    fileHeader FileHeader;
};
template <class T>
T numrote(T a)//将长短整形值翻转，弥补memcpy从数组拷贝到整形值时发生的翻转
{
	int s = sizeof(a);
	T temp = 0;

	if (s == 2) {//短整形
		T temp1 = a >> 8 & 0x00ff;
		T temp2 = a & 0x00ff;
		temp = (temp2 << 8 & 0xff00) | (temp1 & 0xff00);
	}
	if (s == 4) {//长整型
		T temp1 = a >> 24 & 0x000000ff;
		T temp2 = a >> 16 & 0x000000ff;
		T temp3 = a >> 8 & 0x000000ff;
		T temp4 = a & 0x000000ff;
		temp = (temp4 << 24 & 0xff000000) |
			(temp3 << 16 & 0x00ff0000) |
			(temp2 << 8 & 0x0000ff00) |
			(temp1 & 0x000000ff);
	}
	a = temp;
	return a;
}



/* End of bmp.h */

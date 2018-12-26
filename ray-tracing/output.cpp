#include <iostream>
#include <fstream>
//#include <jpeglib.h>

#include "output.h"

void output(Screen *getScreen)
{
	std::ofstream ofs("result.ppm");
	ofs << "P3\n"
		<< getScreen->w << " " << getScreen->h << "\n255\n";
	for (int y = 0; y < getScreen->h; y++)
	{
		for (int i = 0; i < getScreen->w; i++)
		{
			int index = y * getScreen->w + i;
			ofs << getScreen->colors[index].R << " " << getScreen->colors[index].G << " " << getScreen->colors[index].B;
			if (i < (getScreen->w) - 1)
			{
				ofs << " ";
			}
		}
		ofs << "\n";
	}
	return;
}
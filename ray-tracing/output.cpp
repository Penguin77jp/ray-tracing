#include <iostream>
#include <fstream>
#include <iostream>
#include <time.h>

//#include <jpeglib.h>

#include "output.h"
#include "debug.h"

void output(Screen *getScreen)
{
	LogColorful("Start outputting",LogColor_enum::Error);
	std::ofstream ofs("result.ppm");
	ofs << "P3\n"
		<< getScreen->w << " " << getScreen->h << "\n255\n";
	int _clockKeep = clock()*0.001;//msc -> sc
	for (int y = 0; y < getScreen->h; y++)
	{
		if (_clockKeep != (int)(clock()*0.001)) {
			std::cout << "Outputting:" << (float)y / getScreen->h*100.0 << "%" << std::endl;
			_clockKeep = clock()*0.001;
		}
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
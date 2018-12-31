#include "output.h"
#include "render.h"
// #include "cpplinq/CppLinq/cpplinq.hpp"

int main()
{
	const int w = 1920*0.25;
	const int h = 1080*0.25;
	const double pov = 0.02;
	Ray cameraRay = Ray(V(), V(0, 0, 1));
	std::vector<Sphere> spheres = {  Sphere(V(300, 300, 150), 100, ColorPix(0, 0, 255), ColorPix(255, 255, 255)) };
	//std::vector<Sphere> spheres = { Sphere(V(0, 0, 150), 100, ColorPix(0, 0, 255), ColorPix(0, 0, 0)), Sphere(V(0, 300, 150), 100, ColorPix(0, 0, 255), ColorPix(255, 255, 255)) };
	Screen screen = Screen(w, h,pov, cameraRay, spheres);
	render(screen);
	output(&screen);
	//system("open result.ppm");
	return 0;
}
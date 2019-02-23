#include <vector>
#include <float.h>
#include <math.h>
#include "def.h"

Screen::Screen(int width, int high, double pov, const Ray &cam, std::vector<Sphere> &spheres)
{
	w = width;
	h = high;
	this->pov = pov;
	for (int i = 0; i < width * high; i++)
	{
		Color a;
		colors.push_back(a);
	}
	cameraRay = cam;
	this->spheres = spheres;
}

int Screen::GetHigh(int index)
{
	return index / w;
}
int Screen::GetWidth(int index)
{
	return index % w;
}

V::V() :
	x(0), y(0), z(0) {}

V::V(double x, double y, double z) :
	x(x), y(y), z(z) {}

V operator+(V a, V b)
{
	return V(a.x + b.x, a.y + b.y, a.z + b.z);
}
V operator-(V a, V b)
{
	return V(a.x - b.x, a.y - b.y, a.z - b.z);
}
V operator*(double a, V b)
{
	return V(a * b.x, a * b.y, a * b.z);
}
V operator/(V a, double b) {
	return V(a.x / b, a.y / b, a.z / b);
}
std::optional<double> operator/(V a, V b) {
	double bai;
	bai = a.x / b.x;
	//«‚Í•‚“®¬””äŠr
	if (fabs(a.y / b.y - bai)  < DBL_EPSILON && fabs(a.z / b.z - bai) < DBL_EPSILON) {
		return bai;
	}
	else {
		return std::nullopt;
	}
}

double Magnitude(V a)
{
	return pow(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2), 0.5);
}

V Normalize(V a) {
	return a / Magnitude(a);
}

double Dot(V a, V b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

std::string V2string(V a)
{
	return "(" + std::to_string(a.x) + "," + std::to_string(a.y) + "," + std::to_string(a.z) + ")";
}

Ray::Ray()
	: o(), d() {}

Ray::Ray(const Ray &ray)
	: o(ray.o), d(ray.d) {}

Ray::Ray(const V & org, const V & dir)
	: o(org), d(dir) {}

Color::Color()
	: R(255), G(0), B(255) {}

Color::Color(double r, double g, double b)
	: R(r), G(g), B(b) {}

Color::Color(const Color &color)
	: R(color.R), G(color.G), B(color.B) {}

Color Color::operator+=(Color a) {
	return Color(this->R+a.R,this->G+a.G,this->B+a.B);
}
Color operator+ (Color a, Color b) {
	return Color(a.R + b.R, a.G+ b.G, a.B + b.B);
}

Color operator*(Color color, double p)
{
	return Color(color.R * p, color.G * p, color.B * p);
}
Color operator*(double p, Color color)
{
	return Color(color.R * p, color.G * p, color.B * p);
}
Color operator*(Color a, Color b) {
	return Color(a.R*b.R, a.G*b.G, a.B*b.B);
}
double Color::Power() {
	double max = 0;
	if (R > max) {
		max = R;
	}
	if (G > max) {
		max = G;
	}
	if (B > max) {
		max = B;
	}
	return max;
}

Sphere::Sphere(V v, double rad, Color col, Color ems)
	: p(v), r(rad), color(col), emission(ems) {}

Sphere::Sphere()
	: p(), r(1), color(), emission() {}
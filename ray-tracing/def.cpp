#include <vector>
#include <float.h>
#include <math.h>
#include "def.h"

Screen::Screen(int width, int high, double cameraDistance, const Ray &cam, std::vector<Sphere> &spheres)
{
	w = width;
	h = high;
	this->cameraDistance = cameraDistance;
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

V V::operator+(V a)
{
	return V(this->x + a.x, this->y + a.y, this->z + a.z);
}

V V::operator+(V a) const
{
	return V(this->x + a.x, this->y + a.y, this->z + a.z);
}



V V::operator-(V a)
{
	return V(this->x - a.x, this->y - a.y, this->z - a.z);
}
V V::operator*(double a)
{
	return V(a * this->x, a * this->y, a * this->z);
}
V V::operator*(double a) const
{
	return V(a * this->x, a * this->y, a * this->z);
}
V V::operator/(double a) {
	return V(this->x / a, this->y / a, this->z / a);
}
V V::operator/(double a) const{
	return V(this->x / a, this->y / a, this->z / a);
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

double V::Magnitude()
{
	return pow(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2), 0.5);
}

V V::Normalize() {
	return V(this->x / this->Magnitude(),this->y / this->Magnitude(), this->z / this->Magnitude());
}

double Dot(V a, V b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

std::string V::V2string()
{
	return "(" + std::to_string(this->x) + "," + std::to_string(this->y) + "," + std::to_string(this->z) + ")";
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

Color operator*(Color color, double p)
{
	return Color(color.R * p, color.G * p, color.B * p);
}
Color operator*(double p, Color color)
{
	return Color(color.R * p, color.G * p, color.B * p);
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
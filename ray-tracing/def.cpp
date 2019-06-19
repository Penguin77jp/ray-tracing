#include <cmath>
#include "def.h"

Screen::Screen(int width, int high, double cameraDistance,const V& cam_center, const V &cam_foward, const V &cam_up, std::vector<Sphere> &spheres)
{
	w = width;
	h = high;
	this->cameraDistance = cameraDistance;
	for (int i = 0; i < width * high; i++)
	{
		Color a;
		colors.push_back(a);
	}
	cameraRay_center = cam_center;
	cameraRay_foward = cam_foward.Normalize();
	cameraRay_up = cam_up.Normalize();
	this->spheres = spheres;
}

int Screen::GetHigh(int index)
{
	return index / w;
}
double Screen::GetHigh01(int index)
{
	return (double)index / w / h;
}
int Screen::GetWidth(int index)
{
	return index % w;
}
double Screen::GetWidth01(int index)
{
	return (double)(index % w) / w;
}

V::V() :
	x(0), y(0), z(0) {}

V::V(double x, double y, double z) :
	x(x), y(y), z(z) {}
V V::operator+(V a) const
{
	return V(this->x + a.x, this->y + a.y, this->z + a.z);
}
V V::operator-(V a) const
{
	return V(this->x - a.x, this->y - a.y, this->z - a.z);
}
V V::operator*(double a) const
{
	return V(a * this->x, a * this->y, a * this->z);
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
double V::Magnitude() const{
	return pow(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2), 0.5);
}

V V::Normalize() const{
	return V(this->x / this->Magnitude(),this->y / this->Magnitude(), this->z / this->Magnitude());
}

double Dot(const V &a,const V &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
V Cross(const V &a, const V &b) {
	return  V(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
}

std::string V::V2string() const
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

Color::Color(int r, int g, int b)
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
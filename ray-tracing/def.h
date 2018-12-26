#pragma once

#include <string>
#include <cmath>
#include <vector>

struct V
{
	double x;
	double y;
	double z;
	V();
	V(double x, double y, double z);
};

V operator+(V a, V b);
V operator-(V a, V b);
V operator*(double a, V b);

double Magnitude(V a);

double Dot(V a, V b);

std::string V2string(V a);

struct Ray
{
	V o;
	V d;
	Ray();
	Ray(const Ray &ray);
	Ray(const V& org, const V& dir);
};

class ColorPix
{
public:
	int R;
	int G;
	int B;
	ColorPix();
	ColorPix(double r, double g, double b);
	ColorPix(const ColorPix &color);
	double Power() {
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
};

ColorPix operator*(ColorPix color, double p);

struct Sphere
{
	V p;
	double r;
	ColorPix color;
	ColorPix emission;
	Sphere(V v, double rad, ColorPix col, ColorPix ems);
	Sphere();
};

class Screen
{
public:
	int w, h;
	std::vector<ColorPix> colors;
	Ray cameraRay;
	std::vector<Sphere> spheres;
	Screen(int, int, const Ray &, std::vector<Sphere> &);
	int GetHigh(int);
	// int GetHigh01(int);
	int GetWidth(int);
	// int GetWidth01(int);
};

struct HitInfo
{
	Sphere hitObject;
	V position;
	V hitObjectNormal;
};
#pragma once

#include <string>
#include <cmath>
#include <vector>
#include <optional>

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
V operator/(V a, double b);
std::optional<double> operator/(V a, V b);

double Magnitude(V a);

V Normalize(V);

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

class Color
{
public:
	int R;
	int G;
	int B;
	Color();
	Color(double r, double g, double b);
	Color(const Color &color);
	double Power();
	Color operator+=(Color);
};
	Color operator+(Color, Color);
	Color operator*(Color, double);
	Color operator*(double ,Color );
	Color operator*(Color, Color);
struct Sphere
{
	V p;
	double r;
	Color color;
	Color emission;
	Sphere(V v, double rad, Color col, Color ems);
	Sphere();
};

class Screen
{
public:
	int w, h;
	double pov;
	std::vector<Color> colors;
	Ray cameraRay;
	std::vector<Sphere> spheres;
	Screen(int, int,double, const Ray &, std::vector<Sphere> &);
	int GetHigh(int);
	// int GetHigh01(int);
	int GetWidth(int);
	// int GetWidth01(int);
};

struct HitInfo
{
	Ray ray;
	Sphere hitObject;
	V position;
	V hitObjectNormal;
	double dot;
	Color color;
};
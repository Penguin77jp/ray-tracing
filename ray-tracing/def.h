#pragma once

#include <string>
#include <cmath>
#include <vector>
#include <optional>

class V
{
public:
	double x;
	double y;
	double z;
	V();
	V(double x, double y, double z);
	V operator+(V a);
	V operator+(V a) const;
	V operator-(V a);
	V operator*(double a);
	V operator*(double a) const;
	V operator/(double a);
	V operator/(double a) const;
	double Magnitude();
	V Normalize();
	std::string V2string();
};

std::optional<double> operator/(V a, V b);

double Dot(V a, V b);


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
};

Color operator*(Color color, double p);
Color operator*(double p,Color color);

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
	std::vector<Color> colors;
	Ray cameraRay;
	double cameraDistance;
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
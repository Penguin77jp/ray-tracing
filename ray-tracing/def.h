#pragma once

#include <string>
#include <vector>
#include <optional>

class V {
public:
	double x;
	double y;
	double z;
	V();
	V(double x, double y, double z);
	V operator+(V a) const;
	V operator-(V a) const;
	V operator*(double a) const;
	V operator/(double a) const;
	double Magnitude() const;
	V Normalize() const;
	std::string V2string() const;
};

std::optional<double> operator/(V a, V b);

double Dot(const V &a,const V &b);
V Cross(const V &a, const V &b);

struct Ray {
	V o;
	V d;
	Ray();
	Ray(const Ray& ray);
	Ray(const V& org, const V& dir);
};

class Color {
public:
	int R;
	int G;
	int B;
	Color();
	Color(int r, int g, int b);
	Color(const Color& color);
	double Power();
};

Color operator*(Color color, double p);
Color operator*(double p, Color color);

struct Sphere {
	V p;
	double r;
	Color color;
	Color emission;
	Sphere(V v, double rad, Color col, Color ems);
	Sphere();
};

class Screen {
public:
	int w, h;
	std::vector<Color> colors;
	V cameraRay_foward;
	V cameraRay_up;
	V cameraRay_center;
	double cameraDistance;
	std::vector<Sphere> spheres;
	Screen(int, int, double, const V&, const V&,const V&, std::vector<Sphere>&);
	int GetHigh(int);
	double GetHigh01(int);
	int GetWidth(int);
	double GetWidth01(int);
};

struct HitInfo {
	Ray ray;
	Sphere hitObject;
	V position;
	V hitObjectNormal;
	double dot;
	Color color;
};
#pragma once


#include "Surface.h"
#include "Vector3D.h"
#include "Ray.h"
#include <vector>

class Sphere : public Surface
{
private:
	Vector3D center;
	double radius;

	double intersectDiscriminant(Ray);
public:
	Sphere();
	Sphere(const Vector3D&, double);

	Vector3D getCenter();
	double getRadius();

	std::vector<double> intersections(Ray) override;
	void transform(Vector3D translation, Vector3D rotation = Vector3D(0, 0, 0)) override;
};
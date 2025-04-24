#ifndef CIRCLEMATH_H
#define CIRCLEMATH_H

#include <vector>
#include <tuple>

struct Point {
    double x, y;
};

std::tuple<double, double, double> convertToStandard(double a, double b, double d);

std::vector<Point> circleIntersections(double x0, double y0, double r0,
                                       double x1, double y1, double r1);

#endif // CIRCLEMATH_H

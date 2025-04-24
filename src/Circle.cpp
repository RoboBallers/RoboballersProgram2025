#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <Circle.h>

// Converts (x + a)^2 + (y + b)^2 = d^2  into center and radius
std::tuple<double, double, double> convertToStandard(double a, double b, double d) {
    double x_center = -a;
    double y_center = -b;
    double radius = d;
    return {x_center, y_center, radius};
}

std::tuple<double, double, double> convertToStandard(double a, double b, double d) {
    return {-a, -b, d};
}

std::vector<Point> circleIntersections(double x0, double y0, double r0,
                                       double x1, double y1, double r1) {
    std::vector<Point> intersections;

    double dx = x1 - x0;
    double dy = y1 - y0;
    double d = std::sqrt(dx * dx + dy * dy);

    if (d > r0 + r1 || d < fabs(r0 - r1)) return intersections;

    double a = (r0*r0 - r1*r1 + d*d) / (2*d);
    double h = std::sqrt(r0*r0 - a*a);

    double x2 = x0 + a * (dx / d);
    double y2 = y0 + a * (dy / d);

    double rx = -dy * (h / d);
    double ry = dx * (h / d);

    intersections.push_back({x2 + rx, y2 + ry});
    if (d != r0 + r1 && d != fabs(r0 - r1))
        intersections.push_back({x2 - rx, y2 - ry});

    return intersections;
}

    // Circle 1: (x + 2)^2 + (y + 3)^2 = 5^2
    // Circle 2: (x - 1)^2 + (y + 1)^2 = 4^2
    

    // if (points.empty()) {
    //     std::cout << "No intersection\n";
    // } else {
    //     for (const auto& p : points) {
    //         std::cout << "Intersection at: (" << p.x << ", " << p.y << ")\n";
    //     }
    // }
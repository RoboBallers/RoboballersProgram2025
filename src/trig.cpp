#include <trig.h>
#include <math.h>

double Trig::toRadians(double degrees) {
    return degrees * (M_PI / 180);
}

double Trig::Cos(double degrees) {
    return cos(toRadians(degrees));
}

double Trig::Sin(double degrees) {
    return sin(toRadians(degrees));
}

double Trig::avg(double a, double b) {
    return (a + b) / 2;
}


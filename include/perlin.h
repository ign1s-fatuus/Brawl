#ifndef PERLIN_HEADER
#define PERLIN_HEADER

double rawnoise(int n);

double noise2d(int x, int y, int octave, int seed);

double interpolate(double a, double b, double x);

double smooth2d(double x, double y, int octave, int seed);

double pnoise2d(double x, double y, double persistence, int octaves, int seed);

#endif
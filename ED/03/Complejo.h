#ifndef COMPLEJO
#define COMPLEJO

#include <iostream>
#include <array>

class Complejo {
    float real, imaginario;

public:
    Complejo(float r, float i) : real(r), imaginario(i) {};

    bool mandelbrot(int iteraciones, Complejo c) {
        int i = 0;
        bool mandelbort = true;
        Complejo j(0, 0);
        while (i < iteraciones && mandelbort) {
            j = j * j + c;
            if (modulo(j) > 2) mandelbort = false;
            i++;
        }
        return mandelbort;
    }

    Complejo& operator +(Complejo const& other) {
        real += other.real;
        imaginario += other.imaginario;
        return *this;
    }

    Complejo& operator *(Complejo const& other) {
        real = real * other.real - imaginario * other.imaginario;
        imaginario = real * other.imaginario + other.real * imaginario;
        return *this;
    }

    double modulo(Complejo j) {
        double mod = sqrt(j.real * j.real + j.imaginario * j.imaginario);
        return mod;
    }
};

#endif

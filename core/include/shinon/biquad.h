// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2026 add000
// Part of Shinon (深音)
#pragma once
#include <cmath>
#include <complex>

namespace shinon {

struct BiquadCoeffs {
    double b0 = 1, b1 = 0, b2 = 0, a1 = 0, a2 = 0;  // normalized (a0 = 1)
};

// RBJ Audio EQ Cookbook peaking filter.
inline BiquadCoeffs makePeaking(double fs, double f0, double gainDb, double q) {
    const double pi = 3.14159265358979323846;
    const double A = std::pow(10.0, gainDb / 40.0);
    const double w0 = 2.0 * pi * f0 / fs;
    const double alpha = std::sin(w0) / (2.0 * q);
    const double cw = std::cos(w0);
    const double a0 = 1.0 + alpha / A;
    BiquadCoeffs c;
    c.b0 = (1.0 + alpha * A) / a0;
    c.b1 = (-2.0 * cw) / a0;
    c.b2 = (1.0 - alpha * A) / a0;
    c.a1 = (-2.0 * cw) / a0;
    c.a2 = (1.0 - alpha / A) / a0;
    return c;
}

// Magnitude response in dB at frequency f (used by FR editor and fitter).
inline double magnitudeDb(const BiquadCoeffs& c, double fs, double f) {
    const double pi = 3.14159265358979323846;
    const std::complex<double> z1 = std::polar(1.0, -2.0 * pi * f / fs);
    const std::complex<double> z2 = z1 * z1;
    const auto num = c.b0 + c.b1 * z1 + c.b2 * z2;
    const auto den = 1.0 + c.a1 * z1 + c.a2 * z2;
    return 20.0 * std::log10(std::abs(num / den));
}

// Transposed Direct Form II, float64 state for stability at low frequencies.
class Biquad {
public:
    void setCoeffs(const BiquadCoeffs& c) { c_ = c; }
    void reset() { z1_ = z2_ = 0; }
    inline float process(float x) {
        const double in = x;
        const double out = c_.b0 * in + z1_;
        z1_ = c_.b1 * in - c_.a1 * out + z2_;
        z2_ = c_.b2 * in - c_.a2 * out;
        return static_cast<float>(out);
    }
private:
    BiquadCoeffs c_;
    double z1_ = 0, z2_ = 0;
};

}  // namespace shinon

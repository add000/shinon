// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright (c) 2026 add000
#include <cmath>
#include <cstdio>
#include "shinon/biquad.h"

static int failures = 0;
#define CHECK_NEAR(a, b, tol) do { double _a=(a), _b=(b); \
  if (std::fabs(_a-_b) > (tol)) { std::printf("FAIL %s:%d %f vs %f\n", __FILE__, __LINE__, _a, _b); ++failures; } } while (0)

int main() {
    const double fs = 48000.0;
    // Peaking filter: gain at center frequency must equal requested gain.
    auto c = shinon::makePeaking(fs, 1000.0, 6.0, 1.0);
    CHECK_NEAR(shinon::magnitudeDb(c, fs, 1000.0), 6.0, 1e-6);
    // Far from center the response approaches 0 dB.
    CHECK_NEAR(shinon::magnitudeDb(c, fs, 20.0), 0.0, 0.1);
    // Zero gain = unity (flat).
    auto flat = shinon::makePeaking(fs, 1000.0, 0.0, 1.0);
    CHECK_NEAR(shinon::magnitudeDb(flat, fs, 3000.0), 0.0, 1e-9);
    // Time-domain filter on a DC-free impulse stays finite.
    shinon::Biquad bq; bq.setCoeffs(c);
    double sum = 0; for (int i = 0; i < 1000; ++i) sum += std::fabs(bq.process(i == 0 ? 1.0f : 0.0f));
    CHECK_NEAR(std::isfinite(sum) ? 1.0 : 0.0, 1.0, 0.0);
    if (failures == 0) std::printf("OK\n");
    return failures;
}

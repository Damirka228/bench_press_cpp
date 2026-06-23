#include "calculator.h"
#include <cmath>

Results Calculator :: calculate (double weight, int reps) {
    Results r;
    r.epley =  weight * (1 + reps / 30.0);
    r.brzycki =  weight * (36 / (37 - reps));
    r.lander = (100 * weight) / (101.3 - 2.67123 * reps);
    r.lombardi = weight * pow(reps, 0.1);
    r.mayhew = (100 * weight) / (52.2 + 41.9 * exp(-0.055 * reps));
    r.oconner = weight * (1 + reps / 40.0);
    r.watan = (100 * weight) / (48.8 + 53.8 * exp(-0.075 * reps));
    r.average = (r.epley + r.brzycki + r.lander + r.lombardi + r.mayhew + r.oconner + r.watan) / 7;
    return r;
}
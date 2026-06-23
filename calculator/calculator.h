#pragma once
struct Results
{
    double epley;
    double brzycki;
    double lander;
    double lombardi;
    double mayhew;
    double oconner;
    double watan;
    int average;
    double weight;
    int reps;
};



class Calculator {
public:
    Results calculate(double weight, int reps);
};
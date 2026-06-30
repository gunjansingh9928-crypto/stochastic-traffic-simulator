#pragma once
#include <random>

class RequestGenerator {
public:
    explicit RequestGenerator(double lambda, unsigned int seed = 1234);

    double next_arrival_time(double current_time);
    int next_request_id();

private:
    double lambda;
    int counter;
    std::mt19937 rng;
    std::exponential_distribution<double> arrival_dist;
};

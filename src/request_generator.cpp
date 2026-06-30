#include "request_generator.h"

RequestGenerator::RequestGenerator(double lambda, unsigned int seed)
    : lambda(lambda), counter(0), rng(seed), arrival_dist(lambda) {}

double RequestGenerator::next_arrival_time(double current_time) {
    return current_time + arrival_dist(rng);
}

int RequestGenerator::next_request_id() {
    return ++counter;
}

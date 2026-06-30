#include "logger.h"
#include <iostream>
#include <numeric>
#include <iomanip>

void Logger::record_wait(double wait_time) {
    wait_times.push_back(wait_time);
}

void Logger::record_drop() {
    ++dropped;
}

void Logger::record_arrival() {
    ++arrivals;
}

double Logger::average_wait_time() const {
    if (wait_times.empty()) return 0.0;
    return std::accumulate(wait_times.begin(), wait_times.end(), 0.0) / wait_times.size();
}

double Logger::drop_rate() const {
    if (arrivals == 0) return 0.0;
    return (double)dropped / arrivals;
}

int Logger::total_arrivals() const { return arrivals; }
int Logger::total_dropped() const { return dropped; }

void Logger::print_summary(double sim_time, double idle_fraction) const {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\n===== Simulation Results =====\n";
    std::cout << "Total simulation time   : " << sim_time << " s\n";
    std::cout << "Total arrivals          : " << arrivals << "\n";
    std::cout << "Total dropped           : " << dropped << "\n";
    std::cout << "Drop rate               : " << drop_rate() * 100.0 << " %\n";
    std::cout << "Average waiting time    : " << average_wait_time() << " s\n";
    std::cout << "Server idle fraction    : " << idle_fraction * 100.0 << " %\n";
    std::cout << "==============================\n";
}

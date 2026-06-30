#pragma once
#include <vector>

class Logger {
public:
    void record_wait(double wait_time);
    void record_drop();
    void record_arrival();

    double average_wait_time() const;
    double drop_rate() const;
    int total_arrivals() const;
    int total_dropped() const;
    void print_summary(double sim_time, double idle_fraction) const;

private:
    std::vector<double> wait_times;
    int dropped = 0;
    int arrivals = 0;
};

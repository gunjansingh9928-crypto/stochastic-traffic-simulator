#include <iostream>
#include <string>
#include <queue>
#include <cstdlib>

#include "event_queue.h"
#include "server.h"
#include "request_generator.h"
#include "logger.h"

// Simple arg parser
double get_arg(int argc, char* argv[], const std::string& flag, double def) {
    for (int i = 1; i < argc - 1; ++i)
        if (std::string(argv[i]) == flag)
            return std::stod(argv[i + 1]);
    return def;
}

int main(int argc, char* argv[]) {
    double lambda        = get_arg(argc, argv, "--lambda", 5.0);
    double mu            = get_arg(argc, argv, "--mu", 6.0);
    int    num_servers   = (int)get_arg(argc, argv, "--servers", 3.0);
    int    max_cycles    = (int)get_arg(argc, argv, "--cycles", 100000.0);
    double overflow_prob = get_arg(argc, argv, "--overflow-prob", 0.3);
    int    queue_cap     = (int)get_arg(argc, argv, "--queue-cap", 50.0);

    std::cout << "Starting simulation: lambda=" << lambda
              << " mu=" << mu << " servers=" << num_servers
              << " cycles=" << max_cycles << "\n";

    RequestGenerator gen(lambda);
    ServerPool pool(num_servers, mu);
    EventQueue eq;
    Logger logger;

    // Waiting queue: stores (arrival_time, request_id)
    std::queue<std::pair<double, int>> waiting;

    double current_time = 0.0;
    int cycles_done = 0;

    // Seed first arrival
    double first_arrival = gen.next_arrival_time(0.0);
    eq.push({first_arrival, EventType::ARRIVAL, gen.next_request_id()});

    while (cycles_done < max_cycles && !eq.empty()) {
        Event ev = eq.pop();
        current_time = ev.time;

        if (ev.type == EventType::ARRIVAL) {
            logger.record_arrival();
            int idle = pool.find_idle_server();

            if (idle >= 0) {
                // Serve immediately
                pool.assign(idle, current_time);
                logger.record_wait(0.0);
                eq.push({pool.finish_time(idle), EventType::DEPARTURE, ev.request_id});
            } else if ((int)waiting.size() < queue_cap) {
                // Join waiting queue
                waiting.push({current_time, ev.request_id});
            } else {
                // Overflow — reroute with conditional probability
                double r = (double)rand() / RAND_MAX;
                if (r < overflow_prob) {
                    // Rerouted (treated as served after delay)
                    logger.record_wait(0.5);
                } else {
                    // Dropped
                    logger.record_drop();
                    eq.push({current_time, EventType::OVERFLOW, ev.request_id});
                }
            }

            // Schedule next arrival
            double next = gen.next_arrival_time(current_time);
            eq.push({next, EventType::ARRIVAL, gen.next_request_id()});

        } else if (ev.type == EventType::DEPARTURE) {
            ++cycles_done;

            // Serve next waiting request if any
            if (!waiting.empty()) {
                auto [arr_time, req_id] = waiting.front();
                waiting.pop();
                int idle = pool.find_idle_server();
                if (idle >= 0) {
                    pool.assign(idle, current_time);
                    logger.record_wait(current_time - arr_time);
                    eq.push({pool.finish_time(idle), EventType::DEPARTURE, req_id});
                }
            }
        }
        // OVERFLOW events are logged only
    }

    double idle_frac = pool.total_idle_fraction(current_time);
    logger.print_summary(current_time, idle_frac);

    return 0;
}

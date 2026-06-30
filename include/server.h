#pragma once
#include <vector>
#include <random>

class Server {
public:
    explicit Server(double mu, unsigned int seed);

    bool is_idle() const;
    void start_service(double current_time);
    double finish_time() const;
    void release();
    double idle_time() const;

    double mu;

private:
    bool idle;
    double service_end_time;
    double total_idle_time;
    double last_release_time;
    std::mt19937 rng;
    std::exponential_distribution<double> service_dist;
};

class ServerPool {
public:
    ServerPool(int num_servers, double mu);

    int find_idle_server() const;
    void assign(int server_id, double current_time);
    double release(int server_id);
    double finish_time(int server_id) const;
    double total_idle_fraction(double sim_time) const;
    int num_servers() const;

private:
    std::vector<Server> servers;
};

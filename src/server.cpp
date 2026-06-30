#include "server.h"
#include <stdexcept>
#include <numeric>

Server::Server(double mu, unsigned int seed)
    : mu(mu), idle(true), service_end_time(0.0),
      total_idle_time(0.0), last_release_time(0.0),
      rng(seed), service_dist(mu) {}

bool Server::is_idle() const { return idle; }

void Server::start_service(double current_time) {
    total_idle_time += current_time - last_release_time;
    double duration = service_dist(rng);
    service_end_time = current_time + duration;
    idle = false;
}

double Server::finish_time() const { return service_end_time; }

void Server::release() {
    idle = true;
    last_release_time = service_end_time;
}

double Server::idle_time() const { return total_idle_time; }

ServerPool::ServerPool(int num_servers, double mu) {
    for (int i = 0; i < num_servers; ++i)
        servers.emplace_back(mu, 42 + i);
}

int ServerPool::find_idle_server() const {
    for (int i = 0; i < (int)servers.size(); ++i)
        if (servers[i].is_idle()) return i;
    return -1;
}

void ServerPool::assign(int server_id, double current_time) {
    servers[server_id].start_service(current_time);
}

double ServerPool::release(int server_id) {
    double ft = servers[server_id].finish_time();
    servers[server_id].release();
    return ft;
}

double ServerPool::finish_time(int server_id) const {
    return servers[server_id].finish_time();
}

double ServerPool::total_idle_fraction(double sim_time) const {
    double total_idle = 0.0;
    for (const auto& s : servers)
        total_idle += s.idle_time();
    return total_idle / (sim_time * servers.size());
}

int ServerPool::num_servers() const { return (int)servers.size(); }

# Stochastic Traffic Simulator & Queue Manager

![Build: passing](https://img.shields.io/badge/build-passing-brightgreen)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![Self Project](https://img.shields.io/badge/project-self%20directed-lightgrey)
![Cycles](https://img.shields.io/badge/cycles-100K%2B-orange)

An **event-driven backend simulation** that models queue behavior under unpredictable traffic loads. Built with a modular, object-oriented architecture using **Priority Queues** to track and process events. Simulates real-world network/server queuing scenarios and validates results against theoretical M/M/1 and M/M/c models.

| Metric | Result |
|---|---|
| Request cycles simulated | 100,000+ |
| Runtime (clean memory) | < 10 seconds |
| Variance vs. M/M/c theory | < 2% |

---

## Architecture

The simulator is composed of four loosely-coupled modules:

- **Event Engine** — A min-heap priority queue processes events in chronological order. Arrivals, departures, and queue overflows are dispatched as typed events.
- **Request Generator** — Models incoming traffic as a **Poisson process** (inter-arrival times drawn from an exponential distribution with rate λ).
- **Server Pool** — Multiple servers with service times drawn from an **Exponential distribution** (rate μ). Routing uses conditional probabilities on queue overflow.
- **Data Logger** — Tracks average waiting time, server idle states, and request drop rates across all simulation cycles.

---

## Getting Started

### Prerequisites

- C++17 compiler (g++ or clang++)
- CMake 3.15+

### Build

```bash
git clone https://github.com/yourusername/stochastic-traffic-simulator.git
cd stochastic-traffic-simulator
mkdir build && cd build
cmake ..
make
```

### Run

```bash
./traffic_sim --lambda 5 --mu 6 --servers 3 --cycles 100000
```

---

## Parameters

| Flag | Description |
|---|---|
| `--lambda` | Arrival rate (requests/sec) — Poisson process parameter |
| `--mu` | Service rate per server — Exponential service time parameter |
| `--servers` | Number of parallel servers (M/M/c configuration) |
| `--cycles` | Total request cycles to simulate |
| `--overflow-prob` | Conditional rerouting probability on queue overflow |

---

## Results

- Simulated **100,000+ request cycles** with clean memory management in under 10 seconds.
- Matched simulated drop rates against theoretical **M/M/1** and **M/M/c** queuing models within **2% variance**.
- Data-logging module correctly tracks average waiting time, idle server states, and drop rates across all traffic loads.

---

## Theoretical Validation

Results are compared against closed-form solutions from queuing theory:

- **M/M/1** — Single server, Poisson arrivals, Exponential service. Utilization ρ = λ/μ, mean queue length L = ρ/(1−ρ).
- **M/M/c** — c parallel servers. Erlang-C formula used for wait probability; steady-state metrics derived analytically.

---

## Project Structure

```
stochastic-traffic-simulator/
├── src/              # Core simulation engine: event loop, priority queue, routing
├── include/          # Header files for Queue, Server, Logger, and Event structs
├── tests/            # Unit tests: M/M/1 theoretical validation, drop rate checks
├── CMakeLists.txt    # CMake build config with test targets
└── README.md
```

---

*Self-directed systems programming project · Dec 2025 – Apr 2026*

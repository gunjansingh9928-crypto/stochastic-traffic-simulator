#pragma once
#include <queue>
#include <functional>

enum class EventType {
    ARRIVAL,
    DEPARTURE,
    OVERFLOW
};

struct Event {
    double time;
    EventType type;
    int request_id;

    bool operator>(const Event& other) const {
        return time > other.time;
    }
};

class EventQueue {
public:
    void push(const Event& e);
    Event pop();
    bool empty() const;
    size_t size() const;

private:
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> pq;
};

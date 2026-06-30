#include "event_queue.h"

void EventQueue::push(const Event& e) {
    pq.push(e);
}

Event EventQueue::pop() {
    Event e = pq.top();
    pq.pop();
    return e;
}

bool EventQueue::empty() const {
    return pq.empty();
}

size_t EventQueue::size() const {
    return pq.size();
}

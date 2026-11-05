"""Deterministic non-preemptive CPU scheduling simulation."""
from collections import deque

def simulate(jobs, policy="fcfs", quantum=2):
    if policy not in ("fcfs", "sjf", "rr"):
        raise ValueError("unsupported policy")
    if type(quantum) is not int or quantum <= 0:
        raise ValueError("quantum must be positive integer")
    seen = set()
    pending = []
    for job in jobs:
        name, arrival, burst = job["id"], job["arrival"], job["burst"]
        if not isinstance(name, str) or not name or name in seen:
            raise ValueError("job IDs must be unique nonempty strings")
        if type(arrival) is not int or arrival < 0 or type(burst) is not int or burst <= 0:
            raise ValueError("arrival must be nonnegative and burst positive integers")
        seen.add(name)
        pending.append((arrival, len(pending), name, burst))
    pending.sort()
    remaining = {name: burst for _, _, name, burst in pending}
    completion = {}
    first = {}
    timeline = []
    clock = 0
    ready = deque()
    i = 0
    while len(completion) < len(pending):
        while i < len(pending) and pending[i][0] <= clock:
            ready.append(pending[i])
            i += 1
        if not ready:
            clock = pending[i][0]
            continue
        if policy == "sjf":
            chosen = min(ready, key=lambda j: (j[3], j[0], j[1]))
            ready.remove(chosen)
        else:
            chosen = ready.popleft()
        arrival, order, name, burst = chosen
        first.setdefault(name, clock)
        duration = min(quantum, remaining[name]) if policy == "rr" else remaining[name]
        start = clock
        clock += duration
        remaining[name] -= duration
        timeline.append({"id": name, "start": start, "end": clock})
        while i < len(pending) and pending[i][0] <= clock:
            ready.append(pending[i])
            i += 1
        if remaining[name]:
            ready.append(chosen)
        else:
            completion[name] = clock
    metrics = {}
    for arrival, _, name, burst in pending:
        turnaround = completion[name] - arrival
        metrics[name] = {"completion": completion[name], "turnaround": turnaround,
                         "waiting": turnaround - burst, "response": first[name] - arrival}
    return {"policy": policy, "timeline": timeline, "metrics": metrics}

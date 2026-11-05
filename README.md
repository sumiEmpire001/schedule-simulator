# schedule-simulator

Simulates FCFS, shortest-job-first (non-preemptive), and round-robin CPU scheduling. Returns an execution timeline and per-job waiting, response, turnaround, and completion times. All times are integer ticks. No context-switch overhead, priority scheduling, or real operating-system execution.

## Run

Python 3.10+; no third-party dependencies.

```bash
python -m unittest discover -s tests -v
```

## Python example

```python
from schedule_simulator import simulate
print(simulate([{"id":"A","arrival":0,"burst":3}], policy="rr", quantum=1))
```

GitHub Actions runs tests on Python 3.10, 3.12, and 3.13. Check the latest run before claiming verification.

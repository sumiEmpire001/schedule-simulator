# RoundRobin C++11 reference

Portable fixed-capacity C++11 round-robin scheduler simulation alongside the original Python CPU scheduling simulator. This implementation handles burst-only jobs (all arrive at time zero); unlike Python's full simulator it does not model arrivals, FCFS or SJF.

Build on a host: `cmake -S cpp -B build && cmake --build build && ctest --test-dir build --output-on-failure`.

The header is standard C++11 and suitable for Arduino Uno / ESP32 algorithm integration, but no device firmware or GPIO sketch is included. For board use, supply validated sensor/input data, watchdogs and fail-safe outputs. Hardware and board toolchain builds are unverified.

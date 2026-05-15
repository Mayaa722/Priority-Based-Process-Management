# Priority-Based Process Management in xv6
> Modifying the xv6 OS scheduler to support process priorities, aging, and dynamic scheduling modes.

---

## What is this project?

xv6 normally schedules processes using **round-robin** — every process takes turns getting the CPU no matter how important it is. A critical process has to wait in line behind everything else.

This project replaces the default xv6 scheduler with a **priority-based process management system**.

Each process receives a priority value from:

- **0** → Highest priority
- **19** → Lowest priority

The scheduler always selects the highest-priority runnable process first. To prevent starvation, the project also implements **aging**, allowing long-waiting processes to gradually gain higher priority over time.

---

## What I Built

- A priority-aware scheduler that always executes the highest priority process first
- 4 scheduling modes switchable at runtime
- Aging support to prevent starvation
- 3 new system calls for runtime process management
- Multiple testing programs to validate scheduler behavior

---

## The 4 Scheduling Modes

| Mode | Name | Description |
|------|------|-------------|
| `0` | Non-Preemptive Priority | Highest-priority process runs until it voluntarily yields |
| `1` | Preemptive Priority | Higher-priority processes can interrupt running processes |
| `2` | Round-Robin | Processes with equal priority share CPU fairly |
| `3` | Aging Scheduler *(Default)* | Priority scheduling with automatic aging every 50 ticks |

> Mode 3 is the default scheduler when xv6 boots.

---

## System Calls Added

| System Call | Syscall # | Description |
|-------------|-----------|-------------|
| `setpriority(int pid, int p)` | `22` | Set the priority of any process by PID |
| `getpriority(int pid)` | `24` | Return the priority of any process by PID |
| `setsched(int mode)` | `25` | Change the scheduler mode at runtime |

---

## Files Modified

| File | Changes |
|------|---------|
| `kernel/proc.h` | Added `priority` and `waited_ticks` fields |
| `kernel/proc.c` | Reimplemented `scheduler()` and added priority selection logic |
| `kernel/trap.c` | Added preemption logic for Mode 1 in `usertrap()` and `kerneltrap()` |
| `kernel/syscall.h` | Registered new syscall numbers |
| `kernel/syscall.c` | Added syscall mappings |
| `kernel/sysproc.c` | Implemented scheduler-related system calls |
| `user/user.h` | Declared new user-space functions |
| `user/usys.pl` | Generated syscall stubs |
| `user/priotest.c` | Priority scheduling test |
| `user/schedtest.c` | Scheduler mode test |
| `user/finaltest.c` | Complete system demonstration |

---

## How to Run

### Boot xv6

```bash
make qemu
```

### Run Tests Inside xv6

```bash
$ priotest
$ schedtest
$ finaltest
```

### Exit xv6

```bash
Ctrl + A, then X
```

---

## Test Results

### `priotest` — Priority Scheduling

Two processes: HIGH priority (`5`) vs LOW priority (`15`)

```text
[A] My priority is: 5
HIGH priority process running: 0

[B] My priority is: 15
LOW priority process running: 0

HIGH priority process running: 1
LOW priority process running: 1

Done.
```

> Higher-priority processes always execute before lower-priority processes.

---

### `schedtest` — Scheduling Modes

```text
-- Mode 3: Priority with Aging --
HIGH (priority 5) running
HIGH: 0
LOW (priority 15) running
LOW: 0

-- Mode 2: Round Robin --
P1 (prio 5): 0
P2 (prio 5): 0
Done.
```

> Aging prevents starvation, while Round-Robin ensures fairness between equal-priority processes.

---

### `finaltest` — Complete Scheduler Demonstration

```text
=========================================
   Priority-Based Process Scheduler Test
=========================================

[A] My priority is: 3
[A] HIGH priority running: step 1

[B] My priority is: 18
[B] LOW priority running: step 1

[C] Equal priority running: step 1
[D] Equal priority running: step 1

=========================================
   All tests passed successfully!
=========================================
```

> `getpriority()` correctly returns process priorities.  
> High-priority processes execute first, while equal-priority processes alternate fairly.

---

## Design Decisions

- **Default Priority = 10**  
  New processes start with a balanced mid-range priority.

- **Priority Range = 0–19**  
  Inspired by Linux-style nice values.

- **Aging Threshold = 50 Ticks**  
  Waiting processes gradually gain higher priority to prevent starvation.

---

## Branch

```bash
priority-schedular
```

---

## Future Improvements

- Multi-Level Feedback Queue (MLFQ)
- Dynamic time quantum support
- CPU usage statistics
- Priority inheritance mechanisms
- Per-process scheduling policies

---

## Repository Structure

```text
xv6-riscv/
├── kernel/
│   ├── proc.c
│   ├── proc.h
│   ├── trap.c
│   ├── syscall.c
│   ├── syscall.h
│   └── sysproc.c
├── user/
│   ├── user.h
│   ├── usys.pl
│   ├── priotest.c
│   ├── schedtest.c
│   └── finaltest.c
├── Makefile
└── README.md
```

---

## Summary

This project transforms the default xv6 scheduler into a fully functional **priority-based scheduling system** with:

- Dynamic scheduling modes
- Runtime scheduler switching
- Aging support
- Fair Round-Robin scheduling
- User-level priority management
- Starvation prevention

The implementation demonstrates core operating system concepts including:

- CPU scheduling
- Process management
- System calls
- Concurrency handling
- Fairness and starvation prevention

---

## Key Learning Outcomes

Through this project, I gained practical experience with:

- Operating system scheduler design
- Process management in xv6
- Kernel-level system call implementation
- Starvation prevention techniques
- Runtime scheduling policy control
- Low-level OS debugging and testing

# Priority-Based Process Management in xv6

> Enhancing the xv6 operating system scheduler with **priority scheduling, aging, and dynamic runtime scheduling modes**.

---

## Overview

The default xv6 scheduler uses a **round-robin scheduling algorithm**, where each runnable process receives CPU time in equal rotation regardless of its importance.

This project replaces that behavior with a **priority-based scheduling system**, allowing the operating system to make smarter scheduling decisions based on process urgency.

Each process is assigned a priority value from:

- **0** → Highest priority  
- **19** → Lowest priority  

The scheduler always selects the highest-priority runnable process first.

To prevent starvation, an **aging mechanism** was implemented to gradually boost long-waiting processes.

---

## Features

- Priority-aware CPU scheduling
- Four scheduling modes selectable at runtime
- Aging mechanism to prevent starvation
- New system calls for priority and scheduler control
- User-space test programs for validation
- Dynamic runtime switching between scheduling policies

---

## Scheduling Modes

| Mode | Name | Description |
|------|------|-------------|
| `0` | Non-Preemptive Priority | Runs the highest-priority process until it voluntarily yields |
| `1` | Preemptive Priority | Higher-priority processes can interrupt running lower-priority ones |
| `2` | Round Robin | Processes with equal priority share CPU fairly |
| `3` | Priority with Aging (**Default**) | Priority scheduling with automatic boosting after waiting 50 ticks |

> **Default mode:** `3` (Priority Scheduling with Aging)

---

## System Calls Added

| System Call | Number | Description |
|-------------|--------|-------------|
| `setpriority(int p)` | 22 | Sets the calling process priority (0–19) |
| `getpriority()` | 24 | Returns the current process priority |
| `setsched(int mode)` | 25 | Switches scheduler mode at runtime |

---

## Modified Files

| File | Modification |
|------|-------------|
| `kernel/proc.h` | Added `priority` and `waited_ticks` fields |
| `kernel/proc.c` | Reimplemented scheduler logic and added aging |
| `kernel/syscall.h` | Registered new syscall numbers |
| `kernel/syscall.c` | Added syscall dispatch entries |
| `kernel/sysproc.c` | Implemented syscall handlers |
| `user/user.h` | Added syscall declarations |
| `user/usys.pl` | Added user-space syscall stubs |
| `user/priotest.c` | Priority scheduling validation |
| `user/schedtest.c` | Scheduling mode validation |
| `user/finaltest.c` | Full system demonstration |

---

## Running the Project

### Build and launch xv6

```bash
make qemu
```

### Run test programs

```bash
priotest
schedtest
finaltest
```

### Exit xv6

```bash
Ctrl + A, then X
```

---

## Test Results

## 1. Priority Scheduling Test (`priotest`)

Tests whether higher-priority processes execute before lower-priority ones.

### Output

```text
HIGH priority process running: 0
LOW priority process running: 0
HIGH priority process running: 1
LOW priority process running: 1
Done.
```

### Result

High-priority processes consistently execute before low-priority processes.

---

## 2. Scheduler Modes Test (`schedtest`)

Validates switching between scheduling modes.

### Output

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

### Result

- Aging prevents starvation  
- Round-robin ensures fairness among equal-priority processes

---

## 3. Full Integration Test (`finaltest`)

Demonstrates all implemented features together.

### Output

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

### Result

- `getpriority()` works correctly  
- Higher-priority processes execute first  
- Equal-priority processes alternate fairly  
- Scheduler switching functions as expected

---

## Design Decisions

### Default Priority = `10`

New processes begin with medium priority to ensure balanced scheduling.

### Priority Range = `0–19`

Inspired by Linux **nice values**, providing clear granularity.

### Aging Threshold = `50 ticks`

Chosen to:

- Prevent starvation
- Avoid excessive priority reshuffling
- Preserve scheduler stability

---

## Branch

```bash
priority-scheduler
```

---

## Key Learning Outcomes

Through this project, I gained practical experience with:

- Operating system scheduler design
- Process management in xv6
- Kernel-level system call implementation
- Starvation prevention techniques
- Runtime scheduling policy control
- Low-level OS debugging and testing

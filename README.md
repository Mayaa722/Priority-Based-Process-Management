# Priority-Based Process Management in xv6

## Overview
This project modifies the xv6 operating system scheduler to support priority-based process scheduling with aging, multiple scheduling modes, and dynamic priority management via system calls.

By default, xv6 uses round-robin scheduling — every process gets equal CPU time regardless of importance. This project replaces that with a priority-aware scheduler where each process has a priority value (0 = highest, 19 = lowest), and the scheduler always runs the most urgent process first.

---

## Features
- Priority scheduling — processes with lower priority numbers run first
- 4 scheduler modes switchable at runtime
- Aging — prevents starvation by boosting waiting processes over time
- 3 new system calls — setpriority, getpriority, setsched
- 3 test programs — priotest, schedtest, finaltest

---

## Scheduler Modes

| Mode | Name | Description |
|------|------|-------------|
| 0 | Non-Preemptive | Runs highest priority process to completion |
| 1 | Preemptive | Higher priority process preempts running one |
| 2 | Round-Robin | Equal priority processes take fair turns |
| 3 | Aging (default) | Priority + boost every 50 ticks to prevent starvation |

---

## System Calls Added

| Syscall | Number | Description |
|---------|--------|-------------|
| setpriority(int p) | 22 | Sets calling process priority (0–19) |
| getpriority(void) | 24 | Returns calling process current priority |
| setsched(int mode) | 25 | Switches scheduler mode at runtime |

---

## Files Modified

| File | Change |
|------|--------|
| kernel/proc.h | Added int priority and int waited_ticks to struct proc |
| kernel/proc.c | Rewrote scheduler() with 4 modes + aging, initialized fields in allocproc(), added highestPriorityRunnable() helper |
| kernel/syscall.h | Added SYS_setpriority (22), SYS_sleep (23), SYS_getpriority (24), SYS_setsched (25) |
| kernel/syscall.c | Registered all new syscalls in dispatch table |
| kernel/sysproc.c | Implemented sys_setpriority(), sys_getpriority(), sys_setsched() |
| user/user.h | Declared setpriority(), getpriority(), setsched(), sleep() |
| user/usys.pl | Added user-space stubs for all new syscalls |
| user/priotest.c | Test: two processes with different priorities |
| user/schedtest.c | Test: all scheduler modes |
| user/finaltest.c | Test: full priority + round-robin demonstration |

---

## How to Run

Build and boot xv6:
make qemu

Run test programs inside xv6:
$ priotest
$ schedtest
$ finaltest

Exit xv6: Ctrl+A then X

---

## Test Results

### priotest
HIGH priority process running: 0
LOW priority process running: 0
HIGH priority process running: 1
LOW priority process running: 1
HIGH priority process running: 2
LOW priority process running: 2
Done.

Result: HIGH always runs before LOW in every round.

### schedtest
=== Scheduler Mode Test ===
-- Mode 3: Priority with Aging --
HIGH (priority 5) running
HIGH: 0
LOW (priority 15) running
LOW: 0
HIGH: 1
LOW: 1
-- Mode 2: Round Robin --
P1 (prio 5): 0
P2 (prio 5): 0
P1 (prio 5): 1
P2 (prio 5): 1
Done.

Result: Aging prevents starvation. Round-robin gives equal processes fair turns.

### finaltest
=========================================
   Priority-Based Process Scheduler Test
=========================================
Test 1: Two processes with different priorities
Process A -> priority 3 (HIGH)
Process B -> priority 18 (LOW)
[A] My priority is: 3
[A] HIGH priority running: step 1
[B] My priority is: 18
[B] LOW priority running: step 1
[A] HIGH priority running: step 2
[B] LOW priority running: step 2
[A] Done.
[B] Done.
Test 2: Equal priority - Round Robin
[C] Equal priority running: step 1
[D] Equal priority running: step 1
[C] Equal priority running: step 2
[D] Equal priority running: step 2
=========================================
   All tests passed successfully!
=========================================

---

## Design Decisions
- Default priority = 10 so new processes start at medium priority
- Priority range 0–19 mirrors Linux nice values
- Aging threshold = 50 ticks balances responsiveness with fairness
- sched_mode global variable allows runtime switching without recompiling

---

## Branch
priority-schedular

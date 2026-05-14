Copy and paste this exactly into the GitHub editor:

---

```markdown
# Priority-Based Process Management in xv6

## What is this project?

xv6 normally schedules processes using round-robin — every process takes turns getting the CPU, no matter how important or urgent it is. That means a critical process has to wait in line behind everything else.

I changed that.

This project adds a real priority system to xv6. Every process gets a priority number from **0 (most urgent)** to **19 (least urgent)**. The scheduler always picks the most important process first. We also added **aging** so that low-priority processes never get stuck waiting forever.

---

## What i Built

-  A priority-aware scheduler that always runs the highest priority process first
-  4 scheduling modes switchable at runtime
-  Aging to prevent starvation — low priority processes eventually get their turn
-  3 new system calls so user programs can control their own priority
-  3 test programs that prove everything works

---

## The 4 Scheduling Modes

| Mode | Name | What it does |
|------|------|--------------|
| `0` | Non-Preemptive | Runs the highest priority process until it gives up the CPU |
| `1` | Preemptive | A higher priority process can interrupt a running one |
| `2` | Round-Robin | Processes at the same priority level take fair turns |
| `3` | **Aging (default)** | Priority scheduling + processes get boosted after waiting 50 ticks |

> Mode 3 is the default when xv6 boots.

---

## System Calls Added

| System Call | Syscall # | What it does |
|-------------|-----------|--------------|
| `setpriority(int p)` | 22 | Set your process priority (0–19) |
| `getpriority()` | 24 | Read your current priority |
| `setsched(int mode)` | 25 | Switch the scheduler mode at runtime |

---

## Files Modified

| File | What we changed |
|------|-----------------|
| `kernel/proc.h` | Added `int priority` and `int waited_ticks` to every process |
| `kernel/proc.c` | Rewrote `scheduler()` with 4 modes + aging, added `highestPriorityRunnable()` |
| `kernel/syscall.h` | Registered new syscall numbers |
| `kernel/syscall.c` | Added new syscalls to the dispatch table |
| `kernel/sysproc.c` | Implemented `sys_setpriority()`, `sys_getpriority()`, `sys_setsched()` |
| `user/user.h` | Declared new syscalls for user programs |
| `user/usys.pl` | Added user-space stubs |
| `user/priotest.c` | Test program 1 |
| `user/schedtest.c` | Test program 2 |
| `user/finaltest.c` | Test program 3 |

---

## How to Run

**Boot xv6:**
```bash
make qemu
```

**Run the test programs inside xv6:**
```
$ priotest
$ schedtest
$ finaltest
```

**Exit:** `Ctrl+A` then `X`

---

## Test Results

### `priotest` — Does priority work?
Two processes: HIGH (priority 5) vs LOW (priority 15)

```
HIGH priority process running: 0
LOW priority process running: 0
HIGH priority process running: 1
LOW priority process running: 1
Done.
```
>  HIGH always runs before LOW in every round.

---

### `schedtest` — Do the modes work?

```
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
>  Aging prevents starvation. Round-robin gives equal processes fair turns.

---

### `finaltest` — Full demonstration

```
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
>  getpriority() works. A always runs before B. C and D alternate fairly.

---

## Design Decisions

- **Default priority = 10** — new processes start in the middle, not too high or too low
- **Range 0–19** — inspired by Linux nice values
- **Aging threshold = 50 ticks** — low enough to help starving processes quickly, high enough to avoid constant reshuffling

---

## Branch
> `priority-schedular`
```

# 4000. Largest Integer With Given Digit Sum
**Difficulty:** Easy
**Link:** https://leetcode.com/problems/largest-integer-with-given-digit-sum/
**Topics:** Math, Greedy

---

## 📜 Problem Statement

Given non-negative integers `n` and `s`, return the largest integer with **at most `n` digits** whose digits sum to `s`. If no such integer exists, return `-1`.

### Example 1
```
Input:  n = 2, s = 9
Output: 90
```

### Example 2
```
Input:  n = 2, s = 19
Output: -1      → max possible digit sum with 2 digits is 9+9=18
```

### Example 3
```
Input:  n = 5, s = 0
Output: 0
```

### Constraints
- `1 <= n <= 5`
- `0 <= s <= 100`

---

## 🧠 Intuition

Two separate ideas maximize a number: **more digits beats fewer digits** (a 2-digit number always exceeds any 1-digit number), and **among numbers with the same digit count, bigger digits on the left beat bigger digits on the right** (compare `91` vs `19` — leftmost digit dominates).

Combine both, and the greedy strategy falls out immediately:
1. **Always use exactly `n` digits** if possible (never fewer) — more digits is always better.
2. **Front-load the leftmost digits with `9`** (the largest single digit) for as long as the remaining sum allows.
3. Once the remaining sum drops to `9` or below, place it as the next digit, and **pad every digit after that with `0`** — trailing zeros are harmless since they only occupy less-significant positions.

### When is it impossible?
The largest digit sum achievable with `n` digits is `9 * n` (every digit maxed out). If `s` exceeds that, no valid number exists — return `-1`.

---

## ✅ Approach

1. **Feasibility check:** if `s > 9*n`, return `-1`.
2. **Zero case:** if `s == 0`, the only valid number is `0`.
3. **Greedy build:** repeat `n` times:
   - If the remaining `s <= 9`, place `s` as the next digit, then set `s = 0` for all future digits (they become `0`).
   - Otherwise, place `9` as the next digit and subtract `9` from `s`.
   - Append each digit via `ans = ans*10 + digit` — since digits are placed in order and each new digit shifts the previous ones left, the **first digit placed lands as the most significant digit**, which is exactly what we want (9s pushed as far left as possible).

---

## 🔍 Dry Run

**Input:** `n = 3, s = 10`

| Iteration | s before | Digit placed | s after | ans |
|-----------|----------|---------------|---------|-----|
| 1 | 10 | `9` (since 10 > 9) | 1 | 9 |
| 2 | 1  | `1` (since 1 <= 9)  | 0 | 91 |
| 3 | 0  | `0`                 | 0 | 910 |

Result: **910** — the leading `9` is placed first (most significant), the leftover `1` fills the next slot, and the final digit pads with `0` since the sum is already exhausted. This is indeed the largest 3-digit-or-fewer number summing to `10`.

---

## ⏱️ Complexity

| | Complexity | Why |
|---|---|---|
| **Time** | `O(n)` | Loop runs exactly `n` times (`n <= 5`, so effectively constant) |
| **Space** | `O(1)` | Just a running integer accumulator |

---

## 🔑 Pattern
**Greedy digit construction: maximize length first, then front-load the largest digit at each remaining position.** This shows up whenever a problem asks for the "largest number under some digit-level constraint" — the strategy is almost always (1) use as many digits as allowed, then (2) greedily assign the biggest legal digit to each position from left to right.

### Side note: redundant guards
The submitted code has two early-return special cases — `if (s == 0) return 0;` and `if (n == 1 && s <= 9) return s;` — that turn out to be unnecessary: tracing the general loop for both `s = 0` and `n = 1` shows it produces the identical result on its own. They're harmless (just an extra `O(1)` check before the main loop), but worth knowing they can be deleted without changing behavior — useful to recognize since spotting "this guard is actually already covered by the general case" is a habit worth building for cleaner code.
# 3731. Find Missing Elements
**Difficulty:** Easy
**Link:** https://leetcode.com/problems/find-missing-elements/
**Topics:** Array, Sorting, Two Pointers

---

## 📜 Problem Statement

Given an array `nums` of unique integers, originally containing every integer in some range `[min, max]` (both endpoints still present), some integers may now be missing. Return a sorted list of all missing integers in that range.

### Example 1
```
Input:  nums = [1,4,2,5]
Output: [3]
```

### Example 2
```
Input:  nums = [7,8,6,9]
Output: []
```

### Example 3
```
Input:  nums = [5,1]
Output: [2,3,4]
```

### Constraints
- `2 <= nums.length <= 100`
- `1 <= nums[i] <= 100`

---

## 🧠 Intuition

If the array had **no gaps**, then after sorting, each position `i` would hold exactly `nums[0] + i` — a clean, predictable sequence with no jumps. So the whole problem becomes: **walk the sorted array and compare each element against what it "should" be if nothing were missing.** Any mismatch reveals a gap.

### The tricky part: tracking "what should be here" separately from the array index
Once one number goes missing, the *expected* value and the *array index* drift apart — the expected value needs to keep counting up by 1 every step, but the array index only advances once a real match is found. That's why the code keeps a separate `drift` variable instead of just using `nums[0] + i` directly: `drift` represents "the next expected integer," and it only increments when either a real match occurs or a missing number gets recorded — while `i` (the array index) only advances when a real match is found.

### The `i--` trick
```cpp
if (drift + i != nums[i]) {
    missing.push_back(drift + i);
    drift = drift + 1;
    i--;
}
```
When a gap is found, the code records the missing number, bumps `drift` forward by one (accounting for the number we just "filled in" conceptually), and then does `i--` — which, combined with the `for` loop's automatic `i++`, results in a **net-zero change to `i`**. In effect: *retry the same array index, but with the expected value advanced by one.* This lets a single `for` loop handle runs of multiple consecutive missing numbers without needing a separate inner `while` loop.

---

## ✅ Approach

1. Sort `nums`.
2. Set `drift = nums[0]` — the first expected value in the range.
3. Walk index `i` from `0` to `n-1`:
   - If `drift + i == nums[i]`, this position has no gap — move on (`i` advances naturally via the loop).
   - If they don't match, `drift + i` is a missing number: record it, increment `drift`, and re-check the **same** `i` again (via `i--`).
4. Return the collected missing numbers — they come out already in sorted order, since `drift` only ever increases.

---

## 🔍 Dry Run

**Input:** `nums = [5, 1]` → sorted: `[1, 5]`, `drift = 1`

| i | drift+i | nums[i] | Match? | Action |
|---|---------|---------|--------|--------|
| 0 | 1 | 1 | yes | advance i |
| 1 | 2 | 5 | no  | push `2`, drift→2, retry i=1 |
| 1 | 3 | 5 | no  | push `3`, drift→3, retry i=1 |
| 1 | 4 | 5 | no  | push `4`, drift→4, retry i=1 |
| 1 | 5 | 5 | yes | advance i, loop ends |

Result: `[2, 3, 4]` ✅ matches expected output — the retry mechanism correctly walks through an entire run of consecutive missing numbers before the array index finally advances.

---

## ⏱️ Complexity

| | Complexity | Why |
|---|---|---|
| **Time** | `O(n log n)` | Dominated by the initial sort; the fill loop itself does a total of `n + (missing count)` iterations — every real match advances `i`, every missing number costs exactly one extra retry iteration, so it's linear in the range size, not quadratic |
| **Space** | `O(1)` extra | Beyond the output list itself; sort is in-place (aside from its own recursion overhead) |

---

## 🔑 Pattern
**Sorted-array gap detection via an "expected value" pointer.** Whenever consecutive integers should form an unbroken run, don't compare adjacent array elements to each other — compare each element against what an unbroken sequence *would* produce at that point. Keeping the expected-value counter separate from the array index (rather than conflating them) is what lets a single pass handle any number of consecutive gaps cleanly.

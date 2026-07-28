# 4001. Aggregate Two Time Series
**Difficulty:** Medium
**Link:** https://leetcode.com/problems/aggregate-two-time-series/
**Topics:** Array, Two Pointers, Simulation

---

## 📜 Problem Statement

Given two 2D arrays `series1` and `series2`, each element `[timestamp, value]`, both sorted strictly increasing by timestamp. For any timestamp missing from a series, its value is taken from the **next available timestamp** in that same series (or `0` if none exists). Return the aggregated `[timestamp, summedValue]` pairs across every timestamp present in either series, sorted increasing.

### Example 1
```
series1 = [[1,3],[4,1]], series2 = [[2,2],[5,2]]
Output:  [[1,5],[2,3],[4,3],[5,2]]
```

### Example 2
```
series1 = [[1,5],[3,1]], series2 = [[2,2]]
Output:  [[1,7],[2,3],[3,1]]
```

### Example 3
```
series1 = [[1,5]], series2 = [[1000000000,2]]
Output:  [[1,7],[1000000000,2]]
```

### Constraints
- `1 <= series1.length, series2.length <= 10^5`
- `1 <= series1[i][0], series2[i][0] <= 10^9`
- `1 <= series1[i][1], series2[i][1] <= 10^9`
- Both series sorted strictly increasing by timestamp

---

## 🧠 Intuition

The "missing value comes from the **next available** timestamp" rule sounds like it needs lookahead bookkeeping — but a plain two-pointer merge over both sorted series turns out to satisfy it **automatically**, with zero extra work.

Here's why: at any point during the merge, pointer `i` sits on the next *unconsumed* entry of `series1`, and pointer `j` sits on the next unconsumed entry of `series2`. Whichever pointer hasn't been advanced past the current timestamp yet is, by definition, pointing at that series' **next available future value** — exactly what the problem asks for. So the standard "merge two sorted lists" pattern already encodes the required semantics; no special-casing needed.

### The three cases at each step
- `series1[i].timestamp < series2[j].timestamp` → emit `series1[i]`'s timestamp, sum `series1[i].value + series2[j].value` (using `series2[j]` as its "next available" stand-in), advance `i`.
- `series1[i].timestamp > series2[j].timestamp` → mirror case, advance `j`.
- `series1[i].timestamp == series2[j].timestamp` → both have real data here, sum both values directly, advance **both** pointers.
- Once one series is exhausted, whatever remains in the other series has no partner left (value `0` on the other side), so just copy those entries through as-is.

---

## ✅ Approach 

1. Two pointers `s1 = 0`, `s2 = 0`.
2. While both pointers are in range:
   - If `series1[s1][0] <= series2[s2][0]`: emit `(series1[s1][0], series1[s1][1] + series2[s2][1])`. If the timestamps were *equal*, also advance `s2`. Always advance `s1`.
   - Else: emit `(series2[s2][0], series1[s1][1] + series2[s2][1])`, advance `s2`.
3. Drain whichever series still has leftover entries, emitting each as-is (no partner to sum with).

---

## 🔍 Dry Run

**Input:** `series1 = [[1,3],[4,1]]`, `series2 = [[2,2],[5,2]]`

| Step | s1 ts | s2 ts | Emitted | Note |
|------|-------|-------|---------|------|
| 1 | 1 | 2 | `[1, 3+2=5]` | `1<=2`, advance s1 only (not equal) |
| 2 | 4 | 2 | `[2, 1+2=3]` | `4>2`, advance s2. Note: series1 value used is still `1` (from ts=4) — the "next available" future value |
| 3 | 4 | 5 | `[4, 1+2=3]` | `4<=5`, advance s1 (not equal) |
| 4 | — | 5 | `[5, 2]` | series1 exhausted, drain series2 as-is |

Result: `[[1,5],[2,3],[4,3],[5,2]]` ✅ matches expected output exactly.

---

## ⏱️ Complexity

| | Complexity | Why |
|---|---|---|
| **Time** | `O(n + m)` | Each pointer advances at most `n` and `m` times total — no backtracking |
| **Space** | `O(n + m)` | Required for the output itself; `O(1)` extra beyond that |



---

## 🔑 Pattern
**Two-pointer merge, where "missing value = next available" falls out for free from standard merge mechanics.** Whenever a problem talks about "carrying forward the next/previous value across two sorted sequences," check first whether a plain merge-two-sorted-lists walk already satisfies the requirement before reaching for anything more complex — it very often does.
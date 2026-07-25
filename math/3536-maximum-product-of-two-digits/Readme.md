# 3536. Maximum Product of Two Digits
**Difficulty:** Easy
**Link:** https://leetcode.com/problems/maximum-product-of-two-digits/
**Topics:** Math

---

## 📜 Problem Statement

Given a positive integer `n`, return the **maximum product of any two digits** in `n`. The same digit can be reused if it appears more than once.

### Example 1
```
Input:  n = 31
Output: 3      → digits [3,1], only product: 3*1=3
```

### Example 2
```
Input:  n = 22
Output: 4      → digits [2,2], product: 2*2=4
```

### Example 3
```
Input:  n = 124
Output: 8      → digits [1,2,4], best product: 2*4=8
```

### Constraints
- `10 <= n <= 10^9`

---

## 🧠 Intuition

"Maximum product of any two digits" sounds like it wants you to check every pair — but products only get maximized by using the **largest** values available. You don't need every pairwise product, you just need the **top 2 digits** in `n`, then multiply them.

This is the classic **"find max and second-max in one pass"** pattern, just applied to digits instead of an array.

---

## ✅ Approach

1. Peel off digits one at a time using `% 10` and `/ 10`.
2. Track the two largest digits seen so far — `max1` (largest) and `max2` (second largest) — updating both in a single pass.
3. Return `max1 * max2`.

### Why `>=` and not `>` in the first comparison?
```cpp
if (digit >= max1) {
    max2 = max1;
    max1 = digit;
}
```
Using `>=` (not strict `>`) matters here: if the new digit *ties* the current max (like the `22` example), we still want to shift the old `max1` down into `max2` — otherwise a repeated digit would never get credited as the "second" pick, and `22` would incorrectly compute `2 * (uninitialized max2)` instead of `2 * 2`.

---

## 🔍 Dry Run

**Input:** `n = 124`

| Step | digit | max1 | max2 |
|------|-------|------|------|
| start | — | -∞ | -∞ |
| peel 4 | 4 | **4** | -∞ |
| peel 2 | 2 | 4 | **2** |
| peel 1 | 1 | 4 | 2 *(1 < 2, no update)* |

Result: `max1 * max2 = 4 * 2 = 8` ✅

---

## ⏱️ Complexity

| | Complexity | Why |
|---|---|---|
| **Time** | `O(log n)` | One pass over the digits of `n` (at most 10 digits, since `n <= 10^9`) |
| **Space** | `O(1)` | Just two tracking variables, no digit array needed |

---

## 🔑 Pattern
**Single-pass top-2 tracking.** Whenever a problem needs the "best pair" from a stream/sequence and the operation (product, sum, etc.) is maximized by extremes, you rarely need to store the full list — just carry the top-1 and top-2 running values forward as you scan.
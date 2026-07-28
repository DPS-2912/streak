# 3560. Find Minimum Log Transportation Cost
**Difficulty:** Easy
**Link:** https://leetcode.com/problems/find-minimum-log-transportation-cost/
**Topics:** Math, Greedy

---

## 📜 Problem Statement

You have two logs of length `n` and `m`, and three trucks, each able to carry a log of length at most `k`. You may cut a log of length `x` into two pieces `len1` and `len2` (`len1 + len2 = x`), at a cost of `len1 * len2`. Return the minimum total cutting cost to fit both logs across the three trucks. If no cutting is needed, the cost is `0`.

### Example 1
```
Input:  n = 6, m = 5, k = 5
Output: 5      → cut 6 into 1 and 5 (cost 1*5=5); pieces {1,5,5} fit in 3 trucks
```

### Example 2
```
Input:  n = 4, m = 4, k = 6
Output: 0      → both logs already fit, no cut needed
```

### Constraints
- `2 <= k <= 10^5`
- `1 <= n, m <= 2*k`
- Input is always guaranteed transportable

---

## 🧠 Intuition

### Only one log can ever need cutting
There are exactly **3 trucks** and **2 logs**. If a log needs cutting, it splits into 2 pieces, consuming 2 trucks by itself. Since there are only 3 trucks total, **at most one log can be the one that gets cut** — if both `n > k` and `m > k` simultaneously, you'd need 4 trucks minimum, which the problem's "always transportable" guarantee rules out. So in any valid input, either both logs already fit (`n<=k and m<=k`, cost 0), or exactly one of them needs a single cut.

### If a log must be cut, why does an *uneven* split minimize cost?
This is the part worth sitting with. Given a fixed sum `x = len1 + len2`, most people's instinct is that splitting evenly minimizes things — but for a **product** with a fixed sum, the opposite is true:

- Product `len1 * len2` is **maximized** when the two pieces are as *equal* as possible.
- Product `len1 * len2` is **minimized** when the two pieces are as *unequal* as possible.

Quick sanity check with `x = 10`:
```
5 * 5  = 25   (equal split — largest product)
4 * 6  = 24
2 * 8  = 16
1 * 9  = 9    (most extreme split — smallest product)
```
So to minimize cost, we want to push the split as far apart as the constraints allow. But we're not free to go fully extreme (like `1` and `9`) — **both pieces must be `<= k`** to fit in a truck. So the most extreme split *allowed* is: make one piece exactly `k` (the largest a single truck permits), and the other piece absorbs the rest, `x - k`.

```
cost = k * (x - k)
```

Since the constraint `x <= 2k` guarantees `x - k <= k` too, this split is always valid — both pieces fit.

---

## ✅ Approach

1. If both `n <= k` and `m <= k`, return `0` — nothing to cut.
2. Otherwise, exactly one of `n`, `m` exceeds `k`. For whichever one does, compute:
   ```
   cost = k * (x - k)
   ```
   where `x` is that log's length.
3. Return the cost.

The submitted code expresses this as two `while` loops (one per log) instead of a single `if`/computation — functionally, each loop can only ever execute **once**, since after one iteration the log's remaining length drops to `x - k <= k`, which fails the loop condition immediately. It's written generally but the problem's constraints (`n, m <= 2k`) guarantee it never needs a second pass.

---

## 🔍 Dry Run

**Input:** `n = 6, m = 5, k = 5`

- `m = 5`, is `m > k`? `5 > 5` → false. Skip.
- `n = 6`, is `n > k`? `6 > 5` → true.
  - `cost += k * (n - k) = 5 * (6 - 5) = 5 * 1 = 5`
  - `n -= k` → `n = 1`
  - loop again: `n > k`? `1 > 5` → false. Stop.

Return `cost = 5` ✅ matches expected output.

---

## ⏱️ Complexity

| | Complexity | Why |
|---|---|---|
| **Time** | `O(1)` | Each `while` loop runs at most once, given `n, m <= 2k` |
| **Space** | `O(1)` | Just a running `cost` accumulator |

---

## 🔑 Pattern
**Fixed-sum product optimization under a bound.** Whenever a cost is defined as a product of two values summing to a fixed total, remember: equal split maximizes the product, extreme split (pushed to the tightest allowed boundary) minimizes it. Combined with a simple resource-counting argument (3 trucks, 2 logs → at most one log can be split), the "hard-looking" problem collapses into a single formula.
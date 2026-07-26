ls# 628. Maximum Product of Three Numbers
**Difficulty:** Easy
**Link:** https://leetcode.com/problems/maximum-product-of-three-numbers/
**Topics:** Array, Math, Sorting

---

## 📜 Problem Statement

Given an integer array `nums`, find three numbers whose product is maximum, and return that product.

### Example 1
```
Input:  nums = [1,2,3]
Output: 6
```

### Example 2
```
Input:  nums = [1,2,3,4]
Output: 24
```

### Example 3
```
Input:  nums = [-1,-2,-3]
Output: -6
```

### Constraints
- `3 <= nums.length <= 10^4`
- `-1000 <= nums[i] <= 1000`

---

## 🧠 Intuition

The obvious first thought is "sort the array, multiply the three largest." That works — *unless* the array contains negative numbers.

The trick: **two negatives multiplied together become positive.** So if the array has two very negative numbers, pairing them with the single largest positive number can beat the "three largest" strategy outright.

### Two candidates, always
There are only two ways a maximum-product triplet can ever look:

1. **Three largest values** — the safe default when negatives don't help (e.g. `[1,2,3,4]` → `2*3*4=24`).
2. **Two smallest (most negative) values × the single largest value** — wins when two big negatives flip to a large positive (e.g. `[-5,-4,1,2,3]` → `(-5)*(-4)*3 = 60`, which beats `1*2*3=6`).

You never need a third candidate — mixing "one smallest + two largest," for instance, can never beat one of the two above (a quick sign-check confirms this: an odd number of negatives in your chosen triplet always makes the product ≤ 0 or non-optimal compared to one of the two clean candidates).

So the whole problem reduces to: **track the top 3 largest and bottom 2 smallest values in a single pass, then take the better of the two candidate products.**

---

## ✅ Approach

1. **Special-case `size == 3`** — with exactly 3 elements, there's only one possible triplet, so just multiply them directly and return.
2. **Single pass, cascading comparisons:**
   - Maintain `max1 >= max2 >= max3` (top 3 largest), updated via a cascading `if / else if / else if` chain.
   - Maintain `min1 <= min2` (bottom 2 smallest), updated the same way.
3. **Compute both candidates:**
   ```
   ans1 = max1 * max2 * max3      (three largest)
   ans2 = min1 * min2 * max1      (two smallest * largest)
   ```
4. **Return `max(ans1, ans2)`.**

### Why cascading `if / else if` works for top-3
This is the same single-pass "top-k tracking" idea as the [Maximum Product of Two Digits](../3536_Maximum_Product_of_Two_Digits/problem.md) problem, extended one level deeper:
```
if x beats max1:  max3 = max2, max2 = max1, max1 = x   (shift everyone down)
elif x beats max2: max3 = max2, max2 = x
elif x beats max3: max3 = x
```
Each `elif` only fires if the number failed to dethrone something higher up — so at most one shift happens per element, keeping it `O(1)` work per element.

---

## 🔍 Dry Run

**Input:** `nums = [-5, -4, 1, 2, 3]`

| Element | max1,max2,max3 after | min1,min2 after |
|---------|----------------------|-------------------|
| -5      | -5, -inf, -inf        | -5, 0 *(see pitfall below)* |
| -4      | -5, -4, -inf          | -5, -4 |
| 1       | 1, -5, -4             | -5, -4 |
| 2       | 2, 1, -5              | -5, -4 |
| 3       | 3, 2, 1               | -5, -4 |

```
ans1 = 3 * 2 * 1   = 6
ans2 = (-5) * (-4) * 3 = 60
max(6, 60) = 60
```
The two-negatives strategy wins here — confirming why we can't just sort and grab the top 3.

---

## ⏱️ Complexity

| | Complexity | Why |
|---|---|---|
| **Time** | `O(n)` | Single pass over the array, constant work per element |
| **Space** | `O(1)` | Only 5 tracking variables, no sorting or extra array |

A sort-based approach would work too (`O(n log n)` time, `O(1)` extra space if in-place), but the single-pass version is strictly faster and is the natural next step up from the top-2 tracking pattern.

---

## 🔑 Pattern
**Single-pass top-k / bottom-k tracking, extended to handle sign flips.** Whenever a "maximize a product of k elements" problem allows negative numbers, always check whether pairing an even count of the most negative values can outperform the naive "top-k by value" answer — then track both extremes in one pass instead of sorting.
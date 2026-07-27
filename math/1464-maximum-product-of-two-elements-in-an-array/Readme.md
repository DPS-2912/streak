# 1464. Maximum Product of Two Elements in an Array
**Difficulty:** Easy
**Link:** https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/
**Topics:** Array, Sorting

---

## 📜 Problem Statement

Given an array of integers `nums`, choose two different indices `i` and `j`. Return the maximum value of `(nums[i]-1) * (nums[j]-1)`.

### Example 1
```
Input:  nums = [3,4,5,2]
Output: 12      → (4-1)*(5-1) = 3*4 = 12
```

### Example 2
```
Input:  nums = [1,5,4,5]
Output: 16      → (5-1)*(5-1) = 4*4 = 16
```

### Example 3
```
Input:  nums = [3,7]
Output: 12      → (3-1)*(7-1) = 2*6 = 12
```

### Constraints
- `2 <= nums.length <= 500`
- `1 <= nums[i] <= 10^3`

---

## 🧠 Intuition

Strip away the `-1` for a second and this is just "find the two largest numbers and multiply them" — the exact same [top-2 single-pass pattern](../3536_Maximum_Product_of_Two_Digits/problem.md) used for the digit problem.

The `-1` doesn't change *which* two numbers you should pick. Since every element gets the same `-1` applied, and `nums[i] >= 1` for all elements (per constraints, so `nums[i]-1 >= 0` — never negative), the ordering between elements is preserved: whichever two numbers were largest before subtracting 1 are still the two largest after subtracting 1. So the "-1" is really just a red herring dressing up a plain top-2 problem — apply it only at the very end, on the two winners, not during the comparisons.

---

## ✅ Approach

1. Single pass through `nums`, tracking `max1` (largest) and `max2` (second largest) — same cascading update as the digit-product problem.
2. Once both are found, return `(max1 - 1) * (max2 - 1)`.

### Why `>=` instead of `>` for the `max1` check?
```cpp
if (nums[i] >= max1) {
    max2 = max1;
    max1 = nums[i];
}
```
Same reasoning as before: if a new element **ties** the current `max1` (like the two `5`s in Example 2), we still need it to push the old `max1` down into `max2` — otherwise a tie would never get credited as the second pick, and `[1,5,4,5]` would compute the wrong pair.

---

## 🔍 Dry Run

**Input:** `nums = [1, 5, 4, 5]`

| Element | max1 | max2 |
|---------|------|------|
| 1       | 1    | -inf |
| 5       | 5    | 1    |
| 4       | 5    | 4    |
| 5       | **5** (tie, shifts old max1=5 into max2) | **5** |

Result: `(5-1) * (5-1) = 4 * 4 = 16` ✅ matches expected output.

---

## ⏱️ Complexity

| | Complexity | Why |
|---|---|---|
| **Time** | `O(n)` | One pass over the array |
| **Space** | `O(1)` | Just two tracking variables |

---

## 🔑 Pattern
**Single-pass top-2 tracking, with a monotonic transform applied after selection.** Whenever the target expression is a fixed, order-preserving function (like `-1`, `*2`, `+k`) applied identically to each candidate, don't fold it into the comparison logic — find the winners first using plain comparisons, then apply the transform once at the end. Same core pattern as [Maximum Product of Two Digits](../3536_Maximum_Product_of_Two_Digits/problem.md), just with a linear twist layered on top.
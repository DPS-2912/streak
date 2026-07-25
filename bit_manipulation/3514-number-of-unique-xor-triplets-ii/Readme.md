# 3514. Number of Unique XOR Triplets II
**Difficulty:** Medium
**Link:** https://leetcode.com/problems/number-of-unique-xor-triplets-ii/
**Topics:** Array, Bit Manipulation, Hash Table

---

## 📜 Problem Statement

You're given `nums` — this time **not** a permutation, just any array of integers. A **XOR triplet** is:

```
nums[i] XOR nums[j] XOR nums[k],  where i <= j <= k
```

Return the number of **unique** values obtainable this way.

### Example 1
```
Input:  nums = [1, 3]
Output: 2
```
Unique values → `{1, 3}`

### Example 2
```
Input:  nums = [6, 7, 8, 9]
Output: 4
```
Unique values → `{6, 7, 8, 9}`

### Constraints
- `1 <= nums.length <= 1500`
- `1 <= nums[i] <= 1500`

---

## 🧠 Why the Problem 3513 trick doesn't apply here

In **[Problem 3513](../3513_Number_of_Unique_XOR_Triplets_I/problem.md)**, the whole solution hinged on `nums` being a **permutation of `1..n`** — that guaranteed powers of two were individually present as elements, that `0` and `mask` were always reachable, and ultimately that the answer collapsed to a clean `mask + 1`.

Here, none of that holds:
- `nums` can have **duplicates** (e.g. `[6,7,8,9]` — no repeats here, but the constraints allow them).
- `nums` is **not** guaranteed to be a contiguous run starting at `1` — Example 2 doesn't even contain `1, 2, or 3`.
- So there's no guarantee `0` is reachable, no guarantee every value up to `mask` is reachable, and no clean formula.

**We're back to genuinely needing to enumerate what's reachable — but smartly, not via `O(n³)` brute force.**

---

## 💡 Intuition

A brute-force solution checks every triplet `(i, j, k)` directly:
```
nums[i] ^ nums[j] ^ nums[k]     → O(n³)
```
With `n` up to `1500`, that's ~3.3 billion operations — too slow.

### The key rewrite
Any triplet XOR can be split into two steps:
```
(nums[i] ^ nums[j]) ^ nums[k]
```
In other words: **first figure out every possible *pair* XOR, then combine each of those with every single array element to get triplet XORs.**

This works because XOR triplet enumeration doesn't care about the *order* you combine things in — grouping `i,j` first and `k` second still covers every triplet, just via two smaller passes instead of one `O(n³)` pass.

### Why a fixed-size array instead of a hash set?
Since `1 <= nums[i] <= 1500`, every XOR result is bounded:
```
nums[i] < 2^11 = 2048
```
So any XOR of two or three such numbers **also fits inside `[0, 2047]`** — meaning we can use a plain boolean array of size `2048` instead of a hash set. Much faster, no hashing overhead.

---

## ✅ Approach

1. **Pair XOR pass** — for every pair `(i, j)` with `i <= j` (including `i == j`), mark `pairXor[nums[i] ^ nums[j]] = true`.
   *(`i == j` gives `nums[i]^nums[i] = 0`, which is how single/double-element triplets like `x^x^y` sneak into the result — same "repeats cancel" idea as Problem I.)*
2. **Triplet XOR pass** — for every marked pair-XOR value `x`, and every element `v` in `nums`, mark `tripletXor[x ^ v] = true`.
3. **Count** — the number of `true` entries in `tripletXor` is the answer.

---

## 🔍 Dry Run

**Input:** `nums = [1, 2, 3]`

### Step 1 — All pair XORs (including `i == j`)
| Pair | XOR |
|------|-----|
| 1^1  | 0   |
| 1^2  | 3   |
| 1^3  | 2   |
| 2^2  | 0   |
| 2^3  | 1   |
| 3^3  | 0   |

Distinct pair XORs → `{0, 1, 2, 3}`

### Step 2 — Combine every pair-XOR with every element
| Pair XOR | ^1 | ^2 | ^3 |
|----------|----|----|----|
| 0        | 1  | 2  | 3  |
| 1        | 0  | 3  | 2  |
| 2        | 3  | 0  | 1  |
| 3        | 2  | 1  | 0  |

Distinct triplet XORs → `{0, 1, 2, 3}`

### Final Answer: `4`

---

## ⏱️ Complexity

| | Complexity | Why |
|---|---|---|
| **Time** | `O(n² + n × 2048)` → effectively `O(n²)` since `2048` is a constant | `n²` for all pairs, `n × 2048` for combining pair-XORs with every element |
| **Space** | `O(2048)` → effectively `O(1)` | Two fixed-size boolean arrays, independent of `n` |

With `n <= 1500`, `n² ≈ 2.25M` — comfortably fast.

---

## 🔑 Pattern
**Meet-in-the-middle via value-range bounding.** When direct `k`-way enumeration is too slow but the *value range* of results is small and fixed (here, bounded by input constraints, not `n`), split the computation into stages (pairs → triplets) and use a fixed-size boolean/presence array instead of hashing. Contrast with Problem I, where the *permutation* structure let us skip enumeration entirely via a formula — here, no such structure exists, so we fall back to bounded enumeration.
# 3518. Smallest Palindromic Rearrangement II
**Difficulty:** Hard
**Link:** https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/
**Topics:** String, Math, Combinatorics, Greedy, Counting

---

## 📜 Problem Statement

Given a palindromic string `s` and an integer `k`, return the **k-th lexicographically smallest** distinct palindromic permutation of `s`. If fewer than `k` distinct palindromic permutations exist, return `""`.

### Example 1
```
s = "abba", k = 2
Output: "baab"      → distinct palindromes: {"abba", "baab"}, k=2 picks "baab"
```

### Example 2
```
s = "aa", k = 2
Output: ""          → only 1 distinct palindrome exists, k=2 is out of range
```

### Example 3
```
s = "bacab", k = 1
Output: "abcba"
```

### Constraints
- `1 <= s.length <= 10^4`
- `s` is guaranteed palindromic
- `1 <= k <= 10^6`

---

## 🧠 Intuition

### Step 1 — Reduce "k-th palindrome" to "k-th half-permutation"
This builds directly on [Smallest Palindromic Rearrangement I](../3517_Smallest_Palindromic_Rearrangement_I/problem.md): a palindrome is fully determined by its first half (plus a fixed middle character). Since two palindromes of the same total length only ever differ within their first-half prefix, **the lexicographic order of full palindromes is identical to the lexicographic order of their first halves.** So the entire "hard" problem collapses to a much more classical one:

> Find the k-th lexicographically smallest distinct **permutation of a multiset** (the left-half letter counts).

This is the multiset generalization of the well-known "k-th permutation sequence" problem — but instead of a plain sequence `1..n`, we have repeated letters, so we need a way to count permutations of a multiset, not just factorials.

### Step 2 — Counting permutations of a multiset
If a multiset has `n` total elements split into groups of sizes `c1, c2, ..., c26` (one per letter), the number of distinct arrangements is the **multinomial coefficient**:
```
n! / (c1! * c2! * ... * c26!)
```
This can be computed incrementally as a **product of binomial coefficients**, one letter at a time:
```
ways = C(c1, c1) * C(c1+c2, c2) * C(c1+c2+c3, c3) * ...
```
Each term answers: "having already placed the first `curr_len` letters, how many ways can I choose which of those `curr_len` slots belong to this next letter type?" Multiplying these together across all letters gives the full multinomial coefficient — this is exactly what the `get_ways` lambda computes, processing letters `a → z` and growing `curr_len` as it goes.

### Step 3 — Greedy digit-by-digit construction (like "k-th permutation," but per letter)
Build the first half one position at a time. At each position, try letters `a` through `z` in order:
- **Tentatively place** that letter (decrement its remaining count).
- **Count how many valid arrangements remain** for the rest of the half, given this tentative placement (`get_ways`).
- **If that count is `>= k`**, this letter is correct for this position — keep it, move to the next position.
- **Otherwise**, this letter accounts for too few arrangements to reach the k-th one. Subtract that count from `k` (skip past all arrangements starting with this letter), undo the tentative placement, and try the next letter.

This is the exact same logic as the classic "find the k-th permutation of `1..n`" problem — just with `get_ways` replacing simple factorials, because we're now ranking permutations of a multiset instead of a set of unique digits.

### Step 4 — Why cap the coefficient at `target_k + 1`?
Multinomial coefficients explode combinatorially — with `n` up to `5000` per half, the true value can vastly exceed what fits in a 64-bit integer. But we never actually need the *exact* value once it's already bigger than `k` — we only ever ask "is this `>= k`?" So the code clips any running product to `target_k + 1` the moment it exceeds `target_k`, which both **prevents overflow** and keeps every `get_ways` call fast, since the multiplication loop can `break` early once the cap is hit.

---

## ✅ Approach

1. Count letter frequencies; split into `half[26]` (each letter's count `/2`) and the middle character (if any letter has an odd count).
2. **Feasibility check:** if the total number of distinct half-permutations is `< k`, return `""`.
3. **Greedy construction**, one position at a time (`m` positions total, `m` = half length):
   - Try each letter `a → z`; tentatively use one occurrence.
   - Compute `ways = get_ways(half, k)` for the remaining letters.
   - If `ways >= k`: commit this letter, move to next position.
   - Else: `k -= ways`, revert the tentative use, try the next letter.
4. **Assemble the result:** `first_half + middle + reverse(first_half)`.

---

## 🔍 Dry Run

**Input:** `s = "bacab"`, `k = 1`

Counts: `a:2, b:2, c:1`. Half counts: `a:1, b:1`. Middle: `c`. Half length `m = 2`.

**Position 0** — try letters in order:
- `a`: tentatively use it (`half[a]=0`). Remaining multiset `{b:1}` → only 1 arrangement (`"b"`). `ways = 1 >= k(=1)` → **commit `a`**.

`first_half = "a"`, remaining half `{b:1}`.

**Position 1** — try letters in order:
- `a`: none left (`half[a]=0`), skip.
- `b`: tentatively use it (`half[b]=0`). Remaining multiset is empty → `1` arrangement (the empty one). `ways = 1 >= k(=1)` → **commit `b`**.

`first_half = "ab"`.

**Assemble:** `first_half + mid + reverse(first_half)` = `"ab" + "c" + "ba"` = **`"abcba"`** ✅ matches expected output.

---

## ⏱️ Complexity

| | Complexity | Why |
|---|---|---|
| **Time** | Roughly `O(m * 26 * (26 + log-ish work capped by k))` | `m` positions × up to `26` candidate letters per position × `get_ways` cost, where the inner nCr computation is capped at `target_k+1`, so it terminates fast once the running product exceeds `k` (rather than scaling with the true, astronomically large multinomial value) |
| **Space** | `O(m)` | For `first_half` and the final result string |

The `target_k + 1` capping is what makes this tractable — without it, the multinomial coefficients themselves would overflow and the arithmetic would be needlessly expensive even to compute.

---

## 🔑 Pattern
**K-th permutation of a multiset via greedy digit selection + capped combinatorial counting.** This generalizes the classic "k-th permutation sequence" pattern (normally solved with factorials and division) to repeated elements, by replacing factorial-based counting with an incrementally-computed, overflow-safe multinomial coefficient. The "cap intermediate values at `target+1`" trick is broadly reusable any time you need to compare a combinatorial count against a bound without risking overflow on the true value.
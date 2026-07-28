# 3517. Smallest Palindromic Rearrangement I
**Difficulty:** Medium
**Link:** https://leetcode.com/problems/smallest-palindromic-rearrangement-i/
**Topics:** String, Greedy, Counting, Two Pointers

---

## 📜 Problem Statement

Given a palindromic string `s`, return the lexicographically smallest palindromic permutation of `s`.

### Example 1
```
Input:  s = "z"
Output: "z"
```

### Example 2
```
Input:  s = "babab"
Output: "abbba"
```

### Example 3
```
Input:  s = "daccad"
Output: "acddca"
```

### Constraints
- `1 <= s.length <= 10^5`
- `s` consists of lowercase English letters
- `s` is guaranteed to be palindromic

---

## 🧠 Intuition

A palindrome is completely determined by its **first half** (plus a middle character, if the length is odd) — the second half is always just the mirror of the first. So "find the smallest palindromic rearrangement" really reduces to: **"what's the smallest possible left half I can build, given these letter counts?"**

To minimize a string lexicographically, you always want the **smallest available letters as early as possible**. Applied to the left half: place letters in ascending order (`a`s before `b`s before `c`s, etc.) — that's the smallest arrangement of any multiset of characters.

### Why is exactly one character allowed to have an odd count?
Because `s` is *guaranteed* palindromic already, its letter counts already satisfy the palindrome rule: at most one letter has an odd count (that one becomes the middle character, if the total length is odd); every other letter has an even count (split evenly between the two mirrored halves).

### The middle character's placement
Since the goal is the *smallest* palindrome, you might wonder if the odd-count letter should be squeezed in early — but it can't be. Its position is fixed at the exact center by the mirror structure, so there's no choice to make there; it just needs to be identified and dropped into the middle slot once the halves are built.

---

## ✅ Approach

1. **Count every letter's frequency** in `s` — one pass, `O(n)`.
2. **Build the left half in ascending letter order (`a` → `z`):**
   - For each letter with count `n_i`: its contribution to each half is `n_i / 2`.
   - If `n_i` is odd, remember this letter as the middle character, and treat the remaining count as even from here on.
   - Push `n_i / 2` copies of the letter into the answer (building the left half).
3. **Append the middle character**, if one was found.
4. **Build the right half in descending letter order (`z` → `a`)** using the same per-letter leftover counts — this produces the exact mirror of the left half, completing the palindrome.

---

## 🔍 Dry Run

**Input:** `s = "babab"` → counts: `a: 2, b: 3`

### Left half (ascending a → z)
| Letter | count | half (count/2) | odd? | pushed | ans so far |
|--------|-------|-----------------|------|--------|------------|
| a | 2 | 1 | no | `a` | `"a"` |
| b | 3 | 1 | yes → middle = `b` | `b` | `"ab"` |

### Middle
`odd = true` → append `b` → `"abb"`

### Right half (descending z → a), using leftover counts (both now `1`)
| Letter | leftover | pushed | ans so far |
|--------|----------|--------|------------|
| b | 1 | `b` | `"abbb"` |
| a | 1 | `a` | `"abbba"` |

**Final: `"abbba"`** ✅ matches expected output.

---

## ⏱️ Complexity

| | Complexity | Why |
|---|---|---|
| **Time** | `O(n)` | One pass to count letters (`O(n)`), plus two fixed `26`-length passes to build both halves (`O(26) = O(1)`) |
| **Space** | `O(n)` | For the output string; counting array itself is `O(26) = O(1)` |

`O(n)` is optimal here — you can't produce an `n`-length answer in less than `O(n)` time.

---

## 🔑 Pattern
**Frequency counting + greedy half-construction for palindrome problems.** Whenever a problem involves rearranging characters into the smallest/largest palindrome, the approach almost always reduces to: count frequencies, split each into a mirrored half, sort/greedily arrange just the half (ascending for smallest, descending for largest), then mirror it — the full-length brute-force search is never necessary.
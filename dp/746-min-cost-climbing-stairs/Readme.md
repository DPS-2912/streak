# 746. Min Cost Climbing Stairs
**Difficulty:** Easy
**Link:** https://leetcode.com/problems/min-cost-climbing-stairs/
**Topics:** Array, Dynamic Programming

---

## 📜 Problem Statement

Given an array `cost` where `cost[i]` is the cost of stepping on step `i`, and each move lets you climb 1 or 2 steps after paying that step's cost, return the minimum total cost to reach the top. You may start from index `0` or index `1`.

### Example 1
```
Input:  cost = [10,15,20]
Output: 15      → start at index 1, pay 15, climb two steps to the top
```

### Example 2
```
Input:  cost = [1,100,1,1,1,100,1,1,100,1]
Output: 6       → skip every "100" by always climbing 2 steps at the right moments
```

### Constraints
- `2 <= cost.length <= 1000`
- `0 <= cost[i] <= 999`

---

## 🧠 Intuition

This is [Climbing Stairs (70)](../70_Climbing_Stairs/problem.md) wearing a cost on its back. The core question is identical — **"what was the last move to reach step `i`?"** — but instead of *counting* how many ways there are, we're now *minimizing* the total price paid to get there.

Same two options as before:
- Arrived at step `i` via a **1-step** from `i-1`
- Arrived at step `i` via a **2-step** from `i-2`

Since we always have to pay `cost[i]` once we land on step `i`, the cheapest way to *be at* step `i` is:
```
ans[i] = cost[i] + min(ans[i-1], ans[i-2])
```
Swap `+` for `min` and "ways" for "cost," and it's the exact same recurrence shape as Climbing Stairs — this is the pattern showing its range already.

### The "top" is one step past the last index — don't miss this
The tricky part isn't the recurrence, it's the finish line. The **top of the floor is past the last stair**, meaning reaching it costs nothing extra beyond whichever of the last two steps you launch from. That's why the final answer is:
```
min(ans[n-1], ans[n-2])
```
and *not* `ans[n-1]` alone — you don't have to step on the very last stair if launching from the second-to-last one (a 2-step jump) is cheaper.

---

## ✅ Approach

1. `ans[i]` = minimum cost to **be standing on** step `i` (having already paid `cost[i]`).
2. **Base cases:** `ans[0] = cost[0]`, `ans[1] = cost[1]` — you're allowed to start at either, so both are "free" starting points that just cost their own step price.
3. **Transition** for `i` from `2` to `n-1`:
   ```
   ans[i] = cost[i] + min(ans[i-1], ans[i-2])
   ```
4. **Final answer:** `min(ans[n-1], ans[n-2])` — the top can be reached by a final 1-step from the last stair, or a final 2-step from the second-to-last, so take whichever is cheaper.

---

## 🔍 Dry Run

**Input:** `cost = [10, 15, 20]`

| i | ans[i] |
|---|--------|
| 0 | 10 (base) |
| 1 | 15 (base) |
| 2 | `cost[2] + min(ans[1], ans[0])` = `20 + min(15,10)` = `20 + 10` = **30** |

Final: `min(ans[2], ans[1])` = `min(30, 15)` = **15** ✅

Notice `ans[2]=30` is never actually the answer — it represents "cost to stand on step 2," which nobody needs to do, since jumping straight from step 1 to the top (skipping step 2 entirely) costs only `15`. This is exactly why the final `min(...)` step matters — the DP array tracks costs to *stand on* each step, but the question asks for the cost to get *past* them all.

---

## ⏱️ Complexity

| | Complexity | Why |
|---|---|---|
| **Time** | `O(n)` | Single pass building the `ans` array |
| **Space** | `O(n)` | Full `ans` array stored |

Same optimization opportunity as Climbing Stairs applies here: since `ans[i]` only depends on `ans[i-1]` and `ans[i-2]`, this can be rolled down to **`O(1)` space** using two rolling variables instead of a full array — worth doing as a follow-up once the array version feels natural.

---

## 🔑 Pattern
**1D DP, cost-minimization variant of "what was the last decision?"** Directly builds on the Climbing Stairs recurrence (`dp[i] = dp[i-1] OP dp[i-2]`), swapping the *ways-counting* operator (`+`) for a *cost-minimizing* one (`min` + `cost[i]`). The other twist to watch for going forward: **where exactly does the DP array's index line up with the actual question being asked** — here, "cost to stand on step i" isn't quite the same as "cost to finish," and that gap is where the real bug risk lives.
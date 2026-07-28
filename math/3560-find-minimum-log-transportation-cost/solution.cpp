class Solution {
public:
    long long minCuttingCost(int n, int m, int k) {
        if (n < k && m < k){
            return 0; // no need to cut logs, already fit in k
        }
        long long cost = 0 ;
        while(m>k){
            //cut the log m
            cost += 1LL * k*(m-k);
            m -= k;
        }
        while(n>k){
            //cut the log m
            cost += 1LL * k*(n-k);
            n -= k;
        }
        return cost;


    }
};
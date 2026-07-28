class Solution {
public:
    int climbStairs(int n) {
        if (n == 1 || n == 2 || n ==3){
            return n;
        }

        vector<int> steps(n+1,1);
        steps[2] = 2;
        steps[3] = 3;
        for(int i = 4 ; i<=n ; i++){
            steps[i] = steps[i-1] + steps[i-2];
        }
        return steps[n];
    }
};
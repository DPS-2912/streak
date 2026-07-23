class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if (n<=2) return n;
        int mask = 0 ;
        for (int i = 0; i<n ; i++){
            mask = mask | nums[i];
        }
        return mask + 1;
    }
};
class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        vector<int>missing;
        sort(nums.begin(), nums.end());
        int drift = nums[0];

        for(int i = 0 ; i<nums.size() ; i++){
            if (drift + i != nums[i]){
                missing.push_back(drift+i);
                drift = drift + 1;
                i -- ;
            }
        }
        return missing;

    }
};
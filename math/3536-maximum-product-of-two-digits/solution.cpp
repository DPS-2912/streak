class Solution {
public:
    int maxProduct(int n) {
        int temp_digit = n ;
        vector<int> digits;
        int max1 = INT_MIN;
        int max2 = max1;
        while (temp_digit > 0){
            int digit = temp_digit%10;
            temp_digit =temp_digit/10;
            if (digit >= max1){
                max2 = max1;
                max1 = digit;
            }
            else if (digit > max2)
            {
                max2 = digit;
            }
        }
        return max1*max2;

    }
};
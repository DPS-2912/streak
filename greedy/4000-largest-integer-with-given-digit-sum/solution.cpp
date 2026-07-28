class Solution {
public:
    int largestInteger(int n, int s) {
        if(s == 0){
            return 0;
        }
        // check s < max sum possible using n digits, 
        if (n == 1 && s<=9){
            return s;
        }
        if(s > (n*9)){
            return -1;
        }
        // for max possible digit, place first digit = 9 ;
        int temp = n;
        int ans = 0 ;
        while (temp > 0){
            if(s<=9){
                ans = (ans*10) + s;
                s = 0;
            }
            else{
                ans = (ans*10) + 9;
                s -= 9;
            }
            temp --;
        }
        return ans;
    }
};
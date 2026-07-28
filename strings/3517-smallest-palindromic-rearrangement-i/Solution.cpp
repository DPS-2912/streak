class Solution {
public:
    string smallestPalindrome(string s) {
        if (s.length() == 1){
            return s;
        }
        string ans = "";
        vector<int> count (26,0);
        for (int i = 0 ; i<s.length(); i++){
            char c = s[i];
            count[c-97]++;
        }  
        char temp;
        int odd = false;
        for (int i = 0 ; i<26 ; i++){
            int temp_count = count[i]/2;
            char c = 97 + i;
            if(count[i] % 2 == 1){
                temp = c;
                count[i]--;
                odd = true;
            }
            count[i] -= temp_count;
            while(temp_count>0){
                temp_count --;
                ans.push_back(c);
            }

        }
        if (odd){
            ans.push_back(temp);
        }        
        for (int i = 25 ; i>=0 ; i--){
            char c = 97 + i;
            while(count[i]>0){
                count[i] --;
                ans.push_back(c);
            }

        }
    
        return ans;
    }
};
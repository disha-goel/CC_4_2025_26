// UID:24BCS10773

// Brute Force Approach
// Time Complexity: O(N^2)
class SolutionBrute {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int count=0;
        for(int i=0;i<nums.size();i++){
            int product=1;
            for(int j=i;j<nums.size();j++){
                product*=nums[j];
                if(product<k){
                    count++;
                } else{
                    break;
                }
            }
        }
        return count;
    }
};


// Optimal Approach (Sliding Window)
// Time Complexity: O(N)
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if(k<=1){
            return 0;
        }
        int count=0;
        int l=0;
        long long product=1;
        for(int i=0;i<nums.size();i++){
            product*=nums[i];
            while(product>=k){
                product/=nums[l];
                l++;
            }
            count += (i-l+1);
        }
        return count;
    }
};

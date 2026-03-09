//UID:24BCS10773

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        long long total = 0;
        for (int x : nums) {
            total += x;
        }
        int remainder = total % p;
        if (remainder == 0) {
            return 0;
        }
        unordered_map<int, int> mp;
        mp[0] = -1;
        long long prefix = 0;
        int minLen = nums.size();
        for (int i = 0; i < nums.size(); i++) {
            prefix = (prefix + nums[i]) % p;
            int val = (prefix - remainder + p) % p;
            if (mp.count(val)) {
                minLen = min(minLen, i - mp[val]);
            }
            mp[prefix] = i;
        }
        if (minLen == nums.size()) {
            return -1;
        }
        return minLen;
    }
};

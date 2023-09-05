#include "base/TreeNode.hpp"

class Solution
{
public:
    int numTrees(int n)
    {
        vector<int> f(n + 1, 0);
        f[0] = 1;
        f[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            int left = 0;
            int right = i - 1;
            while (left <= i - 1)
            {
                f[i] += f[left] * f[right];
                left++;
                right--;
            }
        }
        return f[n];
    }
};
/*

238. Product of Array Except Self
---------------------------------
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

Example 1:
Input: nums = [1,2,3,4]
Output: [24,12,8,6]

Example 2:
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]

Constraints:
2 <= nums.length <= 105
-30 <= nums[i] <= 30

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 

Follow up: Can you solve the problem in O(1) extra space complexity? (The output array does not count as extra space for space complexity analysis.)

*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *productExceptSelf(int *nums, int numsSize, int *returnSize) 
{
    int *pre = malloc(numsSize*sizeof(int));
    int *post = malloc(numsSize*sizeof(int));
    int *anwser = malloc(numsSize*sizeof(int));
    *returnSize = numsSize;

    if (numsSize > 0) {
        pre[0] = 1;
    }
    if (numsSize > 1) {
        post[numsSize-1] = 1;
    }
    for (int i = 1; i < numsSize; i++) {
        pre[i] = nums[i-1] * pre[i-1];
    }
    for (int i = numsSize - 2; i >= 0; i--) {
        post[i] = nums[i+1] * post[i+1];
    }

    for (int i = 0; i < numsSize; i++) {
        anwser[i] = pre[i] * post[i];
    }
    return anwser;
}

bool intArrayEqual(int *a, int *b, int size)
{
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

#include "productarrayexpectself_tests.h"

int main() {
    struct test {
        char *name;
        int *nums;
        int numsSize;
        int *returnNums;
    };

    struct test tests[] = {
        {
            .name = "Example 1",
            .nums = (int[]){1,2,3,4},
            .numsSize = 4,
            .returnNums = (int[]){24,12,8,6},
        },
        {
            .name = "Example 2",
            .nums = (int[]){-1,1,0,-3,3},
            .numsSize = 5,
            .returnNums = (int[]){0,0,9,0,0},
        },
        {
            .name = "Example 3",
            .nums = (int[]){-1,1,1,-1,1},
            .numsSize = 5,
            .returnNums = (int[]){-1,1,1,-1,1},
        },
        {
            .name = "Big Test",
            .nums = (int*)bigTest,
            .numsSize = sizeof(bigTest) / sizeof(bigTest[0]),
            .returnNums = (int*)bigTest,
        },

    };

    int testsCount = sizeof(tests) / sizeof(struct test);

    for (int i = 0; i < testsCount; i++) {
        struct test t = tests[i];

        int gotSize;
        int *got = productExceptSelf(t.nums, t.numsSize, &gotSize);
        assert(got != NULL);

        printf("%s >> productExpectSelf(", t.name);
        for (int i = 0; i < t.numsSize; i++) printf("%d%s", t.nums[i], i!=t.numsSize-1?", ":"");
        printf(") = (");
        for (int i = 0; i < gotSize; i++) printf("%d%s", got[i], i!=gotSize-1?", ":"");
        printf("), expect => (");
        for (int i = 0; i < t.numsSize; i++) printf("%d%s", t.returnNums[i], i!=t.numsSize-1?", ":"");
        printf(")\n");

        assert(gotSize == t.numsSize);
        assert(intArrayEqual(got, t.returnNums, gotSize));
        free(got);

        printf("  ---- PASSED ----\n");
    } 

    printf("\n***** All test passed ******\n");

    return 0;
}


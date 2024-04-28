/*
334. Increasing Triplet Subsequence
-----------------------------------
Given an integer array nums, return true if there exists a triple of indices (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]. If no such indices exists, return false.

Example 1:
Input: nums = [1,2,3,4,5]
Output: true
Explanation: Any triplet where i < j < k is valid.

Example 2:
Input: nums = [5,4,3,2,1]
Output: false
Explanation: No triplet exists.

Example 3:
Input: nums = [2,1,5,0,4,6]
Output: true
Explanation: The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 < nums[5] == 6.

Constraints:
1 <= nums.length <= 5 * 105
-231 <= nums[i] <= 231 - 1

Follow up: Could you implement a solution that runs in O(n) time complexity and O(1) space complexity?

*/

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

/*

{20,100,10,12,5,13}

20]----
i=20

100]----
i=20,j=100,
i=100

10]----
i=20,j=100,
i=100
i=10

12]----
i=20,j=100,
i=100
i=10,12

5]----
i=20,j=100,
i=100
i=10,12

13]----
i=20,j=100,
i=100
i=10,12,13

 */

typedef struct {
    int num[2];
    int len;
} Triplett;

typedef struct {
    Triplett *trip;
    int len;
    int cap;
} Stack;

Stack *stack_push(Stack *stack, Triplett trip)
{
    size_t mincap = stack->len + 1;
    if (mincap >= stack->cap) {
        size_t newcap = mincap * 2;
        stack->trip = realloc(stack->trip, newcap * sizeof(Triplett));
        stack->cap = newcap;
    }
    stack->trip[stack->len++] = trip;
    return stack;
}

bool increasingTriplet(int* nums, int numsSize)
{
    if (numsSize < 3) return false;

    Stack stack = {0};
    
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        for (int j = 0; j < stack.len; j++) {
            Triplett *trip = &stack.trip[j]; 
            if (trip->len == 2) {
                if (trip->num[0] < trip->num[1] && trip->num[1] < num)
                    return true;
            } else if (trip->len == 1) {
                if (trip->num[0] < num) {
                    Triplett newtrip = *trip;
                    newtrip.num[1] = num;
                    newtrip.len++;
                    stack_push(&stack, newtrip);
                }
            }
        }
        Triplett newtrip;
        newtrip.num[0] = num;
        newtrip.num[1] = 0;
        newtrip.len = 1;
        stack_push(&stack, newtrip);
    }
    return false;
}

#include "increasingtriplet_testdata.h"

int main()
{
    struct test {
        char *name;
        int *nums;
        int numsSize;
        bool anwser;
    };

    struct test tests[] = {
        {
            .name = "Example 1",
            .nums = (int[]){1,2,3,4,5},
            .numsSize = 5,
            .anwser = true,
        },
        {
            .name = "Example 2",
            .nums = (int[]){5,4,3,2,1},
            .numsSize = 5,
            .anwser = false,
        },
        {
            .name = "Example 3",
            .nums = (int[]){2,1,5,0,4,6},
            .numsSize = 6,
            .anwser = true,
        },
        {
            .name = "Example 4",
            .nums = (int[]){20,100,10,12,5,13},
            .numsSize = 6,
            .anwser = true,
        },
        {
            .name = "Example 5",
            .nums = (int[]){1,5,0,4,1,3},
            .numsSize = 6,
            .anwser = true,
        },
        {
            .name = "Example 6",
            .nums = (int*)bigTest,
            .numsSize = sizeof(bigTest) / sizeof(bigTest[0]),
            .anwser = true,
        },
    };

    int testsCount = sizeof(tests) / sizeof(struct test);

    for (int i = 0; i < testsCount; i++) {
        struct test t = tests[i];

        bool got = increasingTriplet(t.nums, t.numsSize);

        printf("%s >> increasingTriplet(", t.name);
        for (int i = 0; i < t.numsSize; i++) printf("%d%s", t.nums[i], i!=t.numsSize-1?", ":"");
        printf(") = %s, but want %s\n", got?"true":"false", t.anwser?"true":"false");
        assert(got == t.anwser);

        printf("  ---- PASSED ----\n");
    } 

    printf("\n***** All test passed ******\n");

    return 0;
}


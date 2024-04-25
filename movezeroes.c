#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
// https://leetcode.com/problems/move-zeroes/?envType=study-plan-v2&envId=leetcode-75

void moveZeroes(int *nums, int numsSize) {

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0) {
            for (int j = i; j < numsSize; j++) {
                if (nums[j] != 0) {
                    int tmp = nums[j];
                    nums[j] = nums[i];
                    nums[i] = tmp;
                    break;
                }
            }
        }
    }
}

bool numsEq(int *nums1, int *nums2, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        if (nums1[i] != nums2[i])
            return false;
    }
    return true;
}

void printNums(int *nums, int numsSize) {
    printf("[");
    for (int i = 0; i < numsSize; i++) {
        printf("%d", nums[i]);
        if (i + 1 < numsSize)
            printf(",");
    }
    printf("]");
}

// [1,0,0,3,12]
int main() {

    struct test {
        char *name;
        int *input;
        int *output;
        size_t size;
    };

    struct test tests[] = {
        {
            .name = "Example 1",
            .input = (int[]){0, 1, 0, 3, 12},
            .output = (int[]){1, 3, 12, 0, 0},
            .size = 5,
        },
        {
            .name = "Example 2",
            .input = (int[]){0},
            .output = (int[]){0},
            .size = 1,
        },
    };

    int testsCount = sizeof(tests) / sizeof(struct test);
    
    for (int i = 0; i < testsCount; i++) {
        struct test t = tests[i];

        printf("%s: ", t.name);
        printNums(t.input, t.size);
     
        // SUT - System Under Test
        moveZeroes(t.input, t.size);

        printf(" -> ");
        printNums(t.input, t.size);
        printf(" : expect ");
        printNums(t.output, t.size);
        printf("\n");

        assert(numsEq(t.input, t.output, t.size));
    }

    printf("\n***** All test passed ******\n");

    return 0;
}

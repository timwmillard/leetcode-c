#include <stdlib.h>
#include <stdbool.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool *kidsWithCandies(int *candies, int candiesSize, int extraCandies,
                      int *returnSize) {

    int maxCandies = 0;
    for (int i = 0; i < candiesSize; i++) {
        if (candies[i] > maxCandies)
            maxCandies = candies[i];
    }

    bool *results = malloc(sizeof(bool) * candiesSize);
    for (int i = 0; i < candiesSize; i++) {
        results[i] = candies[i] + extraCandies >= maxCandies;
    }

    *returnSize = candiesSize;

    return results;
}

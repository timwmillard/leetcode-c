#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n) {

    for (int i = 0; i < flowerbedSize; i++) {
        bool plot = flowerbed[i];
        bool left = true;
        bool right = true;
        if (i > 0)
            left = flowerbed[i-1];
        if (i < flowerbedSize - 1)
            right = flowerbed[i+1];

        bool canPlant = !plot && !left && !right;
        if (canPlant)
            n--;

    }
    return n <= 0;
}

int main() {

    int flowerbed1[] = {1, 0, 0, 0, 1};
    bool got1 = canPlaceFlowers(flowerbed1, 5, 1);
    printf("got1 = %s\n", got1? "true" : "false");
    assert(got1 == true);

    int flowerbed2[] = {1, 0, 0, 0, 1};
    bool got2 = canPlaceFlowers(flowerbed2, 5, 2);
    printf("got2 = %s\n", got2? "true" : "false");
    assert(got2 == false);

    int flowerbed3[] = {1, 0, 0, 0, 0, 1};
    bool got3 = canPlaceFlowers(flowerbed3, 6, 2);
    printf("got3 = %s\n", got3? "true" : "false");
    assert(got3 == false);

    return 0;
}

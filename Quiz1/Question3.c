#include <stdlib.h>
#include <stdbool.h>

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

bool containsDuplicate(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), cmp);

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == nums[i - 1])
            return true;
    }
    return false;
}

int main(){

    int nums[] = {1,2,3,4,5,6,5,3,2};

    bool result = containsDuplicate(nums, sizeof(nums));

    if(result){
        printf("The array contain duplicates.");
    }else{
        printf("The array doesn't contain duplicates.");
    }
    
}
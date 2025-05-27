int singleNumber(int* nums, int numsSize) {
    int result = 0;
    for (int i = 0; i < numsSize; i++) {
        result ^= nums[i];
    }
    return result;
}

int main(){

    int nums[] = {1,2,3,4,5,6,5,3,2};

    int result = singleNumber(nums, sizeof(nums));

    printf("Result: %d", result);
}
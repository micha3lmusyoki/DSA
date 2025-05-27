int removeDuplicates(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    int i = 0; // Slow pointer

    for (int j = 1; j < numsSize; j++) {
        if (nums[j] != nums[i]) {
            i++;
            nums[i] = nums[j];
        }
    }

    return i + 1; // New length
}

int main(){

    int nums[] = {1,2,3,4,5,6,5,3,2};

    int result = removeDuplicates(nums, sizeof(nums));

    printf("Result: %d", result);
}
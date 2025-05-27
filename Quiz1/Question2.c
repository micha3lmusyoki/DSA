void rotate(int* nums, int k) {
    int n = sizeof(nums);
    k = k % n;
    int temp[n];

    for (int i = 0; i < k; i++) {
        temp[i] = nums[n - k + i];
    }

    for (int i = k; i < n; i++) {
        temp[i] = nums[i - k];
    }

    for (int i = 0; i < n; i++) {
        nums[i] = temp[i];
    }

}

int main(){

    int nums[] = {1,2,3,4,5,6,5,3,2};

    rotate(nums, 2);

    for (int i = 0; i < sizeof(nums); i++) {
        printf("%d ", nums[i]);
    }
}
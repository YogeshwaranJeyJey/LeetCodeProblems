int countWhileMerge(long* sums, int left, int right, int lower, int upper) {
    if (right - left <= 1) return 0;
    int mid = (left + right) / 2;
    int count = countWhileMerge(sums, left, mid, lower, upper) +
                countWhileMerge(sums, mid, right, lower, upper);

    int j = mid, k = mid, t = mid;
    long cache[right - left];
    int r = 0;

    for (int i = left; i < mid; i++) {
        while (k < right && sums[k] - sums[i] < lower) k++;
        while (j < right && sums[j] - sums[i] <= upper) j++;
        count += j - k;
    }

    int i = left, m = mid;
    int idx = 0;
    while (i < mid && m < right) {
        if (sums[i] < sums[m]) cache[idx++] = sums[i++];
        else cache[idx++] = sums[m++];
    }
    while (i < mid) cache[idx++] = sums[i++];
    while (m < right) cache[idx++] = sums[m++];

    for (i = 0; i < idx; i++)
        sums[left + i] = cache[i];

    return count;
}

int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    long* prefix = (long*)malloc((numsSize + 1) * sizeof(long));
    prefix[0] = 0;
    for (int i = 0; i < numsSize; i++)
        prefix[i + 1] = prefix[i] + nums[i];

    int result = countWhileMerge(prefix, 0, numsSize + 1, lower, upper);
    free(prefix);
    return result;
}
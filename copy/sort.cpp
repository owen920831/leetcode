void bubble_sort(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++) {
            if (nums[i] > nums[j])
                swap(nums[i], nums[j]);
        }
    }   
}

void select_sort(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; i++){
        int mn_idx = i;
        for (int j = i+1; j < n; j++) {
            if (nums[mn_idx] > nums[j])
                mn_idx = j;
        }
        swap(nums[i], nums[mn_idx]);
    }   
}

auto insert_sort = [](vector<int>& nums) {
    int n = nums.size();
    for (int i = 1; i < n; i++) { // 默認i=0已經排序
        int key = nums[i];
        int j = i - 1; //以排序的末尾
        while (j >= 0 && nums[j] > key) { // 比key大的往後移一位
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = key; //插入
    }
};

function<void(vector<int>&, int, int)> merge_sort_rec; // 前向宣告
auto merge_func = [](vector<int>& nums, int l, int m, int r) {
    vector<int> left(nums.begin() + l, nums.begin() + m + 1);
    vector<int> right(nums.begin() + m + 1, nums.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) nums[k++] = left[i++];
        else nums[k++] = right[j++];
    }
    while (i < left.size()) nums[k++] = left[i++];
    while (j < right.size()) nums[k++] = right[j++];
};
auto merge_sort_rec = [&](vector<int>& nums, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    merge_sort_rec(nums, l, m);
    merge_sort_rec(nums, m + 1, r);
    merge_func(nums, l, m, r);
};
auto merge_sort = [&](vector<int>& nums) {
    merge_sort_rec(nums, 0, nums.size() - 1);
};

function<void(vector<int>&, int, int)> quick_sort_rec;
auto partition_func = [](vector<int>& nums, int low, int high) {
    int pivot = nums[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (nums[j] < pivot) swap(nums[++i], nums[j]);
    }
    swap(nums[i + 1], nums[high]);
    return i + 1;
};
auto quick_sort_rec = [&](vector<int>& nums, int low, int high) {
    if (low < high) {
        int pi = partition_func(nums, low, high);
        quick_sort_rec(nums, low, pi - 1);
        quick_sort_rec(nums, pi + 1, high);
    }
};
auto quick_sort = [&](vector<int>& nums) {
    quick_sort_rec(nums, 0, nums.size() - 1);
};

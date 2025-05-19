vector<int> manacher(string &s) {
    string t = "^";
    for (char c : s) {
        t += '#';
        t += c;
    }
    t += "#$";

    vector<int> half_len(t.length() - 2);
    half_len[1] = 1;
    int box_m = 0, box_r = 0, max_i = 0;
    for (int i = 2; i < half_len.size(); i++) {
        int hl = 1;
        if (i < box_r) {
            hl = min(half_len[box_m * 2 - i], box_r - i);
        }
        while (t[i - hl] == t[i + hl]) {
            hl++;
            box_m = i;
            box_r = i + hl;
        }

        half_len[i] = hl;
    }
    return half_len;
}
// Z-function : 后缀的前缀
vector<int> cal_z(string &s) {
    int m = s.size();
    vector<int> z(m, 0);
    int bl = 0, br = 0;
    for (int i = 1; i < m; i++){
        if (i <= br){
            z[i] = min(z[i-bl], br-i+1);
        }
        while (i + z[i] < m && s[z[i]] == s[i + z[i]]) {
            bl = i;
            br = i + z[i];
            z[i]++;
        }
    }
    z[0] = m;
    return z;
}
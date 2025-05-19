    int kmp(vector<int> &text, vector<int> &pattern) {
        int m = pattern.size();
        vector<int> pi(m);
        int c = 0;
        // Compute the pi[i] := the length of the longest prefix of pattern[0..i] which is also a suffix of pattern[0..i]
        for (int i = 1; i < m; i++) {
            int v = pattern[i];
            while (c && pattern[c] != v) {
                c = pi[c - 1];
            }
            if (pattern[c] == v) {
                c++;
            }
            pi[i] = c;
        }
        
        // Find the number of occurrences of pattern in text
        int cnt = 0;
        c = 0;
        for (int i = 0; i < text.size(); i++) {
            int v = text[i];
            while (c && pattern[c] != v) {
                c = pi[c - 1];
            }
            if (pattern[c] == v) {
                c++;
            }
            if (c == m) {
                cnt++;
                c = pi[c - 1];
            }
        }
        return cnt;
    }
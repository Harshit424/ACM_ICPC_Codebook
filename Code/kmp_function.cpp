/*
    where π[i] is the length of the longest proper prefix of the substring s[0…i] which is also a suffix of this substring. A proper prefix of a string is a prefix that is not equal to the string itself. By definition, π[0]=0. 

    in short, π[i] => max length s.t prefix of s[0..i] is same as suffix of s[0..i]
*/
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

#include <iostream>
#include <vector>
using namespace std;

void computeLPS(const string& pat, vector<int>& lps) {
  int len = lps[0] = 0;
  int i = 1;
  int nPat = pat.length();

  while (i < nPat) {
    if (pat[i] == pat[len]) lps[i++] = ++len;
    else if (len != 0) len = lps[len - 1];
    else lps[i++] = 0;
  }
}

int KMPSearch(const string& text, const string& pat) {
  int m = pat.length();
  int n = text.length();
  vector<int> lps(m);
  computeLPS(pat, lps);

  int i = 0, j = 0;
  while (i < n) {
    if (pat[j] == text[i]) i++, j++;

    if (j == m) return i - j;
    else if (i < n && pat[j] != text[i]) {
      if (j != 0) j = lps[j - 1];
      else i++;
    }
  }

  return -1;
}

bool isValid(const vector<string>& code) {
  string stack;
  for (const string& line : code) {
    for (char ch : line) {
      if (ch == '(') stack.push_back(ch);
      else if (ch == ')') {
        if (stack.empty() || stack.back() != '(') return false;
        stack.pop_back();
      }
    }
  }

  return stack.empty();
}

int main() {
  int n;
  cin >> n;
  cin.ignore();
  vector<string> code(n);

  for (int i = 0; i < n; i++) getline(cin, code[i]);
  bool valid = isValid(code);
  cout << "Validasi Kurung:" << (valid ? "" : " Tidak") << " Seimbang\n";

  string pattern;
  cin >> pattern;

  bool found = false;
  for (int i = 0; i < n; i++) {
    int pos = KMPSearch(code[i], pattern);
    if (pos != -1) {
      found = true;
      cout << "Substring ditemukan pada [" << i + 1 << ", " << pos + 1 << "]\n";
    }
  }

  if (!found) cout << "Substring tidak ditemukan\n";
}

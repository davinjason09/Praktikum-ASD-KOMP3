#include <iostream>
#include <vector>
using namespace std;

struct Node {
  char op;
  Node* next;

  Node(char op) : op(op), next(nullptr) {}
};

class Stack {
private:
  Node* top;

public:
  Stack() : top(nullptr) {}

  void push(char op);
  char pop();
  char peek() const;
  bool isEmpty() const;
};

void Stack::push(char op) {
  Node* newNode = new Node(op);
  newNode->next = top;
  top = newNode;
}

char Stack::pop() {
  if (isEmpty()) throw runtime_error("Stack is empty");

  Node* temp = top;
  char op = top->op;
  top = top->next;
  delete temp;
  return op;
}

char Stack::peek() const {
  if (isEmpty()) throw runtime_error("Stack is empty");
  return top->op;
}

bool Stack::isEmpty() const {
  return top == nullptr;
}

void computeLPS(const string& pat, vector<int>& lps) {
  int len = lps[0] = 0;
  int i = 1;
  int nPat = pat.length();

  while (i < nPat) {
    if (pat[i] == pat[len]) lps[i++] = ++len;
    else {
      if (len != 0) len = lps[len - 1];
      else lps[i++] = 0;
    }
  }
}

vector<int> KMPSearch(const string& text, const string& pattern) {
  int m = pattern.length();
  int n = text.length();
  vector<int> res;
  vector<int> lps(m);
  computeLPS(pattern, lps);

  int i = 0, j = 0;
  while (i < n) {
    if (pattern[j] == text[i]) i++, j++;

    if (j == m) res.push_back(i - j), j = lps[j - 1];
    else if (i < n && pattern[j] != text[i]) {
      if (j != 0) j = lps[j - 1];
      else i++;
    }
  }

  return res;
}

bool isValid(const vector<string>& code) {
  Stack stack;
  for (const string& line : code) {
    for (char ch : line) {
      if (ch == '(') stack.push(ch);
      else if (ch == ')' && (stack.isEmpty() || stack.pop() != '(')) return false;
      else continue;
    }
  }

  return stack.isEmpty();
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
    vector<int> pos = KMPSearch(code[i], pattern);
    if (!pos.empty()) {
      found = true;
      for (int p : pos) cout << "Substring ditemukan pada [" << i + 1 << ", " << p + 1 << "]\n";
    }
  }

  if (!found) cout << "Substring tidak ditemukan\n";
}

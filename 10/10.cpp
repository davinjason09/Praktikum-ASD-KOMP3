#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
  string text;
  Node* next;

  Node(string t) : text(t), next(nullptr) {}
};

class Stack {
private:
  Node* top;

public:
  Stack();
  ~Stack();

  void push(const string& text);
  string pop();
  bool isEmpty() const;
  string peek() const;
  string getAll() const;
};

Stack::Stack() : top(NULL) {}

Stack::~Stack() {
  while (!isEmpty()) pop();
}

void Stack::push(const string& text) {
  Node* newNode = new Node(text);
  newNode->next = top;
  top = newNode;
}

string Stack::pop() {
  if (isEmpty()) {
    cout << "Stack is empty\n";
    return "";
  }

  Node* temp = top;
  string poppedText = top->text;
  top = top->next;
  delete temp;
  return poppedText;
}

bool Stack::isEmpty() const {
  return top == NULL;
}

string Stack::peek() const {
  if (isEmpty()) {
    cout << "Stack is empty\n";
    return "";
  }
  return top->text;
}

string Stack::getAll() const {
  string result;
  Node* current = top;
  while (current != NULL) {
    result = current->text + result;
    current = current->next;
  }
  return result;
}

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

void WRITE(const string& text, Stack& undo, Stack& redo) {
  undo.push(text);
  redo = Stack();
}

void UNDO(Stack& undo, Stack& redo) {
  if (undo.isEmpty()) {
    cout << "Nothing to undo\n";
    return;
  }
  string lastText = undo.pop();
  redo.push(lastText);
}

void REDO(Stack& undo, Stack& redo) {
  if (redo.isEmpty()) {
    cout << "Nothing to redo\n";
    return;
  }
  string lastText = redo.pop();
  undo.push(lastText);
}

void FIND(Stack& undo) {
  string pattern;
  cin.ignore();
  getline(cin, pattern);

  string text = undo.getAll();
  int index = KMPSearch(text, pattern);
  if (index != -1) cout << "Kata ditemukan pada indeks " << index << '\n';
  else cout << "Kata tidak ditemukan\n";
}

int main() {
  Stack undo, redo;
  int n;
  cin >> n;

  while (n--) {
    string command;
    cin >> command;

    if (command == "WRITE") {
      string text;
      cin.ignore();
      getline(cin, text);
      WRITE(text, undo, redo);
    } else if (command == "UNDO") {
      UNDO(undo, redo);
    } else if (command == "REDO") {
      REDO(undo, redo);
    } else if (command == "PRINT") {
      cout << undo.getAll() << '\n';
    } else if (command == "FIND") {
      FIND(undo);
    }
  }
}

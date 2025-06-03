#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
  string title;
  string author;
  int year;

  Node* left;
  Node* right;
  Node(string t, string a, int y) : title(t), author(a), year(y), left(NULL), right(NULL) {}
};

class AVLTree {
private:
  Node* root;

  int height(Node* node);
  int balanceFactor(Node* node);
  Node* rightRotate(Node* y);
  Node* leftRotate(Node* x);
  Node* add(Node* node, string title, string author, int year);
  void inOrder(Node* node);

public:
  AVLTree();

  void add(string title, string author, int year);
  void inOrder();
  Node* getRoot();
};

AVLTree::AVLTree() : root(NULL) {}

int AVLTree::height(Node* node) {
  if (node == NULL) return 0;
  return 1 + max(height(node->left), height(node->right));
}

int AVLTree::balanceFactor(Node* node) {
  if (node == NULL) return 0;
  return height(node->left) - height(node->right);
}

Node* AVLTree::rightRotate(Node* y) {
  Node* x = y->left;
  Node* T2 = x->right;

  x->right = y;
  y->left = T2;

  return x;
}

Node* AVLTree::leftRotate(Node* x) {
  Node* y = x->right;
  Node* T2 = y->left;

  y->left = x;
  x->right = T2;

  return y;
}

Node* AVLTree::add(Node* node, string title, string author, int year) {
  if (node == NULL) return new Node(title, author, year);

  if (title < node->title) {
    node->left = add(node->left, title, author, year);
  } else if (title > node->title) {
    node->right = add(node->right, title, author, year);
  } else {
    return node;  // Duplicate titles are not allowed
  }

  int balance = balanceFactor(node);

  // Left Left Case
  if (balance > 1 && title < node->left->title) { return rightRotate(node); }

  // Right Right Case
  if (balance < -1 && title > node->right->title) { return leftRotate(node); }

  // Left Right Case
  if (balance > 1 && title > node->left->title) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Right Left Case
  if (balance < -1 && title < node->right->title) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

void AVLTree::add(string title, string author, int year) {
  root = add(root, title, author, year);
}

void AVLTree::inOrder(Node* node) {
  if (node == NULL) return;

  inOrder(node->left);
  cout << "Title: " << node->title << ", Author: " << node->author << ", Year: " << node->year
       << endl;
  inOrder(node->right);
}

void AVLTree::inOrder() {
  inOrder(root);
}

Node* AVLTree::getRoot() {
  return root;
}

void computeLPS(const string& pattern, vector<int>& lps) {
  int len = 0;
  int i = 1;
  int nPat = (int)pattern.size();

  while (i < nPat) {
    if (pattern[i] == pattern[len]) lps[i++] = ++len;
    else if (len != 0) len = lps[len - 1];
    else lps[i++] = 0;
  }
}

int KMPSearch(const string& text, const string& pattern) {
  int M = pattern.length();
  int N = text.length();
  vector<int> lps(M, 0);

  computeLPS(pattern, lps);

  int i = 0;
  int j = 0;
  while (i < N) {
    if (pattern[j] == text[i]) i++, j++;

    if (j == M) {
      return i - j;
    } else if (i < N && pattern[j] != text[i]) {
      if (j != 0) j = lps[j - 1];
      else i++;
    }
  }
  return -1;
}

void FIND(Node* root, const string& pattern, const string& type, vector<Node*>& result) {
  if (root == NULL) return;

  if (type == "JUDUL" && KMPSearch(root->title, pattern) != -1) {
    result.push_back(root);
  } else if (type == "PENULIS" && KMPSearch(root->author, pattern) != -1) {
    result.push_back(root);
  }

  FIND(root->left, pattern, type, result);
  FIND(root->right, pattern, type, result);
}

void FIND(Node* root, int year, vector<Node*>& result) {
  if (root == NULL) return;

  if (root->year == year) { result.push_back(root); }

  FIND(root->left, year, result);
  FIND(root->right, year, result);
}

int main() {
  AVLTree library;
  int n;
  cin >> n;

  while (n--) {
    string title, author;
    int year;
    cin.ignore();
    getline(cin, title);
    getline(cin, author);
    cin >> year;
    library.add(title, author, year);
  }

  int m;
  cin >> m;

  while (m--) {
    string type;
    cin >> type;

    string pattern;
    int year;
    vector<Node*> result;
    if (type == "TAHUN") {
      cin >> year;
      FIND(library.getRoot(), year, result);
    } else {
      cin.ignore();
      getline(cin, pattern);
      FIND(library.getRoot(), pattern, type, result);
    }

    cout << "Hasil untuk query " << type << ' ' << pattern << ":\n";
    if (result.empty()) cout << "Tidak ada buku yang mengandung query tersebut.\n";
    else {
      for (const auto& book : result)
        cout << "- " << book->title << ", " << book->author << ", " << book->year << '\n';
    }
  }
}

#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct Node {
  string key;
  Node *left, *right;

  Node(const string& k) : key(k), left(nullptr), right(nullptr) {}

  Node* add(Node* root, const string& key) {
    if (!root) return new Node(key);

    if (key < root->key) root->left = add(root->left, key);
    else if (key > root->key) root->right = add(root->right, key);
    return root;
  }

  Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left) current = current->left;

    return current;
  }

  Node* remove(Node* root, const string& key) {
    if (!root) return root;

    if (key < root->key) root->left = remove(root->left, key);
    else if (key > root->key) root->right = remove(root->right, key);
    else {
      if (!root->left) {
        Node* temp = root->right;
        delete root;
        return temp;
      } else if (!root->right) {
        Node* temp = root->left;
        delete root;
        return temp;
      }

      Node* temp = minValueNode(root->right);
      root->key = temp->key;
      root->right = remove(root->right, temp->key);
    }

    return root;
  }

  void inorder(Node* root) {
    if (!root) return;

    inorder(root->left);
    cout << root->key << ' ';
    inorder(root->right);
  }
};

class BST {
public:
  Node* root;

  BST() : root(nullptr) {}

  void add(const string& key) {
    root = root->add(root, key);
  }

  void remove(const string& key) {
    root = root->remove(root, key);
  }

  void inorder() {
    root->inorder(root);
    cout << '\n';
  }
};

void computeLPSArray(const string& pat, vector<int>& lps) {
  int len = lps[0] = 0;
  int i = 1;
  int nPat = (int)pat.length();

  while (i < nPat) {
    if (pat[i] == pat[len]) {
      lps[i++] = ++len;
    } else {
      if (len != 0) len = lps[len - 1];
      else lps[i++] = 0;
    }
  }
}

bool KMPSearch(const string& pat, const string& txt) {
  int M = pat.length();
  int N = txt.length();
  vector<int> lps(M);

  computeLPSArray(pat, lps);

  int i = 0, j = 0;

  while (i < N) {
    if (pat[j] == txt[i]) i++, j++;

    if (j == M) return true;
    else if (i < N && pat[j] != txt[i]) {
      if (j != 0) j = lps[j - 1];
      else i++;
    }
  }

  return false;
}

bool checkSpam(const string& text, Node* root) {
  if (!root) return false;

  queue<Node*> q;
  q.push(root);
  while (!q.empty()) {
    Node* current = q.front();
    q.pop();

    if (KMPSearch(current->key, text)) return true;
    if (current->left) q.push(current->left);
    if (current->right) q.push(current->right);
  }

  return false;
}

int main() {
  BST bst;
  int n;
  cin >> n;

  while (n--) {
    string command, key;
    cin >> command >> key;

    if (command == "TAMBAH") bst.add(key);
    else if (command == "HAPUS") bst.remove(key);
    else { cout << "Perintah tidak dikenal\n", n++; }
  }

  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    string text;
    cin.ignore();
    getline(cin, text);

    bool isSpam = checkSpam(text, bst.root);
    cout << "Email " << i + 1 << ": " << (isSpam ? "SPAM" : "AMAN") << '\n';
  }
}

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
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

class Heap {
private:
  int size;
  vector<int> arr;

  void heapify(int i);

public:
  Heap(int capacity);
  ~Heap();

  void push(int key);
  int top();
  int pop();
  void remove(int key);
  void printHeap();
};

Heap::Heap(int capacity) {
  this->size = 0;
  arr.resize(capacity);
}

Heap::~Heap() {
  arr.clear();
  size = 0;
}

void Heap::heapify(int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < size && arr[left] > arr[largest]) largest = left;

  if (right < size && arr[right] > arr[largest]) largest = right;

  if (largest != i) {
    swap(arr[i], arr[largest]);
    heapify(largest);
  }
}

void Heap::push(int key) {
  size++;
  int i = size - 1;
  arr[i] = key;

  while (i != 0 && arr[(i - 1) / 2] < arr[i]) {
    swap(arr[i], arr[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

int Heap::top() {
  if (size == 0) return -1;
  return arr[0];
}

int Heap::pop() {
  if (size <= 0) return -1;
  if (size == 1) {
    size--;
    return arr[0];
  }

  int root = arr[0];
  arr[0] = arr[size - 1];
  size--;
  heapify(0);

  return root;
}

void Heap::remove(int key) {
  int index = -1;
  for (int i = 0; i < size; i++) {
    if (arr[i] == key) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    cout << "Key not found\n";
    return;
  }

  if (index == size - 1) {
    size--;
    return;
  }

  arr[index] = arr[--size];
  heapify(index);
}

void Heap::printHeap() {
  cout << "Heap: ";
  for (int i = 0; i < size; i++) cout << arr[i] << " ";
  cout << "\n";
}

int getPriority(const string& str) {
  if (str == "TINGGI") return 3;
  else if (str == "MEDIUM") return 2;
  else if (str == "RENDAH") return 1;
  else {
    cout << "Invalid priority string: " << str << "\n";
    throw invalid_argument("Invalid priority string");
  }
}

string getPriorityString(int priority) {
  switch (priority) {
    case 3: return "TINGGI";
    case 2: return "MEDIUM";
    case 1: return "RENDAH";
    default: return "UNKNOWN";
  }
}

int main() {
  int n;
  cin >> n;

  vector<pair<string, string>> words(n);
  for (int i = 0; i < n; i++) {
    string word, priority;
    cin >> word >> priority;
    words[i] = {word, priority};
  }

  int m;
  cin >> m;
  cin.ignore();
  for (int i = 0; i < m; i++) {
    string text;
    getline(cin, text);

    Heap heap(100);
    vector<pair<int, int>> wordPos;
    for (const auto& [word, priority] : words) {
      int pos = KMPSearch(text, word);
      if (pos != -1) {
        heap.push(getPriority(priority));
        wordPos.push_back({pos, word.size()});
      }
    }

    cout << "Unggahan " << i + 1 << ": ";
    if (heap.top() == -1) cout << "AMAN\n";
    else {
      cout << "Tingkat sensitivitas " << getPriorityString(heap.top()) << "\n";
      sort(wordPos.begin(), wordPos.end());
      int currPos = 0;
      for (size_t i = 0; i < text.size(); i++) {
        auto [pos, len] = wordPos[currPos];

        if (i == pos) {
          cout << "[REDACTED]";
          i += len - 1;
          currPos++;
        } else {
          cout << text[i];
        }
      }
      cout << '\n';
    }
  }
}

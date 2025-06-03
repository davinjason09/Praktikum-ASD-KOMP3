#include <iostream>
using namespace std;

struct Node {
  string name;
  Node* next;
  bool isEmergency = false;

  Node(string name) : name(name), next(NULL) {}
};

class Queue {
private:
  Node* head;
  Node* tail;

public:
  Queue() : head(NULL), tail(NULL) {}

  void enqueueNormal(string value);
  void enqueueEmergency(string value);
  string dequeue();
};

void Queue::enqueueNormal(string value) {
  Node* newNode = new Node(value);
  if (tail) tail->next = newNode;
  else head = newNode;
  tail = newNode;
}

void Queue::enqueueEmergency(string value) {
  Node* newNode = new Node(value);

  if (head == NULL) head = tail = newNode;
  else if (head->isEmergency) {
    Node* curr = head;
    while (curr->next && curr->next->isEmergency) curr = curr->next;

    newNode->next = curr->next;
    curr->next = newNode;
  } else {
    newNode->next = head;
    head = newNode;
  }
}

string Queue::dequeue() {
  if (!head) return "";

  Node* temp = head;
  head = head->next;

  if (head == NULL) tail = NULL;

  string name = temp->name;
  delete temp;
  return name;
}

int main() {
  int n;
  cin >> n;
  Queue q;

  for (int i = 0; i < n; i++) {
    string action;
    cin >> action;

    if (action == "DATANG") {
      char type;
      string name;
      cin >> type >> name;

      if (type == 'N') q.enqueueNormal(name);
      else if (type == 'E') q.enqueueEmergency(name);
    } else if (action == "LAYANI") {
      string name = q.dequeue();

      if (name.empty()) cout << "Tidak ada pasien\n";
      else cout << name << '\n';
    } else {
      cout << "Perintah tidak dikenal\n";
      i--;
    }
  }

  return 0;
}

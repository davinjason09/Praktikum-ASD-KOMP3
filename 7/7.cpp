#include <iostream>
using namespace std;

struct Node {
  string name;
  int apptTime;
  Node* next;

  Node(string name, int apptTime) : name(name), apptTime(apptTime), next(NULL) {}
};

class Queue {
private:
  Node* head;
  Node* tail;

public:
  Queue() : head(NULL), tail(NULL) {}
  ~Queue();

  void enqueue(string name, int apptTime);
  string dequeue();
  void printList();
};

Queue::~Queue() {
  while (head) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }
}

void Queue::enqueue(string name, int apptTime) {
  Node* newNode = new Node(name, apptTime);

  if (!head && !tail) {
    head = tail = newNode;
    return;
  }

  if (apptTime == -1) {
    tail->next = newNode;
    tail = newNode;
  } else {
    if (head->apptTime == -1 || head->apptTime > apptTime) {
      newNode->next = head;
      head = newNode;
      if (!tail) tail = newNode;
    } else {
      Node* curr = head;
      while (curr->next && curr->next->apptTime <= apptTime && curr->next->apptTime != -1)
        curr = curr->next;

      newNode->next = curr->next;
      curr->next = newNode;
      if (!newNode->next) tail = newNode;
    }
  }
}

string Queue::dequeue() {
  if (!head) return "";

  Node* temp = head;
  head = head->next;

  if (!head) tail = NULL;

  string name = temp->name;
  delete temp;
  return name;
}

void Queue::printList() {
  Node* curr = head;
  while (curr) {
    cout << curr->name << " (" << curr->apptTime << ") ";
    curr = curr->next;
    if (curr) cout << "-> ";
  }
  cout << '\n';
}

int main() {
  Queue queue;
  int n;
  cin >> n;

  string action;
  while (n--) {
    cin >> action;

    if (action == "DATANG") {
      string name;
      int apptTime;
      cin >> name >> apptTime;
      queue.enqueue(name, apptTime);
    } else if (action == "LAYANI") {
      string served = queue.dequeue();
      if (served.empty()) cout << "Tidak ada pasien \n";
      else cout << served << '\n';
    } else if (action == "PRINT") {
      queue.printList();
    } else {
      cout << "Perintah tidak dikenal\n";
      n++;
    }
  }
}

// COMSC-210 | Midterm #1 | Andrei Buchatskiy
// IDE used : Visual Studio Code

#include <iostream>
using namespace std;

// constant integers, used just in the dummy statement
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    // first private variable is a struct Node, which is one element in the double linked list
    struct Node {
        int data; // the data value stored at the given node
        Node* prev; // pointer to the previous node in the list
        Node* next; // pointer to the next node in the list

        // the node constructor, intializes values for a new ndoe
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; // sets the data value to the given val
            prev = p; // previous link is set to nullptr if not given, if given then it is set to the given p value
            next = n; // next link is set to nullptr if not given, if given then it is set to the given n value
        }
    };

    Node* head; // pointer to the first ndoe in list
    Node* tail; // pointer to last node in list

public:
    // default constructor, gives you an empty list start
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // insert new node with given value after the node at given position
    void insert_after(int value, int position) {
        // first check for negative position, if  position is negative then tell the user and exit the function (without adding the given value anywhere)
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        // allocate new node with the given value
        Node* newNode = new Node(value);
        // if thelist is empty than the new node is now both the head and the tail
        if (!head) {
            head = tail = newNode;
            // exit the function after setting the node as both head and tail
            return;
        }

        // temp node starting at the head used to walk through the list until you reach the given position
        Node* temp = head;
        // loop until you reach given position (and as long as temp exists and is not null)
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next; // move to next

        // if the position is longer than the list, than dont add the node and exit the function
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;  // free the node created previously
            return; // exit the function
        }

        // link the newNode next to node that was after the temp node (which is now at the position we want to insert after)
        newNode->next = temp->next;
        // link the newNode prev to the temp node (which is at the position we need the newNode to be directly after)
        newNode->prev = temp;
        // check if the temp node was not the tail node
        if (temp->next)
            temp->next->prev = newNode; // make it so the node that was after temp now is linked prev to newNode, so it now is after newNode
        else // check if the temp node was the tail
            tail = newNode; // if so set the newNode to be the tail
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    return 0;
}

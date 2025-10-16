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
        temp->next = newNode; // now link the given position node next to the newNode
    }

    // delete the given value if found in the list
    void delete_val(int value) {
        // if list is empty just exit the function
        if (!head) return;

        // start walking from the head
        Node* temp = head;
        
        // walk until the value is found (or list is done)
        while (temp && temp->data != value)
            temp = temp->next; // move to next

        // if youve gone through the list and havent found the value, then exit the function without deleting anything
        if (!temp) return; 

        // temp is not the head link the previous node to the next node (essentially cut the temp nodes connections)
        if (temp->prev)
            temp->prev->next = temp->next;

        // if it is the head, then move the head up to the next
        else
            head = temp->next; 

        // if temp is not tail, link next node to previous node (as in said before cut the temp node connections)
        if (temp->next)
            temp->next->prev = temp->prev;
        
        // if it is the tail then move the tail back one
        else
            tail = temp->prev; 

        // free the temp node, removing it from the list now that its connections are cut
        delete temp;
    }

    // delete the node at given poisition
    void delete_pos(int pos) {
        // check if list is empty
        if (!head) {
            cout << "List is empty." << endl; // output the list is empty
            return; // exit the function
        }
    
        // looks like we are treating the 1 as the first position, if position 1 is input then delete the head
        if (pos == 1) {
            pop_front(); // call the pop_front() function in order to remove the head node
            return; // exit the function after popping the head
        }
    
        // start walking from the head
        Node* temp = head;
    
        // starting at 1 walk to the given position node
        for (int i = 1; i < pos; i++){
            // if we no longer have enough nodes for the given  position (so the position was longer than the list length) 
            if (!temp) {  
                cout << "Position doesn't exist." << endl; // output that the position does not exist
                return; // exit without deleting anything
            }
            else 
                temp = temp->next; // if position exists keep walking and go to the next node
        }
        if (!temp) { // once again check if the position exists
            cout << "Position doesn't exist." << endl; // if does not exist output statement
            return; // exit wihtout deleting anything
        }
    
        // check if temp is the tail
        if (!temp->next) {
            pop_back(); // if it is the tail call the pop_back() function to remove the tail
            return; // exit 
        }
    
        // keep pointer previous to temp
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next; // link previous node to temp, to the node after temp
        temp->next->prev = tempPrev; // link the node after temp back to the node prev to temp
        delete temp; // free temp node
    }

    // add value to the end of the list (add a new tail)
    void push_back(int v) {
        // create newNode with given value v
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

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;


const int MIN_NR = 1, MAX_NR = 100, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string name;
        Node* prev;
        Node* next;
        Node(string cn, Node* p = nullptr, Node* n = nullptr) {
            name = cn; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string cn, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(cn);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string cn) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->name != cn)
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
        cout << setw(15) << temp->name << " left the line\n";
        delete temp;
    }

    void push_back(string cn) {
        Node* newNode = new Node(cn);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        cout << setw(15) << newNode->name << " joins the line\n";
    }
    
    void push_front(string cn) {
        Node* newNode = new Node(cn);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        cout << setw(15) << newNode->name << " (VIP) joins the front of the line\n";
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        cout << setw(15) << temp->name << " is served\n";

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

        cout << setw(15) << temp->name << " (at the rear) left the line\n";

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
        cout << setw(15) << "Resulting Line:\n";
        while (current) {
            cout << setw(15) << current->name << " \n";
            current = current->next;
        }
        cout << endl << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->name << " joins the line\n";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    srand(time(0));

    ifstream fin;
    vector <string> names;
    fin.open("names.txt");
    if (fin.good()){
        string name;
        while(getline(fin, name))
            names.push_back(name);
        
        DoublyLinkedList line;

        int lineSize = 0;
        
        cout << "Store opens:\n";
        for (int i = 0; i < 5; i++){
            line.push_back(names[rand()%names.size()]);
            lineSize++;
        }
        cout << endl;
        line.print();
        int timeSteps = 20;        

        for (int i = 1; i < timeSteps; i++){
            cout << setw(10) << "Time Step #" << i + 1 << endl;
            
            int pHelp = rand()%(MAX_NR-MIN_NR+1)+MIN_NR;
            if (pHelp <= 40){
                line.pop_front();
                lineSize--;
            }

            int pJoin = rand()%(MAX_NR-MIN_NR+1)+MIN_NR;
            if (pJoin <= 60){
                line.push_back(names[rand()%names.size()]);
                lineSize++;
            }

            int pEndLeave = rand()%(MAX_NR-MIN_NR+1)+MIN_NR;
            if (pEndLeave <= 20){
                line.pop_back();
                lineSize--;
            }

            int pVIP = rand()%(MAX_NR-MIN_NR+1)+MIN_NR;
            if (pVIP <= 10){
                line.push_front(names[rand()%names.size()]);
                lineSize++;
            }

            int pRandLeave = rand()%(MAX_NR-MIN_NR+1)+MIN_NR;
            if (pRandLeave <= 10){
                line.delete_pos(rand()%lineSize + 1);
                lineSize--;
            }

            line.print();
        }

        fin.close();
    }
    else
        cout << "File not found.\n";
    
    return 0;
}
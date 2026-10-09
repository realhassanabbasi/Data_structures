// tests/test_all.cpp — one assertion-based test driver for every structure in
// this repo. Dependency-free: plain hand-rolled CHECK macros, no frameworks.
//
// Each implementation from the repo root is wrapped in its own namespace below
// (implementations are pasted verbatim, minus their individual main() demos)
// so the driver compiles as a single translation unit.
//
// Build & run:
//   g++ -std=c++11 -Wall -Wextra tests/test_all.cpp -o tests/test_all
//   ./tests/test_all

#include <iostream>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

// ---- tiny test framework -------------------------------------------------
static int g_pass = 0;
static int g_fail = 0;

#define CHECK(cond) do { \
    if (cond) { ++g_pass; } \
    else { ++g_fail; cout << "FAIL [" << __func__ << ":" << __LINE__ << "] " #cond "\n"; } \
} while (0)

// passes only if the statement throws a string literal (the "underflow" style
// used by these implementations)
#define CHECK_THROWS(stmt) do { \
    bool threw = false; \
    try { stmt; } catch (const char*) { threw = true; } \
    CHECK(threw); \
} while (0)

namespace sl {
class Node{
private:
    int element;
    Node *next_node;
public:
    Node(int e=0,Node *n=nullptr):element(e),next_node(n){}
    //Getters
    int retrieve() const{
        return element;
    }
    Node* next() const {
        return next_node;
    }
    //Setters
    void setnext(Node* n){
        next_node=n;
    }
    void setelement(int e){
        element= e;
    }
    friend class SinglyList;
};
class SinglyList{
private:
    Node* list_head;
public:
    SinglyList() {
        list_head = nullptr;
    }
    bool emptyList(){
        return list_head==nullptr;
    }
    int listSize(){
        int size=0;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            size++;
        }
        return size;
    }
    int frontElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        return list_head->retrieve();
    }
    int lastElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        Node *p1=nullptr;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            p1=ptr;
        }
        return p1->retrieve();
    }
    int countElement(int n)const{
        if (list_head==nullptr){
            throw "underflow";
        }
        int countE=0;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            if(ptr->retrieve()==n){
                countE++;
            }
        }
        return countE;
    }
    Node *head(){
        return list_head;
    }
    Node *tail(){
        Node* tail=nullptr;
        for(Node* ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
                tail=ptr;
        }
        return tail;
    }
    void pushAtFront(int e){
        Node*p=new Node(e,list_head);
        list_head=p;
    }
    void pushAtEnd(int e){
        //For an Empty List
        if (list_head == nullptr) {
            list_head = new Node(e, nullptr);
            return;
        }
        Node* last=nullptr;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            last=ptr;
        }
        Node*newnode= new Node(e,nullptr);
        last->setnext(newnode);
    }
    int popAtEnd(){
        int e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        //If the list have only 1 element
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node* last=nullptr;
        Node* secondLast=nullptr;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
                if(ptr->next()!=nullptr){
                    secondLast=ptr;
                }
                last=ptr;
        }
        e=last->retrieve();
        secondLast->setnext(nullptr);
        delete last;
        return e;
    }
    int popAtFront(){
        int e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node* temp= list_head;
        e=list_head->retrieve();
        list_head=list_head->next();
        delete temp;
        return e;
    }
    void display() {
        for (Node* ptr = list_head; ptr != nullptr; ptr = ptr->next()) {
            cout << ptr->retrieve() << " ";
        }
        cout << endl;
    }

    void eraseElement(int e) {
        if (list_head == nullptr) {
            throw "underflow";
        }

        Node* current = list_head;
        Node* previous = nullptr;
        bool found = false;

        while (current != nullptr) {

            if (previous == nullptr && current->retrieve() == e) {
                found = true;
                popAtFront();
                current = list_head;
                continue;
            }

            if (current->retrieve() == e && current->next() == nullptr) {
                found = true;
                popAtEnd();
                break;
            }

            if (current->retrieve() == e) {
                found = true;
                Node* temp = current;
                previous->setnext(current->next());
                current = current->next();
                delete temp;
            }

            else {
                previous=current;
                current=current->next();
            }
        }

        if (!found) {
            cout<<"Element not found"<<endl;
        }
    }


    ~SinglyList() {
        Node* current = list_head;
        while (current != nullptr) {
            Node* next = current->next();
            delete current;
            current = next;
        }
        list_head = nullptr;
    }


};

} // namespace sl

namespace circ {

template<typename N>
class Node {
private:
    N element;
    Node<N>* next_node;
public:
    Node(N e = 0, Node<N>* n = nullptr) : element(e), next_node(n) {}
    N retrieve() const { return element; }
    Node<N>* next() const { return next_node; }
    void setnext(Node<N>* n) { next_node = n; }
    void setelement(N e) { element = e; }
};
template<typename C>
class CircularList {
private:
    Node<C>* tail;  // points to the last node
public:
    CircularList() : tail(nullptr) {}

    bool emptyList() const { return tail == nullptr; }

    int listSize() const {
        if (tail == nullptr) return 0;
        int s = 0;
        Node<C>* ptr = tail->next();
        do {
            s++;
            ptr = ptr->next();
        } while (ptr != tail->next());
        return s;
    }

    C frontElement() const {
        if (tail == nullptr) throw "underflow";
        return tail->next()->retrieve();
    }

    C lastElement() const {
        if (tail == nullptr) throw "underflow";
        return tail->retrieve();
    }

    void pushAtFront(C e) {
        Node<C>* newNode = new Node<C>(e);
        if (tail == nullptr) {
            newNode->setnext(newNode);
            tail = newNode;
        } else {
            newNode->setnext(tail->next());
            tail->setnext(newNode);
        }
    }

    void pushAtEnd(C e) {
        pushAtFront(e);
        tail = tail->next();
    }

    C popAtFront() {
        if (tail == nullptr) throw "underflow";
        Node<C>* head = tail->next();
        C e = head->retrieve();
        if (head == tail) {
            delete head;
            tail = nullptr;
        } else {
            tail->setnext(head->next());
            delete head;
        }
        return e;
    }

    C popAtEnd() {
        if (tail == nullptr) throw "underflow";
        Node<C>* head = tail->next();
        C e;
        if (head == tail) {
            e = tail->retrieve();
            delete tail;
            tail = nullptr;
            return e;
        }
        Node<C>* ptr = head;
        while (ptr->next() != tail) {
            ptr = ptr->next();
        }
        e = tail->retrieve();
        ptr->setnext(head);
        delete tail;
        tail = ptr;
        return e;
    }

    void display() const {
        if (tail==nullptr) {
            cout<<"List is empty\n";
            return;
        }
        Node<C>* ptr = tail->next();
        do {
            cout<<ptr->retrieve()<<" ";
            ptr=ptr->next();
        } while(ptr != tail->next());
        cout << endl;
    }

    void eraseElement(C e) {
        if (tail == nullptr) {
            cout << "List is empty\n";
            return;
        }
        Node<C>* ptr = tail->next();
        Node<C>* previous = tail;
        bool found = false;
        do {
            if (ptr->retrieve() == e) {
                found = true;
                Node<C>* erasePtr = ptr;
                if (erasePtr == tail->next()) {
                    popAtFront();
                    ptr = tail ? tail->next() : nullptr;
                    previous = tail;
                } else if (erasePtr == tail) {
                    popAtEnd();
                    ptr = tail ? tail->next() : nullptr;
                } else {
                    previous->setnext(erasePtr->next());
                    ptr = erasePtr->next();
                    delete erasePtr;
                }
            } else {
                previous = ptr;
                ptr = ptr->next();
            }
        } while (ptr && ptr!=tail->next());

        if (!found) cout << "Element not found\n";
    }
    ~CircularList() {
        while (!emptyList()) {
            popAtFront();
        }
    }

};

} // namespace circ

namespace dl {

template<typename T>
class Node{
private:
    T element;
    Node<T> *next_node,*previous_node;
public:
    Node(T e=T(),Node<T> *n=nullptr,Node<T>*p=nullptr):element(e),next_node(n),previous_node(p){}
    //Getters
    T retrieve() const{
        return element;
    }
    Node<T>* next() const {
        return next_node;
    }
    Node<T>* previous() const{
        return previous_node;
    }
    //Setters
    void setnext(Node<T>* n){
        next_node=n;
    }
    void setprevious(Node<T>* n){
        previous_node=n;
    }
    void setelement(T e){
        element= e;
    }
};

template<typename T>
class DoublyList{
private:
    Node<T> *list_head;
public:
    DoublyList() {
        list_head = nullptr;
    }
    bool emptyList(){
        return list_head==nullptr;
    }
    int listSize(){
        int size=0;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            size++;
        }
        return size;
    }
    T frontElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        return list_head->retrieve();
    }
    T lastElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        Node<T> *p1=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            p1=ptr;
        }
        return p1->retrieve();
    }
    int countElement(T n)const{
        if (list_head==nullptr){
            throw "underflow";
        }
        int countE=0;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            if(ptr->retrieve()==n){
                countE++;
            }
        }
        return countE;
    }
    Node<T> *head(){
        return list_head;
    }
    void pushAtFront(T e){
        Node<T>*p=new Node<T>(e,list_head,nullptr);
        if(list_head!=nullptr){
            list_head->setprevious(p);
        }
        list_head=p;
    }
    void pushAtEnd(T e){
        //For an Empty List
        if (list_head == nullptr) {
            pushAtFront(e);
            return;
        }
        Node<T>* last=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            last=ptr;
        }
        Node<T>*newnode= new Node<T>(e,nullptr,last);
        last->setnext(newnode);
    }
    T popAtEnd(){
        T e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node<T>* last=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            last=ptr;
        }
        e=last->retrieve();
        last->previous()->setnext(nullptr);
        delete last;
        return e;
    }
    T popAtFront(){
        T e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node<T>* temp= list_head;
        e=list_head->retrieve();
        list_head=list_head->next();
        list_head->setprevious(nullptr);
        delete temp;
        return e;
    }
    void eraseElement(T e){
        // empty list
        if (list_head == nullptr) {
            throw "underflow";
        }
        bool found=false;
        for(Node<T> *ptr=list_head;ptr!=nullptr;){
                if(ptr->retrieve()==e){
                    found = true;
                    Node<T>* erasePtr=ptr;
                    ptr=ptr->next();
                    if(erasePtr==list_head){
                        popAtFront();
                    }
                    else if (erasePtr->next()==nullptr){
                        popAtEnd();
                    }
                    else{
                        erasePtr->previous()->setnext(erasePtr->next());
                        erasePtr->next()->setprevious(erasePtr->previous());
                        delete erasePtr;
                        erasePtr = nullptr;
                        }
                }
                else {
                    ptr= ptr->next();
                }
        }
        if(found==false){
            cout<<"Element not found"<<endl;
        }
    }
    void display() {
        for (Node<T>* ptr = list_head; ptr != nullptr; ptr = ptr->next()) {
            cout<<ptr->retrieve()<<" ";
        }
        cout <<endl;
    }
    ~DoublyList() {
        for (Node<T>* current=list_head; current != nullptr; ) {
            Node<T>* nextNode=current->next();
            delete current;
            current=nextNode;
        }
        list_head=nullptr;
    }

};

} // namespace dl

namespace stk {
template<typename T>
class Node{
private:
    T element;
    Node<T> *next_node;
public:
    Node(T e=T(),Node<T> *n=nullptr):element(e),next_node(n){}
    //Getters
    T retrieve() const{
        return element;
    }
    Node<T>* next() const {
        return next_node;
    }
    //Setters
    void setnext(Node<T>* n){
        next_node=n;
    }
    void setelement(T e){
        element= e;
    }
};
template<typename T>
class SinglyList{
private:
    Node<T>* list_head;
public:
    SinglyList() {
        list_head = nullptr;
    }
    bool emptyList(){
        return list_head==nullptr;
    }
    int listSize()const {
        int size=0;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            size++;
        }
        return size;
    }
    T frontElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        return list_head->retrieve();
    }
    T lastElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        Node<T> *p1=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            p1=ptr;
        }
        return p1->retrieve();
    }
    int countElement(T n)const{
        if (list_head==nullptr){
            throw "underflow";
        }
        int countE=0;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            if(ptr->retrieve()==n){
                countE++;
            }
        }
        return countE;
    }
    Node<T> *head() const {
        return list_head;
    }
    Node<T> *tail() const {
        Node<T>* tail=nullptr;
        for(Node<T>* ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
                tail=ptr;
        }
        return tail;
    }
    void pushAtFront(T e){
        Node<T>*p=new Node<T>(e,list_head);
        list_head=p;
    }
    void pushAtEnd(T e){
        //For an Empty List
        if (list_head == nullptr) {
            list_head = new Node<T>(e, nullptr);
            return;
        }
        Node<T>* last=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            last=ptr;
        }
        last->setnext(new Node<T>(e,nullptr));
    }
    T popAtEnd(){
        T e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        //If the list have only 1 element
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node<T>* last=nullptr;
        Node<T>* secondLast=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
                if(ptr->next()!=nullptr){
                    secondLast=ptr;
                }
                last=ptr;
        }
        e=last->retrieve();
        secondLast->setnext(nullptr);
        delete last;
        return e;
    }
    T popAtFront(){
        T e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node<T>* temp= list_head;
        e=list_head->retrieve();
        list_head=list_head->next();
        delete temp;
        return e;
    }
    void display() const {
        for (Node<T>* ptr = list_head; ptr != nullptr; ptr = ptr->next()) {
            cout<<ptr->retrieve()<<" ";
        }
        cout<<endl;
    }

    void eraseElement(T e) {
        if (list_head == nullptr) {
            throw "underflow";
        }

        Node<T>* current = list_head;
        Node<T>* previous = nullptr;
        bool found = false;

        while (current != nullptr) {

            if (previous == nullptr && current->retrieve() == e) {
                found = true;
                popAtFront();
                current = list_head;
                continue;
            }

            if (current->retrieve()==e && current->next()==nullptr) {
                found = true;
                popAtEnd();
                break;
            }

            if (current->retrieve()==e) {
                found=true;
                Node<T>* temp=current;
                previous->setnext(current->next());
                current=current->next();
                delete temp;
            }

            else {
                previous=current;
                current=current->next();
            }
        }

        if (!found) {
            cout<<"Element not found"<<endl;
        }
    }


    ~SinglyList() {
        Node<T>* current = list_head;
        while (current != nullptr) {
            Node<T>* next = current->next();
            delete current;
            current = next;
        }
        list_head = nullptr;
    }


};

template<typename Type>
class StackList{
private:
    SinglyList<Type> l;
public:
    bool emptyStack(){
        return l.emptyList();
    }
    Type top() {
        if (emptyStack()) {
            throw "underflow";
        }
        return l.frontElement();
    }
    Type pop(){
        if (emptyStack()) {
            throw "underflow";
        }
        return l.popAtFront();
    }
    void push(Type e){
        l.pushAtFront(e);
    }
};
template<typename Type>
class StackArray{
private:
    Type *arr;
    int arrCapacity;
    int stackSize;
public:
    StackArray(int n):arrCapacity(n),stackSize(0),arr(new Type[arrCapacity]){}
    ~StackArray(){
        delete [] arr;
    }
    bool emptyStack(){
        return stackSize==0;
    }
    Type top() {
        if(emptyStack()){
            throw "underflow";
        }
        return arr[stackSize-1];
    }

    Type pop(){
        if(emptyStack()){
            throw "underflow";
        }
        --stackSize;
        return arr[stackSize];
    }

    void push(Type n){
        if(stackSize==arrCapacity){
            doubleCapacity();
        }
        arr[stackSize]=n;
        ++stackSize;
    }
    void doubleCapacity(){
        Type *tempArray=new Type[2*arrCapacity];
        for(int i=0;i<arrCapacity;i++){
            tempArray[i]=arr[i];
        }
        delete []arr;
        arr=tempArray;
        arrCapacity*=2;
    }
};

} // namespace stk

namespace que {

template<typename T>
class Node{
private:
    T element;
    Node<T> *next_node;
public:
    Node(T e=T(),Node<T> *n=nullptr):element(e),next_node(n){}
    //Getters
    T retrieve() const{
        return element;
    }
    Node<T>* next() const {
        return next_node;
    }
    //Setters
    void setnext(Node<T>* n){
        next_node=n;
    }
    void setelement(T e){
        element= e;
    }
};
template<typename T>
class SinglyList{
private:
    Node<T>* list_head;
public:
    SinglyList() {
        list_head = nullptr;
    }
    bool emptyList(){
        return list_head==nullptr;
    }
    int listSize()const {
        int size=0;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            size++;
        }
        return size;
    }
    T frontElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        return list_head->retrieve();
    }
    T lastElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        Node<T> *p1=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            p1=ptr;
        }
        return p1->retrieve();
    }
    int countElement(T n)const{
        if (list_head==nullptr){
            throw "underflow";
        }
        int countE=0;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            if(ptr->retrieve()==n){
                countE++;
            }
        }
        return countE;
    }
    Node<T> *head() const {
        return list_head;
    }
    Node<T> *tail() const {
        Node<T>* tail=nullptr;
        for(Node<T>* ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
                tail=ptr;
        }
        return tail;
    }
    void pushAtFront(T e){
        Node<T>*p=new Node<T>(e,list_head);
        list_head=p;
    }
    void pushAtEnd(T e){
        //For an Empty List
        if (list_head == nullptr) {
            list_head = new Node<T>(e, nullptr);
            return;
        }
        Node<T>* last=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            last=ptr;
        }
        last->setnext(new Node<T>(e,nullptr));
    }
    T popAtEnd(){
        T e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        //If the list have only 1 element
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node<T>* last=nullptr;
        Node<T>* secondLast=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
                if(ptr->next()!=nullptr){
                    secondLast=ptr;
                }
                last=ptr;
        }
        e=last->retrieve();
        secondLast->setnext(nullptr);
        delete last;
        return e;
    }
    T popAtFront(){
        T e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node<T>* temp= list_head;
        e=list_head->retrieve();
        list_head=list_head->next();
        delete temp;
        return e;
    }
    void display() const {
        for (Node<T>* ptr = list_head; ptr != nullptr; ptr = ptr->next()) {
            cout<<ptr->retrieve()<<" ";
        }
        cout<<endl;
    }

    void eraseElement(T e) {
        if (list_head == nullptr) {
            throw "underflow";
        }

        Node<T>* current = list_head;
        Node<T>* previous = nullptr;
        bool found = false;

        while (current != nullptr) {

            if (previous == nullptr && current->retrieve() == e) {
                found = true;
                popAtFront();
                current = list_head;
                continue;
            }

            if (current->retrieve() == e && current->next() == nullptr) {
                found = true;
                popAtEnd();
                break;
            }

            if (current->retrieve() == e) {
                found = true;
                Node<T>* temp = current;
                previous->setnext(current->next());
                current = current->next();
                delete temp;
            }

            else {
                previous=current;
                current=current->next();
            }
        }

        if (!found) {
            cout<<"Element not found"<<endl;
        }
    }


    ~SinglyList() {
        Node<T>* current = list_head;
        while (current != nullptr) {
            Node<T>* next = current->next();
            delete current;
            current = next;
        }
        list_head = nullptr;
    }


};

template<typename Type>
class Queue{
private:
    SinglyList<Type> l;
public:
    bool emptyQueue(){
        return l.emptyList();
    }
    Type top() const {
        return l.frontElement();
    }
    Type pop(){
        return l.popAtFront();
    }
    void push (Type n){
        l.pushAtEnd(n);
    }
};

template<typename Q>
class QueueArray{
private:
    int queueSize;
    int ifront;
    int iback;
    int arrayCapacity;
    Q *array1;
public:
    QueueArray(int n):queueSize(0),
    ifront(0),
    iback(-1),
    arrayCapacity(n),
    array1(new Q[arrayCapacity]){}
    ~QueueArray(){
        delete []array1;
    }
    bool emptyQueue(){
        return queueSize==0;
    }
    Q frontE() const {
        if(emptyQueue()){
            throw "overflow";
        }
        return array1[ifront];
    }

    void push(Q e){
        if(queueSize==arrayCapacity){
            throw "underflow";
        }
        iback=(iback+1)%arrayCapacity;
        array1[iback] = e;
        queueSize++;
    }
    Q pop(){
        if(emptyQueue()){
            throw "underflow";
        }
        Q value=array1[ifront];
        ifront=(ifront+1)%arrayCapacity;
        queueSize--;
        return value;
    }
    void traverse() {
        if (queueSize == 0) {
            cout<<"Queue is empty\n";
            return;
        }

        int i=ifront;
        for (int c=0;c<queueSize;c++) {
            cout<<array1[i]<<" ";
            i=(i+1)%arrayCapacity;
        }
        cout<<endl;
    }



};

} // namespace que

namespace tree {

template<typename T>
class Node{
private:
    T element;
    Node<T> *next_node;
public:
    Node(T e=T(),Node<T> *n=nullptr):element(e),next_node(n){}
    //Getters
    T retrieve() const{
        return element;
    }
    Node<T>* next() const {
        return next_node;
    }
    //Setters
    void setnext(Node<T>* n){
        next_node=n;
    }
    void setelement(T e){
        element= e;
    }
};
template<typename T>
class SinglyList{
private:
    Node<T>* list_head;
public:
    SinglyList() {
        list_head = nullptr;
    }
    bool emptyList(){
        return list_head==nullptr;
    }
    int listSize()const {
        int size=0;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            size++;
        }
        return size;
    }
    T frontElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        return list_head->retrieve();
    }
    T lastElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        Node<T> *p1=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            p1=ptr;
        }
        return p1->retrieve();
    }
    int countElement(T n)const{
        if (list_head==nullptr){
            throw "underflow";
        }
        int countE=0;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            if(ptr->retrieve()==n){
                countE++;
            }
        }
        return countE;
    }
    Node<T> *head() const {
        return list_head;
    }
    Node<T> *tail() const {
        Node<T>* tail=nullptr;
        for(Node<T>* ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
                tail=ptr;
        }
        return tail;
    }
    void pushAtFront(T e){
        Node<T>*p=new Node<T>(e,list_head);
        list_head=p;
    }
    void pushAtEnd(T e){
        //For an Empty List
        if (list_head == nullptr) {
            list_head = new Node<T>(e, nullptr);
            return;
        }
        Node<T>* last=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            last=ptr;
        }
        last->setnext(new Node<T>(e,nullptr));
    }
    T popAtEnd(){
        T e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        //If the list have only 1 element
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node<T>* last=nullptr;
        Node<T>* secondLast=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
                if(ptr->next()!=nullptr){
                    secondLast=ptr;
                }
                last=ptr;
        }
        e=last->retrieve();
        secondLast->setnext(nullptr);
        delete last;
        return e;
    }
    T popAtFront(){
        T e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node<T>* temp= list_head;
        e=list_head->retrieve();
        list_head=list_head->next();
        delete temp;
        return e;
    }
    void display() const {
        for (Node<T>* ptr = list_head; ptr != nullptr; ptr = ptr->next()) {
            cout<<ptr->retrieve()<<" ";
        }
        cout<<endl;
    }

    void eraseElement(T e) {
        if (list_head == nullptr) {
            throw "underflow";
        }

        Node<T>* current = list_head;
        Node<T>* previous = nullptr;
        bool found = false;

        while (current != nullptr) {

            if (previous == nullptr && current->retrieve() == e) {
                found = true;
                popAtFront();
                current = list_head;
                continue;
            }

            if (current->retrieve() == e && current->next() == nullptr) {
                found = true;
                popAtEnd();
                break;
            }

            if (current->retrieve() == e) {
                found = true;
                Node<T>* temp = current;
                previous->setnext(current->next());
                current = current->next();
                delete temp;
            }

            else {
                previous=current;
                current=current->next();
            }
        }

        if (!found) {
            cout<<"Element not found"<<endl;
        }
    }


    ~SinglyList() {
        Node<T>* current = list_head;
        while (current != nullptr) {
            Node<T>* next = current->next();
            delete current;
            current = next;
        }
        list_head = nullptr;
    }


};
template<typename Type>
class SimpleTree{
private:
    Type node_value;
    SimpleTree<Type> *parent_node;
    SinglyList<SimpleTree*> children;
public:
    SimpleTree(Type const& obj,SimpleTree *p){
        node_value=obj;
        parent_node=p;
    }
    Type retrieve(){
        return node_value;
    }
    SimpleTree<Type>* parent() const {
        return parent_node;
    }
    bool isRoot() const {
        return parent()==nullptr;
    }
    int degree() const {
        return children.listSize();
    }
    bool isLeaf() const {
        return degree()==0;
    }
    SimpleTree<Type>* child(int n) const {
        if (n < 0 || n >= degree()) return nullptr;
        Node<SimpleTree<Type>*>* node = children.head();
        for (int i = 0; i < n; ++i) {
            node = node->next();
        }

        return node->retrieve();
    }



    void insertNode(Type const &obj){
        children.pushAtEnd(new SimpleTree<Type>(obj,this));
    }
    void detach(){
        if(isRoot()){
            return;
        }
        parent()->children.eraseElement(this);
        parent_node=nullptr;
    }
    void attach(SimpleTree<Type>* tree){
        if(!tree->isRoot()){
            tree->detach();
        }
        tree->parent_node=this;
        children.pushAtEnd(tree);
    }
    int sizee() const {
        int treeSize = 1;
        for(Node<SimpleTree<Type>*>* node = children.head(); node != nullptr; node = node->next()){
            treeSize += node->retrieve()->sizee();
        }
        return treeSize;
    }
    int height() const {
        int treeHeight = 0;
        for(Node<SimpleTree<Type>*>* node = children.head(); node != nullptr; node = node->next()){
            treeHeight = std::max(treeHeight, 1 + node->retrieve()->height());
        }
        return treeHeight;
    }
    void depth_first_traversal() const {
        cout<<retrieve()<<"\t";
        for(Node<SimpleTree*>* ptr=children.head();ptr!=nullptr;ptr=ptr->next()){
            ptr->retrieve()->depth_first_traversal();
        }
    }


};

} // namespace tree

namespace hm {
// HashMap.cpp — a hash table with separate chaining and automatic rehashing.
//
// Why this file exists: hashing is the missing classic in this collection.
// Two strings can land in the same bucket (a collision) and the table stays
// fast by relinking lists, not by moving everything around.


template <typename K, typename V>
class HashMap {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(const K& k, const V& v) : key(k), value(v), next(NULL) {}
    };

    Node** buckets;          // raw array of bucket heads, no STL containers
    size_t bucketCount;
    size_t itemCount;

    // index inside the bucket array for a key
    size_t indexFor(const K& key, size_t tableSize) const {
        return std::hash<K>()(key) % tableSize;
    }

    // double the table and move every node — called when load gets too high
    void rehash() {
        size_t oldCount = bucketCount;
        Node** oldBuckets = buckets;

        bucketCount = oldCount * 2;
        buckets = new Node*[bucketCount]();
        itemCount = 0;                     // insert() counts them again

        for (size_t i = 0; i < oldCount; i++) {
            Node* cur = oldBuckets[i];
            while (cur != NULL) {
                insert(cur->key, cur->value);
                Node* dead = cur;
                cur = cur->next;
                delete dead;
            }
        }
        delete[] oldBuckets;
        std::cout << "[rehash] table grew to " << bucketCount << " buckets\n";
    }

public:
    HashMap(size_t startSize = 8) : bucketCount(startSize), itemCount(0) {
        buckets = new Node*[bucketCount]();   // () zeroes the pointers
    }

    ~HashMap() {
        for (size_t i = 0; i < bucketCount; i++) {
            Node* cur = buckets[i];
            while (cur != NULL) {
                Node* dead = cur;
                cur = cur->next;
                delete dead;
            }
        }
        delete[] buckets;
    }

    // insert or update — same key twice keeps only the newest value
    void insert(const K& key, const V& value) {
        if (itemCount + 1 > bucketCount * 3 / 4)   // load factor 0.75
            rehash();

        size_t i = indexFor(key, bucketCount);
        Node* cur = buckets[i];
        while (cur != NULL) {
            if (cur->key == key) {                 // key exists: update
                cur->value = value;
                return;
            }
            cur = cur->next;
        }
        Node* n = new Node(key, value);            // new key: push to front
        n->next = buckets[i];
        buckets[i] = n;
        itemCount++;
    }

    // get into `out`; returns false if the key is missing
    bool get(const K& key, V& out) const {
        Node* cur = buckets[indexFor(key, bucketCount)];
        while (cur != NULL) {
            if (cur->key == key) {
                out = cur->value;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    bool contains(const K& key) const {
        V tmp;
        return get(key, tmp);
    }

    // true if something was actually removed
    bool remove(const K& key) {
        size_t i = indexFor(key, bucketCount);
        Node* cur = buckets[i];
        Node* prev = NULL;
        while (cur != NULL) {
            if (cur->key == key) {
                if (prev == NULL)
                    buckets[i] = cur->next;
                else
                    prev->next = cur->next;
                delete cur;
                itemCount--;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    size_t size() const { return itemCount; }

    // print each bucket so collisions are visible
    void display() const {
        for (size_t i = 0; i < bucketCount; i++) {
            std::cout << "bucket " << i << ":";
            Node* cur = buckets[i];
            if (cur == NULL) { std::cout << " (empty)\n"; continue; }
            while (cur != NULL) {
                std::cout << " [" << cur->key << " -> " << cur->value << "]";
                cur = cur->next;
            }
            std::cout << "\n";
        }
    }
};

} // namespace hm

// ---- tests ---------------------------------------------------------------

void test_singly() {
    sl::SinglyList l;
    CHECK(l.emptyList());
    CHECK(l.listSize() == 0);
    CHECK_THROWS(l.popAtFront());    // empty pop throws
    CHECK_THROWS(l.popAtEnd());
    CHECK_THROWS(l.frontElement());
    CHECK_THROWS(l.eraseElement(1)); // empty erase throws

    l.pushAtFront(10); l.pushAtEnd(20); l.pushAtEnd(30); l.pushAtFront(5);
    CHECK(l.listSize() == 4);
    CHECK(l.frontElement() == 5);
    CHECK(l.lastElement() == 30);
    CHECK(l.countElement(10) == 1);

    CHECK(l.popAtFront() == 5);
    CHECK(l.popAtEnd() == 30);
    CHECK(l.listSize() == 2);

    l.pushAtFront(50);              // 50 10 20
    l.eraseElement(50);             // erase head -> 10 20
    CHECK(l.frontElement() == 10 && l.listSize() == 2);
    l.eraseElement(20);             // erase tail -> 10
    CHECK(l.lastElement() == 10 && l.listSize() == 1);

    l.pushAtEnd(40); l.pushAtEnd(50); l.pushAtEnd(60);  // 10 40 50 60
    l.eraseElement(50);             // erase middle -> 10 40 60
    CHECK(l.listSize() == 3);
    l.eraseElement(999);            // missing: prints, list untouched
    CHECK(l.listSize() == 3);

    l.pushAtFront(40); l.pushAtFront(40);  // 40 40 10 40 60
    l.eraseElement(40);                    // removes ALL 40s -> 10 60
    CHECK(l.listSize() == 2 && l.frontElement() == 10 && l.lastElement() == 60);

    while (!l.emptyList()) l.popAtFront();
    CHECK(l.emptyList());

    sl::SinglyList s;               // single-element pops
    s.pushAtFront(7);
    CHECK(s.popAtEnd() == 7 && s.emptyList());
    s.pushAtFront(8);
    CHECK(s.popAtFront() == 8 && s.emptyList());
}

void test_circular() {
    circ::CircularList<int> c;
    CHECK(c.emptyList());
    CHECK(c.listSize() == 0);
    CHECK_THROWS(c.popAtFront());
    CHECK_THROWS(c.popAtEnd());
    CHECK_THROWS(c.frontElement());

    c.pushAtEnd(1); c.pushAtEnd(2); c.pushAtEnd(3);
    CHECK(c.listSize() == 3);
    CHECK(c.frontElement() == 1);
    CHECK(c.lastElement() == 3);
    c.pushAtFront(0);               // 0 1 2 3
    CHECK(c.frontElement() == 0 && c.lastElement() == 3);

    CHECK(c.popAtFront() == 0);
    CHECK(c.popAtEnd() == 3);
    CHECK(c.listSize() == 2);

    c.pushAtEnd(4); c.pushAtEnd(5); // 1 2 4 5 — drain in ring order
    CHECK(c.popAtFront() == 1);
    CHECK(c.popAtFront() == 2);
    CHECK(c.popAtFront() == 4);
    CHECK(c.popAtFront() == 5);
    CHECK(c.emptyList());

    c.pushAtEnd(10); c.pushAtEnd(20); c.pushAtEnd(30); c.pushAtEnd(40);
    c.eraseElement(10);             // erase head
    CHECK(c.frontElement() == 20 && c.listSize() == 3);
    c.eraseElement(40);             // erase tail
    CHECK(c.lastElement() == 30 && c.listSize() == 2);
    c.pushAtEnd(50); c.pushAtEnd(60);  // 20 30 50 60
    c.eraseElement(50);             // erase middle
    CHECK(c.listSize() == 3 && c.lastElement() == 60);
    c.eraseElement(999);            // missing: prints, list untouched
    CHECK(c.listSize() == 3);

    circ::CircularList<int> one;    // single-element erase
    one.pushAtEnd(7);
    one.eraseElement(7);
    CHECK(one.emptyList());

    circ::CircularList<int> e;      // erase on empty: prints, no crash
    e.eraseElement(1);
    CHECK(e.emptyList());
}

void test_doubly() {
    dl::DoublyList<int> d;
    CHECK(d.emptyList());
    CHECK_THROWS(d.popAtFront());
    CHECK_THROWS(d.popAtEnd());
    CHECK_THROWS(d.eraseElement(1)); // empty erase throws

    d.pushAtFront(2); d.pushAtFront(1); d.pushAtEnd(3); d.pushAtEnd(4);
    CHECK(d.listSize() == 4);
    CHECK(d.frontElement() == 1);
    CHECK(d.lastElement() == 4);
    CHECK(d.countElement(2) == 1);

    {   // backward links intact across the whole list
        dl::Node<int>* t = d.head();
        while (t->next()) t = t->next();
        int back = 0;
        for (; t; t = t->previous()) ++back;
        CHECK(back == 4);
    }

    CHECK(d.popAtFront() == 1);
    CHECK(d.popAtEnd() == 4);
    CHECK(d.listSize() == 2);
    {   // backward links still consistent after pops
        dl::Node<int>* t = d.head();
        while (t->next()) t = t->next();
        CHECK(t->retrieve() == 3);
        CHECK(t->previous()->retrieve() == 2);
        CHECK(t->previous()->previous() == nullptr);
    }

    d.eraseElement(2);              // erase head -> 3
    CHECK(d.frontElement() == 3 && d.listSize() == 1);
    d.pushAtEnd(5); d.pushAtFront(0);  // 0 3 5
    d.eraseElement(5);              // erase tail -> 0 3
    CHECK(d.lastElement() == 3);
    d.pushAtEnd(9);                 // 0 3 9
    d.eraseElement(3);              // erase middle -> 0 9
    CHECK(d.listSize() == 2 && d.frontElement() == 0 && d.lastElement() == 9);
    d.eraseElement(999);            // missing: prints, list untouched
    CHECK(d.listSize() == 2);
}

void test_stack() {
    stk::StackList<int> s;          // linked-list stack
    CHECK(s.emptyStack());
    CHECK_THROWS(s.pop());
    CHECK_THROWS(s.top());
    s.push(1); s.push(2); s.push(3);
    CHECK(s.top() == 3);
    CHECK(s.pop() == 3);
    CHECK(s.pop() == 2);
    CHECK(s.pop() == 1);
    CHECK(s.emptyStack());

    stk::StackArray<int> a(2);      // array stack, starts with capacity 2
    CHECK(a.emptyStack());
    CHECK_THROWS(a.pop());
    CHECK_THROWS(a.top());
    a.push(10); a.push(20);
    a.push(30);                     // forces doubleCapacity()
    a.push(40); a.push(50);         // and again
    CHECK(a.top() == 50);
    CHECK(a.pop() == 50);
    CHECK(a.pop() == 40);
    CHECK(a.pop() == 30);
    CHECK(a.pop() == 20);
    CHECK(a.pop() == 10);
    CHECK(a.emptyStack());

    stk::StackList<string> ss;      // templates work for other types
    ss.push("hello");
    CHECK(ss.top() == "hello");
    CHECK(ss.pop() == "hello");
}

void test_queue() {
    que::Queue<int> q;              // linked-list queue (FIFO)
    CHECK(q.emptyQueue());
    CHECK_THROWS(q.pop());
    q.push(1); q.push(2); q.push(3);
    CHECK(q.top() == 1);
    CHECK(q.pop() == 1);
    CHECK(q.pop() == 2);
    q.push(4);
    CHECK(q.pop() == 3);
    CHECK(q.pop() == 4);
    CHECK(q.emptyQueue());

    que::QueueArray<int> qa(3);     // circular-buffer queue
    CHECK(qa.emptyQueue());
    CHECK_THROWS(qa.pop());
    qa.push(1); qa.push(2); qa.push(3);
    CHECK_THROWS(qa.push(4));        // full queue throws
    CHECK(qa.pop() == 1);
    qa.push(4);                     // wraps around the buffer
    CHECK(qa.pop() == 2);
    CHECK(qa.pop() == 3);
    CHECK(qa.pop() == 4);
    CHECK(qa.emptyQueue());
}

void test_tree() {
    tree::SimpleTree<string>* root = new tree::SimpleTree<string>("root", nullptr);
    CHECK(root->isRoot());
    CHECK(root->isLeaf());
    CHECK(root->sizee() == 1);
    CHECK(root->height() == 0);

    tree::SimpleTree<string>* c1 = new tree::SimpleTree<string>("c1", nullptr);
    tree::SimpleTree<string>* c2 = new tree::SimpleTree<string>("c2", nullptr);
    root->attach(c1);
    root->attach(c2);
    CHECK(root->degree() == 2);
    CHECK(!root->isLeaf());
    CHECK(!c1->isRoot());
    CHECK(c1->parent() == root);
    CHECK(c1->isLeaf());
    CHECK(root->child(0) == c1);
    CHECK(root->child(1) == c2);
    CHECK(root->child(5) == nullptr); // out-of-range child -> nullptr

    tree::SimpleTree<string>* g1 = new tree::SimpleTree<string>("g1", nullptr);
    c1->attach(g1);
    CHECK(root->sizee() == 4);
    CHECK(root->height() == 2);
    CHECK(c1->height() == 1);

    g1->detach();                   // detach removes it from its parent
    CHECK(root->sizee() == 3);
    CHECK(g1->isRoot());
    CHECK(g1->parent() == nullptr);
    CHECK(c1->isLeaf());

    c2->attach(g1);                 // reattach under another parent
    CHECK(c2->degree() == 1);
    CHECK(root->sizee() == 4);
    CHECK(root->height() == 2);

    delete g1; delete c1; delete c2; delete root;
}

void test_hashmap() {
    hm::HashMap<string,int> m;
    CHECK(m.size() == 0);
    int v = -1;
    CHECK(!m.get("nope", v));       // missing key -> false
    CHECK(!m.contains("nope"));
    CHECK(!m.remove("nope"));       // remove missing -> false

    m.insert("a", 1); m.insert("b", 2); m.insert("c", 3);
    CHECK(m.size() == 3);
    CHECK(m.get("b", v) && v == 2);
    m.insert("b", 20);              // same key: updates, does not grow
    CHECK(m.get("b", v) && v == 20);
    CHECK(m.size() == 3);
    CHECK(m.contains("a"));
    CHECK(m.remove("b"));
    CHECK(!m.contains("b"));
    CHECK(m.size() == 2);
    CHECK(!m.remove("b"));          // removing twice reports false

    hm::HashMap<string,int> tiny(4); // rehash boundary: force growth,
    for (int i = 0; i < 50; i++)      // every key must survive it
        tiny.insert("k" + to_string(i), i);
    CHECK(tiny.size() == 50);
    bool allok = true;
    for (int i = 0; i < 50; i++) {
        int x = -1;
        if (!tiny.get("k" + to_string(i), x) || x != i) { allok = false; break; }
    }
    CHECK(allok);

    hm::HashMap<int,string> im;     // templates work for other key types
    im.insert(1, "one");
    string s;
    CHECK(im.get(1, s) && s == "one");
}

int main() {
    test_singly();
    test_circular();
    test_doubly();
    test_stack();
    test_queue();
    test_tree();
    test_hashmap();

    cout << "\n==== RESULT: " << g_pass << " passed, " << g_fail << " failed ====\n";
    return g_fail == 0 ? 0 : 1;
}

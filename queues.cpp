#include<iostream>
#include <stdexcept>
using namespace std;

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
    bool emptyQueue() const{
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
int main(){

}

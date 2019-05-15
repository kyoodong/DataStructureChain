#include <iostream>

template <class T> class Chain; // forward declaration

class Number {
private:
    int num;

public:
    Number(int n = 0) : num(n) {}

    Number& operator=(const Number& ref) {
        num = ref.num;
        return *this;
    }

    operator int () {
        return num;
    }

    void ShowNumber() {
        std::cout << num << std::endl;
    }
};

template <class T>
class ChainNode {
    friend class Chain<T>;
public:
    ChainNode() : link(NULL){}
    ChainNode(T data) : data(data), link(NULL){}
    ~ChainNode();

private:
    T data;
    ChainNode<T> *link;
};

template <class T>
class Chain {
public:
    class Iterator {
    public:
        Iterator(ChainNode<T>* n){
            node = n;
        }
        Iterator(const Iterator& it) {
            this->node = it.node;
        }

        Iterator operator++();
        Iterator operator++(int mark);
        bool operator==(const Iterator&);
        bool operator!=(const Iterator&);
        T operator*();
        void operator=(const Iterator&);

    private:
        ChainNode<T>* node;
    };

    Chain(): size(0), first(NULL){}
    ~Chain();
    void InsertFront(const T& element);
    void InsertBack(const T& element);
    void Insert(const T& element, const unsigned at);
    T Front() const;
    T Back() const;
    T Get(const unsigned at) const;
    void EraseFront();
    void EraseBack();
    void Erase(const unsigned at);

    Iterator begin() const;
    Iterator end() const;

private:
    ChainNode<T> *first;
    unsigned size;

    ChainNode<T>* GetNode(const unsigned at) const;
};

template <typename T>
ChainNode<T>::~ChainNode() {
    link = NULL;
}

template <typename T>
Chain<T>::~Chain() {
    if (first != NULL) {
        ChainNode<T>* next;
        for (ChainNode<T>* node = first; node != NULL; node = next) {
            next = node->link;
            delete node;
        }
    }

    first = NULL;
}

template <typename T>
void Chain<T>::InsertFront(const T& element) {
    ChainNode<T>* node = new ChainNode<T>(element);
    if (first != NULL)
        node->link = first;

    first = node;
    size++;
}

template <typename T>
void Chain<T>::InsertBack(const T& element) {
    if (size == 0)
        InsertFront(element);

    else
        Insert(element, size - 1);
}

template <typename T>
void Chain<T>::Insert(const T& element, const unsigned at) {
    ChainNode<T>* node = GetNode(at);
    ChainNode<T>* newNode = new ChainNode<T>(element);
    newNode->link = node->link;
    node->link = newNode;
    size++;
}

template <typename T>
T Chain<T>::Front() const {
    return Get(0);
}

template <typename T>
T Chain<T>::Back() const {
    return Get(size - 1);
}

template <typename T>
T Chain<T>::Get(unsigned at) const {
    return GetNode(at)->data;
}

template <typename T>
void Chain<T>::EraseFront() {
    ChainNode<T>* node = GetNode(0);
    ChainNode<T>* next = node->link;

    first = next;
    delete node;
    size--;
}

template <typename T>
void Chain<T>::EraseBack() {
    Erase(size - 1);
}

template <typename T>
void Chain<T>::Erase(unsigned at) {
    ChainNode<T>* prev = GetNode(at - 1);
    ChainNode<T>* node = prev->link;

    if (node == NULL)
        throw NULL;

    prev->link = node->link;
    delete node;
    size--;
}

template <typename T>
ChainNode<T>* Chain<T>::GetNode(const unsigned at) const {
    if (at >= size)
        throw size;

    ChainNode<T>* node = first;
    for (int i = 0; i < at; i++) {
        node = node->link;
    }
    return node;
}

template <typename T>
typename Chain<T>::Iterator Chain<T>::begin() const {
    Iterator iterator(first);
    return iterator;
}

template <typename T>
typename Chain<T>::Iterator Chain<T>::end() const {
    Iterator iterator(first);
    for (int i = 0; i < size; i++) {
        iterator++;
    }
    return iterator;
}

template <typename T>
typename Chain<T>::Iterator Chain<T>::Iterator::operator++() {
    Iterator it = *this;
//    *this = *node->link;
    this = node->link;
    return it;
}

template <typename T>
typename Chain<T>::Iterator Chain<T>::Iterator::operator++(int mark) {
    node = node->link;
    return *this;
}

template <typename T>
bool Chain<T>::Iterator::operator==(const Iterator& iterator) {
    return this->node == iterator.node;
}

template <typename T>
bool Chain<T>::Iterator::operator!=(const Iterator& iterator) {
    return this->node != iterator.node;
}

template <typename T>
T Chain<T>::Iterator::operator*() {
    return node->data;
}

template <typename T>
void Chain<T>::Iterator::operator=(const Iterator& it) {
    this->node = it.node;
}

int main() {
    Chain<Number> chain;
    for (int i = 1; i <= 9; i++) {
        chain.InsertBack(i);
    }

    std::cout << "1 ~ 9까지 수 입력" << std::endl;
    for (Chain<Number>::Iterator iterator = chain.begin(); iterator != chain.end(); iterator++) {
        std::cout << *iterator << " ";
    }
    std::cout << std::endl;

    chain.InsertFront(0);

    std::cout << "0을 맨 앞에 삽입" << std::endl;
    int sum = 0;
    for (Chain<Number>::Iterator iterator = chain.begin(); iterator != chain.end(); iterator++) {
        sum += *iterator;
        std::cout << *iterator << " ";
    }
    std::cout << std::endl << "sum = " << sum << std::endl;

    chain.InsertBack(10);

    std::cout << "10을 맨 뒤에 삽입" << std::endl;
    sum = 0;
    for (Chain<Number>::Iterator iterator = chain.begin(); iterator != chain.end(); iterator++) {
        sum += *iterator;
        std::cout << *iterator << " ";
    }
    std::cout << std::endl << "sum = " << sum << std::endl;

    std::cout << "Front 출력 : " << chain.Front() << std::endl;
    std::cout << "Back 출력 : " << chain.Back() << std::endl;
    std::cout << "Get(2) 출력 : " << chain.Get(2) << std::endl;

    chain.EraseFront();

    std::cout << "맨 앞에 있는 0 삭제" << std::endl;
    sum = 0;
    for (Chain<Number>::Iterator iterator = chain.begin(); iterator != chain.end(); iterator++) {
        sum += *iterator;
        std::cout << *iterator << " ";
    }
    std::cout << std::endl << "sum = " << sum << std::endl;

    chain.EraseBack();

    std::cout << "맨 뒤에 있는 10 삭제" << std::endl;
    sum = 0;
    for (Chain<Number>::Iterator iterator = chain.begin(); iterator != chain.end(); iterator++) {
        sum += *iterator;
        std::cout << *iterator << " ";
    }
    std::cout << std::endl << "sum = " << sum << std::endl;

    chain.Insert(100, 2);

    std::cout << "2번째 원소 뒤에 100 삽입" << std::endl;
    sum = 0;
    for (Chain<Number>::Iterator iterator = chain.begin(); iterator != chain.end(); iterator++) {
        sum += *iterator;
        std::cout << *iterator << " ";
    }
    std::cout << std::endl << "sum = " << sum << std::endl;

    chain.Erase(6);

    std::cout << "6번째 원소 삭제" << std::endl;
    sum = 0;
    for (Chain<Number>::Iterator iterator = chain.begin(); iterator != chain.end(); iterator++) {
        sum += *iterator;
        std::cout << *iterator << " ";
    }
    std::cout << std::endl << "sum = " << sum << std::endl;
    return 0;
}
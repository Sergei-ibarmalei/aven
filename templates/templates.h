#pragma once


template<class N>
struct Node
{
    N* object{ nullptr };
    struct Node* next{ nullptr };
};

template<class T>
class StoreBase
{
protected:
    Node<T>* first{ nullptr };
    Node<T>* tmp{ nullptr };
    StoreBase() {}
    StoreBase(const StoreBase&) = delete;
    StoreBase& operator=(const StoreBase&) = delete;

public:
    ~StoreBase();
    void Push(T* object);
    void CheckStoreForGone();
    bool StoreIsEmpty() const { return first == nullptr; }
    Node<T>* First() { return this->first; }
    Node<T>* FirstConst() const { return this->first; }

};

template<class T>
StoreBase<T>::~StoreBase()
{
    while (this->first)
    {
        Node<T>* tmp = this->first;
        this->first = this->first->next;
        delete tmp;
        tmp = nullptr;

    }
}

template<class T>
void StoreBase<T>::Push(T* object)
{
    this->tmp = new Node<T>;
    this->tmp->object = object;
    this->tmp->next = this->first;
    this->first = this->tmp;
}

template<class T>
void StoreBase<T>::CheckStoreForGone()
{
    Node<T>** currentNode = &this->first;
    while (*currentNode)
    {
        if ((*currentNode)->object->ObjectStatus() !=
            enumObjectStatus::isOnScreen)
        {
            this->tmp = *currentNode;
            *currentNode = (*currentNode)->next;
            delete this->tmp;
            this->tmp = nullptr;
        }
        else
        {
            currentNode = &(*currentNode)->next;
        }
    }
}


template<class T>
class StoreLaser : public StoreBase<T>
{
private:
    void moving(Node<T>* n);

public:
    void Move();
};

template<class T>
void StoreLaser<T>::moving(Node<T>* n)
{
    if (!n) return;
    n->object->Move();
    moving(n->next);
}

template<class T>
void StoreLaser<T>::Move()
{
    if (!this->first) return;
    moving(this->first);
}



template<class T>
class StoreCartoon : public StoreBase<T>
{
private:
    void ticking(Node<T>* n);
public:
    void Tick();
};

template<class T>
void StoreCartoon<T>::ticking(Node<T>* n)
{
    if (!n) return;
    n->object->Tick();
    ticking(n->next);
}

template<class T>
void StoreCartoon<T>::Tick()
{
    if (!this->first) return;
    ticking(this->first);
}





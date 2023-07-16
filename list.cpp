#include "list.h"

#include <utility>

node* list::GetNode(int index) {
    node* cursor = this->head;
    for (int i = 0; i < index; ++i, cursor = cursor->next) {
        if (!cursor->next) {
            return nullptr;
        }
    }
    return cursor;
}
int list::Insert(int index, string label, string content, int len) {
    node* in_place_of = this->GetNode(index);
    if (!in_place_of) {
        return 1;
    }
    node* prev = in_place_of->prev;
    node* nnode = new node(std::move(label), std::move(content), len);
    nnode->prev = prev;
    nnode->next = in_place_of;
    in_place_of->prev = nnode;
    if (prev) {prev->next = nnode;}
    if (index == 0) {
        this->head = nnode;
    }
    if (in_place_of == this->tail) {
        this->tail = nnode;
    }
    return 0;
}

int list::push_back( string label, string content, int len) {
    node* n = new node(std::move(label), std::move(content), len);
    if (!this->head) {
        this->head = n;
    }
    if (this->tail) {
        node* tail = this->tail;
        tail->next = n;
    }
    n->prev = this->tail;
    this->tail = n;
    return 0;
}
int list::push_front( string label, string content, int len) {
    node* n = new node(std::move(label), std::move(content), len);
    if (!this->tail) {
        this->tail = n;
    }
    if (this->head) {
        node* head = this->head;
        head->prev = n;
    }
    n->next = this->head;
    this->head = n;
    return 0;
}
node* list::pop_back() {
    node* retv = this->tail;
    if (!retv) {
        return nullptr;
    }
    this->tail = retv->prev;
    retv->next = nullptr;
    retv->prev = nullptr;
    if (this->tail) {
        this->tail->next = nullptr;
    }
    if (this->head == retv) {
        this->head = nullptr;
    }
    return retv;
}
node* list::pop_front() {
    node* retv = this->head;
    if (!retv) {
        return nullptr;
    }
    this->head = retv->next;
    retv->next = nullptr;
    retv->prev = nullptr;
    if (this->head) {
        this->head->prev = nullptr;
    }
    if (this->tail == retv) {
        this->tail = nullptr;
    }
    return retv;
}

void list::encrypt() {
    node* cursor = this->head;
    while (cursor) {
        cursor->Encrypt(this->password, this->seed);
        cursor = cursor->next;
    }
}
void list::decrypt() {
    node* cursor = this->head;
    while (cursor) {
        cursor->Decrypt(this->password, this->seed);
        cursor = cursor->next;
    }
}
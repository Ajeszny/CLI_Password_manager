#include "list.h"

#include <utility>

node* list::get_node(int index){
    node* cursor = this->head;
    for (int i = 0; i < index; ++i, cursor = cursor->next) {
        if (!cursor->next) {
            return nullptr;
        }
    }
    return cursor;
}

string list::get_password(int index) {
    return this->get_node(index)->GetDecrString(this->password, this->seed);
}

int list::insert(int index, string label, string content, int len) {
    node* in_place_of = this->get_node(index);
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

int list::get_length() {
    node* cursor = this->head;
    int len = 0;
    while (cursor) {
        len++;
        cursor = cursor->next;
    }
    return len;
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

void list::save_to_file(string filename) {
    FILE* fp = fopen(filename.c_str(), "w");
    node* cursor = this->head;
    fprintf(fp, "%i\n", this->get_length());
    while (cursor) {
        fprintf(fp, "%i%s\n%s\n", cursor->GetLen(), cursor->GetLabel().c_str(), cursor->GetContent().c_str());
        cursor = cursor->next;
    }
    fclose(fp);
}

int list::load_from_file(std::string filename) {
    FILE* fp = fopen(filename.c_str(), "r");
    if (!fp){
        return 1;
    }
    int len;
    int err = fscanf(fp, "%i", &len);
    if (err != 1) {
        return 2;
    }
    for (int i = 0; i < len; ++i) {
        int entry_len;
        char label[1024];
        char content[256];
        err = fscanf(fp, "%i%[^\n]\n%s", &entry_len, label, content);
        if (err != 3) {
            return 2;
        }
        this->push_back(label, content, entry_len);
    }
    return 0;
}

list::list(string password, int seed) {
    this->head = nullptr;
    this->password = std::move(password);
    this->seed = seed;
    this->tail = nullptr;
}

list::list() {
    this->head = nullptr;
    this->tail = nullptr;
}

list::list(string filename, string password, int seed) {
    this->head = nullptr;
    this->password = std::move(password);
    this->seed = seed;
    this->tail = nullptr;
    load_from_file(std::move(filename));
}

list::~list() {
    node* cursor = this->head;
    while (cursor) {
        if (!cursor->prev) {
            delete cursor->prev;
        }
        cursor = cursor->next;
    }
}
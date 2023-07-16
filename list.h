#ifndef UNTITLED6_LIST_H
#define UNTITLED6_LIST_H
#include "node.h"


class list {
public:
    node* head;
    node* tail;
    string password;
    int seed;
    node* GetNode(int index);
    int Insert(int index, string label, string content, int len);
    int push_back( string label, string content, int len);
    int push_front( string label, string content, int len);
    node* pop_back();
    node* pop_front();
    void encrypt();
    void decrypt();
    list(string password, int seed);
    list();
};

#endif

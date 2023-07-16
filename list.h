#ifndef UNTITLED6_LIST_H
#define UNTITLED6_LIST_H
#include "node.h"


class list {
public:
    node* head;
    node* tail;
    string password;
    int seed;
    node* get_node(int index);
    int insert(int index, string label, string content, int len);
    int get_length();
    int push_back( string label, string content, int len);
    int push_front( string label, string content, int len);
    node* pop_back();
    node* pop_front();
    void encrypt();
    void decrypt();
    void save_to_file(string filename);
    int load_from_file(string filename);
    list(string password, int seed);
    list(string filename, string password, int seed);
    list();
    ~list();
};

#endif

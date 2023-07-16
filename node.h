#ifndef UNTITLED6_NODE_H
#define UNTITLED6_NODE_H
#include "encrypt_api.h"
using std::string;

class node {
public:
    node* prev;
    node* next;
    string GetLabel();
    void SetLabel(string label);
    string GetContent();
    void SetContent(string content);
    int GetLen();
    void SetLen(int len);
    void Encrypt(string password, int seed);
    node();
    node(string label, string content, int len);

private:
    string label;
    string content;
    int len;
};


#endif

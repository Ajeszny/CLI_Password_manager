#include "node.h"

string node::GetLabel() {
    return this->label;
}
void node::SetLabel(string label) {
    this->label = label;
}
string node::GetContent() {
    return this->content;
}
void node::SetContent(std::string content) {
    this->content = content;
}
int node::GetLen() {
    return this->len;
}
void node::SetLen(int len) {
    this->len = len;
}

node::node() {
    this->prev = nullptr;
    this->len = 0;
    this->label = "";
    this->content = "";
    this->next = nullptr;
}

node::node(std::string label, std::string content, int len) {
    this->prev = nullptr;
    this->len = len;
    this->label = label;
    this->content = content;
    this->next = nullptr;
}

void node::Encrypt(string password, int seed) {
    string ToProcess = Get_Encrypted_String(this->label, this->content, password, seed);
    char* label_alloc = (char*)calloc(ToProcess.length(), sizeof(char));
    char* content_alloc = (char*)calloc(ToProcess.length(), sizeof(char));
    char* kostyl = (char*)calloc(ToProcess.length(), sizeof(char));
    sscanf(ToProcess.c_str(), "%[^\n]\n%s", label_alloc, content_alloc);
    this->label = label_alloc;
    this->content = content_alloc;
    free(label_alloc); free(content_alloc);
}
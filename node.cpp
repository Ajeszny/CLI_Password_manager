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
void node::Encrypt(const string& password, int seed) {
    int ticks = 0;
    string ToProcess;
    while(ticks < 16) {
        ticks++;
        try {
            ToProcess = Get_Encrypted_String(this->label, this->content, password, seed);
            break;
        } catch (std::length_error) {
            this->content.push_back('.');
        }
    }
    if (ticks == 16) {
        throw std::logic_error("There is something weird with your text dude");
    }
    this->content = ToProcess;
}

void node::Decrypt(const string& password, int seed) {
    string processed = Get_Decrypted_String(this->len, this->label.c_str(), this->content.c_str(), password.c_str(), seed);
    char* kostyl = (char*)calloc(this->len+1, sizeof(char));
    strcpy(kostyl, processed.c_str());
    this->content = kostyl;
    free(kostyl);
}

string node::GetDecrString(const std::string &password, int seed) {
    string processed = Get_Decrypted_String(this->len, this->label.c_str(), this->content.c_str(), password.c_str(), seed);
    char* kostyl = (char*)calloc(this->len+1, sizeof(char));
    strcpy(kostyl, processed.c_str());
    string rv = kostyl;
    free(kostyl);
    return rv;
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
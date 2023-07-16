//
// Created by Professional on 15.07.2023.
//

#ifndef UNTITLED6_ENCRYPT_API_H
#define UNTITLED6_ENCRYPT_API_H
#include <iostream>
#include <string>
#include <cstring>
#include <random>
#include <sstream>
#include "SHA256.h"
#include "AES.h"
using std::string;

string encrypt(const unsigned char* plain, const char* pass, int seed);
string decrypt(const unsigned char* cip, const char* pass, int seed, int len);
char* Get_Encrypted_String(const string& label, const string& input, const string& password, int seed);
string Get_Decrypted_String(int len, const char* label, const char* input, const char* pass, int seed);
int Hex_To_Char(const char* hex, char* expr);
#endif //UNTITLED6_ENCRYPT_API_H

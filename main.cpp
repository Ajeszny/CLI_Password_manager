#include <iostream>
#include <string>
#include <cstring>
#include <random>
#include <sstream>
#include "SHA256.h"
#include "AES.h"
using std::string;

string encrypt(const unsigned char* plain, const char* pass, int seed) {
    string a = pass;
    SHA256 sha;
    sha.update(a);
    uint8_t * key = sha.digest();
    AES aes = AES(AESKeyLength::AES_256);
    unsigned char ev[16];
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0, 255);
    for (int i = 0; i < 16; ++i) {
        ev[i] = dist(gen);
    }
    string s = string((char*)aes.EncryptCFB(plain, strlen((char*)plain), key, ev));
    delete key;
    return s;
}

string decrypt(const unsigned char* cip, const char* pass, int seed, int len) {
    string a = pass;
    SHA256 sha;
    sha.update(a);
    uint8_t * key = sha.digest();
    AES aes = AES(AESKeyLength::AES_256);
    unsigned char ev[16];
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0, 255);
    for (int i = 0; i < 16; ++i) {
        ev[i] = dist(gen);
    }
    return string((char*)aes.DecryptCFB(cip, len, key, ev));
}

char* Get_Encrypted_String(const string& label, const string& input, const string& password, int seed) {
    std::stringstream astringstream;
    string encr = encrypt((const unsigned char*)input.c_str(), password.c_str(), seed);
    string bin;
    astringstream << input.length() << label << '\n';
    for (int i = 0; i < encr.length(); ++i) {
        char hexString[10];
        char WHY = encr[i];
        sprintf(hexString, "%02x", (unsigned char)WHY);
        astringstream << hexString;
    }
    string retval(astringstream.str());
    char* dunno = (char*)calloc(retval.length()+1, sizeof(char));
    strcpy(dunno, retval.c_str());
    return dunno;
}

int Hex_To_Char(const char* hex, char* expr) {
    while(*hex&&*(hex+1)) {
        char n[3];
        strncpy(n, hex, 2);
        hex += 2;
        int ni;
        sscanf(n, "%x", &ni);
        if (ni > 255) {
            return 1;
        }
        *expr = ni;
        expr++;
    }
    return 0;
}

string Get_Decrypted_String(int len, const char* label, const char* input, const char* pass, int seed) {//Here I guess I'll use C strings as it's easier to manupulate those
    int number;
    char *encr = (char*) calloc(strlen(input)/2 + 1, sizeof(char));//We don't know the size so I'm allocating in a way so that the capacity is 100% bigger than the things we will put there
    int err = Hex_To_Char(input, encr);
    string decr;
    decr = decrypt(reinterpret_cast<const unsigned char *>(encr), pass, seed, len);
    decr[len] = 0;
    return decr;
}

int main() {
    string a("Dante"), b("Stuckenschmidtus"), c("test");
    int seed = 228;
    string d = Get_Encrypted_String(a, b, c, seed);
    int aa;
    char *e = (char*)calloc(a.length(), sizeof(char)), *f = (char*)calloc(d.length(), sizeof(char));
    sscanf(d.c_str(), "%i%[^\n]\n%s", &aa, e, f);
    string g = Get_Decrypted_String(aa, e, f, "test", seed);
    return 0;
}

#include "encrypt_api.h"


string encrypt(const unsigned char* plain, const char* pass, int seed) {
    string a = pass;//Convert password to a string

    SHA256 sha;
    sha.update(a);
    uint8_t * key = sha.digest();//SHA-256 a pass into a key

    AES aes = AES(AESKeyLength::AES_256);//Initialise AES

    unsigned char ev[16];
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0, 255);
    for (int i = 0; i < 16; ++i) {
        ev[i] = dist(gen);
    }//Randomly create an initialization vector using <random> and set seed

    string s = string((char*)aes.EncryptCFB(plain, strlen((char*)plain), key, ev));//Now we use CFB encryption to encrypt the data

    delete key;
    return s;//Delete the allocated stuff and return the string
}

string decrypt(const unsigned char* cip, const char* pass, int seed, int len) {
    string a = pass;//Convert password to a string

    SHA256 sha;
    sha.update(a);
    uint8_t * key = sha.digest();//SHA-256 a pass into a key

    AES aes = AES(AESKeyLength::AES_256);//Initialise AES

    unsigned char ev[16];
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0, 255);
    for (int i = 0; i < 16; ++i) {
        ev[i] = dist(gen);
    }//Randomly create an initialization vector using <random> and set seed

    string s = string((char*)aes.DecryptCFB(cip, strlen(reinterpret_cast<const char *>(cip)), key, ev));//The function is basically the same thing but encrypts the data

    delete key;
    return s;//Delete the allocated stuff and return the string
}

char* Get_Encrypted_String(const string& label, const string& input, const string& password, int seed) {
    std::stringstream astringstream;//Initialize the stringstream

    string encr = encrypt((const unsigned char*)input.c_str(), password.c_str(), seed);//Get an encrypted string

    astringstream << label << '\n';//Add the couple of values to the stringstream

    for (int i = 0; i < encr.length(); ++i) {
        char hexString[10];
        char WHY = encr[i];
        sprintf(hexString, "%02x", (unsigned char)WHY);
        astringstream << hexString;//Add the hex representation of the encoded message byte by byte
    }

    string retval(astringstream.str());
    char* dunno = (char*)calloc(retval.length()+1, sizeof(char));
    strcpy(dunno, retval.c_str());//Some weird manipulations with string so that it won't throw SYGSEGV

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
    return 0;///Utility function for converting hex expression to a C string
}

string Get_Decrypted_String(int len, const char* label, const char* input, const char* pass, int seed) {//Here I guess I'll use C strings as it's easier to manupulate those
    char *encr = (char*) calloc(strlen(input)/2 + 1, sizeof(char));//We don't know the size so I'm allocating in a way so that the capacity is 100% bigger than the things we will put there
    Hex_To_Char(input, encr);//Make the encrypted data gibberish again
    string decr;
    decr = decrypt(reinterpret_cast<const unsigned char *>(encr), pass, seed, len);
    decr[len] = 0;//Decrypt the string and crop it

    free(encr);//Free the allocated memory

    return decr;
}
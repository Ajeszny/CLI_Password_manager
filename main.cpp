#include "encrypt_api.h"

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

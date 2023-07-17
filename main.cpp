#include "list.h"

int main() {
    char fname[1001], password[128];
    list l;
    int seed;
    printf("Give the name of the file");
    scanf("%s", fname);
    fflush(stdin);
    printf("Give the password");
    scanf("%128[^\n]", password);
    fflush(stdin);
    printf("Enter the seed(any number you want, it'll be used in encryption)");
    scanf("%i", &seed);
    FILE* fp = fopen(fname, "r");
    if (!fp) {
        l = list(password, seed);
    }
    else {
        fclose(fp);
        l = list(fname, password, seed);
    }
    while(1) {
        node* cursor = l.head;
        for (int i = 0; cursor; ++i) {
            printf("%i.%s\n", i+1, cursor->GetLabel().c_str());
            cursor = cursor->next;
        }
        int choice;
        printf("Input the number of the thing you wanna get password of");
        scanf("%i", &choice);
        choice--;
        if (choice >= l.get_length()) {
            char label[1001], npwd[128];
            printf("Enter the label");
            fflush(stdin);
            scanf("%[^\n]", label);
            fflush(stdin);
            printf("Now enter the password for that label");
            scanf("%[^\n]", npwd);
            fflush(stdin);
            l.decrypt();
            l.push_back(label, npwd, strlen(label));
            l.encrypt();
        } else if (choice < 0) {
            break;
        } else {
            printf("%s\n", l.get_password(choice).c_str());
        }
    }
    l.save_to_file(fname);
    return 0;
}

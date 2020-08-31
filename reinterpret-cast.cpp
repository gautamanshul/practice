#include <stdio.h>
#include <string.h>
#include <iostream>
namespace reinterpret {

    struct s {
        uint8_t a;
        uint8_t b[100];
        uint8_t c[100];
        uint32_t f;
    } st;

    void func(char *arr) {
        st.a = 1;
        memcpy(st.b, "cryptoiv", 8);
        memcpy(st.c, "storagekey", 10);
        st.f = 100;

        printf("arr size %d\n", sizeof(arr));
        memcpy(arr, (const unsigned char *) &st, sizeof(st));
        memcpy(arr + sizeof(st), "abcdef", 6);
        printf("arr = %s len = %d\n", arr, strlen(arr));

    }

    bool func1(const std::string &dec) {

        std::cout << dec << std::endl;
        return true;
    }

    int main() {
        char arr[100];
        memset(arr, '\0', sizeof(arr));
        printf("arr len %d\n", strlen(arr));

        printf("sizeof st = %d\n", sizeof(st));
        func(arr);
        uint8_t *p = reinterpret_cast<uint8_t *> (arr);
        printf("p is %d\n", *p);
        p++;
        printf("p is <%s>\n", p);
        printf("arr loc %p. New loc %p\n", arr, arr + sizeof(st));
        p += sizeof(st.b);
        printf("p is <%s>\n", p);
        p += sizeof(st.c);
        uintptr_t addr = (uintptr_t) p;
        if (addr % 8 != 0) {
            addr += 8 - addr % 8;
            p = (uint8_t *) addr;
        }
        struct s s2;

        memcpy(&s2, arr, sizeof(s2));
        std::cout << "b is " << s2.b << std::endl;
        std::cout << "c is " << s2.c << std::endl;
        std::cout << "f is " << st.f << std::endl;
        //char* c = reinterpret_cast<char *>( p );
        //c++;
        //c++;
        uint32_t *f = reinterpret_cast<uint32_t *>( p );
        printf("p is %d\n", *f);
        char payload[10];
        strcpy(payload, "abcd");
        func1(payload);
        return 0;
    }

}
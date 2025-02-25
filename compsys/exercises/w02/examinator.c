/*
#include <stdio.h>

typedef unsigned char byte;

void binary_print(byte toPrint);
void display(size_t index, byte toPrint);
void dump_mem(byte* ptr, size_t N);

int main() {
    int test = 80;
    int test2 = -80;
    double test3 = 0.5;
    double test4 = 0.1;
    byte beginningOfTest1 = ((byte) test);
    byte* test1 = &beginningOfTest1;
    dump_mem(test1, 20);
}

void binary_print(byte toPrint) {
    int intByte = (int) toPrint;
    char binByte[8] = {0};
    for (int i = 0; i <= 7; i ++){
        binByte[i] = intByte % 2;
        intByte = intByte /2;
    }

    for (int i = 7; i >= 0; i--) {
        printf("%d", binByte[i]);
    }
    printf(" ");
}

void display(size_t index, byte toPrint) {
    int intByte = (int) toPrint;
    printf("%02zu :", index);
    binary_print(toPrint);
    printf("%3u", intByte);
    if (intByte >= 32 && intByte <= 126) {
        printf(" '%c'", toPrint);
    }
}

void dump_mem(byte* ptr, size_t N) {
    printf("%p", ptr);
    puts("");
    puts("");
    for (int index = 0; index < N; index ++) {
        display(index, ptr[index]);
        puts("");
    }
}
*/

#include <stdio.h>

typedef unsigned char byte;

void binary_print(byte toPrint);
void display(size_t index, byte toPrint);
void dump_mem(void* ptr, size_t N);

int main() {
    int test = 80;
    int test2 = -80;
    double test3 = 0.5;
    double test4 = 0.1;

    dump_mem(&test, sizeof(test));
    dump_mem(&test2, sizeof(test2));
    dump_mem(&test3, sizeof(test3));
    dump_mem(&test4, sizeof(test4));

    return 0;
}

void binary_print(byte toPrint) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (toPrint >> i) & 1);
    }
    printf(" ");
}

void display(size_t index, byte toPrint) {
    printf("%02zu : ", index);
    binary_print(toPrint);
    printf("%3u", toPrint);
    if (toPrint >= 32 && toPrint <= 126) {
        printf(" '%c'", toPrint);
    }
    puts("");
}

void dump_mem(void* ptr, size_t N) {
    byte* bytePtr = (byte*) ptr;
    printf("%p\n\n", ptr);
    for (size_t index = 0; index < N; index++) {
        display(index, bytePtr[index]);
    }
    puts("");
}

// Estructuras Dinamicas de Datos: Pilas
// Rafael Mata, José Carrillo, Marlon Urdaneta, Tomás Santana, Juan Gil

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 40
#define true 1
#define false 0

typedef struct {
    char name[MAX_STRING];
    char brand[MAX_STRING];
    char cpu[MAX_STRING];
    char videoCard[MAX_STRING];
    int launchYear;
    int ram; // Storage in GiB
    int storage; // Storage in GiB
    char storageType[MAX_STRING];
    int isLaptop;
} PC;

typedef struct Node {
    PC content;
    struct Node* next;
} Node;

typedef struct {
    Node* begin;
    // Node* end; 
} Stack;

Node* NewNode(PC value) {
    Node* new = NULL;
    new = (Node*)malloc(sizeof(Node));

    if (new != NULL) {
        new->content = value;
        new->next = NULL;
    }
    return new;
}

Stack* NewStack(PC firstValue) {
    Stack* new = NULL;
    new = (Stack*)malloc(sizeof(Stack));

    if (new != NULL) {
        new->begin = NewNode(firstValue);
    }
    return new;
}

void push(Stack* stack, PC value) {
    Node* node = NewNode(value);
    node->content = value;

    node->next = stack->begin;
    stack->begin = node;
}

void pop(Stack* stack) {
    Node* erased = stack->begin;
    stack->begin = erased->next;
    free(erased);
}

void iterateStack(Stack* stack, PC (*function)(PC)) {
    Node* actual = stack->begin;
    while (actual != NULL) {
        (*function)(actual->content);
        actual = actual->next;
    }
}

int itemExist(Stack* stack, char name[]) {
    Node* actual = stack->begin;
    while (actual != NULL) {
        if (!strcmp(actual->content.name, name)) return 1; 
    }
    return 0;
}

PC printInfo(PC n) {
    printf(
        "----------------------------------------------\n"
        "\t Name: \t\t %s \n"
        "\t Brand: \t %s \n"
        "\t CPU: \t\t %s \n"
        "\t RAM: \t\t %i GiB\n"
        "\t Video Card: \t %s\n"        
        "\t Launch Year: \t %i \n"        
        "\t Storage: \t %i GiB %s \n"        
        "\t It's a %s \n"
        "----------------------------------------------\n"
        ,n.name, n.brand, n.cpu, n.ram, n.videoCard, n.launchYear
        , n.storage, n.storageType, n.isLaptop ? "Laptop" : "Desktop PC"
        );
    return n;
}

int main() {
    PC dummy1 = {"ThinkPad E560", "Lenovo", "Intel Core i5-6200U", "Intel Skylate", 2015, 8, 1024, "SSD Sata", true};
    PC dummy2 = {"Inspiron 7465", "Dell", "AMD Ryzen 7 5700U", "AMD Radeon GX 450", 2020, 16, 512, "SSD NVMe", true};
    PC dummy3 = {"NZXT Build", "Custom Build", "Intel Core i9-12900k", "NVIDIA RTX 3090 Founders Edition", 2022, 32, 4096, "SSD  NVMe M.2", false};

    Stack* stack = NewStack(dummy1);
    push(stack, dummy2);
    push(stack, dummy3);

    iterateStack(stack, &printInfo);

    printf("\nAfter deleting a record\n\n");
    pop(stack);

    iterateStack(stack, &printInfo);
    return 0;
}

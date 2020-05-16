#include "bible.h"
#include "output.h"
#include "struct.h"

void print_header() { // вывод разметки таблицы
    printf("| %2s|%15s | %8s | %6s| %9s | %4s | %4s | %4s |\n", "Id", "Section", "Product", "Weight(g)", "Calories",
           "Protein",
           " Fat ", "Carbohydrates");
    printf("+---+----------------+----------+----------+-----------+---------+-------+---------------+\n");
}

void struct_out(Node *node) { // вывод полей структуры
    printf("| %2d|%15s | %8s |%9d | %9.2f | %7.2f | %5.2f | %13.2f |\n",
           node->id, node->name, node->type, node->weight, node->calories, node->micro[0],
           node->micro[1],
           node->micro[2]);
}


void Print_Node(Head *head) {// вывод списка
    print_header();
    Node *node = NULL;
    node = head->first;
    while (node != head->last) {// проход по списку с головы выводя каждый узел
        struct_out(node);
        node = node->next;
    }
    struct_out(head->last);
    printf("\n");
}

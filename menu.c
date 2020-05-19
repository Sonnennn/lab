
#include "bible.h"
#include "struct.h"
#include "menu.h"
#include "work_with_list.h"
#include "work_with_data_and_memory.h"
#include "output.h"

void Menu(Head *head) {// вывод меню действий
    int point = 0;
    void (*kind[5])(Head *);
    kind[0] = Menu_before;// массив указателей на функцию для удобства
    kind[1] = Menu_after;
    kind[2] = Menu_delete;
    kind[3] = Menu_copy;
    kind[4] = Menu_change_head;
    while (point != 6) {// вывод возможных действий
        printf("What do you wanna do?\n");
        printf("1 - add node before\n");
        printf("2 - add node after\n");
        printf("3 - delete node\n");
        printf("4 - copy node to position\n");
        printf("5 - change start of the list\n");
        printf("6 - exit\n");

        scanf("%d", &point);// выбор нужной функции
        if (point == 6)return;

        kind[point - 1](head);
    }
}

void Menu_copy(Head *head) {// меню операции копирования
    Node *node, *new_node;
    char **node_dates;
    int paste = 0;
    int copy = 0;
    printf("which node you wanna to copy:");
    while ((copy > head->cnt) || (copy < 1)) {
        scanf("%d", &copy);// считываем номер узла который нужно скопировать
        if (copy > head->cnt || copy < 1) {
            printf("wrong node , try again\n");
            printf("which node you wanna to  copy");
        }
    }
    printf("\n");
    node = select_by_id(head, copy);// ищем этот узел
    node_dates = scan_date(node);
    new_node = create_node(node_dates, 1);
    printf("which node you want to paste:");
    scanf("%d", &paste);// считываем номер узла перед которым нужно вставить

    printf("\n");
    copy_node(head, new_node, paste);// выполняем копирование и вставку
    Print_Node(head);// выводим список


}

void Menu_before(Head *head) {// меню для операции вставки до
    Node *new_node, *node;
    char **str_array;
    int id = 0;
    printf("which node copy you wanna to put before:");
    while ((id > head->cnt) || (id < 1)) {
        scanf("%d", &id);// считываем номер узла перед которым нужно добавить
        if (id > head->cnt || id < 1) {
            printf("wrong node , try again\n");
            printf("which node copy you wanna to put before:");
        }
    }
    printf("\n");
    str_array = scan_node();// считываем информацию для нового узла
    new_node = create_node(str_array, 1);// создаем узел
    printf("Your new node:\n");
    print_header();
    struct_out(new_node);
    printf("\n");
    node = select_by_id(head, id);// ищем узел по номеру
    insert_before(head, new_node, node);// вставляем узел до искомого
    Print_Node(head);// выводим список
}

void Menu_after(Head *head) {// меню для операции добавление после
    Node *new_node, *node;
    char **str_array;
    int id = 0;
    printf("which node you wanna to put after:");
    while ((id > head->cnt) || (id < 1)) {
        scanf("%d", &id);// считываем номер узла после которого нужно добавить
        if (id > head->cnt || id < 1) {
            printf("wrong node, try again\n");
            printf("which node you wanna to put after:");
        }
    }
    printf("\n");
    str_array = scan_node();// вводим информации для узла
    new_node = create_node(str_array, 1);// создаем узел
    printf("Your new node:\n");
    print_header();
    struct_out(new_node);
    printf("\n");
    node = select_by_id(head, id);// ищем указатель по номеру
    insert_after(head, new_node, node);// вставляем после найденного узла новый
    Print_Node(head);// выводим новый список


}

void Menu_delete(Head *head) {// меню для операции удаления
    Node *node;
    int id = 0;
    printf("which node you wanna delete:");
    while ((id > head->cnt) || (id < 1)) {
        scanf("%d", &id);// считываем номер узла который нужно удалить
        if (id > head->cnt || id < 1) {
            printf("wrong node , try again\n");
            printf("which node you wanna delete:");
        }
    }
    printf("\n");
    node = select_by_id(head, id);// ищем на него указатель
    delete_selected(head, node);// удаляем из списка
    Print_Node(head);// выводим новый список


}

void Menu_change_head(Head *head) {// меню смены начала списка
    Node *node;
    int id = 0;
    printf("What node should the list start from?:");
    while ((id > head->cnt) || (id < 1)) {
        scanf("%d", &id);// считываем номер узла с которого будет начинаться список
        if (id > head->cnt || id < 1) {
            printf("wrong node , try again\n");
            printf("What node should the list start from?:");
        }
    }
    printf("\n");
    node = select_by_id(head, id);// ищем на него указатель
    change_head(head, node);// меняем начало
    Print_Node(head);// выводим новый список

}


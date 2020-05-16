#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scan.h"

typedef struct Node {
    int id;
    char *name;
    char *type;
    int weight;
    float calories;
    float micro[3];
    struct Node *next; // указатель на следующий узел
    struct Node *prev;// указатель на предыдущий узел

} Node;
typedef struct Head {
    int cnt;
    Node *first;
    Node *last;
} Head;

Head *make_head();// создание головы списка
Node *create_node(char **str, int id);// создание узла списка
Node *select_by_id(Head *head, int n);// поиска узла по номеру
void insert_before(Head *head, Node *new_node, Node *current_node);// вставка до
void insert_after(Head *head, Node *new_node, Node *current_node);// вставка после
void copy_node(Head *head, Node *current_node, int k);// копирование с .. в ..
void delete_selected(Head *head, Node *current_node);// удаление узла
void Print_Node(Head *head);// вывод списка
void print_header();// вывод заголовка для таблицы
void Menu(Head *head);// вывод меню
void Menu_copy(Head *head); //вывод меню для копирования
void Menu_before(Head *head); // Вывод меню для добавления до
void Menu_after(Head *head); // Вывод меню для добавления после
void Menu_delete(Head *head); // Вывод меню для удаления
void Free_Node(Head *head);// освобождение памяти под список
void struct_out(Node *node);// вывод одного узла
char **simple_split(char *str, int length, char sep);// разделение строки для считывания инф.

int main() {
    Head *head = NULL;
    Node *node = NULL, *node_temp = NULL;
    int maxlen = 128;
    int slen, i, str;
    char **s2 = NULL;
    char file_name[255];
    char s1[maxlen];
    char sep;
    FILE *file = NULL;

    printf("Enter file name: ");// считываем имя файла
    fgets(file_name, 255, stdin);
    *strchr(file_name, '\n') = 0;
    printf("Enter separator:");// считываем разделитель
    scanf("%c", &sep);

    file = fopen(file_name, "r");
    if (file != NULL) {
        head = make_head();
        str = 0;
        printf("\n");
        while ((fgets(s1, maxlen, file)) != NULL) str++;
        rewind(file);// считаем количество строк в файле
// читаем данные из файла и заполняем структуру
        for (i = 1; i < str + 1; i++) {
            fgets(s1, maxlen, file); // берем одну строку
            slen = strlen(s1);
            s1[slen - 1] = '\0';
            slen = strlen(s1);
            s2 = simple_split(s1, slen, sep); // разбиваем ее на части
            node = create_node(s2, i);// создаем элемент списка
            if (i == 1) {// если это первый элемент, то указатель на него помещаем в Head
                head->first = node;
                head->cnt = i;
            }
            if (i > 1) {
                node_temp->next = node;// указатель на новый элемент
                node->prev = node_temp;
            }
            node_temp = node;// запоминаем указатель на прошлый элемент

        }
        head->last = node;// заносим последний элемент в Head
        head->last->next = head->first;
        head->first->prev = head->last;
        head->cnt = head->last->id;// номер последнего элемента - кол-во элементов
        Print_Node(head);// выводим изначальный список
        Menu(head);
        fclose(file);
        Free_Node(head);// освобождаем память выделенную под список
    } else puts("File not found!");
    return 0;
}


void Menu_copy(Head *head) {// меню операции копирования
    Node *node;
    int copy, paste;
    printf("which node id you want to copy:");
    scanf("%d", &copy);// считываем номер узла который нужно скопировать
    node = select_by_id(head, copy);// ищем этот узел
    printf("which node id you want to paste:");
    scanf("%d", &paste);// считываем номер куда нужно вставить
    printf("\n");
    copy_node(head, node, paste);// выполняем копирование и вставку
    Print_Node(head);// выводим список


}

void Menu_before(Head *head) {// меню для операции вставки до
    Node *new_node, *node;
    char **s2;
    int id = 0;
    printf("which node id you want to put after:");
    while ((id > head->cnt) || (id < 1)) {
        scanf("%d", &id);// считываем номер узла после которого нужно добавить
        if (id > head->cnt || id < 1) {
            printf("wrong node id , try again\n");
            printf("which node id you want to put after:");
        }
    }
    printf("\n");
    s2 = scan_node();// считываем информацию для нового узла
    new_node = create_node(s2, 1);// создаем узел
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
    printf("which node id you want to put after:");
    while ((id > head->cnt) || (id < 1)) {
        scanf("%d", &id);// считываем номер узла после которого нужно добавить
        if (id > head->cnt || id < 1) {
            printf("wrong node id , try again\n");
            printf("which node id you want to put after:");
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
    int id;
    printf("which node id you want to delete:");
    scanf("%d", &id);// вводим номер узла который нужно удалить
    printf("\n");
    node = select_by_id(head, id);// ищем на него указатель
    delete_selected(head, node);// удаляем из списка
    Print_Node(head);// выводим новый список


}

Node *select_by_id(Head *head, int n) { // поиск нужного узла по номеру
    Node *node;
    int k;

    node = head->first;
    k = head->cnt;
    if (n > k) n = k;
    if (n == 0) n = 1;
    if ((n > 0) && (n <= k)) {// проходим по списку пока не дойдем до нужного номера
        while ((node->id) != n)
            node = node->next;
    } else node = NULL;
    return node;// возвращаем указатель на этот узел
}

void delete_selected(Head *head, Node *current_node) {// удаление определенного узла
    Node *node_temp, *temp;

    node_temp = head->first;
    temp = head->last;
    if (current_node == node_temp) {// если это первый узел , то
        head->first = current_node->next;// то первым будет узел после прошлого первого
        current_node->next = NULL;// освобождаем память под этот узел
        free(current_node->name);
        free(current_node->type);
        current_node->name = NULL;
        current_node->type = NULL;
        free(current_node);
        node_temp = head->first;
        while (node_temp != NULL) {// проходим по списку уменьшая номера узлов
            node_temp->id--;
            node_temp = node_temp->next;
        }

    } else {
        while (node_temp != NULL) {// проходим по списку пока не дойдем до нужного
            if (node_temp->next == current_node) {// если это нужный узел
                if (current_node == temp) head->last = node_temp;// если это последний то обновляем последний в голове
                node_temp->next = current_node->next;// предыдущему узлу даем адрес на следующий
                free(current_node->name);// освобождаем память под этот узел
                free(current_node->type);
                current_node->name = NULL;
                current_node->type = NULL;
                current_node->next = NULL;
                free(current_node);
                while (node_temp->next != NULL) {// проходим дальше по узлам уменьшая их номер
                    node_temp = node_temp->next;
                    node_temp->id--;

                }
            } else node_temp = node_temp->next;
        }
    }
    head->cnt--;
}

void insert_after(Head *head, Node *new_node, Node *current_node) {// вставка узла после текущего
    Node *node_temp;
    if (head && new_node && current_node) {
        new_node->next = current_node->next;
        new_node->prev = current_node;
        current_node->next = new_node;
        new_node->next->prev = new_node;
        if (current_node == head->last){
            head->last = new_node;}
        new_node->id = current_node->id + 1;
        node_temp = new_node;
        while (node_temp->next != head->first) {// проходим по списку увеличивая номера узлов
            node_temp = node_temp->next;
            node_temp->id++;

        }
        head->cnt++;
    }

}


void insert_before(Head *head, Node *new_node, Node *current_node) {// вставка узла перед определенным элементом
    Node *node_temp;
    if (head && new_node && current_node) {
        new_node->prev = current_node->prev;
        new_node->next = current_node;
        current_node->prev = new_node;
        new_node->prev->next = new_node;
        if (current_node == head->first)
            head->first = new_node;
        new_node->id = current_node->id;
        node_temp = new_node;
        while (node_temp->next != head->first) {// проходим по списку увеличивая номера узлов
            node_temp = node_temp->next;
            node_temp->id++;

        }
        head->cnt++;
    }

}

void copy_node(Head *head, Node *current_node, int k) {// копирование данных из одного узла в другой
    Node *new_temp, *new = NULL;

    if (k == 0) {// если нужно скопировать элемент в начало списка , то
        new = (Node *) malloc(sizeof(Node));// выделяем память под узел списка
        new->name = (char *) malloc(30 * sizeof(char));
        new->type = (char *) malloc(30 * sizeof(char));
        strcpy(new->name, current_node->name);// копируем все данные с копируемого узла
        strcpy(new->type, current_node->type);
        new->calories = current_node->calories;
        new->weight = current_node->weight;
        for (int i = 0; i < 3; i++) {
            new->micro[i] = current_node->micro[i];
        }
        new->next = head->first;// указатель на следующий элемент становится прошлый первый
        head->first = new;
        new->id = 1;
        new_temp = head->first;
        while (new_temp->next != NULL) {// увеличиваем индексы всех элементов списка
            new_temp = new_temp->next;
            new_temp->id++;
        }

    } else {
        if (k > head->cnt) {// если индекс узла превышает количество элементов в списке , то ставим его в конец
            new = (Node *) malloc(sizeof(Node));// выделяем память под узел списка
            new->name = (char *) malloc(30 * sizeof(char));// копируем все данные
            new->type = (char *) malloc(30 * sizeof(char));
            strcpy(new->name, current_node->name);
            strcpy(new->type, current_node->type);
            new->calories = current_node->calories;
            new->weight = current_node->weight;
            for (int i = 0; i < 3; i++) {
                new->micro[i] = current_node->micro[i];
            }
// бывшему последнему элементу ставим указатель на новый элемент
            head->last->next = new;
            head->last = new;// обновляем последний элемент головы списка
            new->id = head->cnt + 1;
        } else {
            new_temp = select_by_id(head, k);
            free(new_temp->type); // если индекс лежит среди элементов списка ,то
            free(new_temp->name); // то освобождаем ячейки этого узла
            new_temp->name = (char *) malloc(30 * sizeof(char));// и заносим информацию с копируемого элемента
            new_temp->type = (char *) malloc(30 * sizeof(char));
            strcpy(new_temp->name, current_node->name);
            strcpy(new_temp->type, current_node->type);
            new_temp->calories = current_node->calories;
            new_temp->weight = current_node->weight;
            for (int i = 0; i < 3; i++) {
                new_temp->micro[i] = current_node->micro[i];
            }
        }
    }
    head->cnt++;

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

void Free_Node(Head *head) {// освобождение памяти под список
    Node *temp_node = NULL;
    Node *temp=NULL;
    temp_node = head->last;
    while (temp_node!= head->first) {// проходим по списку и освобождаем память пока не дойдем до конца
        free(temp_node->type);
        free(temp_node->name);
        temp=temp_node->prev;
        temp_node = temp;
    }
    free(temp_node->type);
    free(temp_node->name);
    free(head);
}

Node *create_node(char **str, int id) // инициализация узла
{
    Node *new_node = NULL; // выделяем память под узел и заполняем его и массива строк
    new_node = (Node *) malloc(sizeof(Node));
    new_node->id = id;
    new_node->name = str[0];
    new_node->type = str[1];
    new_node->weight = atoi(str[2]);
    new_node->calories = atof(str[3]);
    new_node->micro[0] = atof(str[4]);
    new_node->micro[1] = atof(str[5]);
    new_node->micro[2] = atof(str[6]);
    new_node->next = NULL;
    new_node->prev = NULL;


    return new_node; // возвращаем адрес узла
}


void Menu(Head *head) {// вывод меню действий
    int point = 0;
    void (*kind[4])(Head *);
    kind[0] = Menu_before;// массив указателей на функцию для удобства
    kind[1] = Menu_after;
    kind[2] = Menu_delete;
    kind[3] = Menu_copy;
    while (point != 5) {// вывод возможных действий
        printf("What do you wanna do?\n");
        printf("1 - add node before\n");
        printf("2 - add node after\n");
        printf("3 - delete node\n");
        printf("4 - copy node to position\n");
        printf("5 - exit\n");

        scanf("%d", &point);// выбор нужной функции
        if (point == 5)return;

        kind[point - 1](head);
    }
}

Head *make_head() {// создание головы списка
    Head *head = NULL;

    head = (Head *) malloc(sizeof(Head));
    if (head) {
        head->cnt = 0;
        head->first = NULL;
        head->last = NULL;
    }
    return head;
}


/* ----------------------------------------- */
char **simple_split(char *str, int length, char sep) { // разделение строки на части
    char **str_array = NULL;
    int i, j, k, m;
    int key;
    for (j = 0, m = 0; j < length; j++) {
        if (str[j] == sep) m++;// считаем кол-во знаков разделителей
    }

    key = 0;
    str_array = (char **) malloc((m + 1) * sizeof(char *));// выделяем память под массив строк
    if (str_array != NULL) {
        for (i = 0; i <= m; i++) {
            str_array[i] = (char *) malloc(length * sizeof(char));
            if (str_array[i] != NULL) key = 1;// проходим по строке ища знак разделитель
            else {
                key = 0;
                i = m;
            }
        }
        if (key) {
            k = 0;
            m = 0;
            for (j = 0; j < length; j++) {// как только знак нашелся , заполняем соответствующее элемент массива строк
                if (str[j] != sep) str_array[m][j - k] = str[j];
                else {
                    str_array[m][j - k] = '\0';
                    k = j + 1;
                    m++;
                }
            }

        }
    }
    str_array[m][j - k] = '\0';
    return str_array;// возвращаем указатель на массив строк
}

/* ----------------------------------------- */
void print_header() { // вывод разметки таблицы
    printf("| %2s|%15s | %8s | %6s| %9s | %4s | %4s | %4s |\n", "Id", "Section", "Product", "Weight(g)", "Calories",
           "Protein",
           " Fat ", "Carbohydrates");
    printf("+---+----------------+----------+----------+-----------+---------+-------+---------------+\n");
}

/* ----------------------------------------- */

/* ----------------------------------------- */
void struct_out(Node *node) { // вывод полей структуры
    printf("| %2d|%15s | %8s |%9d | %9.2f | %7.2f | %5.2f | %13.2f |\n",
           node->id, node->name, node->type, node->weight, node->calories, node->micro[0],
           node->micro[1],
           node->micro[2]);
}


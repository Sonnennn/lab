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
void Menu_change_head(Head *head);
void Free_Node(Head *head);// освобождение памяти под список
void struct_out(Node *node);// вывод одного узла
char **simple_split(char *str, int length, char sep);// разделение строки для считывания инф.
char** scan_date(Node* node);
void change_head(Head *head,Node * node);

int main() {
    Head *head = NULL;
    Node *node = NULL, *node_temp = NULL,*temp=NULL;
    int maxlen = 128;
    int slen, i, str,flag;
    char **s2 = NULL;
    char file_name[maxlen];
    char out_file_name[maxlen];
    char s1[maxlen];
    char sep;
    FILE *file = NULL;
    FILE *out_file=NULL;

    printf("Enter file name: ");// считываем имя файла
    fgets(file_name, maxlen, stdin);
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
        printf("\n");

        printf("do you wanna save result?\n");
        printf("1-Yes\n");
        printf("2-No\n");
        printf("\nYour choice:");
        scanf("%d",&flag);
        if(flag==1)
        {
         fflush(stdin);
        printf("Which file you wanna save result: ");// считываем имя файла
        fgets(out_file_name, maxlen, stdin);
        *strchr(out_file_name, '\n') = 0;
        out_file=fopen(out_file_name,"w");
        temp=head->first;
        while(temp!=head->last){
            fprintf(out_file,"%s;%s;%d;%.2f;%.2f;%.2f;%.2f\n",temp->name,temp->type,temp->weight,temp->calories,temp->micro[0],temp->micro[1],temp->micro[2]);
            temp=temp->next;
        }
        fprintf(out_file,"%s;%s;%d;%.2f;%.2f;%.2f;%.2f\n",temp->name,temp->type,temp->weight,temp->calories,temp->micro[0],temp->micro[1],temp->micro[2]);
        fclose(out_file);
        }
        fclose(file);
        Free_Node(head);// освобождаем память выделенную под список
    } else puts("File not found!");
    return 0;
}


void Menu_copy(Head *head) {// меню операции копирования
    Node *node,*new_node;
    char **node_dates;
    int paste=0;
     int copy = 0;
    printf("which node you wanna to copy:");
    while ((copy > head->cnt) || (copy < 1)) {
        scanf("%d", &copy);// считываем номер узла после которого нужно добавить
        if (copy > head->cnt || copy < 1) {
            printf("wrong node , try again\n");
            printf("which node you wanna to  copy");
        }
    }
    printf("\n");
    node = select_by_id(head, copy);// ищем этот узел
    node_dates=scan_date(node);
    new_node=create_node(node_dates,1);
    printf("which node you want to paste:");
    scanf("%d", &paste);// считываем номер узла после которого нужно добавить

    printf("\n");
    copy_node(head, new_node, paste);// выполняем копирование и вставку
    Print_Node(head);// выводим список


}

void Menu_before(Head *head) {// меню для операции вставки до
    Node *new_node, *node;
    char **s2;
    int id = 0;
    printf("which node copy you wanna to put before:");
    while ((id > head->cnt) || (id < 1)) {
        scanf("%d", &id);// считываем номер узла после которого нужно добавить
        if (id > head->cnt || id < 1) {
            printf("wrong node , try again\n");
            printf("which node copy you wanna to put before:");
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
        scanf("%d", &id);// считываем номер узла после которого нужно добавить
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
void Menu_change_head(Head *head){
    Node*node;
    int id=0;
    printf("What node should the list start from?:");
    while ((id > head->cnt) || (id < 1)) {
        scanf("%d", &id);// считываем номер узла после которого нужно добавить
        if (id > head->cnt || id < 1) {
            printf("wrong node , try again\n");
            printf("What node should the list start from?:");
        }
    }
    printf("\n");
    node = select_by_id(head, id);// ищем на него указатель
    change_head(head, node);// удаляем из списка
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
    Node *temp;
    int flag;
    current_node->prev->next=current_node->next;
    current_node->next->prev=current_node->prev;
    if (current_node==head->first)
    {   flag=1;
        head->first=current_node->next;
    }
    if (current_node==head->last)
    {
        head->last=current_node->prev;
    }
    if( current_node->prev!=head->last&&current_node->next!=head->first)
        flag=2;
     if (flag==1)
     {
         temp=head->first;
         while (temp!=head->last)
         {
             temp->id--;
             temp=temp->next;
         }
         temp->id--;
     }
     if (flag==2)
     {
        temp=current_node->prev;
         while (temp->next!=head->last)
         {
             temp=temp->next;
             temp->id--;
         }
         temp=temp->next;
         temp->id--;
     }

    free(current_node->name);
    free(current_node->type);
    free(current_node);
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

void copy_node(Head *head, Node *new_node, int k) {// копирование данных из одного узла в другой
    Node *temp= NULL;
    if (k>head->cnt){
        temp=select_by_id(head,k);
        insert_after(head,new_node,temp);
    }else{
    temp=select_by_id(head,k);
    insert_before(head,new_node,temp);}
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
        free(temp_node);
        temp_node = temp;
    }
    free(temp_node->type);
    free(temp_node->name);
    free(temp_node);
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
    void (*kind[5])(Head *);
    kind[0] = Menu_before;// массив указателей на функцию для удобства
    kind[1] = Menu_after;
    kind[2] = Menu_delete;
    kind[3] = Menu_copy;
    kind[4]= Menu_change_head;
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

char ** scan_date(Node* node){

    int length=100;
    char **str_array = NULL;
    str_array = (char **) malloc((7 + 1) * sizeof(char *));// выделяем память под массив строк
    if (str_array != NULL) {
        for (int i = 0; i <= 7; i++) {
            str_array[i] = (char *) malloc(length * sizeof(char));
        }
        strcpy(str_array[0],node->name);
        strcpy(str_array[1],node->type);
        itoa(node->weight,str_array[2],10);
        sprintf(str_array[3],"%.2f",node->calories);
        sprintf(str_array[4],"%.2f",node->micro[0]);
        sprintf(str_array[5],"%.2f",node->micro[1]);
        sprintf(str_array[6],"%.2f",node->micro[2]);
    }
return(str_array);
}
void change_head(Head *head,Node * node){
    Node *temp;
    Node *temp_begin=head->first;
    Node *temp_last=head->last;
    int begin=node->id-1;
    int end=head->cnt-begin;
head->first=node;
head->last=node->prev;
temp=head->first;
while(temp!=temp_begin){
    temp->id=temp->id-begin;
    temp=temp->next;
}
while(temp_last!=head->last){
    temp_last=temp_last->next;
    temp_last->id=temp_last->id+end;

}
}
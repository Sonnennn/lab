#include "bible.h"
#include "struct.h"
#include "work_with_data_and_memory.h"

Head *read_from_file() {// создание списка данных из файла
    Head *head = NULL;
    Node *node = NULL, *node_temp = NULL;
    int maxlen = 128;
    int slen, i, str;
    char **s2 = NULL;
    char file_name[maxlen];
    char s1[maxlen];
    char sep;
    FILE *file = NULL;
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
        fclose(file);
    } else puts("File not found!");
    return (head);
}

void out_to_file(Head *head) {// запись списка в файл
    int flag;
    Node *temp = NULL;
    int maxlen = 128;
    FILE *out_file = NULL;
    char out_file_name[maxlen];
    printf("\n");

    printf("do you wanna save result?\n");// спрашиваем хочет ли сохрвнить
    printf("1-Yes\n");
    printf("2-No\n");
    printf("\nYour choice:");
    scanf("%d", &flag);
    if (flag == 1) {
        fflush(stdin);
        printf("Which file you wanna save result: ");// считываем имя файла
        fgets(out_file_name, maxlen, stdin);
        *strchr(out_file_name, '\n') = 0;
        out_file = fopen(out_file_name, "w");// открываем файл для записи
        temp = head->first;
        while (temp != head->last) {// пока не конеч списка заносим данные с узлов
            fprintf(out_file, "%s;%s;%d;%.2f;%.2f;%.2f;%.2f\n", temp->name, temp->type, temp->weight, temp->calories,
                    temp->micro[0], temp->micro[1], temp->micro[2]);
            temp = temp->next;
        }
        fprintf(out_file, "%s;%s;%d;%.2f;%.2f;%.2f;%.2f\n", temp->name, temp->type, temp->weight, temp->calories,
                temp->micro[0], temp->micro[1], temp->micro[2]);
        fclose(out_file);
    }
}


#include "bible.h"
#include "struct.h"

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

char **scan_node() { // ввод элементов нового узла списка
    int slen;// длина строки
    char data[30];// массив для ввода информации с строки
    char **str_array = NULL;
    str_array = (char **) malloc((8) * sizeof(char *));// выделяем память для массива строк
    printf("enter your dates:\n");
    for (int i = 0; i < 7; i = i + 1) {
        fflush(stdin);
        fgets(data, 30, stdin);// считываем строки
        str_array[i] = (char *) malloc(255 * sizeof(char));
        slen = strlen(data);
        data[slen - 1] = '\0';
        for (int j = 0; j < slen; j++) {// заполняем строками массив строк
            str_array[i][j] = data[j];
        }
        str_array[i][slen - 1] = '\0';
    }
    return str_array;// возвращаем указатель на массив строк
}

void Free_Node(Head *head) {// освобождение памяти под список
    Node *temp_node = NULL;
    Node *temp = NULL;
    temp_node = head->last;
    while (temp_node != head->first) {// проходим по списку и освобождаем память пока не дойдем до конца
        free(temp_node->type);
        free(temp_node->name);
        temp = temp_node->prev;
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

char **scan_date(Node *node) {//создает массив строк с данными переданного узла

    int length = 100;
    char **str_array = NULL;
    str_array = (char **) malloc((7 + 1) * sizeof(char *));// выделяем память под массив строк
    if (str_array != NULL) {
        for (int i = 0; i <= 7; i++) {
            str_array[i] = (char *) malloc(length * sizeof(char));// выделяет память под сами строки
        }
        strcpy(str_array[0], node->name);// заполняет сами строки данными из полей узла
        strcpy(str_array[1], node->type);
        itoa(node->weight, str_array[2], 10);
        sprintf(str_array[3], "%.2f", node->calories);
        sprintf(str_array[4], "%.2f", node->micro[0]);
        sprintf(str_array[5], "%.2f", node->micro[1]);
        sprintf(str_array[6], "%.2f", node->micro[2]);
    }
    return (str_array);
}


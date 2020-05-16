
#include "scan.h"
#include "bible.h"
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
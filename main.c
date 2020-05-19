#include "bible.h"
#include "menu.h"
#include "struct.h"
#include "work_with_file.h"
#include "output.h"
#include "work_with_data_and_memory.h"

int main() {
    Head *head = NULL;
    head = read_from_file();// формируем начальный список из файла
    Print_Node(head);// выводим изначальный список
    Menu(head); // меню действий со списком
    out_to_file(head);// запись списка в файл
    Free_Node(head);// освобождаем память выделенную под список

    return 0;
}



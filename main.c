#include "menu.h"
#include "struct.h"
#include "work_with_file.h"
#include "output.h"
#include "work_with_data_and_memory.h"
int main() {
        Head *head = NULL;
        head=read_from_file();
        Print_Node(head);// выводим изначальный список
        Menu(head);
        out_to_file(head);
        Free_Node(head);// освобождаем память выделенную под список

    return 0;
}



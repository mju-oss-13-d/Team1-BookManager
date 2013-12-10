#ifndef __LINKED_LIST_FUNCTION_H__
#define __LINKED_LIST_FUNCTION_H__

#include "structure_file.h"

BOOK_NODE *insert(BOOK_NODE *, BOOK_NODE *);
BOOK_NODE* delete_book_file(char* a, char* b, BOOK_NODE *list);
BOOK_NODE* Find(char* a, char* b, BOOK_NODE *list);
void *print_links(BOOK_NODE * );
unsigned int counting_links(BOOK_NODE *);

#endif  // __LINKED_LIST_FUNCTION_H__

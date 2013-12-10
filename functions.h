#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "structure_file.h"

int menu_print(void);           /* 메뉴 구현 함수 원형 */
void insert_book();          /* 메뉴 1번인 Insert, 도서추가 부분을 구현 */
void print_list_books();     /* 메뉴 2번인 List, 목록 출력을 구현 */
void Find_book(); /* 찾는 함수 */
void delete_book(); /* 지우는 함수 */

void inputing_data_except_null(char *, int); /* 문자열을 입력 받아서 첫번째 인수에 저장한다. 두번째 인수는 길이  */
int pointing_location_of_null(char *);

#endif // __FUNCTIONS_H__

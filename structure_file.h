#ifndef __STRUCTURE_FILE_H__
#define __STRUCTURE_FILE_H__

#define HOW_MANY_MAGIC_NUMBER 30 /* 매직 넘버의 갯수 */

#define BOOK_NAME       30      /* 책의 이름을 받을 바이트 수 */
#define AUTHOR_NAME     15      /* 저자의 이름을 받을 바이트 수 */
#define PUBLISHER_NAME  15      /* 출판사의 이름을 받을 바이트 수 */
#define HOW_MUCH_BOOK   15      /* 책의 가격을 받을 바이트 수 */
#define YEAR_OF_PUB     15      /* 출판년도를 받을 바이트 수 */

#pragma pack(1)                 /* 구조체를 1바이트 단위로 채워 넣는다. */


typedef struct dbf_header       /* 데이터 파일의 헤더를 위한 버퍼 */
{
    unsigned int amount_of_book;         /* 총 입력된 파일의 권 수. */
    char magic_number[HOW_MANY_MAGIC_NUMBER];      /* Asterisk로 이루어진 총 30바이트의 공간 */
    /* 헤더 파일은 위에 명시된 것과 같이 총 34바이트를 차지하게 된다. */
} DBF_HEADER;

typedef struct booktype_node         /*  책의 기본 구조체 */
{
    char book[30];       /* 책 */
    char author[AUTHOR_NAME];   /* 저자 */
    char publisher[PUBLISHER_NAME]; /* 출판사 */
    char price[HOW_MUCH_BOOK];      /* 가격 */
    char year[YEAR_OF_PUB];         /* 출판년도 */
    struct booktype_node *next;     /* 연결 리스트 및 터플을 위한 공간. */
} BOOK_NODE;

#endif // __STRUCTURE_FILE_H__



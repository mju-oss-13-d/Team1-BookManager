#include "header_files.h"

void writing_data_file(BOOK_NODE *books)           /*  저 수준 파일 입출력을 통한 데이터 파일 생성 함수 */
{
    DBF_HEADER header;
    
    char turple = '|';            /* 터플 */
    
    int infd;
    char buffer[35];
    
//  infd = open("book.dbf", O_CREAT | O_RDWR | O_BINARY); /* DOS 용. */

    header.amount_of_book = counting_links(books); /* counting_links 함수가 링크 수를 세어서 대입 */
    INIT_writing_header(header.amount_of_book);      /* 헤더 삽입 함수, 책의 권 수도 함께 삽입 */
    
    
    infd = open("book.dbf", O_RDWR); /* 리눅스용 */
    if(infd < 0)
    {
        perror("Sorry, failed to open the file.");
        exit(-1);
    }

    read(infd, buffer, 34);            /* 헤더 데이터 바로 다음 위치인 35바이트에 위치 시킨다. */

    while(1)                    /* 도서목록을 파일에 쓰기 위한 루틴. */
    {
        /* write(infd, books, (sizeof(BOOK_NODE) - 4)); /\* 버퍼에 있는 내용을 파일에 쓴다. *\/ */
        write(infd, books, (sizeof(BOOK_NODE))); /* 버퍼에 있는 내용을 파일에 쓴다. */

        lseek(infd, -1, SEEK_CUR); /* 데이터 구조체 멤버 next의 자리를 사용한다. */
        write(infd, &turple, 1); /* 미리 선언된 터플을 파일에 쓴다. */
        
        if(books -> next == NULL) /* 목록의 끝인지를 판단 */
        {
            break;              /* 끝이면 저장 끝 */
        }
        else
        {
            books = books -> next;
        }
    }
    close(infd);                /* 파일을 닫는다. */

}

void INIT_writing_header(unsigned int amount_of_books)      /* 새로 생성된 데이터 파일에 헤더정보를 쓴다. */
{
    DBF_HEADER header = {0, "******************************"}; /* 구조체 초기화 별은 30개*/

    header.amount_of_book = amount_of_books; /* 책의 갯수 대입한다. */
    
    int outfd;

    /* 쓰기전용으로 파일을 연다. */
/* //    outfd = open("book.dbf", O1_WRONLY | O_BINATY); /\* 바이너리 형태의 쓰기 전용으로 파일을 연다. *\/ */

    outfd = open("book.dbf", O_CREAT | O_TRUNC | O_RDWR, S_IREAD | S_IWRITE); /* 바이너리 형태의 쓰기 전용, 읽고 쓰기 가능 파일을 새로 만든다. */
    if(outfd < 0)                                  /* 파일열기를 실패했을땐 종료. */
    {
        printf("Failed to open the file for writing.\n");
        exit(-1);
    }

    /* 헤더 부분을 작성하기 위해 준비된 구조체에 정보입력. */
    write(outfd, &header, sizeof(header)); /* 버퍼에 있는 내용을 파일에 쓴다. */
    
    close(outfd);               /* 파일을 닫는다. */
}

BOOK_NODE *loading_data_file(BOOK_NODE *data)     /* 파일을 불러 들인다. */
{
    BOOK_NODE temp;
    BOOK_NODE *temp_return = data;     /* 리턴용 변수 */

    int amount_books;
    int infd;                   /* 파일 핸들러 */
    int i_counter;

    infd = open("book.dbf", O_RDWR); /* 파일 존재 여부를 검사. 이 부분이 없으면 garbage 값을 가지고 linked list에 접근 */
    if(infd == -1)                   /* 파일이 없으면 -1 가지게 되는 -1 과 비교 */
    {
        printf("There is no data file, \"book.dbf\" or failed to open the file.\n");
        close(infd);
        
        return temp_return;     /* NULL 값을 다시 돌려주고 함수 종료. */
    }
        
    amount_books = checking_header(&infd); /* 헤더 검사를 한다. */
    if(amount_books < 0)                  /* 헤더 검사에서 오류 */
    {
        printf("The data file might be broken. Please check the file. \n");
        return temp_return;     /* NULL 값을 돌려주고 함수 종료. */
    }
    else
    {
        lseek(infd, 1 * sizeof(DBF_HEADER), SEEK_SET); /* 헤더 부분 만큼 지나간다. */

        for(i_counter = 1; amount_books >= i_counter; ++i_counter) /* 파일에서 데이터 구조체 단위로 뽑아서 메모리 적재 */
        {
            read(infd, &temp, sizeof(BOOK_NODE)); /* 데이터를 읽어서, 구조체에 넣는다. */
            temp_return = insert(&temp, temp_return); /* linked list에 넣고 반환되는 첫 NODE 주소를 대입. */
        }
    }

    return temp_return;         /* 첫 NODE의 시작 값을 반환한다. */
}

int checking_header(int *infd) /* 헤더를 검사하고 return 값으로 레코드 갯수를 반환한다. */
{
    DBF_HEADER header_temp;

    unsigned int amountBooks = 0;
    char magic_key_from_file[35];
    char buffer[31] = {"******************************"}; /* 헤더검사를 위한 매직 키,
                                                           * 자동으로 들어갈 NULL 자리를 비워 둠 */
    *infd = open("book.dbf", O_RDWR); /* 파일을 불러온다. */
    if(infd < 0)                     /* 실패했다면 에러 메세지를 출력 후 함수를 종료. */
    {
        perror("Failed to open the file :: ");
       return;
    }
    read(*infd, &header_temp, sizeof(DBF_HEADER)); /* 헤더 부분에서 매직 키에 접근. */
    amountBooks = header_temp.amount_of_book;         /* 갯수를 대입 */
    
    strcpy(magic_key_from_file, header_temp.magic_number); /* 매직키를 추출하여 준비된 배열에 넣는다. */
//waring
    magic_key_from_file[30] = '\0';                        /* 마지막에 NULL을 넣어서 garbage 값을 방지 */
    
    if(0 == strcmp(magic_key_from_file, buffer))  /* 주어진 매직 키와 파일에서 추출한 키와 비교한다.  */
    {
        /* return header_temp.amount_of_book; /\* 올바른 데이터 파일일 경우, 레코드 갯수를 반환 *\/ */
        return amountBooks; /* 올바른 데이터 파일일 경우, 레코드 갯수를 반환 */
    }
    else
    {
        return -1;               /* 데이터 파일에 이상이 있을 경우 */
    }

}

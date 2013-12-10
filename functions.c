#include "header_files.h"

BOOK_NODE *main_list = NULL; /* 이 변수는 반드시 도서목록 연결 리스트의 시작을 가지고 있어야 한다. */
BOOK_NODE *Found_book = NULL;
BOOK_NODE *deleted_book = NULL;
 
int menu_print()
{
    int choisen_menu_number;  /* 선택된 메뉴번호를 저장하는 변수 */
    main_list = loading_data_file(main_list); /* 기본 데이터 파일인 "book.dbf"을 부른다. */
        
    while(1)                    /* 메뉴는 종료를 선택할 때까지 반복해서 출력된다. */
    {
        putchar('\n');
        printf("1.  Insert\n");
        printf("2.  List\n");
        printf("3.  Save as a data file\n");
	printf("4.  (new)Delete List\n");		/*new*/
	printf("5.  (new)Search the Book\n");	/*new*/
        printf("6.  Quit\n\n");
        printf("Enter the number : ");

        choisen_menu_number = getchar(); /* 메뉴 번호를 아스키코드로 받는다. */
        __fpurge(stdin);                 /* 버퍼를 비워 준다. */
        
        switch(choisen_menu_number)
        {
        case '1':                     /* 책을 연속적으로 추가하는 기능을 기본으로 한다. */
            insert_book();
            break;

        case '2':
            print_list_books(); /* 입력된 도서목록을 출력하며 책 추가 기능과 삭제 기능이 있다. */
            break;

        case '3':
            writing_data_file(main_list);
            break;

        case '4':
		delete_book();
	    break;

	case '5':
		Find_book();
            	break;

	case '6':
            printf("Thanks for using. See you again.\n");
            exit(-1);

        default:                /* 사용자가 지정된 키 이외의 입력을 했을 경우 에러 메세지 출력 후 다시 메뉴를 출력. */
            printf("You enter the wrong number.\n");
        }
    }    
    return choisen_menu_number;
}

void insert_book()          /* 메뉴 1번인 Insert, 도서추가 부분을 구현 */
{
    BOOK_NODE books = {0, 0, 0, 0, 0, 0}; /* 구조체 멤버들을 NULL 로 초기화 한다.
                                           * 초기화는 {0, }; 와 같은 방법도 가능하다.*/

    printf("Enter the book's title : "); /* 책 제목을 입력 받는다. */
    inputing_data_except_null(books.book, sizeof(books.book));
    
    printf("Enter the author's name : "); /* 저자의 이름을 입력 받는다. */
    inputing_data_except_null(books.author, sizeof(books.author));

    printf("Enter the publisher's name : "); /* 발행처를 입력 받는다. */
    inputing_data_except_null(books.publisher, sizeof(books.publisher));

    printf("Enter the price of the book : "); /* 책의 가격을 입력 받는다. */
    inputing_data_except_null(books.price, sizeof(books.price));

    printf("Enter the year of publishing : "); /* 책의 발행 연도를 입력 받는다. */
    inputing_data_except_null(books.year, sizeof(books.year));
           
    main_list = insert(&books, main_list); /* 도서목록 연결 리스트에 추가한다. */

    writing_data_file(main_list); /* 입력받은 데이터를 데이터 파일에 쓴다. */
}

void print_list_books()         /* 메뉴 2번인 도서목록 출력을 구현. */
{
    print_links(main_list);
    return;
}

void inputing_data_except_null(char *data, int length) /* 입력 받은 데이터에서 NULL을 제거하는 함수 */
{
    fgets(data, length, stdin); /* fgets로 지정된 길이 만큼만 입력을 받을 수 있게 한다. */
    __fpurge(stdin);            /* stdin에 있는 버퍼제거. 리눅스용 */

    *(data + strlen(data) - 1) = 0; /* 받은 문자열 맨끝의 NULL 문자 삭제. */
}

int pointing_location_of_null(char *data) /* 문자열을 카운팅하는 함수. 사용하지 않는다. */
{
    int icnt = 0;

    while(1)
    {
        /* if(buff[icnt] == '\0') */
        if(*(data + icnt) == '\n')
        {
            break;
        }
        icnt++;
    }
    return icnt;
}
void delete_book(){
	deleted_book = NULL;
	if (main_list -> next == 0){
		printf("List is one! Do you want delete list? Delete 'book.bdf'!\n");
		return;
	}
	printf("What Kind of Book do you want to delete?\n");
	char name[30];
	char author[30];
	printf("Book Name: ");
	inputing_data_except_null(name, sizeof(name));
	printf("\nBook Author: ");
	inputing_data_except_null(author, sizeof(author));
	deleted_book = delete_book_file(name, author, main_list);
	if (deleted_book != 0){
		main_list = deleted_book;
		writing_data_file(main_list);
	}
}
void Find_book() // 책이름을 받고 책을 찾는 함수
{
	Found_book = NULL;
	printf("What is name of the book?\n");
	char name[30];
	char author[30];
	printf("Book Name: ");
	inputing_data_except_null(name, sizeof(name));
	printf("\nBook Author: ");
	inputing_data_except_null(author, sizeof(author));
	Found_book = Find(name, author, main_list);
	if (Found_book != 0){
		printf("Book      : %s\n", Found_book -> book);
		printf("Author    : %15s | ", Found_book -> author);
		printf("Publisher : %15s\n", Found_book -> publisher);
		printf("Price     : %15s | ", Found_book -> price);
		printf("Year      : %15s\n", Found_book -> year);
	}
}

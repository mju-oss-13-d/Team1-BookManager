#include "header_files.h"

/* 책을 추가하는 insert 함수 */
//BOOK_NODE *insert(char *book, char *author, char *publisher, char *price, BOOK_NODE *list)
void delete_book_file(char* a, BOOK_NODE *list){
    BOOK_NODE *tmp;
    if(strcmp(a, list->book) == 0){
	tmp = list;
	list = list->next;
	free(tmp);
		
	return;
    } else {
	if(list->next != 0){
		list = list->next;
		delete_book_file(a, list);
	} else {
	printf("there's no bookfile in here.\n");
	}
    }
}
	

BOOK_NODE *insert(BOOK_NODE *book_st, BOOK_NODE *list)
{
    BOOK_NODE *current = NULL;  /* 앞장 서는 연결 선 */
    BOOK_NODE *follow = NULL;   /* 뒤 따라가는 연결 선 */
    BOOK_NODE *newnode = NULL;  /* 새로운 NODE */

    current = list;             /* current = follow = list; */
    follow = list;

    /* 새로운 노드 생성 */
    newnode = (BOOK_NODE *)malloc(sizeof(BOOK_NODE)); /* 동적할당을 받아서 새로운 NODE인 newnode를 만든다.  */
    if(newnode == NULL)                                /* 동적할당 실패시, 에러 메세지를 출력 후 종료. */
    {
        printf("Failed to allocate memory.\n");
        return list;            /* 원래 받았던 주소는 그냥 돌려준다. */
    }
    *newnode = *book_st;          /* 새로운 노드에 입력 받았던 내용을 넣는다. */

    /* 삽입 위치로 이동 */
    while((current != NULL) && strcmp(current -> book, book_st -> book) == 1) /* 처음이 아니고, 오름차순으로.  */
    {
        follow = current;       /* follow는 current의 NODE에, */
        current = current -> next; /* current는 한개 NODE 전진. */
    }
    
    /* 삽입 */
    newnode -> next = current;  /* newnode 의 next에 current를 연결. 첫 NODE일 경우 NULL이 next에 연결됨. */
    if(current == list)        /* current와 list가 같을 경우는, */
    {
        list = newnode;
    }
    else
    {
        follow -> next = newnode; /* 그 외 경우에는 앞 노드의 next에 연결 됨. */
    }

    return list;                /* 첫 번째 NODE를 가지고 있는 list를 return 한다. */
}

void *print_links(BOOK_NODE *linked_list)
{
    BOOK_NODE *temp;

    int i_cnt = 0;              /* 출력한 도서를 카운트 */
    int i_book_number = 1;      /* 출력시 책에 번호를 위한 카운트 */
    char c_cmd = 0;
    
    temp = linked_list;

    if(temp == NULL)            /* 책이 없을 경우 없다는 메세지를 띄우고 return 한다. */
    {
        printf("\nThere is no book to show in book list.\n");

        return;
    }

    printf("================= Book List =================\n");
    while('q' != c_cmd)         /* 입력으로 'q' 를 받으면 빠져나간다. */
    {
        while(1)
        {
            putchar('\n');
            printf("#%d\n", i_book_number);
            printf("Book      : %s\n", temp -> book);
            printf("Author    : %15s | ", temp -> author);
            printf("Publisher : %15s\n", temp -> publisher);
            printf("Price     : %15s | ", temp -> price);
            printf("Year      : %15s\n", temp -> year);

            /* 페이지 기능 */
            if((i_cnt == 4) || (temp -> next == NULL)) /* 더 이상 출력할 책이 없거나 네 권 단위로 출력 후, 빠져나간다. */
            {
                i_cnt = 0;      /* 다음 책들을 위해 카운트 초기화 */
                break;
            }
            
            temp = temp -> next;

            ++i_book_number;
            ++i_cnt;
        }

        /* 명령을 받을 상태 메뉴 출력 */
        printf("(p)revious, (Enter Key) for next page, (q)uit :: %d / %d > ", i_book_number, counting_links(linked_list));
        c_cmd = getchar();
    }
    __fpurge(stdin);            /* 다음 메뉴 출력에서 입력이 두번 들어가는 것을 방지한다. */
    
    return;
}

unsigned int counting_links(BOOK_NODE *books) /* linked list의 NODE 갯수를 세어서 반환한다. */
{
    int ui_counter = 0;

    while(1)
    {
        if(books == NULL)
        {
            break;
        }
        else
        {
            ui_counter = ui_counter + 1;
            books = books -> next;
        }
    }
    return ui_counter;
}

/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node
{
    int key;
    struct Node *llink;
    struct Node *rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode **h);
int freeList(listNode *h);
int insertLast(listNode *h, int key);
int deleteLast(listNode *h);
int insertFirst(listNode *h, int key);
int deleteFirst(listNode *h);
int invertList(listNode *h);

int insertNode(listNode *h, int key);
int deleteNode(listNode *h, int key);

void printList(listNode *h);

int main()
{
    char command;
    int key;
    listNode *headnode = NULL;

    do
    {
        printf("[----- [Hyaejun Mun] [2019015035] -----]\n");
        printf("----------------------------------------------------------------\n");
        printf("                  Doubly Circular Linked List                   \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'z':
        case 'Z':
            initialize(&headnode);
            break;
        case 'p':
        case 'P':
            printList(headnode);
            break;
        case 'i':
        case 'I':
            printf("Your Key = ");
            scanf("%d", &key);
            insertNode(headnode, key);
            break;
        case 'd':
        case 'D':
            printf("Your Key = ");
            scanf("%d", &key);
            deleteNode(headnode, key);
            break;
        case 'n':
        case 'N':
            printf("Your Key = ");
            scanf("%d", &key);
            insertLast(headnode, key);
            break;
        case 'e':
        case 'E':
            deleteLast(headnode);
            break;
        case 'f':
        case 'F':
            printf("Your Key = ");
            scanf("%d", &key);
            insertFirst(headnode, key);
            break;
        case 't':
        case 'T':
            deleteFirst(headnode);
            break;
        case 'r':
        case 'R':
            invertList(headnode);
            break;
        case 'q':
        case 'Q':
            freeList(headnode);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

int initialize(listNode **h)
{

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if (*h != NULL)
        freeList(*h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    *h = (listNode *)malloc(sizeof(listNode));
    (*h)->rlink = *h;
    (*h)->llink = *h;
    (*h)->key = -9999;
    return 1;
}

/* 메모리 해제 */
int freeList(listNode *h)
{
    if (h == NULL) // 선언되지 않으면 실행할 수 없다.
    {
        printf("no list.\n");
        return 0;
    }
    listNode *p = h->rlink; // 다음 노드를 가리키는 포인터.
    listNode *back = p;     // 동적 할당을 풀어줄 포인터.
    while (p != h)          // 하나씩 이동하면서 풀어준다.
    {                       // 바로 풀어주면 다음 노드로 이동할 위치 정보를 잃어버리기 때문에,
        back = p;           // 다음 노드를 가리키는 포인터가 추가로 필요하다.
        p = p->rlink;       // h를 가리키게 되면 마지막 노드가 된 것이므로 종료한다.
        free(back);
    }
    free(h); // 원소들의 할당이 모두 끝나면, h도 할당 해제해 준다.
    return 0;
}

void printList(listNode *h)
{
    int i = 0;
    listNode *p;

    printf("\n---PRINT\n");

    if (h == NULL)
    {
        printf("Nothing to print....\n");
        return;
    }

    p = h->rlink;

    while (p != NULL && p != h)
    {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->rlink;
        i++;
    }
    printf("  items = %d\n", i);

    /* print addresses */
    printf("\n---checking addresses of links\n");
    printf("-------------------------------\n");
    printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

    i = 0;
    p = h->rlink;
    while (p != NULL && p != h)
    {
        printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
        p = p->rlink;
        i++;
    }
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode *h, int key)
{
    if (h == NULL) // 선언되지 않으면 실행할 수 없다.
    {
        printf("no list.\n");
        return 0;
    }
    listNode *p = (listNode *)malloc(sizeof(listNode)); // 삽입할 노드 추가
    p->key = key;
    p->rlink = h; // 마지막이므로, h와 마지막 노드 사이에 삽입한다.
    p->llink = h->llink;
    p->llink->rlink = p; // h 노드와 마지막 노드도 p를 가리키도록 해야 한다.
    h->llink = p;
    return 1;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode *h)
{
    if (h == NULL) // 선언되지 않으면 실행할 수 없다.
    {
        printf("no list.\n");
        return 0;
    }
    if (h->rlink == h) // 리스트가 비었으면 원소를 삭제할 수 없다.
    {
        printf("List is empty.\n");
        return 0;
    }
    listNode *p = h->llink; // h->llink가 가리키는 노드가 마지막 노드이다.
                            // p의 왼쪽 노드와 오른쪽 노드가 서로를 가리키게 해 준다.
    p->rlink->llink = p->llink;
    p->llink->rlink = p->rlink;
    free(p); // 리스트의 다른 노드들의 정리가 끝났으면, 선택한 노드를 해제한다.
    return 1;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode *h, int key)
{
    if (h == NULL) // 선언되지 않으면 실행할 수 없다.
    {
        printf("no list.\n");
        return 0;
    }
    // 리스트에 삽입할 노드 생성
    listNode *p = (listNode *)malloc(sizeof(listNode));
    p->key = key;        // 노드 값 생성, 첫 번째 위치에 삽입되기 위해
    p->rlink = h->rlink; // 좌 링크는 head, 우 링크는 첫 번째 원소를 가리킴.
    p->llink = h;
    p->rlink->llink = p; // 그 후, 첫 번째 원소의 좌 링크와 head의 우 링크가
    h->rlink = p;        // 삽입할 노드를 가리키게 함.
    return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode *h)
{
    if (h == NULL) // 선언되지 않으면 실행할 수 없다.
    {
        printf("no list.\n");
        return 0;
    }
    if (h->rlink == h) // 리스트가 비었으면 원소를 삭제할 수 없다.
    {
        printf("List is empty.\n");
        return 0;
    }
    listNode *p = h->rlink; // h->rlink가 가리키는 노드가 마지막 노드이다.
                            // p의 왼쪽 노드와 오른쪽 노드가 서로를 가리키게 해 준다.
    p->llink->rlink = p->rlink;
    p->rlink->llink = p->llink;
    free(p); // 리스트의 다른 노드들의 정리가 끝났으면, 선택한 노드를 해제한다.
    return 1;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode *h)
{
    if (h == NULL) // 선언되지 않으면 실행할 수 없다.
    {
        printf("no list.\n");
        return 0;
    }
    if (h->rlink == h) // 원소가 없으면 역순배치할 수 없다.
    {
        printf("list is empty.\n");
        return 0;
    }
    if (h->rlink->rlink == h) // 원소가 하나면 역순배치해도 의미가 없다.
    {
        printf("there is only one element.");
        return 0;
    }
    listNode *p = h;           // 다음 노드를 가리키는 노드
    listNode *turn = h->llink; // 링크를 변경할 노드를 가리키는 노드.
                               // 처음 시작시, 이전 노드가 마지막 노드가 되도록 하기 위해
                               // h->llink로 초기화한다.
    listNode *back = NULL;     // 이전 노드를 가리키는 노드
    while (turn->llink != h)   // 마지막 원소까지 변경했으면 종료한다.
    {                          // 여기서, 모든 역순배치가 끝났으면 마지막 원소 변경이 끝났을 때
        back = turn;           // p->rlink가 아닌, p->llink가 h를 가리킴에 유의하자.
        turn = p;              // p의 시작값이 h이므로, p != h는 while 조건문으로 사용될 수 없다.
        p = p->rlink;          // 바로 종료되기 때문이다.
        turn->rlink = back;
        turn->llink = p;
    }
    return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode *h, int key)
{
    if (h == NULL) // 선언되지 않으면 실행할 수 없다.
    {
        printf("no list.\n");
        return 0;
    }
    // 삽입할 노드를 동적할당한다.
    listNode *p = (listNode *)malloc(sizeof(listNode));
    p->key = key;
    if (h->rlink == h) // 원소가 없으면 그냥 배치한다.
    {
        insertFirst(h, key);
        return 0;
    }
    listNode *find = h->rlink; // 리스트를 탐색할 포인터.
    while (find != h)
    {
        if (find->key > key) // 입력받은 key보다 더 큰 값이 나오면,
        {
            p->llink = find->llink; // 그 값을 find와 그 이전 노드 사이에 삽입한다.
            p->rlink = find;
            find->llink->rlink = p;
            find->llink = p;
            return 0;
        }
        find = find->rlink; // 값이 더 크지 않으면, 다음 노드로 이동한다.
    }
    insertLast(h, key); // 리스트를 다 돌아도 없으면, 마지막에 삽입한다.
    return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode *h, int key)
{
    if (h == NULL) // 선언되지 않으면 실행할 수 없다.
    {
        printf("no list.\n");
        return 0;
    }
    if (h->rlink == h) // 리스트가 비었으면 원소를 삭제할 수 없다.
    {
        printf("List is empty.\n");
        return 0;
    }
    listNode *find = h->rlink; // 리스트를 탐색할 포인터.
    while (find != h)
    {
        if (find->key == key) // 입력받은 key와 같은 노드가 나오면,
        {
            find->llink->rlink = find->rlink;
            find->rlink->llink = find->llink;
            free(find); // find 앞뒤 노드들이 서로를 가리키게 하고,
            return 0;   // 자신은 할당 해제한다.
        }
        find = find->rlink; // 값이 같지 않으면, 다음 노드로 이동한다.
    }
    printf("There is no key.\n"); // 다 돌아봐도 없으면, 실패를 출력한다.
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList
//
//그니까 링크트 리스트에 인트가 잇는데 리스트노도의 헤드를 가리키는데 리스트노드는 넥스트를 가리킨다 
///////////////////////// function prototypes ////////////////////////////////////
//정렬된 리스트일수도잇고 빈 리스트일수도 없을거같은데 널인가? 널체킹...해야된다고 헐~ 
//next null 이면 직전값을 출력하면 마지막값 
//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
//정수를 입력하게 해서 그러면 링크드리스트에 오름차순으로 들어간다
// insertSortedLL 펑션은 만약 이미 최근 링크드리스트에 존재하면 정수를 넣는것을
// 허용하지 않는다..?
// 펑션은 새 아이템이 추가된 인덱스 위치를 반환해야하한다
// 펑션이 잘 동작하지 않으면? -1 을 리턴한다
// 링크드 리스트가 잘 정돈되거나 빈 리스트라고 가정할 수 있다.
// let temp = ListNode {
// next: ll.head,
// item: item
// }
int insertSortedLL(LinkedList *ll, int item)
{	              //([Linked list], 8)
	ListNode *pre, *cur;
	
	if (ll == NULL)
			return -1;

	// 리스트에 노드가 하나도 없음
	if (ll->head == NULL){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = item;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	cur = ll->head;
	// 새로 들어온 노드가 제일 작을때
	if (cur->item > item){
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = item;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	int index = 0;

	while(cur !=NULL){
		if (cur->item == item){
			return -1;
		}
		index ++;
		if ( cur->next == NULL){
			cur->next = malloc(sizeof(ListNode));
			cur->next->item = item;
			ll->size++;
			return ll->size;
		}
		if (cur->next->item > item){
			pre = cur->next;
			cur->next = malloc(sizeof(ListNode));
			cur->next->item = item;
			cur->next->next =pre;
			ll->size++;
			return index;
		}
		cur = cur->next;


	}
	return -1;

}
// 	int idx = 0; // index
	
// 	ListNode *temp = ll->head; // 안들어갓...내가 넣어줘야대
// 	// temp->next = ll->head;//띄어쓰기 no
	
// //	템프의 아이템을 헤드에다 넣는다
// 	if (ll->head == NULL){
// 		insertNode(ll, 0 , item);
// 		return 0;
// 	} 
// 	while ( temp!= NULL){
// 		if (temp->item == item) {
// 			return -1;
// 		}
// 		else if (temp->item > item){
// 				insertNode(ll, idx, item);
// 			return idx;
// 		}
// 		temp = temp->next;
// 		idx++;
// 	}
// 	insertNode(ll, idx,item);
// 	return idx;


	
// 헤드포인트를 업데이트...
	/* add your code here */
	/*정렬된 링크드 리스트  
	링크드 리스트에 값을 넣는 함수이다
	8은 2앞에 넣는게 아니고 오름차순 위치에 들어가는거...
	8보다는 작고 앞에 수보다는 큰 부분을 찾아서 
	링크드리스트의 노드에 들어간 데이터값을 확인해서 
	입력값보다 작으면 뒤로 한칸씩 옮겨주고 입력값보다 큰 수를 만나면 거기 전에 링크드리스트에 저장
	일단은 
	 */


///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

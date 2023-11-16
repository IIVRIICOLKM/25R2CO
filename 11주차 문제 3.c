#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ELEMENTS 10

typedef struct {
	int key;
} element;

element heap[MAX_ELEMENTS];
int n = 0;

void insert_max_heap(element);
element delete_max_heap();
int search_heap(int);
void print_heap();

int main()
{
	element e;
	srand(time(NULL));

	/*히프 삽입*/
	printf("E[] = ");
	for (int i = 1; i < MAX_ELEMENTS; i++)
	{
		e.key = 1 + rand() % 20;
		insert_max_heap(e);
	}
	print_heap(MAX_ELEMENTS);
	/*히프 탐색*/
	while (1)
	{
		int x, result;
		printf("(-1 : 종료)탐색할 값을 입력하시오: ");
		scanf("%d", &x);
		if (x == -1) break;
		result = search_heap(x);

		if(result)
		    printf("처음 탐색된 히프 번호 = %d\n", result);
		else
			printf("찾는 번호가 없습니다.\n", result);
	}

	/*히프 삭제*/
	int random = 2 + rand() % 8;
	for (int i = 1; i < random; i++)
	{
		e.key = 1 + rand() % 20;
		delete_max_heap();
	}
	printf("\n삭제 히프 E[] = ");
	print_heap(MAX_ELEMENTS - random);

	return 0;
}


void insert_max_heap(element item)
{
	int i = ++n;
	while ((i != 1) && (item.key > heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}  

element delete_max_heap()
{
	int parent, child;
	element temp, max;

	max = heap[1];
	temp = heap[n--]; parent = 1; child = 2;
	while (child <= n) {
		// c = 현재 parent의 큰 자식
		if ((child < n) && (heap[child].key < heap[child + 1].key)) child++;
		if (temp.key >= heap[child].key) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return max;
}

int search_heap(int x)
{
	for (int index = 1; index <= n; index++)
		if (heap[index].key == x)
			return index;
	return 0;
}

void print_heap(int r)
{
	for (int i = 1; i < r; i++)
		printf("%d ", heap[i].key);
	printf("\n");
}
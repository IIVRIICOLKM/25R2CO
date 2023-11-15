#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAMESIZE 20                              //학생의 이름을 20자 이내로 제한
#define SIZE 100                                 //학생수를 100명으로 제한                                                                           

static int count;                                //학생수 저장 변수
char lastname[NAMESIZE];                         //이전 학생의 이름 저장(사용자가 가장 마지막으로 입력한 학생 - 중복 없을 때)

typedef struct student                           
{
	struct student* lstu;                        //노드의 좌우측 링크
	struct student* rstu;
	char name[NAMESIZE];                               
	int score, rank;                                    
}STUDENT;
/*헤드 노드*/
typedef struct h_student                         
{
	STUDENT* head;
}H_STUDENT;
/*공백 노드 생성*/
H_STUDENT* CreateStudentList()          
{
	H_STUDENT* H;
	H = malloc(sizeof(H_STUDENT));
	H->head = NULL;
	return H;
}
/*원형 정의*/
void New_Student(H_STUDENT* H, STUDENT* pre, int score, char* name);       //L139
void Delete_Student(H_STUDENT* H, char* name);       //L166
STUDENT* Search_Name(H_STUDENT* H, char* name);       //L192
void Print_Student(H_STUDENT* H);       //L206
void Set_Rank(H_STUDENT* H);       //L226

int interface()                                  //인터페이스 : 메뉴 출력 및 기능선택 -> 선택한 기능을 정숫값으로 반환
{
	printf("\n1. 입력\n");
	printf("2. 검색\n");
	printf("3. 제거\n");
	printf("4. 종료\n\n");

	int x;
	printf("사용할 기능을 입력하시오: ");
	scanf_s("%d", &x);
	getchar();

	return x;
}

int main()
{
	H_STUDENT* Hstu = CreateStudentList();             //공백 노드 생성
	STUDENT* students;                                 
	char name[NAMESIZE];                               //학생 이름
	int score;
	for (int i = 0; i < NAMESIZE; i++)                 //lastname 배열 NULL로 초기화
		lastname[i] = NULL;


	while (1)
	{
		int choice = interface();
		if (choice == 4 || count == SIZE)              //인터페이스의 4번을 선택하거나 학생 수가 100이 되면 종료
			break;

		switch (choice)                                
		{/*새로운 학생 입력*/
		case 1:
		{
			printf("이름, 성적을 입력하시오: ");
			gets_s(name, NAMESIZE);
			if (((Hstu -> head != NULL) && (Search_Name(Hstu, name) != NULL)))          //중복된 이름 존재 시 메세지 출력 후 switch문 종료
			{
				printf("\n중복된 이름 %s이 존재합니다.", name);
				printf("\n학생 수 : %d\n", count);
				break;
			}
			scanf_s("%d", &score);

			if (!count)                                      //학생 수가 0명이면(이 때 헤드 포인터는 NULL)
			{
				New_Student(Hstu, NULL, score, name);
				for (int i = 0; i < strlen(name); i++)       //else에서 파라미터로 넘기기 위한 현재 이름을 lastname 에 저장
					lastname[i] = name[i];
				Print_Student(Hstu);                         //학생 정보 출력
				printf("\n학생 수 : %d\n", count);           //현재 학생 수 출력
			}
			else
			{
				students = Search_Name(Hstu, lastname);      //이전 노드 탐색 후 반환
				New_Student(Hstu, students, score, name);    //학생 추가(students = 이전 노드)
				Set_Rank(Hstu);                              //노드들의 rank값 세팅
				Print_Student(Hstu); //(95-96)L87과 동일
				printf("\n학생 수 : %d\n", count);

				for (int i = 0; i < NAMESIZE; i++)           
					lastname[i] = NULL;
				for (int i = 0; i < NAMESIZE; i++)
					lastname[i] = name[i];                   //lastname 최신화
			}
			break;
		}
		/*학생 검색*/
		case 2:
		{
			printf("찾는 학생의 이름을 입력하시오: ");
			gets_s(name, NAMESIZE);
			STUDENT *tmp = Search_Name(Hstu, name);         //이름이 같은 노드 반환
			if (tmp != NULL)                               
				printf("이름 : %s\n성적 : %d점\n등수 : %d등\n", tmp->name, tmp->score, tmp->rank);
			else
				printf("찾는 학생이 존재하지 않습니다.\n");       //노드 존재 : 값 출력, 미존재 : 메세지 출력
			printf("\n학생 수 : %d\n", count);
			break;
		}
		/*학생 제거*/
		case 3:
		{
			printf("제거할 학생의 이름을 입력하시오: ");          
			gets_s(name, NAMESIZE);
			printf("\n%s 학생 제거중...\n", name);
			STUDENT* del = Search_Name(Hstu, name);              //특정 학생의 이름을 가진 노드 반환(L191)
			Delete_Student(Hstu, del);                           //학생 제거(L165)
			Set_Rank(Hstu);                                      //제거 후 순위 재배열(L226)
			printf("\n학생 수 : %d\n", count);
			break;
		}
		/*선택지 이외이면 위로 가기*/
		default:
			break;
		}
	}

	return 0;
}
/*학생 추가 함수*/
void New_Student(H_STUDENT* H, STUDENT *pre, int score, char*name)                       
{   //새 노드에 공간 할당
	STUDENT* New_stu;
	New_stu = malloc(sizeof(STUDENT));                    
	//데이터 삽입
	strcpy(New_stu-> name, name);                         
	New_stu->score = score;
	//헤드가 NULL일 때
	if (H->head == NULL)
	{
		New_stu->rstu = NULL;
		New_stu->lstu = NULL;
		H->head = New_stu;          //헤드 노드가 처음 추가된 학생을 가리킴
		count++;
		New_stu->rank = 1;
	}
	else
	{
		New_stu->rstu = pre->rstu;         //노드 추가 알고리즘
		pre->rstu = New_stu;
		New_stu->lstu = pre;
		if (New_stu->rstu != NULL)
			New_stu->rstu->lstu = New_stu;
		count++;
	}
}                                                                                                         
/*학생 제거 함수*/
void Delete_Student(H_STUDENT* H, STUDENT*del)
{
	if (H->head == NULL){printf("\n공간에 학생이 저장되지 않았습니다.\n"); return;}        
	else if (del == NULL){printf("\n학생을 찾을 수 없습니다.\n"); return;}

	else if (count == 1){free(del);         /*학생 수가 1명일 때*/
		H->head = NULL;                     //삭제 후 헤드포인터 NULL로 설정
		count--;}
	else if (del->rstu == NULL)             /*제거하는 학생이 마지막 노드일 때*/
	{   for (int i = 0; i < NAMESIZE; i++) lastname[i] = NULL;
		for (int i = 0; i < NAMESIZE; i++) lastname[i] = del->lstu->name[i];                  //입력 기능에 에러가 생기지 않기위해 lastname을 이전 노드의 값으로 치환
		del->lstu->rstu = del->rstu;        //del의 오른쪽 링크값 NULL로
		free(del);                          //할당 해제 후 학생 수 감소
		count--;}
	else if (del->lstu == NULL)             /*제거하는 학생이 처음 노드일 때*/
	    {del->rstu->lstu = del->lstu;       //다음 노드의 왼쪽 링크값 NULL로
		H->head = del->rstu;                //헤드포인터 변경
		free(del);
		count--;}
	else                                    /*이외의 경우 : 이중 연결 리스트 삭제 알고리즘 적용*/
	    {del->lstu->rstu = del->rstu;
		del->rstu->lstu = del->lstu;
		free(del);
		count--;}
}
/*학생 검색 함수*/
STUDENT* Search_Name(H_STUDENT* H, char* name)      
{
	STUDENT* tmp;
	tmp = H->head;
	while (tmp != NULL)
	{
		if (strcmp(tmp->name, name) == 0)
			return tmp;
		else
			tmp = tmp->rstu;
	}
	return tmp;
}                                             //tmp를 헤드포인터부터 끝까지 이동하면서 일치하는 이름 발견 시 노드 반환, 끝까지 가서 없으면 NULL값 반환                
/*학생 출력 함수*/
void Print_Student(H_STUDENT* H)              
{
	STUDENT* search;
	printf("학생 리스트 = (");

	for(int i = 1; i <= count; i++)           //8회 반복
	{
		search = H->head;                     //1회 반복 할 때 마다 search값을 헤드포인터로 설정
		while (1)
		{
			if (i == search->rank)            //학생 출력 시 등수 순으로 출력
				printf("%s : %d점, %d등 ", search->name, search->score, search->rank);
			search = search->rstu;
			if (search == NULL)               //탐색 종료시 while문 종료
				break;
		}
	}
	printf(")\n");
}                                             //출력시 랭크를 세팅하고 출력하기 때문에 등수 순서로 출력
/*등수 세팅 함수*/
void Set_Rank(H_STUDENT* H)
{
	STUDENT* tmp, * search;
	tmp = H->head; 

	for (; tmp != NULL; tmp = tmp->rstu)
	{
		tmp->rank = 1;                                  //현재 비교하는 대상의 rank값 1로 초기화
		for (search = H->head; search != NULL; search = search->rstu)
		{
			if (tmp->score < search->score)             //상대적인 점수가 낮을 때 rank값 증가
				tmp->rank++;
		}
	}
}
#include <stdio.h>
#include <string.h>
#define SIZE 100                                 //학생수를 100명으로 제한                                                                           
#define FNAMESIZE 30                             //사용자가 입력할 파일 이름의 크기 30으로 제한

typedef struct student                           //구조체 : 학생들의 정보 저장
{
	char name[20];                               //학생 이름
	int number, grade;                           //학번, 학년
	int Mid, Final, Hw, Total;                   //중간, 기말, 과제, 총점

}STUDENT;

int end_num = 9;                                 //구조체 배열의 가장 마지막 인덱스 저장 변수(초깃값 : 9)
char filename[FNAMESIZE] = { NULL };             //사용자로부터 입력받을 파일 이름(크기 : 30)

void print_data(STUDENT, FILE*);                       //정의 : Line 83, 단일 학생 정보 출력
void initialize(STUDENT);                              //정의 : Line 93, 구조체 배열의 특정 인덱스 초기화(학생 초기화)
void Exchange(int*, int*);                             //정의 : Line 105, 버블 정렬 시, 학생 정보 위치 교환
void push_data(STUDENT*, int);                         //정의 : Line 112, 학생 삭제 후 인덱스 앞당기기

void search_name(STUDENT*);                            //정의 : Line 132, 이름 탐색
void New_student(STUDENT*);                            //정의 : Line 154, 학생 추가(추가하는 학생의 인덱스는 기존 마지막 인덱스 + 1)
void Delete_student(STUDENT*);                         //정의 : Line 187, 학생 삭제
void sum_sorting_print(STUDENT*);                      //정의 : Line 213, 정렬 후 출력
void get_average(STUDENT*);                            //정의 : Line 255, 평균 점수 출력

void (*numbered_function[5])(STUDENT*) = { search_name, New_student, Delete_student, sum_sorting_print, get_average };               //특정 기능을 가진 함수 포인터 초기화(L22 ~ L26)


int interface()                                  //인터페이스 : 메뉴 출력 및 기능선택 -> 선택한 기능을 정숫값으로 반환
{
	printf("현재 학생 수 : %d\n\n", end_num + 1);
	printf("1. 이름 검색\n");
	printf("2. 학생 추가\n");
	printf("3. 학생 삭제\n");
	printf("4. 성적순 정렬\n");
	printf("5. 평균 구하기\n");
	printf("6. 종료\n");

	int x;
	printf("사용할 기능을 입력하시오: ");
	scanf_s("%d", &x);
	getchar();

	return x;
}

int main()
{
	
	STUDENT Dongguk[SIZE] = {                          //학생 100명의 정보를 담을 구조체 배열(10명 선입력)
		{"Tom", 1, 3, 60, 55, 70}, 
		{"Jerry", 2, 4, 50, 65, 75},
		{"Jack", 3, 2, 75, 70, 90},
		{"Camile", 4, 1, 70, 45, 55},
		{"Tifanny", 5, 2, 100, 90, 100},
		{"Andy", 6, 4, 45, 30, 50},
		{"Lilly", 7, 1, 65, 80, 75},
		{"Ryu", 8, 2, 30, 25, 35},
		{"Jeff", 9, 1, 90, 75, 80},
		{"Tom", 10, 3, 95, 100, 100}
	};

	for (int i = 10; i < SIZE; i++)                   //선입력 학생 제외 정보 초기화
		initialize(Dongguk[i]);

	while (1)
	{
		int choice = interface();
		if (choice == 6)
			break;
		numbered_function[choice - 1](Dongguk);       //함수 포인터 호출
	}

	return 0;
}


void print_data(STUDENT data, FILE* fp)               //단일 학생 정보 출력(총점은 정렬 후 출력)
{
	fprintf(fp, "\n이름 : %s\n", data.name);
	fprintf(fp, "학번 : %d\n", data.number);
	fprintf(fp, "학년 : %d\n", data.grade);
	fprintf(fp, "중간점수 : %d\n", data.Mid);
	fprintf(fp, "기말점수 : %d\n", data.Final);
	fprintf(fp, "과제점수 : %d\n", data.Hw);
}

void initialize(STUDENT data)                         //단일 학생 정보 초기화
{
	for (int i = 0; i < 20; i++)
		data.name[i] = NULL;
	data.number = -1;
	data.grade = -1;
	data.Mid = -1;
	data.Final = -1;
	data.Hw = -1;
	data.Total = -1;
}

void Exchange(int* x, int* y)                         //변수 교환(버블 정렬에 활용)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

void push_data(STUDENT*data, int d_stu)               //데이터 한칸 앞당기기(범위 : 삭제한 인덱스 +1 ~ 마지막 인덱스)
{
	for (int i = d_stu + 1; i <= end_num; i++)
	{
		strcpy(data[i - 1].name, data[i].name);
		data[i - 1].number = data[i].number;
		data[i - 1].grade = data[i].grade;
		data[i - 1].Mid = data[i].Mid;
		data[i - 1].Final = data[i].Final;
		data[i - 1].Hw = data[i].Hw;

		if (i == end_num)                             //기존 마지막 인덱스 탐색 -> 기존 마지막 인덱스 데이터 초기화 후 end_num 감소 
		{
			initialize(data[i]);
			end_num -= 1;
		}
	}
}                                                     //함수 실행 결과 : 데이터가 있는 인덱스 연속, end_num 1 감소


void search_name(STUDENT* data)                       //검색할 학생 이름, 파일명 입력 -> end_num까지 탐색(이름 있으면 데이터 출력) -> 파일 닫기
{                                                              
	char s_name[20]; int count = 0;
	printf("\n학생의 이름을 입력하시오: ");
	gets_s(s_name, 20);
	printf("\n파일명을 입력하시오: ");
	gets_s(filename, FNAMESIZE);

	FILE* fp = fopen(filename, "a");                  //파일 열기(파일 존재 시 a모드, 없을 시 w모드)
	if(fp == NULL)
		fp = fopen(filename, "w");

	for (int i = 0; i <= end_num; i++)                //end_num까지 탐색(이름 있으면 데이터 출력, count값 증가)
	{
		if (!strcmp(data[i].name, s_name))
		{
			print_data(data[i], fp);
			count++;
		}
	}
	if (!count)                                   //count가 0이면 목록에 없음(메세지 출력)
		printf("%s학생은 목록에 없습니다.", s_name);
	fclose(fp);
}                                                     //함수 실행 결과 : 이름 존재 - 학생의 정보 파일에 출력, 이름 미존재 - 메세지 출력

void New_student(STUDENT* data)                       //학생 정보 입력, 중복 학번 존재 시 입력중인 데이터 초기화 후 end_num 감소 후 함수 종료(Line 170)
{
	end_num += 1;
	printf("이름: ");
	gets_s(data[end_num].name, 20);

	printf("학번: ");
	scanf_s("%d", &data[end_num].number);

	for (int i = 0; i < end_num; i++)
	{
		if (data[i].number == data[end_num].number)
		{
			printf("중복되는 학번이 존재합니다.\n");
			initialize(data[end_num]);
			end_num -= 1;
			return;
		}
	}

	printf("학년: ");
	scanf_s("%d", &data[end_num].grade);
	printf("중간 점수: ");
	scanf_s("%d", &data[end_num].Mid);
	printf("기말 점수: ");
	scanf_s("%d", &data[end_num].Final);
	printf("과제 점수: ");
	scanf_s("%d", &data[end_num].Hw);
}                                                     //함수 실행 결과 : 기존 마지막 인덱스 다음에 학생 추가, 학번 겹치면 메세지 출력 후 함수 종료.                                                       

void Delete_student(STUDENT* data)                      //학생 정보 삭제 
{
	int stu_number, deleted_student = -1;
	printf("\n(-1 입력불가)삭제할 학생의 학번을 입력하시오: ");
	scanf_s("%d", &stu_number);
	getchar();

	for (int i = 0; i <= end_num; i++)                  //탐색 인덱스(0 ~ end_num)
	{
		if (stu_number == data[i].number)               //입력한 학번과 동일 인덱스 발견 시 초기화
		{
			initialize(data[i]);
			deleted_student = i;    
		}
	}
	if (deleted_student != -1)
	{
		if (deleted_student == end_num)                 //마지막 인덱스 학생을 지우면 마지막 인덱스만 감소
			end_num -= 1;
		else
			push_data(data, deleted_student);           //push_data(L109) 실행
	}
	else
		printf("찾는 학생이 없습니다.\n");
}

void sum_sorting_print(STUDENT* data)                   //파일명 입력 -> 총점 계산 -> 데이터 이동(버블 정렬) -> 성적순으로 파일에 데이터 출력
{
	printf("\n파일명을 입력하시오: ");
	gets_s(filename, FNAMESIZE);

	for (int i = 0; i <= end_num; i++)
		data[i].Total = data[i].Mid + data[i].Final + data[i].Hw;

	for (int i = 0; i < end_num; i++)
	{
		for (int j = i + 1; j <= end_num; j++)
		{
			char tmp[20] = { NULL };
			if (data[i].Total < data[j].Total)
			{
				strcpy(tmp, data[i].name);
				strcpy(data[i].name, data[j].name);
				strcpy(data[j].name, tmp);

				Exchange(&data[i].number, &data[j].number);
				Exchange(&data[i].grade, &data[j].grade);
				Exchange(&data[i].Mid, &data[j].Mid);
				Exchange(&data[i].Final, &data[j].Final);
				Exchange(&data[i].Hw, &data[j].Hw);
				Exchange(&data[i].Total, &data[j].Total);
			}
		}
	}

	FILE* fp = fopen(filename, "a");
	if (fp == NULL)
		fp = fopen(filename, "w");

	for (int i = 0; i <= end_num; i++)
	{
		fprintf(fp, "%d등", i + 1);
		print_data(data[i], fp);
		fprintf(fp, "총점 : %d\n", data[i].Total);
	}
	fclose(fp);
}                                                       //함수 실행 결과 : 성적순으로 파일에 데이터 출력                                                           

void get_average(STUDENT* data)                         //파일명 입력 -> 파일 오픈 -> 중간, 기말, 과제점수 end_num까지 합산 -> 각 합계를 count값으로 나눈 후 출력
{
	printf("\n파일명을 입력하시오: ");
	gets_s(filename, FNAMESIZE);

	FILE* fp = fopen(filename, "a");
	if (fp == NULL)
		fp = fopen(filename, "w");

	double count = 0, sum_Mid = 0, sum_Final = 0, sum_Hw = 0;
	for (int i = 0; i <= end_num; i++)
	{
		sum_Mid += data[i].Mid;
		sum_Final += data[i].Final;
		sum_Hw += data[i].Hw;
		count++;
	}
	fprintf(fp, "중간 평균 = %lf\n기말 평균 = %lf\n과제 평균 = %lf\n", sum_Mid / count, sum_Final / count, sum_Hw / count);
	fclose(fp);
}                                                       //함수 실행 결과 : 성적순으로 파일에 데이터 출력  
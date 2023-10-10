#include <stdio.h>
#include <math.h>

typedef struct Point                                           //점의 좌표 구조체(멤버 : x좌표, y좌표)
{
	double x, y;
}POINT;

typedef struct Circle                                          //원 구조체(멤버 : 원의 중점, 반지름)
{
	POINT medium;
	double radius;
}CIRCLE;

double get_distance(CIRCLE s, POINT m)                         //원의 중점과 점 사이의 거리를 구하는 함수(매개변수 : 원 구조체 s, 점 구조체 m)
{
	return sqrt(pow(s.medium.x - m.x, 2) + pow(s.medium.y - m.y, 2));
}

int get_locrela(CIRCLE s, POINT m)                             //원과 점의 위치관계를 판단하는 함수(매개변수 : 원 구조체 s, 점 구조체 m)
{
	double distance = get_distance(s, m);
	if (distance > s.radius)                                   //점이 원 밖에있음
		return 1;
	else if (distance == s.radius)                             //점이 원 위에있음
		return 0;
	else                                                       //점이 원 안에 있음
		return -1; 

}

int main()
{
	CIRCLE Test;
	POINT p;

	printf("원의 정보를 입력하시오(반지름, 중점(x y)): ");
	scanf_s("%lf %lf %lf", &Test.radius, &Test.medium.x, &Test.medium.y);

	printf("사용자가 선택할 점의 좌표를 입력하시오(x y): ");
	scanf_s("%lf %lf", &p.x, &p.y);

	int result = get_locrela(Test, p);                                            //원과 점의 위치관계를 구하는 함수를 호출 후

	if (result == 1)                                                              //조건에 따라 정수값을 반환받고 값에따라 결과 출력
		printf("\n점은 원 밖에 있습니다.");
	else if (result == 0)
		printf("\n점은 원 위에 있습니다.");
	if (result == -1)
		printf("\n점은 원 안에 있습니다.");

	return 0;
}
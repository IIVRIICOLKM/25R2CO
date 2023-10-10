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

double get_point_distance(POINT m, POINT n)                    //점과 점 사이의 거리를 구하는 함수(매개변수 : 두 점 구조체)
{
	return sqrt(pow(m.x - n.x, 2) + pow(m.y - n.y, 2));        
}

int get_circle_locrela(CIRCLE s, CIRCLE t)                     //원과 원의 위치관계를 구하는 함수(매개변수 : 두 원 구조체)
{
	double rad, radprime, sum, sub, distance = get_point_distance(s.medium, t.medium);

	if (s.radius > t.radius)                                   //원 s의 반지름이 t의 반지름보다 크면
	{
		rad = s.radius;                                        //더 큰 원의 반지름은 rad 변수에
		radprime = t.radius;                                   //더 작은 원의 반지름은 radprime 변수에 저장
	}
	else                                                       //두 원의 반지름이 같거나 반대의 경우에는
	{
		rad = t.radius;                                        
		radprime = s.radius;
	}                                                          //줄 24 와 반대의 경우 적용
	sum = rad + radprime;
	sub = rad - radprime;

	if (distance > sum)
		return 1;                                    //만나지 않는 원
	else if (distance == sum)                    
		return 2;                                    //외접원
	else if (distance < sum)
	{
		if (distance > sub)                          
			return 3;                                //두 점 만남
		else if (distance == sub)
			return 4;                                //내접원
		else
			return 5;                                //포함관계, 동일한 원
	}
}


int main()
{
	CIRCLE C1, C2;

	printf("원 1의 정보를 입력하시오(반지름, 중점(x y)): ");
	scanf_s("%lf %lf %lf", &C1.radius, &C1.medium.x, &C1.medium.y);

	printf("원 2의 정보를 입력하시오(반지름, 중점(x y)): ");
	scanf_s("%lf %lf %lf", &C2.radius, &C2.medium.x, &C2.medium.y);

	int result = get_circle_locrela(C1, C2);                                            //원의 위치관계를 구하는 함수를 호출 후

	if (result == 1)                                                                    //조건에 따라 정수값을 반환받고 값에따라 결과 출력
		printf("\n두 원은 만나지 않습니다.");
	else if (result == 2)
		printf("\n두 원은 외접합니다.");
	else if (result == 3)
		printf("\n두 원은 두 점에서 만납니다.");
	else if (result == 4)
		printf("\n두 원은 내접합니다.");
	else if (result == 5)
		printf("\n두 원은 한 원이 다른 원을 포함하는 관계입니다.");

	return 0;
}
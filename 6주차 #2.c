#include <stdio.h>

int main(void)
{
	int A[2][3];                                               // 배열 A(2 x 3)
	int B[3][4];                                               // 배열 B(3 x 4)

	int Arraymult[2][4];                                       // 배열 Arraymult(2x4)

	printf("배열 A를 입력하시오(요소 : 6개) : ");
	for (int i = 0; i < 2; i++)            
	{
		for (int j = 0; j < 3; j++)
			scanf_s("%d", &A[i][j]);                           // 사용자로부터 배열 A 입력
	}                                       
	printf("\n배열 B를 입력하시오(요소 : 12개) : ");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
			scanf_s("%d", &B[i][j]);                           // 사용자로부터 배열 B 입력
	}

	int* arraypoint = Arraymult;                               // int형 포인터 arraypoint 형성 후 배열의 주소 대입
	
	for (int i = 0; i < 2; i++)                                // ~34번째 줄까지 배열의 곱 계산 후 배열 Arraymult에 저장
	{
		for (int j = 0; j < 4; j++)
		{
			int sum = 0;                                       // 합계를 저장할 sum 변수 생성
			for (int k = 0; k < 3; k++)                        // 배열곱의 한 요소를 결정
				sum += A[i][k] * B[k][j];                      
			*arraypoint++ = sum;                               // 한 사이클이 완료되면 arraypoint가 현재 가리키는 곳에 sum을 저장하고 다음 주소로 이동
		}
	}

	printf("\nA[]\n");

	for (int i = 0; i < 2; i++)                                //배열 A 출력
	{
		for (int j = 0; j < 3; j++)
			printf("%3d", A[i][j]);
		printf("\n");
	}

	printf("\nB[]\n");

	for (int i = 0; i < 3; i++)                                //배열 B 출력
	{
		for (int j = 0; j < 4; j++)
			printf("%3d", B[i][j]);
		printf("\n");
	}

	printf("\nA[] * B[]\n");                                   

	for (int i = 0; i < 2; i++)                                //배열곱 A * B 출력
	{
		for (int j = 0; j < 4; j++)
			printf("%3d", Arraymult[i][j]);
		printf("\n");
	}


	return 0;
}
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
구현해야 할 퀵 정렬 알고리즘: - 크기가 n인 배열을 동적 할당하여, 입력된 양의 정수 저장(입력 정수는 중복 가능). - 기준값(pivot)을 정할 때, 다음 방법을 이용한다:
(1) 부리스트의 수들 중 1개의 위치를 무작위로 선택(즉, 입력배열의 l과 r 사이의 1개
위치를 랜덤하게 선택)하여 pivot의 위치로 정한다. (2) 아래 힌트처럼 pivot의 위치를 정하는 findPivot 함수를 별도 작성해서 이 함수의
반환값을 inPlacePartition 함수가 사용하는 방식을 추천한다. - inPlacePartition의 반환값은 두 인덱스 (a, b)로, 그 의미는 분할 결과, 배열의 l번째 수부터
a – 1번째 수는 pivot보다 작은 값을, 배열의 a번째부터 b번째 수는 pivot과 같은 값을, b
+ 1번째부터 r번째 수는 pivot보다 큰 값을 가진다는 것이다(즉, 이후 호출되는 재귀함수는
l부터 a – 1까지 부배열에 대해서와 b + 1부터 r까지의 부배열에 대해서 다루고, pivot과
같은 값들인 a부터 b번째 값들은 재귀에서 제외된다).


*/
//문제 2 : 제자리 퀵 정렬

int findPivot(int* L, int l, int r) {//피벗 설정
    int random1, random2, random3;

    if (r - l <= 1) {
        return l;
    }

    //난수 생성
    srand((unsigned)time(NULL));

    random1 = (rand() % (r - l)) + l;
    random2 = (rand() % (r - l)) + l;
    random3 = (rand() % (r - l)) + l;

    if ((L[random1] >= L[random2] && L[random1] <= L[random3]) || (L[random1] <= L[random2] && L[random1] >= L[random3])) {
        return random1;//random1 반환
    }

    else if (((L[random2] >= L[random1]) && (L[random2] <= L[random3])) || ((L[random2] <= L[random1]) && (L[random2] >= L[random3]))) {
        return random2;//random2 반환
    }

    else {
        return random3;//random3 반환
    }
}

int inPlacePartition(int* L, int l, int r, int k) {
    int tmp;
    int i = l, j = r - 1;//i에 l값을 j에 r-1값을 저장
    int p = L[k];

    //피벗값과 r번째 값 교환
    tmp = L[k];
    L[k] = L[r];
    L[r] = tmp;

    while (i <= j) {//i가 j보다 작거나 같을 동안
        while (i <= j && L[i] < p) {//i번째 값이 피벗값보다 작을 동안
            i = i + 1;//i++
        }

        while (i <= j && L[j] >= p) {//j번째 값이 피벗값보다 클 동안
            j = j - 1;//j--
        }

        if (i < j) {//i가 j보다 작다면
            tmp = L[i];//i번째 값과 j번째 값 교환
            L[i] = L[j];
            L[j] = tmp;
        }
    }

    tmp = L[i];//i번째 값과 r번째 값 교환
    L[i] = L[r];
    L[r] = tmp;
    j = r;

    return i;//i 반환
}

void inPlaceQuickSort(int* L, int l, int r) {//제자리 퀵 정렬
    int k;
    int a, b, c;

    if (l >= r) {//l이 r보다 큰 경우 함수 종료
        return;
    }

    k = findPivot(L, l, r);//k가 피벗
    a = b = inPlacePartition(L, l, r, k);//inPlaePartition의 반환값이 두 인덱스 a, b에 저장
    c = a;

    inPlaceQuickSort(L, l, c - 1);//1부터 c-1까지는 피벗보다 작음
    inPlaceQuickSort(L, b + 1, r);//b+1부터 r까지는 피벗보다 큼
}

void printArray(int* L, int n) {//정렬된 배열 출력
    for (int i = 0; i < n; i++) {
        printf(" %d", L[i]);
    }
    printf("\n");
}

void main() {
    int* L, n;

    scanf("%d", &n);//배열 크기 입력받기

    L = (int*)malloc(sizeof(int) * n);//크기가 n인 배열 동적할당

    for (int i = 0; i < n; i++) {
        scanf("%d", &L[i]);//n개의 정수 입력받아 배열 L에 저장
    }

    inPlaceQuickSort(L, 0, n - 1);//제자리 퀵 정렬
    printArray(L, n);//정렬된 리스트 출력
    free(L);//동적할당된 배열 L 메모리 해제
}

#include "quickSortArray.h"
#include "resetDataset.h"

void quickSortArray(int data[], int size)
{
    rQuickSortArray(data, 0, size - 1);
}

void rQuickSortArray(int data[], int start, int end)
{
    int pivot;
    if (start <= end)
    {                                //재귀 종료조건
    
    pivot = start + rand() % (end - start + 1); //알고리즘에 의해 선택. random의 경우 pivot = start + rand()%(end - start + 1);
   // for (int i = start; i <= end; i++)
        //printf("%d", data[i]);
    
    pivot = partitionArray(data, start, end, pivot);
    //구간이 나뉜 다음 새로운 pivot을 반환받아 구간을 나눌 수 있게 된다.
    rQuickSortArray(data, start, pivot - 1);
    rQuickSortArray(data, pivot + 1, end); // GT

    }
}

int partitionArray(int data[], int l, int r, int k) //정렬 후 새로운 피봇의 인덱스 반환
{

    // l 부터 r까지 탐색하면서 k보다 작은 건 왼쪽 , 큰 건 오른쪽
    // k를 맨 왼쪽에 놓고
    //더 작은게 있으면 미루면서 추가 -> X

    // 3 4 7 5 1 6
    // pivot  = 4
    // 4 3 7 5 1 6  pi = 0
    //    pl   pr        ->swap -> 한칸 씩 전진
    // 4 3 1 5 7 6
    //      pl = pr       ->done (pl >= pr)
    // 4  | 3 1  |  5 7 6    -> 3 1 '4' 5 7 6   //미루는 일이 없게 하려고 함....
    // LT자리의 맨 오른쪽과 자리를 교환해서 pivot이 LT 맨 마지막에 위치하도록 한디(시간 단축)
    // 1 3 4 5 7 6   => 결과.
    // pl-1 을 반환!!

    int pivot = data[k];
    int temp;

    //시작: pivot을 맨 왼쪽에 위치.
    temp = data[l];
    data[l] = data[k];
    data[k] = temp;

    int pl;
    int pr;

    pl = l + 1;
    pr = r;

    while (pl <= pr)
    {
        while (data[pl] <= pivot && pl <= r) // 나중 조건을 잊지 않도록 조심해야 한다!!
            pl++;
        while (data[pr] >= pivot && pr >= l) // 나중 조건!
            pr--;
        if (pl <= pr)
        {
        temp = data[pl];
        data[pl] = data[pr];
        data[pr] = temp;
        }
    }

    data[l] = data[pr];
    data[pr] = pivot;
    return pr;

}

//피봇의 선택 -> 구글에 검색.. (정교할 수록 좋으나 시간이 많이 듬.)
// random pivot 3개 중에서 중간값 선택하기
//

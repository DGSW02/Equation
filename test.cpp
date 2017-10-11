#include <stdio.h>
#include <stdlib.h>

int *find_yak(int n); //약수 찾기
int jegup(int a, int n); // 제곱
int find_hae(int *a, int b, int c, int n) // 해 찾기
void print_hae(int a, int b); // 해 출력

int main()
{
    int *a = NULL; //다차항 배열
    int *l, *m; //최고차항의 약수, 상수항의 약수
    int b, c;
    int i, j, k;
    int n;
    bool e;
    printf("최고차항 입력 : ");
    scanf("%d", &n);
    a = (int*)malloc(sizeof(int)*n+2);
    i=0;
    while(i <= n)
    {
        if(i != n)
            printf("%d차항 입력 : ", n-i);
        else
            printf("상수항 입력 : ");
        scanf("%d", &a[i]);
        i++;
    }
    a[n+1] = NULL;
    while(1)
    {
        if(a[0] == 0)
        {
            for(i=0; i<n+1; i++)
            {
                a[i] = a[i+1];
            }
            printf("%d\n", a[n]);
            printf("%d차항인데 왜 최고차항이 0이냐! 미쳤냐!\n%d차항으로 계산하겠다!\n", n, n-1);
            n--;
            continue;
        }
        if(a[n] == 0)
        {
            print_hae(a[n], 1); // a[n] = 0
            a[n] = NULL;
            n--;
            continue;
        }
        if(n > 0)
        {
            l = find_yak(a[0]);
            m = find_yak(a[n]);
            for(i=0; l[i] != -1; i++)
            {
                for(j=0; m[j] != -1; j++)
                {
                    if(!find_hae(a, m[j], l[i], n))
                    {
                        print_hae(m[j], l[i]);
                    }
                    if(!find_hae(a, -m[j], l[i], n))
                    {
                        print_hae(-m[j], l[i]);
                    }
                }
            }
            free(m);
            free(l);
            free(a);
            return 0;
        }
    }
    return 0;
}




int *find_yak(int n) //약수 찾기
{
    if(n < 0)
        n *= -1;
    int *a = (int*)malloc(sizeof(int));
    int i, j=0;
    for(i=1; i*i<n; i++)
    {
        if(n%i == 0)
        {
            a = (int*)realloc(a, sizeof(int)*2);
            a[j++] = i;
            a[j++] = n/i;
        }
    }
    if(i*i == n)
    {
        a = (int*)realloc(a, sizeof(int));
        a[j++] = i;
    }
    a[j] = -1;
    return a;
}

int jegup(int a, int n) // 제곱
{
    if(n == 0)
        return 1;
    int i;
    for(i=0; i<n-1; i++)
    {
        a *= a;
    }
    return a;
}

int find_hae(int *a, int b, int c, int n) // 해 찾기
{
    //*a = 다차방정식
    //b = 최고차항의 약수
    //c = 상수항의 약수
    int i;
    int sum = 0;
    for(i=0; a[i] != NULL; i++)
    {
        sum += jegup(b, n-i) * a[i] * jegup(c, i);
    }
    return sum;
}

void print_hae(int a, int b)
{
    if(b == 1)
    {
        printf("방정식의 해 : %d\n", a);
    }
    else
        printf("방정식의 해 : %d / %d\n", a, b);
}

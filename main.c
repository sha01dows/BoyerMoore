#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define len 100
//tìm P trong t
int nhap(char a[])
{
    int i=0;
    char c;
    while(c!='\n')
    {
        scanf("%c", &c);
        a[i]=c;
        i++;
    }
    return i;
}

void inMang(char a[], int n)
{
    printf("\n");
    for(int i=0; i<n; i++)
    {
        printf("%c", a[i]);
    }
}
void makeBC(char p[], int last[], int n)
{
    for(int i=0; i<256; i++)
    {
        last[i]=-1;
    }
    for(int i=0; i<n; i++)
    {
        last[p[i]]=i;
    }
}
void makeF(int f[], int s[], char p[], int n)
{
    for(int i=0; i<n; i++)
    {
        s[i]=0;
    }
    int i=n, j=n+1;
    f[i]=j;
    while(i > 0)
    {

        while(j <= n && p[i-1] != p[j-1])
        {

            if(s[j] == 0)
                s[j] = j-i;
            j = f[j];
        }
        i--;
        j--;
        f[i] = j;
    }
}
int max(int a, int b)
{
    int max=(a>b)?a:b;
    return max;
}
void makeS(int f[], int s[], char p[], int n)
{
    int j = f[0];

    for(int i = 0; i <= n; i++)
    {

        if(s[i] == 0)
            s[i] = j;

        if(i == j)
            j = f[j];
    }

}
void Boyer_Moore(char t[], char p[], int m, int n)
{
    int bc[256]; //array bad character
    int f[m+1]; //F function preprocess contained the starting
    //position of the widest border of the suffix
    //of the pattern beginning at position i.
    int s[m+1]; //Mảng s này người ta nói là lưu khoảng cách dịch chuyển
    //lớn nhất có thể.

    //make preprocess
    makeBC(p,bc, n);
    makeF(f,s,p,n);
    makeS(f,s,p, n);

    //search
    int i = 0,j;

    while(i <= m-n)
    {

        j = n-1;
        while(j >= 0 && f[j] == t[i+j])
            j--;

        if(j < 0)
        {

            printf( "Found pattern at index: %d", i);
            i += s[0];
        }
        else
            i += max(s[j+1], j - bc[t[i+j]]);
    }

}

int main()
{
    char t[len], p[len];
   // int f[len], s[len], bc[255];
    fgets(t, len, stdin);
    fflush(stdin);
    fgets(p, len, stdin);
    int m=strlen(t);
    int n=strlen(p);
    Boyer_Moore(t, p, m, n);
    return 0;
}

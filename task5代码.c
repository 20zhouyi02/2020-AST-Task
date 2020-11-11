#include<stdio.h>
#define N 5

struct Struct{
    int id;
    double grades;
};

struct Struct sort(struct Struct* sn,int n);

void main()
{
    struct Struct student[N];
    int i;

    for(i=0;i<N;i++)
    {
        printf("请输入学号：\n");
        scanf("%d",&student[i].id);
        printf("请输入成绩：\n");
        scanf("%lf",&student[i].grades);
    }
    sort(student,N);
}

struct Struct sort(struct Struct* student,int n)
{
    struct Struct t;
    int a,b,c;
    for(a=0;a<n-1;a++)
    {
        for(b=a+1;b<n;b++)
        {
            if(student[a].grades<student[b].grades)
            {
                t=student[a];
                student[a]=student[b];
                student[b]=t;
            }
        }
    }
    for(c=0;c<n;c++)
    {
        printf("%d  %lf\n",student[c].id,student[c].grades);
    }
};


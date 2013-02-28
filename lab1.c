#include<stdio.h>
#include<conio.h>
#include<malloc.h>
// VARIANT 5
typedef enum {JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC,NONE} month;
char MONTH[13][5]={"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC","NONE"};
struct date
{
    int d;
    month m;
    int y;
};
struct firm
{
    char name[30];
    char tax[7];
    struct date last_date;
    struct date act_date;
}   arr[50];
int mystrcmp(char *p,char *q)
{
    int i=0,ind=0;
    while(p[i] && q[i])
    {
        if (p[i]==q[i]) ind=1;
        else ind=0;
        if ((!p[i+1] && q[i+1]) || (p[i+1] && !q[i+1])) ind = 0;
        i++;
    }
    return ind;
}
void mystrcpy(char *p,char *q)
{
    int i=0;
    while(q[i])
    {
        p[i]=q[i];
        i++;
    }
}
void char_to_enum1(char *p,int i)
{

    if     ( mystrcmp(p, "jan") ) {arr[i].last_date.m=JAN;}
    else if( mystrcmp(p, "feb") ) {arr[i].last_date.m=FEB;}
    else if( mystrcmp(p, "mar") ) {arr[i].last_date.m=MAR;}
    else if( mystrcmp(p, "apr") ) {arr[i].last_date.m=APR;}
    else if( mystrcmp(p, "may") ) {arr[i].last_date.m=MAY;}
    else if( mystrcmp(p, "jun") ) {arr[i].last_date.m=JUN;}
    else if( mystrcmp(p, "jul") ) {arr[i].last_date.m=JUL;}
    else if( mystrcmp(p, "aug") ) {arr[i].last_date.m=AUG;}
    else if( mystrcmp(p, "sep") ) {arr[i].last_date.m=SEP;}
    else if( mystrcmp(p, "okt") ) {arr[i].last_date.m=OCT;}
    else if( mystrcmp(p, "nov") ) {arr[i].last_date.m=NOV;}
    else if( mystrcmp(p, "dec") ) {arr[i].last_date.m=DEC;}
    else if( mystrcmp(p, "0"  ) ) {arr[i].last_date.m=NONE;}
}
void char_to_enum2(char *p,int i)
{

    if     ( mystrcmp(p, "jan") ) {arr[i].act_date.m=JAN;}
    else if( mystrcmp(p, "feb") ) {arr[i].act_date.m=FEB;}
    else if( mystrcmp(p, "mar") ) {arr[i].act_date.m=MAR;}
    else if( mystrcmp(p, "apr") ) {arr[i].act_date.m=APR;}
    else if( mystrcmp(p, "may") ) {arr[i].act_date.m=MAY;}
    else if( mystrcmp(p, "jun") ) {arr[i].act_date.m=JUN;}
    else if( mystrcmp(p, "jul") ) {arr[i].act_date.m=JUL;}
    else if( mystrcmp(p, "aug") ) {arr[i].act_date.m=AUG;}
    else if( mystrcmp(p, "sep") ) {arr[i].act_date.m=SEP;}
    else if( mystrcmp(p, "okt") ) {arr[i].act_date.m=OCT;}
    else if( mystrcmp(p, "nov") ) {arr[i].act_date.m=NOV;}
    else if( mystrcmp(p, "dec") ) {arr[i].act_date.m=DEC;}
    else if( mystrcmp(p, "0"  ) ) {arr[i].act_date.m=NONE;}
}
int myatoi(char q[])                   // в функцию передается указатель
{
    int n,i=0,znak;
    while(*(q+i)==' ') i++;
    if (!*(q+i)) return 0;                                     // в строке одни пробелы
    znak=(*(q+i)=='-')? -1: 1;
    if (*(q+i)=='+' || *(q+i)=='-') i++;               // пропуск позиции знака
    for(n=0; *(q+i)>'0' && *(q+i)<='9'; i++)  // выбор цифр числа из строки
    n=10*n+(*(q+i)-'0');
    return znak*n;                                               // возврат signed int
}
int debt(int i)
{
    if(arr[i].act_date.y>arr[i].last_date.y) return 1;
    else if(arr[i].act_date.y<arr[i].last_date.y) return 0;
    if(arr[i].act_date.m>arr[i].last_date.m) return 1;
    else if(arr[i].act_date.m<arr[i].last_date.m) return 0;
    if(arr[i].act_date.d>arr[i].last_date.d) return 1;
    else if(arr[i].act_date.d<arr[i].last_date.d) return 0;
    return 0;
}
void set_name()
{
    int i;
    char *p;
    for(i = 0; i < 50; i++)
    {
        p=(char*)malloc(30);
	    printf("Please enter company name Numb.%d:",i+1);
        gets(p);
        if (mystrcmp(p,"end")) break;
	    else mystrcpy(arr[i].name,p);
	    free(p);
    }
}
void set_tax()
{
    int i;
    for(i = 0; i < 50 && arr[i].name[1]; i++)
    {
        printf("Please enter amount of tax to the firm %s:",arr[i].name);
        fflush(stdin);
        scanf("%s",arr[i].tax);
    }
}
void set_dates()
{

    int i;
    for(i = 0; i < 50 && arr[i].name[1]; i++)
    {
        char *p;
        p=(char*)calloc(4,1);
        printf("Please enter the date of the deadline for tax payment (or '0 'in all respects, if not been made) for the firm %s\n",arr[i].name);
        printf("DD MMM YYYY:");
	    fflush(stdin);
	    scanf("%d%s%d",&arr[i].last_date.d,p,&arr[i].last_date.y);
	    char_to_enum1(p,i);
	    free(p);
	    p=(char*)malloc(4);
	    printf("Please enter date of the actual tax payment (or '0 'in all respects, if not been made) for the firm %s\n",arr[i].name);
	    printf("DD MMM YYYY:");
	    fflush(stdin);
	    scanf("%d%s%d",&arr[i].act_date.d,p,&arr[i].act_date.y);
	    char_to_enum2(p,i);
	    free(p);
    }
}
void display_firms_data ()
{
    int i;
    for(i = 0; i < 50 && arr[i].name[1]; i++)
    {
        printf("Information about the firm %s:\n",arr[i].name);
	    printf("The value of tax - %s\n",arr[i].tax);
	    printf("Date of tax payment deadline - %d/%s/%d\n",arr[i].last_date.d,MONTH[arr[i].last_date.m],arr[i].last_date.y);
	    printf("Date of the actual tax payment - %d/%s/%d\n",arr[i].act_date.d,MONTH[arr[i].act_date.m],arr[i].act_date.y);
    }
}
int main()
{
    int i,j;
    struct firm tmp;
    set_name();
    set_tax();
    set_dates();
    //display_firms_data();
    for(i=0;i<49;i++)
    {
        for(j=i+1;j<50;j++)
	    {
            if (myatoi(arr[i].tax)<myatoi(arr[j].tax))
            {
                tmp=arr[i];
                arr[i]=arr[j];
                arr[j]=tmp;
            }
        }
    }
    //if(debt(i)) printf("%s has a debt to pay tax value %s$",arr[i].name,arr[i].tax);
    display_firms_data();
    getch ();
    return 0;

}

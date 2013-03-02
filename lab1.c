#include<stdio.h>
#include<conio.h>
#include<malloc.h>
// VARIANT 5
typedef enum {JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC,NONE} month;
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
    };

int mystrcmp(char *p,char *q)
{
    int i=0,ind=0;
    while(p[i] && q[i])
    {
        if (p[i]==q[i]) ind=1;
        else return 0;
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
	p[i]='\0';
}
month char_to_enum1(char *p)
{
    if     ( mystrcmp(p, "jan") ) {return JAN;}
    else if( mystrcmp(p, "feb") ) {return FEB;}
    else if( mystrcmp(p, "mar") ) {return MAR;}
    else if( mystrcmp(p, "apr") ) {return APR;}
    else if( mystrcmp(p, "may") ) {return MAY;}
    else if( mystrcmp(p, "jun") ) {return JUN;}
    else if( mystrcmp(p, "jul") ) {return JUL;}
    else if( mystrcmp(p, "aug") ) {return AUG;}
    else if( mystrcmp(p, "sep") ) {return SEP;}
    else if( mystrcmp(p, "oct") ) {return OCT;}
    else if( mystrcmp(p, "nov") ) {return NOV;}
    else if( mystrcmp(p, "dec") ) {return DEC;}
    else if( mystrcmp(p, "0"  ) ) {return NONE;}
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
int debt(int i,struct firm arr[50])
{
    if(arr[i].act_date.y>arr[i].last_date.y) return 1;
    else if(arr[i].act_date.y<arr[i].last_date.y) return 0;
    if(arr[i].act_date.m>arr[i].last_date.m) return 1;
    else if(arr[i].act_date.m<arr[i].last_date.m) return 0;
    if(arr[i].act_date.d>arr[i].last_date.d) return 1;
    else if(arr[i].act_date.d<arr[i].last_date.d) return 0;
    return 0;
}
void set_name(struct firm arr[50])
{
    int i;
    char *p;
    for(i = 0; i < 50; i++)
    {
        p=(char*)calloc(30,1);
        printf("Please enter company name Numb.%d:",i+1);
        gets(p);
        if (mystrcmp(p,"end")) {arr[i].name[0]=NULL; break;}
        else mystrcpy(arr[i].name,p);
        free(p);
    }
}
void set_tax(struct firm arr[50])
{
    int i;
    for(i = 0; i < 50 && arr[i].name[0]; i++)
    {
        printf("Please enter amount of tax to the firm %s:",arr[i].name);
        fflush(stdin);
        scanf("%s",arr[i].tax);
    }
}
void set_dates(struct firm arr[50])
{

    int i;
    for(i = 0; i < 50 && arr[i].name[0]; i++)
    {
        char *p;
        p=(char*)calloc(4,1);
        printf("Please enter the date of the deadline for tax payment (or '0 'in all respects, if not been made) for the firm %s\n",arr[i].name);
        printf("DD MMM YYYY:");
        fflush(stdin);
	scanf("%d%s%d",&arr[i].last_date.d,p,&arr[i].last_date.y);
	arr[i].last_date.m=char_to_enum1(p);
	free(p);
	p=(char*)malloc(4);
	printf("Please enter date of the actual tax payment (or '0 'in all respects, if not been made) for the firm %s\n",arr[i].name);
	printf("DD MMM YYYY:");
	fflush(stdin);
	scanf("%d%s%d",&arr[i].act_date.d,p,&arr[i].act_date.y);
	arr[i].act_date.m=char_to_enum1(p);
	free(p);
    }
}
void display_firms_data (struct firm arr[50], char MONTH[13][5])
{
    int i;
    for(i = 0; i < 50 && arr[i].name[0]; i++)
    {
        printf("Information about the firm %s:\n",arr[i].name);
        printf("The value of tax - %s\n",arr[i].tax);
	printf("Date of tax payment deadline - %d/%s/%d\n",arr[i].last_date.d,MONTH[arr[i].last_date.m],arr[i].last_date.y);
	printf("Date of the actual tax payment - %d/%s/%d\n",arr[i].act_date.d,MONTH[arr[i].act_date.m],arr[i].act_date.y);
    }
}
int main()
{
	char MONTH[13][5]={"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC","NONE"};
    struct firm arr[50];
    int i,j;
    struct firm tmp;
    set_name(arr);
    set_tax(arr);
    set_dates(arr);
    //display_firms_data();
    for(i=0;i<49 && arr[i].name[0];i++)
    {
        for(j=i+1;j<50 && arr[j].name[0];j++)
	    {
            if (myatoi(arr[i].tax)<myatoi(arr[j].tax))
            {
                tmp=arr[i];
                arr[i]=arr[j];
                arr[j]=tmp;
            }
        }
    }
    //for(i=0;i<49 && j<=5;i++)
    //{
    //    if (dept(i,&arr)) j++;
    //    else
    //}
    //if(debt(i)) printf("%s has a debt to pay tax value %s$",arr[i].name,arr[i].tax);
    display_firms_data(arr,&MONTH);
    getch();
    return 0;
}

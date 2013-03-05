#include<stdio.h>
#include<stdlib.h>
#include "mystdlib.h"
#include<malloc.h>
// VARIANT 5
enum month {JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC,NONE};
struct date
{
    int d;
    enum month m;
    int y;
};
struct firm
{
    char name[30];
    char tax[7];
    struct date last_date;
    struct date act_date;
};
enum month char_to_enum1(char *str)
{
    if     ( mystrcmp(str, "jan") ) {return JAN;}
    else if( mystrcmp(str, "feb") ) {return FEB;}
    else if( mystrcmp(str, "mar") ) {return MAR;}
    else if( mystrcmp(str, "apr") ) {return APR;}
    else if( mystrcmp(str, "may") ) {return MAY;}
    else if( mystrcmp(str, "jun") ) {return JUN;}
    else if( mystrcmp(str, "jul") ) {return JUL;}
    else if( mystrcmp(str, "aug") ) {return AUG;}
    else if( mystrcmp(str, "sep") ) {return SEP;}
    else if( mystrcmp(str, "oct") ) {return OCT;}
    else if( mystrcmp(str, "nov") ) {return NOV;}
    else if( mystrcmp(str, "dec") ) {return DEC;}
    else if( mystrcmp(str, "0"  ) ) {return NONE;}
}
int check_debt(int i,struct firm arr[50])
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
    int i,j=0;
	char *str;
    for(i = 0; i < 50; i++)
    {
        str=(char*)calloc(30,1);
        printf("Please enter company name Numb.%d:",i+1);
        fgets(str,30,stdin);
        if (mystrcmp(str,"end")) {arr[i].name[0]=NULL; break;}
        else mystrcpy(arr[i].name,str);
        free(str);
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
        char *str;
        str=(char*)calloc(4,1);
        printf("Please enter the date of the deadline for tax payment (or '0 'in all respects, if not been made) for the firm %s\n",arr[i].name);
        printf("DD MMM YYYY:");
        fflush(stdin);
        scanf("%d%s%d",&arr[i].last_date.d,str,&arr[i].last_date.y);
        arr[i].last_date.m=char_to_enum1(str);
        free(str);
        str=(char*)malloc(4);
        printf("Please enter date of the actual tax payment (or '0 'in all respects, if not been made) for the firm %s\n",arr[i].name);
        printf("DD MMM YYYY:");
        fflush(stdin);
        scanf("%d%s%d",&arr[i].act_date.d,str,&arr[i].act_date.y);
        arr[i].act_date.m=char_to_enum1(str);
        free(str);
    }
}
void display_firms_data (struct firm arr[50], char month_names[13][5])
{
    int i;
    for(i = 0; i < 50 && arr[i].name[0]; i++)
    {
        printf("Information about the firm %s:\n",arr[i].name);
        printf("The value of tax - %s\n",arr[i].tax);
        printf("Date of tax payment deadline - %d/%s/%d\n",arr[i].last_date.d,month_names[arr[i].last_date.m],arr[i].last_date.y);
        printf("Date of the actual tax payment - %d/%s/%d\n",arr[i].act_date.d,month_names[arr[i].act_date.m],arr[i].act_date.y);
    }
}
int main()
{
    char month_names[13][5]={"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC","NONE"};
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
    //    if (check_debt(i,&arr)) j++;
    //    else
    //}
    //if(check_debt(i)) printf("%s has a debt to pay tax value %s$",arr[i].name,arr[i].tax);
    display_firms_data(arr,&month_names);
    return 0;
}

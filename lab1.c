#include<stdio.h>
#include<conio.h>
#include<malloc.h>
struct firm
{
    char im[30];
    char nalog[7];
    char *date;
    char *date_fact;
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
void set_name()
{
    int i;
    char *p;
    for(i = 0; i < 50; i++)
    {
        gets(p);
        if (mystrcmp(p,"end")) break;

    }

}
void interact_firms ()
{
    int i;
    for(i = 0; i < 50; i++)
        puts(arr[i].im);
}
int main()
{

    set_name();
    interact_firms();
    getch ();
    return 0;

}

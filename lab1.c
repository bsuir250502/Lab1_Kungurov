#include<stdio.h>
#include "mystdlib.h"
#include<malloc.h>
// VARIANT 5
enum month { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC,
        NONE };
struct date {
    int d;
    enum month m;
    int y;
};
struct company {
    char name[30];
    char tax[7];
    struct date last_date;
    struct date act_date;
};
enum month char_to_enum1(char *str)
{
    if (!mystrcmp(str, "jan")) {
        return JAN;
    } else if (!mystrcmp(str, "feb")) {
        return FEB;
    } else if (!mystrcmp(str, "mar")) {
        return MAR;
    } else if (!mystrcmp(str, "apr")) {
        return APR;
    } else if (!mystrcmp(str, "may")) {
        return MAY;
    } else if (!mystrcmp(str, "jun")) {
        return JUN;
    } else if (!mystrcmp(str, "jul")) {
        return JUL;
    } else if (!mystrcmp(str, "aug")) {
        return AUG;
    } else if (!mystrcmp(str, "sep")) {
        return SEP;
    } else if (!mystrcmp(str, "oct")) {
        return OCT;
    } else if (!mystrcmp(str, "nov")) {
        return NOV;
    } else if (!mystrcmp(str, "dec")) {
        return DEC;
    } else if (!mystrcmp(str, "0")) {
        return NONE;
    }
}

int check_debt(int i, int monitor_day, int monitor_year,
               enum month monitor_month, struct company arr[50])
{
    int debt = 0;
    if (arr[i].last_date.y > monitor_year)
        return 0;
    if (arr[i].act_date.y > monitor_year)
        return 1;
    if (arr[i].last_date.y == monitor_year
        || arr[i].act_date.y == monitor_year) {
        if (arr[i].last_date.m > monitor_month)
            return 0;
        if (arr[i].act_date.m > monitor_month)
            return 1;
        if (arr[i].last_date.m == monitor_month
            || arr[i].act_date.m == monitor_month) {
            if (arr[i].last_date.d >= monitor_day)
                return 0;
            if (arr[i].act_date.d > monitor_day)
                return 1;
            else
                return 0;
        }
    }
}

void set_name(struct company arr[50], FILE * p)
{
    int i, j = 0;
    char *str;
    for (i = 0; i < 50; i++) {
        str = (char *) calloc(30, 1);
        printf("Please enter company name Numb.%d:", i + 1);
        fscanf(p, "%s", str);
        if (!mystrcmp(str, "end")) {
            arr[i].name[0] = NULL;
            break;
        } else
            mystrcpy(arr[i].name, str);
        free(str);
    }
}

void set_tax(struct company arr[50], FILE * p)
{
    int i;
    for (i = 0; i < 50 && arr[i].name[0]; i++) {
        printf("Please enter amount of tax to the company %s:",
               arr[i].name);
        fflush(stdin);
        fscanf(p, "%s", arr[i].tax);
    }
}

void set_dates(struct company arr[50], FILE * p)
{

    int i;
    for (i = 0; i < 50 && arr[i].name[0]; i++) {
        char *str;
        str = (char *) calloc(4, 1);
        printf
            ("Please enter the date of the deadline for tax payment (or '0 'in all respects, if not been made) for the company %s\n",
             arr[i].name);
        printf("DD MMM YYYY:");
        fflush(stdin);
        fscanf(p, "%d%s%d", &arr[i].last_date.d, str, &arr[i].last_date.y);
        arr[i].last_date.m = char_to_enum1(str);
        free(str);
        str = (char *) malloc(4);
        printf
            ("Please enter date of the actual tax payment (or '0 'in all respects, if not been made) for the company %s\n",
             arr[i].name);
        printf("DD MMM YYYY:");
        fflush(stdin);
        fscanf(p, "%d%s%d", &arr[i].act_date.d, str, &arr[i].act_date.y);
        arr[i].act_date.m = char_to_enum1(str);
        free(str);
    }
}

void display_company_data(struct company arr[50], char month_names[13][5])
{
    int i;
    for (i = 0; i < 5 && arr[i].name[0]; i++) {
        printf("\nNumb.%d\nInformation about the company %s:\n", i + 1,
               arr[i].name);
        printf("The value of tax - %s\n", arr[i].tax);
        printf("Date of tax payment deadline - %d/%s/%d\n",
               arr[i].last_date.d, month_names[arr[i].last_date.m],
               arr[i].last_date.y);
        printf("Date of the actual tax payment - %d/%s/%d\n",
               arr[i].act_date.d, month_names[arr[i].act_date.m],
               arr[i].act_date.y);
    }
}

int main()
{
    char month_names[13][5] =
        { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP",
"OCT", "NOV", "DEC", "NONE" };
    struct company arr[50];
    char *str = (char *) malloc(4);
    int i, j, n = 0, monitor_day = 0, monitor_year = 0, replaceable =
        0, substitutive = 0;
    enum month monitor_month;
    struct company tmp;
    FILE *p;
    p = fopen("d:\\git\\lab1_kungurov\\input.txt", "rt");
    set_name(arr, p);
    set_tax(arr, p);
    set_dates(arr, p);
    for (i = 0; i < 49 && arr[i].name[0]; i++) {
        for (j = i + 1; j < 50 && arr[j].name[0]; j++) {
            if (myatoi(arr[i].tax) < myatoi(arr[j].tax)) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    printf("Please enter the date monitor debt");
    fscanf(p, "%d%s%d", &monitor_day, str, &monitor_year);
    monitor_month = char_to_enum1(str);
    while (n < 5) {
        if (!check_debt(n, monitor_day, monitor_year, monitor_month, arr)) {
            replaceable = n;
            for (i = n + 1; i < 30; i++)
                if (check_debt
                    (i, monitor_day, monitor_year, monitor_month, arr)) {
                    substitutive = i;
                    break;
                }
            tmp = arr[replaceable];
            arr[replaceable] = arr[substitutive];
            arr[substitutive] = tmp;
        }
        n++;
    }
    for (j = 0; j < n; j++) {
        for (i = 0; i < n - 1; i++) {
            if (mystrcmp(arr[i].name, arr[i + 1].name) > 0) {
                tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
            }
        }
    }
    display_company_data(arr, &month_names);
    return 0;
}

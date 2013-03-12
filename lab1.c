#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
// VARIANT 5
struct company {
    char name[30];
    char tax[7];
    time_t last_date;
    time_t act_date;

};
int check_debt(int i, struct company arr[50], time_t monitor_date)
{
    if (arr[i].last_date > monitor_date)
        return 0;
    if (arr[i].act_date > monitor_date)
        return 1;
}

int check_error(char *str_check)
{
    int i;
    if (*(str_check) == '0' && *(str_check + 1) == '\n')
        return 0;
    for (i = 0; i < 2; i++) {
        if (*(str_check + i) >= 0 && *(str_check + i) <= 9)
            continue;
        else
            return 2;
    }
    for (i = 3; i < 6; i++) {
        if ((*(str_check + i) >= 'a' && *(str_check + i) <= 'z')
            || (*(str_check + i) >= 'A' && *(str_check + i) <= 'Z'))
            continue;
        else
            return 2;
    }
    for (i = 7; i < 11; i++) {
        if (*(str_check + i) >= 0 && *(str_check + i) <= 9)
            continue;
        else
            return 2;
    }
    return 1;
}

void set_name(struct company arr[50])
{
    int i;
    char *str;
    for (i = 0; i < 50; i++) {
        str = (char *) calloc(30, 1);
        printf("Please enter company name Numb.%d:", i + 1);
        fgets(str, 30, stdin);
        *(str + strlen(str) - 1) = '\0';
        if (!strcmp(str, "end")) {
            arr[i].name[0] = '0';
            break;
        } else
            strcpy(arr[i].name, str);
        free(str);
    }
}

void set_tax(struct company arr[50])
{
    int i;
    for (i = 0; i < 50 && arr[i].name[0] != '0'; i++) {
        printf("Please enter amount of tax to the company %s:",
               arr[i].name);
        fgets(arr[i].tax, 7, stdin);
    }
}

void set_dates(struct company arr[50])
{

    int i;
    char *str;
    struct tm tm;
    str = (char *) calloc(15, 1);
    for (i = 0; i < 50 && arr[i].name[0]; i++) {
        printf
            ("Please enter the date of the deadline for tax payment for the company %s\n",
             arr[i].name);
        printf("DD MMM YYYY:");
        fgets(str, 15, stdin);
        strptime(str, "%d%B%y", &tm);
        arr[i].last_date = mktime(&tm);
        free(str);
        str = (char *) malloc(15);
        printf
            ("Please enter date of the actual tax payment for the company %s\n",
             arr[i].name);
        printf("DD MMM YYYY:");
        fgets(str, 15, stdin);
        strptime(str, "%d%B%y", &tm);
        arr[i].act_date = mktime(&tm);
        free(str);
    }
}

void display_company_data(struct company arr[50])
{
    int i;
    for (i = 0; i < 5 && arr[i].name[0]; i++) {
        printf("\nNumb.%d: %s", i + 1, arr[i].name);
    }
}

int main(void)
{
    struct company arr[50];
    char *str = (char *) malloc(4);
    int i, j, n = 0, replaceable, substitutive;
    struct tm tm;
    time_t monitor_date;
    struct company tmp;
    set_name(arr);
    set_tax(arr);
    set_dates(arr);
    for (i = 0; i < 49 && arr[i].name[0]; i++) {
        for (j = i + 1; j < 50 && arr[j].name[0]; j++) {
            if (atoi(arr[i].tax) < atoi(arr[j].tax)) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    printf("Please enter the date monitor debt");
    fgets(str, 15, stdin);
    strptime(str, "%d%B%y", &tm);
    monitor_date = mktime(&tm);
    while (n < 5) {
        if (!check_debt(n, arr, monitor_date)) {
            replaceable = n;
            for (i = n + 1; i < 30; i++)
                if (check_debt(i, arr, monitor_date)) {
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
            if (strcmp(arr[i].name, arr[i + 1].name) > 0) {
                tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
            }
        }
    }
    display_company_data(arr);
}

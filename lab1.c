#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
const int max_number_of_companies = 50;
const int input_buffer_length = 30;
struct company {
    char name[30];
    char tax[7];
    time_t last_date;
    time_t act_date;
    int is_debt;

};
void check_debt(int i, struct company arr[max_number_of_companies], time_t monitor_date)
{
    if (arr[i].is_debt == 1)
        return;
    if (arr[i].last_date > monitor_date) {
        arr[i].is_debt = 0;
        return;
    } else if (arr[i].act_date > monitor_date)
        arr[i].is_debt = 1;
}


void set_name(struct company arr[max_number_of_companies])
{
    int i;
    char *input_buffer;
    for (i = 0; i < max_number_of_companies; i++) {
        input_buffer = (char *) calloc(input_buffer_length, 1);
        printf("Please enter company name Numb.%d:", i + 1);
        fgets(input_buffer, input_buffer_length, stdin);
        *(input_buffer + strlen(input_buffer) - 1) = '\0';
        if (!strcmp(input_buffer, "end")) {
            arr[i].name[0] = '\0';
            break;
        } else
            strcpy(arr[i].name, input_buffer);
        free(input_buffer);
    }
}

void set_tax(struct company arr[max_number_of_companies])
{
    int i;
    for (i = 0; i < max_number_of_companies && arr[i].name[0]; i++) {
        printf("Please enter amount of tax to the company %s:",
               arr[i].name);
        fgets(arr[i].tax, 7, stdin);
    }
}

void set_dates(struct company arr[max_number_of_companies])
{

    int i;
    char *input_buffer;
    struct tm tm;
    for (i = 0; i < max_number_of_companies && arr[i].name[0]; i++) {
        printf
            ("Please enter the date of the deadline for tax payment for the company %s\n",
             arr[i].name);
        printf("DD MMM YYYY:");
        input_buffer = (char *) calloc(input_buffer_length, 1);
        while (1) {

            fgets(input_buffer, input_buffer_length, stdin);
            *(input_buffer + strlen(input_buffer) - 1) = '\0';
            if (!strptime(input_buffer, "%d %b %y", &tm))
                printf("Enter correct date");
            else
                break;
        }
        arr[i].last_date = mktime(&tm);
        free(input_buffer);
        input_buffer = (char *) calloc(input_buffer_length, 1);
        printf
            ("Please enter date of the actual tax payment for the company %s\n",
             arr[i].name);
        printf("DD MMM YYYY:");
        while (1) {

            fgets(input_buffer, input_buffer_length, stdin);
            if (input_buffer[0] == '0') {
                arr[i].is_debt = 1;
                break;
            } else {
                arr[i].is_debt = 0;
                *(input_buffer + strlen(str) - 1) = '\0';
                if (!strptime(input_buffer, "%d %b %y", &tm))
                    printf("Enter correct date");
                else
                    break;
            }
        }
        arr[i].act_date = mktime(&tm);
        free(input_buffer);
    }
}

void display_company_data(struct company arr[max_number_of_companies])
{
    int i;
    for (i = 0; i < 5 && arr[i].is_debt; i++) {
        printf("\nNumb.%d: %s", i + 1, arr[i].name);
    }
}

int main(void)
{
    struct company arr[max_number_of_companies];
    char *input_buffer = (char *) malloc(input_buffer_length);
    int i, j, n = 0, replaceable, substitutive;
    struct tm tm;
    time_t monitor_date;
    struct company tmp;
    set_name(arr);
    set_tax(arr);
    set_dates(arr);
    for (i = 0; i < max_number_of_companies && arr[i].name[0]; i++) {
        for (j = i + 1; j < max_number_of_companies && arr[j].name[0]; j++) {
            if (atoi(arr[i].tax) < atoi(arr[j].tax)) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    printf("Please enter the date monitor debt");
    fgets(input_buffer, input_buffer_length, stdin);
    strptime(input_buffer, "%d %B %y", &tm);
    monitor_date = mktime(&tm);
    for (i = 0; i < max_number_of_companies && arr[i].name[0]; i++) {
        check_debt(i, arr, monitor_date);
        printf("%s %d", arr[i].name, arr[i].is_debt);
    }
    while (n < 5) {
        if (!arr[i].is_debt) {
            replaceable = n;
            for (i = n + 1; i < max_number_of_companies; i++)
                if (arr[i].is_debt) {
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

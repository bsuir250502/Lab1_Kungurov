/* -*- coding: utf-8-dos -*- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "mystdlib.h"
#include "dates.h"

struct company {
    char name[30];
    long int tax;
    time_t last_date;
    time_t act_date;
};

int check_debt(struct company company, time_t monitor_date)
{
    int debt = 0;
    if (company.last_date < monitor_date
        && (!company.act_date || company.act_date > monitor_date)) {
        debt = company.tax;
    }
    return debt;
}


int initialize_companies(struct company *companies, size_t max)
{
    int i;
    const int input_buffer_length = 31;
    char input_buffer[input_buffer_length];
    for (i = 0; i < max; i++) {
        printf("Please enter company name Numb.%d:", i + 1);
        my_gets(input_buffer, input_buffer_length);
        if (!strcmp(input_buffer, "end")) {
            break;
        } else {
            strcpy(companies[i].name, input_buffer);
        }
    }
    return i;
}


void display_company(struct company company)
{
    printf("\nname: %s\n", company.name);
}

int main(void)
{
    const int max_number_of_companies = 50;
    struct company companies[max_number_of_companies];
    struct company *company;
    int number_of_companies;
    int i;
    struct company tmp;
    time_t monitor_date;
    char date_format[] = "%d %b %Y";
    number_of_companies =
        initialize_companies(companies, max_number_of_companies);
    for (i = 0; i < number_of_companies; i++) {
        company = &companies[i];
        printf("Please enter amount of tax to the company %s:\n",
               company->name);
        company->tax = read_number();
        printf("Please enter tax payment deadline date (DD MMM YYYY): \n");
        company->last_date = get_date(date_format);
        printf
            ("Please enter actual tax payment date or 0 for no date (DD MMM YYYY): \n");
        company->act_date = try_get_date("0", date_format);
        }
    printf("Please enter monitor date (DD MMM YYYY): \n");
    monitor_date = try_get_date("0", date_format);
    int j, replaceable, substitutive;
    for (i = 0; i < number_of_companies; i++) {
        for (j = i + 1; j < number_of_companies; j++) {
            if (companies[i].tax < companies[j].tax) {
                memset(&tmp, 0, sizeof(struct company));
                tmp = companies[i];
                companies[i] = companies[j];
                companies[j] = tmp;
            }
        }
    }
    i = 0;
    while (i < number_of_companies) {
        if (!check_debt(companies[i], monitor_date)) {
            replaceable = i;
            for (j = i + 1; j < number_of_companies; j++)
                if (check_debt(companies[j], monitor_date)) {
                    substitutive = j;
                    memset(&tmp, 0, sizeof(struct company));
                    tmp = companies[replaceable];
                    companies[replaceable] = companies[substitutive];
                    companies[substitutive] = tmp;
                    break;
                }
        }
        i++;
    }
    for (i = 0; check_debt(companies[i], monitor_date) && i < 5; i++) {
        for (j = i + 1; check_debt(companies[j], monitor_date) && j < 5;
             j++) {
            if (strcmp(companies[i].name, companies[j].name) > 0) {
                memset(&tmp, 0, sizeof(struct company));
                tmp = companies[i];
                companies[i] = companies[j];
                companies[j] = tmp;
            }
        }
    }
    puts("\nThe five companies with the most debt, in alphabetical order:");
    for (i = 0; check_debt(companies[i], monitor_date) && i < 5; i++) {
        display_company(companies[i]);
    }
    return 0;
}

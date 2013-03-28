/* -*- coding: utf-8-dos -*- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdarg.h>
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

int namecmp(const void *a, const void *b)
{
    struct company *pa = a;
    struct company *pb = b;
    return strcmp(pa->name, pb->name);
}

int debtcmp(const void *a, const void *b, ...)
{
    static time_t monitor_date = 0;
    struct company *pb = a;
    struct company *pa = b;
    va_list ap;
    if (!a && !b) {
        va_start(ap, b);
        monitor_date = va_arg(ap, time_t);
        va_end(ap);
        return 0;
    };
    return check_debt(*pa, monitor_date) - check_debt(*pb, monitor_date);
}

int main(int argc, char **argv)
{
    const int max_number_of_companies = 50;
    struct company companies[max_number_of_companies];
    struct company *company;
    int number_of_companies;
    int i;
    struct company tmp;
    time_t monitor_date;
    char date_format[] = "%d %b %Y";
    if (argc == 2){
        if ((strcmp(argv[1],"-h"))==0) { puts("Instructions for use:\n 1.Start the program (cd drive :/ place / location / file / -> make -> ./lab1).\n2. Company name. Our offers to enter the business name, type a name (no more than 30 characters)\nthen click <enter>. Entering stop when you enter the 50 firms, or if you need a stop earlier,\njust type 'end' (without the quotes). You will then proceed to enter personal information\nfor each firm.\n3. PERSONAL INFORMATION FOR EACH OF COMPANIES.\n    3.1. To offer input tax (tax), enter the number (not more than 7 digits).\n    3.2. Next, enter the date of the offer closing date (deadline), type the date in\n        format DD MMM YYYY (Ex. 01 jan 1970) or write the month when you enter a fully\n        (Ex. 01 january 1970). If you enter the wrong program will tell you.\n    3.3. Next on the proposal to introduce the date of actual payment, enter the date (see section 3.2)\n    or '0' (zero), if the payment of the tax has not been made.\nItems 3.1 - 3.2 is repeated for all input firms.\n4. DATE AT THE TIME TRACKING be produced by the debtor. The proposal to introduce\ndate monitoring of debtors (monitor_date), enter in the mentioned format (see section 3.2).\n"); return 0;}}
       
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
    int j, replaceable, substitutive, number_of_debt_companies;
    debtcmp(NULL, NULL, monitor_date);
    qsort(companies, number_of_companies, sizeof(struct company), debtcmp);
    for (i = 0; check_debt(companies[i],monitor_date) && i < 5; i++);
    number_of_debt_companies = i;
    qsort(companies, number_of_debt_companies, sizeof(struct company), namecmp);
    puts("\nThe five companies with the most debt, in alphabetical order:");
    for (i = 0; i < number_of_debt_companies; i++) {
        printf("\nname: %s\n", companies[i].name);
    }
    return 0;
}

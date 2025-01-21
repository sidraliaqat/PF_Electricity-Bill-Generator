// Electricity Bill Generator.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <string.h>

struct customer {
    char name[50];
    int id;  
    int units;
    char address[50];
    char date[15];
} c;
struct bill {
	int id;
	 int total_bill;
    int fined_months;
	float tax_amount;
	float g_total_bill;
}b;

void calculate_total_bill() {
    int price_of_each_unit = 70;
    printf("Enter the units consumed: ");
    scanf_s("%d", &c.units);
    b.total_bill = price_of_each_unit * c.units;
}

void get_customer_data()
{
    printf("Enter Customer ID: ");
    scanf_s("%d", &c.id);  
    printf("Enter Customer name: ");
    scanf_s("%s", c.name, 50);
    printf("Enter Customer's Address: ");
    scanf_s("%s", c.address, 50);
    printf("Enter today's date: ");
    scanf_s("%s", c.date, 25);
}

void check_previous_bills() 
{
    char response;
    printf("Have you paid the previous bills? (Y/N): ");
    scanf_s(" %c", &response);
    if (response == 'N' || response == 'n') {
        int unpaid_months;
        int total_unpaid_amount = 0;
        printf("Enter the number of months you have not paid: ");
        scanf_s("%d", &unpaid_months);
        for (int i = 1; i <= unpaid_months; ++i) {
            int unpaid_amount;
            printf("Enter the unpaid amount for month %d: ", i);
            scanf_s("%d", &unpaid_amount);
            total_unpaid_amount += unpaid_amount;
        }

        if (unpaid_months > 3) {
            printf("Warning: Your meter will be cut within a week if the bill is not paid.\n");
        }
        int fine = unpaid_months * 1000;
        b.total_bill += total_unpaid_amount + fine;
        b.fined_months = unpaid_months;
    }
}
void add_tax() {
    float tax_rate = 0.05;
    b.tax_amount = b.total_bill * tax_rate;
    b.g_total_bill = b.tax_amount + b.total_bill;
}
void display_bill() {
    FILE* bill;
    fopen_s(&bill, "bill.txt", "a");
	fprintf(bill,"\n\n=============================================");
    fprintf(bill,"\n\t      ELECTRICITY BILL");
    fprintf(bill,"\n============================================\n");
    fprintf(bill, "Customer Name: %s\n", c.name);
    fprintf(bill, "Customer ID: %d\n", c.id); 
    fprintf(bill, "Customer Address: %s\n", c.address);
    fprintf(bill, "Issue Date: %s\n", c.date);
    fprintf(bill, "Units Consumed: %d\n", c.units);
    fprintf(bill, "Total Bill: %d\n", b.total_bill);
	fprintf(bill, "Tax Amount: %2f\n", b.tax_amount);
	fprintf(bill, "Grand Total Bill: %2f\n", b.g_total_bill);
    if (b.fined_months > 0) {
        fprintf(bill, "Also Fined for %d month(s) of previous unpaid bills.\n", b.fined_months);
    }
	fprintf(bill, "BILL GENERATED!\n");
    fprintf(bill, "============================================\n");
    fclose(bill);
}
int main() {
    get_customer_data();
	calculate_total_bill();
    check_previous_bills();
	add_tax();
    display_bill();
    printf("\n\n===========================================");
    printf("\n\t      ELECTRICITY BILL");
    printf("\n===========================================\n");
    printf("Customer Name: \t\t %s\n", c.name);
    printf("Customer ID: \t\t%d\n", c.id); 
    printf("Customer Address:\t %s\n", c.address);
    printf("Units Consumed:\t\t %d\n", c.units);
    printf("Issue Date:\t\t %s\n", c.date);
    printf("Tax Amount:\t\t%2f\n", b.tax_amount);
    printf("Total Bill: \t\t%d\n", b.total_bill);
    printf("Grand Total Bill:\t %2f\n", b.g_total_bill);
    printf("\nBILL GENERATED!\n");
    printf("===========================================\n");
    return 0;
}

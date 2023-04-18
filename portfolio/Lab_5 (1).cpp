#include <iostream> 
#include <cmath>  
#include <iomanip>
#include <fstream>
#include <string> 

#define TAX_RATE .0125
#define INSURANCE_COST 550 
#define UTILITIES_COST 300

using namespace std;



/*****************************************************************************/
//                            main()
/*****************************************************************************/
/*
********************
    Variables:
********************

double selling_price; House selling price
down_paymt; Amount of down payment
loan_amount; Loan to be borrowed from the bank
interest_rate; Annual Interest rate on the loan
monthly_mortgage; Monthly mortgage payment calculated from
the compound interest formula
tax_amount; monthly property tax payment
total_monthly_cost; total monthly cost, sum of mortgage,utilities,
property tax and insurance

int payoff_years; No. of years to be taken to payoff the loan,
to be converted to monthe period to be used
in the compound interest formula

*************************
   Invoked Functions:
*************************

1. "get_mortgage_input_data" inputs mortgage data from user
    a) house selling price
     b) loan interest rate charged by the bank
     c) number of years the user want to take to payoff the loan

2. "calc_monthly_costs" calculates the Monthly House Cost and gives:
     a) down payment,
     b) loan amount,
     c) monthly mortgage payment,
     d) monthly property tax payment,
     e) monthly insurance premium payment, and
     f) total monthly cost - sum of mortgage, utilities, tax and insurance

3. "file_output_data" writes output data to a text file

/*****************************************************************************/

double get_mortgage_input_data (double &price, double &rate, int &time_period);
double calc_monthly_costs (double &mortgage, double &total, double price, double &payment, double &loan, double interest, double payoff, double &taxes);
double calc_down_payment (double price, double &payment);
double calc_loan_amount (double price, double &loan);
double calc_monthly_mortgage_payment(double loan, double rate, int time_period, double &mortgage);

void file_output_data (double price, double payment, double loan, double interest, int years, double mortgage, double taxes, double total);

int main() {
    double selling_price;
    double interest_rate;
    int payoff_years; 
    double down_paymt;
    double loan_amount; 
    double monthly_mortgage;
    double tax_amount;
    double total_monthly_cost; 

    get_mortgage_input_data(selling_price, interest_rate, payoff_years);  
    calc_monthly_costs (monthly_mortgage, total_monthly_cost, selling_price, down_paymt, loan_amount, interest_rate, payoff_years, tax_amount);  
    file_output_data(selling_price, down_paymt, loan_amount, interest_rate, payoff_years, monthly_mortgage, tax_amount, total_monthly_cost); 

}

double get_mortgage_input_data (double &price, double &rate, int &time_period) {
    cout << "Enter the selling price of the house: " << endl; 
    cin >> price;
    cout << "Enter the annual rate of interest: " << endl; 
    cin >> rate;
    cout << "Enter the loan duration: " << endl;
    cin >> time_period; 
    return 0;
}

double calc_monthly_costs (double &mortgage, double &total, double price, double &payment, double &loan, double interest, double payoff, double &taxes) { 
    calc_down_payment(price, payment); 
    calc_loan_amount(price, loan);
    calc_monthly_mortgage_payment(loan, interest, payoff, mortgage);
    taxes = TAX_RATE * price;
    total = mortgage +  UTILITIES_COST + (taxes) + INSURANCE_COST; 
    return 0;
}

double calc_down_payment (double price, double &payment) {
   payment = price * .20; 
   return 0;

}

double calc_loan_amount (double price, double &loan){
    loan = price * .80; 
    return 0;
}

double calc_monthly_mortgage_payment(double loan, double rate, int time_period, double &mortgage) {
    double monthly_interest = rate/12;

    mortgage = loan * monthly_interest * (pow((1 + monthly_interest), (time_period * 12)))
    /(pow((1 + monthly_interest), (time_period * 12)) -1); 
    return 0;
}

void file_output_data (double price, double payment, double loan, double interest, int years, double mortgage, double taxes, double total) {
    const int TITLE_BARRIER = 60;
    const int RIGHT_ALIGN = 40;
    const int DOLLAR_SIGN = 2;
    const int SUB_BARRIER = 25;

    ofstream file_out;
    const string pathname = "C:\\Users\\benya\\Desktop\\";
    const string fullname = pathname + "Lab_5.txt";
    
    file_out.open(fullname.c_str());

    file_out << setprecision(2) << fixed; 
    file_out << setfill('*') << setw(TITLE_BARRIER) << "*" << endl 
    << "                    MONTHLY COST OF HOUSE" << endl 
    << setfill('*') << setw(TITLE_BARRIER) << "*" << endl
    << left << setfill(' ') << setw(RIGHT_ALIGN) << "SELLING PRICE" << setw(DOLLAR_SIGN) << "$" 
    << right << price << endl
    << left << setw(RIGHT_ALIGN) << "DOWN PAYMENT" << setw(DOLLAR_SIGN) << "$" 
    << right << payment << endl
    << left << setw(RIGHT_ALIGN) << "AMOUNT OF LOAN" << setw(DOLLAR_SIGN) << "$"
    << right << loan << endl << endl
    << left << setw(RIGHT_ALIGN) << "INTEREST RATE" << interest << "%" << endl
    << setw(RIGHT_ALIGN) << "TAX RATE" << TAX_RATE << "%" << endl << endl
    << setw(RIGHT_ALIGN) << "DURATION OF LOAN (YEARS)" << years << "%" << endl << endl << endl 
    << setfill('*') << setw(SUB_BARRIER) << "*" << endl
    << "MONTHLY PAYMENT" << endl
    << setw(SUB_BARRIER) << "*" << endl << setfill(' ') 
    << setw(RIGHT_ALIGN) << "MORTGAGE PAYMENT " << setw(DOLLAR_SIGN) << "$" << right << mortgage << endl << left
    << setw(RIGHT_ALIGN) << "UTILITIES " << setw(DOLLAR_SIGN) << "$" << right << UTILITIES_COST << endl << left
    << setw(RIGHT_ALIGN) << "PROPERTY TAXES " << setw(DOLLAR_SIGN) << "$" << right << taxes << endl << left
    << setw(RIGHT_ALIGN) << "INSURANCE " << setw(DOLLAR_SIGN) << "$" << right << INSURANCE_COST << endl 
    << right << "-----------------" << endl << left
    << setw (RIGHT_ALIGN) << " " << setw(DOLLAR_SIGN) << "$" << right << total;







    file_out.close(); 
}






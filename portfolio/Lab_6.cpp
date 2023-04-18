#include <iostream> 
#include <cmath>
#include <iomanip>
#include <fstream> 

using namespace std; 

///Function prototypes 
void get_credit_data(double &, double &, double &);
void print_monthly_plan_header(double, double, double);
void calc_monthly_plan(double &balance, double, double, double &month, double & month_interest, double & minimum_payment, double &interest_sum);
void print_credit_plan(double balance, double month, double month_interest, double minimum_payment, double interest_sum);


/*****************************************************************************/
//                                main()
/*****************************************************************************/
/*
********************
Variables:
********************

credit_balance; principal credit balance
interest_rate; rate of interest in percent
minimum_monthly_payment; percent of minimum payment
month_count; keeps track of month
monthly_interest; amount of interest to be paid that month
monthly_minimum_payment; amount of minimum payment that month
total_interest_paid; total amount of interest paid over time

*************************
   Invoked Functions:
*************************

1. "get_credit_data" reads credit data from a text file, assigns that data to reference parameters 
2. "print_monthly_plan_header" writes balance, interest rate, and minimum payment,m and a barrier
    to a .txt file
3. "calc monthly costs" converts data in to decimal form, calculates balance, interest, payment, 
    total interest. Also keeps track of months. 
4. "print_credit_plan" writes the month, balance, interest, minimum payment, and total interest paid onto
    a .txt file. 

/*****************************************************************************/
int main() {
    ///Define variables 
    double credit_balance;
    double interest_rate;
    double minimum_monthly_payment;
    double month_count;
    double monthly_interest;
    double monthly_minimum_payment;
    double total_interest_paid; 
    
    ///These functions remain outside the while loop because they do not need to be repeated
    get_credit_data(credit_balance, interest_rate, minimum_monthly_payment);   
    print_monthly_plan_header(credit_balance, interest_rate, minimum_monthly_payment); 
    
    ///While loop allows the program to continually write onto a .txt file
    while (credit_balance > 0) {
        ///these functions are inside the while loop so they can be repeated as nessecary 
        calc_monthly_plan(credit_balance, interest_rate, minimum_monthly_payment, month_count, monthly_interest, monthly_minimum_payment, total_interest_paid); 
        print_credit_plan(credit_balance, month_count, monthly_interest, monthly_minimum_payment, total_interest_paid );
    }
}

///These must be reference parameters because their data needs to be passed onto the other functions. 
void get_credit_data(double &balance, double &rate, double &payment) {
    ifstream file_in; 
    
    const string input_file_pathname = "c:\\users\\arrow\\desktop\\";
    const string input_file_fullname = input_file_pathname + "lab6.txt"; 
    
    file_in.open(input_file_fullname.c_str());
    
    ///checks for failure
    if (file_in.fail()) {
        cout << "File open failed. Program abort." << endl; 
    }
    
    ///I chose this method because it is effective in splitting the stream into different variables
    file_in >> balance >> rate >> payment;

    file_in.close();
}

void print_monthly_plan_header(double balance, double rate, double payment) {
    ///these constants make it easy to adjust formatting
    const int BANNER_ALIGN = 30;
    const int BARRIER = 115;
    const int COLUMN = 20;
    
    ofstream file_out; 
    const string output_pathname = "C:\\Users\\arrow\\Desktop\\";
    const string output_fullname = output_pathname + "lab_6_output";
    file_out.open(output_fullname.c_str(), ios :: app);

    ///write output to a .txt file
    file_out << setprecision(2) << fixed;
    file_out << setfill(' ') << setw(BANNER_ALIGN) << " " << "Balance Owing: $ " << balance << endl 
    << setfill(' ') << setw(BANNER_ALIGN) << " " << "APR as % " << rate << endl 
    << setfill(' ') << setw(BANNER_ALIGN) << " " << "Percent for minimum payment as % " << payment << endl 
    << setfill('-') << setw(BARRIER) << "-" << endl << setfill(' ') 
    << setw(COLUMN) << "Month" << setw(COLUMN) << "Balance" << setw(COLUMN)
    << "Monthly Interest" << setw(COLUMN) << "Minimum" << setw(COLUMN) << "Interest paid" << endl << endl; 
}

///once again, these parameters had to be passed by reference because the upcoming print function will need the values that this function will calculate. 
void calc_monthly_plan(double &balance, double rate, double payment, double &month, double &month_interest, double &minimum_payment, double &interest_sum) {
    double interest = rate/100;
    double payment_percent = payment/100; 
    month++;
    month_interest = (interest/12) * balance;
    minimum_payment = (month_interest + balance) * payment_percent;
    ///This section allows the program to mantain a "base minimum"
    if (minimum_payment < 15) {
        minimum_payment = 15;
    }
    ///this section precents the balance from going into the negative by ensuring that the final deduction from balance will always be equal to the balance, resulting 0. 
    if (minimum_payment >= (balance + month_interest)) {
        minimum_payment = balance + month_interest;
    }
    interest_sum = interest_sum + month_interest; 
    balance = (balance + month_interest) - minimum_payment;
}

///these parameters do not need to be reference parameters because they do not get changed here. 
void print_credit_plan(double balance, double month, double month_interest, double minimum_payment, double interest_sum) {
    const int COLUMN = 20;

    ofstream file_out; 
    const string output_pathname = "C:\\Users\\arrow\\Desktop\\";
    const string output_fullname = output_pathname + "lab_6_output";
    file_out.open(output_fullname.c_str(), ios :: app);

    ///checks for failure
    if (file_out.fail()) {
        cout << "File open open failed. Program abort." << endl; 
    }
    
    ///writes to a file. 
    file_out << setw(COLUMN) << right << month << setw(COLUMN) << balance << setw(COLUMN) << month_interest
    << setw(COLUMN) << minimum_payment << setw(COLUMN) << interest_sum << endl; 

    file_out.close(); 
}




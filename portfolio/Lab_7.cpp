/*****************************************************************************/
//  Filename:      Lab_7.cpp
//
//  Author:        Ben Ha
//
//  Date:          2022.05.4
//
//  Modifications: 2022.05.7
//
//
//  Description:   This file reads heart rate data from a .txt file
//                 and outputs the data into another .txt file after    
//                 performing the nessecary calculations. 
/*****************************************************************************/
#include <iostream>
#include <cmath>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdio> 

///these are in the macros so they can be accessed by all functions
#define PARTITION_SIZE 6
#define SUBJECT_COUNT 10
#define DAYS 5

using namespace std;

///function definitions
void get_data(ifstream &in_file, int &id, int &meas_maxHR, int &age, double &total_avg, double &highest, int &exer_days, int &rejects);
void construct_arrays( int id, int meas_maxHR, int age, double total_avg, double highest, int exer_days, int rejects, int id_array[], double average_array[], int exer_days_array[], double est_maxHR_array[], double meas_to_estHR_array[], double max_to_mesHR_array[]);
double calc_meas_to_estHR(double, double);
void sort_arrays(int id_array[], double average_array[], int exer_days_array[], double est_maxHR_array[], double meas_to_estHR_array[], double max_to_mesHR_array[]); 
void output_header(ofstream &out_file); 
void output_all(int id_array[], double average_array[], int exer_days_array[], double est_maxHR_array[], double meas_to_estHR_array[], double max_to_mesHR_array[]);

/*****************************************************************************/
//                                                                     main()
/*****************************************************************************/
/*
********************
        Variables:
********************
subject_id; array for subject id
weekly_average_HR; array for weekly average HR
days_excercised; array for days excercised
estimated_maxHR; array for estimated max HR
measured_to_estimatedHR; array for ratio of measured to estimated HR
maximum_to_measuredHR; array for ratio of maximum to measured HR

id_number; id number for current subject
measured_max_HR; measured max HR for current subject
subject_age; age for current subject
total_of_avg_HR; total of the average HR for the subject, to be divded by number of days - rejected days. 
highest_HR; stores the highest HR for the current subject
excercise_days; stores the number of days excercised for current subject
false_readings; stores the number of days that resulted in invalid results. 


*************************
   Invoked Functions:
*************************
get_data; reads .txt file data and stores data into variables
construct_arrays; performs calculations and constructs arrays for subject
calc_meas_to_estHR; calculated the measured to estimated HR, called from construct_arrays. 
sort_arrays; sorts the arrays by id number
output_header; prints out header for output
output_all; prints out arrays, redirects to .txt file


/*****************************************************************************/
int main() 
{
    ///initialize arrays
    int subject_id[SUBJECT_COUNT];
    double weekly_average_HR[SUBJECT_COUNT]; 
    int days_exercised[SUBJECT_COUNT];
    double estimated_maxHR[SUBJECT_COUNT];
    double measured_to_estimatedHR[SUBJECT_COUNT];
    double maximum_to_measuredHR[SUBJECT_COUNT];

    ///variables to be defined in the get_data funciton, and then passed to the construct_arrays function. 
    int id_number; 
    int measured_max_HR; 
    int subject_age; 
    double total_of_avg_HR; 
    double highest_HR;
    int excercise_days;
    int false_readings;  
    ///open HR file
    ifstream file_in;
    const string input_pathname = "C:\\users\\arrow\\desktop\\";
    const string input_fullname = input_pathname + "HR.txt"; 
    file_in.open(input_fullname.c_str()); 
    ///check for failure
    if(file_in.fail())
    {
        cout << "No such file" << endl;
        system("pause");
        exit(100);
    }
    ///create output file
    ofstream file_out;
    const string output_pathname = "C:\\users\\arrow\\desktop\\";
    const string output_fullname = output_pathname + "lab_7_output.txt";
    file_out.open(output_fullname.c_str(), ios :: app);
    ///check for output failure
    if(file_out.fail())
    {
        cout << "file open failed" << endl;
        system("pause");
        exit(100);
    }
    ///this loop allows us to decouple the input and calculation functions, which I will explain later. 
    while(!file_in.eof()) 
    {
        get_data(file_in, id_number, measured_max_HR, subject_age, total_of_avg_HR, highest_HR, excercise_days, false_readings); 
        construct_arrays(id_number, measured_max_HR, subject_age, total_of_avg_HR, highest_HR, excercise_days, false_readings, subject_id, weekly_average_HR, days_exercised, estimated_maxHR, measured_to_estimatedHR, maximum_to_measuredHR);
    }

    sort_arrays(subject_id, weekly_average_HR, days_exercised, estimated_maxHR, measured_to_estimatedHR, maximum_to_measuredHR); 
    output_header(file_out);
    output_all(subject_id, weekly_average_HR, days_exercised, estimated_maxHR, measured_to_estimatedHR, maximum_to_measuredHR);

    ///close files
    file_out.close();
    file_in.close();
}

///in order to follow the requirement of 6 arrays, get_data uses int and double variables that will get rewritten for every subject number after being passed to the construct_arrays function. 
void get_data(ifstream &in_file, int &id, int &meas_maxHR, int &age, double &total_avg, double &highest, int &exer_days, int &rejects) 
{
    double current_commuting_HR;
    double add_to_total = 0;
    double excercise; 
    
    highest = 0; 
    exer_days = 0;
    rejects = 0;
    
    in_file >> id >> meas_maxHR >> age; 
    ///this for loop reads the input data.
    for (int idx = 2; idx <= PARTITION_SIZE; idx++)
    {
        if(highest == 0) 
        {
            in_file >> total_avg >> highest >> excercise;
        }
        else 
        { ///this section searches for the highest commuting HR
            in_file >> add_to_total >> current_commuting_HR >> excercise;  
            if(current_commuting_HR > highest)
            {
                highest = current_commuting_HR; 
            }
        }
        ///this section checks for rejects and exercise days. 
        if(add_to_total == -1)
        {
            rejects++;
        }
        else
        {
            total_avg += add_to_total; 
        }

        if(excercise != 0 )
        {
            exer_days++;
        }
    }
///cout << id << endl << meas_maxHR << endl << age << endl << total_avg << endl << highest << endl << exer_days << endl << rejects << endl;
}

///now that the parameters have been passed, construct_arrays can begin its task of making the array for the subject number. this process repeats until the end of the file. 
void construct_arrays(int id, int meas_maxHR, int age, double total_avg, double highest, int exer_days, int rejects, int id_array[], double average_array[], int exer_days_array[], double est_maxHR_array[], double meas_to_estHR_array[], double max_to_mesHR_array[])
{
    static int subject_index = 0; ///this is a counter that will allow us to assign data to different array indexes between calls. 

    ///assign values to array indexes, perform nessecary calculations
    id_array[subject_index] = id;
    average_array[subject_index] = total_avg/(DAYS-rejects); ///my solution to the weekly average was to subtract the number of rejected days. 
    exer_days_array[subject_index] = exer_days;
    est_maxHR_array[subject_index] = 220 - age;
    meas_to_estHR_array[subject_index] = calc_meas_to_estHR(meas_maxHR, est_maxHR_array[subject_index]);
    max_to_mesHR_array[subject_index] = highest/meas_maxHR; 
    
    
    subject_index++;

}

///this function gets called from within construct_arrays
double calc_meas_to_estHR(double measured, double estimated) 
{
    return(measured/estimated);
}


void sort_arrays(int id_array[], double average_array[], int exer_days_array[], double est_maxHR_array[], double meas_to_estHR_array[], double max_to_mesHR_array[])
{
    int current; int walker; 
    int smallestIndex;
    double temp; 

    ///this works by storing the index of the smallest ID number and swapping places with the current. repeating this process for every subject sorts them from least to greatest.
    for (current = 0; current < SUBJECT_COUNT; current++)
    {
        smallestIndex = current;
        for (walker = current; walker < SUBJECT_COUNT; walker++)
        {
            if(id_array[walker] < id_array[smallestIndex])
            {
                smallestIndex = walker;
            }
        }

        ///this process is a byproduct of using parallel arrays rather than classes, each array must be arranged one by one so that the data matches its original subject. 
        temp = id_array[current];
        id_array[current] = id_array[smallestIndex];
        id_array[smallestIndex] = temp; 

        temp = average_array[current];
        average_array[current] = average_array[smallestIndex];
        average_array[smallestIndex] = temp;

        temp = exer_days_array[current];
        exer_days_array[current] = exer_days_array[smallestIndex];
        exer_days_array[smallestIndex] = temp;

        temp = est_maxHR_array[current];
        est_maxHR_array[current] = est_maxHR_array[smallestIndex];
        est_maxHR_array[smallestIndex] = temp;

        temp = meas_to_estHR_array[current];
        meas_to_estHR_array[current] = meas_to_estHR_array[smallestIndex];
        meas_to_estHR_array[smallestIndex] = temp;

        temp = max_to_mesHR_array[current];
        max_to_mesHR_array[current] = max_to_mesHR_array[smallestIndex];
        max_to_mesHR_array[smallestIndex] = temp;

        
    }

}

void output_header(ofstream &out_file)
{
    const int GAP = 15; 
    out_file << fixed; 
    out_file << setw(GAP) << "SUBJECT" << setw(GAP) << "AVERAGE" << setw(GAP) << "DAYS" << setw(GAP) << "ESTIMATED"
    << setw(GAP) << "%MEASURED" << setw(GAP) << "%MAX" << endl
    
    <<setw(GAP) << "NUMBER" << setw(GAP) << "COMMUTING" << setw(GAP) << "EXERCISED" << setw(GAP) << "MAX HR" 
    << setw(GAP) << "TO" << setw(GAP) << "COMMUTING" << endl 
    
    << setw(GAP) << " " << setw(GAP) << " " << setw(GAP) << " " << setw(GAP) << " " << setw(GAP) << "ESTIMATED"
    << setw(GAP) << "HR TO" << endl

    << setw(GAP) << " " << setw(GAP) << " " << setw(GAP) << " " << setw(GAP) << " " << setw(GAP) << "MAX HR"
    << setw(GAP) << "MEASURED" << endl; 
}

void output_all(int id_array[], double average_array[], int exer_days_array[], double est_maxHR_array[], double meas_to_estHR_array[], double max_to_mesHR_array[])
{
    const int GAP = 15;
    ///this allows us to redirect the cout output into the text file we created in main(). The key here is using "a+" so that it will write to the end of the file. 
    freopen("C:\\users\\arrow\\desktop\\lab_7_output.txt", "a+", stdout);
    
    for(int idx = 0; idx < SUBJECT_COUNT; idx++)
    {
        cout << fixed << setprecision(2);
        cout << setw(GAP) << id_array[idx] << setw(GAP) << average_array[idx] << setw(GAP) << exer_days_array[idx]
        << setw(GAP) << est_maxHR_array[idx] << setw(GAP) << meas_to_estHR_array[idx] << setw(GAP) << max_to_mesHR_array[idx] << endl; 
    }
}


    
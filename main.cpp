#include "calculator.hpp" //include the calculator header file
#include "iostream" // include the input output stream
#include "fstream" // allow files to be opened as a stream
#include "string" // allows the string datatype for input
using namespace std; // this is for simplicity for cout and cin and cerr

int main(){//this is the main function we run
    double secondVal = -123.456;//this is the second value we were given to add if the double is valid
    string inputFile;//this stores the file name 
    cout << "Enter a file name: ";//this outputs to the terminal "Enter a ..."
    cin >> inputFile;//this takes in the file name and stores it in the previously declared variable

    ifstream file(inputFile);// this turns the file input into a stream
    string line;//this is so we can traverse the file line by line
    
    if (file.is_open()) {//this makes sure the file is a valid file
        while (getline(file, line)) {//this goes through the lines of the file until one cannot be found
            if (isValidDoubleString(line)) {//this calls the function to check if the string is a valid double
                double value = parse_number(line);//if it is we turn it into a double using the parse function and store in value
                double sum = value + secondVal;//we add the input value with the harcoded value
                cout << line << " + " << secondVal << " = " << sum << endl; // we output all data to the terminal 
            } else {// the line is not a valid double
                cout << "Invalid double: " << line << endl;//output that it is an invalid double
            }
        }
        file.close();//close the file
    } else {
        cerr << "Unable to open file\n"; // let the user know they entered the wrong filename
        return 1;//return the error code for c++ and end main
    }
    return 0; // end main by returning 0;
}
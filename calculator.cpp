//isdigit is used throughout to check if string has value 0-9
//chatgpt helped me with the idea of comparing the traversal variable to the length to check if its a valid double
#include "calculator.hpp" //include the calculator header file
#include "iostream" // include the input output stream
#include "fstream" // allow files to be opened as a stream
#include "string" // allows the string datatype for input
using namespace std; // this is for simplicity for cout and cin and cerr

//the function below turns the string input into a double
double parse_number(const string &expression) {//takes a string address as input and returns a double
    int i = 0; // this is used to go through the string like an array
    double result = 0.0;//this is the return value
    bool isNegative = false;// this is a preset boolean for future if-statement

    //both have to have conditionals because the +- is optional
    if (expression[0] == '-') { //this checks if the first element is -
        isNegative = true;//if it is the number is negative
        i++;//traverse to next item in the string
    }else if(expression[0] == '+') { //checks if the first element is +
        i++; //traverse to the next item in the string
    }
    //i looked up the isdigit function
    while (isdigit(expression[i])) {//this goes through each charater of the double before the '.' if it exists 0-9
        result = result * 10 + (expression[i] - '0');//the parentheses convert it to its integer value then the result is prevous parts of the integer portion
        i++;//this makes us go to the next element in the string
    }

    if (expression[i] == '.') {// check if there is a decimal portion of the double
        i++; //go past the . in the double
        double place = 0.1; // this keeps track of what place we are in like tenths, hundredths...
        while (isdigit(expression[i])) { // this checks if we are still working with digits
            result += (expression[i] - '0') * place; //this turns the current string value at i into an integer and multiplies it by its place which is then added to the result.
            place *= 0.1;//after each iteration move the place out 1 
            i++; // go to the next element in the string
        }
    }

    if (isNegative){//if the number is negative do the statement below
        return -result; //return the negative version of the result
    }else{//the number must be positive
        return result;//retunr the result
    }
}

//all bound checks are before the && because if statements short circuit
bool isValidDoubleString(const string& s) {//this takes a string address input and returns a bool for if it would be a valid double or not
    if(s.empty()){//makes sure the input isn't just whitespace
        return false; // if it is just whitespace return false
    }
    int i = 0;// used to iterated through the string again
    int n = s.length(); // used for bound checking
    bool hasDigits = false; //this is used to make sure there is a valid integer before the decimal

    //sign checking
    if(s[0] == '+' || s[0] == '-'){//if there is a plus or minus we need to skip that for traversal purposes
        i++;//go to next character
    }

    while(i < n && isdigit(s[i])){ //i < n is for bound checking and isdigit checks for 1-9
        hasDigits = true;//this is used for the final return statement so -.3 returns false
        i++;//this is used to make sure that the number of elements is all digits before the . 
    }

    if(i < n && s[i] == '.'){//this bound checks and then checks if there is a decimal
        i++;//go past the '.' and look at the next character
        if (i == n) { //checks if the last value is . which is invalid
            return false;//ends the function and says that the string is an invalid double
        }
        while (i < n && isdigit(s[i])){//goes through the decimal portion and insures to stay in the bounds and check if it is a digit
            i++;//go to next value
        } //this basically makes it so i == n so we can check the double using that
    }

    return hasDigits && i == n; //the value must have digits and if i does not equal n then one of the digits was not a decimal value
}



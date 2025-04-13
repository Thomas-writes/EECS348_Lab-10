//isInt is used throughout to check if string has value 0-9
//chatgpt helped me with the idea of comparing the traversal variable to the length to check if its a valid double
#include "calculator.hpp" //include the calculator header file
#include "iostream" // include the input output stream
#include "fstream" // allow files to be opened as a stream
#include "string" // allows the string datatype for input
using namespace std; // this is for simplicity for cout and cin and cerr

//uses the fact that ascii values will still work for comparison
bool isInt(char c) { // takes a char input and returns a bool
    return c >= '0' && c <= '9'; //compares c's ascii value to 0 and 9s if c is inbetween (inclusive) 0-9 returns true
}

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

    while (isInt(expression[i])) {//this goes through each charater of the double before the '.' if it exists 0-9
        result = result * 10 + (expression[i] - '0');//the parentheses convert it to its integer value then the result is prevous parts of the integer portion
        i++;//this makes us go to the next element in the string
    }

    if (expression[i] == '.') {// check if there is a decimal portion of the double
        i++; //go past the . in the double
        double place = 0.1; // this keeps track of what place we are in like tenths, hundredths...
        while (isInt(expression[i])) { // this checks if we are still working with digits
            result += (expression[i] - '0') * place; //this turns the current string value at i into an integer and multiplies it by its place which is then added to the result.
            place *= 0.1;//after each iteration move the place out 1 
            i++; // go to the next element in the string
        }
    }

    if (isNegative){//if the number is negative do the statement below
        return -result; //return the negative version of the result
    }else{//the number must be positive
        return result;//return the result
    }
}


//get the integer portion to the same length then get the decimal portion to the same length then add them character by character.
//chatgpt was used to help with the idea of adding 0s to preserve the 10s places
//chatgpt also helped with adding/subtracting character by character
string stringadd(string &s, string &s2){//takes two string address inputs and returns a string
    int i = 0; // used to traverse the first string - integer portion
    int i2 = 0; // used to traverse the second string - integer portion
    int d = 0; // used to traverse the first string - decimal portion
    int d2 = 0; // used to traverse the second string - decimal portion
    string intsub; //substring for the first string integer portion
    string intsub2; //substring for the second string integer portion
    string decsub; //substring for the first string decimal portion
    string decsub2; //substring for the second string decimal portion
    char sign1; // keeps track of the sign for first string 
    char sign2; // keeps track of the sign for second string

    if(isInt(s[0])){//checks if the first digit is a sign or not
        sign1 = '+';//if it doesn't have a sign its positive
        i++;//we want to go to the next part of the string
        s = '+' + s;//add the + to the front - this insures no indexing mistakes when we work with negatives
    }
    if(isInt(s2[0])){//checks if the first digit is a sign or not
        sign2 = '+';//if it doesn't have a sign its positive
        i2++;//we want to go to the next part of the string
        s2 = '+' + s2;//add the + to the front - this insures no indexing mistakes when we work with negatives
    }
    if(s[0] == '+' || s[0] == '-'){//if there is a plus or minus we need to skip that for traversal purposes
        sign1 = s[0];//save the sign
        i++;//go to next character
    }
    if(s2[0] == '+' || s2[0] == '-'){//if there is a plus or minus we need to skip that for traversal purposes
        sign2 = s2[0];//save the sign
        i2++;//go to next character
    }
    
    while(isInt(s[i])){//checks if the value is 0-9
        i++;//traverse the integer portion
    }
    while(isInt(s2[i2])){//checks if the value is 0-9
        i2++;//traverse the integer portion
    } 
    
    
    intsub = s.substr(1, i - 1);//since there is a sign on the front of it we start at index 1 and the length is integer length - 1 to exlude the sign
    intsub2 = s2.substr(1, i2 - 1);//since there is a sign on the front of it we start at index 1 and the length is integer length - 1 to exlude the sign

    //this is used to make sure we dont subtract values in different 10s
    if (i > i2) {//checks if string 1 has more integer places the string 2
        int diff = i - i2; // calculate the difference between the two lengths
        intsub2 = string(diff, '0') + intsub2; // generates a string of length diff of 0s and adds it to the integer substring so they are the same length
    } 
    if (i2 > i) {//checks if string 2 has more integer places the string 1
        int diff = i2 - i; // calculate the difference between the two lengths
        intsub = string(diff, '0') + intsub; // generates a string of length diff of 0s and adds it to the integer substring so they are the same length
    }

    
    if(s[i] == '.'){//if there is a decimal value 
        i++;//skip the decimal point
    }
    if(s2[i2] == '.'){//if there is a decimal value
        i2++;//skip the decimal point
    }
    d = i;//d is used to keep track of the decimal portion so we want to start it after the decimal
    d2 = i2;//d2 is used to keep track of the decimal portion so we want to start it after the decimal
    while(isInt(s[d])){//checks if the value is 0-9
        d++;//traverse the decimal value
    }
    while(isInt(s2[d2])){//checks if the value is 0-9
        d2++;//traverse the decimal value
    }

    decsub = s.substr(i, d - i);//creates the decimal substring 
    decsub2 = s2.substr(i2, d2 - i2);//creates the decimal substring 2

    if ((d - i) > (d2 - i2)) { // if decsub length > decsub2 length we need to adjust decsub2
        int diff = (d - i) - (d2 - i2); // find the difference in length of the dec substrings
        decsub2 += string(diff, '0'); // add the different in 0s to the end of decsub 2
    } else if ((d2 - i2) > (d - i)) { // if decsub2 length > decsub length we need to adjust decsub
        int diff = (d2 - i2) - (d - i); // find the difference in length of the dec substrings
        decsub += string(diff, '0');// add the different in 0s to the end of decsub
    }

    string left = intsub + decsub; //this will be the whole left number
    string right = intsub2 + decsub2; //this will be another whole number
    string result;//this is the return value
    int carry = 0;//this is how we will keep track of addition or subtraction that goes to the next place 

    if (sign1 == sign2) {//if the signs are the same we do normal addition
        for (int j = left.length() - 1; j >= 0; j--) {//we start with the smallest decimal value and move through the number
            int sum = (left[j] - '0') + (right[j] - '0') + carry;//we add the values as integers using 0 to convert ascii to binary
            carry = sum / 10; //this returns the carry since division is truncating
            result = char((sum % 10) + '0') + result;//we return the sum back to a char and add it to the left side of result
        }
        if (carry){//when we are done adding if carry is a thing we need to add it to the result
            result = '1' + result;//the carry is going to be 1 so we add that to the front of result
        } 
        
        int dotPos = result.length() - decsub.length(); //finds where the . should be
        if (dotPos < 0) {//when the decimal portion is longer than the result meaning the result is something line .004 
            result = string(-dotPos, '0') + result;//we want to add the leading 0s to the result - turn 4 into 004
            dotPos = 0;//the dot pos is 0
        }
        result.insert(dotPos, 1, '.');//inserts the . in the result string
        
        if (sign1 == '-') {//checks if the addition was with negative numbers
            result = '-' + result;//make the result negative
        }
    } else {// the signs are different so we need to do subtraction
        bool leftIsBigger = left >= right;//check which value is bigger can use ascii values
        string a;//this is a temporary value used for sthe bigger value
        string b;//this is a temporary value used for sthe smaller value

        if (leftIsBigger) {//check if the left is bigger
            a = left;//if it is we want a to be the bigger value
            b = right;//b should be the smaller value
        } else {// the right is bigger
            a = right;//a should be the bigger value
            b = left;//b should be the smaller value
        }
        for (int j = a.length() - 1; j >= 0; j--) {//we start with the smallest decimal value and move through the number
            int digitA = a[j] - '0';//get 1 digit of a as an int
            int digitB = b[j] - '0' + carry; // get 1 digit of b as an int
            if (digitA < digitB) {//think of this like subtraction by hand we pull 10 from the value to the left of where we are at
                digitA += 10;//add 10 to the current value of a so that digitA-digitB won't produce a negative value
                carry = 1;//make sure we account for the carry
            } else {
                carry = 0;// digitA is bigger than digitB so no carry is needed
            }
            result = char((digitA - digitB) + '0') + result;//do the subtraction and turn it back into a character and store on the left side of the result
        }
        int pos = 0;//we are going to remove leading 0s using this
        while (pos < result.size() - 1 && result[pos] == '0'){// make sure we don't go out of the index with the < and then check if that char is 0
            pos++;//if it is we want to add to pos so we can use substring after
        } 
        result = result.substr(pos);//get the result substring after the 0s
        if (!leftIsBigger) {//left is sign1 so if left isn't bigger we want to get the sign from sign2
            sign1 = sign2;//set sign1 to sign2 since sign2 is bigger
        }
        int dotPos = result.length() - decsub.length();//finds where the . should be
        if (dotPos < 0) {//when the decimal portion is longer than the result meaning the result is something line .004 
            result = string(-dotPos, '0') + result;//we want to add the leading 0s to the result - turn 4 into 004
            dotPos = 0;//the dot pos is 0 because its only the decimal portion
        }
        result.insert(dotPos, 1, '.');//inserts the . in the result string
        
        if (result != "0" && sign1 == '-') {// if the result is nonzero and the sign1 is negative
            result = '-' + result;//result needs to be negative also
        }
    }

    
    bool allZero = true;//this is used to check if the output is all zeros so we can format it better no +or- 0s
    for (char c : result) {//this does a loop through every character in result
        if (c != '0' && c != '.') { //if the character isn't 0 we know that the result is not all zeros
            allZero = false;//set allzeros to false
            break;//break the loop because we know its not all zeros
        }
    }
    if (allZero) {//if it is all zeros
        return "0";//return 0 instead of a misformatted 0 like -00.00
    }
    if (result.length() >= 2 && result[0] == '+' && result[1] == '.') {//short circuit if the length is less than 2 then if the first real value is . then we need to put a 0 in front
        result = "0" + result.substr(1);//add 0 to the front of a substring that starts with .
    } else if (result.length() >= 2 && result[0] == '-' && result[1] == '.') { //short circuit if the length is less than 2 then if the first real value is . then we need to put a 0 in front
        result = "-0" + result.substr(1);//add 0 to the front of a substring that starts with .
    }

    return result;//return the result we found
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

    while(i < n && isInt(s[i])){ //i < n is for bound checking and isInt checks for 1-9
        hasDigits = true;//this is used for the final return statement so -.3 returns false
        i++;//this is used to make sure that the number of elements is all digits before the . 
    }

    if(i < n && s[i] == '.'){//this bound checks and then checks if there is a decimal
        i++;//go past the '.' and look at the next character
        if (i == n) { //checks if the last value is . which is invalid
            return false;//ends the function and says that the string is an invalid double
        }
        while (i < n && isInt(s[i])){//goes through the decimal portion and insures to stay in the bounds and check if it is a digit
            i++;//go to next value
        } //this basically makes it so i == n so we can check the double using that
    }

    return hasDigits && i == n; //the value must have digits and if i does not equal n then one of the digits was not a decimal value
}



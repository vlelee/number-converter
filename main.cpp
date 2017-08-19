#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>

using namespace std;

string reverseNum(string num){
    string rNum;
    for(int i = num.length() - 1; i > -1; i--){
        rNum.push_back(num[i]);
    }
    return rNum;
}

string to_string(int num){
    ostringstream convert;
    convert << num;
    return convert.str();
}

char getHexLetter(int num){
    char letter[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    return letter[num - 10];
}

int getDecLetter(char l){
    char letter[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    for(int i = 0; i < 6; i++){
        if(l == letter[i]){
            return 10 + i;
        }
    }
    cout << "Incorrect Hex Letter found. Results will be incorrect." << endl;
    return 0;
}

//ConvertToDec function takes a string number (binary or hexadecimel) and returns an integer value
int ConvertToDec(string num, int power){
    int acc = 0;
    if(power == 2){
        for(int i = 0; i < num.length(); i++){
            int bin_num = (int)num[i] - '0';
            acc += (pow(power, (num.length() - 1) - i)) * bin_num;
        }
    }

    if(power == 16){
        for(int i = 0; i < num.length(); i++){
            int hex_num;
            if(isdigit(num[i])){
                hex_num = (int)num[i] - '0';
            }
            else if(isalpha(num[i])){
                hex_num = getDecLetter(num[i]);

            }
            acc += (pow(power, (num.length() - 1) - i)) * hex_num;
        }
    }
    return acc;
}

//DecToBin function takes a decimal int number and returns a binary string number
string DecToBin(int dec_num){
    string answer;
    int remainder;
    if(dec_num < 0) {
        return "No negative decimal numbers";
    }

    while(dec_num > 0){
        remainder = dec_num % 2;
        dec_num = dec_num / 2;

        if(remainder == 0){
            answer.push_back('0');
        }
        else{
            answer.push_back('1');
        }
    }

    while(answer.length() < 4 || ((answer.length() > 4) && (answer.length() < 8))){
        answer.push_back('0');
    }

    return reverseNum(answer);
}

//DecToHex function takes a decimal int number and returns a hexadecimal string number
string DecToHex(int dec_num){
    string answer;
    if(dec_num > 15){
        while(dec_num > 0){
            int remainder = dec_num % 16;
            dec_num = dec_num / 16;
            if( remainder > 9){
                char letter = getHexLetter(remainder);
                answer.push_back(letter);
            }
            else{
                answer.push_back('0' + remainder);
            }
        }
        return reverseNum(answer);
    }
    else{
        if(dec_num > 9){
            answer.push_back(getHexLetter(dec_num));
            return answer;
        }
    }
    return to_string(dec_num);
}

//BinToDec function takes a binary string number, converts it to decimal and returns an integer value
int BinToDec(string binary_num){
    return ConvertToDec(binary_num, 2);
}

//HexToDec function takes a hexadecimal string number, converts it to decimal and returns an integer value
int HexToDec(string hex_num){
    return ConvertToDec(hex_num, 16);
}

//BinToHex function takes a binary string number, converts it to decimal then to hexadecimal, and returns a string number
string BinToHex(string binary_num){
    int dec = BinToDec(binary_num);
    return DecToHex(dec);

}

//HexToBin function takes a hex string number, converts it to decimal then to binary, and returns a string number
string HexToBin(string hex_num){
    int dec = HexToDec(hex_num);
    return DecToBin(dec);
}

//CheckBinary function checks binary input for numbers other than 1 and 0, returns false if found, otherwise true
bool CheckBinary(string input){
    for(int i = 0; i < input.length(); i++){
        int digit = (int)input[i] - '0';
        if(digit != 0 && digit != 1)
            return false;
    }
    return true;
}

//CheckNegative function checks input number for negative sign, returns false if found, otherwise true
bool CheckNegative(string input){
    if(input[0] == '-')
        return false;
    return true;
}

//CheckStrInput function takes the command, checks for errors and returns empty if error, otherwise returns str_input
string CheckStrInput(int command){
    cout << "Please enter a number: ";
    string str_input;
    cin >> str_input;
    cout << endl;
    if(!CheckNegative(str_input)){
        cout << "Error: no negative values. Return to Main Menu." << endl;
        return "";
    }

    if(command < 2){
        bool flag = CheckBinary(str_input);
        if(!flag){
            cout << "Flag: " << flag << " Error: incorrect binary format." << endl;
            return "";
        }
    }

    return str_input;
}

//CheckIntInput function takes command input, checks for error, if found return 0, else returns num_input 
int CheckIntInput(int command){
    cout << "Please enter a number: ";
    int num_input;
    cin >> num_input;
    cout << endl;
    if(num_input < 0){
        cout << "Error: no negative values." << endl;
        return 0;
    }
    return num_input;
}

//ExecuteCommand function takes command input, finds the function matching command, and returns result
void ExecuteCommand(int command){
    string result = "";
    switch(command){
    case 0 : {
        cout << "Binary to Decimal Conversion" << endl;
        string input = CheckStrInput(command);
        result = to_string(BinToDec(input));
        break;
    }
    case 1 : {
        cout << "Binary to Hexadecimal Conversion" << endl;
        string input = CheckStrInput(command);
        result = BinToHex(input);
        break;
    }
    case 2 : {
        cout << "Decimal to Binary Conversion" << endl;
        int input = CheckIntInput(command);
        result = DecToBin(input);
        break;
    }
    case 3 : {
        cout << "Hexadecimal to Decimal Conversion" << endl;
        string input = CheckStrInput(command);
        result = to_string(HexToDec(input));
        break;
    }
    case 4 : {
        cout << "Decimal to Hexadecimal Conversion" << endl;
        int input = CheckIntInput(command);
        result = DecToHex(input);
        break;
    }
    case 5 : {
        cout << "Hexadecimal to Binary Conversion" << endl;
        string input = CheckStrInput(command);
        result = HexToBin(input);
        break;
    }

    }

    cout << "\n" << result << endl;
}

//MenuCommand function shows the menu and sends command input to ExecuteCommand function
void MenuCommand(){
    int command = 0;
    while(command != 6){
        cout << "\nEnter a number command from the menu \n0 Binary to Decimal \n1 Binary to Hexadecimal\n2 Decimal to Binary\n3 Hexadecimal to Decimal";
        cout << "\n4 Decimal to Hexadecimal\n5 Hexadecimal to Binary\n6 Quit" << endl;

        cin >> command;
        if((command > -1) && (command < 6)){
            ExecuteCommand(command);
        }
    }
}



int main()
{
    MenuCommand();
    return 0;
}

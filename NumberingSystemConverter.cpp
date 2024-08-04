// Name: Ziad Elsayed Mohamed
#include<bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

// Converts a floating-point number to a different base
string ConvertToX_Float(ld Number, int base) {
    string convert = "";
    ld result, reminder;
    ll carry;
    map<ld, int> checker; // Map to check if the fractional part has been seen before
    result = Number * base;
    
    while (true) {
        carry = floor(result); // Integer part of the result
        reminder = result - carry; // Fractional part of the result
        reminder *= 10; // Scale up for better precision
        reminder = round(reminder); // Round to nearest integer
        reminder /= 10; // Scale back down
        
        Number *= base; // Update Number for next iteration
        
        char ch = carry + '0'; // Convert carry to character
        if (carry > 9) // Handle values greater than 9 (hexadecimal)
            ch = carry + '7';
        
        if (checker[reminder]) { // Check if this fractional part has been seen before
            break;
        }
        checker[reminder]++;
        convert += ch; // Append character to the result
        
        if (reminder == 0) // Terminate if the fractional part is zero
            break;
        
        result = reminder * base; // Update result for next iteration
    }
    return convert;
} 

// Converts an integer to a different base
string ConvertToX_Int(ll Number, int base) {
    string convert = "";
    ll result, reminder;
    
    while (true) {
        result = Number / base; // Integer division
        reminder = Number % base; // Remainder
        
        Number /= base; // Update Number for next iteration
        
        char ch = reminder + '0'; // Convert remainder to character
        if (reminder > 9) // Handle values greater than 9 (hexadecimal)
            ch = reminder + '7';
        
        convert += ch; // Append character to the result
        
        if (result == 0) // Terminate if the result is zero
            break;
    }
    
    reverse(convert.begin(), convert.end()); // Reverse the result string
    return convert;
} 

// Converts a floating-point number from a specific base to decimal
ld ConvertToDecimal_Float(string StrNumber, string TypeFrom) {
    long double FloatNumber = 0;
    
    if (TypeFrom == "A" or TypeFrom == "a") {
        // Base 10 (Decimal)
        FloatNumber = stold(StrNumber) / (powl(10, StrNumber.length()));
    }
    else if (TypeFrom == "B" or TypeFrom == "b") {
        // Base 2 (Binary)
        ll base = 2, sum = 0;
        for (int i = 1; i <= StrNumber.length(); i++) {
            FloatNumber += pow(base, -i) * (StrNumber[i - 1] - '0');
        }
    }
    else if (TypeFrom == "C" or TypeFrom == "c") {
        // Base 8 (Octal)
        ll base = 8, sum = 0;
        for (int i = 1; i <= StrNumber.length(); i++) {
            FloatNumber += pow(base, -i) * (StrNumber[i - 1] - '0');
        }
    }
    else if (TypeFrom == "D" or TypeFrom == "d") {
        // Base 16 (Hexadecimal)
        vector<int> hexa;
        for (int i = 0; i < StrNumber.length(); i++) {
            int check = StrNumber[i] - '0';
            if (check > 9) 
                check = StrNumber[i] - '7'; // Convert 'A'-'F' to 10-15
            hexa.push_back(check);
        }
        ll base = 16, sum = 0;
        for (int i = 1; i <= StrNumber.length(); i++) {
            FloatNumber += pow(base, -i) * (hexa[i - 1]);
        }
    }
    return FloatNumber;
}

// Converts an integer from a specific base to decimal
ll ConvertToDecimal_Int(string StrNumber, string TypeFrom) {
    ll Number;
    
    if (TypeFrom == "A" or TypeFrom == "a") {
        // Base 10 (Decimal)
        Number = stol(StrNumber);
    }
    else if (TypeFrom == "B" or TypeFrom == "b") {
        // Base 2 (Binary)
        ll base = 2, sum = 0;
        for (int i = StrNumber.length() - 1, j = 0; i >= 0; i--, j++) {
            sum += powl(base, i) * (StrNumber[j] - '0');
        }
        Number = sum;
    }
    else if (TypeFrom == "C" or TypeFrom == "c") {
        // Base 8 (Octal)
        ll base = 8, sum = 0;
        for (int i = StrNumber.length() - 1, j = 0; i >= 0; i--, j++) {
            sum += powl(base, i) * (StrNumber[j] - '0');
        }
        Number = sum;
    }
    else if (TypeFrom == "D" or TypeFrom == "d") {
        // Base 16 (Hexadecimal)
        vector<int> hexa;
        for (int i = 0; i < StrNumber.length(); i++) {
            int check = StrNumber[i] - '0';
            if (check > 9) 
                check = StrNumber[i] - '7'; // Convert 'A'-'F' to 10-15
            hexa.push_back(check);
        }
        ll base = 16, sum = 0;
        for (int i = StrNumber.length() - 1, j = 0; i >= 0; i--, j++) {
            sum += powl(base, i) * (hexa[j]);
        }
        Number = sum;
    }
    return Number;
}

signed main() {
    string TypeFrom, TypeTo, StrNumber, FirstPart, SecondPart;
    cout << "Welcome to our program\n";
    
    while (true) {
        ll IntNumber;
        ld FloatNumber;
        cout << "Please enter the type of number system that you want to convert (from/to)\n";
        cout << "A) Decimal    B) Binary\n";
        cout << "C) Octal      D) Hexadecimal\n";
        cout << "E) Exit\nFrom: ";
        cin >> TypeFrom;

        if (TypeFrom == "E" or TypeFrom == "e")
            break;

        cout << "To: ";
        cin >> TypeTo;
        cout << "Enter the number: ";
        cin >> StrNumber;
        
        int DecimalPoint;
        bool exist = false;
        
        // Find the position of the decimal point if it exists
        for (int i = 0; i < StrNumber.length(); i++) {
            if (StrNumber[i] == '.') {
                DecimalPoint = i;
                exist = true;
                break;
            }
        }
        
        // Convert integer and fractional parts to decimal
        IntNumber = (DecimalPoint != 0 ? ConvertToDecimal_Int(StrNumber.substr(0, DecimalPoint), TypeFrom) : 0);
        FloatNumber = (exist ? ConvertToDecimal_Float(StrNumber.substr(DecimalPoint + 1, StrNumber.length() - DecimalPoint - 1), TypeFrom) : 0);
        
        if (TypeTo == "A" or TypeTo == "a") {
            // Convert to decimal
            cout << "Decimal number = " << fixed << setprecision(6) << IntNumber + FloatNumber << endl;
        }
        else if (TypeTo == "B" or TypeTo == "b") {
            // Convert to binary
            cout << "Binary number = ";
            FirstPart = ConvertToX_Int(IntNumber, 2);
            SecondPart = (exist ? ConvertToX_Float(FloatNumber, 2) : "");
            cout << FirstPart << '.' << SecondPart << endl;
        }
        else if (TypeTo == "C" or TypeTo == "c") {
            // Convert to octal
            cout << "Octal number = ";
            FirstPart = ConvertToX_Int(IntNumber, 8);
            SecondPart = (exist ? ConvertToX_Float(FloatNumber, 8) : "");
            cout << FirstPart << '.' << SecondPart << endl;
        }
        else if (TypeTo == "D" or TypeTo == "d") {
            // Convert to hexadecimal
            cout << "Hexadecimal number = ";
            FirstPart = ConvertToX_Int(IntNumber, 16);
            SecondPart = (exist ? ConvertToX_Float(FloatNumber, 16) : "");
            cout << FirstPart << '.' << SecondPart << endl;
        }
        else 
            cout << "Invalid choice!\nTry again\n";
    }
}

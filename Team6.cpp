#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
using namespace std;

   // =====Healper Functions=====//     "Habiba"
class BigInt {
string number;    // Stores the number as a string
bool isNegative;  // True if number is negative

// Remove unnecessary leading zeros from the number string
void removeLeadingZeros() {
// TODO: Implement this function
if(number.empty()){
number = "0";
isNegative = false;
return;
}
size_t i = 0;
while(i< number.size() && number[i]=='0')
i++;
if(i == number.size()){
number = "0";
isNegative = false;
return;
}

if(i>0) number.erase(0,i);

}

// Compare absolute values of two BigInts (ignore signs)
// Returns: 1 if |this| > |other|, 0 if equal, -1 if |this| < |other|
int compareMagnitude(const BigInt& other) const {
// TODO: Implement this function
size_t i1 = 0;
while (i1 < number.size() && number[i1] == '0')
i1++;
size_t i2 = 0;
while (i2< other.number.size()&& other.number[i2] == '0')
i2++;

size_t length1 =(i1 >= number.size()) ? 0 :( number.size() -i1);
size_t length2 = (i2 >= other.number.size()) ? 0 : (other,number.size() -i2);


if(length1 == 0 && length2 == 0)
return 0;

if( length1 != length2)
return (length1 > length2) ? 1 : -1;

for(size_t k = 0; k< number.size(); k++){
char c1 = number[i1 + k];
char c2 = other.number[i2 + k];
if (c1>c2)
return 1;
if(c1<c2)
return -1;
}

return 0;
}
//========Constructors , destructor //    "kareem" 

public:
// Default constructor - initialize to zero
BigInt() {
// TODO: Implement this constructor
number = "0";
isNegative = false;
}

// Constructor from 64-bit integer
BigInt(int64_t value) {
// TODO: Implement this constructor
if (!value) // if value = 0
{
number = "0";
isNegative = false;
return;
}
if(value < 0) // if value is negative
{
isNegative = true;
value = -value;
}
else // number is positive
{
isNegative = false;
}
number = to_string(value);

}

// Constructor from string representation
BigInt(const string& str) {
// TODO: Implement this constructor
if((str.empty()) || (str == "0"))
{
number = "0";
isNegative = false;
return;
}
if(str[0] == '-')
{
isNegative = true;
number = str.substr(1);
}
else if(str[0] == '+')
{
isNegative = false;
number = str.substr(1);
}
else
{
isNegative = false;
number = str;
}

removeLeadingZeros();
}

// Copy constructor
BigInt(const BigInt& other) {
// TODO: Implement this constructor
number = other.number;
isNegative = other.isNegative;
}

// Destructor
~BigInt() {
// TODO: Implement if needed
cout << "Object is Destroyed" << endl;
}

// Assignment operator           "Habiba" 
BigInt& operator=(const BigInt& other) {
// TODO: Implement this operator
if(this != &other){
number = other.number;
isNegative = other.isNegative;

removeLeadingZeros();
if(number == "0")
isNegative = false;
}
return *this;
}
// Unary negation operator (-x)
BigInt operator-() const {
BigInt result;
// TODO: Implement negation logic
result = *this;
if(result.number != "0"){
result. isNegative = !result.isNegative;
}
return result;
}

// Unary plus operator (+x)
BigInt operator+() const {
BigInt result;
// TODO: Implement this operator
return *this;
return result;
}

    //Arithmatic assignment Operators//         "Ahmed Ammar"
    //Arithmatic assignment Operators//         "Ahmed Rasoul"
// Addition assignment operator (x += y)
         // TODO: Implement this operator
    BigInt& operator+=(const BigInt& other)
    {
        if (isNegative == other.isNegative) {
            string a = number;
            string b = other.number;

            if (a.size() < b.size())
            {
                swap(a, b);
            }

            reverse(a.begin(), a.end());
            reverse(b.begin(), b.end());

            string result = "";
            int carry = 0;

            for (size_t i = 0; i < a.size(); i++) {
                int digitA = a[i] - '0';
                int digitB = 0;
                if (i < b.size()) {
                    digitB = b[i] - '0';
                }

                int sum = digitA + digitB + carry;
                result.push_back((sum % 10) + '0');
                carry = sum / 10;
            }

            if (carry)
            {
                result.push_back(carry + '0');
            }

            reverse(result.begin(), result.end());
            number = result;
        }
        else
        {
            *this -= (-other);
        }
        removeLeadingZeros();
return *this;
}

// Subtraction assignment operator (x -= y)
BigInt& operator-=(const BigInt& other) {
        // TODO: Implement this operator
        if (isNegative != other.isNegative)
        {
            *this += (-other);
            return *this;
        }
        int cmp = compareMagnitude(other);
        if (cmp == 0) {
            number = "0";
            isNegative = false;
            return *this;
        }
        const string* bigger;
        const string* smaller;
        bool resultNegative;

        if (cmp >= 0) {
            bigger = &number;
            smaller = &other.number;
            resultNegative = isNegative;
        }
        else {
            bigger = &other.number;
            smaller = &number;
            resultNegative = !isNegative;
        }

        string a = *bigger, b = *smaller;

        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());

        string result = "";
        int borrow = 0;

        for (size_t i = 0; i < a.size(); i++) {
            int digitA = a[i] - '0' - borrow;
            int digitB = 0;
            if (i < b.size())
            {
                digitB = b[i] - '0';
            }

            if (digitA < digitB)
            {
                digitA += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }

            int dif = digitA - digitB;
            result.push_back(dif + '0');
        }

        reverse(result.begin(), result.end());
        number = result;
        isNegative = resultNegative;
        removeLeadingZeros();

return *this;
}

// Multiplication assignment operator (x *= y)
BigInt& operator*=(const BigInt& other) {
        // TODO: Implement this operator
        string first = number;
        string second = other.number;

        if (first == "0" || second == "0")
        {
            number = "0";
            isNegative = false;
            return *this;
        }
        int n = first.size();
        int m = second.size();
        string result(n + m, '0');

        reverse(first.begin(), first.end());
        reverse(second.begin(), second.end());

        for (int i = 0; i < n; i++) {
            int carry = 0;
            int digitA = first[i] - '0';

            for (int j = 0; j < m; j++) {
                int digitB = second[j] - '0';

                int temp = (result[i + j] - '0') + digitA * digitB + carry;
                result[i + j] = (temp % 10) + '0';
                carry = temp / 10;
            }

            if (carry > 0) {
                result[i + m] += carry;
            }
        }

        reverse(result.begin(), result.end());
        number = result;

        isNegative = (isNegative != other.isNegative);
        removeLeadingZeros();

return *this;
}

// Division assignment operator (x /= y)
BigInt& operator/=(const BigInt& other) {
        // TODO: Implement this operator
        if (other.number == "0") {
            throw std::runtime_error("Division by zero"); 
        }

        bool resultNegative = (this->isNegative != other.isNegative);

        BigInt dividend = *this;
        dividend.isNegative = false;
        BigInt divisor = other;
        divisor.isNegative = false;

        if (dividend < divisor) {
            number = "0";
            isNegative = false;
            return *this;
        }

        string result = "";
        BigInt current("0");

        for (char digit : dividend.number) {
            current *= 10;
            current += BigInt(digit - '0');
            int count = 0;

            while (current >= divisor) {
                current -= divisor;
                count++;
            }
            result.push_back(count + '0');
        }
        number = result;
        removeLeadingZeros();
        isNegative = (number != "0") ? resultNegative : false; 
return *this;
}

// Modulus assignment operator (x %= y)
BigInt& operator%=(const BigInt& other) {
        // TODO: Implement this operator
        if (other.number == "0") {
            throw std::runtime_error("Modulo by zero");
        }

        bool resultNegative = this->isNegative;

        BigInt dividend = *this;
        dividend.isNegative = false;
        BigInt divisor = other;
        divisor.isNegative = false;

        if (dividend < divisor) {
            number = dividend.number;
            isNegative = resultNegative;
            return *this;
        }

        BigInt quotient = dividend;
        quotient /= divisor;
        BigInt temp = quotient;
        BigInt remainder = dividend;
        temp *= divisor;
        remainder -= temp;
        *this = remainder;
        if (number != "0") {
            isNegative = resultNegative;
        }
        else {
            isNegative = false;
        }
return *this;
}

// Increment and decrement operators //          "Elham"


BigInt& operator++() {
    
    *this += BigInt(1);
    return *this;  
}


BigInt operator++(int) {
    BigInt temp(*this);   
    *this += BigInt(1);   
    return temp;          
}


BigInt& operator--() {
   
    *this -= BigInt(1);
    return *this;  
}


BigInt operator--(int) {
    BigInt temp(*this);   
    *this -= BigInt(1);   // Decreaseing 1
    return temp;          
}
//conversion and stream operators //           "Muhammed"
// Convert BigInt to string representation
string toString() const {
return (isNegative && number != "0" ? "-" : "") + number;

}

// Output stream operator (for printing)
friend ostream& operator<<(ostream& os, const BigInt& num) {
os << num.toString();
return os;
}

// Input stream operator (for reading from input)
friend istream& operator>>(istream& is, BigInt& num) {
string str;
is >> str;
num = BigInt(str);
return is;
}
// Friend declarations for comparison operators
    friend bool operator==(const BigInt& lhs, const BigInt& rhs);
    friend bool operator<(const BigInt& lhs, const BigInt& rhs);
    friend bool operator>(const BigInt& lhs, const BigInt& rhs);
    friend bool operator!=(const BigInt& lhs, const BigInt& rhs);
    friend bool operator<=(const BigInt& lhs, const BigInt& rhs);
    friend bool operator>=(const BigInt& lhs, const BigInt& rhs);
    };


//============Binary arithmatic operators=============//         "Ahmed Rasoul" 
//============Binary arithmatic operators=============//         "Ahmed Ammar" 
// Binary addition operator (x + y)
BigInt operator+(BigInt lhs, const BigInt& rhs) {
lhs += rhs;
BigInt result= lhs;
return result;
}

// Binary subtraction operator (x - y)
BigInt operator-(BigInt lhs, const BigInt& rhs) {
lhs -= rhs;
BigInt result = lhs;
return result;
}

// Binary multiplication operator (x * y)
BigInt operator*(BigInt lhs, const BigInt& rhs) {
lhs *= rhs;
BigInt result = lhs;
return result;
}

// Binary division operator (x / y)
BigInt operator/(BigInt lhs, const BigInt& rhs) {
lhs /= rhs;
BigInt result = lhs;
return result;
}

// Binary modulus operator (x % y)
BigInt operator%(BigInt lhs, const BigInt& rhs) {
lhs %= rhs;
BigInt result = lhs;
return result;
}
//=================Comparison Operators=================//        "Elham"


bool operator==(const BigInt& lhs, const BigInt& rhs) {
    return (lhs.isNegative == rhs.isNegative && lhs.number == rhs.number);
}

// Inequality comparison operator (x != y)
bool operator!=(const BigInt& lhs, const BigInt& rhs) {
    return !(lhs == rhs);
}

// Less-than comparison operator (x < y)
bool operator<(const BigInt& lhs, const BigInt& rhs) {
    // if their signs are differnt
    if (lhs.isNegative != rhs.isNegative)
        return lhs.isNegative; 

    // in case they are -
    if (lhs.isNegative && rhs.isNegative)
        return rhs.compareMagnitude(lhs) > 0; 

    // they are +
    return lhs.compareMagnitude(rhs) < 0;
}

// 
bool operator<=(const BigInt& lhs, const BigInt& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

// Greater-than comparison operator (x > y)
bool operator>(const BigInt& lhs, const BigInt& rhs) {
    return !(lhs <= rhs);
}

// Greater-than-or-equal comparison operator (x >= y)
bool operator>=(const BigInt& lhs, const BigInt& rhs) {
    return !(lhs < rhs);
}
//=================Test Program=================//            "muhammed"
int main() {
cout << "=== BigInt Class Test Program ===" << endl << endl;
cout << "NOTE: All functions are currently empty." << endl;
cout << "Your task is to implement ALL the functions above." << endl;
cout << "The tests below will work once you implement them correctly." << endl << endl;


   // Test 1: Constructors and basic output
   cout << "1. Constructors and output:" << endl;
   BigInt a(12345);              // Should create BigInt from integer
   BigInt b("-67890");           // Should create BigInt from string
   BigInt c("0");                // Should handle zero correctly
   BigInt d = a;                 // Should use copy constructor
   cout << "a (from int): " << a << endl;        // Should print "12345"
   cout << "b (from string): " << b << endl;     // Should print "-67890"
   cout << "c (zero): " << c << endl;            // Should print "0"
   cout << "d (copy of a): " << d << endl << endl; // Should print "12345"

   // Test 2: Arithmetic operations
   cout << "2. Arithmetic operations:" << endl;
   cout << "a + b = " << a + b << endl;          // Should calculate 12345 + (-67890)
   cout << "a - b = " << a - b << endl;          // Should calculate 12345 - (-67890)
   cout << "a * b = " << a * b << endl;          // Should calculate 12345 * (-67890)
   cout << "b / a = " << b / a << endl;          // Should calculate (-67890) / 12345
   cout << "a % 100 = " << a % BigInt(100) << endl << endl; // Should calculate 12345 % 100

   // Test 3: Relational operators
   cout << "3. Relational operators:" << endl;
   cout << "a == d: " << (a == d) << endl;       // Should be true (12345 == 12345)
   cout << "a != b: " << (a != b) << endl;       // Should be true (12345 != -67890)
   cout << "a < b: " << (a < b) << endl;         // Should be false (12345 < -67890)
   cout << "a > b: " << (a > b) << endl;         // Should be true (12345 > -67890)
   cout << "c == 0: " << (c == BigInt(0)) << endl << endl; // Should be true (0 == 0)

   // Test 4: Unary operators and increments
   cout << "4. Unary operators and increments:" << endl;
   cout << "-a: " << -a << endl;                 // Should print "-12345"
   cout << "++a: " << ++a << endl;               // Should increment and print "12346"
   cout << "a--: " << a-- << endl;               // Should print "12346" then decrement
   cout << "a after decrement: " << a << endl << endl; // Should print "12345"

   // Test 5: Large number operations
   cout << "5. Large number operations:" << endl;
   BigInt num1("12345678901234567890");
   BigInt num2("98765432109876543210");
   cout << "Very large addition: " << num1 + num2 << endl;
   cout << "Very large multiplication: " << num1 * num2 << endl << endl;

   // Test 6: Edge cases and error handling
   cout << "6. Edge cases:" << endl;
   BigInt zero(0);
   BigInt one(1);
   try {
       BigInt result = one / zero;               // Should throw division by zero error
       cout << "Division by zero succeeded (unexpected)" << endl;
   } catch (const runtime_error& e) {
       cout << "Division by zero correctly threw error: " << e.what() << endl;
   }
   cout << "Multiplication by zero: " << one * zero << endl;        // Should be "0"
   cout << "Negative multiplication: " << BigInt(-5) * BigInt(3) << endl;  // Should be "-15"
   cout << "Negative division: " << BigInt(-10) / BigInt(3) << endl;       // Should be "-3"
   cout << "Negative modulus: " << BigInt(-10) % BigInt(3) << endl;        // Should be "-1"
   return 0;
}

         
 


#include <iostream>
#include <string>
#include <cstdint>
using namespace std;
    // =====Healper Functions=====//     "Habiba"
class BigInt {
    string number;    // Stores the number as a string
    bool isNegative;  // True if number is negative
   
    // Remove unnecessary leading zeros from the number string
    void removeLeadingZeros() {
        // TODO: Implement this function
    }

    // Compare absolute values of two BigInts (ignore signs)
    // Returns: 1 if |this| > |other|, 0 if equal, -1 if |this| < |other|
    int compareMagnitude(const BigInt& other) const {
        // TODO: Implement this function
        return 0;
    }
    //========Constructors , destructor //    "kareem" 

public:
    // Default constructor - initialize to zero
    BigInt() {
        // TODO: Implement this constructor
    }

    // Constructor from 64-bit integer
    BigInt(int64_t value) {
        // TODO: Implement this constructor
    }

    // Constructor from string representation
    BigInt(const string& str) {
        // TODO: Implement this constructor
    }

    // Copy constructor
    BigInt(const BigInt& other) {
        // TODO: Implement this constructor
    }

    // Destructor
    ~BigInt() {
        // TODO: Implement if needed
    }

    // Assignment operator           "Habiba" 
    BigInt& operator=(const BigInt& other) {
        // TODO: Implement this operator
        return *this;
    }

    // Unary negation operator (-x)
    BigInt operator-() const {
        BigInt result;
        // TODO: Implement negation logic
        return result;
    }

    // Unary plus operator (+x)
    BigInt operator+() const {
        BigInt result;
        // TODO: Implement this operator
        return result;
    }

    //Arithmatic assignment Operators//         "Ahmed Ammar"
    // Addition assignment operator (x += y)
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
        const string& bigger = (cmp >= 0) ? number : other.number;
        const string& smaller = (cmp >= 0) ? other.number : number;
        bool resultNegative = (cmp >= 0) ? isNegative : !isNegative;

        string a = bigger, b = smaller;

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
        isNegative = (number != "0") ? resultNegative : false;
        return *this;
    }

      // Increment and decrement operators //          "Elham"
    // Pre-increment operator (++x)
    BigInt& operator++() {
        // TODO: Implement this operator
        return *this;
    }

    // Post-increment operator (x++)
    BigInt operator++(int) {
        BigInt temp;
        // TODO: Implement this operator
        return temp;
    }

    // Pre-decrement operator (--x)
    BigInt& operator--() {
        // TODO: Implement this operator
        return *this;
    }

    // Post-decrement operator (x--)
    BigInt operator--(int) {
        BigInt temp;
        // TODO: Implement this operator
        return temp;
    }
      //conversion and stream operators //           "Muhammed"
    // Convert BigInt to string representation
    string toString() const {
        // TODO: Implement this function
        return "";
    }

    // Output stream operator (for printing)
    friend ostream& operator<<(ostream& os, const BigInt& num) {
        // TODO: Implement this operator
        return os;
    }

    // Input stream operator (for reading from input)
    friend istream& operator>>(istream& is, BigInt& num) {
        // TODO: Implement this operator
        return is;
    }

    // Friend declarations for comparison operators
    friend bool operator==(const BigInt& lhs, const BigInt& rhs){

    }
    friend bool operator<(const BigInt& lhs, const BigInt& rhs){

    }
};

//============Binary arithmatic operators=============//         "Ahmed Rasoul" 
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
// Equality comparison operator (x == y)
bool operator==(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    return false;
}

// Inequality comparison operator (x != y)
bool operator!=(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    return false;
}

// Less-than comparison operator (x < y)
bool operator<(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    return false;
}

// Less-than-or-equal comparison operator (x <= y)
bool operator<=(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    return false;
}

// Greater-than comparison operator (x > y)
bool operator>(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    return false;
}

// Greater-than-or-equal comparison operator (x >= y)
bool operator>=(const BigInt& lhs, const BigInt& rhs) {
    // TODO: Implement this operator
    return false;
}
//=================Test Program=================//            "muhammed"
int main() {
    cout << "=== BigInt Class Test Program ===" << endl << endl;
    cout << "NOTE: All functions are currently empty." << endl;
    cout << "Your task is to implement ALL the functions above." << endl;
    cout << "The tests below will work once you implement them correctly." << endl << endl;

    /*
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
    */

    return 0;
}
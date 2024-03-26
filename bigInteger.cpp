#include <iostream>
#include <string>
#include <cstring>

using namespace std;

// char to int
int choi(char num) {
    int result = int(num) - '0';
    return result;
}

// 숫자 비교
int comparison(string first, string second) {
    if (first.compare(second) == 0) {
        return 0;   
    } else {
        for (int i = 0; i < first.length(); i++) {
            if (choi(first[i]) > choi(second[i])) {
                return 1;
            } else if (choi(first[i]) < choi(second[i])) {
                return -1;
            }
        }
    }
}

int main() {
    string firstNumber, secondNumber, sum, sub;
    int sumNumber = 0;
    int subNumber = 0;
    int carry = 0;
    cout << "First Number\t>> ";
    cin >> firstNumber;
    cout << "Second Number\t>> ";
    cin >> secondNumber;

    // 숫자 자리 수 맞추기
    if (firstNumber.length() > secondNumber.length()) {
        int num = firstNumber.length() - secondNumber.length();
        for (int i = 0; i < num; i++) {
            secondNumber = secondNumber.insert(0, "0");
        }
    } else if(firstNumber.length() < secondNumber.length()) {
        int num = secondNumber.length() - firstNumber.length();
        for (int i = 0; i < num; i++) {
            firstNumber = firstNumber.insert(0, "0");
        }
    }

    // 큰 수를 first로, 작은 수를 second로 옮기기
    if (comparison(firstNumber, secondNumber) == -1) {

        string tmp = firstNumber;
        firstNumber = secondNumber;
        secondNumber = tmp;
        sub = "-";
    }

    // 덧셈
    for (int i = firstNumber.length()-1; i >= 0; i--) {
        sumNumber = choi(firstNumber[i]) + choi(secondNumber[i]) + carry;
        carry = 0;
        if (sumNumber >= 10) {
            carry = 1;
            sumNumber -= 10;
        }
        sum = sum.insert(0, to_string(sumNumber));
        if (i == 0 && carry == 1) {
        sum = sum.insert(0, "1");
        }
        sumNumber = 0;
    }
    
    // 뺄셈
    // 빌려오는 수 생각하기. 
    // 큰 수에서 빼고 상황에 따라 - 붙이기.
    // 큰 수 -1, 마지막 +10 후 다시 계산.
    for (int i = firstNumber.length()-1; i >= 0; i--) {
        if (choi(firstNumber[i]) < choi(secondNumber[i])) {
            carry = firstNumber[i-1];
            carry -= 1;
            firstNumber[i-1] = char(carry);
            subNumber = choi(firstNumber[i]) - choi(secondNumber[i]) + 10;
        } else {
            subNumber = choi(firstNumber[i]) - choi(secondNumber[i]);
        }

        if (sub[0] == '-') {
            sub = sub.insert(1, to_string(subNumber));
        } else {
            sub = sub.insert(0, to_string(subNumber));
        }

        if (i == 0 && subNumber == 0) {
            if (sub[0] == '-') {
                while (sub[1] == '0') {
                    sub = sub.erase(1, 1);
                }
            } else {
                while (sub[0] == '0' && sub.length() > 1) {
                    sub = sub.erase(0, 1);
                }
            }   
        }
    }
    
    // sum, sub 출력
    cout << "Sum\t\t>> " << sum << endl;
    cout << "Sub\t\t>> " << sub << endl;
    return 0;
}
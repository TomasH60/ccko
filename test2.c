#include <stdio.h>

int main() {
    int hours, grossPay, taxes;
    
    int payRate = 12;
    double netPay;

    
    scanf("%d", &hours);
    if (hours > 40) {
        grossPay = 480 + (18 * (hours - 40));
    } else {
        grossPay = 12 * hours;
    }
    if (grossPay <= 300 ) {
        netPay = grossPay * 0.85;
        taxes = 15;
    } else if ( grossPay > 300 && grossPay <= 450) 
    {
        netPay = grossPay * 0.8;
        taxes = 20;
    } else {
        netPay = grossPay * 0.75;
        taxes = 25;
    }
    printf("Working hours: %d\nGross pay: %d\nTax rate: %d\nNet pay: %g", hours, grossPay, taxes, netPay);
    return 0;
}
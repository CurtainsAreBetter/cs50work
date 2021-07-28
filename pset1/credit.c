#include <cs50.h>
#include <stdio.h>
#include <string.h>

int long_length(long n);
int get_digit(long n, int length);
bool checksum(long cnumber);
long lten(int digits);

int main(void)
{
    string creditor;
    long card = get_long("Number: ");
    int nlen = long_length(card);
    // Got worried about putting the correct amount of zeros so made it
    // more clear with lten()
    long ax = lten(13);  // amex
    long lv = lten(15);  // long visa
    long sv = lten(12);  // short visa
    long mc = lten(14);  // mastercard
    if (nlen == 15 && ((card >= 34 * ax && card < 35 * ax) || (card >= 37 * ax && card < 38 * ax)))
    {
        creditor = "AMEX";
    }
    else if ((nlen == 13 || nlen == 16) && ((card >= 4 * sv && card < 5 * sv) || (card >= 4 * lv && card < 5 * lv)))
    {
        creditor = "VISA";
    }
    else if ((nlen == 16) && card >= 51 * mc && card < 56 * mc)
    {
        creditor = "MASTERCARD";
    }
    else
    {
        creditor = "INVALID";
    }
    // check if checksum needs to be checked
    if (strcmp(creditor, "INVALID") != 0)
    {
        if (! checksum(card))
        {
            creditor = "INVALID";
        }
    }
    printf("%s\n", creditor);

}


// get digit length of long (number of digits really)
int long_length(long n)
{

    // Will ignore negative signs and only return digit length
    if (n < 0)
    {
        n = n * -1;
    }
    long e = 10;
    int len = 1;
    while (n > e || n == e)
    {
        len++;
        e = e * 10;
    }
    return len;
}


int get_digit(long n, int length)
{
    //get num place
    long d = 1;
    for (int i = 0; i < length - 1; i++)
    {
        d = d * 10;
    }
    int i = 0;
    while (i * d < n || i * d == d)
    {
        i++;
    }
    i--;
    if (i < 0)
    {
        i = 0;
    }
    return i;
}

bool checksum(long cnumber)
{
    int multi = 0;
    int check = 0;
    int length = long_length(cnumber);
    bool answer;

    // Eventually within the loop the card number value will hit zero
    // signaling the end of the card number has been reached
    // (sort of) if ending in n zeros then stop earlier without bugs
    while (cnumber > 0)
    {

        // get the leading digit of the card number
        int dig = get_digit(cnumber, length);
        // even positions are multiplied and all that
        // odd positions are just added
        if (length % 2 == 0)
        {
            // multiply the digit
            int tdig = dig * 2;
            // check if that has lead to a two digit number
            // the highest it could be is 18
            if (tdig > 9)
            {
                check += 1 + (tdig - 10);
            }
            else
            {
                check += tdig;
            }
        }
        else
        {
            check += dig;
        }
        // Incrementing by removing the first digit of the number
        // and thus lower the length manually

        long tens = 1;
        for (int j = 0; j < length - 1; j++)
        {
            tens = tens * 10;
        }
        // subtract the value of its largest number place
        cnumber = cnumber - ((long)dig * tens);

        // update length
        length = long_length(cnumber);

    }
    // if ends in 0
    if (check % 10 == 0)
    {
        answer = true;
    }
    else
    {
        answer = false;
    }
    return answer;
}

long lten(int digits)
{
    long x = 1;
    for (int i = 0; i < digits; i++)
    {
        x = x * 10;
    }
    return x;
}

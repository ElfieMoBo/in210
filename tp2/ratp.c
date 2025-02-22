#include <stdbool.h>
#include <stdio.h>
#include "age.h"

static const float Price = 1.2;

/* Function to test (with a "magical number") */
float computePrice(int age, bool tourist)
{
    if (age>12)
    {
        if (tourist)
            return Price*2;
        return Price;
    }
    else 
    {
        if (tourist)
            return Price;
        return Price/2;
    }
}

/* Function to test (with a call to an extern function) */
float computePriceLim(int age, bool tourist){
    int limitAge;
    int *plimit = &limitAge;
    recupAge(plimit);
    if(age>limitAge)
        return Price;
    else 
        return Price/2;
}

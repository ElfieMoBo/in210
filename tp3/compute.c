#include "age.h"

int getReducedTicket(int age, int retired)
{   
    int limitAge1=0;
    int limitAge2=0;
    // int response=0;
    int *plimit1 = &limitAge1;
    int *plimit2 = &limitAge2;
    recupLimitAge1(plimit1);
    recupLimitAge2(plimit2);
    if (age < 0)
         return -1;
    if ((age>limitAge1) && (age<limitAge2))
        return 0;
    else
        if ((!retired) && (age>=limitAge2))
            return 0;
        else 
            return 1;
}

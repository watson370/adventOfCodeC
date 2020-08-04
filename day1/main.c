#include <stdio.h>
#include <stdlib.h>
#include <string.h>
long int Calc(long int mass);
long int CalcWithFuelAdjustment(long int mass);
int main(void)
{
    int values[2000];
    FILE *fp;

    fp = fopen("day1input.txt", "r");
    if (fp == NULL)
    {
        printf("%s", "file could not be opened");
        return 1;
    }
    int current = fgetc(fp);
    char buffer[20];
    int pos = 0;
    int next_val_pos = 0;

    while (current != EOF)
    {
        //add this to a char *
        //48-57
        if (pos < sizeof(buffer) - 1) //check for overflow, save last for nil
        {
            //handle num and handle comma
            if ((current <= 57 && current >= 48))
            { //check input is valid num
                buffer[pos] = current;
                pos++;
            }
            else if (current == 44)
            {
                buffer[pos] = '\0';
                int val = atoi(buffer); //todo handle error
                if (next_val_pos < sizeof(values))
                {
                    values[next_val_pos++] = val;
                }
                // printf("We got the string %s and the number %d\n", buffer, val);
                pos = 0; //don't bother overwriting
            }
        }
        // printf("next char is %c, but as an int %d\n", current, current);
        current = fgetc(fp);
    }

    fclose(fp);

    long long int res = 0;
    long long int totalMass = 0;
    //iterate through values
    for (size_t index = 0;
         index < next_val_pos;
         index++)
    {
        // printf("The next value is %d \n", values[index]);
        totalMass += values[index];
        res += Calc(values[index]);
    }
    printf("The calculated fuel for all of the day1 modules is %lld for a total mass of %lld\n", res, totalMass);
    long long int reswadj = 0;
    long long int totalMasswadj = 0;
    for (size_t index = 0;
         index < next_val_pos;
         index++)
    {
        totalMasswadj += values[index];
        reswadj += CalcWithFuelAdjustment(values[index]);
    }
    printf("The calculated fuel for all of the day1 modules including adjustment for fuel mass is %lld for a total mass of %lld\n", reswadj, totalMasswadj);
    return 0;
}

//Calc  takes in the mass and returns the fuel required
long int Calc(long int mass)
{
    long int div;
    div = mass / 3;
    return div - 2;
}

//CalcWithFuelAdjustment adjusts for fuel needed for fuel mass
long int CalcWithFuelAdjustment(long int mass)
{
    long long int totalFuel = 0;
    long long int round = mass;
    long long int fuel = 0;
    fuel = Calc(round);
    while (fuel >= 0)
    {
        totalFuel += fuel;
        round = fuel;
        fuel = Calc(round);
    }
    return totalFuel;
}

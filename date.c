#include "date.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct date  {
    int day;
    int month;
    int year;
} Date;


Date *date_create( char *datestr){
    Date *d =  malloc(sizeof(Date));
    // const char delimiter[2] = "/";
    char *token;
//printf("datestring %s", datestr);
    if(d !=NULL){
        token = strtok(datestr, "/");
        d->day = atoi(token);
        token = strtok(NULL, "/");
        d->month = atoi(token);
        token = strtok(NULL, "/");
        d->year = atoi(token);
    //printf("datemonth %d \n", d->month);
    }else{
        free(d);
       
    }
    return d;
}

Date *date_duplicate(Date *d){
    Date *duplicate_date=  malloc(sizeof(Date));
    if(duplicate_date !=NULL){
        duplicate_date->day = d->day; // duplicate date day assigned value of original date  day
        duplicate_date->month = d->month; // duplicate date mont assigned value of original date  month
        duplicate_date->year = d->year; // duplicate date year assigned value of original date  year
    }
    //printf("This is the duplicate year %d", duplicate_date->year);
    return duplicate_date;

}

int date_compare(Date *date1, Date *date2){
    if(date1->year < date2->year){
        // date1 year being < date 2 year means  date1 < date 2
        
        return -1 ; 
    }else if (date1->year > date2->year){
        
         // date1 year being > date 2 year means  date1 > date 2
        return 1;
    }else{
        
        /// if both years are equal move to the month of the year 
        if(date1->month < date2->month){
            
             // date1 month being < date 2 month means  date1 < date 2
             return -1;
        }
        else if(date1->month > date2->month ){
            
         // date1 month being > date 2 month means  date1 > date 2
            return 1;
        }else {
            // if both months are equal move to the day of the month
            if(date1->day < date2->day){
                
                // date1 day being < date 2 day means  date1 < date 2
                return -1;
            }else if(date1->day > date2->day){
                
                 // date1 day being > date 2 day means  date1 > date 2
                return 1;
            }else{
                
                // both days are equal meaning the dates are equal
                return 0;
            }

        }
    }
}

void date_destroy(Date *d){
    if (d != NULL)
    free(d); // release the memory block which was previously allocated to Date by malloc()
}
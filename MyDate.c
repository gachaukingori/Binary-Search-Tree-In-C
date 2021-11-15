#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _DATE_H_INCLUDED_
#define _DATE_H_INCLUDED_


//typedef struct date Date;
typedef struct date  {
    int day;
    int month;
    int year;


} Date;
Date *date_create( char *datestr){
    Date *d = (Date *) malloc(sizeof(Date));
    const char delimiter[2] = "/";
    char *token;

    if(d !=NULL){
        token = strtok(datestr, delimiter);
        d->day = atoi(token);
        token = strtok(NULL, delimiter);
        d->month = atoi(token);
        token = strtok(NULL, delimiter);
        d->year = atoi(token);
        
       // printf("Day: %d  \n Month: %d  \n Year: %d \n", d->day, d->month, d->year);
    
    }
    return d;
}


Date *date_duplicate(Date *d){
    Date dd = (Date *) malloc(sizeof(Date));
    if(dd !=NULL){
        dd->day = d->day;
        dd->month = d->month;
        dd->year = d->year;
    }
    return dd;

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
    free(d);
}


int main(){
      Date *d;
    char buf[1024], *s;
//     char *datestr = "03/12/1997";
//     Date *d  = date_create(datestr);
//    // printf("this is the date\n, %d, %d, %d", d->day, d->month, d->year);
// return 0;

  while (fgets(buf, sizeof(buf), stdin) != NULL) {
    if (!(d = date_create(buf))) {
    fprintf(stderr, "Unable to create a date.\n");
    return -1;
    }
      printf("Year: %d Month: %d Day: %d", d->year, d->month, d->day);
  }
  return 0;

}
#endif /* _DATE_H_INCLUDED_ */
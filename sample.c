#include<stdio.h>

typedef struct date {
    int mm, dd, yy;
}
date;

char *PrintJustAnyThing(){
    return "This is a return STratament \n";
   //int myIntPointer = 45;
  // return myIntPointer;
}

int main( ){

    char *myReturn = PrintJustAnyThing();  

   // int *myReturn = "Helloe world";
    printf("this is my return , %s", myReturn);


    // printf("Helllo World Again \n");
    // date var1;

//     puts("Enter date in the format m/d/yy\n");
//     scanf("%d",&var1.mm);
// 	scanf("%d",&var1.dd);
// 	scanf("%d",&var1.yy);

// printf("You entered the following date: %d/%d/0%d\n",var1.mm,var1.dd,var1.yy);
//    char dateStr [30];


//      puts("Enter date in the format m/d/yy");
//      fgets(dateStr, 30, stdin);
//      scanf("%s",&dateStr);

// printf("You entered the date: %s \n", dateStr);
	 
	 
	 
    return 0;
}


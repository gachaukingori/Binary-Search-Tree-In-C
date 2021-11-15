#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
    char domain[20];
    printf("enter the domain name \n");
    scanf("%s", &domain);

    char *temp = strrchr(domain, '.') + 1;
    
for(int i = 0; (temp[i]!= '\0'); i++){
    if(temp[i] != '.'){
        temp[i] = tolower(temp[i]);
    }
}
printf("\n You have entered the folloeing domain, %s \n", temp);

return 0;
}
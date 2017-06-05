
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>


main()
{
 

printf("Content-Type: text/plain ; charset=utf-8\n\n");


char *data = getenv("QUERY_STRING");

char username[100];
char password[100];




sscanf(data,"name=%[^&]&password=%s",username,password);



if(strcmp(username,"yashwanth") == 0 && strcmp(password,"batman") == 0 )
{
 printf("Your login credentials are valid.Welcome: %s",username);
}


else {
  printf("Error ! Your login credentials are valid ");
}

}


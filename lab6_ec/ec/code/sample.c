#include <stdio.h>
#include <stdlib.h>
main(){

printf("Content-Type: text/plain; charset=utf-8\n\n");
printf("It is a sample program \n");
char *data= getenv("QUERY_STRING");
char uname[50]="bindu", pswrd[50]="hima";
sscanf(data,"username=%[^&]&password=%s",uname,pswrd);
//printf("username=%s,password=%s",uname,pswrd);
if(strcmp(uname,"bindu")!=0 || strcmp(pswrd,"hima")!=0){
	printf("Please enter valid credentials");
}
else{
	printf("Thanks for logging in");
}





/*char *data = getenv("QUERY_STRING");
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
*/

return 0;
}


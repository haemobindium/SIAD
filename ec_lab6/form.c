
#include <stdio.h>
#include <stdlib.h>
main(){

printf("Content-Type: text/plain; charset=utf-8\n\n");
printf("Hello World \n");
char *data= getenv("QUERY_STRING");
char *username = getenv("QUERY_STRING");
char *password = getenv("QUERY_STRING");
printf("data:%s",data);
sscanf(data,"username=%[^&]&password=%s",username,password);
printf("username=%s,password=%s",username,password);
return 0;
}

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "string.h"
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif
//#include "conio.h"
//#include "curses.h"
int main()
{
char key;
char text[256]="input-";
char ic[22]="adb shell input text ";
char temp[256];

printf("\nadb Navigator tool for navigating on device using adb.\nPlease Contact \"sbachchuwar@nvidia.com\" for any issues.\nMake sure adb is in /bin/ & working. \n");
printf("Checking adb device state...\n");
//system("sudo adb wait-for-device");
int adbgetstate();
adbgetstate();

//FILE *adbok=popen("echo $?")

int help();
help();


//fgets(text, sizeof text, stdin);
//printf("%s ",text);

//sleep(2);
printf("\nPress q for quit\n");

system("/bin/stty raw");
while((key=getchar())!='q')
{
//getchar();
switch(key)
{

case 'w': printf(":UP\r\n");system("adb shell input keyevent 19");printf("\r");break;
case 's': printf(":DOWN\r\n");system("adb shell input keyevent 20");printf("\r");break;
case 'a': printf(":LEFT\r\n");system("adb shell input keyevent 21");printf("\r");break;
case 'd': printf(":RIGHT\r\n");system("adb shell input keyevent 22");printf("\r");break;
case 'e': printf(":SELECT OR CLICK\r\n");system("adb shell input keyevent 23");printf("\r");break;
case 'h': printf(":HOME\r\n");system("adb shell input keyevent 3");printf("\r");break;
case 'b': printf(":BACK\r\n");system("adb shell input keyevent 4");printf("\r");break;
case 'm': printf(":MENU\r\n");system("adb shell input keyevent 82");printf("\r");break;
case 'c': printf(":CANCEL OR DELETE\r\n");system("adb shell input keyevent 67");printf("\r");break;
case 'u': printf(":UNLOCK\r\n");system("adb shell input keyevent 82");printf("\r");break;
//case 'n': printf(":NOTIFICATION MENU\r\n");system("adb shell input keyevent 83");break;
case 't': printf(":TEXT WRITE\r\n");system ("/bin/stty cooked");fgets(text, sizeof text, stdin);snprintf(temp, sizeof(temp),"%s%s%s%s",ic,"\"",text,"\"");system(temp);system("/bin/stty raw");
case 'o': printf(":OPTIONS\r\n");help();printf("\r");break;
//case 'C': printf(":NO ACTION SPECIFIED. PRESS q FOR QUIT\r\n");printf("\r");break;
default: printf(":NO ACTION SPECIFIED\r\n");

}
}
printf("\r\nQuitting..");
system ("/bin/stty cooked");
printf("\n");

fflush(stdout);
}
int help()
{
printf("\r\nFollowing is the mapping of keyboard keys with action"
"\r\n=========================="
"\r\nq --> QUIT"
"\r\nw --> UP"
"\r\ns --> DOWN"
"\r\na --> LEFT"
"\r\nd --> RIGHT"
"\r\ne --> SELECT OR CLICK"
"\r\nh --> HOME"
"\r\nm --> MENU"
"\r\nb --> BACK"
"\r\nc --> CANCEL OR DELETE"
"\r\nu --> UNLOCK"
"\r\nt --> TEXT WRITE"
"\r\no --> OPTIONS(FOR TOOL)"
"\r\nq --> QUIT"
"\r\n==========================\r\n");
return 0;
}

int adbgetstate()
{

char err[256];
FILE *fp=popen("sudo adb get-state 2>&1","r");

char *output=fgets(err,sizeof(err),fp);
if(!strcmp(output,"unknown\n") || !strcmp(output,"offline\n"))
{
printf("adb Error: State-%sPlease keep adb binary in /bin/ & make sure device is connected.\nExiting....\n",output);
exit(0);
}
else if(!strcmp(output,"* daemon not running. starting it now on port 5037 *\n"))
{
printf("daemon not running. starting it now ..");
sleep(2);
adbgetstate();
}
else
printf("adb result:%s",output);
//printf("adb ouput:%s",output);
pclose(fp);
}

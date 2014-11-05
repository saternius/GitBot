#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "signal.h"
#include "time.h"
#include <sys/time.h>

void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}


int main(){
	srand(time(NULL));
	char filename[256];
	gen_random(filename,8);
	char command[256];

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char content[256];
	sprintf(content,"committed: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	
	sprintf(command,"echo \"%s\" > %s.txt",content,filename);
	//puts(command);
	system(command);

	sprintf(command,"git add %s.txt",filename);
	//puts(command);
	system(command);
	system("git commit -m \"Please never use this\"");
	system("git push origin master");
}


#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

//set up a couple constants
#define BRIGHTPATH "/sys/class/leds/smc::kbd_backlight/brightness"
#define MAXPATH "/sys/class/leds/smc::kbd_backlight/max_brightness"
#define INCR 15

// some function declarations
int getMaxBrightness();

int getCurrentBrightness(int fd);

void setNewBrightness(int fd, int cur_bright, int max_bright, char *user_in);

// call main code
int main(int argc, char *argv[]){
	// first I need to do some work to handle the input argument, ideas from
	// https://www.unix.com/programming/154129-how-turn-argv-1-into-string-c.html	
	char *str = (char *)NULL;
	int len = 0;

	if (argc != 2) return 1;

	len = strlen(argv[1]);
	if ((str = malloc(len +1)) != NULL){
		bzero(str, len + 1);
		strncpy(str, argv[1], len);
	} else {
		exit(EXIT_FAILURE);
	}

	int max_bright = getMaxBrightness();
	int fd = open(BRIGHTPATH, O_RDWR);
	if (fd != -1){
		int cur_bright = getCurrentBrightness(fd);
		setNewBrightness(fd, cur_bright, max_bright, str);
		close(fd);
	}

	free(str);
	return 0;
}

int getMaxBrightness(){
	int fd;
	char buffer[5];
	// initialize max_bright just incase we cannot open the file
	int max_bright = 0;
	fd = open(MAXPATH, O_RDONLY);
	if (fd != -1){
		lseek(fd,0,SEEK_SET);
		read(fd, buffer, 5);
		max_bright = atoi(buffer);
		close(fd);
	}
	return max_bright;
}

int getCurrentBrightness(int fd){
	char buffer[5];
	lseek(fd,0,SEEK_SET);
	read(fd, buffer, 5);
	int cur_bright = atoi(buffer);
	return cur_bright;
}

void setNewBrightness(int fd, int cur_bright, int max_bright, char *user_in){
	char buffer[5];
	int new_bright = 0;
	if (strcmp(user_in,"down") == 0){
		if ((cur_bright - INCR) <= 0){
			new_bright = 0;
		} else {
			new_bright = cur_bright - INCR;
		}
	} else if (strcmp(user_in,"up") == 0){
		if ((cur_bright + INCR) >= max_bright) {
			new_bright = max_bright;
		} else {
			new_bright = cur_bright + INCR;
		}
	} else {
		"do nothing";
	}
	sprintf(buffer, "%d", new_bright);
	write(fd, buffer, sizeof(buffer));
}

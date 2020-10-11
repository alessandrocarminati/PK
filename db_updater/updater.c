#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/kd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define ERROR -1
#define PERIOD 40000

long int GetStatusLed(int fd) {
	long int orig;

	ioctl(fd, KDGETLED, &orig);
	return(orig);
}


void SetStatusLed(int fd, long int status) {
	ioctl(fd, KDSETLED, status);
}

/*
 capslock   mosi
 numlock    ck
 scrolllock latch
*/
void SerialOUT8Bit(int fd, unsigned char data) {
	char i,s;

	ioctl(fd, KDSETLED, 0); // Clear all leds
	for (i=0; i<8; i++) {
		s =2|((data>>(7-i))&1)<<2;
		ioctl(fd, KDSETLED, s);
		usleep(PERIOD);
		s =0|((data>>(7-i))&1)<<2;
		if (i==7) s|=1;
		ioctl(fd, KDSETLED, s);
		usleep(PERIOD);
		}
}

void main(int argc, char **argv) {
	int fd;
	FILE *fd2;
	int i = 0;
	unsigned char data;
	long int orig = 0;

	if ((fd = open("/dev/console", O_NOCTTY)) == ERROR) {
		perror("cannot open console");
		exit(0);
		}
	fd2 = fopen(argv[1], "r");
	orig=GetStatusLed(fd);
	printf("Uploading database....\n");
	while( !feof( fd2 ) ) {
		fread( &data, sizeof( char ), 1, fd2 );
		SerialOUT8Bit(fd,data);
		printf("%.2f%% \n\033[1A",i/192.0*100);
		i++;
		}
	printf("\n");
	fclose(fd2);
	SetStatusLed(fd,orig);
}

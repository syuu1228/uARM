#include "SoC.h"

#include <emscripten.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>

unsigned char* readFile(const char* name, UInt32* lenP){

	long len = 0;
	unsigned char *r = NULL;
	int i;
	FILE* f;

	f = fopen(name, "r");
	if(!f){
		perror("cannot open file");
		return NULL;
	}

	i = fseek(f, 0, SEEK_END);
	if(i){
		return NULL;
		perror("cannot seek to end");
	}

	len = ftell(f);
	if(len < 0){
		perror("cannot get position");
		return NULL;
	}

	i = fseek(f, 0, SEEK_SET);
	if(i){
		return NULL;
		perror("cannot seek to start");
	}


	r = malloc(len);
	if(!r){
		perror("cannot alloc memory");
		return NULL;
	}

	if(len != (long)fread(r, 1, len, f)){
		perror("canot read file");
		free(r);
		return NULL;
	}

	*lenP = len;
	return r;
}



static int ctlCSeen = 0;

static int readchar(void){

	return 0;
}

static void writechar(int chr){

	if(!(chr & 0xFF00)){

		printf("%c", chr);
	}
	else{
		printf("<<~~ EC_0x%x ~~>>", chr);
	}
	fflush(stdout);
}

void ctl_cHandler(_UNUSED_ int v){	//handle SIGTERM

//	exit(-1);
	ctlCSeen = 1;
}

int rootOps(void* userData, UInt32 sector, void* buf, UInt8 op){

	FILE* root = userData;
	int i;

	switch(op){
		case BLK_OP_SIZE:

			if(sector == 0){	//num blocks

				if(root){

					i = fseeko(root, 0, SEEK_END);
					if(i) return false;

					 *(unsigned long*)buf = (off_t)ftello(root) / (off_t)BLK_DEV_BLK_SZ;
				}
				else{

					*(unsigned long*)buf = 0;
				}
			}
			else if(sector == 1){	//block size

				*(unsigned long*)buf = BLK_DEV_BLK_SZ;
			}
			else return 0;
			return 1;

		case BLK_OP_READ:

			i = fseeko(root, (off_t)sector * (off_t)BLK_DEV_BLK_SZ, SEEK_SET);
			if(i) return false;
			return fread(buf, 1, BLK_DEV_BLK_SZ, root) == BLK_DEV_BLK_SZ;

		case BLK_OP_WRITE:

			i = fseeko(root, (off_t)sector * (off_t)BLK_DEV_BLK_SZ, SEEK_SET);
			if(i) return false;
			return fwrite(buf, 1, BLK_DEV_BLK_SZ, root) == BLK_DEV_BLK_SZ;
	}
	return 0;
}

SoC soc;

void main_loop() {
  for( int step = 0; step != 1000000; ++step )
	   socStep(&soc);
}

int main(){

	struct termios cfg, old;
	FILE* root = NULL;

	root = fopen("rootfs.img", "r+b");
	if(!root){
		fprintf(stderr,"Failed to open root device\n");
		exit(-1);
	}

	socInit(&soc, socRamModeAlloc, NULL, readchar, writechar, rootOps, root);
 emscripten_set_main_loop( &main_loop, 60, 1 );
	return 0;
}


//////// runtime things

void* emu_alloc(UInt32 size){

	return calloc(size,1);
}

void emu_free(void* ptr){

	free(ptr);
}

UInt32 rtcCurTime(void){

	struct timeval tv;

	gettimeofday(&tv, NULL);

	return tv.tv_sec;
}

void err_str(const char* str){

	fprintf(stderr, "%s", str);
}

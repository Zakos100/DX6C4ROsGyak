#include <stdio.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <stdlib.h>
	#include <string.h>
	
	int main(){
	
	    pid_t child;
	    int fd;
	
	    if((mkfifo("DX6C4R", S_IRUSR | S_IWUSR)) < 0) {
	        printf("Nem sikerult leterhozni a FIFOT!\n");
	        exit(-1);
		}
	
	    if((child = fork()) < 0){
	        printf("Nem sikerult a gyerek fork processz letrehozasa!\n");
	        exit(-1);
	    }
		
	    if(!child){
	        char *szoveg = "Zarandi Akos";
			
	        if((fd = open("DX6C4R", O_WRONLY)) < 0){
	            printf("Nem sikerult a FIFO megnyitasa!\n");
	            exit(-1);	
	        } 
	        else {	
	            write(fd, szoveg, strlen(szoveg));		
	        }
	
	    }
		
	    if(child){
	        char s[50];
	        if((fd = open("DX6C4R", O_RDONLY)) <0 ){
	            printf("Nem sikerult a FIFO megnyitasa!\n");
	            exit(-1);
				
	        } else {
	            read(fd, s, sizeof(s));
	            printf("Kiolvasott adat: %s\n", s);
				
	        }
	        if((unlink("DX6C4R")) < 0 || (close(fd)) < 0){
				
	            printf("Nem sikerult a FIFO torlese.");
				
	        } 
	        else {
	            printf("FIFO sikeresen torolve.");
	        }
		}
	
	    return 0;
	}

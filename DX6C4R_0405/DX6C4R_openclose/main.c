#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char buf [20];
    int buffLength;
    int fileDescriptor;
    int writeInfo;
    int seekInfo;
    int readInfo;



    fileDescriptor = open("DX6C4R.txt",O_RDWR);
    if (fileDescriptor == -1){
        perror("open() hiba:");
        exit(fileDescriptor);
    }
    printf("File Descriptor erteke: %d\n", fileDescriptor);


    seekInfo= lseek(fileDescriptor, 0, SEEK_SET);
    if (seekInfo==-1){
        perror("A pozicionalas nem volt sikeres");
        exit(seekInfo);
    }
    printf("A kurzus pozicioja %d,\n", seekInfo);


    readInfo=read(fileDescriptor, buf, 15);
    if (readInfo==-1){
        perror("Az olvasás nem volt sikeres");
        exit(readInfo);
    }
    printf("A read() erteke: %d\n", readInfo);
    printf("A beolvasott ertek: %a\n", buf);


    strcpy(buf, "Ez egy teszt");
    buffLength=strlen(buf);
    writeInfo=write(fileDescriptor, buf, buffLength);

    if (writeInfo==-1){
        perror("Az iras nem volt sikeres");
        exit(writeInfo);
    }
    printf("A write() -tal beirt byte-ok szama: %d", writeInfo);


}

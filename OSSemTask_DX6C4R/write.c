#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
	// Változók deklarálása
    int a, b, c;
	float x, y, d;
	char as, bs, cs, space=' ';
	
	
    // Kulcs létrehozása
    key_t kulcs = ftok("shmfile",65);
  
    // Az shmget egy azonosítót ad vissza az shmid-vel
    int shmid = shmget(kulcs, 1024, 0666|IPC_CREAT);
  
    // shmat-al csatlakozunk a memóriaszegmensre
    char *str = (char*) shmat(shmid,(void*)0,0);
	
	
	
	FILE* ptr;
 
	if ((ptr=fopen("teszt.txt", "r")) == NULL){
       printf("Fajl megnyitasa sikertelen! A hiba oka:\n");
	   perror(0);
	   exit(1);
	}
	
	FILE* ptr2;
 
	if ((ptr2=fopen("eredmeny.txt", "w")) == NULL){
       printf("Fajl megnyitasa sikertelen! A hiba oka:\n");
	   perror(0);
	   exit(1);
	}
	

	// Első fájl tartalmának olvasása majd kiírása a memóriaszegmensbe, fájl pointer lezárása
	fgets(str, 256, ptr);
	fclose(ptr);
  
    printf("A szegmensbe irt adat: %s\n", str);
	
	
	
	// Szétszedjük a beolvasott sort,
	// és mivel ezek karakterek, átkonvertáljuk intbe őket
	as=str[0];
	a=atoi(&as);
	
	bs=str[2];
	b=atoi(&bs);
	
	
	cs=str[4];
	c=atoi(&cs);
	
	// Másodfokú egyenlet megoldása (komplex számokkal is működik)
	
	d = b * b - 4 * a * c;
	
	printf("d: %f\n\n", d);
  
	if(d < 0){
    printf("A gyokok komplex szamok.\n\n");
 
    printf("A(z) %dx^2 + %dx + %d = 0 egyenlet gyokei: \n", a, b, c);
    printf("%.4f%+.4fi", -b/(2*a), sqrt(-d) / (2*a));
    printf(", %.4f%+.4fi", -b/(2*a), -sqrt(-d) / (2*a));
	printf("\n");
  
    return 0;
  }
  
  
  else if(d == 0){
   printf("A ket gyok megegyezik.\n");
 
   x = -b / (2*a);
   printf("A(z) %dx^2 + %dx + %d = 0 egyenlet gyoke: %.4f\n", a, b, c, x);
 
   return 0;
  }
  
  
  else{
   printf("A gyokok valos szamok.\n");
  
   x = ( -b + sqrt(d)) / (2*a);
   y = ( -b - sqrt(d)) / (2*a);
   printf("A(z) %dx^2 + %dx +%d = 0 egyenlet gyokei: %.4f , es %.4f\n", a, b, c, x, y);
  }
  
  fprintf(ptr2, "%d %d %d %.4f %.4f\n", a, b, c, x, y);
	
	
    // Lecsatlakozunk a memóriaszegmensről. 
    shmdt(str);
	fclose(ptr2);
	
	return 0;
}
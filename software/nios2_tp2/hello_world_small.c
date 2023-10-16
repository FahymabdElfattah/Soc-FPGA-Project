

#include <stdio.h>
#include "system.h"
#include "sys/alt_irq.h"
#include "sys/alt_stdio.h"


char	seven_S[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };
//char seven_S[] = {0x00, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x50, 0x5C, 0x67, 0x77, 0x73, 0x39, 0x5E, 0x79, 0x71 };
char	hex_segments[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

/*void Update_HEX_display( int buffer ){
	volatile int * HEX3_HEX0_ptr = (int *) HEX_BASE;
	int shift_buffer, nibble;
	char code;
	int i;

	shift_buffer = buffer;
	for ( i = 0; i < 8; ++i ){
		nibble = shift_buffer & 0x0000000F;		// character is in rightmost nibble
		code = seven_S[nibble];
		hex_segments[i] = code;
		shift_buffer = shift_buffer >> 4;
	}
	*(HEX3_HEX0_ptr) = *(int *) hex_segments; 		// drive the hex displays
	return;
}*/
volatile int edge_capture;
volatile int * key_ptr = (int *) KEY_BASE;
volatile int * HEX_ptr = (int *) HEX_BASE;

void handle_key_interrupts(void* context, alt_u32 id){
int press = * (key_ptr +3); // lecture du registre du periph.
if (press&0x2){
	  printf("j'ai tappé KEY1");
	  *HEX_ptr = 0x4F5B063F;
	}
else if (press&0x4){
	  printf("j'ai tappé KEY2");
	  *HEX_ptr = 0x000000CF;
	}
else if (press&0x8){
	  printf("j'ai tappé KEY3");
	  *HEX_ptr = 0x0000520F;
	}
* (key_ptr + 3) =0;  // effacer le registre du periph.
}

void init_key(){
void* edge_capture_ptr = (void*) &edge_capture;
* (key_ptr + 2) = 0xe; // Masque de l’interruption "1110"
 alt_irq_register( KEY_IRQ, edge_capture_ptr,handle_key_interrupts);
}


int s=59,m=0,h=0;
int main(){
  printf("Hello from Nios  hhh!\n");
  init_key();
  int h = 0 , m = 16 , s = 50;      //Initialisation des variables
  while (1){
	     //system("Pause");                //Attend l'appui d'une touche
	     //system("cls");                  //Effacer l'ecran
	     while (h < 24){
	         if (h < 10) {
	         //printf("0%i : ",h);         //Affichage avec 0 devant
	         }else{
	        // printf("%i : ",h);          //Sans le 0 si > 10
	         }
	         if (m < 10) {
	         //printf("0%i : ",m);
	        	 *HEX_ptr = ((seven_S[m/10]<< 24)|(seven_S[m%10]<< 16)|(seven_S[s/10]<< 8)|(seven_S[s%10]&0xff));

	         }else{
	         //printf("%i : ",m);
	        	 *HEX_ptr = ((seven_S[m/10]<< 24)|(seven_S[m%10]<< 16)|(seven_S[s/10]<< 8)|(seven_S[s%10]&0xff));

	         }
	         if (s < 10){
	        	 *HEX_ptr = ((seven_S[m/10]<< 24)|(seven_S[m%10]<< 16)|(seven_S[s/10]<< 8)|(seven_S[s%10]&0xff));	         }else{
	         //printf("%i",s);

	         *HEX_ptr = ((seven_S[m/10]<< 24)|(seven_S[m%10]<< 16)|(seven_S[s/10]<< 8)|(seven_S[s%10]&0xff));
	        // Update_HEX_display(s);
	         //printf("\n");

	         }
	         s++;                        //Incrémentation des secondes
	         usleep(600000);                //Attente de 1000 mili-secondes
	         //usleep(1);
	         //system("cls");              //Effacer l'ecran

	         if (s > 59)
	         {
	             s = 0;
	             m++;
	         }
	         if (m > 59)
	         {
	             m = 0;
	             h++;
	         }
	     }

  };




  return 0;
}



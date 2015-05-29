#include <18F4550.h>
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN
#use delay(clock=48M)
#include <pic18_usb.h>
#include <CelaneoDaQ_desc_hid.h> 
#include <usb.c>

#define PWW PIN_C0 
#define PWW2 PIN_C1
#define PWW3 PIN_C2


#define param1 Entrada[8] // Primer parámetro recibdo
#define param2 Entrada[9] // Segundo parámetro recibdo
#define param3 Entrada[10] // Segundo parámetro recibdo

#define CONTROLPWW 4 
#define CONTROLPWW2 5
#define CONTROLPWW3 6

#BYTE TRISD = 0x0F95
#BYTE PORTD = 0x0F83


#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1)

 int r=0;
void IndV()
{
 if(r==0)
 {
  PORTD = 1;
  output_high(PIN_D0);
  output_high(PIN_D7);
  delay_ms(50);
  output_high(PIN_D1);
  output_high(PIN_D6);
  delay_ms(50);
  output_high(PIN_D2);
  output_high(PIN_D5);
  delay_ms(50);
  output_high(PIN_D3);
  output_high(PIN_D4);
  delay_ms(50);
  //------------
  PORTD =(0x00);
  output_high(PIN_D3);
  output_high(PIN_D4);
  delay_ms(80);
  output_low(PIN_D3);
  output_low(PIN_D4);
  output_high(PIN_D2);
  output_high(PIN_D5); 
  delay_ms(80);
  output_low(PIN_D2);
  output_low(PIN_D5);
  output_high(PIN_D1);
  output_high(PIN_D6);
  delay_ms(80);
  output_low(PIN_D1);
  output_low(PIN_D6);
  output_high(PIN_D0);
  output_high(PIN_D7);
  delay_ms(80);
  //-----------
 output_d(0xFF);
 delay_ms(100);
 output_d(0x00); 
 delay_ms(100);
 output_d(0xFF);
 delay_ms(100);
 output_d(0x00);
 delay_ms(100);
 output_d(0xFF);
 delay_ms(100);
 output_d(0x00); 
  output_d(0xFF);
 delay_ms(100);
 output_d(0x00); 
 delay_ms(100);
 output_d(0xFF);
 delay_ms(100);
 output_d(0x00);
 delay_ms(100);
 output_d(0xFF);
 delay_ms(100);
 output_d(0x00); 
 r++;
 }
}

void main(VOID) 
{
   setup_adc_ports(AN0_TO_AN7);
   setup_adc(ADC_CLOCK_INTERNAL);
   
   set_tris_d(0x00);                
   output_d(0x00);   
   set_tris_b(0xFF);

   int Entrada[64];
   int Salida[64];
   INT8 valorPWW = 0; // Valor del pulso PWW
   INT8 valorPWW2 = 0;
   INT8 valorPWW3 = 0;
   INT8 i; // Indice del bucle PWW
   INT8 j;
   INT8 k;
   
   
   output_low (PWW); // Pulso en bajo
   output_low (PWW2);
   
   usb_init (); // Inicializamos el USB
   usb_task (); // Habilita el periferico usb y las interrupciones
   usb_wait_FOR_enumeration (); // Esperamos hasta que el PicUSB sea configurado por el PC
   


   
   WHILE (TRUE) // Se cumple siempre (Bucle infinito)
   {
     usb_task();
      IF (usb_enumerated ()) // Si el PicUSB está configurado
      {
        IndV();
        IF (valorPWW != 0) // Si valorPWW no es cero
         {
            IF (valorPWW == 0xFF) // Si es el máximo
            {
               output_high(PWW); // Pulso en alto
            }

            ELSE
            {
               output_high (PWW); // Pulso en alto
               FOR (i = 1; i <= valorPWW; ++i) // valorPWW en alto
               {
                  delay_us (100); // Retardo de 100us
               }

               output_low (PWW); // Pulso en bajo
               FOR (i = 1; i <= (255-valorPWW); ++i) // (255-valorPWW) en bajo
               {
                  delay_us (100); // Retardo de 100us
               }
            }
         }

         ELSE
         {
            output_low (PWW); // Pulso en bajo si valorPWW es cero
         }
         
        IF (valorPWW2 != 0) // Si valorPWW no es cero
         {
            IF (valorPWW2 == 0xFF) // Si es el máximo
            {
               output_high(PWW2); // Pulso en alto
            }

            ELSE
            {
               output_high (PWW2); // Pulso en alto
               FOR (j = 1; j <= valorPWW2; ++j) // valorPWW en alto
               {
                  delay_us (100); // Retardo de 100us
               }

               output_low (PWW2); // Pulso en bajo
               FOR (j = 1; j <= (255-valorPWW2); ++j) // (255-valorPWW) en bajo
               {
                  delay_us (100); // Retardo de 100us
               }
            }
         }

         ELSE
         {
            output_low (PWW2); // Pulso en bajo si valorPWW es cero
         }
         
        IF (valorPWW3 != 0) // Si valorPWW no es cero
         {
            IF (valorPWW3 == 0xFF) // Si es el máximo
            {
               output_high(PWW3); // Pulso en alto
            }

            ELSE
            {
               output_high (PWW3); // Pulso en alto
               FOR (k = 1; k <= valorPWW3; ++k) // valorPWW en alto
               {
                  delay_us (100); // Retardo de 100us
               }

               output_low (PWW3); // Pulso en bajo
               FOR (k = 1; k <= (255-valorPWW3); ++k) // (255-valorPWW) en bajo
               {
                  delay_us (100); // Retardo de 100us
               }
            }
         }

         ELSE
         {
            output_low (PWW3); // Pulso en bajo si valorPWW es cero
         }
         
           set_Adc_channel(0);
           delay_us(10);       
           Salida[0]=read_adc();        

           set_Adc_channel(1);
           delay_us(10);
           Salida[1]=read_adc();

           set_Adc_channel(2);
           delay_us(10);       
           Salida[2]=read_adc();
           
           set_Adc_channel(3);
           delay_us(10);       
           Salida[3]=read_adc();
           
           set_Adc_channel(4);
           delay_us(10);       
           Salida[4]=read_adc();
           
           set_Adc_channel(5);
           delay_us(10);       
           Salida[5]=read_adc();
           
           set_Adc_channel(6);
           delay_us(10);       
           Salida[6]=read_adc();
           
           set_Adc_channel(7);
           delay_us(10);       
           Salida[7]=read_adc();
           
           Salida[8]=INPUT(PIN_B0);
           Salida[9]=INPUT(PIN_B1);
           Salida[10]=INPUT(PIN_B2);
           Salida[11]=INPUT(PIN_B3);
           Salida[12]=INPUT(PIN_B4);
           Salida[13]=INPUT(PIN_B5);
           Salida[14]=INPUT(PIN_B6);
           Salida[15]=INPUT(PIN_B7);  
           usb_put_packet(1,Salida,64,USB_DTS_TOGGLE);  
           }
           
         IF (usb_kbhit (1)) // Si el EndPoint de salida contiene datos del PC
         {
           if(Entrada[0]==1)
           {
             output_high(pin_d0);
           }
           else
           {
              output_low(pin_d0);
           }
           if(Entrada[1]==1)
           {
             output_high(pin_d1);
           }
           else
           {
             output_low(pin_d1);
           }
           if(Entrada[2]==1)
           {
             output_high(pin_d2);
           }
           else
           {
             output_low(pin_d2);
           }
           if(Entrada[3]==1)
           {
             output_high(pin_d3);
           }
           else
           {
             output_low(pin_d3);
           }
           if(Entrada[4]==1)
           {
             output_high(pin_d4);
           }
           else
           {
             output_low(pin_d4);
           }
           if(Entrada[5]==1)
           {
             output_high(pin_d5);
           }
           else
           {
             output_low(pin_d5);
           }
           if(Entrada[6]==1)
           {
             output_high(pin_d6);
           }
           else
           {
             output_low(pin_d6);
           }
           if(Entrada[7]==1)
           {
             output_high(pin_d7);
           }
           else
           {
            output_low(pin_d7);
           }
            valorPWW= param1; // Asignamos el valor del PWW
            valorPWW2 = param2; // Asignamos el valor del PWW
            valorPWW3 = param3;
            usb_get_packet (1, Entrada, 64); // Cojemos el paquete de tamaño 3 bytes del EP1 // y lo almacenamos en la variable recibe
      }
   }
}








#include <Servo.h>   // incluimos la biblioteca Servo 

Servo miservo1;       // creamos un objecto servo para controlar el motor 
Servo miservo2;       // creamos un objecto servo para controlar el motor 
Servo miservo3;       // creamos un objecto servo para controlar el motor 

float sdistancia = A2; // Sensor Distancia 
float snivel = A0; // Potenciometro

void setup() {
    //initialize serial communications at 9600 bps
    Serial.begin(9600);
    miservo1.attach(11);  // liga el servo al pin 11
    miservo2.attach(9);  // liga el servo al pin 9 
    miservo3.attach(6);  // liga el servo al pin 6
      
    Serial.println("Inicialización"); 
    
    delay(5000);
    miservo1.write(180);                 
    miservo2.write(0);                
    miservo3.write(0);
    delay(5000);
}

        
 
void loop() {
    
    //LECTURA DE SENSORES
    
    float distancia, nivel, deseada, actual;

    // Distancia Actual (Sensor Distancia)
    
    distancia = analogRead(sdistancia); 
    actual = pow(3027.4 / distancia, 1.2134); // conversión a centímetros
    Serial.print("Distancia Actual: ");
    //actual = map(actual,3,28,28,3);
    Serial.println(actual);

    // Distancia Deseada (Potenciometro)
    nivel = analogRead(snivel);
    deseada = nivel * (60.0 / 1023.0);
    Serial.print("Nivel Deseado: ");
    //deseada = map(deseada,0,30,5,28);

    Serial.println(deseada);


    //FUNCIONES DE MEMBRESIA
    float error;
    float Lectura1, Lectura2;
    float  Entrada1neg, Entrada1pos, Entrada1med;
    float  Entrada2vac, Entrada2lle, Entrada2med, Entrada2cer;
    float div1, div2, div3, div4, div5, div6, div7;
    float sum1, sum2, sum3, sum4, sum5, sum6, sum7;
    float mult1, mult2, mult3, mult4, mult5, mult6, mult7;
    error = deseada - actual;
    Lectura1 = error;
    Lectura2 = actual;

    //definicion de constantes de salida//SUGENO
    float servo1_cerrado = 0; //servo1 Llenado
    float servo1_casi = 60;
    float servo1_medio = 45;
    float servo1_abierto = 90;
    float servo2_cerrado = 0; //servo2 Vaciado
    float servo2_casi = 60;    
    float servo2_medio = 45;
    float servo2_abierto = 90;
    //  

    //Funciones Error
    //Funcion de Negativo 
    if (Lectura1 > -2) { Entrada1neg = 0; }
    else if (Lectura1 < -60) { Entrada1neg = 1; }     
    else if (Lectura1 >= -60 && Lectura1 <= -2)
    {
      div1 = -0.01724;
      sum1 = Lectura1 + 2;
      mult1 = div1*sum1;
      Entrada1neg = mult1;
    } 

    //Funcion de Positivo 
    if (Lectura1 < 2) { Entrada1pos = 0; }
    else if (Lectura1 > 60) { Entrada1pos = 1; }     
    else if (Lectura1 <= 60 && Lectura1 >= 2)
    {
      div2 = 0.01724;
      sum2 = Lectura1 - 2;
      mult2 = div2*sum2;
      Entrada1pos = mult2;
    } 

    //Funcion de Medio
    if (Lectura1 < -60) { Entrada1med = 0; }
    else if (Lectura1 > 60) { Entrada1med = 0; } 
    else if (Lectura1 == 0) { Entrada1med = 1; }         
    else if (Lectura1 >= -60 && Lectura1 < 0)
    {
      div3 = 0.01666;
      sum3 = Lectura1 + 60;
      mult3 = div3*sum3;
      Entrada1med = mult3;
    } 
    else if (Lectura1 <= 60 && Lectura1 > 0)
    {
      div3 = -0.01666;
      sum3 = Lectura1 - 60;
      mult3 = div3*sum3; 
      Entrada1med = mult3;
    } 

    //Funciones Nivel Actual
    //Funcion de Vacio 
    if (Lectura2 > 15) { Entrada2vac = 0; }
    else if (Lectura2 < 6) { Entrada2vac = 1; }     
    else if (Lectura2 >= 6 && Lectura2 <= 15)
    {
      div4 = -0.11111;
      sum4 = Lectura2 - 15;
      mult4 = div4*sum4;
      Entrada2vac = mult4;
    } 

    //Funcion de Lleno 
    if (Lectura2 < 40) { Entrada2lle = 0; }
    else if (Lectura2 > 55) { Entrada2lle = 1; }     
    else if (Lectura2 <= 55 && Lectura2 >= 40)
    {
      div5 = 0.06666;
      sum5 = Lectura2 - 40;
      mult5 = div5*sum5; 
      Entrada2lle = mult5;
    } 

    //Funcion de Medio
    if (Lectura2 < 15) { Entrada2med = 0; }
    else if (Lectura2 > 50) { Entrada2med = 0; } 
    else if (Lectura2 == 30) { Entrada2med = 1; }         
    else if (Lectura2 >= 15 && Lectura2 < 30)
    {
      div6 = 0.06666;
      sum6 = Lectura2 - 15;
      mult6 = div6*sum6; 
      Entrada2med = mult6;
    } 
    else if (Lectura2 <= 50 && Lectura2 > 30)
    {
      div6 = -0.05;
      sum6 = Lectura2 - 50;
      mult6 = div6*sum6; 
      Entrada2med = mult6;
    } 
    
    //Funcion de Cerca
    if (Lectura2 < 7) { Entrada2cer = 0; }
    else if (Lectura2 > 30) { Entrada2cer = 0; } 
    else if (Lectura2 == 15) { Entrada2cer = 1; }         
    else if (Lectura2 >= 7 && Lectura2 < 15)
    {
      div7 = 0.125;
      sum7 = Lectura2 - 7;
      mult7 = div7*sum7; 
      Entrada2cer = mult7;
    } 
    else if (Lectura2 <= 30 && Lectura2 > 15)
    {
      div7 = -0.06666;
      sum7 = Lectura2 - 30;
      mult7 = div7*sum7; 
      Entrada2cer = mult7;
    } 
    
    //REGLAS
    //  Entrada1neg, Entrada1pos, Entrada1med; Error
    //  Entrada2vac, Entrada2lle, Entrada2med; Distancia

    float R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12;
    float R1_serv1 = 0; float R1_serv2 = 0;
    float R2_serv1 = 0; float R2_serv2 = 0;
    float R3_serv1 = 0; float R3_serv2 = 0;
    float R4_serv1 = 0; float R4_serv2 = 0;
    float R5_serv1 = 0; float R5_serv2 = 0;
    float R6_serv1 = 0; float R6_serv2 = 0;
    float R7_serv1 = 0; float R7_serv2 = 0;
    float R8_serv1 = 0; float R8_serv2 = 0;
    float R9_serv1 = 0; float R9_serv2 = 0;
    float R10_serv1 = 0; float R10_serv2 = 0;
    float R11_serv1 = 0; float R11_serv2 = 0;
    float R12_serv1 = 0; float R12_serv2 = 0;
    float denominador, servo1, servo2;

    R1 = min(Entrada1neg, Entrada2lle);
    R1_serv1= R1*servo1_cerrado;
    R1_serv2= R1*servo2_abierto;

    R2 = min(Entrada1neg, Entrada2cer);
    R2_serv1= R2*servo1_cerrado;
    R2_serv2= R2*servo2_casi;
    
    R3 = min(Entrada1neg, Entrada2med);
    R3_serv1= R3*servo1_cerrado;
    R3_serv2= R3*servo2_medio;  
                
    R4 = min(Entrada1neg, Entrada2vac);
    R4_serv1= R4*servo1_cerrado;
    R4_serv2= R4*servo2_cerrado;  

    R5 = min(Entrada1med, Entrada2lle);
    R5_serv1= R5*servo1_cerrado;
    R5_serv2= R5*servo2_cerrado;

    R6 = min(Entrada1med, Entrada2cer);
    R6_serv1= R6*servo1_cerrado;
    R6_serv2= R6*servo2_cerrado;  
    
    R7 = min(Entrada1med, Entrada2med);
    R7_serv1= R7*servo1_cerrado;
    R7_serv2= R7*servo2_cerrado;  
                
    R8 = min(Entrada1med, Entrada2vac);
    R8_serv1= R8*servo1_cerrado;
    R8_serv2= R8*servo2_cerrado; 

    R9 = min(Entrada1pos, Entrada2lle);
    R9_serv1= R9*servo1_abierto;
    R9_serv2= R9*servo2_cerrado;

    R10 = min(Entrada1pos, Entrada2cer);
    R10_serv1= R10*servo1_casi;
    R10_serv2= R10*servo2_cerrado;  
    
    R11 = min(Entrada1pos, Entrada2med);
    R11_serv1= R11*servo1_medio;
    R11_serv2= R11*servo2_cerrado;  
                
    R12 = min(Entrada1pos, Entrada2vac);
    R12_serv1= R12*servo1_cerrado;
    R12_serv2= R12*servo2_cerrado; 

    //Calculo de centroides 

    denominador = R1 + R2 + R3 + R4 + R5 + R6 + R7 + R8 + R9+ R10 + R11 + R12;
    servo1 = (R1_serv1 + R2_serv1 + R3_serv1 + R4_serv1 + R5_serv1 + R6_serv1 + R7_serv1 + R8_serv1 + R9_serv1 + R10_serv1 + R11_serv1 + R12_serv1) / denominador;
    servo2 = (R1_serv2 + R2_serv2 + R3_serv2 + R4_serv2 + R5_serv2 + R6_serv2 + R7_serv2 + R8_serv2 + R9_serv2 + R10_serv2 + R11_serv2 + R12_serv2) / denominador;
    
    servo1 = map(servo1,0,43,0,90);
    
    Serial.print("Servo Llenado : ");
    Serial.println(servo1);
    
    Serial.print("Servo Vaciado: ");
    Serial.println(servo2);
    Serial.println(" ");
    miservo2.write(servo1);                 

    servo1 = map(servo1,0,90,180,90);
    
    miservo1.write(servo1);                
    miservo3.write(servo2);


    delay(10000); // tiempo de espera

}


#include <Servo.h>   // incluimos la biblioteca Servo 

Servo miservo1;       // creamos un objecto servo para controlar el motor 
Servo miservo2;       // creamos un objecto servo para controlar el motor 
Servo miservo3;       // creamos un objecto servo para controlar el motor 

float sdistancia = A0; //ir_sensor0
float snivel = A2;

void setup() {
    //initialize serial communications at 9600 bps
    Serial.begin(9600);
    miservo1.attach(9);  // liga el servo al pin 9
    miservo2.attach(11);  // liga el servo al pin 10
    miservo3.attach(10);  // liga el servo al pin 9
    miservo1.write(0);                 //  manda al servo la posicion
    miservo2.write(0);                 //  manda al servo la posicion
    miservo3.write(0);   

}

        
 
void loop() {
    
    //LECTURA DE SENSORES
    
    float distancia, nivel, deseada, actual;

    // Distancia Actual (Sensor Distancia)
    
    distancia = analogRead(sdistancia); // lectura del sensor 0
    actual = pow(3027.4 / distancia, 1.2134); // conversión a centímetros
    Serial.print("Distancia Actual: ");
    actual = map(actual,6,28,28,6);
    Serial.println(actual); // lectura del sensor 0

    // Distancia Deseada (Potenciometro)
    // read the input on analog pin 0:
    nivel = analogRead(snivel);
    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    deseada = nivel * (27 / 1023.0) + 6;
    Serial.print("Nivel Deseado: ");
    deseada = map(deseada,0,27,6,28);

    Serial.println(deseada);


    //FUNCIONES DE MEMBRESIA
    float error;
    float Lectura1, Lectura2;
    float  Entrada1neg, Entrada1pos, Entrada1med;
    float  Entrada2vac, Entrada2lle, Entrada2med;
    float div1, div2, div3, div4, div5, div6;
    float sum1, sum2, sum3, sum4, sum5, sum6;
    float mult1, mult2, mult3, mult4, mult5, mult6;
    error = deseada - actual;
    Lectura1 = error;
    Lectura2 = actual;

    //definicion de constantes de salida//SUGENO
    float servo1_cerrado = 0; //servo1 Llenado
    float servo1_medio = 45;
    float servo1_abierto = 90;
    float servo2_cerrado = 0; //servo2 Vaciado
    float servo2_medio = 45;
    float servo2_abierto = 90;
    //  

    //Funciones Error
    //Funcion de Negativo 
    if (Lectura1 > -2) { Entrada1neg = 0; }
    else if (Lectura1 < -30) { Entrada1neg = 1; }     
    else if (Lectura1 >= -30 && Lectura1 <= -2)
    {
      div1 = -0.03571;
      sum1 = Lectura1 + 2;
      mult1 = div1*sum1; // Ec Recta y = (1/28)(x+2)
      Entrada1neg = mult1;
    } 

    //Funcion de Positivo 
    if (Lectura1 < 2) { Entrada1pos = 0; }
    else if (Lectura1 > 30) { Entrada1pos = 1; }     
    else if (Lectura1 <= 30 && Lectura1 >= 2)
    {
      div2 = 0.03571;
      sum2 = Lectura1 - 2;
      mult2 = div2*sum2; // Ec Recta y = (1/28)(x+2)
      Entrada1pos = mult2;
    } 

    //Funcion de Medio
    if (Lectura1 < -30) { Entrada1med = 0; }
    else if (Lectura1 > 30) { Entrada1med = 0; } 
    else if (Lectura1 == 0) { Entrada1med = 1; }         
    else if (Lectura1 >= -30 && Lectura1 < 0)
    {
      div3 = 0.03333;
      sum3 = Lectura1 + 30;
      mult3 = div3*sum3; // Ec Recta y = (1/28)(x+2)
      Entrada1med = mult3;
    } 
    else if (Lectura1 <= 30 && Lectura1 > 0)
    {
      div3 = -0.03333;
      sum3 = Lectura1 - 30;
      mult3 = div3*sum3; // Ec Recta y = (1/28)(x+2)
      Entrada1med = mult3;
    } 

    //Funciones Nivel Actual
    //Funcion de Vacio 
    if (Lectura2 > 12) { Entrada2vac = 0; }
    else if (Lectura2 < 7) { Entrada2vac = 1; }     
    else if (Lectura2 >= 7 && Lectura2 <= 12)
    {
      div4 = -0.11111;
      sum4 = Lectura2 - 12;
      mult4 = div4*sum4; // Ec Recta y = (1/9)(x-12)
      Entrada2vac = mult4;
    } 

    //Funcion de Lleno 
    if (Lectura2 < 18) { Entrada2lle = 0; }
    else if (Lectura2 > 27) { Entrada2lle = 1; }     
    else if (Lectura2 <= 27 && Lectura2 >= 18)
    {
      div5 = 0.11111;
      sum5 = Lectura2 - 18;
      mult5 = div5*sum5; // Ec Recta y = (1/28)(x+2)
      Entrada2lle = mult5;
    } 

    //Funcion de Medio
    if (Lectura2 < 9) { Entrada2med = 0; }
    else if (Lectura2 > 24) { Entrada2med = 0; } 
    else if (Lectura2 == 15) { Entrada2med = 1; }         
    else if (Lectura2 >= 9 && Lectura2 <= 24)
    {
      div6 = 0.16666;
      sum6 = Lectura2 - 9;
      mult6 = div6*sum6; // Ec Recta y = (1/28)(x+2)
      Entrada2med = mult6;
    } 
    else if (Lectura2 <= 25 && Lectura2 > 15)
    {
      div6 = -0.11111;
      sum6 = Lectura2 - 24;
      mult6 = div6*sum6; // Ec Recta y = (1/28)(x+2)
      Entrada2med = mult6;
    } 

    //REGLAS
    //  Entrada1neg, Entrada1pos, Entrada1med; Error
    //  Entrada2vac, Entrada2lle, Entrada2med; Distancia

    float R1, R2, R3, R4, R5, R6, R7, R8, R9;
    float R1_serv1 = 0; float R1_serv2 = 0;
    float R2_serv1 = 0; float R2_serv2 = 0;
    float R3_serv1 = 0; float R3_serv2 = 0;
    float R4_serv1 = 0; float R4_serv2 = 0;
    float R5_serv1 = 0; float R5_serv2 = 0;
    float R6_serv1 = 0; float R6_serv2 = 0;
    float R7_serv1 = 0; float R7_serv2 = 0;
    float R8_serv1 = 0; float R8_serv2 = 0;
    float R9_serv1 = 0; float R9_serv2 = 0;
    float denominador, servo1, servo2, servo3;
    
    R1 = min(Entrada1med, Entrada2vac);
    R1_serv1= R1*servo1_cerrado;
    R1_serv2= R1*servo2_cerrado;
    
    R2 = min(Entrada1med, Entrada2med);
    R2_serv1= R2*servo1_cerrado;
    R2_serv2= R2*servo2_cerrado;
    
    R3 = min(Entrada1med, Entrada2lle);
    R3_serv1= R3*servo2_cerrado;
    R3_serv2= R3*servo2_cerrado; 
       
    R4 = min(Entrada1neg, Entrada2vac);
    R4_serv1= R4*servo1_cerrado;
    R4_serv2= R4*servo2_medio;  
      
    R5 = min(Entrada1neg, Entrada2med);
    R5_serv1= R5*servo1_cerrado;
    R5_serv2= R5*servo2_medio;  
      
    R6 = min(Entrada1neg, Entrada2lle);
    R6_serv1= R6*servo1_cerrado;
    R6_serv2= R6*servo2_abierto;  
      
    R7 = min(Entrada1pos, Entrada2vac);
    R7_serv1= R7*servo1_abierto;
    R7_serv2= R7*servo2_cerrado;    
    
    R8 = min(Entrada1pos, Entrada2med);
    R8_serv1= R8*servo1_medio;
    R8_serv2= R8*servo2_cerrado;
    
    R9 = min(Entrada1pos, Entrada2lle);
    R9_serv1= R9*servo1_medio;
    R9_serv2= R9*servo2_cerrado;       

    //Calculo de centroides 

    denominador = R1 + R2 + R3 + R4 + R5 + R6 + R7 + R8 + R9;
    servo1 = (R1_serv1 + R2_serv1 + R3_serv1 + R4_serv1 + R5_serv1 + R6_serv1 + R7_serv1 + R8_serv1 + R9_serv1) / denominador;
    servo2 = (R1_serv2 + R2_serv2 + R3_serv2 + R4_serv2 + R5_serv2 + R6_serv2 + R7_serv2 + R8_serv2 + R9_serv2) / denominador;

    Serial.print("Servo Llenado : ");
    Serial.println(servo1);
    Serial.print("Servo Vaciado: ");
    Serial.println(servo2);
    Serial.println(" ");

    servo2 = 90 - servo2;
    servo3 = 90 - servo1;
    miservo1.write(servo3);
    miservo2.write(servo2);
    miservo3.write(servo1);

    delay(1000); // tiempo de espera

}

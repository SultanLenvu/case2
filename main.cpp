
#include "mbed.h"

#include "Sht31.h"  // Датчик влажности и температуры
#include "LIS331.h" // Акселерометр
#include "VL6180.h" // Дальномер
#include <cstdio>

//=============================================================
//  Первая часть лабораторной работы 2
//=============================================================
/*
//sda, scl
Sht31   temp_sensor(I2C_SDA, I2C_SCL);

int main()

{
    float t;
    float h;

    while (true) {
        t = temp_sensor.readTemperature();
        h = temp_sensor.readHumidity();
        printf("%f", t);
        printf(" %f\n\r", h);
        wait_ms(500);
    }
}
*/
/*

Sht31   temp_sensor(I2C_SDA, I2C_SCL);

int main()
{
    // Set 8g range on accel
    accel.setFullScaleRange8g();
    printf("Accel Address:%x\n\r",accel.getWhoAmI());
    float x, y, z;

    while (1) {
        x = accel.getAccelX();
        y = accel.getAccelY();
        z = accel.getAccelZ();
        printf("%f, %f, %f \n\r", x, y, z);
        wait_ms(500);
    }
}
*/

/*
VL6180 rf(I2C_SDA, I2C_SCL); //I2C sda and scl

int main()
{
    float reading;
    while(1) {
        reading = rf.read();
        printf("Read %4.1f cm\n", reading);
        wait_ms(500);
    }
}
*/

//=============================================================
//  Вторая часть лабораторной работы 2
//=============================================================

/*

void print_char(char c = '*')
{
    printf("%c", c);
    fflush(stdout);
}

Thread thread;

DigitalOut led1(LED1);

void print_thread()
{
    while (true) {
        wait(1);
        print_char();
    }
}

int main()
{
    printf("\n\n*** RTOS basic example ***\n");
    thread.start(print_thread);
    while (true) {
        led1 = !led1;
        wait(0.5);
    }
}


*/

//=============================================================
//  Практикум лабораторной работы 2
//=============================================================

#define MEASURING_FREQUENCY 0.5
#define UPPER_LIMIT 0.4 
#define LOWER_LIMIT 0.2

//sda, scl
//Sht31   humidity_sensor(I2C_SDA, I2C_SCL);
AnalogIn adc(PA_7);

DigitalOut led1(LED1);
Ticker sensor_timer; // Used for debouncing

Thread thread;

volatile float blinkingFrequency = 1.0;

void blinking(void){
    while(1) {
        led1 = !led1;
        wait(blinkingFrequency);
    }
}

void measureHumidity(void) {
    float h = 0;
    
    //h = humidity_sensor.readHumidity();
    h = adc.read();

    if ((h > 0.2) || (h < 0.4)){
        blinkingFrequency = 0.25;
        printf("WARNING: Humidity is out of tolerance limits: %f\n", h);
        fflush(stdout);
    }
    else {
        blinkingFrequency = 1;
        printf("Current humidity: %f\n", h);
        fflush(stdout);
    }
}

int main() {
    //sensor_timer.attach(&measureHumidity, MEASURING_FREQUENCY);
    //led_timer.attach(&blinking, blinkingFrequency);

    thread.start(blinking);

    while(1) {
        measureHumidity();
        wait(1);
    }
}



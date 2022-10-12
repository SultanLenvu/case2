
#include "mbed.h"

#include "Sht31.h"
#include "LIS331.h"
#include "VL6180.h"

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
DigitalOut led1(LED1);

InterruptIn button1(USER_BUTTON);
volatile bool button1_pressed = false; // Used in the main loop
volatile bool button1_enabled = true; // Used for debouncing
Timeout button1_timeout; // Used for debouncing

// Enables button when bouncing is over
void button1_enabled_cb(void)
{
    button1_enabled = true;
}

// ISR handling button pressed event
void button1_onpressed_cb(void)
{
    if (button1_enabled) { // Disabled while the button is bouncing
        button1_enabled = false;
        button1_pressed = true; // To be read by the main loop
        button1_timeout.attach(callback(button1_enabled_cb), 0.3); // Debounce time 300 ms
    }
}

int main()
{
    //button1.mode(PullUp); // Activate pull-up
    button1.fall(callback(button1_onpressed_cb)); // Attach ISR to handle button press event

    int idx = 0; // Just for printf below

    while(1) {
        if (button1_pressed) { // Set when button is pressed
            button1_pressed = false;
            printf("Button pressed %d\n", idx++);
            led1 = !led1;
        }
    }
}
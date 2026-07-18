#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdio_rtt.h" // Needed if you want to use stdio_rtt_init()

#define BUFFER_SIZE 256

int main()
{
    // stdio_init_all(); // will init rtt, plus uart anbd/or USB if you have enabled these

    stdio_rtt_init();   // all you need if using rtt only, must #include "pico/stdio_rtt.h"

    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    uint32_t count = 0;
    char buffer[BUFFER_SIZE];
    
    while (true) {
        count++;

        // output using puts()
        puts("On");
        gpio_put(LED_PIN, 1); // Turn LED ON
        sleep_ms(1000);       // Wait 1 second

        // Demonstrate on way to read from the rtt stream
        int c = getchar_timeout_us(0); 
        int ci = 0;
        if (c != PICO_ERROR_TIMEOUT) {
            buffer[ci++] = (char)c;
        }
        while (c != PICO_ERROR_TIMEOUT && ci < BUFFER_SIZE - 1) {
            c = getchar_timeout_us(0);
            if (c != PICO_ERROR_TIMEOUT) {
                buffer[ci++] = (char)c; 
            }
        }
        if (ci != 0) {
            buffer[ci] = 0;
            printf ("Received: %s\n", buffer);
        }

        // Output using printf
        printf("Off. This was loop number %d\n", count);
        gpio_put(LED_PIN, 0); // Turn LED OFF
        sleep_ms(1000);       // Wait 1 second
    }
}

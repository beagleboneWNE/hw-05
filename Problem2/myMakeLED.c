/** 
 * Program: myMakeLED
 * Description: Controls an LED on the BeagleBone. 
 *              If an invalid command is given, it blinks the LED at a 1-second ON/OFF cycle.
 * Command Line Arguments:
 *     - "on"  → Turns the LED ON
 *     - "off" → Turns the LED OFF
 *     - "flash" → Blinks LED at 50ms intervals
 *     - "status" → Displays current LED trigger status
 *     - Invalid argument → Prints error and blinks LED (1s ON, 1s OFF)
 * Example Invocations:
 *     sudo ./myMakeLED on
 *     sudo ./myMakeLED off
 *     sudo ./myMakeLED flash
 *     sudo ./myMakeLED status
 *     sudo ./myMakeLED invalid  (This will blink the LED)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(char filename[], char value[]);
void removeTrigger();
void blinkLED();  // Function to blink the LED for invalid commands

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <on|off|flash|status>\n", argv[0]);
        return 1;
    }

    printf("Starting the myMakeLED program\n");
    printf("The current LED Path is: " LED3_PATH "\n");

    // Select whether command is on, off, flash, or status
    if (strcmp(argv[1], "on") == 0) {
        printf("Turning the LED on\n");
        removeTrigger();
        writeLED("/brightness", "1");
    } 
    else if (strcmp(argv[1], "off") == 0) {
        printf("Turning the LED off\n");
        removeTrigger();
        writeLED("/brightness", "0");
    } 
    else if (strcmp(argv[1], "flash") == 0) {
        printf("Flashing the LED\n");
        writeLED("/trigger", "timer");
        writeLED("/delay_on", "50");
        writeLED("/delay_off", "50");
    } 
    else if (strcmp(argv[1], "status") == 0) {
        FILE* fp;
        char fullFileName[100];
        char line[80];
        sprintf(fullFileName, LED3_PATH "/trigger");
        fp = fopen(fullFileName, "rt");  // Reading text
        if (fp == NULL) {
            printf("Error: Unable to read LED status!\n");
            return 1;
        }
        while (fgets(line, 80, fp) != NULL) {
            printf("%s", line);
        }
        fclose(fp);
    } 
    else {
        printf("Invalid command! Blinking LED...\n");
        blinkLED();  // Start blinking LED
    }

    printf("Finished the myMakeLED Program\n");
    return 0;
}

// Function to write values to LED control files
void writeLED(char filename[], char value[]) {
    FILE* fp;
    char fullFileName[100];
    sprintf(fullFileName, LED3_PATH "%s", filename);
    fp = fopen(fullFileName, "w+");
    if (fp == NULL) {
        printf("Error: Unable to access %s\n", fullFileName);
        return;
    }
    fprintf(fp, "%s", value);
    fclose(fp);
}

// Function to remove trigger before setting brightness
void removeTrigger() {
    writeLED("/trigger", "none");
}

// Function to blink LED at 1-second intervals for invalid commands
void blinkLED() {
    while (1) {
        writeLED("/brightness", "1");  // Turn LED ON
        sleep(1);
        writeLED("/brightness", "0");  // Turn LED OFF
        sleep(1);
    }
}


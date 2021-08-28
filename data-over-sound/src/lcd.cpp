#include "dlog.h"
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "data-over-sound"

#if !defined(PACKAGE)
#define PACKAGE "org.example.data-over-sound"
#endif

#define LCD_ADDR (0x27)
#define I2C_BUS_NUMBER (7)

extern "C" {
void initLcd() {
	lcd.begin();
	lcd.backlight();
	lcd.clear();
}

void setLcd(char* message1, char* message2)
{
	/*
    int ret;
    peripheral_i2c_h i2c = NULL;

    ret = peripheral_i2c_open(I2C_BUS_NUMBER, LCD_ADDR, &i2c);
    if (ret != PERIPHERAL_ERROR_NONE) {
        return;
    }
    peripheral_i2c_write(i2c, message, strlen(message));
	peripheral_i2c_close(i2c);
	*/
	dlog_print(DLOG_ERROR, LOG_TAG, "setLcd Called");


	lcd.setCursor(0, 0); // Set the cursor on the third column and first row.
	lcd.print(message1); // Print the string "Hello World!"
	lcd.setCursor(0, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
	lcd.print(message2);
}

}

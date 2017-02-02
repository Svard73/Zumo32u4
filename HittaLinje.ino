#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motor;

unsigned int lineSensorValues[5];

void setup()
{
	lineSensors.initFiveSensors();
	loadCustomCharacters();
}


void loadCustomCharacters()
{
	static const char levels[] PROGMEM = {
		0, 0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63
	};
	lcd.loadCustomCharacter(levels + 0, 0);  // 1 bar
	lcd.loadCustomCharacter(levels + 1, 1);  // 2 bars
	lcd.loadCustomCharacter(levels + 2, 2);  // 3 bars
	lcd.loadCustomCharacter(levels + 3, 3);  // 4 bars
	lcd.loadCustomCharacter(levels + 4, 4);  // 5 bars
	lcd.loadCustomCharacter(levels + 5, 5);  // 6 bars
	lcd.loadCustomCharacter(levels + 6, 6);  // 7 bars
}

void printBar(uint8_t height)
{
	if (height > 8) { height = 8; }
	const char barChars[] = { ' ', 0, 1, 2, 3, 4, 5, 6, 255 };
	lcd.print(barChars[height]);
}

void printReadingsToLCD()
{
	// On the first line of the LCD, display the bar graph.
	lcd.gotoXY(0, 0);
	for (uint8_t i = 0; i < 5; i++)
	{
		uint8_t barHeight = map(lineSensorValues[i], 0, 2000, 0, 8);
		printBar(barHeight);
	}

	// On the second line of the LCD, display one raw reading.
	lcd.gotoXY(1, 1);


}

void loop()
{
	printReadingsToLCD();
	lineSensors.read(lineSensorValues, true);

	int16_t position = lineSensors.readLine(lineSensorValues) -2000;



	//delay(500);


	motor.setSpeeds(100, 100);
	if (position<-2)
		motor.setSpeeds(10, 200);
	else if(position>2)
		motor.setSpeeds(200, 10);
	

	lcd.print(position);
	delay(10);
	/* add main program code here */

}

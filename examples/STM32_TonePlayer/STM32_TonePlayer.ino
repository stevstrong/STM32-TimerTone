
#include <TimerTone.h>
#include "melody.h"

const uint8_t speaker_pins[] = {PA8, PA0, PA6, PB6}; // timer1 ch1, timer2 ch1, timer3 ch1, timer4 ch1

const uint8_t BUTTON = PB3;

const uint8_t * const scores[] = {score1, score2, score3};

uint8_t score_nr;
uint32_t time;

enum {CHANNEL_1 = BIT0, CHANNEL_2 = BIT1, CHANNEL_3 = BIT2, CAHNNEL_4 = BIT3 };
//-----------------------------------------------------------------------------
void Blink(void)
{
	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
//-----------------------------------------------------------------------------
void setup()
{
	Serial.begin(115200);
	//while (!Serial) ; delay(1000);

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	
	pinMode(BUTTON, INPUT_PULLUP);
	
	uint8_t t_break = 2; // millisecond break between consecutive tones

	if ( !toneSetup(speaker_pins, t_break) ) {
		Serial << ("Tone player could not be initialized, invalid speaker pin (no timer associated)!\n\n") <<
		("Try again with a PWM compatible pin.\n");
		while(1); // halt
	}
	Serial << ("Tone player initialized.\n\n");

	time = millis()+3000;
}
//-----------------------------------------------------------------------------
uint8_t Check_button()
{
	uint8_t cnt = 0;
	for (uint8_t i = 0; i<5; i++) {
		if ( !digitalRead(BUTTON) ) cnt++;
		delay(10);
	}
	if (cnt==5) return true;
	else return false;	
}
//-----------------------------------------------------------------------------
void loop()
{
	if ( isPlaying() ) {

		if ( isPlayingBreak( (CHANNEL_1) ) ) // + CHANNEL_2 + CHANNEL_3 + CAHNNEL_4) ) ) // more channels can be added.
			digitalWrite(LED_BUILTIN, HIGH);
		else
			digitalWrite(LED_BUILTIN, LOW);

		time = millis();

	} else {

		digitalWrite(LED_BUILTIN, HIGH);

		if (  (millis()-time)>3000 ) {

			if ( score_nr>=(sizeof(scores)/sizeof(uint8_t *)) )
				score_nr = 0;

			tonePlay( scores[score_nr++] );
		}
	}
	
	if ( Check_button() ) { // button pressed ?
		while ( Check_button() ) delay(10); // wait for button release
		toneStop();
		time = millis()+3000;
		Serial << ("tone stopped.\n");
	}
	
}

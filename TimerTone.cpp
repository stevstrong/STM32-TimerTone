
#include "TimerTone.h"

const uint8_t LED_PIN = PC13;
const uint8_t DBG_PIN = PC14;
const uint8_t DBG_PIN2 = PC15;

#define SET_PIN(pin, s) digitalWrite((pin), (s))
#define SET_PIN(pin, s) digitalWrite((pin), (s))

#define SET_PIN_HIGH(pin)SET_PIN((pin), HIGH)
#define SET_PIN_LOW(pin) SET_PIN((pin), LOW)
/**/
//-----------------------------------------------------------------------------
static volatile uint16_t ticks;
static volatile uint16_t playing_tone[4];
static volatile uint16_t next_tone[4];
static volatile uint16_t channel[4];
static volatile voidFuncPtr isr[4];
static timer_dev * const hwTimer[4] = {TIMER1, TIMER2, TIMER3, TIMER4};
static volatile const uint8_t *ptr, *score;
static uint32_t time;
static uint8_t tone_break;

volatile uint8_t tone_playing;
//-----------------------------------------------------------------------------
void playTone(uint8_t tim_nr, uint16_t note);
//void playToneTimed(uint8_t tim_nr, uint16_t note, uint16_t dur);
void playPause(uint16_t dur);
void stopTone(uint8_t tim_nr);
void playNext(void);
//-----------------------------------------------------------------------------
void systick_isr()
{
	if ( ticks ) {
		if ( (--ticks)==0 )
			playNext();
	}
}
//-----------------------------------------------------------------------------
void playNext(void)
{
	while (1) {
		uint8_t dat = *ptr++;
		if ( dat&BIT7 ) {
			// control byte
			if ( (dat&0xF0)==0x90 ) { // play tone
				uint8_t pitch = *ptr++; // read pitch
				if ( (dat&=0x0F)<4 ) {
					uint16_t t = pitches[pitch];
					playTone(dat, t); // play previously parsed channel
					//Serial << ("Time: ") << time << (", pos: ") << (uint32_t)(ptr-score-1) << (": play channel: ") << (dat) << (", pitch: ") << (pitch) << endl;
					//if (dat==0) {
						Serial << ("playTone(") << (dat) << (", ") << (t) << (");") << endl;
					//}
					//Serial << ("play channel: ") << (dat) << (", pitch: ") << (pitch) << endl;
				}
			} else if ( (dat&0xF0)==0x80 ) { // end of a tone
				if ( (dat&=0x0F)<4 ) {
					stopTone(dat);
					//Serial << ("Time: ") << time << (", pos: ") << (uint32_t)(ptr-score-1) << (": stop channel: ") << dat << endl;
					//Serial << ("stop channel: ") << dat << endl;
					//if (dat==0) {
						Serial << ("stopTone(") << (dat) << (");") << endl;
					//}
				}
			} else if ( (dat&0xF0)==0xF0 ) {
				// end of stream. Stop playing
				Serial << ("Time: ") << time << (", pos: ") << (uint32_t)(ptr-score-1) << (": play finished.") << endl;
				tone_playing = false;
				break;
			} else {
				// not supported control, neglect this
				Serial << ("Time: ") << time << (", pos: ") << (uint32_t)(ptr-score-1) << (": unsknown control byte: ") << _HEX(dat) << endl;
				//dat = *ptr++; // dummy read, optional
				tone_playing = false;
			}
		} else {
			// this is delay data.
			uint16_t tmp = (dat<<8) + (*ptr++);
			if (tmp==0) continue;
			//Serial << ("Time: ") << time << (", pos: ") << (uint32_t)(ptr-score-2) << (": delay: ") << tmp << endl;
			playPause(tmp);
			Serial << ("delay(") << tmp << (");") << endl;
			time += tmp;
			break;
		}
	}
}
//-----------------------------------------------------------------------------
void playTone(uint8_t tim_nr, uint16_t note)
{
	timer_dev * timer = hwTimer[tim_nr];
	timer_pause(timer);
	if ( playing_tone[tim_nr] ) {
		next_tone[tim_nr] = note;
		timer_resume(timer);
		return;
	}
	playing_tone[tim_nr] = note;
	timer_detach_interrupt(timer, 0);
	timer_detach_interrupt(timer, channel[tim_nr]);
	timer_set_prescaler(timer, 72); // 1µsec clock
	uint32_t reload = (1000000/note);
	timer_set_reload(timer, reload-1); // x2);
	timer_set_compare(timer, channel[tim_nr], reload>>1); // 50% duty cycle
	timer_generate_update(timer);
	timer_resume(timer);
}
//-----------------------------------------------------------------------------
void playPause(uint16_t dur)
{
	ticks = dur;
}
//-----------------------------------------------------------------------------
void stopTone(uint8_t tim_nr)
{
	if ( playing_tone[tim_nr] ) {
		// soft stop
		timer_dev * timer = hwTimer[tim_nr];
		timer_pause(timer);
		timer_attach_interrupt(timer, channel[tim_nr], isr[tim_nr]);
		timer_resume(timer);
	}
}
//-----------------------------------------------------------------------------
void Timer_Isr(uint8_t tim_nr)
{
	timer_dev * timer = hwTimer[tim_nr];
	timer_pause(timer);
	uint8_t chan = channel[tim_nr];
	timer_detach_interrupt(timer, chan);
	if ( timer_get_compare(timer, chan)>0 ) {	// last half
		timer_set_compare(timer, chan, 0); // 0% duty cycle
		timer_attach_interrupt(timer, 0, isr[tim_nr]);
		timer_resume(timer);
		return;
	}
	uint16_t ton = next_tone[tim_nr];
	if ( ton ) {
		if ( tone_break && !(ton&BIT15)) { // playing break	
			timer_set_prescaler(timer, 36000); // 0,5 msec clock
			timer_set_reload(timer, (tone_break<<1)-1); // x2);
			timer_detach_interrupt(timer, 0);
			timer_generate_update(timer);
			timer_attach_interrupt(timer, 0, isr[tim_nr]);
			timer_resume(timer);
		
			next_tone[tim_nr] = (ton | BIT15);
			if ( tim_nr==0) SET_PIN_LOW(DBG_PIN);

		} else { // play next tone
			next_tone[tim_nr] = 0;
			// reconfigure timer
			uint16_t reload = (1000000ul/(ton&0x7FFF));; // remove 1 period break mark
			timer_detach_interrupt(timer, 0);
			timer_set_prescaler(timer, 72); // 1µsec clock
			timer_set_reload(timer, reload-1); // x2);
			timer_set_compare(timer, chan, reload>>1); // 50% duty cycle
			timer_generate_update(timer);
			timer_resume(timer);
			if ( tim_nr==0) SET_PIN_HIGH(DBG_PIN);
		}
	} else {
		timer_detach_interrupt(timer, 0);
		playing_tone[tim_nr] = false;
	}
}
//-----------------------------------------------------------------------------
void Timer1_Isr(void)
{
	Timer_Isr(0);
}
//-----------------------------------------------------------------------------
void Timer2_Isr(void)
{
	Timer_Isr(1);
}
//-----------------------------------------------------------------------------
void Timer3_Isr(void)
{
	Timer_Isr(2);
}
//-----------------------------------------------------------------------------
void Timer4_Isr(void)
{
	Timer_Isr(3);
}
//-----------------------------------------------------------------------------
uint8_t isPlaying(void) { return tone_playing; }
//-----------------------------------------------------------------------------
uint8_t isPlayingBreak(uint8_t mask)
{
	for (uint8_t i = 0; i<4; i++) {
		if ( mask&BIT(i) && playing_tone[i] ) return false;
	}
	return true;
}
//-----------------------------------------------------------------------------
uint8_t toneSetup(const uint8_t * timerPins, uint8_t br)
{
	tone_break = br;
	for (uint8_t i = 0; i<4; i++) {
		uint8_t pin = timerPins[i];
		uint8_t chan = PIN_MAP[pin].timer_channel;
		channel[i] = chan;
		if ( chan==0 ) return 0;
		pinMode(pin, PWM);
		next_tone[i] = 0;
		playing_tone[i] = false;
		timer_pause(hwTimer[i]);
	}
	isr[0] = Timer1_Isr;
	isr[1] = Timer2_Isr;
	isr[2] = Timer3_Isr;
	isr[3] = Timer4_Isr;
	ticks = 0;
	systick_attach_callback(systick_isr);
	return true;
}
//-----------------------------------------------------------------------------
void tonePlay(const uint8_t * melody)
{
	ptr = score = melody;
	time = 0;
	tone_playing = true;
	playPause(1);
}
//-----------------------------------------------------------------------------
void toneStop(void)
{
	ticks = 0;
	//systick_attach_callback(NULL);
	for (uint8_t i = 0; i<4; i++) {
		stopTone(i);
		while ( playing_tone[i] );
	}
	tone_playing = false;
}

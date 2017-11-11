
#include <Arduino.h>
#include <Streaming.h>

#include "pitches.h"


extern uint8_t toneSetup(const uint8_t * pins, uint8_t br);
extern void tonePlay(const uint8_t * melody);
extern void toneStop(void);

extern void playTone(uint8_t tim_nr, uint16_t note);
extern void stopTone(uint8_t tim_nr);

extern uint8_t isPlaying(void);
extern uint8_t isPlayingBreak(uint8_t mask);


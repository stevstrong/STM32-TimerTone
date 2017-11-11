/*************************************************
 * Public Constants
 *************************************************/

#define NOTE_C0  16
#define NOTE_CS0 17
#define NOTE_D0  18
#define NOTE_DS0 19
#define NOTE_E0  21
#define NOTE_F0  22
#define NOTE_FS0 23
#define NOTE_G0  24
#define NOTE_GS0 26
#define NOTE_A0  28
#define NOTE_AS0 29
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

const uint16_t pitches[] = {
	0  ,
	NOTE_C0 ,
    NOTE_CS0,
    NOTE_D0 ,
    NOTE_DS0,
    NOTE_E0 ,
    NOTE_F0 ,
    NOTE_FS0,
    NOTE_G0 ,
    NOTE_GS0,
    NOTE_A0 ,
    NOTE_AS0,
	NOTE_B0 ,
    NOTE_C1 ,
    NOTE_CS1,
    NOTE_D1 ,
    NOTE_DS1,
    NOTE_E1 ,
    NOTE_F1 ,
    NOTE_FS1,
    NOTE_G1 ,
    NOTE_GS1,
    NOTE_A1 ,
    NOTE_AS1,
    NOTE_B1 ,
    NOTE_C2 ,
    NOTE_CS2,
    NOTE_D2 ,
    NOTE_DS2,
    NOTE_E2 ,
    NOTE_F2 ,
    NOTE_FS2,
    NOTE_G2 ,
    NOTE_GS2,
    NOTE_A2 ,
    NOTE_AS2,
    NOTE_B2 ,
    NOTE_C3 ,
    NOTE_CS3,
    NOTE_D3 ,
    NOTE_DS3,
    NOTE_E3 ,
    NOTE_F3 ,
    NOTE_FS3,
    NOTE_G3 ,
    NOTE_GS3,
    NOTE_A3 ,
    NOTE_AS3,
    NOTE_B3 ,
    NOTE_C4 ,
    NOTE_CS4,
    NOTE_D4 ,
    NOTE_DS4,
    NOTE_E4 ,
    NOTE_F4 ,
    NOTE_FS4,
    NOTE_G4 ,
    NOTE_GS4,
    NOTE_A4 ,
    NOTE_AS4,
    NOTE_B4 ,
    NOTE_C5 ,
    NOTE_CS5,
    NOTE_D5 ,
    NOTE_DS5,
    NOTE_E5 ,
    NOTE_F5 ,
    NOTE_FS5,
    NOTE_G5 ,
    NOTE_GS5,
    NOTE_A5 ,
    NOTE_AS5,
    NOTE_B5 ,
    NOTE_C6 ,
    NOTE_CS6,
    NOTE_D6 ,
    NOTE_DS6,
    NOTE_E6 ,
    NOTE_F6 ,
    NOTE_FS6,
    NOTE_G6 ,
    NOTE_GS6,
    NOTE_A6 ,
    NOTE_AS6,
    NOTE_B6 ,
    NOTE_C7 ,
    NOTE_CS7,
    NOTE_D7 ,
    NOTE_DS7,
    NOTE_E7 ,
    NOTE_F7 ,
    NOTE_FS7,
    NOTE_G7 ,
    NOTE_GS7,
    NOTE_A7 ,
    NOTE_AS7,
    NOTE_B7 ,
    NOTE_C8 ,
    NOTE_CS8,
    NOTE_D8 ,
    NOTE_DS8,
	0xFF
};

enum {
	pause = 0, // 0
	c0 , //  1
    cs0, //  2 
    d0 , //  3 
    ds0, //  4 
    e0 , //  5 
    f0 , //  6 
    fs0, //  7 
    g0 , //  8 
    gs0, //  9 
    a0 , // 10 
    as0, // 11 
	b0 , // 12
    c1 , // 13
    cs1, // 14
    d1 , // 15
    ds1, // 16
    e1 , // 17
    f1 , // 18
    fs1, // 19
    g1 , // 20
    gs1, // 21
    a1 , // 22
    as1, // 23
    b1 , // 24
    c2 , // 25
    cs2, // 26
    d2 , // 27
    ds2, // 28
    e2 , // 29
    f2 , // 30
    fs2, // 31
    g2 , // 32
    gs2, // 33
    a2 , // 34
    as2, // 35
    b2 , // 36
    c3 , // 37
    cs3, // 38
    d3 , // 39
    ds3, // 40
    e3 , // 41
    f3 , // 42
    fs3, // 43
    g3 , // 44
    gs3, // 45
    a3 , // 46
    as3, // 47
    b3 , // 48
    c4 , // 49
    cs4, // 50
    d4 , // 51
    ds4, // 52
    e4 , // 53
    f4 , // 54
    fs4, // 55
    g4 , // 56
    gs4, // 57
    a4 , // 58
    as4, // 59
    b4 , // 60
    c5 , //
    cs5, //
    d5 , //
    ds5, //
    e5 , //
    f5 , //
    fs5, //
    g5 , //
    gs5, //
    a5 , //
    as5, //
    b5 , //
    c6 , //
    cs6, //
    d6 , //
    ds6, //
    e6 , //
    f6 , //
    fs6, //
    g6 , //
    gs6, //
    a6 , //
    as6, //
    b6 , //
    c7 , //
    cs7, //
    d7 , //
    ds7, //
    e7 , //
    f7 , //
    fs7, //
    g7 , //
    gs7, //
    a7 , //
    as7, //
    b7 , //
    c8 , //
    cs8, //
    d8 , //
    ds8, //
	LAST_NOTE
};
#include <TrinketKeyboard.h>
#include <EEPROM.h>
#define SETUP_IDX 8
#define BROWSEPIN 0
#define ENTERPIN 1
#define DATAPIN 2
char UPDATE_STR[] = {'U','p','d','a','t','e',' ','p','s','w',' ','D','B','\0','\0','\0'};
char label[8];
char pswd[16];
unsigned char index, releasedB,releasedE;


void LCD1WireSend(unsigned char b) {
	char i;  //28 0010 1000

	for (i=7;i>0;i--) {
		if ((b>>i)&0x1) { // send 1
			digitalWrite(DATAPIN,LOW);
			delayMicroseconds(2);
			digitalWrite(DATAPIN,HIGH);
			delayMicroseconds(200);
			} else { // send 0
				digitalWrite(DATAPIN,LOW);
				delayMicroseconds(120);
				digitalWrite(DATAPIN,HIGH);
				delayMicroseconds(480);
				}
			}
	// send latch
	digitalWrite(DATAPIN,LOW);
	delayMicroseconds(460);
	digitalWrite(DATAPIN,HIGH);
	delayMicroseconds(1700);
	TrinketKeyboard.poll();
}

void LCDinit() {

	LCD1WireSend(0x28);
	LCD1WireSend(0x20); //init 4bit mode
	LCD1WireSend(0x08); 
	LCD1WireSend(0x00); //first nibble
	LCD1WireSend(0xc8);
	LCD1WireSend(0xc0); //second nibble clearscreen home show cursor
}

void LCDChar(unsigned char c) {
	LCD1WireSend( (c & 0xf0) | 0x0a);
	LCD1WireSend( (c & 0xf0) | 0x02);
	LCD1WireSend( c<<4 | 0x0a);
	LCD1WireSend( c<<4 | 0x02);
}

void LCDWrite(char *st) {

	while (*st != 0) {
		LCDChar(*st);
		st++;
		}
}

void LCDClear() {

	LCD1WireSend(0x08);
	LCD1WireSend(0x00); //first nibble
	LCD1WireSend(0xf8);
	LCD1WireSend(0xf0); //second nibble clearscreen home show cursor
}

void LCDGotoN(unsigned char n){

	 LCD1WireSend(0x88|n&70);
	 LCD1WireSend(0x80|n&70);
	 LCD1WireSend(n<<4|0x8);
	 LCD1WireSend(n<<4);
}

void LCDCLS() {
	LCD1WireSend(0x08);
	LCD1WireSend(0x00);
	LCD1WireSend(0x18);
	LCD1WireSend(0x10);
}


void evaluateBitString(unsigned char b, char *buf) {

	for (int i=0; i<8; i++) 
		if ((b>>i)&1) *(buf+7-i)=0x31; 
			else *(buf+7-i)=0x30;
}

/*
 * serial communication over keyboard status leds
 * use CapsLock as MOSI
   *    NumLock as CLK
   * ScrollLock as LATCH
 */

void download_psw_db() {
	char inprogress=1;
	char prevClk;
	char buffer_sreg;
	unsigned char cnt=0;

	LCDCLS();
	LCDWrite("Updating DB...");

	while (inprogress) {
		TrinketKeyboard.poll();
		unsigned char led=TrinketKeyboard.getLEDstate();
		if (!(led & KB_LED_NUM) && prevClk) {
			buffer_sreg=(buffer_sreg<<1) |(led & KB_LED_CAPS?1:0);
			if ((led & KB_LED_SCROLL)) {
				EEPROM.write(cnt,buffer_sreg);
				cnt++;
				digitalWrite(ENTERPIN,cnt&1);
				if (cnt>=192) inprogress=0;
				}
                                                          
			}
		prevClk=(led & KB_LED_NUM)?1:0;
		}
}

void send_keystrokes(char *psw) {
	unsigned char i=0;

	while (*(psw+i)) {
		TrinketKeyboard.pressKey(*(psw+i)>>6?2:0,*(psw+i)&0x3f);
		TrinketKeyboard.pressKey(0, 0);
		i++;
		}
}

void setup() {

	TrinketKeyboard.begin();
	pinMode(DATAPIN,OUTPUT);
	pinMode(BROWSEPIN,INPUT);
	pinMode(ENTERPIN,INPUT);
	releasedB=1;
	releasedE=1;
	index=0;
	LCDinit();
	LCDWrite("Password Keeper");
	LCDGotoN(0x40);
	LCDWrite("Rev 0.1");
	for (char i=0;i<20;i++) {
		TrinketKeyboard.poll();
		delay(100);
		}
	LCDCLS();
	for(char i=0;i<8;i++) label[i]=EEPROM.read(8*index+i);
	LCDWrite(label);
}

void loop() {
	TrinketKeyboard.poll();
	if (digitalRead(BROWSEPIN) & releasedB ){
		index=(index+1);
		if (index>SETUP_IDX) index=0;
		LCDCLS();
		if (index!=SETUP_IDX) {
			for(char i=0;i<8;i++) label[i]=EEPROM.read(8*index+i);
			LCDWrite(label);
			} else LCDWrite(UPDATE_STR);
		releasedB=0;
		} else {
			if (!digitalRead(BROWSEPIN)) releasedB=1;
			}
	if (digitalRead(ENTERPIN) & releasedE ){
		if (index==SETUP_IDX) {
//			pinMode(ENTERPIN,OUTPUT);
			download_psw_db();
//			pinMode(ENTERPIN,INPUT);
			index=0;
			LCDCLS();
			for(char i=0;i<8;i++) label[i]=EEPROM.read(8*index+i);
			LCDWrite(label);
			} else {
				for(char i=0;i<16;i++) pswd[i]=EEPROM.read(64+16*index+i);
				send_keystrokes(pswd);
				}
			releasedE=0;
			} else {
				if (!digitalRead(ENTERPIN)) releasedE=1;
				}
}

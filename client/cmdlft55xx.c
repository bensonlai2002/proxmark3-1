//-----------------------------------------------------------------------------
//
// This code is licensed to you under the terms of the GNU GPL, version 2 or,
// at your option, any later version. See the LICENSE.txt file for the text of
// the license.
//-----------------------------------------------------------------------------
// Low frequency T55xx commands
//-----------------------------------------------------------------------------
#include "cmdlft55xx.h"

// Default configuration
t55xx_conf_block_t config = { .modulation = DEMOD_ASK, .inverted = false, .offset = 0x00, .block0 = 0x00, .Q5 = false };

t55xx_conf_block_t Get_t55xx_Config(){
	return config;
}
void Set_t55xx_Config(t55xx_conf_block_t conf){
	config = conf;
}

int usage_t55xx_config(){
	PrintAndLogEx(NORMAL, "Usage: lf t55xx config [d <demodulation>] [i 1] [o <offset>] [Q5]");
	PrintAndLogEx(NORMAL, "Options:");
	PrintAndLogEx(NORMAL, "       h                                - This help");
	PrintAndLogEx(NORMAL, "       b <8|16|32|40|50|64|100|128>     - Set bitrate");
	PrintAndLogEx(NORMAL, "       d <FSK|FSK1|FSK1a|FSK2|FSK2a|ASK|PSK1|PSK2|NRZ|BI|BIa>  - Set demodulation FSK / ASK / PSK / NRZ / Biphase / Biphase A");
	PrintAndLogEx(NORMAL, "       i [1]                            - Invert data signal, defaults to normal");
	PrintAndLogEx(NORMAL, "       o [offset]                       - Set offset, where data should start decode in bitstream");
	PrintAndLogEx(NORMAL, "       Q5                               - Set as Q5(T5555) chip instead of T55x7");
	PrintAndLogEx(NORMAL, "       ST                               - Set Sequence Terminator on");
	PrintAndLogEx(NORMAL, "");
	PrintAndLogEx(NORMAL, "Examples:");
	PrintAndLogEx(NORMAL, "      lf t55xx config d FSK          - FSK demodulation");
	PrintAndLogEx(NORMAL, "      lf t55xx config d FSK i 1      - FSK demodulation, inverse data");
	PrintAndLogEx(NORMAL, "      lf t55xx config d FSK i 1 o 3  - FSK demodulation, inverse data, offset=3,start from position 3 to decode data");
	PrintAndLogEx(NORMAL, "");
	return 0;
}
int usage_t55xx_read(){
	PrintAndLogEx(NORMAL, "Usage:  lf t55xx read [b <block>] [p <password>] <override_safety> <page1>");
	PrintAndLogEx(NORMAL, "Options:");
	PrintAndLogEx(NORMAL, "     b <block>    - block number to read. Between 0-7");
	PrintAndLogEx(NORMAL, "     p <password> - OPTIONAL password (8 hex characters)");
	PrintAndLogEx(NORMAL, "     o            - OPTIONAL override safety check");
	PrintAndLogEx(NORMAL, "     1            - OPTIONAL read Page 1 instead of Page 0");
	PrintAndLogEx(NORMAL, "     ****WARNING****");
	PrintAndLogEx(NORMAL, "     Use of read with password on a tag not configured for a pwd");
	PrintAndLogEx(NORMAL, "     can damage the tag");
    PrintAndLogEx(NORMAL, "");
	PrintAndLogEx(NORMAL, "Examples:");
    PrintAndLogEx(NORMAL, "      lf t55xx read b 0				- read data from block 0");
	PrintAndLogEx(NORMAL, "      lf t55xx read b 0 p feedbeef		- read data from block 0 password feedbeef");
	PrintAndLogEx(NORMAL, "      lf t55xx read b 0 p feedbeef o	- read data from block 0 password feedbeef safety check");
	PrintAndLogEx(NORMAL, "");
	return 0;
}
int usage_t55xx_write(){
	PrintAndLogEx(NORMAL, "Usage:  lf t55xx write [b <block>] [d <data>] [p <password>] [1] [t]");
	PrintAndLogEx(NORMAL, "Options:");
	PrintAndLogEx(NORMAL, "     b <block>    - block number to write. Between 0-7");
	PrintAndLogEx(NORMAL, "     d <data>     - 4 bytes of data to write (8 hex characters)");
	PrintAndLogEx(NORMAL, "     p <password> - OPTIONAL password 4bytes (8 hex characters)");
	PrintAndLogEx(NORMAL, "     1            - OPTIONAL write Page 1 instead of Page 0");
	PrintAndLogEx(NORMAL, "     t            - OPTIONAL test mode write - ****DANGER****");
    PrintAndLogEx(NORMAL, "");
	PrintAndLogEx(NORMAL, "Examples:");
	PrintAndLogEx(NORMAL, "      lf t55xx write b 3 d 11223344            - write 11223344 to block 3");
	PrintAndLogEx(NORMAL, "      lf t55xx write b 3 d 11223344 p feedbeef - write 11223344 to block 3 password feedbeef");
	PrintAndLogEx(NORMAL, "");
	return 0;
}
int usage_t55xx_trace() {
	PrintAndLogEx(NORMAL, "Usage:  lf t55xx trace [1]");
	PrintAndLogEx(NORMAL, "Options:");
	PrintAndLogEx(NORMAL, "     1             - if set, use Graphbuffer otherwise read data from tag.");
	PrintAndLogEx(NORMAL, "");
	PrintAndLogEx(NORMAL, "Examples:");
	PrintAndLogEx(NORMAL, "      lf t55xx trace");
	PrintAndLogEx(NORMAL, "      lf t55xx trace 1");
	PrintAndLogEx(NORMAL, "");
	return 0;
}
int usage_t55xx_info() {
	PrintAndLogEx(NORMAL, "Usage:  lf t55xx info [1]");
	PrintAndLogEx(NORMAL, "Options:");
	PrintAndLogEx(NORMAL, "     1             - if set, use Graphbuffer otherwise read data from tag.");
	PrintAndLogEx(NORMAL, "");
	PrintAndLogEx(NORMAL, "Examples:");
	PrintAndLogEx(NORMAL, "      lf t55xx info");
	PrintAndLogEx(NORMAL, "      lf t55xx info 1");
	PrintAndLogEx(NORMAL, "");
	return 0;
}
int usage_t55xx_dump(){
	PrintAndLogEx(NORMAL, "Usage:  lf t55xx dump <password> [o]");
	PrintAndLogEx(NORMAL, "Options:");
	PrintAndLogEx(NORMAL, "     <password>  - OPTIONAL password 4bytes (8 hex symbols)");
	PrintAndLogEx(NORMAL, "     o           - OPTIONAL override, force pwd read despite danger to card");
	PrintAndLogEx(NORMAL, "");
	PrintAndLogEx(NORMAL, "Examples:");
	PrintAndLogEx(NORMAL, "      lf t55xx dump");
	PrintAndLogEx(NORMAL, "      lf t55xx dump feedbeef o");
	PrintAndLogEx(NORMAL, "");
	return 0;
}
int usage_t55xx_detect(){
	PrintAndLogEx(NORMAL, "Usage:  lf t55xx detect [1] [p <password>]");
	PrintAndLogEx(NORMAL, "Options:");
	PrintAndLogEx(NORMAL, "     1             - if set, use Graphbuffer otherwise read data from tag.");
	PrintAndLogEx(NORMAL, "     p <password>  - OPTIONAL password (8 hex characters)");
	PrintAndLogEx(NORMAL, "");
	PrintAndLogEx(NORMAL, "Examples:");
	PrintAndLogEx(NORMAL, "      lf t55xx detect");
	PrintAndLogEx(NORMAL, "      lf t55xx detect 1");
	PrintAndLogEx(NORMAL, "      lf t55xx detect p 11223344");
	PrintAndLogEx(NORMAL, "");
	return 0;
}
int usage_t55xx_detectP1(){
	PrintAndLogEx(NORMAL, "Command: Detect Page 1 of a t55xx chip");
	PrintAndLogEx(NORMAL, "Usage:  lf t55xx p1detect [1] [p <password>]");
	PrintAndLogEx(NORMAL, "Options:");
	PrintAndLogEx(NORMAL, "     1             - if set, use Graphbuffer otherwise read data from tag.");
	PrintAndLogEx(NORMAL, "     p <password>  - OPTIONAL password (8 hex characters)");
	PrintAndLogEx(NORMAL, "");
	PrintAndLogEx(NORMAL, "Examples:");
	PrintAndLogEx(NORMAL, "      lf t55xx p1detect");
	PrintAndLogEx(NORMAL, "      lf t55xx p1detect 1");
	PrintAndLogEx(NORMAL, "      lf t55xx p1detect p 11223344");
	PrintAndLogEx(NORMAL, "");
	return 0;
}
int usage_t55xx_wakup(){
	PrintAndLogEx(NORMAL, "Usage:  lf t55xx wakeup [h] p <password>");
	PrintAndLogEx(NORMAL, "This commands send the Answer-On-Request command and leaves the readerfield ON afterwards.");
	PrintAndLogEx(NORMAL, "Options:");
	PrintAndLogEx(NORMAL, "     h 			- this help");
    PrintAndLogEx(NORMAL, "     p <password>	- password 4bytes (8 hex symbols)");
    PrintAndLogEx(NORMAL, "");
	PrintAndLogEx(NORMAL, "Examples:");
    PrintAndLogEx(NORMAL, "      lf t55xx wakeup p 11223344  - send wakeup password");
	return 0;
}
int usage_t55xx_chk(){
	PrintAndLogEx(NORMAL, "This command uses a dictionary attack");
	PrintAndLogEx(NORMAL, "press 'enter' to cancel the command");
    PrintAndLogEx(NORMAL, "Usage: lf t55xx bruteforce [h] <m> [i <*.dic>]");
	PrintAndLogEx(NORMAL, "Options:");
	PrintAndLogEx(NORMAL, "     h			- this help");
	PrintAndLogEx(NORMAL, "     m			- use dictionary from flashmemory\n");
    PrintAndLogEx(NORMAL, "     i <*.dic>	- loads a default keys dictionary file <*.dic>");
    PrintAndLogEx(NORMAL, "");
    PrintAndLogEx(NORMAL, "Examples:");
    PrintAndLogEx(NORMAL, "       lf t55xx bruteforce m");
	PrintAndLogEx(NORMAL, "       lf t55xx bruteforce i default_pwd.dic");
    PrintAndLogEx(NORMAL, "");
    return 0;
}
int usage_t55xx_bruteforce(){
	PrintAndLogEx(NORMAL, "This command uses bruteforce to scan a number range");
	PrintAndLogEx(NORMAL, "press 'enter' to cancel the command");
    PrintAndLogEx(NORMAL, "Usage: lf t55xx bruteforce [h] <start password> <end password>");
    PrintAndLogEx(NORMAL, "       password must be 4 bytes (8 hex symbols)");
	PrintAndLogEx(NORMAL, "Options:");
	PrintAndLogEx(NORMAL, "     h			- this help");
	PrintAndLogEx(NORMAL, "     <start_pwd> - 4 byte hex value to start pwd search at");
	PrintAndLogEx(NORMAL, "     <end_pwd>   - 4 byte hex value to end pwd search at");
    PrintAndLogEx(NORMAL, "");
    PrintAndLogEx(NORMAL, "Examples:");
    PrintAndLogEx(NORMAL, "       lf t55xx bruteforce aaaaaaaa bbbbbbbb");
    PrintAndLogEx(NORMAL, "");
    return 0;
}
int usage_t55xx_recoverpw(){
	PrintAndLogEx(NORMAL, "This command uses a few tricks to try to recover mangled password");
	PrintAndLogEx(NORMAL, "press 'enter' to cancel the command");
	PrintAndLogEx(NORMAL, "WARNING: this may brick non-password protected chips!");
	PrintAndLogEx(NORMAL, "Usage: lf t55xx recoverpw [password]");
	PrintAndLogEx(NORMAL, "       password must be 4 bytes (8 hex symbols)");
	PrintAndLogEx(NORMAL, "       default password is 51243648, used by many cloners");
	PrintAndLogEx(NORMAL, "Options:");
	PrintAndLogEx(NORMAL, "     h           - this help");
	PrintAndLogEx(NORMAL, "     [password]  - 4 byte hex value of password written by cloner");
	PrintAndLogEx(NORMAL, "");
	PrintAndLogEx(NORMAL, "Examples:");
	PrintAndLogEx(NORMAL, "       lf t55xx recoverpw");
	PrintAndLogEx(NORMAL, "       lf t55xx recoverpw 51243648");
	PrintAndLogEx(NORMAL, "");
	return 0;
}int usage_t55xx_wipe(){
	PrintAndLogEx(NORMAL, "Usage:  lf t55xx wipe [h] [Q5]");
	PrintAndLogEx(NORMAL, "This commands wipes a tag, fills blocks 1-7 with zeros and a default configuration block");
	PrintAndLogEx(NORMAL, "Options:");
	PrintAndLogEx(NORMAL, "     h 	- this help");
	PrintAndLogEx(NORMAL, "     Q5  - indicates to use the T5555 (Q5) default configuration block");
    PrintAndLogEx(NORMAL, "");
	PrintAndLogEx(NORMAL, "Examples:");
    PrintAndLogEx(NORMAL, "      lf t55xx wipe	-  wipes a t55x7 tag,    config block 0x000880E0");
	PrintAndLogEx(NORMAL, "      lf t55xx wipe Q5 -  wipes a t5555 Q5 tag, config block 0x6001F004");
	return 0;
}
int usage_lf_deviceconfig(){
	PrintAndLogEx(NORMAL, "Sets t55x7 timings for direkt commands. The timings are set here in Field Clocks (FC), \nwhich is converted to (US) on device");
	PrintAndLogEx(NORMAL, "Usage: lf t55xx deviceconfig a <gap> b <gap> c <gap> d <gap> e <gap> p");
	PrintAndLogEx(NORMAL, "Options:");
	PrintAndLogEx(NORMAL, "       h              - This help");
	PrintAndLogEx(NORMAL, "       a <8..255>     - Set start gap");
	PrintAndLogEx(NORMAL, "       b <8..255>     - Set write gap");
	PrintAndLogEx(NORMAL, "       c <8..255>     - Set write ZERO gap");
	PrintAndLogEx(NORMAL, "       d <8..255>     - Set write ONE gap");
	PrintAndLogEx(NORMAL, "       e <8..255>     - Set read gap");
	PrintAndLogEx(NORMAL, "       p              - persist to flashmemory");
	PrintAndLogEx(NORMAL, "");
	PrintAndLogEx(NORMAL, "Examples:");
	PrintAndLogEx(NORMAL, "      lf t55xx deviceconfig a 29 b 17 c 15 d 47 e 15   - default T55XX");
	PrintAndLogEx(NORMAL, "      lf t55xx deviceconfig a 55 b 14 c 21 d 30        - default EM4305");
	PrintAndLogEx(NORMAL, "");
	return 0;
}

int CmdHelp(const char *Cmd);

void printT5xxHeader(uint8_t page){
	PrintAndLogEx(NORMAL, "Reading Page %d:", page);
	PrintAndLogEx(NORMAL, "blk | hex data | binary                           | ascii");
	PrintAndLogEx(NORMAL, "----+----------+----------------------------------+-------");
}

int CmdT55xxSetConfig(const char *Cmd) {

	uint8_t offset = 0;
	char modulation[6] = {0x00};
	char tmp = 0x00;
	uint8_t bitRate = 0;
	uint8_t rates[9] = {8,16,32,40,50,64,100,128,0};
	uint8_t cmdp = 0;
	bool errors = false;
	while(param_getchar(Cmd, cmdp) != 0x00 && !errors) {
		tmp = tolower(param_getchar(Cmd, cmdp));
		switch(tmp)	{
		case 'h':
			return usage_t55xx_config();
		case 'b':
			errors |= param_getdec(Cmd, cmdp+1, &bitRate);
			if ( !errors){
				uint8_t i = 0;
				for (; i < 9; i++){
					if (rates[i]==bitRate) {
						config.bitrate = i;
						break;
					}
				}
				if (i==9) errors = true;
			}
			cmdp+=2;
			break;
		case 'd':
			param_getstr(Cmd, cmdp+1, modulation, sizeof(modulation));
			cmdp += 2;

			if ( strcmp(modulation, "FSK" ) == 0) {
				config.modulation = DEMOD_FSK;
			} else if ( strcmp(modulation, "FSK1" ) == 0) {
				config.modulation = DEMOD_FSK1;
				config.inverted=1;
			} else if ( strcmp(modulation, "FSK1a" ) == 0) {
				config.modulation = DEMOD_FSK1a;
				config.inverted=0;
			} else if ( strcmp(modulation, "FSK2" ) == 0) {
				config.modulation = DEMOD_FSK2;
				config.inverted=0;
			} else if ( strcmp(modulation, "FSK2a" ) == 0) {
				config.modulation = DEMOD_FSK2a;
				config.inverted=1;
			} else if ( strcmp(modulation, "ASK" ) == 0) {
				config.modulation = DEMOD_ASK;
			} else if ( strcmp(modulation, "NRZ" ) == 0) {
				config.modulation = DEMOD_NRZ;
			} else if ( strcmp(modulation, "PSK1" ) == 0) {
				config.modulation = DEMOD_PSK1;
			} else if ( strcmp(modulation, "PSK2" ) == 0) {
				config.modulation = DEMOD_PSK2;
			} else if ( strcmp(modulation, "PSK3" ) == 0) {
				config.modulation = DEMOD_PSK3;
			} else if ( strcmp(modulation, "BIa" ) == 0) {
				config.modulation = DEMOD_BIa;
				config.inverted=1;
			} else if ( strcmp(modulation, "BI" ) == 0) {
				config.modulation = DEMOD_BI;
				config.inverted=0;
			} else {
				PrintAndLogEx(WARNING, "Unknown modulation '%s'", modulation);
				errors = true;
			}
			break;
		case 'i':
			config.inverted = param_getchar(Cmd,cmdp+1) == '1';
			cmdp+=2;
			break;
		case 'o':
			errors |= param_getdec(Cmd, cmdp+1, &offset);
			if ( !errors )
				config.offset = offset;
			cmdp+=2;
			break;
		case 'q':
			config.Q5 = true;
			cmdp++;
			break;
		case 's':
			config.ST = true;
			cmdp++;
			break;
		default:
			PrintAndLogEx(WARNING, "Unknown parameter '%c'", param_getchar(Cmd, cmdp));
			errors = true;
			break;
		}
	}

	// No args
	if (cmdp == 0) return printConfiguration( config );

	//Validations
	if (errors) return usage_t55xx_config();

 	config.block0 = 0;
 	return printConfiguration ( config );
}

int T55xxReadBlock(uint8_t block, bool page1, bool usepwd, bool override, uint32_t password){
	//Password mode
	if ( usepwd ) {
		// try reading the config block and verify that PWD bit is set before doing this!
		if ( !override ) {

			if ( !AquireData(T55x7_PAGE0, T55x7_CONFIGURATION_BLOCK, false, 0 ) ) return 0;

			if ( !tryDetectModulation() ) {
				PrintAndLogEx(NORMAL, "Safety Check: Could not detect if PWD bit is set in config block. Exits.");
				return 0;
			} else {
				PrintAndLogEx(NORMAL, "Safety Check: PWD bit is NOT set in config block. Reading without password...");
				usepwd = false;
				page1 = false;
			}
		} else {
			PrintAndLogEx(NORMAL, "Safety Check Overriden - proceeding despite risk");
		}
	}

	if (!AquireData(page1, block, usepwd, password) ) return 0;
	if (!DecodeT55xxBlock()) return 0;

	char blk[10] = {0};
	sprintf(blk, "%02d", block);
	printT55xxBlock(blk);
	return 1;
}

int CmdT55xxReadBlock(const char *Cmd) {
	uint8_t block = REGULAR_READ_MODE_BLOCK;
	uint32_t password = 0; //default to blank Block 7
	bool usepwd = false;
	bool override = false;
	bool page1 = false;
	bool errors = false;
	uint8_t cmdp = 0;
	while(param_getchar(Cmd, cmdp) != 0x00 && !errors) {
		switch ( tolower(param_getchar(Cmd, cmdp))) {
		case 'h':
			return usage_t55xx_read();
		case 'b':
			errors |= param_getdec(Cmd, cmdp+1, &block);
			cmdp += 2;
			break;
		case 'o':
			override = true;
			cmdp++;
			break;
		case 'p':
			password = param_get32ex(Cmd, cmdp+1, 0, 16);
			usepwd = true;
			cmdp += 2;
			break;
		case '1':
			page1 = true;
			cmdp++;
			break;
		default:
			PrintAndLogEx(WARNING, "Unknown parameter '%c'", param_getchar(Cmd, cmdp));
			errors = true;
			break;
		}
	}
	if (errors) return usage_t55xx_read();

	if (block > 7 && block != REGULAR_READ_MODE_BLOCK	) {
		PrintAndLogEx(NORMAL, "Block must be between 0 and 7");
		return 0;
	}

	printT5xxHeader(page1);
	return T55xxReadBlock(block, page1, usepwd, override, password);
}

bool DecodeT55xxBlock(){

	char buf[30] = {0x00};
	char *cmdStr = buf;
	int ans = 0;
	bool ST = config.ST;
	uint8_t bitRate[8] = {8,16,32,40,50,64,100,128};
	DemodBufferLen = 0x00;

	switch( config.modulation ){
		case DEMOD_FSK:
			snprintf(cmdStr, sizeof(buf),"%d %d", bitRate[config.bitrate], config.inverted );
			ans = FSKrawDemod(cmdStr, false);
			break;
		case DEMOD_FSK1:
		case DEMOD_FSK1a:
			snprintf(cmdStr, sizeof(buf),"%d %d 8 5", bitRate[config.bitrate], config.inverted );
			ans = FSKrawDemod(cmdStr, false);
			break;
		case DEMOD_FSK2:
		case DEMOD_FSK2a:
			snprintf(cmdStr, sizeof(buf),"%d %d 10 8", bitRate[config.bitrate], config.inverted );
			ans = FSKrawDemod(cmdStr, false);
			break;
		case DEMOD_ASK:
			snprintf(cmdStr, sizeof(buf),"%d %d 1", bitRate[config.bitrate], config.inverted );
			ans = ASKDemod_ext(cmdStr, false, false, 1, &ST);
			break;
		case DEMOD_PSK1:
			// skip first 160 samples to allow antenna to settle in (psk gets inverted occasionally otherwise)
			save_restoreGB(GRAPH_SAVE);
			CmdLtrim("160");
			snprintf(cmdStr, sizeof(buf),"%d %d 6", bitRate[config.bitrate], config.inverted );
			ans = PSKDemod(cmdStr, false);
			//undo trim samples
			save_restoreGB(GRAPH_RESTORE);
			break;
		case DEMOD_PSK2: //inverted won't affect this
		case DEMOD_PSK3: //not fully implemented
			// skip first 160 samples to allow antenna to settle in (psk gets inverted occasionally otherwise)
			save_restoreGB(GRAPH_SAVE);
			CmdLtrim("160");
			snprintf(cmdStr, sizeof(buf),"%d 0 6", bitRate[config.bitrate] );
			ans = PSKDemod(cmdStr, false);
			psk1TOpsk2(DemodBuffer, DemodBufferLen);
			//undo trim samples
			save_restoreGB(GRAPH_RESTORE);
			break;
		case DEMOD_NRZ:
			snprintf(cmdStr, sizeof(buf),"%d %d 1", bitRate[config.bitrate], config.inverted );
			ans = NRZrawDemod(cmdStr, false);
			break;
		case DEMOD_BI:
		case DEMOD_BIa:
			snprintf(cmdStr, sizeof(buf),"0 %d %d 1", bitRate[config.bitrate], config.inverted );
			ans = ASKbiphaseDemod(cmdStr, false);
			break;
		default:
			return false;
	}
	return (bool) ans;
}

bool DecodeT5555TraceBlock() {
	DemodBufferLen = 0x00;

	// According to datasheet. Always: RF/64, not inverted, Manchester
	return (bool) ASKDemod("64 0 1", false, false, 1);
}

// sanity check. Don't use proxmark if it is offline and you didn't specify useGraphbuf
static int SanityOfflineCheck( bool useGraphBuffer ){
	if ( !useGraphBuffer && IsOffline() ) {
		PrintAndLogEx(NORMAL, "Your proxmark3 device is offline. Specify [1] to use graphbuffer data instead");
		return 0;
	}
	return 1;
}

int CmdT55xxDetect(const char *Cmd){
	bool errors = false;
	bool useGB = false, usepwd = false;
	uint32_t password = 0;
	uint8_t cmdp = 0;

	while (param_getchar(Cmd, cmdp) != 0x00 && !errors) {
		switch ( tolower(param_getchar(Cmd, cmdp))) {
		case 'h':
			return usage_t55xx_detect();
		case 'p':
			password = param_get32ex(Cmd, cmdp+1, 0, 16);
			usepwd = true;
			cmdp += 2;
			break;
		case '1':
			// use Graphbuffer data
			useGB = true;
			cmdp++;
			break;
		default:
			PrintAndLogEx(WARNING, "Unknown parameter '%c'", param_getchar(Cmd, cmdp));
			errors = true;
			break;
		}
	}
	if (errors) return usage_t55xx_detect();

	// sanity check.
	if (!SanityOfflineCheck(useGB)) return 1;

	if ( !useGB) {
		if ( !AquireData(T55x7_PAGE0, T55x7_CONFIGURATION_BLOCK, usepwd, password) )
			return 1;
	}

	if ( !tryDetectModulation() )
		PrintAndLogEx(WARNING, "Could not detect modulation automatically. Try setting it manually with \'lf t55xx config\'");

	return 0;
}

// detect configuration?
bool tryDetectModulation(){

	t55xx_conf_block_t tests[15];
	int bitRate = 0, clk = 0, firstClockEdge = 0;
	uint8_t hits = 0, fc1 = 0, fc2 = 0, ans = 0;

	ans = fskClocks(&fc1, &fc2, (uint8_t *)&clk, &firstClockEdge);

	if (ans && ((fc1==10 && fc2==8) || (fc1==8 && fc2==5))) {
		if ( FSKrawDemod("0 0", false) && test(DEMOD_FSK, &tests[hits].offset, &bitRate, clk, &tests[hits].Q5)){
			tests[hits].modulation = DEMOD_FSK;
			if (fc1==8 && fc2 == 5)
				tests[hits].modulation = DEMOD_FSK1a;
			else if (fc1==10 && fc2 == 8)
				tests[hits].modulation = DEMOD_FSK2;
			tests[hits].bitrate = bitRate;
			tests[hits].inverted = false;
			tests[hits].block0 = PackBits(tests[hits].offset, 32, DemodBuffer);
			tests[hits].ST = false;
			++hits;
		}
		if ( FSKrawDemod("0 1", false) && test(DEMOD_FSK, &tests[hits].offset, &bitRate, clk, &tests[hits].Q5)) {
			tests[hits].modulation = DEMOD_FSK;
			if (fc1 == 8 && fc2 == 5)
				tests[hits].modulation = DEMOD_FSK1;
			else if (fc1 == 10 && fc2 == 8)
				tests[hits].modulation = DEMOD_FSK2a;
			tests[hits].bitrate = bitRate;
			tests[hits].inverted = true;
			tests[hits].block0 = PackBits(tests[hits].offset, 32, DemodBuffer);
			tests[hits].ST = false;
			++hits;
		}
	} else {
		clk = GetAskClock("", false);
		if (clk > 0) {
			tests[hits].ST = true;
			// "0 0 1 " == clock auto, invert false, maxError 1.
			// false = no verbose
			// false = no emSearch
			// 1 = Ask/Man
			// st = true
			if ( ASKDemod_ext("0 0 1", false, false, 1, &tests[hits].ST) && test(DEMOD_ASK, &tests[hits].offset, &bitRate, clk, &tests[hits].Q5)) {
				tests[hits].modulation = DEMOD_ASK;
				tests[hits].bitrate = bitRate;
				tests[hits].inverted = false;
				tests[hits].block0 = PackBits(tests[hits].offset, 32, DemodBuffer);
				++hits;
			}
			tests[hits].ST = true;
			// "0 0 1 " == clock auto, invert true, maxError 1.
			// false = no verbose
			// false = no emSearch
			// 1 = Ask/Man
			// st = true
			if ( ASKDemod_ext("0 1 1", false, false, 1, &tests[hits].ST)  && test(DEMOD_ASK, &tests[hits].offset, &bitRate, clk, &tests[hits].Q5)) {
				tests[hits].modulation = DEMOD_ASK;
				tests[hits].bitrate = bitRate;
				tests[hits].inverted = true;
				tests[hits].block0 = PackBits(tests[hits].offset, 32, DemodBuffer);
				++hits;
			}
			if ( ASKbiphaseDemod("0 0 0 2", false) && test(DEMOD_BI, &tests[hits].offset, &bitRate, clk, &tests[hits].Q5) ) {
				tests[hits].modulation = DEMOD_BI;
				tests[hits].bitrate = bitRate;
				tests[hits].inverted = false;
				tests[hits].block0 = PackBits(tests[hits].offset, 32, DemodBuffer);
				tests[hits].ST = false;
				++hits;
			}
			if ( ASKbiphaseDemod("0 0 1 2", false) && test(DEMOD_BIa, &tests[hits].offset, &bitRate, clk, &tests[hits].Q5) ) {
				tests[hits].modulation = DEMOD_BIa;
				tests[hits].bitrate = bitRate;
				tests[hits].inverted = true;
				tests[hits].block0 = PackBits(tests[hits].offset, 32, DemodBuffer);
				tests[hits].ST = false;
				++hits;
			}
		}
		clk = GetNrzClock("", false);
		if (clk > 8) { //clock of rf/8 is likely a false positive, so don't use it.
			if ( NRZrawDemod("0 0 1", false)  && test(DEMOD_NRZ, &tests[hits].offset, &bitRate, clk, &tests[hits].Q5)) {
				tests[hits].modulation = DEMOD_NRZ;
				tests[hits].bitrate = bitRate;
				tests[hits].inverted = false;
				tests[hits].block0 = PackBits(tests[hits].offset, 32, DemodBuffer);
				tests[hits].ST = false;
				++hits;
			}

			if ( NRZrawDemod("0 1 1", false)  && test(DEMOD_NRZ, &tests[hits].offset, &bitRate, clk, &tests[hits].Q5)) {
				tests[hits].modulation = DEMOD_NRZ;
				tests[hits].bitrate = bitRate;
				tests[hits].inverted = true;
				tests[hits].block0 = PackBits(tests[hits].offset, 32, DemodBuffer);
				tests[hits].ST = false;
				++hits;
			}
		}

		clk = GetPskClock("", false);
		if (clk > 0) {
			// allow undo
			save_restoreGB(GRAPH_SAVE);
			// skip first 160 samples to allow antenna to settle in (psk gets inverted occasionally otherwise)
			CmdLtrim("160");
			if ( PSKDemod("0 0 6", false) && test(DEMOD_PSK1, &tests[hits].offset, &bitRate, clk, &tests[hits].Q5)) {
				tests[hits].modulation = DEMOD_PSK1;
				tests[hits].bitrate = bitRate;
				tests[hits].inverted = false;
				tests[hits].block0 = PackBits(tests[hits].offset, 32, DemodBuffer);
				tests[hits].ST = false;
				++hits;
			}
			if ( PSKDemod("0 1 6", false) && test(DEMOD_PSK1, &tests[hits].offset, &bitRate, clk, &tests[hits].Q5)) {
				tests[hits].modulation = DEMOD_PSK1;
				tests[hits].bitrate = bitRate;
				tests[hits].inverted = true;
				tests[hits].block0 = PackBits(tests[hits].offset, 32, DemodBuffer);
				tests[hits].ST = false;
				++hits;
			}
			//ICEMAN: are these PSKDemod calls needed?
			// PSK2 - needs a call to psk1TOpsk2.
			if ( PSKDemod("0 0 6", false)) {
				psk1TOpsk2(DemodBuffer, DemodBufferLen);
				if (test(DEMOD_PSK2, &tests[hits].offset, &bitRate, clk, &tests[hits].Q5)){
					tests[hits].modulation = DEMOD_PSK2;
					tests[hits].bitrate = bitRate;
					tests[hits].inverted = false;
					tests[hits].block0 = PackBits(tests[hits].offset, 32, DemodBuffer);
					tests[hits].ST = false;
					++hits;
				}
			} // inverse waves does not affect this demod
			// PSK3 - needs a call to psk1TOpsk2.
			if ( PSKDemod("0 0 6", false)) {
				psk1TOpsk2(DemodBuffer, DemodBufferLen);
				if (test(DEMOD_PSK3, &tests[hits].offset, &bitRate, clk, &tests[hits].Q5)){
					tests[hits].modulation = DEMOD_PSK3;
					tests[hits].bitrate = bitRate;
					tests[hits].inverted = false;
					tests[hits].block0 = PackBits(tests[hits].offset, 32, DemodBuffer);
					tests[hits].ST = false;
					++hits;
				}
			} // inverse waves does not affect this demod
		//undo trim samples
			save_restoreGB(GRAPH_RESTORE);
		}
	}
	if ( hits == 1) {
		config.modulation = tests[0].modulation;
		config.bitrate = tests[0].bitrate;
		config.inverted = tests[0].inverted;
		config.offset = tests[0].offset;
		config.block0 = tests[0].block0;
		config.Q5 = tests[0].Q5;
		config.ST = tests[0].ST;
		printConfiguration( config );
		return true;
	}

	bool retval = false;
	if ( hits > 1) {
		PrintAndLogEx(SUCCESS, "Found [%d] possible matches for modulation.", hits);
		for(int i=0; i<hits; ++i){
			retval = testKnownConfigBlock(tests[i].block0);
			if ( retval ) {
				PrintAndLogEx(NORMAL, "--[%d]--------------- << selected this", i+1);
				config.modulation = tests[i].modulation;
				config.bitrate = tests[i].bitrate;
				config.inverted = tests[i].inverted;
				config.offset = tests[i].offset;
				config.block0 = tests[i].block0;
				config.Q5 = tests[i].Q5;
				config.ST = tests[i].ST;
			} else {
				PrintAndLogEx(NORMAL, "--[%d]---------------", i+1);
			}
			printConfiguration( tests[i] );
		}
	}
	return retval;
}

bool testKnownConfigBlock(uint32_t block0) {
	switch(block0){
		case T55X7_DEFAULT_CONFIG_BLOCK:
		case T55X7_RAW_CONFIG_BLOCK:
		case T55X7_EM_UNIQUE_CONFIG_BLOCK:
		case T55X7_FDXB_CONFIG_BLOCK:
		case T55X7_HID_26_CONFIG_BLOCK:
		case T55X7_PYRAMID_CONFIG_BLOCK:
		case T55X7_INDALA_64_CONFIG_BLOCK:
		case T55X7_INDALA_224_CONFIG_BLOCK:
		case T55X7_GUARDPROXII_CONFIG_BLOCK:
		case T55X7_VIKING_CONFIG_BLOCK:
		case T55X7_NORALYS_CONFIG_BLOCK:
		case T55X7_IOPROX_CONFIG_BLOCK:
		case T55X7_PRESCO_CONFIG_BLOCK:
			return true;
	}
	return false;
}

bool testModulation(uint8_t mode, uint8_t modread){
	switch( mode ){
		case DEMOD_FSK:
			if (modread >= DEMOD_FSK1 && modread <= DEMOD_FSK2a) return true;
			break;
		case DEMOD_ASK:
			if (modread == DEMOD_ASK) return true;
			break;
		case DEMOD_PSK1:
			if (modread == DEMOD_PSK1) return true;
			break;
		case DEMOD_PSK2:
			if (modread == DEMOD_PSK2) return true;
			break;
		case DEMOD_PSK3:
			if (modread == DEMOD_PSK3) return true;
			break;
		case DEMOD_NRZ:
			if (modread == DEMOD_NRZ) return true;
			break;
		case DEMOD_BI:
			if (modread == DEMOD_BI) return true;
			break;
		case DEMOD_BIa:
			if (modread == DEMOD_BIa) return true;
			break;
		default:
			return false;
	}
	return false;
}

bool testQ5Modulation(uint8_t	mode, uint8_t	modread){
	switch( mode ){
		case DEMOD_FSK:
			if (modread >= 4 && modread <= 5) return true;
			break;
		case DEMOD_ASK:
			if (modread == 0) return true;
			break;
		case DEMOD_PSK1:
			if (modread == 1) return true;
			break;
		case DEMOD_PSK2:
			if (modread == 2) return true;
			break;
		case DEMOD_PSK3:
			if (modread == 3) return true;
			break;
		case DEMOD_NRZ:
			if (modread == 7) return true;
			break;
		case DEMOD_BI:
			if (modread == 6) return true;
			break;
		default:
			return false;
	}
	return false;
}

int convertQ5bitRate(uint8_t bitRateRead) {
	uint8_t expected[] = {8, 16, 32, 40, 50, 64, 100, 128};
	for (int i=0; i<8; i++)
		if (expected[i] == bitRateRead)
			return i;

	return -1;
}

bool testQ5(uint8_t mode, uint8_t *offset, int *fndBitRate, uint8_t	clk){

	if ( DemodBufferLen < 64 ) return false;
	uint8_t si = 0;
	for (uint8_t idx = 28; idx < 64; idx++){
		si = idx;
		if ( PackBits(si, 28, DemodBuffer) == 0x00 ) continue;

		uint8_t safer     = PackBits(si, 4, DemodBuffer); si += 4;     //master key
		uint8_t resv      = PackBits(si, 8, DemodBuffer); si += 8;
		// 2nibble must be zeroed.
		if (safer != 0x6 && safer != 0x9) continue;
		if ( resv > 0x00) continue;
		//uint8_t	pageSel   = PackBits(si, 1, DemodBuffer); si += 1;
		//uint8_t fastWrite = PackBits(si, 1, DemodBuffer); si += 1;
		si += 1+1;
		int bitRate       = PackBits(si, 6, DemodBuffer)*2 + 2; si += 6;     //bit rate
		if (bitRate > 128 || bitRate < 8) continue;

		//uint8_t AOR       = PackBits(si, 1, DemodBuffer); si += 1;
		//uint8_t PWD       = PackBits(si, 1, DemodBuffer); si += 1;
		//uint8_t pskcr     = PackBits(si, 2, DemodBuffer); si += 2;  //could check psk cr
		//uint8_t inverse   = PackBits(si, 1, DemodBuffer); si += 1;
		si += 1+1+2+1;
		uint8_t modread   = PackBits(si, 3, DemodBuffer); si += 3;
		uint8_t maxBlk    = PackBits(si, 3, DemodBuffer); si += 3;
		//uint8_t ST        = PackBits(si, 1, DemodBuffer); si += 1;
		if (maxBlk == 0) continue;
		//test modulation
		if (!testQ5Modulation(mode, modread)) continue;
		if (bitRate != clk) continue;
		*fndBitRate = convertQ5bitRate(bitRate);
		if (*fndBitRate < 0) continue;
		*offset = idx;

		return true;
	}
	return false;
}

bool testBitRate(uint8_t readRate, uint8_t clk){
	uint8_t expected[] = {8, 16, 32, 40, 50, 64, 100, 128};
	if (expected[readRate] == clk)
		return true;

	return false;
}

bool test(uint8_t mode, uint8_t *offset, int *fndBitRate, uint8_t clk, bool *Q5){

	if ( DemodBufferLen < 64 ) return false;
	uint8_t si = 0;
	for (uint8_t idx = 28; idx < 64; idx++){
		si = idx;
		if ( PackBits(si, 28, DemodBuffer) == 0x00 ) continue;

		uint8_t safer    = PackBits(si, 4, DemodBuffer); si += 4;     //master key
		uint8_t resv     = PackBits(si, 4, DemodBuffer); si += 4;     //was 7 & +=7+3 //should be only 4 bits if extended mode
		// 2nibble must be zeroed.
		// moved test to here, since this gets most faults first.
		if ( resv > 0x00) continue;

		int bitRate      = PackBits(si, 6, DemodBuffer); si += 6;     //bit rate (includes extended mode part of rate)
		uint8_t extend   = PackBits(si, 1, DemodBuffer); si += 1;     //bit 15 extended mode
		uint8_t modread  = PackBits(si, 5, DemodBuffer); si += 5+2+1;
		//uint8_t pskcr   = PackBits(si, 2, DemodBuffer); si += 2+1;  //could check psk cr
		//uint8_t nml01    = PackBits(si, 1, DemodBuffer); si += 1+5;   //bit 24, 30, 31 could be tested for 0 if not extended mode
		//uint8_t nml02    = PackBits(si, 2, DemodBuffer); si += 2;

		//if extended mode
		bool extMode =( (safer == 0x6 || safer == 0x9) && extend) ? true : false;

		if (!extMode){
			if (bitRate > 7) continue;
			if (!testBitRate(bitRate, clk)) continue;
		} else { //extended mode bitrate = same function to calc bitrate as em4x05
			if (EM4x05_GET_BITRATE(bitRate) != clk) continue;

		}
		//test modulation
		if (!testModulation(mode, modread)) continue;
		*fndBitRate = bitRate;
		*offset = idx;
		*Q5 = false;
		return true;
	}
	if (testQ5(mode, offset, fndBitRate, clk)) {
		*Q5 = true;
		return true;
	}
	return false;
}

void printT55xxBlock(const char *blockNum){

	uint8_t i = config.offset;
	uint8_t endpos = 32 + i;
	uint32_t blockData = 0;
	uint8_t bits[64] = {0x00};

	if ( !DemodBufferLen) return;

	if ( endpos > DemodBufferLen){
		PrintAndLogEx(NORMAL, "The configured offset %d is too big. Possible offset: %d)", i, DemodBufferLen-32);
		return;
	}

	for (; i < endpos; ++i)
		bits[i - config.offset] = DemodBuffer[i];

	blockData = PackBits(0, 32, bits);
	uint8_t bytes[4] = {0};
	num_to_bytes(blockData, 4, bytes);

	PrintAndLogEx(NORMAL, " %s | %08X | %s | %s", blockNum, blockData, sprint_bin(bits,32), sprint_ascii(bytes,4));
}

int special(const char *Cmd) {
	uint32_t blockData = 0;
	uint8_t bits[32] = {0x00};

	PrintAndLogEx(NORMAL, "OFFSET | DATA  | BINARY                              | ASCII");
	PrintAndLogEx(NORMAL, "-------+-------+-------------------------------------+------");
	int i,j = 0;
	for (; j < 64; ++j){

		for (i = 0; i < 32; ++i)
			bits[i]=DemodBuffer[j+i];

		blockData = PackBits(0, 32, bits);

		PrintAndLogEx(NORMAL, "%02d | 0x%08X | %s",j , blockData, sprint_bin(bits,32));
	}
	return 0;
}

int printConfiguration( t55xx_conf_block_t b){
	PrintAndLogEx(NORMAL, "Chip Type  : %s", (b.Q5) ? "T5555(Q5)" : "T55x7");
	PrintAndLogEx(NORMAL, "Modulation : %s", GetSelectedModulationStr(b.modulation) );
	PrintAndLogEx(NORMAL, "Bit Rate   : %s", GetBitRateStr(b.bitrate, (b.block0 & T55x7_X_MODE && (b.block0>>28==6 || b.block0>>28==9))) );
	PrintAndLogEx(NORMAL, "Inverted   : %s", (b.inverted) ? _GREEN_(Yes) : "No" );
	PrintAndLogEx(NORMAL, "Offset     : %d", b.offset);
	PrintAndLogEx(NORMAL, "Seq. Term. : %s", (b.ST) ? _GREEN_(Yes) : "No" );
	PrintAndLogEx(NORMAL, "Block0     : 0x%08X", b.block0);
	PrintAndLogEx(NORMAL, "");
	return 0;
}

int CmdT55xxWakeUp(const char *Cmd) {
	uint32_t password = 0;
	uint8_t cmdp = 0;
	bool errors = false;
	while (param_getchar(Cmd, cmdp) != 0x00 && !errors) {
		switch (tolower(param_getchar(Cmd, cmdp))) {
		case 'h':
			return usage_t55xx_wakup();
		case 'p':
			password = param_get32ex(Cmd, cmdp+1, 0, 16);
			cmdp += 2;
			errors = false;
			break;
		default:
			PrintAndLogEx(WARNING, "Unknown parameter '%c'", param_getchar(Cmd, cmdp));
			errors = true;
			break;
		}
	}
	if (errors) return usage_t55xx_wakup();

	UsbCommand c = {CMD_T55XX_WAKEUP, {password, 0, 0}};
	clearCommandBuffer();
	SendCommand(&c);
	PrintAndLogEx(SUCCESS, "Wake up command sent. Try read now");
	return 0;
}

int CmdT55xxWriteBlock(const char *Cmd) {
	uint8_t block = 0xFF; //default to invalid block
	uint32_t data = 0; //default to blank Block
	uint32_t password = 0; //default to blank Block 7
	bool usepwd = false;
	bool page1 = false;
	bool gotdata = false;
	bool testMode = false;
	bool errors = false;
	uint8_t cmdp = 0;
	while (param_getchar(Cmd, cmdp) != 0x00 && !errors) {
		switch (tolower(param_getchar(Cmd, cmdp))) {
		case 'h':
			return usage_t55xx_write();
		case 'b':
			errors |= param_getdec(Cmd, cmdp+1, &block);
			cmdp += 2;
			break;
		case 'd':
			data = param_get32ex(Cmd, cmdp+1, 0, 16);
			gotdata	= true;
			cmdp += 2;
			break;
		case 'p':
			password = param_get32ex(Cmd, cmdp+1, 0, 16);
			usepwd = true;
			cmdp += 2;
			break;
		case 't':
			testMode = true;
			cmdp++;
			break;
		case '1':
			page1 = true;
			cmdp++;
			break;
		default:
			PrintAndLogEx(WARNING, "Unknown parameter '%c'", param_getchar(Cmd, cmdp));
			errors = true;
			break;
		}
	}
	if (errors || !gotdata) return usage_t55xx_write();

	if (block > 7) {
		PrintAndLogEx(WARNING, "Block number must be between 0 and 7");
		return 0;
	}

	UsbCommand c = {CMD_T55XX_WRITE_BLOCK, {data, block, 0}};
	UsbCommand resp;
 	c.d.asBytes[0] = (page1) ? 0x2 : 0;
 	c.d.asBytes[0] |= (testMode) ? 0x4 : 0;

	char pwdStr[16] = {0};
	snprintf(pwdStr, sizeof(pwdStr), "pwd: 0x%08X", password);

	PrintAndLogEx(INFO, "Writing page %d  block: %02d  data: 0x%08X %s", page1, block, data,  (usepwd) ? pwdStr : "" );

	//Password mode
	if (usepwd) {
		c.arg[2] = password;
		c.d.asBytes[0] |= 0x1;
	}
	clearCommandBuffer();
	SendCommand(&c);
	if ( !WaitForResponseTimeout(CMD_ACK, &resp, 1500 )){
		PrintAndLogEx(WARNING, "Error occurred, device did not ACK write operation. (May be due to old firmware)");
		return 0;
	}
	return 1;
}

int CmdT55xxReadTrace(const char *Cmd) {
	char cmdp = tolower(param_getchar(Cmd, 0));
	if (strlen(Cmd) > 1 || cmdp == 'h') return usage_t55xx_trace();

	bool pwdmode = false;
	uint32_t password = 0;

	if (strlen(Cmd) == 0) {
		// sanity check.
		if (!SanityOfflineCheck(false)) return 1;

		if ( !AquireData( T55x7_PAGE1, REGULAR_READ_MODE_BLOCK, pwdmode, password ) )
			return 1;
	}

	if ( config.Q5 ){
		if (!DecodeT5555TraceBlock()) return 1;
	} else {
		if (!DecodeT55xxBlock()) return 1;
	}

	if ( !DemodBufferLen ) return 1;

	RepaintGraphWindow();
	uint8_t repeat = (config.offset > 5) ? 32 : 0;

	uint8_t si = config.offset + repeat;
	uint32_t bl1 = PackBits(si, 32, DemodBuffer);
	uint32_t bl2 = PackBits(si+32, 32, DemodBuffer);

	if (config.Q5) {
		uint32_t hdr = PackBits(si, 9,  DemodBuffer); si += 9;

		if (hdr != 0x1FF) {
		  PrintAndLogEx(FAILED, "Invalid Q5 Trace data header (expected 0x1FF, found %X)", hdr);
		  return 1;
		}

		t5555_tracedata_t data = {.bl1 = bl1, .bl2 = bl2, .icr = 0, .lotidc = '?', .lotid = 0, .wafer = 0, .dw =0};

		data.icr     = PackBits(si, 2,  DemodBuffer); si += 2;
		data.lotidc  = 'Z' - PackBits(si, 2,  DemodBuffer); si += 3;

		data.lotid   = PackBits(si, 4,  DemodBuffer); si += 5;
		data.lotid <<= 4;
		data.lotid  |= PackBits(si, 4,  DemodBuffer); si += 5;
		data.lotid <<= 4;
		data.lotid  |= PackBits(si, 4,  DemodBuffer); si += 5;
		data.lotid <<= 4;
		data.lotid  |= PackBits(si, 4,  DemodBuffer); si += 5;
		data.lotid <<= 1;
		data.lotid  |= PackBits(si, 1,  DemodBuffer); si += 1;

		data.wafer   = PackBits(si, 3,  DemodBuffer); si += 4;
		data.wafer <<= 2;
		data.wafer  |= PackBits(si, 2,  DemodBuffer); si += 2;

		data.dw      = PackBits(si, 2,  DemodBuffer); si += 3;
		data.dw    <<= 4;
		data.dw     |= PackBits(si, 4,  DemodBuffer); si += 5;
		data.dw    <<= 4;
		data.dw     |= PackBits(si, 4,  DemodBuffer); si += 5;
		data.dw    <<= 4;
		data.dw     |= PackBits(si, 4,  DemodBuffer); si += 5;

		printT5555Trace(data, repeat);

	} else {

		t55x7_tracedata_t data = {.bl1 = bl1, .bl2 = bl2, .acl = 0, .mfc = 0, .cid = 0, .year = 0, .quarter = 0, .icr = 0,  .lotid = 0, .wafer = 0, .dw = 0};

		data.acl = PackBits(si, 8,  DemodBuffer); si += 8;
		if ( data.acl != 0xE0 ) {
			PrintAndLogEx(FAILED, "The modulation is most likely wrong since the ACL is not 0xE0. ");
			return 1;
		}

		data.mfc     = PackBits(si, 8,  DemodBuffer); si += 8;
		data.cid     = PackBits(si, 5,  DemodBuffer); si += 5;
		data.icr     = PackBits(si, 3,  DemodBuffer); si += 3;
		data.year    = PackBits(si, 4,  DemodBuffer); si += 4;
		data.quarter = PackBits(si, 2,  DemodBuffer); si += 2;
		data.lotid   = PackBits(si, 14, DemodBuffer); si += 14;
		data.wafer   = PackBits(si, 5,  DemodBuffer); si += 5;
		data.dw      = PackBits(si, 15, DemodBuffer);

		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		if ( data.year > tm.tm_year-110)
			data.year += 2000;
		else
			data.year += 2010;

		printT55x7Trace(data, repeat);
	}
	return 0;
}

void printT55x7Trace( t55x7_tracedata_t data, uint8_t repeat ){
	PrintAndLogEx(NORMAL, "-- T55x7 Trace Information ----------------------------------");
	PrintAndLogEx(NORMAL, "-------------------------------------------------------------");
	PrintAndLogEx(NORMAL, " ACL Allocation class (ISO/IEC 15963-1)  : 0x%02X (%d)", data.acl, data.acl);
	PrintAndLogEx(NORMAL, " MFC Manufacturer ID (ISO/IEC 7816-6)    : 0x%02X (%d) - %s", data.mfc, data.mfc, getTagInfo(data.mfc));
	PrintAndLogEx(NORMAL, " CID                                     : 0x%02X (%d) - %s", data.cid, data.cid, GetModelStrFromCID(data.cid));
	PrintAndLogEx(NORMAL, " ICR IC Revision                         : %d", data.icr );
	PrintAndLogEx(NORMAL, " Manufactured");
	PrintAndLogEx(NORMAL, "     Year/Quarter : %d/%d", data.year, data.quarter);
	PrintAndLogEx(NORMAL, "     Lot ID       : %d", data.lotid );
	PrintAndLogEx(NORMAL, "     Wafer number : %d", data.wafer);
	PrintAndLogEx(NORMAL, "     Die Number   : %d", data.dw);
	PrintAndLogEx(NORMAL, "-------------------------------------------------------------");
	PrintAndLogEx(NORMAL, " Raw Data - Page 1");
	PrintAndLogEx(NORMAL, "     Block 1  : 0x%08X  %s", data.bl1, sprint_bin(DemodBuffer+config.offset+repeat,32) );
	PrintAndLogEx(NORMAL, "     Block 2  : 0x%08X  %s", data.bl2, sprint_bin(DemodBuffer+config.offset+repeat+32,32) );
	PrintAndLogEx(NORMAL, "-------------------------------------------------------------");

	/*
	TRACE - BLOCK O
		Bits	Definition								HEX
		1-8		ACL Allocation class (ISO/IEC 15963-1)	0xE0
		9-16	MFC Manufacturer ID (ISO/IEC 7816-6)	0x15 Atmel Corporation
		17-21	CID										0x1 = Atmel ATA5577M1  0x2 = Atmel ATA5577M2
		22-24	ICR IC revision
		25-28	YEAR (BCD encoded) 						9 (= 2009)
		29-30	QUARTER									1,2,3,4
		31-32	LOT ID

	TRACE - BLOCK 1
		1-12	LOT ID
		13-17	Wafer number
		18-32	DW,  die number sequential
	*/
}

void printT5555Trace( t5555_tracedata_t data, uint8_t repeat ){
	PrintAndLogEx(NORMAL, "-- T5555 (Q5) Trace Information -----------------------------");
	PrintAndLogEx(NORMAL, "-------------------------------------------------------------");
	PrintAndLogEx(NORMAL, " ICR IC Revision  : %d", data.icr );
	PrintAndLogEx(NORMAL, "     Lot          : %c%d", data.lotidc, data.lotid);
	PrintAndLogEx(NORMAL, "     Wafer number : %d", data.wafer);
	PrintAndLogEx(NORMAL, "     Die Number   : %d", data.dw);
	PrintAndLogEx(NORMAL, "-------------------------------------------------------------");
	PrintAndLogEx(NORMAL, " Raw Data - Page 1");
	PrintAndLogEx(NORMAL, "     Block 1  : 0x%08X  %s", data.bl1, sprint_bin(DemodBuffer+config.offset+repeat,32) );
	PrintAndLogEx(NORMAL, "     Block 2  : 0x%08X  %s", data.bl2, sprint_bin(DemodBuffer+config.offset+repeat+32,32) );

	/*
		** Q5 **
		TRACE - BLOCK O and BLOCK1
		Bits	Definition				HEX
		1-9		Header                  0x1FF
		10-11 IC Revision
		12-13 Lot ID char
		15-35 Lot ID (NB parity)
		36-41 Wafer number (NB parity)
		42-58 DW, die number sequential (NB parity)
		60-63 Parity bits
		64    Always zero
	*/
}

//need to add Q5 info...
int CmdT55xxInfo(const char *Cmd){
	/*
		Page 0 Block 0 Configuration data.
		Normal mode
		Extended mode
	*/
	bool pwdmode = false;
	uint32_t password = 0;
	char cmdp = tolower(param_getchar(Cmd, 0));

	if (strlen(Cmd) > 1 || cmdp == 'h') return usage_t55xx_info();

	if (strlen(Cmd) == 0) {
		// sanity check.
		if (!SanityOfflineCheck(false)) return 1;

		if ( !AquireData( T55x7_PAGE0, T55x7_CONFIGURATION_BLOCK, pwdmode, password ) )
			return 1;
	}

	if (!DecodeT55xxBlock()) return 1;

	// too little space to start with
	if ( DemodBufferLen < 32) return 1;

	//
	//PrintAndLogEx(NORMAL, "Offset+32 ==%d\n DemodLen == %d", config.offset + 32, DemodBufferLen);

	uint8_t si = config.offset;
	uint32_t block0   = PackBits(si, 32, DemodBuffer);
	uint32_t safer    = PackBits(si, 4, DemodBuffer); si += 4;
	uint32_t resv     = PackBits(si, 7, DemodBuffer); si += 7;
	uint32_t dbr      = PackBits(si, 3, DemodBuffer); si += 3;
	uint32_t extend   = PackBits(si, 1, DemodBuffer); si += 1;
	uint32_t datamod  = PackBits(si, 5, DemodBuffer); si += 5;
	uint32_t pskcf    = PackBits(si, 2, DemodBuffer); si += 2;
	uint32_t aor      = PackBits(si, 1, DemodBuffer); si += 1;
	uint32_t otp      = PackBits(si, 1, DemodBuffer); si += 1;
	uint32_t maxblk   = PackBits(si, 3, DemodBuffer); si += 3;
	uint32_t pwd      = PackBits(si, 1, DemodBuffer); si += 1;
	uint32_t sst      = PackBits(si, 1, DemodBuffer); si += 1;
	uint32_t fw       = PackBits(si, 1, DemodBuffer); si += 1;
	uint32_t inv      = PackBits(si, 1, DemodBuffer); si += 1;
	uint32_t por      = PackBits(si, 1, DemodBuffer); si += 1;

	if (config.Q5)
		PrintAndLogEx(NORMAL, _RED_(*** Warning ***) " Config Info read off a Q5 will not display as expected");

	PrintAndLogEx(NORMAL, "");
	PrintAndLogEx(NORMAL, "-- T55x7 Configuration & Tag Information --------------------");
	PrintAndLogEx(NORMAL, "-------------------------------------------------------------");
	PrintAndLogEx(NORMAL, " Safer key                 : %s", GetSaferStr(safer));
	PrintAndLogEx(NORMAL, " reserved                  : %d", resv);
	PrintAndLogEx(NORMAL, " Data bit rate             : %s", GetBitRateStr(dbr, extend));
	PrintAndLogEx(NORMAL, " eXtended mode             : %s", (extend) ? _YELLOW_(Yes - Warning) : "No");
	PrintAndLogEx(NORMAL, " Modulation                : %s", GetModulationStr(datamod));
	PrintAndLogEx(NORMAL, " PSK clock frequency       : %d", pskcf);
	PrintAndLogEx(NORMAL, " AOR - Answer on Request   : %s", (aor) ? _GREEN_(Yes) : "No");
	PrintAndLogEx(NORMAL, " OTP - One Time Pad        : %s", (otp) ? _YELLOW_(Yes - Warning) : "No" );
	PrintAndLogEx(NORMAL, " Max block                 : %d", maxblk);
	PrintAndLogEx(NORMAL, " Password mode             : %s", (pwd) ? _GREEN_(Yes) : "No");
	PrintAndLogEx(NORMAL, " Sequence Start Terminator : %s", (sst) ? _GREEN_(Yes) : "No");
	PrintAndLogEx(NORMAL, " Fast Write                : %s", (fw)  ? _GREEN_(Yes) : "No");
	PrintAndLogEx(NORMAL, " Inverse data              : %s", (inv) ? _GREEN_(Yes) : "No");
	PrintAndLogEx(NORMAL, " POR-Delay                 : %s", (por) ? _GREEN_(Yes) : "No");
	PrintAndLogEx(NORMAL, "-------------------------------------------------------------");
	PrintAndLogEx(NORMAL, " Raw Data - Page 0");
	PrintAndLogEx(NORMAL, "     Block 0  : 0x%08X  %s", block0, sprint_bin(DemodBuffer + config.offset, 32) );
	PrintAndLogEx(NORMAL, "-------------------------------------------------------------");
	return 0;
}

int CmdT55xxDump(const char *Cmd){

	uint32_t password = 0;
	bool override = false;
	char cmdp = tolower(param_getchar(Cmd, 0));
	if ( cmdp == 'h') return usage_t55xx_dump();

	bool usepwd = ( strlen(Cmd) > 0);
	if ( usepwd ){
		password = param_get32ex(Cmd, 0, 0, 16);
		if (param_getchar(Cmd, 1) =='o' )
			override = true;
	}

	printT5xxHeader(0);
	for ( uint8_t i = 0; i < 8; ++i)
		T55xxReadBlock(i, 0, usepwd, override, password);

	printT5xxHeader(1);
	for ( uint8_t	i = 0; i < 4; i++)
		T55xxReadBlock(i, 1, usepwd, override, password);

	return 1;
}

bool AquireData( uint8_t page, uint8_t block, bool pwdmode, uint32_t password ) {
	// arg0 bitmodes:
	// 	bit0 = pwdmode
	// 	bit1 = page to read from
	// arg1: which block to read
	// arg2: password
	uint8_t arg0 = (page<<1) | pwdmode;
	UsbCommand c = {CMD_T55XX_READ_BLOCK, {arg0, block, password}};
	clearCommandBuffer();
	SendCommand(&c);
	if ( !WaitForResponseTimeout(CMD_ACK, NULL, 2500) ) {
		PrintAndLogEx(WARNING, "command execution time out");
		return false;
	}

	uint8_t got[8000];
	if ( !GetFromDevice(BIG_BUF, got, sizeof(got), 0, NULL, 4000, true)) {
		PrintAndLogEx(WARNING, "command execution time out");
		return false;
	}
	setGraphBuf(got, sizeof(got));
	// set signal properties low/high/mean/amplitude and is_noise detection
	computeSignalProperties(got, sizeof(got));
	RepaintGraphWindow();
	return !getSignalProperties()->isnoise;
}

char * GetBitRateStr(uint32_t id, bool xmode) {
 	static char buf[25];

	char *retStr = buf;
	if (xmode) { //xmode bitrate calc is same as em4x05 calc
		snprintf(retStr,sizeof(buf),"%d - RF/%d", id, EM4x05_GET_BITRATE(id));
	} else {
		switch (id){
		case 0:   snprintf(retStr,sizeof(buf),"%d - RF/8",id);   break;
		case 1:   snprintf(retStr,sizeof(buf),"%d - RF/16",id);  break;
		case 2:   snprintf(retStr,sizeof(buf),"%d - RF/32",id);  break;
		case 3:   snprintf(retStr,sizeof(buf),"%d - RF/40",id);  break;
		case 4:   snprintf(retStr,sizeof(buf),"%d - RF/50",id);  break;
		case 5:   snprintf(retStr,sizeof(buf),"%d - RF/64",id);  break;
		case 6:   snprintf(retStr,sizeof(buf),"%d - RF/100",id); break;
		case 7:   snprintf(retStr,sizeof(buf),"%d - RF/128",id); break;
		default:  snprintf(retStr,sizeof(buf),"%d - (Unknown)",id); break;
		}
	}
	return buf;
}

char * GetSaferStr(uint32_t id){
	static char buf[40];
	char *retStr = buf;

	snprintf(retStr,sizeof(buf),"%d",id);
	if (id == 6) {
		snprintf(retStr,sizeof(buf),"%d - passwd",id);
	}
	if (id == 9 ){
		snprintf(retStr,sizeof(buf),"%d - testmode",id);
	}

	return buf;
}

char * GetModulationStr( uint32_t id){
	static char buf[60];
	char *retStr = buf;

	switch (id){
		case 0: snprintf(retStr,sizeof(buf),"%d - DIRECT (ASK/NRZ)",id); break;
		case 1:	snprintf(retStr,sizeof(buf),"%d - PSK 1 phase change when input changes",id); break;
		case 2:	snprintf(retStr,sizeof(buf),"%d - PSK 2 phase change on bitclk if input high",id); break;
		case 3:	snprintf(retStr,sizeof(buf),"%d - PSK 3 phase change on rising edge of input",id); break;
		case 4:	snprintf(retStr,sizeof(buf),"%d - FSK 1 RF/8  RF/5",id); break;
		case 5:	snprintf(retStr,sizeof(buf),"%d - FSK 2 RF/8  RF/10",id); break;
		case 6:	snprintf(retStr,sizeof(buf),"%d - FSK 1a RF/5  RF/8",id); break;
		case 7: snprintf(retStr,sizeof(buf),"%d - FSK 2a RF/10  RF/8",id); break;
		case 8:	snprintf(retStr,sizeof(buf),"%d - Manchester",id); break;
		case 16: snprintf(retStr,sizeof(buf),"%d - Biphase",id); break;
		case 0x18:snprintf(retStr,sizeof(buf),"%d - Biphase a - AKA Conditional Dephase Encoding(CDP)",id); break;
		case 17: snprintf(retStr,sizeof(buf),"%d - Reserved",id); break;
		default: snprintf(retStr,sizeof(buf),"0x%02X (Unknown)",id); break;
		}
	return buf;
}

char * GetModelStrFromCID(uint32_t cid){

	static char buf[10];
	char *retStr = buf;

	if (cid == 1) snprintf(retStr, sizeof(buf),"ATA5577M1");
	if (cid == 2) snprintf(retStr, sizeof(buf),"ATA5577M2");
	return buf;
}

char * GetSelectedModulationStr( uint8_t id){

	static char buf[20];
	char *retStr = buf;

	switch (id){
		case DEMOD_FSK:	snprintf(retStr,sizeof(buf),"FSK");	break;
		case DEMOD_FSK1: snprintf(retStr,sizeof(buf),"FSK1"); break;
		case DEMOD_FSK1a: snprintf(retStr,sizeof(buf),"FSK1a"); break;
		case DEMOD_FSK2: snprintf(retStr,sizeof(buf),"FSK2"); break;
		case DEMOD_FSK2a: snprintf(retStr,sizeof(buf),"FSK2a"); break;
		case DEMOD_ASK: snprintf(retStr,sizeof(buf),"ASK"); break;
		case DEMOD_NRZ: snprintf(retStr,sizeof(buf),"DIRECT/NRZ"); break;
		case DEMOD_PSK1: snprintf(retStr,sizeof(buf),"PSK1"); break;
		case DEMOD_PSK2: snprintf(retStr,sizeof(buf),"PSK2"); break;
		case DEMOD_PSK3: snprintf(retStr,sizeof(buf),"PSK3"); break;
		case DEMOD_BI: snprintf(retStr,sizeof(buf),"BIPHASE"); break;
		case DEMOD_BIa: snprintf(retStr,sizeof(buf),"BIPHASEa - (CDP)"); break;
		default: snprintf(retStr,sizeof(buf),"(Unknown)"); break;
		}
	return buf;
}

void t55x7_create_config_block( int tagtype ){

	/*
     T55X7_DEFAULT_CONFIG_BLOCK, T55X7_RAW_CONFIG_BLOCK
     T55X7_EM_UNIQUE_CONFIG_BLOCK, T55X7_FDXB_CONFIG_BLOCK,
	 T55X7_FDXB_CONFIG_BLOCK, T55X7_HID_26_CONFIG_BLOCK, T55X7_INDALA_64_CONFIG_BLOCK, T55X7_INDALA_224_CONFIG_BLOCK
	 T55X7_GUARDPROXII_CONFIG_BLOCK, T55X7_VIKING_CONFIG_BLOCK,	T55X7_NORALYS_CONFIG_BLOCK, T55X7_IOPROX_CONFIG_BLOCK
	*/
	static char buf[60];
	char *retStr = buf;

	switch (tagtype){
		case 0: snprintf(retStr, sizeof(buf),"%08X - T55X7 Default", T55X7_DEFAULT_CONFIG_BLOCK); break;
		case 1: snprintf(retStr, sizeof(buf),"%08X - T55X7 Raw", T55X7_RAW_CONFIG_BLOCK); break;
		case 2: snprintf(retStr, sizeof(buf),"%08X - T5555 Q5 Default", T5555_DEFAULT_CONFIG_BLOCK); break;
		default:
			break;
	}
	PrintAndLogEx(NORMAL, buf);
}

int CmdResetRead(const char *Cmd) {
	UsbCommand c = {CMD_T55XX_RESET_READ, {0,0,0}};
	clearCommandBuffer();
	SendCommand(&c);
	if ( !WaitForResponseTimeout(CMD_ACK, NULL, 2500) ) {
		PrintAndLogEx(WARNING, "command execution time out");
		return 0;
	}

	uint8_t got[BIGBUF_SIZE-1];
	if ( !GetFromDevice(BIG_BUF, got, sizeof(got), 0, NULL, 2500, false)) {
		PrintAndLogEx(WARNING, "command execution time out");
		return 0;
	}
	setGraphBuf(got, sizeof(got));
	return 1;
}

int CmdT55xxWipe(const char *Cmd) {
	char writeData[20] = {0};
	char *ptrData = writeData;
	char cmdp = param_getchar(Cmd, 0);
	if ( cmdp == 'h' || cmdp == 'H') return usage_t55xx_wipe();

	bool Q5 = (cmdp == 'q' || cmdp == 'Q');

	// Try with the default password to reset block 0
	// With a pwd should work even if pwd bit not set
	PrintAndLogEx(INFO, "\nBeginning Wipe of a T55xx tag (assuming the tag is not password protected)\n");

	if ( Q5 )
		snprintf(ptrData,sizeof(writeData),"b 0 d 6001F004 p 0");
	else
		snprintf(ptrData,sizeof(writeData),"b 0 d 000880E0 p 0");

	if (!CmdT55xxWriteBlock(ptrData)) PrintAndLogEx(WARNING, "Error writing blk 0");

	for (uint8_t blk = 1; blk<8; blk++) {

		snprintf(ptrData,sizeof(writeData),"b %d d 0", blk);

		if (!CmdT55xxWriteBlock(ptrData)) PrintAndLogEx(WARNING, "Error writing blk %d", blk);

		memset(writeData, 0x00, sizeof(writeData));
	}
	return 0;
}

bool IsCancelled(void) {
	if (ukbhit()) {
		int gc = getchar(); (void)gc;
		PrintAndLogEx(WARNING, "\naborted via keyboard!\n");
		return true;
	}
	return false;
}

int CmdT55xxChkPwds(const char *Cmd) {
	// load a default pwd file.
	char line[9];
	char filename[FILE_PATH_SIZE] = {0};
	int	keycnt = 0;
	uint8_t stKeyBlock = 20;
	uint8_t *keyBlock = NULL, *p = NULL;
    bool found = false;
	uint8_t timeout = 0;

	memset(line, 0, sizeof(line));

    char cmdp = tolower(param_getchar(Cmd, 0));
	if (strlen(Cmd) == 0 || cmdp == 'h') return usage_t55xx_chk();

	/*
	if ( T55xxReadBlock(7, 0, 0, 0, 0) ) {

		// now try to validate it..
		PrintAndLogEx(WARNING, "\n Block 7 was readable");
		return 1;
	}
	*/

	uint64_t t1 = msclock();

	if ( cmdp == 'm' ) {
		UsbCommand c = {CMD_T55XX_CHKPWDS, {0,0,0} };
		clearCommandBuffer();
		SendCommand(&c);
		UsbCommand resp;

		while ( !WaitForResponseTimeout(CMD_ACK, &resp, 2000) ) {
			timeout++;
			printf("."); fflush(stdout);
			if (timeout > 180) {
				PrintAndLogEx(WARNING, "\nno response from Proxmark. Aborting...");
				return 2;
			}
		}

		if ( resp.arg[0] ) {
			PrintAndLogEx(SUCCESS, "\nFound a candidate [ %08X ]. Trying to validate", resp.arg[1]);

			if (!AquireData(T55x7_PAGE0, T55x7_CONFIGURATION_BLOCK, true, resp.arg[1])) {
				PrintAndLogEx(INFO, "Aquireing data from device failed. Quitting");
				return 2;
			}

			found = tryDetectModulation();
			if (found) {
				PrintAndLogEx(SUCCESS, "Found valid password: [ %08X ]", resp.arg[1]);
			} else {
				PrintAndLogEx(WARNING, "Password NOT found.");
			}
		} else {
			PrintAndLogEx(WARNING, "Password NOT found.");
		}

		goto out;
	}

	keyBlock = calloc(stKeyBlock, 4);
	if (keyBlock == NULL) return 1;

	if (cmdp == 'i') {

		int len = strlen(Cmd+2);
		if (len > FILE_PATH_SIZE) len = FILE_PATH_SIZE;
		memcpy(filename, Cmd+2, len);

		FILE * f = fopen( filename , "r");
		if ( !f ) {
			PrintAndLogEx(FAILED, "File: " _YELLOW_(%s) ": not found or locked.", filename);
			free(keyBlock);
			return 1;
		}

		while( fgets(line, sizeof(line), f) ){
			if (strlen(line) < 8 || line[7] == '\n') continue;

			//goto next line
			while (fgetc(f) != '\n' && !feof(f)) ;

			//The line start with # is comment, skip
			if( line[0]=='#' ) continue;

			if (!isxdigit(line[0])) {
				PrintAndLogEx(WARNING, "File content error. '%s' must include 8 HEX symbols", line);
				continue;
			}

			line[8] = 0;

			// realloc keyblock array size.
			if ( stKeyBlock - keycnt < 2) {
				p = realloc(keyBlock, 4 * (stKeyBlock += 10));
				if (!p) {
					PrintAndLogEx(WARNING, "Cannot allocate memory for defaultKeys");
					free(keyBlock);
					if (f)
						fclose(f);
					return 2;
				}
				keyBlock = p;
			}
			// clear mem
			memset(keyBlock + 4 * keycnt, 0, 4);

			num_to_bytes( strtoll(line, NULL, 16), 4, keyBlock + 4*keycnt);

//			PrintAndLogEx(NORMAL, "chk custom pwd[%2d] %08X", keycnt, bytes_to_num(keyBlock + 4 * keycnt, 4) );
			keycnt++;
			memset(line, 0, sizeof(line));
		}

		if (f)
			fclose(f);

		if (keycnt == 0) {
			PrintAndLogEx(WARNING, "No keys found in file");
			free(keyBlock);
			return 1;
		}
		PrintAndLogEx(SUCCESS, "Loaded %d keys", keycnt);

		// loop
		uint64_t testpwd = 0x00;
		for (uint16_t c = 0; c < keycnt; ++c ) {

			if ( IsOffline() ) {
				PrintAndLogEx(WARNING, "Device offline\n");
				free(keyBlock);
				return  2;
			}

			if (IsCancelled()) {
				free(keyBlock);
				return 0;
			}

			testpwd = bytes_to_num(keyBlock + 4*c, 4);

			PrintAndLogEx(INFO, "Testing %08X", testpwd);

			if ( !AquireData(T55x7_PAGE0, T55x7_CONFIGURATION_BLOCK, true, testpwd)) {
				PrintAndLogEx(INFO, "Aquireing data from device failed. Quitting");
				free(keyBlock);
				return 0;
			}

			found = tryDetectModulation();
			if ( found )
				break;

		}
		if ( found )
			PrintAndLogEx(SUCCESS, "Found valid password: [ %08X ]", testpwd);
		else
			PrintAndLogEx(WARNING, "Password NOT found.");
	}

	free(keyBlock);

out:
	t1 = msclock() - t1;
	PrintAndLogEx(SUCCESS, "\nTime in bruteforce: %.0f seconds\n", (float)t1/1000.0);
	return 0;
}

int CmdT55xxBruteForce(const char *Cmd) {

    uint32_t start_password = 0x00000000; //start password
    uint32_t end_password   = 0xFFFFFFFF; //end   password
	uint32_t curr = 0;
    bool found = false;


    char cmdp = tolower(param_getchar(Cmd, 0));
	if (cmdp == 'h') return usage_t55xx_bruteforce();

	uint64_t t1 = msclock();

	// Try to read Block 7, first :)

	// incremental pwd range search
    start_password = param_get32ex(Cmd, 0, 0, 16);
	end_password = param_get32ex(Cmd, 1, 0, 16);

	curr = start_password;

	if ( start_password >= end_password ) {
		return usage_t55xx_bruteforce();
	}

    PrintAndLogEx(INFO, "Search password range [%08X -> %08X]", start_password, end_password);

    while ( !found ){

		printf("."); fflush(stdout);

		if (IsCancelled()) {
			return 0;
		}

		if (!AquireData(T55x7_PAGE0, T55x7_CONFIGURATION_BLOCK, true, curr)) {
			PrintAndLogEx(WARNING, "Aquiring data from device failed. Quitting");
			return 0;
		}

		found = tryDetectModulation();

		if (curr == end_password)
			break;
		curr++;
    }

    PrintAndLogEx(NORMAL, "");

    if (found)
		PrintAndLogEx(SUCCESS, "Found valid password: [ %08X ]", curr);
    else
		PrintAndLogEx(WARNING, "Password NOT found. Last tried: [ %08X ]", --curr);

	t1 = msclock() - t1;
	PrintAndLogEx(SUCCESS, "\nTime in bruteforce: %.0f seconds\n", (float)t1/1000.0);
    return 0;
}

int tryOnePassword(uint32_t password) {
	PrintAndLogEx(INFO, "Trying password %08x", password);
	if (!AquireData(T55x7_PAGE0, T55x7_CONFIGURATION_BLOCK, true, password)) {
		PrintAndLogEx(NORMAL, "Acquire data from device failed. Quitting");
		return -1;
	}

	if (tryDetectModulation())
		return 1;
	else
		return 0;
}

int CmdT55xxRecoverPW(const char *Cmd) {
	int bit = 0;
	uint32_t orig_password = 0x0;
	uint32_t curr_password = 0x0;
	uint32_t prev_password = 0xffffffff;
	uint32_t mask = 0x0;
	int found = 0;
	char cmdp = tolower(param_getchar(Cmd, 0));
	if (cmdp == 'h' ) return usage_t55xx_recoverpw();

	orig_password = param_get32ex(Cmd, 0, 0x51243648, 16); //password used by handheld cloners

	// first try fliping each bit in the expected password
	while (bit < 32) {
		curr_password = orig_password ^ ( 1 << bit );
		found = tryOnePassword(curr_password);
		if (found == -1) return 0;
		bit++;

		if (IsCancelled()) return 0;
	}

	// now try to use partial original password, since block 7 should have been completely
	// erased during the write sequence and it is possible that only partial password has been
	// written
	// not sure from which end the bit bits are written, so try from both ends
	// from low bit to high bit
	bit = 0;
	while (bit < 32) {
		mask += ( 1 << bit );
		curr_password = orig_password & mask;
		// if updated mask didn't change the password, don't try it again
		if (prev_password == curr_password) {
			bit++;
			continue;
		}
		found = tryOnePassword(curr_password);
		if (found == -1) return 0;
		bit++;
		prev_password = curr_password;

		if (IsCancelled()) return 0;
	}

	// from high bit to low
	bit = 0;
	mask = 0xffffffff;
	while (bit < 32) {
		mask -= ( 1 << bit );
		curr_password = orig_password & mask;
		// if updated mask didn't change the password, don't try it again
		if (prev_password == curr_password) {
			bit++;
			continue;
		}
		found = tryOnePassword(curr_password);
		if (found == -1)
			return 0;
		bit++;
		prev_password = curr_password;

		if (IsCancelled()) return 0;
	}

	PrintAndLogEx(NORMAL, "");

	if (found == 1)
		PrintAndLogEx(SUCCESS, "Found valid password: [%08x]", curr_password);
	else
		PrintAndLogEx(WARNING, "Password NOT found.");

	return 0;
}

// note length of data returned is different for different chips.
// some return all page 1 (64 bits) and others return just that block (32 bits)
// unfortunately the 64 bits makes this more likely to get a false positive...
bool tryDetectP1(bool getData) {
	uint8_t preamble[] = {1,1,1,0,0,0,0,0,0,0,0,1,0,1,0,1};
	size_t startIdx = 0;
	uint8_t fc1 = 0, fc2 = 0, ans = 0;
	int clk = 0, firstClockEdge = 0;
	bool st = true;

	if ( getData ) {
		if ( !AquireData(T55x7_PAGE1, 1, false, 0) )
			return false;
	}

	// try fsk clock detect. if successful it cannot be any other type of modulation...  (in theory...)
	ans = fskClocks(&fc1, &fc2, (uint8_t *)&clk, &firstClockEdge);
	if (ans && ((fc1==10 && fc2==8) || (fc1==8 && fc2==5))) {
		if ( FSKrawDemod("0 0", false) &&
			  preambleSearchEx(DemodBuffer, preamble, sizeof(preamble), &DemodBufferLen, &startIdx, false) &&
			  (DemodBufferLen == 32 || DemodBufferLen == 64) ) {
			return true;
		}
		if ( FSKrawDemod("0 1", false) &&
			  preambleSearchEx(DemodBuffer, preamble, sizeof(preamble), &DemodBufferLen, &startIdx, false) &&
			  (DemodBufferLen == 32 || DemodBufferLen == 64) ) {
			return true;
		}
		return false;
	}

	// try ask clock detect.  it could be another type even if successful.
	clk = GetAskClock("", false);
	if (clk > 0) {
		if ( ASKDemod_ext("0 0 1", false, false, 1, &st) &&
			  preambleSearchEx(DemodBuffer, preamble, sizeof(preamble), &DemodBufferLen, &startIdx, false) &&
			  (DemodBufferLen == 32 || DemodBufferLen == 64) ) {
			return true;
		}
		st = true;
		if ( ASKDemod_ext("0 1 1", false, false, 1, &st)  &&
				preambleSearchEx(DemodBuffer, preamble, sizeof(preamble), &DemodBufferLen, &startIdx, false) &&
				(DemodBufferLen == 32 || DemodBufferLen == 64) ) {
			return true;
		}
		if ( ASKbiphaseDemod("0 0 0 2", false) &&
				preambleSearchEx(DemodBuffer, preamble, sizeof(preamble), &DemodBufferLen, &startIdx, false) &&
				(DemodBufferLen == 32 || DemodBufferLen == 64) ) {
			return true;
		}
		if ( ASKbiphaseDemod("0 0 1 2", false) &&
				preambleSearchEx(DemodBuffer, preamble, sizeof(preamble), &DemodBufferLen, &startIdx, false) &&
				(DemodBufferLen == 32 || DemodBufferLen == 64) ) {
			return true;
		}
	}

	// try NRZ clock detect.  it could be another type even if successful.
	clk = GetNrzClock("", false); //has the most false positives :(
	if (clk > 0) {
		if ( NRZrawDemod("0 0 1", false)  &&
				preambleSearchEx(DemodBuffer, preamble, sizeof(preamble), &DemodBufferLen, &startIdx, false) &&
				(DemodBufferLen == 32 || DemodBufferLen == 64) ) {
			return true;
		}
		if ( NRZrawDemod("0 1 1", false)  &&
				preambleSearchEx(DemodBuffer, preamble, sizeof(preamble), &DemodBufferLen, &startIdx, false) &&
				(DemodBufferLen == 32 || DemodBufferLen == 64) ) {
			return true;
		}
	}

	// Fewer card uses PSK
	// try psk clock detect. if successful it cannot be any other type of modulation... (in theory...)
	clk = GetPskClock("", false);
	if (clk > 0) {
		// allow undo
		// save_restoreGB(GRAPH_SAVE);
		// skip first 160 samples to allow antenna to settle in (psk gets inverted occasionally otherwise)
		//CmdLtrim("160");
		if ( PSKDemod("0 0 6", false) &&
			  preambleSearchEx(DemodBuffer, preamble, sizeof(preamble), &DemodBufferLen, &startIdx, false) &&
			  (DemodBufferLen == 32 || DemodBufferLen == 64) ) {
			//save_restoreGB(GRAPH_RESTORE);
			return true;
		}
		if ( PSKDemod("0 1 6", false) &&
			  preambleSearchEx(DemodBuffer, preamble, sizeof(preamble), &DemodBufferLen, &startIdx, false) &&
			  (DemodBufferLen == 32 || DemodBufferLen == 64) ) {
			//save_restoreGB(GRAPH_RESTORE);
			return true;
		}
		// PSK2 - needs a call to psk1TOpsk2.
		if ( PSKDemod("0 0 6", false)) {
			psk1TOpsk2(DemodBuffer, DemodBufferLen);
			if (preambleSearchEx(DemodBuffer, preamble, sizeof(preamble), &DemodBufferLen, &startIdx, false) &&
				  (DemodBufferLen == 32 || DemodBufferLen == 64) ) {
				//save_restoreGB(GRAPH_RESTORE);
				return true;
			}
		} // inverse waves does not affect PSK2 demod
		//undo trim samples
		//save_restoreGB(GRAPH_RESTORE); 
		// no other modulation clocks = 2 or 4 so quit searching
		if (fc1 != 8) return false;
	}

	return false;
}
//  does this need to be a callable command?
int CmdT55xxDetectPage1(const char *Cmd){
	bool errors = false;
	bool useGB = false;
	bool usepwd = false;
	uint32_t password = 0;
	uint8_t cmdp = 0;

	while (param_getchar(Cmd, cmdp) != 0x00 && !errors) {
		switch (tolower(param_getchar(Cmd, cmdp))) {
		case 'h':
			return usage_t55xx_detectP1();
		case 'p':
			password = param_get32ex(Cmd, cmdp+1, 0, 16);
			usepwd = true;
			cmdp += 2;
			break;
		case '1':
			// use Graphbuffer data
			useGB = true;
			cmdp++;
			break;
		default:
			PrintAndLogEx(WARNING, "Unknown parameter '%c'", param_getchar(Cmd, cmdp));
			errors = true;
			break;
		}
	}
	if (errors) return usage_t55xx_detectP1();

	if ( !useGB ) {
		if ( !AquireData(T55x7_PAGE1, 1, usepwd, password) )
			return false;
	}
	bool success = tryDetectP1(false);
	if (success) PrintAndLogEx(SUCCESS, "T55xx chip found!");
	return success;
}

int CmdT55xxSetDeviceConfig(const char *Cmd){
	uint8_t startgap = 0, writegap = 0;
	uint8_t write0 = 0, write1 = 0, readgap = 0;
	bool errors = false, shall_persist = false;
	uint8_t cmdp = 0;
	while (param_getchar(Cmd, cmdp) != 0x00 && !errors) {
		switch (tolower(param_getchar(Cmd, cmdp))) {
		case 'h':
			return usage_lf_deviceconfig();
		case 'a':
			errors |= param_getdec(Cmd, cmdp+1, &startgap);
			cmdp += 2;
			break;
		case 'b':
			errors |= param_getdec(Cmd, cmdp+1, &writegap);
			cmdp += 2;
			break;
		case 'c':
			errors |= param_getdec(Cmd, cmdp+1, &write0);
			cmdp += 2;
			break;
		case 'd':
			errors |= param_getdec(Cmd, cmdp+1, &write1);
			cmdp += 2;
			break;
		case 'e':
			errors |= param_getdec(Cmd, cmdp+1, &readgap);
			cmdp += 2;
			break;
		case 'p':
			shall_persist = true;
			cmdp++;
			break;
		default:
			PrintAndLogEx(WARNING, "Unknown parameter '%c'", param_getchar(Cmd, cmdp));
			errors = 1;
			break;
		}
	}

	//Validations
	if (errors || cmdp == 0) return usage_lf_deviceconfig();

	t55xx_config config = { startgap*8, writegap*8, write0*8, write1*8, readgap*8 };

	UsbCommand c = {CMD_SET_LF_T55XX_CONFIG, {shall_persist,0,0} };
	memcpy(c.d.asBytes, &config, sizeof(t55xx_config));
	clearCommandBuffer();
	SendCommand(&c);
	return 0;
}

static command_t CommandTable[] = {
	{"help",		CmdHelp,           1, "This help"},
	{"bruteforce",	CmdT55xxBruteForce,0, "<start password> <end password> [i <*.dic>] Simple bruteforce attack to find password"},
	{"config",		CmdT55xxSetConfig, 1, "Set/Get T55XX configuration (modulation, inverted, offset, rate)"},
	{"chk",			CmdT55xxChkPwds,   1, "Check passwords"},
	{"detect",		CmdT55xxDetect,    1, "[1] Try detecting the tag modulation from reading the configuration block."},
	{"deviceconfig", CmdT55xxSetDeviceConfig, 1, "Set/Get T55XX device configuration (startgap, writegap, write0, write1, readgap"},
	{"p1detect",	CmdT55xxDetectPage1,1, "[1] Try detecting if this is a t55xx tag by reading page 1"},
	{"dump",		CmdT55xxDump,      0, "[password] [o] Dump T55xx card block 0-7. Optional [password], [override]"},
	{"info",		CmdT55xxInfo,      1, "[1] Show T55x7 configuration data (page 0/ blk 0)"},
	{"read",		CmdT55xxReadBlock, 0, "b <block> p [password] [o] [1] -- Read T55xx block data. Optional [p password], [override], [page1]"},
	{"resetread",	CmdResetRead,      0, "Send Reset Cmd then lf read the stream to attempt to identify the start of it (needs a demod and/or plot after)"},
	{"recoverpw",	CmdT55xxRecoverPW, 0, "[password] Try to recover from bad password write from a cloner. Only use on PW protected chips!"},
	{"special",		special,           0, "Show block changes with 64 different offsets"},
	{"trace",		CmdT55xxReadTrace, 1, "[1] Show T55x7 traceability data (page 1/ blk 0-1)"},
	{"wakeup",		CmdT55xxWakeUp,    0, "Send AOR wakeup command"},
	{"wipe",		CmdT55xxWipe,      0, "[q] Wipe a T55xx tag and set defaults (will destroy any data on tag)"},
	{"write",		CmdT55xxWriteBlock,0, "b <block> d <data> p [password] [1] -- Write T55xx block data. Optional [p password], [page1]"},
	{NULL, NULL, 0, NULL}
};

int CmdLFT55XX(const char *Cmd) {
	clearCommandBuffer();
	CmdsParse(CommandTable, Cmd);
	return 0;
}

int CmdHelp(const char *Cmd) {
	CmdsHelp(CommandTable);
	return 0;
}

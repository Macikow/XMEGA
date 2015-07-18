/*
 * vt100.h
 *
 * Created: 3/28/2015 2:42:50 PM
 *  Author: Maciej
 */ 


#ifndef VT100_H_
#define VT100_H_

/////////////////////////vt /////////////////////////
#define SET_DEFAULT_FONT					"\x1B("
#define SET_ALTERNATIVE_FONT				"\x1B)"
#define	ERASE_FROM_CURSOR_TO_END_OF_LINE 	"\0x1B[K"		//Erases from the current cursor position to the end of the current line.	<ESC>[K
#define	ERASE_LINE_TO_CURSOR				"\0x1B[1K"		//Erases from the current cursor position to the start of the current line.
#define	ERASE_LINE 							"\0x1B[2K"		//Erases the entire current line.
#define	ERASE_FORM_CURRENT_LINE_TO_THE_END	"\033[J"		//Erases the screen from the current line down to the bottom of the screen.
#define	ERASE_FORM_CURREN_LINE_TO_THE_TOP	"\033[1J"		//Erases the screen from the current line up to the top of the screen.
#define	ERASE_SCREEN	"\033[2J"		//Erases the screen with the background colour and moves the cursor to home.
//Cursor control
#define CURSOR_HOME			"\x1B[1;1H"
#define CURSOR_UP			"\x1B[1A"
#define CURSOR_DOWN			"\x1B[1B"
#define CURSOR_FORWARD		"\x1B[1C"
#define CURSOR_BACKWARD		"\x1B[1D"
#define CURSOR_POSITION 
//General text attributes
#define RESET_ALL_ATTR		"\x1B[0m"	//sgr0	Reset all attributes
#define SET_BRIGHT_ATTR		"\x1B[1m"	//bold	Set "bright" attribute
#define SET_DIM_ATTR		"\x1B[2m"	//dim	Set "dim" attribute
#define SET_UNDERSCORE_ATTR "\x1B[4m"	//set smul unset rmul :?:	Set "underscore" (underlined text) attribute
#define SET_BLINK_ATTR		"\x1B[5m"	//blink	Set "blink" attribute
#define SET_RECERSE_ATTR	"\x1B[7m"	//rev	Set "reverse" attribute
#define SET_HIDDEN_ATTR		"\x1B[8m"	//invis	Set "hidden" attribute
//Foreground coloring
#define	SET_FORE_BLACK		"\x1B[30m"	//	setaf 0	Set foreground to color #0 - black
#define	SET_FORE_RED		"\x1B[31m"	//	setaf 1	Set foreground to color #1 - red
#define	SET_FORE_GREEN		"\x1B[32m"	//	setaf 2	Set foreground to color #2 - green
#define	SET_FORE_YELLOW		"\x1B[33m"	//	setaf 3	Set foreground to color #3 - yellow
#define	SET_FORE_BLUE		"\x1B[34m"	//	setaf 4	Set foreground to color #4 - blue
#define	SET_FORE_MAGNETA	"\x1B[35m"	//	setaf 5	Set foreground to color #5 - magenta
#define	SET_FORE_CYAN		"\x1B[36m"	//	setaf 6	Set foreground to color #6 - cyan
#define	SET_FORE_WHITE		"\x1B[37m"	//	setaf 7	Set foreground to color #7 - white
#define	SET_FORE_DEFAULT	"\x1B[39m"	//	setaf 9	Set default color as foreground color
//Background coloring
#define SET_BACK_BLACK		"\x1B[40m"	//	setab 0	Set background to color #0 - black
#define SET_BACK_RED		"\x1B[41m"	//	setab 1	Set background to color #1 - red
#define SET_BACK_GREEN		"\x1B[42m"	//	setab 2	Set background to color #2 - green
#define SET_BACK_YELLOW		"\x1B[43m"	//	setab 3	Set background to color #3 - yellow
#define SET_BACK_BLUE		"\x1B[44m"	//	setab 4	Set background to color #4 - blue
#define SET_BACK_MAGNETA	"\x1B[45m"	//	setab 5	Set background to color #5 - magenta
#define SET_BACK_CYAN		"\x1B[46m"	//	setab 6	Set background to color #6 - cyan
#define SET_BACK_WHITE		"\x1B[47m"	//	setab 7	Set background to color #7 - white
#define SET_BACK_DEFAULT	"\x1B[49m"	//	setaf 9	Set default color as background color



#endif /* VT100_H_ */
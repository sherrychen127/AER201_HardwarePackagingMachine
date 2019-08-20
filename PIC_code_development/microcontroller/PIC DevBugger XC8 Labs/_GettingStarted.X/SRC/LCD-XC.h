
#define LCD-XC_H
// set up the timing for the LCD delays

#define	LCD_delay           5                           
#define	LCD_Startup         5                           

// Command set for Hitachi 44780U LCD display controller
#define LCD_CLEAR           0x01
#define LCD_HOME            0x02
#define LCD_CURSOR_BACK     0x10
#define LCD_CURSOR_FWD      0x14
#define LCD_PAN_LEFT        0x18
#define LCD_PAN_RIGHT       0x1C
#define LCD_CURSOR_OFF      0x0C
#define LCD_CURSOR_ON       0x0E
#define LCD_CURSOR_BLINK    0x0F
#define LCD_CURSOR_LINE2    0xC0

// Macros Recomended for new labs
#define mOPEN_LCD           LCDInit()
#define mLCD_PAN_RIGHT      LCDPutCmd (LCD_PAN_RIGHT)
#define mLCD_PAN_LEFT       LCDPutCmd (LCD_PAN_LEFT)
#define mLCD_CURSOR_BLINK   LCDPutCmd (LCD_CURSOR_BLINK)
#define mLCD_HOME           LCDPutCmd (LCD_HOME)
#define mLCD_CLEAR          LCDPutCmd (LCD_CLEAR)
#define mCURSOR_ON          LCDPutCmd (LCD_CURSOR_ON)
#define mCURSOR_OFF         LCDPutCmd (LCD_CURSOR_OFF)
#define mCURSOR_FWD         LCDPutCmd (LCD_CURSOR_FWD)
#define mCURSOR_BACK        LCDPutCmd (LCD_CURSOR_BACK)
#define mLCD_LINE2          LCDPutCmd (LCD_CURSOR_LINE2)

// Common Function Prototypes for XC8 & XC16
void LCDInit(void);
void LCDPutChar(unsigned char ch);
void LCDPutCmd(unsigned char cmd);

// Common legecy Macros
#define LCDHome()           LCDPutCmd (LCD_HOME)         // legacy support
#define LCDClr()            LCDPutCmd (LCD_CLEAR)        // legacy support
#define LCDPutChar            LCDPutChar                   // legacy support


#if __XC8
//----------------------------------------------------------------------
// Definitions specific to the XC8 compiler
//----------------------------------------------------------------------

// display controller set up commands from page 46 of Hitachi datasheet
#define FUNCTION_SET        0x28                         // 4 bit interface, 2 lines, 5x8 font
#define ENTRY_MODE          0x06                         // increment mode
#define DISPLAY_SETUP       0x0C                         // display on, cursor off, blink off

// Macro Definitions specific to XC8 (not reconended for new code)
#define text_display        LCDPutStr                    // legacy support
#define LCDLine1()          LCDPutCmd (LCD_HOME)         // legacy support
#define LCDLine2()          LCDPutCmd (LCD_CURSOR_LINE2) // legacy support
#define shift_cursor()      LCDPutCmd (LCD_CURSOR_FWD)   // legacy support
#define cursor_on()         LCDPutCmd (LCD_CURSOR_ON)    // legacy support
#define DisplayClr()        LCDPutCmd (LCD_CLEAR)        // Legacy support

// Function prototypes
void LCDInit(void );                                     // initialize the LCD module
void LCDPutChar(unsigned char);                          // display an ASCii character in data mode
void LCDPutCmd(unsigned char);                           // send an ASCii command to the LCD in instruction mode
void LCDPutStr(unsigned char *);                         // display a string
void LCDWriteNibble(unsigned char,unsigned char);

//----------------------------------------------------------------------
// Definitions specific to the PICDEM 2 Plus
// These apply to the Black (2011), Green (2007) and Red (2001) versions
//----------------------------------------------------------------------

//  single bit for selecting command register or data register
#define instr        0
#define data         1

// These #defines create the pin connections to the LCD in case they are changed on a future demo board
#define LCD_PORT     PORTD

#define	LCD_EN       PORTDbits.RD3                      // LCD enable
#define	LCD_RS       PORTDbits.RD2                      // LCD register select line

#define	LCD_EN_DIR   TRISDbits.TRISD3
#define	LCD_RS_DIR   TRISDbits.TRISD2
#endif
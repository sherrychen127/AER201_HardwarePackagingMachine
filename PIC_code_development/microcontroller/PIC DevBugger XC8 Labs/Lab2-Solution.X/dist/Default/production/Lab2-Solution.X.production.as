opt subtitle "Microchip Technology Omniscient Code Generator v1.40 (Free mode) build 201612010151"

opt pagewidth 120

	opt lm

	processor	18F4620
opt include "D:\Program Files (x86)\Microchip\xc8\v1.40\include\18f4620.cgen.inc"
clrc   macro
	bcf	status,0
endm
setc   macro
	bsf	status,0
endm
clrz   macro
	bcf	status,2
endm
setz   macro
	bsf	status,2
endm
skipnz macro
	btfsc	status,2
endm
skipz  macro
	btfss	status,2
endm
skipnc macro
	btfsc	status,0
endm
skipc  macro
	btfss	status,0
endm
pushw macro
	movwf postinc1
endm
pushf macro arg1
	movff arg1, postinc1
endm
popw macro
	movf postdec1,f
	movf indf1,w
endm
popf macro arg1
	movf postdec1,f
	movff indf1,arg1
endm
popfc macro arg1
	movff plusw1,arg1
	decfsz fsr1,f
endm
	global	__ramtop
	global	__accesstop
# 51 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PORTA equ 0F80h ;# 
# 187 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PORTB equ 0F81h ;# 
# 357 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PORTC equ 0F82h ;# 
# 531 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PORTD equ 0F83h ;# 
# 672 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PORTE equ 0F84h ;# 
# 874 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
LATA equ 0F89h ;# 
# 985 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
LATB equ 0F8Ah ;# 
# 1096 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
LATC equ 0F8Bh ;# 
# 1207 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
LATD equ 0F8Ch ;# 
# 1318 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
LATE equ 0F8Dh ;# 
# 1369 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TRISA equ 0F92h ;# 
# 1374 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
DDRA equ 0F92h ;# 
# 1590 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TRISB equ 0F93h ;# 
# 1595 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
DDRB equ 0F93h ;# 
# 1811 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TRISC equ 0F94h ;# 
# 1816 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
DDRC equ 0F94h ;# 
# 2032 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TRISD equ 0F95h ;# 
# 2037 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
DDRD equ 0F95h ;# 
# 2253 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TRISE equ 0F96h ;# 
# 2258 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
DDRE equ 0F96h ;# 
# 2416 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
OSCTUNE equ 0F9Bh ;# 
# 2480 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PIE1 equ 0F9Dh ;# 
# 2556 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PIR1 equ 0F9Eh ;# 
# 2632 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
IPR1 equ 0F9Fh ;# 
# 2708 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PIE2 equ 0FA0h ;# 
# 2773 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PIR2 equ 0FA1h ;# 
# 2838 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
IPR2 equ 0FA2h ;# 
# 2903 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
EECON1 equ 0FA6h ;# 
# 2968 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
EECON2 equ 0FA7h ;# 
# 2974 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
EEDATA equ 0FA8h ;# 
# 2980 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
EEADR equ 0FA9h ;# 
# 2986 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
EEADRH equ 0FAAh ;# 
# 2992 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
RCSTA equ 0FABh ;# 
# 2997 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
RCSTA1 equ 0FABh ;# 
# 3201 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TXSTA equ 0FACh ;# 
# 3206 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TXSTA1 equ 0FACh ;# 
# 3456 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TXREG equ 0FADh ;# 
# 3461 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TXREG1 equ 0FADh ;# 
# 3467 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
RCREG equ 0FAEh ;# 
# 3472 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
RCREG1 equ 0FAEh ;# 
# 3478 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SPBRG equ 0FAFh ;# 
# 3483 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SPBRG1 equ 0FAFh ;# 
# 3489 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SPBRGH equ 0FB0h ;# 
# 3495 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
T3CON equ 0FB1h ;# 
# 3606 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR3 equ 0FB2h ;# 
# 3612 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR3L equ 0FB2h ;# 
# 3618 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR3H equ 0FB3h ;# 
# 3624 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CMCON equ 0FB4h ;# 
# 3713 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CVRCON equ 0FB5h ;# 
# 3791 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
ECCP1AS equ 0FB6h ;# 
# 3872 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PWM1CON equ 0FB7h ;# 
# 3941 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
BAUDCON equ 0FB8h ;# 
# 3946 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
BAUDCTL equ 0FB8h ;# 
# 4112 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCP2CON equ 0FBAh ;# 
# 4190 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCPR2 equ 0FBBh ;# 
# 4196 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCPR2L equ 0FBBh ;# 
# 4202 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCPR2H equ 0FBCh ;# 
# 4208 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCP1CON equ 0FBDh ;# 
# 4304 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCPR1 equ 0FBEh ;# 
# 4310 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCPR1L equ 0FBEh ;# 
# 4316 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCPR1H equ 0FBFh ;# 
# 4322 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
ADCON2 equ 0FC0h ;# 
# 4392 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
ADCON1 equ 0FC1h ;# 
# 4476 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
ADCON0 equ 0FC2h ;# 
# 4594 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
ADRES equ 0FC3h ;# 
# 4600 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
ADRESL equ 0FC3h ;# 
# 4606 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
ADRESH equ 0FC4h ;# 
# 4612 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SSPCON2 equ 0FC5h ;# 
# 4673 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SSPCON1 equ 0FC6h ;# 
# 4742 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SSPSTAT equ 0FC7h ;# 
# 4962 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SSPADD equ 0FC8h ;# 
# 4968 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SSPBUF equ 0FC9h ;# 
# 4974 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
T2CON equ 0FCAh ;# 
# 5044 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PR2 equ 0FCBh ;# 
# 5049 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
MEMCON equ 0FCBh ;# 
# 5153 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR2 equ 0FCCh ;# 
# 5159 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
T1CON equ 0FCDh ;# 
# 5261 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR1 equ 0FCEh ;# 
# 5267 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR1L equ 0FCEh ;# 
# 5273 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR1H equ 0FCFh ;# 
# 5279 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
RCON equ 0FD0h ;# 
# 5411 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
WDTCON equ 0FD1h ;# 
# 5438 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
HLVDCON equ 0FD2h ;# 
# 5443 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
LVDCON equ 0FD2h ;# 
# 5707 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
OSCCON equ 0FD3h ;# 
# 5783 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
T0CON equ 0FD5h ;# 
# 5859 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR0 equ 0FD6h ;# 
# 5865 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR0L equ 0FD6h ;# 
# 5871 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR0H equ 0FD7h ;# 
# 5877 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
STATUS equ 0FD8h ;# 
# 5947 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR2 equ 0FD9h ;# 
# 5953 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR2L equ 0FD9h ;# 
# 5959 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR2H equ 0FDAh ;# 
# 5965 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PLUSW2 equ 0FDBh ;# 
# 5971 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PREINC2 equ 0FDCh ;# 
# 5977 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
POSTDEC2 equ 0FDDh ;# 
# 5983 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
POSTINC2 equ 0FDEh ;# 
# 5989 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
INDF2 equ 0FDFh ;# 
# 5995 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
BSR equ 0FE0h ;# 
# 6001 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR1 equ 0FE1h ;# 
# 6007 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR1L equ 0FE1h ;# 
# 6013 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR1H equ 0FE2h ;# 
# 6019 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PLUSW1 equ 0FE3h ;# 
# 6025 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PREINC1 equ 0FE4h ;# 
# 6031 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
POSTDEC1 equ 0FE5h ;# 
# 6037 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
POSTINC1 equ 0FE6h ;# 
# 6043 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
INDF1 equ 0FE7h ;# 
# 6049 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
WREG equ 0FE8h ;# 
# 6060 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR0 equ 0FE9h ;# 
# 6066 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR0L equ 0FE9h ;# 
# 6072 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR0H equ 0FEAh ;# 
# 6078 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PLUSW0 equ 0FEBh ;# 
# 6084 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PREINC0 equ 0FECh ;# 
# 6090 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
POSTDEC0 equ 0FEDh ;# 
# 6096 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
POSTINC0 equ 0FEEh ;# 
# 6102 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
INDF0 equ 0FEFh ;# 
# 6108 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
INTCON3 equ 0FF0h ;# 
# 6199 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
INTCON2 equ 0FF1h ;# 
# 6268 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
INTCON equ 0FF2h ;# 
# 6384 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PROD equ 0FF3h ;# 
# 6390 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PRODL equ 0FF3h ;# 
# 6396 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PRODH equ 0FF4h ;# 
# 6402 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TABLAT equ 0FF5h ;# 
# 6410 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TBLPTR equ 0FF6h ;# 
# 6416 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TBLPTRL equ 0FF6h ;# 
# 6422 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TBLPTRH equ 0FF7h ;# 
# 6428 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TBLPTRU equ 0FF8h ;# 
# 6436 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PCLAT equ 0FF9h ;# 
# 6443 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PC equ 0FF9h ;# 
# 6449 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PCL equ 0FF9h ;# 
# 6455 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PCLATH equ 0FFAh ;# 
# 6461 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PCLATU equ 0FFBh ;# 
# 6467 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
STKPTR equ 0FFCh ;# 
# 6572 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TOS equ 0FFDh ;# 
# 6578 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TOSL equ 0FFDh ;# 
# 6584 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TOSH equ 0FFEh ;# 
# 6590 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TOSU equ 0FFFh ;# 
# 51 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PORTA equ 0F80h ;# 
# 187 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PORTB equ 0F81h ;# 
# 357 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PORTC equ 0F82h ;# 
# 531 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PORTD equ 0F83h ;# 
# 672 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PORTE equ 0F84h ;# 
# 874 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
LATA equ 0F89h ;# 
# 985 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
LATB equ 0F8Ah ;# 
# 1096 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
LATC equ 0F8Bh ;# 
# 1207 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
LATD equ 0F8Ch ;# 
# 1318 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
LATE equ 0F8Dh ;# 
# 1369 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TRISA equ 0F92h ;# 
# 1374 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
DDRA equ 0F92h ;# 
# 1590 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TRISB equ 0F93h ;# 
# 1595 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
DDRB equ 0F93h ;# 
# 1811 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TRISC equ 0F94h ;# 
# 1816 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
DDRC equ 0F94h ;# 
# 2032 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TRISD equ 0F95h ;# 
# 2037 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
DDRD equ 0F95h ;# 
# 2253 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TRISE equ 0F96h ;# 
# 2258 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
DDRE equ 0F96h ;# 
# 2416 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
OSCTUNE equ 0F9Bh ;# 
# 2480 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PIE1 equ 0F9Dh ;# 
# 2556 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PIR1 equ 0F9Eh ;# 
# 2632 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
IPR1 equ 0F9Fh ;# 
# 2708 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PIE2 equ 0FA0h ;# 
# 2773 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PIR2 equ 0FA1h ;# 
# 2838 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
IPR2 equ 0FA2h ;# 
# 2903 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
EECON1 equ 0FA6h ;# 
# 2968 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
EECON2 equ 0FA7h ;# 
# 2974 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
EEDATA equ 0FA8h ;# 
# 2980 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
EEADR equ 0FA9h ;# 
# 2986 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
EEADRH equ 0FAAh ;# 
# 2992 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
RCSTA equ 0FABh ;# 
# 2997 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
RCSTA1 equ 0FABh ;# 
# 3201 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TXSTA equ 0FACh ;# 
# 3206 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TXSTA1 equ 0FACh ;# 
# 3456 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TXREG equ 0FADh ;# 
# 3461 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TXREG1 equ 0FADh ;# 
# 3467 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
RCREG equ 0FAEh ;# 
# 3472 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
RCREG1 equ 0FAEh ;# 
# 3478 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SPBRG equ 0FAFh ;# 
# 3483 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SPBRG1 equ 0FAFh ;# 
# 3489 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SPBRGH equ 0FB0h ;# 
# 3495 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
T3CON equ 0FB1h ;# 
# 3606 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR3 equ 0FB2h ;# 
# 3612 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR3L equ 0FB2h ;# 
# 3618 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR3H equ 0FB3h ;# 
# 3624 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CMCON equ 0FB4h ;# 
# 3713 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CVRCON equ 0FB5h ;# 
# 3791 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
ECCP1AS equ 0FB6h ;# 
# 3872 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PWM1CON equ 0FB7h ;# 
# 3941 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
BAUDCON equ 0FB8h ;# 
# 3946 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
BAUDCTL equ 0FB8h ;# 
# 4112 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCP2CON equ 0FBAh ;# 
# 4190 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCPR2 equ 0FBBh ;# 
# 4196 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCPR2L equ 0FBBh ;# 
# 4202 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCPR2H equ 0FBCh ;# 
# 4208 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCP1CON equ 0FBDh ;# 
# 4304 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCPR1 equ 0FBEh ;# 
# 4310 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCPR1L equ 0FBEh ;# 
# 4316 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
CCPR1H equ 0FBFh ;# 
# 4322 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
ADCON2 equ 0FC0h ;# 
# 4392 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
ADCON1 equ 0FC1h ;# 
# 4476 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
ADCON0 equ 0FC2h ;# 
# 4594 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
ADRES equ 0FC3h ;# 
# 4600 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
ADRESL equ 0FC3h ;# 
# 4606 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
ADRESH equ 0FC4h ;# 
# 4612 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SSPCON2 equ 0FC5h ;# 
# 4673 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SSPCON1 equ 0FC6h ;# 
# 4742 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SSPSTAT equ 0FC7h ;# 
# 4962 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SSPADD equ 0FC8h ;# 
# 4968 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
SSPBUF equ 0FC9h ;# 
# 4974 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
T2CON equ 0FCAh ;# 
# 5044 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PR2 equ 0FCBh ;# 
# 5049 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
MEMCON equ 0FCBh ;# 
# 5153 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR2 equ 0FCCh ;# 
# 5159 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
T1CON equ 0FCDh ;# 
# 5261 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR1 equ 0FCEh ;# 
# 5267 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR1L equ 0FCEh ;# 
# 5273 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR1H equ 0FCFh ;# 
# 5279 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
RCON equ 0FD0h ;# 
# 5411 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
WDTCON equ 0FD1h ;# 
# 5438 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
HLVDCON equ 0FD2h ;# 
# 5443 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
LVDCON equ 0FD2h ;# 
# 5707 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
OSCCON equ 0FD3h ;# 
# 5783 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
T0CON equ 0FD5h ;# 
# 5859 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR0 equ 0FD6h ;# 
# 5865 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR0L equ 0FD6h ;# 
# 5871 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TMR0H equ 0FD7h ;# 
# 5877 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
STATUS equ 0FD8h ;# 
# 5947 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR2 equ 0FD9h ;# 
# 5953 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR2L equ 0FD9h ;# 
# 5959 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR2H equ 0FDAh ;# 
# 5965 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PLUSW2 equ 0FDBh ;# 
# 5971 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PREINC2 equ 0FDCh ;# 
# 5977 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
POSTDEC2 equ 0FDDh ;# 
# 5983 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
POSTINC2 equ 0FDEh ;# 
# 5989 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
INDF2 equ 0FDFh ;# 
# 5995 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
BSR equ 0FE0h ;# 
# 6001 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR1 equ 0FE1h ;# 
# 6007 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR1L equ 0FE1h ;# 
# 6013 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR1H equ 0FE2h ;# 
# 6019 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PLUSW1 equ 0FE3h ;# 
# 6025 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PREINC1 equ 0FE4h ;# 
# 6031 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
POSTDEC1 equ 0FE5h ;# 
# 6037 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
POSTINC1 equ 0FE6h ;# 
# 6043 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
INDF1 equ 0FE7h ;# 
# 6049 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
WREG equ 0FE8h ;# 
# 6060 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR0 equ 0FE9h ;# 
# 6066 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR0L equ 0FE9h ;# 
# 6072 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
FSR0H equ 0FEAh ;# 
# 6078 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PLUSW0 equ 0FEBh ;# 
# 6084 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PREINC0 equ 0FECh ;# 
# 6090 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
POSTDEC0 equ 0FEDh ;# 
# 6096 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
POSTINC0 equ 0FEEh ;# 
# 6102 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
INDF0 equ 0FEFh ;# 
# 6108 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
INTCON3 equ 0FF0h ;# 
# 6199 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
INTCON2 equ 0FF1h ;# 
# 6268 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
INTCON equ 0FF2h ;# 
# 6384 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PROD equ 0FF3h ;# 
# 6390 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PRODL equ 0FF3h ;# 
# 6396 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PRODH equ 0FF4h ;# 
# 6402 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TABLAT equ 0FF5h ;# 
# 6410 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TBLPTR equ 0FF6h ;# 
# 6416 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TBLPTRL equ 0FF6h ;# 
# 6422 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TBLPTRH equ 0FF7h ;# 
# 6428 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TBLPTRU equ 0FF8h ;# 
# 6436 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PCLAT equ 0FF9h ;# 
# 6443 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PC equ 0FF9h ;# 
# 6449 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PCL equ 0FF9h ;# 
# 6455 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PCLATH equ 0FFAh ;# 
# 6461 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
PCLATU equ 0FFBh ;# 
# 6467 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
STKPTR equ 0FFCh ;# 
# 6572 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TOS equ 0FFDh ;# 
# 6578 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TOSL equ 0FFDh ;# 
# 6584 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TOSH equ 0FFEh ;# 
# 6590 "D:\Program Files (x86)\Microchip\xc8\v1.40\include\pic18f4620.h"
TOSU equ 0FFFh ;# 
	FNCALL	_main,_InitSystem
	FNROOT	_main
	global	_ADCON0
_ADCON0	set	0xFC2
	global	_ADCON1
_ADCON1	set	0xFC1
	global	_OSCCONbits
_OSCCONbits	set	0xFD3
	global	_PORTB
_PORTB	set	0xF81
	global	_TRISB
_TRISB	set	0xF93
; #config settings
global __CFG_OSC$INTIO67
__CFG_OSC$INTIO67 equ 0x0
global __CFG_FCMEN$OFF
__CFG_FCMEN$OFF equ 0x0
global __CFG_IESO$OFF
__CFG_IESO$OFF equ 0x0
global __CFG_PWRT$OFF
__CFG_PWRT$OFF equ 0x0
global __CFG_BOREN$SBORDIS
__CFG_BOREN$SBORDIS equ 0x0
global __CFG_BORV$3
__CFG_BORV$3 equ 0x0
global __CFG_WDT$ON
__CFG_WDT$ON equ 0x0
global __CFG_WDTPS$32768
__CFG_WDTPS$32768 equ 0x0
global __CFG_CCP2MX$PORTC
__CFG_CCP2MX$PORTC equ 0x0
global __CFG_PBADEN$ON
__CFG_PBADEN$ON equ 0x0
global __CFG_LPT1OSC$OFF
__CFG_LPT1OSC$OFF equ 0x0
global __CFG_MCLRE$ON
__CFG_MCLRE$ON equ 0x0
global __CFG_STVREN$ON
__CFG_STVREN$ON equ 0x0
global __CFG_LVP$OFF
__CFG_LVP$OFF equ 0x0
global __CFG_XINST$OFF
__CFG_XINST$OFF equ 0x0
global __CFG_CP0$OFF
__CFG_CP0$OFF equ 0x0
global __CFG_CP1$OFF
__CFG_CP1$OFF equ 0x0
global __CFG_CP2$OFF
__CFG_CP2$OFF equ 0x0
global __CFG_CP3$OFF
__CFG_CP3$OFF equ 0x0
global __CFG_CPB$OFF
__CFG_CPB$OFF equ 0x0
global __CFG_CPD$OFF
__CFG_CPD$OFF equ 0x0
global __CFG_WRT0$OFF
__CFG_WRT0$OFF equ 0x0
global __CFG_WRT1$OFF
__CFG_WRT1$OFF equ 0x0
global __CFG_WRT2$OFF
__CFG_WRT2$OFF equ 0x0
global __CFG_WRT3$OFF
__CFG_WRT3$OFF equ 0x0
global __CFG_WRTC$OFF
__CFG_WRTC$OFF equ 0x0
global __CFG_WRTB$OFF
__CFG_WRTB$OFF equ 0x0
global __CFG_WRTD$OFF
__CFG_WRTD$OFF equ 0x0
global __CFG_EBTR0$OFF
__CFG_EBTR0$OFF equ 0x0
global __CFG_EBTR1$OFF
__CFG_EBTR1$OFF equ 0x0
global __CFG_EBTR2$OFF
__CFG_EBTR2$OFF equ 0x0
global __CFG_EBTR3$OFF
__CFG_EBTR3$OFF equ 0x0
global __CFG_EBTRB$OFF
__CFG_EBTRB$OFF equ 0x0
	file	"dist/Default/production\Lab2-Solution.X.production.as"
	line	#
psect	cinit,class=CODE,delta=1,reloc=2
global __pcinit
__pcinit:
global start_initialization
start_initialization:

global __initialization
__initialization:
psect cinit,class=CODE,delta=1
global end_of_initialization,__end_of__initialization

;End of C runtime variable initialization code

end_of_initialization:
__end_of__initialization:
movlb 0
goto _main	;jump to C main() function
psect	cstackCOMRAM,class=COMRAM,space=1,noexec
global __pcstackCOMRAM
__pcstackCOMRAM:
?_InitSystem:	; 1 bytes @ 0x0
??_InitSystem:	; 1 bytes @ 0x0
??_main:	; 1 bytes @ 0x0
?_main:	; 2 bytes @ 0x0
	ds   2
;!
;!Data Sizes:
;!    Strings     0
;!    Constant    0
;!    Data        0
;!    BSS         0
;!    Persistent  0
;!    Stack       0
;!
;!Auto Spaces:
;!    Space          Size  Autos    Used
;!    COMRAM          127      2       2
;!    BANK0           128      0       0
;!    BANK1           256      0       0
;!    BANK2           256      0       0
;!    BANK3           256      0       0
;!    BANK4           256      0       0
;!    BANK5           256      0       0
;!    BANK6           256      0       0
;!    BANK7           256      0       0
;!    BANK8           256      0       0
;!    BANK9           256      0       0
;!    BANK10          256      0       0
;!    BANK11          256      0       0
;!    BANK12          256      0       0
;!    BANK13          256      0       0
;!    BANK14          256      0       0
;!    BANK15          128      0       0

;!
;!Pointer List with Targets:
;!
;!    None.


;!
;!Critical Paths under _main in COMRAM
;!
;!    None.
;!
;!Critical Paths under _main in BANK0
;!
;!    None.
;!
;!Critical Paths under _main in BANK1
;!
;!    None.
;!
;!Critical Paths under _main in BANK2
;!
;!    None.
;!
;!Critical Paths under _main in BANK3
;!
;!    None.
;!
;!Critical Paths under _main in BANK4
;!
;!    None.
;!
;!Critical Paths under _main in BANK5
;!
;!    None.
;!
;!Critical Paths under _main in BANK6
;!
;!    None.
;!
;!Critical Paths under _main in BANK7
;!
;!    None.
;!
;!Critical Paths under _main in BANK8
;!
;!    None.
;!
;!Critical Paths under _main in BANK9
;!
;!    None.
;!
;!Critical Paths under _main in BANK10
;!
;!    None.
;!
;!Critical Paths under _main in BANK11
;!
;!    None.
;!
;!Critical Paths under _main in BANK12
;!
;!    None.
;!
;!Critical Paths under _main in BANK13
;!
;!    None.
;!
;!Critical Paths under _main in BANK14
;!
;!    None.
;!
;!Critical Paths under _main in BANK15
;!
;!    None.

;;
;;Main: autosize = 0, tempsize = 2, incstack = 0, save=0
;;

;!
;!Call Graph Tables:
;!
;! ---------------------------------------------------------------------------------
;! (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;! ---------------------------------------------------------------------------------
;! (0) _main                                                 2     2      0       0
;!                                              0 COMRAM     2     2      0
;!                         _InitSystem
;! ---------------------------------------------------------------------------------
;! (1) _InitSystem                                           0     0      0       0
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 1
;! ---------------------------------------------------------------------------------
;!
;! Call Graph Graphs:
;!
;! _main (ROOT)
;!   _InitSystem
;!

;! Address spaces:

;!Name               Size   Autos  Total    Cost      Usage
;!BITCOMRAM           7F      0       0       0        0.0%
;!EEDATA             400      0       0       0        0.0%
;!NULL                 0      0       0       0        0.0%
;!CODE                 0      0       0       0        0.0%
;!COMRAM              7F      2       2       1        1.6%
;!STACK                0      0       0       2        0.0%
;!DATA                 0      0       0       3        0.0%
;!BITBANK0            80      0       0       4        0.0%
;!BANK0               80      0       0       5        0.0%
;!BITBANK1           100      0       0       6        0.0%
;!BANK1              100      0       0       7        0.0%
;!BITBANK2           100      0       0       8        0.0%
;!BANK2              100      0       0       9        0.0%
;!BITBANK3           100      0       0      10        0.0%
;!BANK3              100      0       0      11        0.0%
;!BITBANK4           100      0       0      12        0.0%
;!BANK4              100      0       0      13        0.0%
;!BITBANK5           100      0       0      14        0.0%
;!BANK5              100      0       0      15        0.0%
;!BITBANK6           100      0       0      16        0.0%
;!BANK6              100      0       0      17        0.0%
;!BITBANK7           100      0       0      18        0.0%
;!BANK7              100      0       0      19        0.0%
;!BITBANK8           100      0       0      20        0.0%
;!BANK8              100      0       0      21        0.0%
;!BITBANK9           100      0       0      22        0.0%
;!BANK9              100      0       0      23        0.0%
;!BITBANK10          100      0       0      24        0.0%
;!BANK10             100      0       0      25        0.0%
;!BITBANK11          100      0       0      26        0.0%
;!BANK11             100      0       0      27        0.0%
;!BITBANK12          100      0       0      28        0.0%
;!BANK12             100      0       0      29        0.0%
;!BITBANK13          100      0       0      30        0.0%
;!BANK13             100      0       0      31        0.0%
;!BITBANK14          100      0       0      32        0.0%
;!BANK14             100      0       0      33        0.0%
;!ABS                  0      0       0      34        0.0%
;!BITBANK15           80      0       0      35        0.0%
;!BANK15              80      0       0      36        0.0%
;!BIGRAM             F7F      0       0      37        0.0%
;!BITSFR               0      0       0     200        0.0%
;!SFR                  0      0       0     200        0.0%

	global	_main

;; *************** function _main *****************
;; Defined at:
;;		line 5 in file "SRC/Lab2-Solution.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  2   16[None  ] int 
;; Registers used:
;;		wreg, status,2, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14  BANK15
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_InitSystem
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	text0,class=CODE,space=0,reloc=2
	file	"SRC/Lab2-Solution.c"
	line	5
global __ptext0
__ptext0:
psect	text0
	file	"SRC/Lab2-Solution.c"
	line	5
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:
;incstack = 0
	opt	stack 30
	line	7
	
l623:
;Lab2-Solution.c: 7: OSCCONbits.IRCF = 0b110;
	movf	((c:4051)),c,w	;volatile
	andlw	not (((1<<3)-1)<<4)
	iorlw	(06h & ((1<<3)-1))<<4
	movwf	((c:4051)),c	;volatile
	line	8
;Lab2-Solution.c: 8: ADCON0 = 0x00;
	movlw	low(0)
	movwf	((c:4034)),c	;volatile
	line	9
	
l625:
;Lab2-Solution.c: 9: ADCON1 = 0xFF;
	setf	((c:4033)),c	;volatile
	line	10
	
l627:
;Lab2-Solution.c: 10: InitSystem();
	call	_InitSystem	;wreg free
	goto	l629
	line	11
;Lab2-Solution.c: 11: while(1)
	
l17:
	line	13
	
l629:
;Lab2-Solution.c: 12: {
;Lab2-Solution.c: 13: PORTB=0x0F;
	movlw	low(0Fh)
	movwf	((c:3969)),c	;volatile
	line	14
	
l631:
;Lab2-Solution.c: 14: _delay((unsigned long)((500)*(4000000L/4000.0)));
	opt asmopt_push
opt asmopt_off
movlw  3
movwf	(??_main+0+0+1)&0ffh,c,f
movlw	138
movwf	(??_main+0+0)&0ffh,c,f
	movlw	86
u17:
decfsz	wreg,f
	bra	u17
	decfsz	(??_main+0+0)&0ffh,c,f
	bra	u17
	decfsz	(??_main+0+0+1)&0ffh,c,f
	bra	u17
opt asmopt_pop

	line	15
	
l633:
;Lab2-Solution.c: 15: PORTB=0x00;
	movlw	low(0)
	movwf	((c:3969)),c	;volatile
	line	16
	
l635:
;Lab2-Solution.c: 16: _delay((unsigned long)((500)*(4000000L/4000.0)));
	opt asmopt_push
opt asmopt_off
movlw  3
movwf	(??_main+0+0+1)&0ffh,c,f
movlw	138
movwf	(??_main+0+0)&0ffh,c,f
	movlw	86
u27:
decfsz	wreg,f
	bra	u27
	decfsz	(??_main+0+0)&0ffh,c,f
	bra	u27
	decfsz	(??_main+0+0+1)&0ffh,c,f
	bra	u27
opt asmopt_pop

	goto	l629
	line	17
	
l18:
	line	11
	goto	l629
	
l19:
	line	18
	
l20:
	global	start
	goto	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
	signat	_main,90
	global	_InitSystem

;; *************** function _InitSystem *****************
;; Defined at:
;;		line 19 in file "SRC/Lab2-Solution.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13  BANK14  BANK15
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1,class=CODE,space=0,reloc=2
	line	19
global __ptext1
__ptext1:
psect	text1
	file	"SRC/Lab2-Solution.c"
	line	19
	global	__size_of_InitSystem
	__size_of_InitSystem	equ	__end_of_InitSystem-_InitSystem
	
_InitSystem:
;incstack = 0
	opt	stack 30
	line	21
	
l621:
;Lab2-Solution.c: 21: PORTB = 0x00;
	movlw	low(0)
	movwf	((c:3969)),c	;volatile
	line	22
;Lab2-Solution.c: 22: TRISB = 0xF0;
	movlw	low(0F0h)
	movwf	((c:3987)),c	;volatile
	line	23
	
l23:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_InitSystem
	__end_of_InitSystem:
	signat	_InitSystem,89
	GLOBAL	__activetblptr
__activetblptr	EQU	0
	psect	intsave_regs,class=BIGRAM,space=1,noexec
	PSECT	rparam,class=COMRAM,space=1,noexec
	GLOBAL	__Lrparam
	FNCONF	rparam,??,?
	GLOBAL	___rparam_used
	___rparam_used EQU 1
	GLOBAL	___param_bank
	___param_bank EQU 0
GLOBAL	__Lparam, __Hparam
GLOBAL	__Lrparam, __Hrparam
__Lparam	EQU	__Lrparam
__Hparam	EQU	__Hrparam
	end

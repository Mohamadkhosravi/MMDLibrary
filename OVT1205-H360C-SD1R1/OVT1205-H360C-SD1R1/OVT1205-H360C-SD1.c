// Title:     OVT1205SD1 code
// Date:      1401/06/20
// Developer: Mehdi Bolourian
// Copyright: Deno Electronic

// Change the MODEL number to choose the appropriate model

#include "BS66f360C.h"
#include "BS66f360_LIBV413\BS66f360_LIBV413.CEX"
#include "stdint.h"
#include "math.h"

#define VERSION				1
#define MODEL				1

#define ELEMENT_TOP			_pe1
#define ELEMENT_BOTTOM		_pe2
#define MOTOR_CHICKEN		_pe0
#define FAN_CONVECTION		_pe3
#define LAMP				_pd7

#define ELEMENT_TOP_C		_pec1
#define ELEMENT_BOTTOM_C	_pec2
#define MOTOR_CHICKEN_C		_pec0
#define FAN_CONVECTION_C	_pec3
#define LAMP_C				_pdc7

#define COM1				_pe7
#define COM2				_pf0
#define COM3				_pf1
#define COM4				_pf2

#define COM1_C				_pec7
#define COM2_C				_pfc0
#define COM3_C				_pfc1
#define COM4_C				_pfc2

#define	SEGA				_pf3
#define	SEGB				_pf5
#define	SEGC				_pa7
#define	SEGD				_pa6
#define	SEGE				_pa5
#define	SEGF				_pa1
#define	SEGG				_pa2
#define	SEG_ICON			_pa0
#define	SEG_ICON2			_pe5

#define	SEGA_C				_pfc3
#define	SEGB_C				_pfc5
#define	SEGC_C				_pac7
#define	SEGD_C				_pac6
#define	SEGE_C				_pac5
#define	SEGF_C				_pac1
#define	SEGG_C				_pac2
#define	SEG_ICON_C			_pac0
#define	SEG_ICON2_C			_pec5

#define	LED_DATA1			_pc4
#define	LED_DATA2			_pb2
#define	LED_DATA3			_pc5

#define	LED_DATA1_C			_pcc4
#define	LED_DATA2_C			_pbc2
#define	LED_DATA3_C			_pcc5

#define	LED_COM1			_pc7
#define	LED_COM2			_pb3
#define	LED_COM3			_pc6

#define	LED_COM1_C			_pcc7
#define	LED_COM2_C			_pbc3
#define	LED_COM3_C			_pcc6

#define PIN_SHARED_TIMER			_pes14  // PE7(CTP1B) as CTM Output
#define LOW_BYTE_REGISTER_TIMER		_ctm1al // CTM CCRA low byte
#define HIGH_BYTE_REGISTER_TIMER	_ctm1ah // CTM CCRA high byte

#define MUL(A,B)		      	    (A*B)
#define TIMERREGL(PS, FSYS, FRO)	((FSYS/PS/FRO) & 0x00ff)
#define TIMERREGH(PS, FSYS, FRO)	((FSYS/PS/FRO) & 0xff00)>>8

#define OFF							0
#define BUZ_BEEP					1
#define BUZ_ERROR					2
#define BUZ_ALARM					3
#define BUZ_CONNECT					4
#define BUZ_PREHEAT					5
#define TEMPERATURE_SAMPLE_COUNT	5
#define MAIN_TIMER_FREQUENCY		4000
#define BUZZER_INITIAL_FREQUENCY	8000

#define VALUE_1KHZ			0xFA
#define VALUE_2KHZ			0x7D
#define VALUE_3KHZ			0x53
#define VALUE_4KHZ			0x3F
#define VALUE_5KHZ			0x32
#define VALUE_6KHZ			0x2A
#define VALUE_7KHZ			0x23
#define VALUE_8KHZ			0x1F
#define VALUE_9KHZ			0x1C
#define VALUE_10KHZ			0x19
#define VALUE_11KHZ			0x16
#define VALUE_12KHZ			0x14

#define VALUE_SENCOND_10_0	40000
#define VALUE_SENCOND_20_0	80000
#define VALUE_SENCOND_25_0	100000
#define VALUE_SENCOND_30_0	120000
#define VALUE_SENCOND_35_0	140000
#define VALUE_SENCOND_36_0	144000
#define VALUE_SENCOND_37_0	148000
#define VALUE_SENCOND_38_0	152000
#define VALUE_SENCOND_39_0	156000
#define VALUE_SENCOND_40_0	160000

#define VALUE_SENCOND_1_0	4000
#define VALUE_SENCOND_2_0	8000
#define VALUE_SENCOND_3_0	12000
#define VALUE_SENCOND_4_0	16000
#define VALUE_SENCOND_5_0	20000

#define VALUE_SENCOND_0_5	2000
#define VALUE_SENCOND_1_5	6000
#define VALUE_SENCOND_2_5	10000
#define VALUE_SENCOND_3_5	14000
#define VALUE_SENCOND_4_5	18000

#define	PROGRAM_SELECTED	1
#define	SET_TIME			3
#define	SET_TEMP			4
#define SET_CLOCK			5

#define PIZZA				1
#define CHICKEN				2
#define CAKE				3
#define DEFROST				4
#define TOP_HEAT			5
#define BOTTOM_HEAT			6
#define BOTH_HEAT			7
#define ELEMENTS			8
#define EQUIPMENT			9

#define TIME				1
#define TEMP				2

#define T_25				298.15 // 25 degrees celsius in terms of kelvin unit
#define T_0					273.15 // 0 degrees celsius in terms of kelvin unit
#define R_PU				4700.0 // Pull-up resistor of NTC100k sensor
#define R_PD				100.0 // Pull-down resistor of NTC100k sensor
#define B					4261.0 // Beta value for the NTC100k ( log(Rt1/Rt2)/(1/T1-1/T2) ) based on the values of the datasheet document
#define ADC_MAX_VALUE		4095.0 // Maximum value of adc output (4095 in case of 12-bit ADC)
#define R_NTC_25			100000.0 // NTC resistance in the temperature of 25 degrees celcius

#define KEY_THRESHOLD		5000

///////////////////// bit ///////////////////
 // General
uint8_t f_show_version; // Initial in USER_PROGRAM_INITIAL()
uint8_t f_show_brand;
uint8_t	f_element;
uint8_t f_controller_init;
uint8_t f_power;
uint8_t f_standby;
uint8_t f_standby_hold;
uint8_t f_start;
uint8_t f_finish_cooking;
uint8_t f_preheat_enable;
uint8_t f_preheat_alarm;
uint8_t f_blink_state;
uint8_t f_blink_colon;
uint8_t f_startup_temperature;
uint8_t f_element_top;
uint8_t f_element_bottom;
uint8_t f_fan_convection;
uint8_t f_motor_chicken;
 // Display
uint8_t f_icon_colon;
uint8_t f_icon_Degree_Celsius;
uint8_t f_icon_lock;
uint8_t f_icon_cook;
uint8_t f_icon_auto;
uint8_t f_icon_p;
uint8_t f_icon_finish_cooking;
uint8_t f_all_leds_on;
uint8_t f_colon_show;
uint16_t f_cook_show;
 // Key
uint8_t f_key_press;
uint8_t f_lock;
 // Buzzer
uint8_t f_buzzer;
 // Test
uint8_t f_test;
uint8_t f_test_deno;
uint8_t f_relay_test;
uint8_t f_key_test;
uint8_t f_icon_test;
 // XTAL
uint8_t	f_xtal_failure;
uint8_t	f_xtal_show_status;
 // LED
uint8_t f_led_ele_top;
uint8_t f_led_ele_bot;
uint8_t f_led_motor;
uint8_t f_led_pizza;
uint8_t f_led_chicken;
uint8_t f_led_cake;
uint8_t f_led_defrost;
uint8_t f_led_start;
//////////////////////////////////////////////////

 // General
uint8_t		cook_mode;
uint8_t		user_index;
uint16_t	counter_power_off;
uint8_t		count_zero;
uint8_t 	setting_mode;
uint8_t		counter_setting;
 // ERROR
uint8_t		error_number;
 // Temperature
uint16_t	counter_read_temperature;
uint8_t		cook_temperature_set;
uint16_t	caviti_temperature;
double		K1;
double		K2;
double		K3;
double		K4;
 // Buzzer
uint8_t		buzzer;
uint16_t	counter_buzzer;
 // Display
//uint16_t	counter_preshow;
uint8_t		value_segment[5];
uint16_t	counter_show_version;
uint16_t	counter_show_brand;
uint16_t	counter_blink;
uint16_t	counter_blink_colon;
uint16_t	counter_icon_fan;
uint8_t		segment_on;
uint8_t		display_time_temp;
uint8_t		counter_show_time_temp;
uint16_t	counter_cook_show;
uint8_t		counter_set_time;
 // Time
uint8_t		clock_hour;
uint8_t		clock_minute;
uint8_t		clock_second;
uint8_t		cook_second_set;
uint8_t		preheat_time_minute;
uint8_t		preheat_time_second;
uint16_t	cook_minute_set;
 // Key
uint16_t	counter_key_press;
uint8_t		counter_key_release;
uint16_t	speed_key;
 // XTAL
uint16_t	counter_xtal_verify;
 // Test
uint32_t	counter_test;
uint32_t	counter_test_deno;

//	elements_equipment:
//	f_element_top		// Bit 1
//	f_element_bottom	// Bit 2
//	f_fan				// Bit 3
//	f_motor				// Bit 4
struct user{
	uint8_t elements_equipment;
	uint8_t temperature;
	uint8_t minute;
}program_user[21];

/* Function prototypes */
extern void USER_PROGRAM_INITIAL(void); // Initializing peripherals and non-zero variables
extern void USER_PROGRAM		(void); // Main program loop provided by the Touch library (Must have no blocking section)
void variable_init				(void);
void make_segment_data			(void); // Making the data and flags for the 7-segment
void refresh_segment			(void); // Refreshing 1 multiplexed 4-digit 7-segment
void make_led_flags             (void);
void refresh_led                (void);
void make_sound					(void);
void cook_run					(void); // Setting the flags of the corresponding Elements for the cook program
void ending_handle				(void); // End of coocking handle function
void reset						(void); // Reset function after pressing start/stop key
void error_handle				(void); // Handle function after an error is occurred
void program_test				(void);
void program_test_deno			(void);
void temperature_calculation	(void);	// Calculating the corresponding  temperature for a given adc value
uint8_t data_segment			(uint8_t value); // Generating and assigning values of 7-segment data to GPIOs
uint16_t read_adc				(void); // Reading ADC and returning the converted value of the selected input
uint8_t controller				(int16_t set_point, int16_t process_value, int16_t Tu, int16_t Tl, int16_t Ad_i, int16_t Ad_d, int16_t SAMPLE_COUNT, uint8_t init); // Controlling the temperature
uint8_t temperature_predictor	(uint8_t temperature); // Prediciting the temperature of the oven center point
/***********************/
void __attribute((interrupt(0x14))) CTM0AInterrupt	(void);	// Refreshing 7-segment & LED Key
void __attribute((interrupt(0x28))) TB1Interrupt	(void);	// Timebase1 for generating 1 second
/***********************/

void USER_PROGRAM_INITIAL(void)
{
 	/**************** HXT setup *****************/
	// High frequency Internal RC configuration
	_hircen	= 1; // Enabling Internal RC
	_hxten	= 0; // Disabling External XTAL
	_fhs	= 1; // Choosing HIRC in the corresponding  Multiplexer
	// Choosing Fh as Fsys (System Frequency)
	_cks0	= 0;
	_cks1	= 0;
	_cks2	= 0;
	
	// 16MHz Internal RC
	_hirc0	= 0;
	_hirc1	= 1;

 	/****************  LXT setup *****************/
 	//External 32768Hz Crystal Oscillator
	_pas06	= 0; // XT1
	_pas07	= 1;
	_pas10	= 0; // XT2
	_pas11	= 1;
	
	_lxtsp	= 1; // LXT Quick Start control : Enable – Quick Start
	_lxten	= 1; // LXT oscillator enable control : Enable
	_fss	= 1; // Low frequency clock selection : LXT
	// Fsub => LXT (External 32.768kHz. Crystal)

 	/**************** PORT setup *****************/
	/* Initialization of GPIOs */
	/* GPIO settings (0: Output, 1: Input)*/
	ELEMENT_BOTTOM_C	= 0;
	ELEMENT_TOP_C		= 0;
	MOTOR_CHICKEN_C		= 0;
	FAN_CONVECTION_C	= 0;
	LAMP_C				= 0;
	LED_DATA1_C			= 0;
	LED_DATA2_C			= 0;
	LED_DATA3_C			= 0;
	LED_COM1_C			= 0;
	LED_COM2_C			= 0;
	LED_COM3_C			= 0;
	
	ELEMENT_BOTTOM		= 0;
	ELEMENT_TOP			= 0;
	MOTOR_CHICKEN		= 0;
	FAN_CONVECTION		= 0;
	LAMP				= 0;
	LED_DATA1			= 0;
	LED_DATA2			= 0;
	LED_DATA3			= 0;
	LED_COM1			= 0;
	LED_COM2			= 0;
	LED_COM3			= 0;
	
	COM1_C	= 0;
	COM2_C	= 0;
	COM3_C	= 0;
	COM4_C	= 0;
	
	SEGA_C	= 0;
	SEGB_C 	= 0;
	SEGC_C	= 0;
	SEGD_C	= 0;
	SEGE_C	= 0;
	SEGF_C	= 0;
	SEGG_C	= 0;
	SEG_ICON_C	= 0;
	SEG_ICON2_C = 0;
		
	SEGA	= 0;
	SEGB	= 0;
	SEGC	= 0;
	SEGD	= 0;
	SEGE	= 0;
	SEGF	= 0;
	SEGG	= 0;
	SEG_ICON	= 0;
	SEG_ICON2	= 0;
	
	COM1	= 1;
	COM2	= 1;
	COM3	= 1;
	COM4	= 1;
	
	_sledc = 0xff;
	_pans  = 0xff;
	_pfns  = 0xff;
	_pens  = 0xff;

 	/**************** Timer module TM setup *****************/
 	/* Timer CTM0 settings */
	// CTnRP2~CTnRP0: CTMn CCRP 3-bit register, compared with the CTMn Counter : 000: 1024 CTMn clocks
	// CTnCK2~CTnCK0: Select CTMn Counter clock : 000: fSYS/4
	_ct0m0   = 1;
	_ct0m1   = 1;
	_ct0cclr = 1;
	_ctm0al  = TIMERREGL(4, 16000000, MAIN_TIMER_FREQUENCY);
	_ctm0ah  = TIMERREGH(4, 16000000, MAIN_TIMER_FREQUENCY);
	_ct0on	 = 1;//	CTnON: //CTM0 Counter On/Off Control : 1: On
	_ct0pau  = 0;
	/*****************************************/
	
 	/* Timer CTM1 settings */ // Buzzer
	_ct1ck0		= 1; // CTM counter clock as fH/64 // fH(16MHz)/64 = 250 KHz
	_ct1ck1		= 1; // CTM counter clock as fH/64
	_ct1ck2		= 0; // CTM counter clock as fH/64
	_ct1m0		= 0; // Compare match output mode
	_ct1m1		= 0; // Compare match output mode
	_ct1io0		= 1; // Compare match toggle output
	_ct1io1		= 1; // Compare match toggle output
	_ct1oc		= 0; // Initial Low for the Counter output
	_ct1pol		= 0; // Non-inverted polarity
	_ct1cclr	= 1; // Selecting comparator A match
	_ctm1dl		= TIMERREGL(64, 16000000, BUZZER_INITIAL_FREQUENCY); //0x32; // CTM CCRA low byte
	_ctm1dh		= TIMERREGH(64, 16000000, BUZZER_INITIAL_FREQUENCY); //0x00; // CTM CCRA high byte
	_ctm1al		= TIMERREGL(64, 16000000, BUZZER_INITIAL_FREQUENCY); //0x32; // CTM CCRA low byte // 250K / 50Clock = 5KHz
	_ctm1ah		= TIMERREGH(64, 16000000, BUZZER_INITIAL_FREQUENCY); //0x00; // CTM CCRA high byte
	_ct1on		= 1; // Enabling CTM Counter
	_ct1pau		= 0; // Running the Counter
	PIN_SHARED_TIMER		= 1; // PE6(CTP1) as CTM Output
	_pes16		= 0; // PE7(CTP1B) as CTM Output
	_pes17		= 0; // PE7(CTP1B) as CTM Output
	
 	/**************** Time Base Interrupt setup *****************/
	// Time base1 for 1 second delay
	_clksel10	= 0;  // Prescaler 1 clock source selection : fSUB
	_clksel11	= 1;  // Prescaler 1 clock source selection : fSUB
	_tb1on		= 1;  // Time Base 1 Control                : Enable 
	_tb10		= 1;  // Select Time Base 1 Time-out Period : 2^15/fPSC1
	_tb11		= 1;  // Select Time Base 1 Time-out Period : 2^15/fPSC1
	_tb12		= 1;  // Select Time Base 1 Time-out Period : 2^15/fPSC1

 	/**************** ADC module setup *****************/
	_pbs03	= 1;
	_pbs02	= 1; // PB1(AN1) as ADC
	_sacks2	= 0;
	_sacks1	= 0;
	_sacks0	= 1; // A/D converter clock source selection // 001: fSYS/2		
	_sains0	= 0;
	_sains1	= 0;
	_sains2	= 0; // A/D converter input signal selection : External source – External analog channel intput, ANn
	_sacs3	= 0;
	_sacs2	= 0;
	_sacs1	= 0;
	_sacs0	= 1; // 0001: External AN1 input
	_savrs1	= 0;
	_savrs0	= 1; // A/D converter reference voltage selection // 01: Internal A/D converter power, VDD
	_adrfs	= 1; // A/D converter data format: 1 ? SADOH=D[11:8]; SADOL=D[7:0]
	_ade	= 0; // A/D Converter interrupt control: DISABLE interrupt ADC
	_adcen	= 1; // A/D Converter function enable control // 1: Enable	

	/*********************** Initialising ************************/
	// Initialising the controller
	f_controller_init = 1;
	
	// Time
	clock_hour = 12;
	//cook_minute_set		= 90;
	preheat_time_minute	= 12;
	setting_mode = SET_CLOCK;

	// Key
	counter_key_release	= 30;
	
	// Display 
	f_show_version = 1;
	value_segment[1] = 10;
	value_segment[2] = 10;
	value_segment[3] = 10;
	value_segment[4] = 10;

	// Temperature
	caviti_temperature		= 25;
	cook_temperature_set	= 200;
	K1 = T_25*B;
	K2 = ADC_MAX_VALUE*R_PD;
	K3 = B - T_25*log(R_NTC_25);
	K4 = R_PU+R_PD;
	
	display_time_temp = 1;
	/***********************/
	
 	/* Interrupt settings */
	_mf0e	= 1; // Multi-function 0 interrupt control // INTC1 --> bit1 // 1: Enable
	_ctm0ae	= 1; // CTM0 Comparator P match Interrupt control // 1: Enable
	_ctm0af = 0; // CTM0 Comparator P match Interrupt request flag // 0: No request
	_tb1e	= 1; // Time Base 1 interrupt control		: Enable
	_tb1f	= 0; // Time Base 1 interrupt request flag	: No request
	_emi	= 1; // Global interrupt control : Enable
	/**********************/
	
	buzzer	= BUZ_CONNECT;
	temperature_calculation();
}

void USER_PROGRAM(void)
{
	// KEY_DATA[0] = 0x(8-5)(4-1);
	// KEY_DATA[1] = 0x(16-13)(12-9);
	// KEY_DATA[2] = 0x(24-21)(20-17);
	// KEY_DATA[3] = 0x()(28-25);
	// (Power = 20)(Program = 19)(P1-20 = 18)(Element = 17)(Fan/Motor = 16)(Start = 15)(Temp + = 14)(Temp - = 12)(Time - = 11)(Time + = 10)
	
	//////////////////////////////////////////// (( no Key & any Key )) ////////////////////////////////////////////
	if(!KEY_DATA[0] && !KEY_DATA[1] && !KEY_DATA[2]) { // no Key
		f_key_press			= 0;
		f_buzzer			= 0;
		counter_key_press	= 0;
		speed_key			= 1600;
	}
	else if(!error_number && !f_key_press) { // any Key
		counter_key_release	= 0;
		f_standby_hold    	= 0;
		counter_power_off	= 0;
		if(!f_buzzer) {
			buzzer = BUZ_BEEP;
			f_buzzer = 1;
			f_all_leds_on = 0;
		}
		
		if(f_test)
			reset();
		if(f_finish_cooking) {
			reset();
			f_finish_cooking	= 0;
			cook_mode           = 0;
			f_key_press			= 1;
			//buzzer				= BUZ_BEEP;
			counter_buzzer		= 0;
			setting_mode		= OFF;
			f_buzzer		= 1;
		}	
		if(!f_buzzer && (f_power || (KEY_DATA[0] == 0x40 && KEY_DATA[2] == 0x01 && !KEY_DATA[1])/*Lock*/) ) {
			counter_buzzer	= 0;
			//buzzer			= BUZ_BEEP;
			f_buzzer		= 1;
		}
		if(!f_power && !f_show_brand && !f_show_version && ((!KEY_DATA[0] && KEY_DATA[1] == 0x20 && !KEY_DATA[2]) || (KEY_DATA[0] == 0x01 && !KEY_DATA[1] && !KEY_DATA[2]) || (KEY_DATA[0] == 0x02 && !KEY_DATA[2] && !KEY_DATA[1]))) {
			f_all_leds_on       = 0;
			counter_buzzer	    = 0;
			//buzzer		    	= BUZ_BEEP;
			f_buzzer	    	= 1;
			
			if(setting_mode == OFF) {
				setting_mode     = SET_CLOCK;
				counter_set_time = 0;
			}
		}
	}


	if(!f_standby && !f_test && !f_test_deno) {
		//////////////////////////////////////////// (( TOP element )) //////////////////////////////////////
		if((KEY_DATA[0] == 0x08 && !KEY_DATA[1] && !KEY_DATA[2]) && !f_key_press && !f_finish_cooking && !f_lock && f_power && !f_show_version && !f_show_brand && !error_number) {
			f_key_press		= 1;
			counter_setting	= 0;
			
			if((cook_mode > 4 || !cook_mode) && !f_start && setting_mode != SET_CLOCK) {
				if(cook_mode == BOTTOM_HEAT) {
					cook_mode = BOTH_HEAT;
					f_icon_p  = 1;
				}
				else if(cook_mode == TOP_HEAT) {
					cook_mode = 0;
					f_icon_p  = 0;
					setting_mode = OFF;
				}
				else if(cook_mode == BOTH_HEAT) {
					cook_mode = BOTTOM_HEAT;
					f_icon_p  = 1;
				}
				else {
					cook_mode = TOP_HEAT;
					f_icon_p  = 1;
					cook_minute_set      = 0;
					cook_temperature_set = 120;
					setting_mode = PROGRAM_SELECTED;
				}
				f_icon_auto  = 0;
			}
		}
		//////////////////////////////////////////// (( BOT element )) //////////////////////////////////////
		else if((!KEY_DATA[0] && KEY_DATA[1] == 0x80 && !KEY_DATA[2]) && !f_key_press && !f_finish_cooking && !f_lock && f_power && !f_show_version && !f_show_brand && !error_number) {
			f_key_press		= 1;
			counter_setting	= 0;
			
			if((cook_mode > 4 || !cook_mode) && !f_start && setting_mode != SET_CLOCK) {
				if(cook_mode == BOTTOM_HEAT) {
					cook_mode = 0;
					f_icon_p  = 0;
					setting_mode = OFF;
				}
				else if(cook_mode == TOP_HEAT) {
					cook_mode = BOTH_HEAT;
					f_icon_p  = 1;
				}
				else if(cook_mode == BOTH_HEAT) {
					cook_mode = TOP_HEAT;
					f_icon_p  = 1;
				}
				else {
					cook_mode = BOTTOM_HEAT;
					f_icon_p  = 1;
					cook_minute_set      = 0;
					cook_temperature_set = 120;
					setting_mode = PROGRAM_SELECTED;
				}
			}
		}
		//////////////////////////////////////////// (( PIZZA )) ////////////////////////////////////////////
		else if((!KEY_DATA[0] && !KEY_DATA[1] && KEY_DATA[2] == 0x02) && !f_key_press && !f_finish_cooking && !f_lock && f_power && !f_show_version && !f_show_brand && !error_number) {
			f_key_press		= 1;
			counter_setting	= 0;
			
			if(!f_start && cook_mode != PIZZA && setting_mode != SET_CLOCK) {
				cook_mode            = PIZZA;
				if(setting_mode == OFF)
					setting_mode = PROGRAM_SELECTED;
				cook_minute_set      = 15;
				cook_temperature_set = 200;
				f_icon_auto          = 1;
				f_icon_p             = 0;
				f_motor_chicken      = 0;
			}
			else if(!f_start) {
				cook_mode    = 0;
				setting_mode = OFF;
				f_icon_auto  = 0;
			}
		}
		//////////////////////////////////////////// (( CHICKEN )) //////////////////////////////////////////
		else if((KEY_DATA[0] == 0x04 && !KEY_DATA[1] && !KEY_DATA[2]) && !f_key_press && !f_finish_cooking && !f_lock && f_power && !f_show_version && !f_show_brand && !error_number) {
			f_key_press		= 1;
			counter_setting	= 0;
			
			if(!f_start && cook_mode != CHICKEN && setting_mode != SET_CLOCK) {
				cook_mode            = CHICKEN;
				if(setting_mode == OFF)
					setting_mode = PROGRAM_SELECTED;
				cook_minute_set      = 90;
				cook_temperature_set = 200;
				f_icon_auto          = 1;
				f_icon_p             = 0;
				f_motor_chicken      = 0;
			}
			else if(!f_start) {
				cook_mode    = 0;
				setting_mode = OFF;
				f_motor_chicken = 0;
				f_icon_auto  = 0;
			}
		}
		//////////////////////////////////////////// (( CAKE )) /////////////////////////////////////////////
		else if((!KEY_DATA[0] && !KEY_DATA[1] && KEY_DATA[2] == 0x01) && !f_key_press && !f_finish_cooking && !f_lock && f_power && !f_show_version && !f_show_brand && !error_number) {
			f_key_press		= 1;
			counter_setting	= 0;
			
			if(!f_start && cook_mode != CAKE && setting_mode != SET_CLOCK) {
				cook_mode            = CAKE;
				if(setting_mode == OFF)
					setting_mode = PROGRAM_SELECTED;
				cook_minute_set      = 30;
				cook_temperature_set = 170;
				f_icon_auto          = 1;
				f_icon_p             = 0;
				f_motor_chicken      = 0;
			}
			else if(!f_start) {
				cook_mode    = 0;
				setting_mode = OFF;
				f_icon_auto  = 0;
			}
		}
		//////////////////////////////////////////// (( DEFROST )) //////////////////////////////////////////
		else if((KEY_DATA[0] == 0x40 && !KEY_DATA[1] && !KEY_DATA[2]) && !f_key_press && !f_finish_cooking && !f_lock && f_power && !f_show_version && !f_show_brand && !error_number) {
			f_key_press		= 1;
			counter_setting	= 0;
			
			if(!f_start && cook_mode != DEFROST && setting_mode != SET_CLOCK) {
				cook_mode            = DEFROST;
				if(setting_mode == OFF)
					setting_mode = PROGRAM_SELECTED;
				cook_minute_set      = 240;
				cook_temperature_set = 55;
				f_icon_auto          = 1;
				f_icon_p             = 0;
				f_motor_chicken      = 0;
			}
			else if(!f_start) {
				cook_mode    = 0;
				setting_mode = OFF;
				f_icon_auto  = 0;
			}
		}
		//////////////////////////////////////////// (( Motor )) ////////////////////////////////////////////
		else if((KEY_DATA[0] == 0x80 && !KEY_DATA[1] && !KEY_DATA[2]) && !f_key_press && !f_finish_cooking && !f_lock && f_power && !f_show_version && !f_show_brand && !error_number) {
			f_key_press		= 1;
			counter_setting	= 0;
			
			
			if((cook_mode > 4) || (cook_mode == CHICKEN) || (setting_mode == OFF && f_power && (!cook_mode || (cook_mode > 4) || (cook_mode == CHICKEN)))) {
				f_motor_chicken = !f_motor_chicken;
			}
		}
		//////////////////////////////////////////// (( Start )) ////////////////////////////////////////////
		else if((!KEY_DATA[0] && KEY_DATA[1] == 0x20 && !KEY_DATA[2]) && !f_key_press && !f_finish_cooking && !f_lock && !f_show_version && !f_show_brand && !error_number) {
			f_key_press	= 1;
			f_all_leds_on = 0;
			f_power = 1;
			f_preheat_alarm = 0;
			
			if(f_test) {
				f_test = 0;
				reset();
			}
			
			if(setting_mode == SET_CLOCK || (f_start && !f_preheat_enable))
				setting_mode = OFF;
	
			if((cook_minute_set || cook_second_set) && cook_mode) {
			    if(!f_start && !f_preheat_enable && (cook_mode < 4)) {
					preheat_time_minute	= 12;
					preheat_time_second	= 0;
			    	f_preheat_enable	= 1;
			    	f_start				= 1;
			    	//counter_preshow		= 0;
			    }
			    else if((!f_start && (cook_mode >= 4)) || (f_start && f_preheat_enable)) {
					f_start	    = 1;
					f_cook_show = 1;
					f_preheat_enable = 0;
			    }
			    else {
			    	f_start          = !f_start;
			    	f_cook_show      = !f_cook_show;
			    	f_preheat_enable = 0;
			    	cook_second_set  = 0;
			    	cook_mode				 = 0;
			    	f_motor_chicken  = 0;
			    }
			}
	
		    if(f_start) {
				f_controller_init		= 1;
				display_time_temp		= TIME;
				counter_show_time_temp	= 0;
				setting_mode            = PROGRAM_SELECTED;
				
				if((cook_mode == DEFROST) || f_preheat_enable)
		    		f_fan_convection	= 1;
		    	if(cook_mode == CHICKEN)
		    		f_motor_chicken		= 1;
		    }
		    else if(cook_minute_set || cook_second_set){
		    	reset();
		    	setting_mode = OFF;
		    }
		}
		//////////////////////////////////////////// (( Temp + )) ///////////////////////////////////////////
		else if((!KEY_DATA[0] && !KEY_DATA[1] && KEY_DATA[2] == 0x04) && (cook_mode != 0) && !f_finish_cooking && !f_start && !f_lock && f_power && !f_show_version && !f_show_brand && !error_number) {
			if(!f_key_press || (counter_key_press > speed_key/*MUL(MAIN_TIMER_FREQUENCE,0.7)*/ && !f_standby_hold)) {
				counter_key_press = 0;
				
				if(speed_key > 200)
					speed_key -= 200;
				else
					speed_key = 100;
				
				if(cook_mode) {
					if(setting_mode != SET_TEMP)
						setting_mode = SET_TEMP;
					else {
						if(cook_mode == DEFROST) {
							if(cook_temperature_set < 70)
								cook_temperature_set += 1;
						}
						else if(cook_temperature_set < 225)
								cook_temperature_set += 1;
					}
				}
			}
	
			f_key_press		= 1;
			counter_setting	= 0;	
		}
		//////////////////////////////////////////// (( Temp - )) ///////////////////////////////////////////
		else if((!KEY_DATA[0] && KEY_DATA[1] == 0x40 && !KEY_DATA[2]) && (cook_mode != 0) && !f_finish_cooking && !f_start && !f_lock && f_power && !f_show_version && !f_show_brand && !error_number) {
			if(!f_key_press || (counter_key_press > speed_key/*MUL(MAIN_TIMER_FREQUENCE,0.7)*/ && !f_standby_hold)) {
				counter_key_press = 0;
				
				if(speed_key > 200)
					speed_key -= 200;
				else
					speed_key = 100;
				
				if(cook_mode) {
					if(setting_mode != SET_TEMP)
						setting_mode = SET_TEMP;
					else {
						if(cook_temperature_set > 40)
							cook_temperature_set -= 1;
					}
				}
			}
			
			f_key_press		= 1;
			counter_setting	= 0;
		}
		//////////////////////////////////////////// (( Time - )) ///////////////////////////////////////////
		else if((KEY_DATA[0] == 0x01 && !KEY_DATA[1] && !KEY_DATA[2]) && !f_finish_cooking && !f_start && !f_lock && !f_show_version && !f_show_brand && !error_number) {
			if(!f_key_press || (counter_key_press > speed_key && !f_standby_hold)) {
				counter_key_press = 0;
	
				if(speed_key > 200)
					speed_key -= 200;
				else
					speed_key = 100;
		
				if(!f_start) {
					if(setting_mode == SET_CLOCK){
						if(!clock_minute) {
							clock_minute = 59;
							if(!clock_hour)
								clock_hour = 23;
							else
								clock_hour--;
						}
						else
							clock_minute--;
						clock_second = 0;
					}
					else if(cook_mode) {
						if(setting_mode != SET_TIME)
							setting_mode = SET_TIME;
						else {
							if(cook_minute_set)
								cook_minute_set--;
							cook_second_set	= 0;
						}
					}
				}
			}
			
			f_key_press		= 1;
			counter_setting	= 0;
		}
		//////////////////////////////////////////// (( Time + )) ///////////////////////////////////////////
		else if((KEY_DATA[0] == 0x02 && !KEY_DATA[1] && !KEY_DATA[2]) && !f_finish_cooking && !f_start && !f_lock && !f_show_version && !f_show_brand && !error_number) {
			if(!f_key_press || (counter_key_press > speed_key && !f_standby_hold)) {
				counter_key_press = 0;
	
				if(speed_key > 200)
					speed_key -= 200;
				else
					speed_key = 100;
		
				if(!f_start) {
					if(setting_mode == SET_CLOCK) {
						if(++clock_minute > 59) {
							clock_minute = 0;
							if(++clock_hour > 23)
								clock_hour = 0;
						}
						clock_second = 0;
					}
					else if(cook_mode) {
						if(setting_mode != SET_TIME)
							setting_mode = SET_TIME;
						else {
							if(cook_minute_set < 240)
								cook_minute_set++;
							cook_second_set	= 0;
						}
					}
				}
			}
			
			f_key_press		= 1;
			counter_setting	= 0;
		}
		//////////////////////////////////////////// (( (Temp - & Time -) LOCK )) ///////////////////////////
		else if((KEY_DATA[0] == 0x01 && KEY_DATA[1] == 0x40 && !KEY_DATA[2]) && (counter_key_press > KEY_THRESHOLD && !f_standby_hold) && !f_key_press && f_power && !f_finish_cooking && !f_show_version && !error_number) {
			f_key_press	= 1;
			f_lock		= !f_lock;
			f_icon_lock = !f_icon_lock;
			buzzer		= BUZ_BEEP;
		}
		//////////////////////////////////////////// (( (PIZZA & Time -) XTAL status show )) ////////////////
		else if((KEY_DATA[0] == 0x01 && !KEY_DATA[1] && KEY_DATA[2] == 0x02) && (counter_key_press > KEY_THRESHOLD && !f_standby_hold) && !f_key_press && !f_finish_cooking && !f_start && f_power && !cook_mode && !f_show_version && !error_number) {
			f_key_press			= 1;
			f_xtal_show_status	= 1;
			buzzer				= BUZ_BEEP;
		}
		//////////////////////////////////////////// (( (TOP element + PIZZA) TEST )) ///////////////////////
		else if((KEY_DATA[0] == 0x08 && !KEY_DATA[1] && KEY_DATA[2] == 0x02) && (counter_key_press > KEY_THRESHOLD && !f_standby_hold) && !f_key_press && !f_finish_cooking && !f_start && f_power && !cook_mode && !f_show_version && !error_number && f_lock) {
			f_key_press	= 1;
			f_test		= 1;
			f_lock		= 0;
			buzzer		= BUZ_BEEP;
		}
		//////////////////////////////////////////// (( (BOT element + CHICKEN) TEST_DENO )) ////////////////
		else if((KEY_DATA[0] == 0x04 && KEY_DATA[1] == 0x80 && !KEY_DATA[2]) && (counter_key_press > KEY_THRESHOLD && !f_standby_hold) && !f_key_press && !f_finish_cooking && !f_start && f_power && !cook_mode && !f_show_version && !error_number && f_lock) {
			f_key_press	 = 1;
			f_test_deno	 = 1;
			f_relay_test = 1;
			f_lock		 = 0;
			buzzer		 = BUZ_BEEP;
		}
	}
	else if((KEY_DATA[0] || KEY_DATA[1] || KEY_DATA[2]) && !error_number) {
		f_key_press		= 1;
		f_standby   	= 0;
		f_standby_hold 	= 1;
		if(!f_power)
			setting_mode = SET_CLOCK;
	}

	if(f_start) {
		cook_run();
			
		if(f_motor_chicken)
			MOTOR_CHICKEN = 1;
		else
			MOTOR_CHICKEN = 0;
	}
	else if(!f_test && !f_test_deno){
		ELEMENT_TOP		= 0;
		ELEMENT_BOTTOM	= 0;
		FAN_CONVECTION	= 0;
		MOTOR_CHICKEN	= 0;
	}
	
	if(!f_test && !f_test_deno) {	
		if((counter_key_release < 30) && f_power)
			LAMP = 1;
		else {
			counter_key_release	= 30;
			LAMP				= 0;
		}
	}

	if(f_start || f_finish_cooking || f_test || f_test_deno || error_number) // Timer Power OFF
		counter_power_off = 0;
	else if(counter_power_off > 30) {
		f_standby     = 1;
		f_all_leds_on = 0;
		if(setting_mode == SET_CLOCK)
			setting_mode = OFF;
	}
	
	if((counter_read_temperature > MUL(MAIN_TIMER_FREQUENCY,0.5)) || !f_startup_temperature) {
		counter_read_temperature = 0;
		temperature_calculation();
	}

	/******************* Other code sections ************************/
	if(f_key_press || (f_start && !f_preheat_alarm) || (f_power && !f_test && !f_preheat_alarm) || f_show_version || f_show_brand || error_number || f_xtal_show_status || f_finish_cooking || (!f_power && setting_mode != SET_CLOCK)) {
		f_blink_state	= 0;
		counter_blink	= 0;
	}
	else if(counter_blink > MUL(MAIN_TIMER_FREQUENCY,0.5)) { // =2Hz
		counter_blink	= 0;
		f_blink_state	= !f_blink_state; // Blink
	}
	
	if(f_cook_show || f_preheat_alarm || f_test || f_test_deno || f_preheat_enable || f_show_version || f_show_brand || error_number || f_xtal_show_status || f_finish_cooking || setting_mode == SET_CLOCK || setting_mode == SET_TEMP || setting_mode == SET_TIME) {
		f_blink_colon	= 0;
		counter_blink_colon	= 0;
	}
	else if(counter_blink_colon > MUL(MAIN_TIMER_FREQUENCY,0.5)) { // =2Hz
		counter_blink_colon	= 0;
		f_blink_colon	= !f_blink_colon; // Blink
	}

	if(!f_test && !f_test_deno) {
		make_segment_data();
		make_led_flags();
	}
}

void __attribute((interrupt(0x14))) CTMA0Interrupt(void)
{
	static uint16_t	counter_xtal_show_status = 0;

	_ctm0af = 0; // CTM0 Comparator A match Interrupt request flag // 0: No request

	counter_show_version++;
	counter_read_temperature++;
	counter_key_press++;
  counter_blink++;
  counter_blink_colon++;
	counter_icon_fan++;
	
	// Equals to roughly 5 seconds + The Fsub is still set on the LXT option // 30030 = 5 / (1 / 6006) = 6006 x 5
	if( (counter_xtal_verify < MUL(MAIN_TIMER_FREQUENCY,5)) && _fss ) 
		counter_xtal_verify++;
	else {
		_fss           = 0; // Switch to LIRC as the Fsub in case of XTAL failure
		f_xtal_failure = 1;
	}
	// Equals to roughly 1 seconds
	if( (counter_xtal_show_status < MAIN_TIMER_FREQUENCY) && f_xtal_show_status )
		counter_xtal_show_status++;
	else {
		f_xtal_show_status       = 0; // Hide the c1/c0 symbol for the XTAL status
		counter_xtal_show_status = 0;
	}
	
	if( f_cook_show && counter_cook_show < MUL(MAIN_TIMER_FREQUENCY,2) )
		counter_cook_show++;
	else {
		f_cook_show       = 0;
		counter_cook_show = 0;
	}
		
	refresh_segment();
	refresh_led();
	make_sound();
	program_test();
	program_test_deno();
}

void __attribute((interrupt(0x28))) TB1Interrupt(void)
{
	static uint16_t Ad_i = 0;
	static uint16_t Ad_d = 0;
	static uint16_t Tl   = 0;
	static uint16_t Tu   = 0;
		
	counter_key_release++;
	//counter_preshow++;
	counter_power_off++;
	
//	if(!f_power) {
//		if(++counter_set_time > 30) {
//			setting_mode  = OFF;
//			f_all_leds_on = 0;
//		}
//	}
	
	if(f_show_brand)
		counter_show_brand++;
	
	counter_xtal_verify = 0;
	
	counter_blink_colon	= MUL(MAIN_TIMER_FREQUENCY,0.5) + 1;
	
	if(++clock_second > 59) {
		clock_second = 0;
		if(++clock_minute > 59) {
			clock_minute = 0;
			if(++clock_hour > 23)
				clock_hour = 0;
		}
	}

	if(f_start) {
		if(f_preheat_enable) { // Preheat Conditions
		  	if((caviti_temperature+3) >= cook_temperature_set) {
				f_preheat_alarm  	= 1;
				buzzer				= BUZ_PREHEAT;
		  	}
			else if(preheat_time_second)
				preheat_time_second--;
			else {
				if(preheat_time_minute) {
					preheat_time_minute--;
					preheat_time_second	= 59;
				}
				else {
					f_preheat_alarm 	= 1;
					buzzer				= BUZ_PREHEAT;
				}
			}
		}
		else  { // Cook Timer
			if(cook_second_set)
				cook_second_set--;
			else {
				if(cook_minute_set) {
					cook_minute_set--;
					cook_second_set = 59;
				}
				else
					ending_handle();
			}
		}	
	}

	if(++counter_setting > 9 && setting_mode != SET_CLOCK) {
		counter_setting		= 0;
		setting_mode		= OFF;
	}
		
	if(cook_temperature_set > 175) {
		Ad_i	= 3;
		Ad_d	= 2;
		Tl		= 0;
		Tu		= 1;
	}
	else if(cook_temperature_set > 100) {
		Ad_i	= 4;
		Ad_d	= 1;
		Tl		= 1;
		Tu		= 0;
	}
	else if(cook_temperature_set > 85) {
		Ad_i	= 5;
		Ad_d	= 0;
		Tl		= 1;
		Tu		= 0;
	}
	else {
		Ad_i	= 7;
		Ad_d	= 0;
		Tl		= 1;
		Tu		= 0;
	}
  
	f_element = controller(cook_temperature_set, caviti_temperature, Tu, Tl, Ad_i, Ad_d, 30, f_controller_init);
	f_controller_init = 0;
}

uint8_t data_segment(uint8_t value)
{
	uint8_t data_segment_value = 0;

	switch(value) {
		case 0: // 0
			data_segment_value = 0b00111111;// SEGA=1;SEGB=1;SEGC=1;SEGD=1;SEGE=1;SEGF=1;SEGG=0;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 1: // 1
			data_segment_value = 0b00000110;// SEGA=0;SEGB=1;SEGC=1;SEGD=0;SEGE=0;SEGF=0;SEGG=0;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 2: // 2
			data_segment_value = 0b01011011;// SEGA=1;SEGB=1;SEGC=0;SEGD=1;SEGE=1;SEGF=0;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 3: // 3
			data_segment_value = 0b01001111;// SEGA=1;SEGB=1;SEGC=1;SEGD=1;SEGE=0;SEGF=0;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 4: // 4
			data_segment_value = 0b01100110;// SEGA=0;SEGB=1;SEGC=1;SEGD=0;SEGE=0;SEGF=1;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 5: // 5
			data_segment_value = 0b01101101;// SEGA=1;SEGB=0;SEGC=1;SEGD=1;SEGE=0;SEGF=1;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 6: // 6
			data_segment_value = 0b01111101;// SEGA=1;SEGB=0;SEGC=1;SEGD=1;SEGE=1;SEGF=1;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 7: // 7
			data_segment_value = 0b00000111;// SEGA=1;SEGB=1;SEGC=1;SEGD=0;SEGE=0;SEGF=0;SEGG=0;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 8: // 8
			data_segment_value = 0b01111111;// SEGA=1;SEGB=1;SEGC=1;SEGD=1;SEGE=1;SEGF=1;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 9: // 9
			data_segment_value = 0b01101111;// SEGA=1;SEGB=1;SEGC=1;SEGD=1;SEGE=0;SEGF=1;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 10: // OFF
			data_segment_value = 0b00000000;// SEGA=0;SEGB=0;SEGC=0;SEGD=0;SEGE=0;SEGF=0;SEGG=0;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 11: // Dash
			data_segment_value = 0b01000000;// SEGA=0;SEGB=0;SEGC=0;SEGD=0;SEGE=0;SEGF=0;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 14: // n
			data_segment_value = 0b01010100;// SEGA=0;SEGB=0;SEGC=1;SEGD=0;SEGE=1;SEGF=0;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 15: // P
			data_segment_value = 0b01110011;// SEGA=1;SEGB=1;SEGC=0;SEGD=0;SEGE=1;SEGF=1;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 16: // r
			data_segment_value = 0b01010000;// SEGA=0;SEGB=0;SEGC=0;SEGD=0;SEGE=1;SEGF=0;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 17: // E
			data_segment_value = 0b01111001;// SEGA=1;SEGB=0;SEGC=0;SEGD=1;SEGE=1;SEGF=1;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 18: // d
			data_segment_value = 0b01011110;// SEGA=0;SEGB=1;SEGC=1;SEGD=1;SEGE=1;SEGF=0;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 19: // H
			data_segment_value = 0b01110110;// SEGA=0;SEGB=1;SEGC=1;SEGD=0;SEGE=1;SEGF=1;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 20: // A
			data_segment_value = 0b01110111;// SEGA=1;SEGB=1;SEGC=1;SEGD=0;SEGE=1;SEGF=1;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 21: // t
			data_segment_value = 0b01111000;// SEGA=0;SEGB=0;SEGC=0;SEGD=1;SEGE=1;SEGF=1;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 22: // S
			data_segment_value = 0b01101101;// SEGA=1;SEGB=0;SEGC=1;SEGD=1;SEGE=0;SEGF=1;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 24: // Single f_colon_show clock 
			data_segment_value = 0b10000000;// SEGA=0;SEGB=0;SEGC=0;SEGD=0;SEGE=0;SEGF=0;SEGG=0;SEG_ICON=1;SEG_ICON2=0;
		break;
		case 26: // c
			data_segment_value = 0b01011000;// SEGA=0;SEGB=0;SEGC=0;SEGD=1;SEGE=1;SEGF=0;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 27: // i
			data_segment_value = 0b00000100;// SEGA=0;SEGB=0;SEGC=0;SEGD=0;SEGE=1;SEGF=0;SEGG=0;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 28: // o
			data_segment_value = 0b01011100;// SEGA=0;SEGB=0;SEGC=1;SEGD=1;SEGE=1;SEGF=0;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 29: // K
			data_segment_value = 0b01110101;// SEGA=1;SEGB=0;SEGC=1;SEGD=0;SEGE=1;SEGF=1;SEGG=1;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 30: // C
			data_segment_value = 0b00111001;// SEGA=1;SEGB=0;SEGC=0;SEGD=1;SEGE=1;SEGF=1;SEGG=0;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 31: // Under_line
			data_segment_value = 0b00001000;// SEGA=0;SEGB=0;SEGC=0;SEGD=1;SEGE=0;SEGF=0;SEGG=0;SEG_ICON=0;SEG_ICON2=0;
		break;
		case 32: // degree+Celsius
			data_segment_value = 0b11100001;// SEGA=1;SEGB=0;SEGC=0;SEGD=0;SEGE=0;SEGF=1;SEGG=1;SEG_ICON=1;SEG_ICON2=0;
		break;
//		case 33: // P icon, degree
//			data_segment_value = 0b00000000;// SEGA=0;SEGB=0;SEGC=0;SEGD=0;SEGE=0;SEGF=0;SEGG=0;SEG_ICON=0;SEG_ICON2=1;
//		break;
		case 34: // AUTO icon
			data_segment_value = 0b10000000;// SEGA=0;SEGB=0;SEGC=0;SEGD=0;SEGE=0;SEGF=0;SEGG=0;SEG_ICON=1;SEG_ICON2=0;
		break;
		case 35: // Cook icon
			data_segment_value = 0b10000000;// SEGA=0;SEGB=0;SEGC=0;SEGD=0;SEGE=0;SEGF=0;SEGG=0;SEG_ICON=1;SEG_ICON2=0;
		break;
		case 36: // Lock icon
			data_segment_value = 0b01011011;// SEGA=0;SEGB=0;SEGC=0;SEGD=0;SEGE=0;SEGF=0;SEGG=0;SEG_ICON=1;SEG_ICON2=0;
		break;
//		case 37: // Ring icon
//			data_segment_value = 0b00000000;// SEGA=0;SEGB=0;SEGC=0;SEGD=0;SEGE=0;SEGF=0;SEGG=0;SEG_ICON=0;SEG_ICON2=1;
//		break;
	}
	
	return data_segment_value;
}

void make_segment_data(void)
{
	if(error_number) { 
		value_segment[1] = 11; // Dash
		value_segment[2] = 17; // E
		value_segment[3] = error_number; // Num. Error
		value_segment[4] = 11; // Dash
		
		f_icon_Degree_Celsius = f_icon_auto = f_icon_colon = f_icon_cook = f_icon_p = f_icon_finish_cooking = 0;
	}
	else if(!f_show_version && !f_show_brand) {
		if(f_xtal_show_status) {
			value_segment[1] = 26; // c (Down)
			value_segment[2] = !f_xtal_failure;
			value_segment[3] = 10;
			value_segment[4] = 10;
		}
		else if(f_finish_cooking) { // End
			value_segment[1] = 17;
			value_segment[2] = 14;
			value_segment[3] = 18;
			value_segment[4] = 10;
		}
		else if(f_power) {
			if(f_preheat_enable && !f_preheat_alarm) { // PrE
				//if(counter_preshow <= 2) {
				value_segment[1] = 15;
				value_segment[2] = 16;
				value_segment[3] = 17;
				value_segment[4] = 10;
				//}
//				else if((counter_preshow > 2) && (counter_preshow <= 5)) {
//					value_segment[1] = 19;
//					value_segment[2] = 17;
//					value_segment[3] = 20;
//					value_segment[4] = 21;
//				}
				//else
				//	counter_preshow = 0;
			}
			else if(f_preheat_alarm) {
				if(!f_blink_state) {
					value_segment[1] = 15;
					value_segment[2] = 16;
					value_segment[3] = 17;
					value_segment[4] = 10;
				}
				else {
					value_segment[1] = 10;
					value_segment[2] = 10;
					value_segment[3] = 10;
					value_segment[4] = 10;
				}
			}
			else if(f_start) {
				if(f_cook_show) { // COOK
					value_segment[1] = 30;
					value_segment[2] = 0;
					value_segment[3] = 0;
					value_segment[4] = 29;
				}
				else {
					if(cook_minute_set < 60) {
						value_segment[1] = cook_minute_set / 10; // run
						value_segment[2] = cook_minute_set % 10;
						value_segment[3] = cook_second_set / 10;
						value_segment[4] = cook_second_set % 10;
					}
					else {
						value_segment[1] = (cook_minute_set / 60) / 10;
						value_segment[2] = (cook_minute_set / 60) % 10;
						value_segment[3] = (cook_minute_set % 60) / 10;
						value_segment[4] = (cook_minute_set % 60) % 10;
					}
				}
			}
			else {
				if(setting_mode == SET_TIME){
					value_segment[1] = (cook_minute_set / 60) / 10;
					value_segment[2] = (cook_minute_set / 60) % 10;
					value_segment[3] = (cook_minute_set % 60) / 10;
					value_segment[4] = (cook_minute_set % 60) % 10;
				}
				else if(setting_mode == SET_TEMP) {
					if(cook_temperature_set / 100)
						value_segment[1] = cook_temperature_set / 100;
					else
						value_segment[1] = 10; // (segment off)
						   	
					if( ((cook_temperature_set / 10) % 10) || (cook_temperature_set / 100) )
						value_segment[2] = (cook_temperature_set / 10) % 10;
					else
						value_segment[2] = 10; // (segment off)
						
					value_segment[3] = cook_temperature_set % 10;
					value_segment[4] = 32;
				}
				else {
					value_segment[1] = clock_hour / 10;
					value_segment[2] = clock_hour % 10;
					value_segment[3] = clock_minute / 10;
					value_segment[4] = clock_minute % 10;
				}
			}
		}
		else {
			if(f_blink_state && (setting_mode == SET_CLOCK)) {
				value_segment[1] = 10;
				value_segment[2] = 10;
				value_segment[3] = 10;
				value_segment[4] = 10;
			}
			else {
				value_segment[1] = clock_hour / 10;
				value_segment[2] = clock_hour % 10;
				value_segment[3] = clock_minute / 10;
				value_segment[4] = clock_minute % 10;
			}
		}

		/**************** f_colon_show **************/
		if( ((setting_mode == SET_CLOCK && !f_blink_state) || (!f_blink_colon && setting_mode != SET_CLOCK && setting_mode != SET_TEMP) || (setting_mode == SET_TIME)) && !f_cook_show && !f_preheat_enable && !f_test && !(f_test_deno && (f_relay_test ||f_key_test)) && !f_xtal_show_status && !f_finish_cooking && !error_number)
			f_colon_show = 1;
		else
			f_colon_show = 0;
	
		if(f_start && !f_cook_show && !f_preheat_enable)
			f_icon_cook	= 1;
		else
			f_icon_cook	= 0;
		
		if(f_finish_cooking && !f_blink_state)
			f_icon_finish_cooking	= 1;
		else
			f_icon_finish_cooking	= 0;
		
		if(f_lock)
			f_icon_lock	= 1;
		else
			f_icon_lock	= 0;
			
		if((setting_mode == SET_TEMP) && !error_number)
			f_icon_Degree_Celsius = 1;
		else
			f_icon_Degree_Celsius = 0;
	}
	else if(f_show_brand) {
		if(counter_show_brand >= 3) {
			counter_show_brand = 0;
			f_all_leds_on = 1;
			f_show_brand = 0;
		}
		else {
			value_segment[1] = 19; // H
			value_segment[2] = 27; // i
			value_segment[3] = 16; // r
			value_segment[4] = 28; // o
		}
	}
	else {
		if(counter_show_version < MUL(MAIN_TIMER_FREQUENCY,0.8)) {
			value_segment[2] = 10; /* OFF */
			value_segment[3] = 10; /* OFF */
			value_segment[4] = 10; /* OFF */
			
			if(MODEL / 10)
				value_segment[1] = MODEL / 10;
			else
				value_segment[1] = MODEL;
		}
		else if(counter_show_version < MUL(MAIN_TIMER_FREQUENCY,0.9)) {
			if(MODEL / 10)
				value_segment[2] = MODEL % 10;
			else
				value_segment[2] = 10; /* OFF */
		}
		else if(counter_show_version < MUL(MAIN_TIMER_FREQUENCY,1.0)) {
			value_segment[4] = 31; /* Under_line */
		}
		else if(counter_show_version < MUL(MAIN_TIMER_FREQUENCY,1.1)) {
			value_segment[4] = 10; /* OFF */
			value_segment[3] = 31; /* Under_line */
		}
		else if(counter_show_version < MUL(MAIN_TIMER_FREQUENCY,1.2)) {
			value_segment[3] = 10; /* OFF */
			value_segment[2] = 31; /* Under_line */
		}
		else if(counter_show_version < MUL(MAIN_TIMER_FREQUENCY,1.3)) {
			value_segment[2] = 10; /* OFF */
			value_segment[1] = 31; /* Under_line */
		}
		else if(counter_show_version < MUL(MAIN_TIMER_FREQUENCY,1.4)) {
			if(VERSION / 10)
				value_segment[1] = VERSION / 10;
			else
				value_segment[1] = VERSION;
		}
		else if(counter_show_version < MUL(MAIN_TIMER_FREQUENCY,2.2)) {
			if(VERSION / 10)
				value_segment[2] = VERSION % 10;
			else
				value_segment[2] = 10; /* OFF */
		}
		else if(counter_show_version < MUL(MAIN_TIMER_FREQUENCY,2.3)) {
			value_segment[4] = 31; /* Under_line */
		}
		else if(counter_show_version < MUL(MAIN_TIMER_FREQUENCY,2.4)) {
			value_segment[4] = 10; /* OFF */
			value_segment[3] = 31; /* Under_line */
		}
		else if(counter_show_version < MUL(MAIN_TIMER_FREQUENCY,2.5)) {
			value_segment[3] = 10; /* OFF */
			value_segment[2] = 31; /* Under_line */
		}
		else if(counter_show_version < MUL(MAIN_TIMER_FREQUENCY,2.6)) {
			value_segment[2] = 10; /* OFF */
			value_segment[1] = 31; /* Under_line */
		}
		else if(counter_show_version < MUL(MAIN_TIMER_FREQUENCY,2.7)) {
			value_segment[1] = 10; /* OFF */
		}
		else {
			f_show_version	= 0;
			if(!error_number)
				f_show_brand = 1;
		}
	}
}

void refresh_segment(void)
{
	static uint8_t index_segment = 0;
	
	index_segment++;
	switch(index_segment) {
		//////////////////////////////////////// Segment 1 ///////////////////////////////////////
		case 1:
			SEGG = 0;
			COM4 = 1;
			COM1 = 0;
			segment_on = data_segment(value_segment[1]);		
			if(segment_on & 1)
				SEGA = 1;
		break;
		case 2:
			SEGA = 0;
			if(segment_on & 2)
				SEGB = 1;
		break;
		case 3:
			SEGB = 0;
			if(segment_on & 4)
				SEGC = 1;
		break;
		case 4:
			SEGC = 0;
			if(segment_on & 8)
				SEGD = 1;
		break;
		case 5:
			SEGD = 0;
			if(segment_on & 16)
				SEGE = 1;
		break;
		case 6:
			SEGE = 0;
			if(segment_on & 32)
				SEGF = 1;
		break;
		case 7:
			SEGF = 0;
			if(segment_on & 64)
				SEGG = 1;
		break;
		case 8:
			SEGG = 0;
			if(f_icon_lock)
				SEG_ICON=1;
		break;
		//////////////////////////////////////// Segment 2 ///////////////////////////////////////
		case 9:
			SEG_ICON = 0;
			SEG_ICON2 = 0;
			COM1 = 1;
			COM2 = 0;
			segment_on = data_segment(value_segment[2]);		
			if(segment_on & 1)
				SEGA = 1;
		break;
		case 10:
			SEGA = 0;
			if(segment_on & 2)
				SEGB = 1;
		break;
		case 11:
			SEGB = 0;
			if(segment_on & 4)
				SEGC = 1;
		break;
		case 12:
			SEGC = 0;
			if(segment_on & 8)
				SEGD = 1;
		break;
		case 13:
			SEGD = 0;
			if(segment_on & 16)
				SEGE = 1;
		break;
		case 14:
			SEGE = 0;
			if(segment_on & 32)
				SEGF = 1;
		break;
		case 15:
			SEGF = 0;
			if(segment_on & 64)
				SEGG = 1;
		break;
		case 16:
			SEGG = 0;
			if(f_icon_cook)
				SEG_ICON = 1;
		break;
		case 17:
			SEG_ICON = 0;
			if(f_icon_finish_cooking)
				SEG_ICON2=1;
		break;
		//////////////////////////////////////// Segment 3 ///////////////////////////////////////
		case 18:
			SEG_ICON = 0;
			SEG_ICON2 = 0;
			COM2 = 1;
			COM3 = 0;
			segment_on = data_segment(value_segment[3]);		
			if(segment_on & 1)
				SEGA = 1;
		break;
		case 19:
			SEGA = 0;
			if(segment_on & 2)
				SEGB = 1;
		break;
		case 20:
			SEGB = 0;
			if(segment_on & 4)
				SEGC = 1;
		break;
		case 21:
			SEGC = 0;
			if(segment_on & 8)
				SEGD = 1;
		break;
		case 22:
			SEGD = 0;
			if(segment_on & 16)
				SEGE = 1;
		break;
		case 23:
			SEGE = 0;
			if(segment_on & 32)
				SEGF = 1;
		break;
		case 24:
			SEGF = 0;
			if(segment_on & 64)
				SEGG = 1;
		break;
		case 25:
			SEGG = 0;
			if(f_colon_show)
				SEG_ICON=1;
		break;
		case 26:
			SEG_ICON = 0;
			if(f_icon_Degree_Celsius)
				SEG_ICON2=1;
		break;
		//////////////////////////////////////// Segment 4 ///////////////////////////////////////
		case 27:
			SEG_ICON2 = 0;
			COM3 = 1;
			COM4 = 0;
			segment_on = data_segment(value_segment[4]);	
			if(segment_on & 1)
				SEGA = 1;
		break;
		case 28:
			SEGA = 0;
			if(segment_on & 2)
				SEGB = 1;
		break;
		case 29:
			SEGB = 0;
			if(segment_on & 4)
				SEGC = 1;
		break;
		case 30:
			SEGC = 0;
			if(segment_on & 8)
				SEGD = 1;
		break;
		case 31:
			SEGD = 0;
			if(segment_on & 16)
				SEGE = 1;
		break;
		case 32:
			SEGE = 0;
			if(segment_on & 32)
				SEGF = 1;
		break;
		case 33:
			SEGF = 0;
			if(segment_on & 64)
				SEGG = 1;
		break;
		case 34:
			SEGG = 0;
			if(f_icon_p)
				SEG_ICON=1;
		break;
		case 35:
			SEG_ICON = 0;
			if(f_icon_auto)
				SEG_ICON2 = 1;
			index_segment = 0;
	}
}

void make_led_flags(void)
{	
	if((cook_mode == TOP_HEAT || cook_mode == BOTH_HEAT || (cook_mode == DEFROST && f_start) || ((cook_mode == PIZZA || cook_mode == CHICKEN || cook_mode == CAKE) && f_start && f_preheat_enable) || (cook_mode == PIZZA && f_start && !f_preheat_enable && (cook_minute_set < 3)) || ((cook_mode == CHICKEN || cook_mode == CAKE) && f_start && !f_preheat_enable && (cook_minute_set < 2))) && !f_standby && !error_number)
		f_led_ele_top = 1;
	else
		f_led_ele_top = 0;
		
	if((cook_mode == BOTTOM_HEAT || cook_mode == BOTH_HEAT || ((cook_mode == PIZZA || cook_mode == CHICKEN || cook_mode == CAKE) && f_start && f_preheat_enable) || (cook_mode == PIZZA && f_start && !f_preheat_enable && (cook_minute_set > 2)) || ((cook_mode == CHICKEN || cook_mode == CAKE) && f_start && !f_preheat_enable && (cook_minute_set > 1))) && !f_standby && !error_number)
		f_led_ele_bot = 1;
	else
		f_led_ele_bot = 0;
		
	if(((cook_mode == PIZZA && !f_standby)) && !error_number)
		f_led_pizza = 1;
	else
		f_led_pizza = 0;
		
	if(((cook_mode == CHICKEN && !f_standby)) && !error_number)
		f_led_chicken = 1;
	else
		f_led_chicken = 0;
		
	if(((cook_mode == CAKE && !f_standby)) && !error_number)
		f_led_cake = 1;
	else
		f_led_cake = 0;
		
	if(((cook_mode == DEFROST && !f_standby)) && !error_number)
		f_led_defrost = 1;
	else
		f_led_defrost = 0;
		
	if(((f_motor_chicken && !f_standby)) && !error_number)
		f_led_motor = 1;
	else
		f_led_motor = 0;
		
	if((f_start && !f_standby) && !error_number)
		f_led_start = 1;
	else
		f_led_start = 0;
}

void refresh_led(void)
{
	static uint8_t index_led = 0;
	
	LED_COM1 = LED_COM2 = LED_COM3 = 0;
	
	switch(++index_led) {
		case 1: // All LEDs off
			LED_DATA1 = LED_DATA2 = LED_DATA3 = 1;
		break;
		
		case 2: // Pizza
			LED_DATA1 = 0;
			LED_DATA3 = LED_DATA2 = 1;
			if(f_led_pizza || f_all_leds_on)
				LED_COM1 = 1;
		break;
		
		case 3: // Start/Stop
			LED_DATA2 = 0;
			LED_DATA1 = LED_DATA3 = 1;
			if(f_led_start || f_all_leds_on)
				LED_COM1 = 1;
		break;
		
		case 4: // Cake
			LED_DATA3 = 0;
			LED_DATA1 = LED_DATA2 = 1;
			if(f_led_cake || f_all_leds_on)
				LED_COM1 = 1;
		break;
		
		case 5: // Defrost
			LED_DATA1 = 0;
			LED_DATA3 = LED_DATA2 = 1;
			if(f_led_defrost || f_all_leds_on)
				LED_COM2 = 1;
		break;
		
		case 6: // Top
			LED_DATA2 = 0;
			LED_DATA1 = LED_DATA3 = 1;
			if(f_led_ele_top || f_all_leds_on)
				LED_COM2 = 1;
		break;
		
		case 7: // Chicken
			LED_DATA3 = 0;
			LED_DATA1 = LED_DATA2 = 1;
			if(f_led_chicken || f_all_leds_on)
				LED_COM2 = 1;
		break;
		
		case 8: // Bot
			LED_DATA1 = 0;
			LED_DATA2 = LED_DATA3 = 1;
			if(f_led_ele_bot || f_all_leds_on)
				LED_COM3 = 1;
		break;
		
		case 9: // Motor
			LED_DATA3 = 0;
			LED_DATA1 = LED_DATA2 = 1;
			if(f_led_motor || f_all_leds_on)
				LED_COM3 = 1;
		break;
				
		default:
			index_led = 0;
	}
}

void make_sound(void)
{
	counter_buzzer++;

	switch(buzzer) {
		case OFF:
			counter_buzzer	 = 0;
			PIN_SHARED_TIMER = 0;
		break;
		
		case BUZ_CONNECT:
			if( counter_buzzer < 300 ) {
				PIN_SHARED_TIMER = 1;
			}
			else if( counter_buzzer < 500 )
				PIN_SHARED_TIMER = 0;
			else if( counter_buzzer < 800 ) {
				PIN_SHARED_TIMER = 1;
			}
			else if( counter_buzzer < 1500 )
				PIN_SHARED_TIMER = 0;
			else
				buzzer = OFF;
		break;
		
		case BUZ_BEEP:
			if( counter_buzzer < 233 ) {
				PIN_SHARED_TIMER = 1;
			}
			else if( counter_buzzer < 1000 )
				PIN_SHARED_TIMER = 0;
			else
				buzzer = OFF;
		break;
		
		case BUZ_ERROR:
			if( counter_buzzer < 3750 ) {
				PIN_SHARED_TIMER = 1;
			}
			else if( counter_buzzer < 8000 )
				PIN_SHARED_TIMER = 0;
			else if( counter_buzzer < 11750 ) {
				PIN_SHARED_TIMER = 1;
			}
			else if( counter_buzzer < 12000 )
				PIN_SHARED_TIMER = 0;
			else
				buzzer = OFF;
		break;
		
		case BUZ_PREHEAT:
		case BUZ_ALARM: // Contiuous tone
			if( counter_buzzer < 3750 ) {
				PIN_SHARED_TIMER = 1;
			}
			else if( counter_buzzer < 19000 )
				PIN_SHARED_TIMER = 0;
			else if( counter_buzzer < 22750 ) {
				PIN_SHARED_TIMER = 1;
			}
			else if( counter_buzzer < 38000 )
				PIN_SHARED_TIMER = 0;
			else
				counter_buzzer = 0;
		break;
	}
}

void cook_run(void)
{
	switch(cook_mode) {
		case 0:
			ELEMENT_TOP		= 0;
			ELEMENT_BOTTOM	= 0;
			FAN_CONVECTION	= 0;
			MOTOR_CHICKEN	= 0;
		break;
		case PIZZA:
			if(f_preheat_enable) {
		  		ELEMENT_BOTTOM	= f_element;
		  		ELEMENT_TOP		= f_element;
		  		FAN_CONVECTION	= 1;
		  	}	  	
		  	else if(cook_minute_set > 2) {
		  		ELEMENT_BOTTOM	= f_element;
				ELEMENT_TOP	    = 0;
				FAN_CONVECTION	= 1;
		  	}
		  	else {
		  		ELEMENT_TOP		= f_element;
		  		ELEMENT_BOTTOM	= 0;
		  		FAN_CONVECTION	= 1;
		  	}
		break;
		case CHICKEN:
		case CAKE:
			if(f_preheat_enable) {
		  		ELEMENT_BOTTOM	= f_element;
		  		ELEMENT_TOP		= f_element;
		  		FAN_CONVECTION	= 1;
		  	}	  	
		  	else if(cook_minute_set > 1) {
		  		ELEMENT_BOTTOM	= f_element;
				ELEMENT_TOP	= 0;
				FAN_CONVECTION	= 1;
		  	}
		  	else {
		  		ELEMENT_TOP		= f_element;
		  		ELEMENT_BOTTOM	= 0;
		  		FAN_CONVECTION	= 1;
		  	}
		break;
		case DEFROST:
			ELEMENT_TOP		= f_element;
			FAN_CONVECTION  = 1;
		break;
		case TOP_HEAT:
			ELEMENT_TOP		= f_element;
			FAN_CONVECTION  = 0;
		break;
		case BOTTOM_HEAT:
			ELEMENT_BOTTOM	= f_element;
			FAN_CONVECTION  = 1;
		break;
		case BOTH_HEAT:
			ELEMENT_TOP		= f_element;
			ELEMENT_BOTTOM	= f_element;
			FAN_CONVECTION  = 1;
		break;
	}
}

void ending_handle(void)
{
	reset();
	counter_key_release = 0;
	f_finish_cooking	= 1;
	setting_mode        = OFF;
	buzzer              = BUZ_ALARM;
}

void reset(void)
{
	f_start				  = 0;
	f_preheat_enable      = 0;
	f_icon_p              = 0;
	f_icon_cook           = 0;
	f_icon_auto           = 0;
	f_icon_finish_cooking = 0;
	f_motor_chicken       = 0;
	counter_power_off	  = 0;
	counter_key_release   = 0;
	counter_test		  = 0;
	f_all_leds_on		  = 0;
	cook_mode			  = 0;
	f_test				  = 0;
	f_test_deno			  = 0;
}

void error_handle(void)
{
	f_start					= 0;
	f_lock					= 0;
	setting_mode			= 0;
	f_finish_cooking		= 0;
	f_preheat_enable		= 0;
	f_colon_show		    = 0;
	f_show_version			= 0;
	f_show_brand				= 0;
	f_all_leds_on		    = 0;
	f_test				  	= 0;
	f_test_deno			  	= 0;
	f_motor_chicken			= 0;
	cook_mode				= 0;
	counter_power_off	 	= 0;
	counter_key_release  	= 0;
	counter_test		  	= 0;
}

void program_test(void)
{
	if(f_test) {
		counter_test++;		
		if(counter_test == 1) { // ELEMENT_BOT
			ELEMENT_BOTTOM = f_led_ele_bot = 1;
			buzzer = BUZ_BEEP;
		}
		else if(counter_test == VALUE_SENCOND_10_0) { // ELEMENT_TOP
			ELEMENT_BOTTOM = f_led_ele_bot = 0;
			ELEMENT_TOP = f_led_ele_top = 1;
			buzzer = BUZ_BEEP;
		}
		else if(counter_test == VALUE_SENCOND_20_0) { // motor
			ELEMENT_TOP = f_led_ele_top = 0;
			MOTOR_CHICKEN = f_led_motor = 1;
			buzzer = BUZ_BEEP;
		}
		else if(counter_test == VALUE_SENCOND_25_0) { // convection
			MOTOR_CHICKEN = f_led_motor = 0;
			FAN_CONVECTION = 1;
			buzzer = BUZ_BEEP;
		}
		else if(counter_test == VALUE_SENCOND_30_0) { // lamp
			FAN_CONVECTION = 0;
			LAMP = 1;
			buzzer = BUZ_BEEP;
		}
		else if(counter_test == VALUE_SENCOND_35_0) { // f_led_pizza
			LAMP = 0;
			f_led_pizza = 1;
		}
		else if(counter_test == VALUE_SENCOND_36_0) { // f_led_chicken
			f_led_pizza = 0;
			f_led_chicken = 1;
		}
		else if(counter_test == VALUE_SENCOND_37_0) { // f_led_cake
			f_led_chicken = 0;
			f_led_cake = 1;
		}
		else if(counter_test == VALUE_SENCOND_38_0) { // f_led_defrost
			f_led_cake = 0;
			f_led_defrost = 1;
		}
		else if(counter_test == VALUE_SENCOND_39_0) { // f_led_defrost
			f_led_defrost = 0;
			f_led_start = 1;
		}
		else if(counter_test == VALUE_SENCOND_40_0) { // all off
			ELEMENT_TOP					= 0;
			ELEMENT_BOTTOM				= 0;
			MOTOR_CHICKEN				= 0;
			FAN_CONVECTION				= 0;
			LAMP						= 0;
			f_led_pizza					= 0;
			f_led_chicken				= 0;
			f_led_cake					= 0;
			f_led_defrost				= 0;
			f_led_ele_top				= 0;
			f_led_ele_bot				= 0;
			f_led_motor					= 0;
			f_led_start					= 0;
			f_test						= 0;
			buzzer						= BUZ_CONNECT;
		}		
	
		if(!f_blink_state) {
			value_segment[1] = 21; // test
			value_segment[2] = 17; // test
			value_segment[3] = 22; // test
			value_segment[4] = 21; // test
		}
		else {
			value_segment[1] = 10;
			value_segment[2] = 10;
			value_segment[3] = 10;
			value_segment[4] = 10;
		}
		f_icon_lock = f_colon_show = 0;
	}
	else
		counter_test=0;
}

void program_test_deno(void)
{
	if(f_test_deno) {
		if(f_relay_test) {
			counter_test_deno++;
			if(counter_test_deno == 1) { // ELEMENT_BOT
				ELEMENT_BOTTOM = 1;
				buzzer = BUZ_BEEP;	
			}
			else if(counter_test_deno == VALUE_SENCOND_1_0) { // ELEMENT_TOP
				ELEMENT_BOTTOM = 0;
				ELEMENT_TOP = 1;
				buzzer = BUZ_BEEP;
			}
			else if(counter_test_deno == VALUE_SENCOND_2_0) { // motor
				ELEMENT_TOP = 0;
				MOTOR_CHICKEN = 1;
				buzzer = BUZ_BEEP;
			}
			else if(counter_test_deno == VALUE_SENCOND_3_0) { // convection
				MOTOR_CHICKEN = 0;
				FAN_CONVECTION = 1;
				buzzer = BUZ_BEEP;
			}
			else if(counter_test_deno == VALUE_SENCOND_4_0) { // lamp
				FAN_CONVECTION = 0;
				LAMP = 1;
				buzzer = BUZ_BEEP;
			}
			else if(counter_test_deno == VALUE_SENCOND_5_0) { // all off
				ELEMENT_TOP					= 0;
				ELEMENT_BOTTOM				= 0;
				MOTOR_CHICKEN				= 0;
				FAN_CONVECTION				= 0;
				LAMP						= 0;
				f_relay_test				= 0;
				f_key_test  				= 1;
				buzzer						= BUZ_BEEP;
				counter_test_deno			= 0;
			}
		
			value_segment[1] = 21; // test
			value_segment[2] = 17; // test
			value_segment[3] = 22; // test
			value_segment[4] = 21; // test
			f_icon_lock = f_colon_show = 0;
		}
		else if(f_key_test) {
			if(counter_test_deno == 0) {
				f_led_ele_bot = 1;
				if(!KEY_DATA[0] && KEY_DATA[1] == 0x80 && !KEY_DATA[2]) {
					counter_test_deno++;
				}
			}
			else if(counter_test_deno == 1) {
				f_led_ele_bot = 0;
				f_led_ele_top = 1;
				if(KEY_DATA[0] == 0x08 && !KEY_DATA[1] && !KEY_DATA[2]) {
					counter_test_deno++;
				}
			}
			else if(counter_test_deno == 2) {
				f_led_ele_top = 0;
				f_led_motor = 1;
				if(KEY_DATA[0] == 0x80 && !KEY_DATA[1] && !KEY_DATA[2]) {
					counter_test_deno++;
				}
			}
			else if(counter_test_deno == 3) {
				f_led_motor = 0;
				f_led_pizza = 1;
				if(!KEY_DATA[0] && !KEY_DATA[1] && KEY_DATA[2] == 0x02) {
					counter_test_deno++;
				}
			}
			else if(counter_test_deno == 4) {
				f_led_pizza = 0;
				f_led_chicken = 1;
				if(KEY_DATA[0] == 0x04 && !KEY_DATA[1] && !KEY_DATA[2]) {
					counter_test_deno++;
				}
			}
			else if(counter_test_deno == 5) {
				f_led_chicken = 0;
				f_led_cake = 1;
				if(!KEY_DATA[0] && !KEY_DATA[1] && KEY_DATA[2] == 0x01) {
					counter_test_deno++;
				}
			}
			else if(counter_test_deno == 6) {
				f_led_cake = 0;
				f_led_defrost = 1;
				if(KEY_DATA[0] == 0x40 && !KEY_DATA[1] && !KEY_DATA[2]) {
					counter_test_deno++;
				}
			}
			else if(counter_test_deno == 7) {
				f_led_defrost = 0;
				if(!KEY_DATA[0] && !KEY_DATA[1] && KEY_DATA[2] == 0x04) {
					counter_test_deno++;
				}
				
				value_segment[1] = 0;
				if(KEY_DATA[0] == 0x02 && !KEY_DATA[1] && !KEY_DATA[2])
					value_segment[2] = 1;
				else
					value_segment[2] = 10;
				if(!KEY_DATA[0] && KEY_DATA[1] == 0x40 && !KEY_DATA[2])
					value_segment[3] = 2;
				else
					value_segment[3] = 10;
				if(KEY_DATA[0] == 0x01 && !KEY_DATA[1] && !KEY_DATA[2])
					value_segment[4] = 3;
				else
					value_segment[4] = 10;
			}
			else if(counter_test_deno == 8) {
				if(KEY_DATA[0] == 0x02 && !KEY_DATA[1] && !KEY_DATA[2]) {
					counter_test_deno++;
				}
				
				if(!KEY_DATA[0] && !KEY_DATA[1] && KEY_DATA[2] == 0x04)
					value_segment[1] = 0;
				else
					value_segment[1] = 10;
				value_segment[2] = 1;
				if(!KEY_DATA[0] && KEY_DATA[1] == 0x40 && !KEY_DATA[2])
					value_segment[3] = 2;
				else
					value_segment[3] = 10;
				if(KEY_DATA[0] == 0x01 && !KEY_DATA[1] && !KEY_DATA[2])
					value_segment[4] = 3;
				else
					value_segment[4] = 10;
			}
			else if(counter_test_deno == 9) {
				if(!KEY_DATA[0] && KEY_DATA[1] == 0x40 && !KEY_DATA[2]) {
					counter_test_deno++;
				}
				
				if(!KEY_DATA[0] && !KEY_DATA[1] && KEY_DATA[2] == 0x04)
					value_segment[1] = 0;
				else
					value_segment[1] = 10;
				if(KEY_DATA[0] == 0x02 && !KEY_DATA[1] && !KEY_DATA[2])
					value_segment[2] = 1;
				else
					value_segment[2] = 10;
				value_segment[3] = 2;
				if(KEY_DATA[0] == 0x01 && !KEY_DATA[1] && !KEY_DATA[2])
					value_segment[4] = 3;
				else
					value_segment[4] = 10;
			}
			else if(counter_test_deno == 10) {
				if(KEY_DATA[0] == 0x01 && !KEY_DATA[1] && !KEY_DATA[2]) {
					counter_test_deno++;
				}
				
				if(!KEY_DATA[0] && !KEY_DATA[1] && KEY_DATA[2] == 0x04)
					value_segment[1] = 0;
				else
					value_segment[1] = 10;
				if(KEY_DATA[0] == 0x02 && !KEY_DATA[1] && !KEY_DATA[2])
					value_segment[2] = 1;
				else
					value_segment[2] = 10;
				if(!KEY_DATA[0] && KEY_DATA[1] == 0x40 && !KEY_DATA[2])
					value_segment[3] = 2;
				else
					value_segment[3] = 10;
				value_segment[4] = 3;
			}
			else if(counter_test_deno == 11) {
				f_led_start = 1;
				if(!KEY_DATA[0] && KEY_DATA[1] == 0x20 && !KEY_DATA[2]) {
					counter_test_deno = 0;
					f_key_test = 0;
					f_icon_test = 1;
					f_led_start = 0;
				}
				
				value_segment[1] = 8;
				value_segment[2] = 8;
				value_segment[3] = 8;
				value_segment[4] = 8;
			}
			
			if(counter_test_deno < 7) {
				value_segment[1] = 8; // test
				value_segment[2] = 8; // test
				value_segment[3] = 8; // test
				value_segment[4] = 8; // test
			}
		}
		else if(f_icon_test) {
			value_segment[1] = 10;
			value_segment[2] = 10;
			value_segment[3] = 10;
			value_segment[4] = 10;
			
			counter_test_deno++;
			if(counter_test_deno == 1) { // Lock
				f_icon_lock = 1;
			}
			else if(counter_test_deno == VALUE_SENCOND_0_5) { // Auto
				f_icon_lock = 0;
				f_icon_auto = 1;
			}
			else if(counter_test_deno == VALUE_SENCOND_1_0) { // Cook
				f_icon_auto = 0;
				f_icon_cook = 1;
			}
			else if(counter_test_deno == VALUE_SENCOND_1_5) { // Colon
				f_icon_cook = 0;
				f_colon_show = 1;
			}
			else if(counter_test_deno == VALUE_SENCOND_2_0) { // Alarm
				f_colon_show = 0;
				f_icon_finish_cooking = 1;
			}
			else if(counter_test_deno == VALUE_SENCOND_2_5) { // P
				f_icon_finish_cooking = 0;
				f_icon_Degree_Celsius = 1;
			}
			else if(counter_test_deno == VALUE_SENCOND_3_0) { // All off
				f_icon_Degree_Celsius = 0;
				f_icon_p = 1;
			}
			else if(counter_test_deno == VALUE_SENCOND_3_5) {
				f_icon_p = 0;
				f_icon_test = 0;
				f_test_deno = 0;
				buzzer = BUZ_CONNECT;
			}
		}
	}
	else
		counter_test_deno = 0;
}

uint16_t read_adc(void)
{
	static uint8_t  value_adcl = 0;
	static uint8_t  value_adch = 0;
	static uint16_t value_adc  = 0;
	
	//-------- Triggering the ADC
	_start = 0;
	_start = 1;
	_start = 0;
	while(_adbz);
	
	value_adcl = _sadol;
	value_adch = _sadoh;
	if(value_adcl > _sadol)
	{
		value_adcl = _sadol;
		value_adch = _sadoh;
	}
	value_adc  = value_adch*256 + value_adcl;

	return value_adc;
}

void temperature_calculation(void)
{
	static uint8_t	iteration						= 0;
	static uint8_t	counter_sample					= 0;
	static uint8_t	error_number_temporary			= 0;
	static uint16_t	caviti_temperature_sum			= 0;
	static uint16_t	caviti_adc_temporary			= 0;
	static uint16_t	caviti_temperature_temporary	= 0;
	static double	caviti_temperature_temporary1	= 0;
	static double	caviti_temperature_temporary2	= 0;

	switch(iteration){
		case 0:
			caviti_adc_temporary = read_adc();
	
			if(!error_number) {
				if(caviti_adc_temporary < 100) { // Sensor short circuit
					error_number = 2;
				}
				else if(caviti_adc_temporary > 4070) { // Sensor open circuit
					error_number = 1;
				}
				else { // Normal
					error_number = 0;
				}
			}
			else if(error_number == 1) {
				if(caviti_adc_temporary > 4030) { // It's Cool // Sensor open circuit
					error_number = 1;
				}
				else if(caviti_adc_temporary >= 90) { // Normal
					error_number = 0;
				}
			}
			else if(error_number == 2) {
				if(caviti_adc_temporary < 110) { // It's Heat // Sensor short circuit
					error_number = 2;
				}
				else if(caviti_adc_temporary <= 4050) { // Normal
					error_number = 0;
				}
			}

			if(error_number && (error_number_temporary != error_number)) {
				error_number_temporary = error_number;
				buzzer = BUZ_ERROR;
				error_handle();
			}
			else if(!error_number) {
				if(error_number_temporary) {
					buzzer = BUZ_CONNECT;
				}
				error_number_temporary = 0;
			}
			
			caviti_temperature_temporary1 = (K4*caviti_adc_temporary - K2)/(ADC_MAX_VALUE - caviti_adc_temporary);
			iteration = 1;
			break;
			
		case 1:
			caviti_temperature_temporary2 = T_25*log(caviti_temperature_temporary1) + K3;
			iteration = 2;
			break;
			
		case 2:
			caviti_temperature_temporary = (K1) / (caviti_temperature_temporary2) - T_0 + 1;
	
			if(caviti_temperature_temporary > 254)
				caviti_temperature_temporary = 254;
			else if(caviti_temperature_temporary < 1)
				caviti_temperature_temporary = 1;
			
			if(error_number) {
				caviti_temperature		= 25;
				counter_sample			= 0;
				caviti_temperature_sum	= 0;
			}
			else {
				caviti_temperature_sum += caviti_temperature_temporary;
				counter_sample++;
			
				if(counter_sample == TEMPERATURE_SAMPLE_COUNT) {
					caviti_temperature_temporary		= caviti_temperature_sum / TEMPERATURE_SAMPLE_COUNT;
					counter_sample			= 0;
					caviti_temperature_sum	= 0;
					f_startup_temperature	= 1;
					
					if(f_start) // Predictor
						caviti_temperature = temperature_predictor(caviti_temperature_temporary);
					else
						caviti_temperature = caviti_temperature_temporary;	
				}
			}
			
			iteration = 0;
	}
}

uint8_t controller(int16_t set_point, int16_t process_value, int16_t Tu, int16_t Tl, int16_t Ad_i, int16_t Ad_d, int16_t SAMPLE_COUNT, uint8_t init)
{
	static int16_t dT_i						= 0;
	static int16_t dT_d						= 0;
	
	static int16_t last_process_value		= 0;
	static int16_t value_increment			= 0;
	static int16_t value_decrement			= 0;
	static int16_t sample_count				= 0;
	
	static int16_t controller_output		= 1;

	static int8_t  F_VALUEINCREASING		= 1;
	static int8_t  LAST_F_VALUEINCREASING	= 1;
	static int8_t  F_SAMPLE_COUNT_PASSED	= 0;
	
	if(init) {
		controller_output = (process_value < set_point) ? 1 : 0;
		sample_count      = 0;
		value_increment   = 0;
		value_decrement   = 0;
	}
	
	if(process_value > last_process_value) {
		value_decrement   = 0;
		value_increment   += (process_value - last_process_value);
		F_VALUEINCREASING = 1;
	}
	
	if(process_value < last_process_value) {
		value_increment   = 0;
		value_decrement   += (last_process_value - process_value);
		F_VALUEINCREASING = 0;
	}
	
	sample_count++;
	
	if((sample_count == SAMPLE_COUNT) || F_SAMPLE_COUNT_PASSED) {
		F_SAMPLE_COUNT_PASSED = 1;
		
		if((sample_count == SAMPLE_COUNT) || (LAST_F_VALUEINCREASING != F_VALUEINCREASING)) {
			dT_i = value_increment;
			dT_d = value_decrement;
			sample_count    = 0;
			value_increment = 0;
			value_decrement = 0;
		}
			
		if( (F_VALUEINCREASING && ( process_value < (set_point - Tl - Ad_i*dT_i) ) ) || (!F_VALUEINCREASING && ( process_value < (set_point + Tu + Ad_d*dT_d)) ) ) {
			F_SAMPLE_COUNT_PASSED	= ( controller_output == 0 ) ? 0 : 1;
			sample_count			= ( controller_output == 0 ) ? 0 : sample_count;
			controller_output		= 1;
		} else {
			F_SAMPLE_COUNT_PASSED	= ( controller_output == 1 ) ? 0 : 1;
			sample_count			= ( controller_output == 1 ) ? 0 : sample_count;
			controller_output		= 0;
		}
	}
	
	last_process_value		= process_value;
	LAST_F_VALUEINCREASING	= F_VALUEINCREASING;
	
	return controller_output;
}

uint8_t temperature_predictor(uint8_t temperature)
{
	double temperature_predicted = 0;

	if((cook_mode == BOTH_HEAT) || f_preheat_enable) // Top & Bottom
		temperature_predicted = 1.07*temperature;
	else if(cook_mode == TOP_HEAT) // Top
		temperature_predicted = 1.08*temperature;
	else if((cook_mode == BOTTOM_HEAT) || (((cook_mode == PIZZA) || (cook_mode == CAKE) || (cook_mode == CHICKEN)) && !f_preheat_enable) ) // Bottom
		temperature_predicted = 1.08*temperature;
	else
		temperature_predicted = 1*temperature;

	// Avoiding wrong decisions
	if(temperature_predicted > 254)
		temperature_predicted = 254;
	else if(temperature_predicted < 1)
		temperature_predicted = 1;
	
	return (uint8_t)temperature_predicted;
}

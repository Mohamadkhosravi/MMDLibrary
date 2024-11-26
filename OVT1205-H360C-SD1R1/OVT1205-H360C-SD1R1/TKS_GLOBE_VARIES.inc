; ========================================================================================================================
;// Created by:	Bahram Naseri
;// Copyright:	Deno Electronic
;// Date:		1401/03/28
; ========================================================================================================================
#include "BS66F360.inc"
#define _BS66F360_
#define _V413_
#define SystemClock     2 ; 16MHz
#define IO              0
#define TOUCH           1
#define value           16
; Keys' attribute & settings ...
#define KEY1            TOUCH
#define Key1Threshold   value
#define KEY2            TOUCH
#define Key2Threshold   value
#define KEY3            TOUCH
#define Key3Threshold   value
#define KEY4            TOUCH
#define Key4Threshold   value
#define KEY5            IO
#define Key5Threshold   value
#define KEY6            IO
#define Key6Threshold   value
#define KEY7            TOUCH
#define Key7Threshold   value
#define KEY8            TOUCH
#define Key8Threshold   value
#define KEY9            IO
#define Key9Threshold   value
#define KEY10           IO
#define Key10Threshold  value
#define KEY11           IO
#define Key11Threshold  value
#define KEY12           IO
#define Key12Threshold  value
#define KEY13           IO
#define Key13Threshold  value
#define KEY14           TOUCH
#define Key14Threshold  value
#define KEY15           TOUCH
#define Key15Threshold  value
#define KEY16           TOUCH
#define Key16Threshold  value
#define KEY17           TOUCH
#define Key17Threshold  value
#define KEY18           TOUCH
#define Key18Threshold  value
#define KEY19           TOUCH
#define Key19Threshold  value
#define KEY20           IO
#define Key20Threshold  value
#define KEY21           IO
#define Key21Threshold  value
#define KEY22           IO
#define Key22Threshold  value
#define KEY23           IO
#define Key23Threshold  value
#define KEY24           IO
#define Key24Threshold  value
#define KEY25           IO
#define Key25Threshold  value
#define KEY26           IO
#define Key26Threshold  value
#define KEY27           IO
#define Key27Threshold  value
#define KEY28           IO
#define Key28Threshold  value
#define IO_TOUCH_ATTR   ((KEY1 << 0)|(KEY2 << 1)|(KEY3 << 2)|(KEY4 << 3)|(KEY5 << 4)|(KEY6 << 5)|(KEY7 << 6)|(KEY8 << 7)|(KEY9 << 8)|(KEY10 << 9)|(KEY11 << 10)|(KEY12 << 11)|(KEY13 << 12)|(KEY14 << 13)|(KEY15 << 14)|(KEY16 << 15)|(KEY17 << 16)|(KEY18 << 17)|(KEY19 << 18)|(KEY20 << 19)|(KEY21 << 20)|(KEY22 << 21)|(KEY23 << 22)|(KEY24 << 23)|(KEY25 << 24)|(KEY26 << 25)|(KEY27 << 26)|(KEY28 << 27))
#define IO_TOUCH_ATTR2  0000b
; Components' settings ...
; Global options' settings ...
#define DebounceTimes			1	; 80mS
#define AutoCalibrationPeriod	7	; x 8 (640mS)
#define HighSensitive			0	; uncheck
#define MaximumKeyHoldTime		0	; Disable
#define FastResponse			1	; check
#define AutoFrequencyHopping	1	; check
#define OneKeyActive			0	; uncheck
#define PowerSave				0	; uncheck
#define NoiseProtect			1	; check
#define MovingCalibration		0	; check
#define GlobeOptionA    (DebounceTimes | (AutoCalibrationPeriod << 4))
#define GlobeOptionB    (HighSensitive | (MaximumKeyHoldTime << 4))
#define GlobeOptionC    ((PowerSave << 6) | (NoiseProtect << 4) | (FastResponse << 2) | (AutoFrequencyHopping << 3) | (OneKeyActive << 5) | (MovingCalibration << 7))

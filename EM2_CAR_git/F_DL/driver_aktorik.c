
#include "tiva_headers.h"
#include "driver_aktorik.h"

int setSteerServo;
int setThrottleVal;
int speed_controller_impulse = 0;

void Driver_setSteering(signed char steerVal)
{
    if (steerVal <= 0)
    {
        setSteerServo = ST_MIDDLE + (steerVal * 10);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, setSteerServo);

        if (setSteerServo < ST_maxLeft)
        {
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, ST_maxLeft);
        }
    }
    else if(steerVal > 0)
    {
        setSteerServo = ST_MIDDLE + (steerVal * 10);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, setSteerServo);

        if (setSteerServo < ST_maxRight)
        {
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, ST_maxRight);
        }
    }
}

void Driver_setThrottle(short throttleVal)
{
    if(throttleVal < 0)
    {
        setThrottleVal = MinRPW + throttleVal*25;
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, setThrottleVal);
    }
    else if(throttleVal > 0)
    {
        setThrottleVal = MinFPW + throttleVal*25;
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, setThrottleVal);
    }
    else
    {
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, MaxBreak);
    }
}

void Driver_ESCInit()
{
    createPulses(MaxRPW,131);
    createPulses(MinRPW,128);
    createPulses(MinFPW,128);
    createPulses(MaxFPW,128);

    createPulses(MaxBreak, 50);
}

void createPulses(int pwm, int pulseDuration)
{
    speed_controller_impulse = 0;
    while(speed_controller_impulse <= pulseDuration)
    {
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, pwm);
    }
}

void Driver_PWMServo_ISR(void)
{
    speed_controller_impulse++;
    PWMGenIntClear(PWM1_BASE, PWM_GEN_1, PWM_INT_CNT_ZERO);
}

# ifndef DRIVER_DRIVER_AKTORIK_H_
# define DRIVER_DRIVER_AKTORIK_H_

void Driver_setSteering(signed char steerVal);
void Driver_setThrottle(short);
void Driver_ESCInit();
void createPulses(int pwm, int pulseDuration);
void Driver_PWMServo_ISR(void);

#define ST_MIDDLE 3750      //entspr. 1,5ms
#define ST_maxLeft 2750     //entspr. 1,1ms
#define ST_maxRight 4750    //entspr. 1,9ms

#define MaxRPW 2500     //1000 muS
#define MinRPW 5000     //2000 muS
#define MinFPW 7500     //3000 muS
#define MaxFPW 10000    //4000 muS

#define MaxBreak 6250

# endif /* DRIVER_DRIVER_AKTORIK_H_ */

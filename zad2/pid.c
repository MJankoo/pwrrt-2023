#include <stdio.h>
#include <math.h>

void PID(double Kp, double Ki, double Kd, double dt, double value)
{
    double measurement = 0;
    double error = 0;
    double lastError = 0;

    double integral = 0;
    double derivative = 0;

    int i = 0;
    while (1) {
        error = value - measurement;
        integral += error*dt;
        derivative = (error - lastError)/dt;
        measurement = Kp * error + (Ki * integral) + (Kd * derivative);
        measurement *= 1 - exp(-dt/10);
        if (measurement > 5) {
        	measurement = 5;
        }
        if (measurement < -5) {
        	measurement = -5;
        }
        
        lastError = error;
        
  	printf("%f\n", measurement);
  	fflush(stdout);
 
        usleep((int) (dt * 1000000));
    }
}

int main()
{	
    PID(1, 1, 1, 0.1, 5);
    return 0;
}


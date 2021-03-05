#include <stdio.h>

int t_alarm(float t, float lim) {
	int alarm = 0;
	if (t > lim) {
		alarm = 1;
	}
	return alarm;
}

void main() {
	float lim = 25.6;
	float t = 10;
	while (t <= 35) {
		printf("Temperature %f, alarm %d\n", t, t_alarm(t, lim));
		t = t + 0.5;
	}	
}
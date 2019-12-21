#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void workout(int period);
void timer(int *new_time, int *original_time)
{
	if ((int)time(NULL) != *new_time)
	{
		*new_time = (int)time(NULL);
		printf("%d\n", (int)time(NULL) - *original_time);
	}
}

void alarm(int period)
{
	int alert;
	int alert_time;
	int new_time = 0;
	int original_time = (int)time(NULL);
	// These next 3 lines are used to generate the random time
	srand(time(NULL));
	alert = (int)(rand() % period);
	alert_time = alert + (int)time(NULL);
	while (1)
	{
		// Counts the seconds that have elapsed before it's time to workout
		timer(&new_time, &original_time);
		// If the time equals the random time, notify the user
		if ((int)time(NULL) == alert_time)
		{
			printf("Time to workout!\n");
			break;
		}
	}
	workout(period);
}

void grace_period(int period)
{
	int start = (int)time(NULL);
	int new_time = 0;
	int original_time = (int)time(NULL);
	printf("Beginning of grace period:\n");
	while (1)
	{
		timer(&new_time, &original_time);
		if ((int)time(NULL) - start == 30)
		{
			alarm(period);
		}
	}
}

void workout(int period)
{
	int input;
	// Ask for user input to identify when the workout has completed
	printf("Press any number at the end of your workout to begin your rest. ");
	scanf("%d", &input);
	// Workout is finished. Begin the 30 second grace period
	grace_period(period);
}

int main(void)
{
	int period;
	char ch;
	FILE *ifp = fopen("thefile.txt", "r");
	if (ifp == NULL)
	{
	 printf("Error: Failed to open file!\n");
	 return 0;
	}
	while (fscanf(ifp, "%c", &ch) != EOF)
	{
		printf("%c", ch);
	}
	printf("Interval length: ");
	// Takes the length of intervals from the user
	scanf("%d", &period);
	alarm(period * 60);
	return 1;
}

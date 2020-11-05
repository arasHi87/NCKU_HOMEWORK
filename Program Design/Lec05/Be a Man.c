#include <math.h>
#include <stdio.h>

float bmi;
int year, height, weight, age;

int main() {
	scanf("%d%d%d", &year, &height, &weight);
	printf("Age = %d\n", age=2020-year+1);
	printf("Height = %dcm\n", height);
	printf("Weight = %dkg\n", weight);
	printf("BMI = %.1f\n", bmi=(int)(((float)weight/(pow((float)height/100.0, 2)))*10.0+0.5)/10.0);
	
	if (age<19 || age>36) {
		puts("Not a Draftee (age < 19 or age > 36 years old)");
		printf("No need to perform Military Service");
	} else if (bmi>=17.0 && bmi<=31) {
		puts("Physical Status of Regular Service Draftees");
		
		if (year<=1993) printf("1 year of Regular Service");
		else printf("4 months of Regular Service");
	} else if ((bmi>=16.5 && bmi<17) || (bmi>31 && bmi<=31.5)) {
		puts("Physical Status of Substitute Service Draftees");
		
		if (year<=1993) printf("Substitute Services");
		else printf("Replacement Service");
	} else {
		puts("Physical Status of Military Service Exemption");
		printf("Exemption from Military Service");
	}
}

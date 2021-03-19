package HW1;

import java.lang.Math;
import java.util.Scanner;

public class sol {
	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);

		double a = input.nextDouble();
		double b = input.nextDouble();
		double c = input.nextDouble();

		System.out.println(Math.round(((((c / b) * a) / 0.001) / 30) * 10.0) / 10.0);
	}
}

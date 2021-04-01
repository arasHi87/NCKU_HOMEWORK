package HW3;

import java.util.Scanner;

public class sol {
		public static void main(String[] args) {
		@SuppressWarnings("resource")
		Scanner input = new Scanner(System.in);
		int n = input.nextInt();
		
		for (int i=0;i<=n;i++)
			System.out.format("%d ", calc(n, i));
	}
	
	public static int calc(int r, int n) {
		if (n==0) return 1;
		return calc(r, n-1) * (r - n + 1) / n;
	}
}

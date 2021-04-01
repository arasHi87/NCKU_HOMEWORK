package HW04;

import java.util.Scanner;

public class sol {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		
		int n = input.nextInt();
		int maxN = 10000007;
		int[] prime = new int[maxN];
		
		for (int i=1;i<=n;i++) prime[i]=1;
		
		prime[0] = prime[1] = 0;
		
		for (int i=1;i<=n;i++)
			if (prime[i]==1)
				for (int j=i<<1;j<=n;j+=i)
					prime[j]=0;

		for (int i=n-1;i>=1;i--)
			if (prime[i]==1) {
				System.out.println(i);
				break;
			}
	}

}

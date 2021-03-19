package HW2;

import java.util.Scanner;
import java.util.HashMap;

public class sol {
	public static void main(String args[]) {
		Scanner input = new Scanner(System.in);
		
		int a = input.nextInt();
		int b = input.nextInt();
		char ch = input.next().charAt(0);
		String[] i2s = {"", "one", "two", "three", "four",
				"five", "six", "seven", "eight", "nine"};
		HashMap<Character, String> c2s = new HashMap<Character, String>();
	
		c2s.put('+', "plus");
		c2s.put('-', "minus");
		c2s.put('*', "multiplied by");
		c2s.put('/', "to the power");
		
		if (a<0 || a>9 || b<0 || b>9) System.out.println("invalid number");
		else if (b == 0) System.out.println("division by zero is not allowed");
		else System.out.format("%s %s %s is %d", i2s[a], c2s.get(ch), i2s[b], deal(a, b, ch));
	}
	
	public static int deal(int a, int b, char ch) {
		if (ch == '+') return a+b;
		if (ch == '-') return a-b;
		if (ch == '*') return a*b;
		if (ch == '/') return a/b;
		
		return 87;
	}
}

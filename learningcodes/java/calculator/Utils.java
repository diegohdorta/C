import java.io.*;
import java.util.*;

public class Utils {

	int first, second, result;
	
	public Utils(int f, int s) {
		first = f;
		second = s;
	}

	public int getValue() {
	
		Scanner keyboard = new Scanner(System.in);
		System.out.println("Enter an integer: ");

		while (!keyboard.hasNextInt()) {
			System.out.println("Please enter only numbers: ");
			keyboard.next();
		}
		return keyboard.nextInt();
	}

	public void sum() {
		result = first + second;
	}
}

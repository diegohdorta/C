import java.io.*;
import java.util.*;

public class Calculator {

	public static void main(String[] args) {
	
		System.out.println("Calculator");

		Utils utils = new Utils(10, 10);
		
		//utils.first = utils.getValue();
		//utils.second = utils.getValue();
		
		utils.sum();
		
		System.out.println(utils.result);		
	}
}


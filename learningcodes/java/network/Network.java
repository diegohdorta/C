import java.net.*;
import java.io.IOException;
import java.util.Scanner;

public class Network {

        public static void main (String[] args) throws IOException {

		ServerSocket server = null;
		Socket client = null;

		try {
			server = new ServerSocket(5000);
		} catch (IOException e) {
			e.printStackTrace();
		}

		while (true) {
			try {
				client = server.accept();
			} catch (IOException e) {
				System.out.println("IO error: " + e);
			}
			new ThreadNetwork(client).start();
		}		
	}
}




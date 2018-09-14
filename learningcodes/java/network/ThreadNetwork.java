import java.net.*;
import java.io.*;
import java.util.*;

public class ThreadNetwork extends Thread {

	protected Socket socket;
	
	public ThreadNetwork(Socket client) {
		this.socket = client;
	}

	public void run() {
	
		InputStream input = null;
		BufferedReader buffer = null;
		DataOutputStream out = null;
		
		try {
			input = socket.getInputStream();
			buffer = new BufferedReader(new InputStreamReader(input));
			out = new DataOutputStream(socket.getOutputStream());
		} catch (IOException e) {
			return;
		}
		
		String string;
		
		while(true) {
			try {
				string = buffer.readLine();
				if ((string == null)) {
					socket.close();
					return;
				} 
				else {
					System.out.println(socket.getInetAddress().getHostAddress() + " - Client says: " + string);
					out.writeBytes(string + "\n\r");
					out.flush();
				}
			} catch (IOException e) {
				e.printStackTrace();
				return;			
			}
		}	
		
	}
}

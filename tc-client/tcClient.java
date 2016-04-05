import java.io.*;
import java.net.*;
import java.util.concurrent.TimeUnit;

public class tcClient {
	public static void main(String[] args) throws IOException, InterruptedException {
		PrintWriter writer = new PrintWriter("/Users/Vamsee/Work/GitHub/Linux-Qos/tc-client/queue-udp-under-utilised.txt", "UTF-8");
		for(int i=0;i<300;i++){

			// Initializing variables and sockets
			String serverHostname = new String ("192.168.1.1");
			System.out.println ("Attemping to connect to host " +serverHostname + " on port 9000.");

			Socket clientSocket = null;
			BufferedReader in = null;
			// Making connections and setting up input and output buffered readers
			try {
				clientSocket = new Socket(serverHostname, 9000);
				in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
			} catch (UnknownHostException e) {
				System.err.println("Don't know about host: " + serverHostname);
				System.exit(1);
			} catch (IOException e) {
				System.err.println("Couldn't get I/O for "+ "the connection to: " + serverHostname);
				System.exit(1);
			}
			// Reading the data from the server and printing out
			while( true) {
				String msg = in.readLine();
				if (msg == null) break;	 	
				System.out.println( msg);
				writer.println(msg);
			}
			System.out.println("Connection Terminated");
			in.close();
			clientSocket.close();
//			writer.println("The first line");		
			TimeUnit.MILLISECONDS.sleep(100);

		}
		writer.close();
	}
}

import java.io.*;
import java.net.*;

public class Client {
    public static void main(String[] args) throws IOException {
        
        if (args.length != 2) {
            System.err.println(
                "Uso desde consola: java Cliente_de_Eco <nombre de host (computadora)> <numero puerto>");
            System.exit(1);
        }

        String nombreHost = args[0];
        int numeroPuerto = Integer.parseInt(args[1]);
        int number = 1;

        try (
            Socket socketEco = new Socket(nombreHost, numeroPuerto);
            PrintWriter escritor = new PrintWriter(socketEco.getOutputStream(), true);
            
            BufferedReader lector = new BufferedReader(new InputStreamReader(socketEco.getInputStream()));
            BufferedReader teclado = new BufferedReader( new InputStreamReader(System.in))
        ) {
            String usuarioEscribio = "";
            String recibidoDeServer;
            while (number != 0) {
               usuarioEscribio = teclado.readLine();
               number = Integer.parseInt(usuarioEscribio);
                escritor.println(usuarioEscribio);
                if (number != 0) {
                    recibidoDeServer = lector.readLine();
                    System.out.println("Numero recibido:  " + recibidoDeServer);
                }
            }

            socketEco.close();
        } catch (UnknownHostException e) {
            System.err.println("No conozco al host " + nombreHost);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("no se pudo obtener E/S para la conexion " +
                nombreHost);
            System.exit(1);
        } 
    }
}

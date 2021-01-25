import  tango.core.Thread;
import  tango.io.Console;
import  tango.net.device.Socket;

void main(char[][] args)
{
    	if (args.length != 2)
        {
            Cout("Niepoprawna liczba argumentow - podaj wiadomosc!").newline;
            return;
        }

        const int port = 8080;

        auto request = new Socket;
        request.connect (new IPv4Address("localhost", port));

        char[128] response;
        request.write(args[1]);
        auto len = request.input.read (response);
        Cout ("CLIENT RECEIVED: ")(response[0..len]).newline;

        request.close;
}

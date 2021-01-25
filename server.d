import  tango.core.Thread;
import  tango.io.Console;
import  tango.net.device.Socket;
import Integer = tango.text.convert.Integer;
import tango.text.convert.Format;
import tango.text.convert.Layout;

ServerSocket server;

void main(char[][] args)
{
        if (args.length != 2)
        {
            Cout("Niepoprawna liczba argumentow - podaj liczbe watkow!").newline;
            return;
        }
        auto m = Integer.parse (args[1]);


        server = new ServerSocket (new IPv4Address(8080));
        for (int i = 0; i < m; i++) {
            (new MyThread (i)).start;
        }

}

class MyThread : Thread
{
    int number;

    this(int number)
    {
        this.number = number;
        super( &run );
    }

private :
    void run()
        {
        auto Formatter = Layout!(char).instance;
        auto n = Formatter( "{0}", number);
               while (true) {
                        auto request = server.accept;
                        char[128] message;
                        auto size = request.read(message);
                        Cout ("SERVER ")(n)(" RECEIVED: ")(message[0..size]).newline;
                        request.output.write ("SERVER " ~ n ~ " REPLIES: " ~ message[0..size]);
                }

        }
}

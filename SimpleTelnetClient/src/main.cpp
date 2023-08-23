#include <iostream>

#include "impl/AsioTelnetClient.h"
#include <format>

#ifdef POSIX
#include <termios.h>
#endif

int main(int argc, char* argv[])
{
    // on Unix POXIS based systems, turn off line buffering of input, so cin.get() returns after every keypress
    // On other systems, you'll need to look for an equivalent
#ifdef POSIX
    termios stored_settings;
    tcgetattr(0, &stored_settings);
    termios new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_lflag &= (~ISIG); // don't automatically handle control-C
    tcsetattr(0, TCSANOW, &new_settings);
#endif

    std::string dest_ip;
    std::string dest_port;

    if (argc != 3)
    {
#ifdef WIN32
        dest_ip = "127.0.0.1";
        dest_port = "9105";
#else
        std::cerr << "Usage: telnet <host> <port>\n";
        return 1;
#endif
    }
    else
    {
        dest_ip = argv[1];
        dest_port = argv[2];
    }

    try
    {
        std::cout << "Trying to connect " << dest_ip << ":" << dest_port << std::endl;

        boost::asio::io_service io_service;

        // resolve the host name and port number to an iterator that can be used to connect to the server
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(dest_ip, dest_port);
        tcp::resolver::iterator iterator = resolver.resolve(query);
        // define an instance of the main class of this program

        AsioTelnetClient telnet_client(io_service, iterator);

        telnet_client.setReceivedSocketCallback([](const std::string& message) {
            //std::cout << message;
        });

        telnet_client.setClosedSocketCallback([]() {
            std::cout << " # disconnected" << std::endl;
        });

        int x = 0, y = 0, z = 0;
        int o = 0, a = 0, t = 0;
        std::string cmd;

        telnet_client.write("as\n");

        while (1)
        {
            std::cout << "X: ";
            std::cin >> x;

            std::cout << "Y: ";
            std::cin >> y;

            std::cout << "Z: ";
            std::cin >> z;

            std::cout << "O: ";
            std::cin >> o;

            std::cout << "A: ";
            std::cin >> a;

            std::cout << "T: ";
            std::cin >> t;

            cmd = std::format("do lmove trans({}, {}, {}, {}, {}, {})\n", x, y, z, o, a, t);
            telnet_client.write(cmd);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
#ifdef POSIX // restore default buffering of standard input
    tcsetattr(0, TCSANOW, &stored_settings);
#endif
    return 0;
}

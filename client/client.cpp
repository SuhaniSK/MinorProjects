#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <atomic>

using namespace std;
using boost::asio::ip::tcp;

// Function to handle receiving data from the server
void receive_data(tcp::socket& socket, atomic<bool>& running) {
    try {
        while (running) {
            boost::asio::streambuf buffer;
            boost::asio::read_until(socket, buffer, "\n");
            istream is(&buffer);
            string line;
            getline(is, line);
            cout << "Received: " << line << endl;
        }
    } catch (const std::exception& e) {
        if (running) {
            cerr << "Exception: " << e.what() << "\n";
        }
    }
}

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "12345");

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        cout << "Connected to server." << endl;

        atomic<bool> running(true);

        // Start a thread to receive data from the server
        thread receiver(receive_data, std::ref(socket), std::ref(running));

        // Main loop to read user input
        while (true) {
            string input;
            getline(cin, input);

            if (input == "logout") {
                running = false;
                boost::asio::write(socket, boost::asio::buffer(input + "\n"));
                break;
            }

            boost::asio::write(socket, boost::asio::buffer(input + "\n"));
        }

        receiver.join();
    } catch (const std::exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <mutex>
#include <fstream>
#include <ctime>

using namespace std;
using boost::asio::ip::tcp;

// Global variables for logging client times
unordered_map<string, chrono::system_clock::time_point> client_login_times;
mutex mtx;

// Function to log client login and logout times
void log_time(const string& client, const string& action) {
    lock_guard<mutex> lock(mtx);
    auto now = chrono::system_clock::now();
    auto login_time = chrono::system_clock::to_time_t(now);
    ofstream logfile("server_log.txt", ios_base::app);
    logfile << client << " " << action << " at " << ctime(&login_time);
}

// Function to handle client connections
void handle_client(tcp::socket socket) {
    try {
        // Get client address
        string client_address;
        try {
            client_address = socket.remote_endpoint().address().to_string();
        } catch (const boost::system::system_error& e) {
            cerr << "Error getting client address: " << e.what() << "\n";
            return;
        }

        {
            lock_guard<mutex> lock(mtx);
            client_login_times[client_address] = chrono::system_clock::now();
        }
        log_time(client_address, "logged in");

        while (true) {
            // Read data from client
            char data[1024];
            boost::system::error_code error;
            size_t length = socket.read_some(boost::asio::buffer(data), error);

            if (error == boost::asio::error::eof) {
                break; // Connection closed cleanly by peer.
            } else if (error) {
                throw boost::system::system_error(error); // Some other error.
            }

            // Process data (for demonstration, just echo back)
            boost::asio::write(socket, boost::asio::buffer(data, length));

            // Send real-time data to client
            string message = "Real-time data: " + to_string(chrono::system_clock::now().time_since_epoch().count()) + "\n";
            boost::asio::write(socket, boost::asio::buffer(message));
        }
    } catch (const std::exception& e) {
        cerr << "Exception in thread: " << e.what() << "\n";
    }

    // Log client exit
    string client_address;
    try {
        client_address = socket.remote_endpoint().address().to_string();
    } catch (const boost::system::system_error& e) {
        cerr << "Error getting client address: " << e.what() << "\n";
        return;
    }
    log_time(client_address, "logged out");
}

int main() {
    try {
        // Create an io_context for I/O operations
        boost::asio::io_context io_context;

        // Create an acceptor to listen for incoming connections on port 12345
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));

        cout << "Server started, waiting for connections..." << endl;

        // Continuously accept new connections
        while (true) {
            // Create a socket for the new connection
            tcp::socket socket(io_context);
            
            // Wait for a client to connect
            acceptor.accept(socket);
            cout << "Client connected." << endl;
            
            // Start a new thread to handle the connection and stream data
            thread(handle_client, std::move(socket)).detach();
        }
    } catch (const std::exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

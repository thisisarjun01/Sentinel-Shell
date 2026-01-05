#include<iostream>
#include<sstream>
#include<ctime>
using namespace std;
int main()
{
    string input;
    cout << "========================================" << endl;
    cout << "   SENTINEL SHELL v1.0 - Day 5 Edition  " << endl;
    cout << "   Type 'help' to see commands.         " << endl;
    cout << "========================================" << endl;
    
    while(true)
    {
        cout<<"Sentinel>";
       if (!getline(cin,input)) break;
       if (input.empty()) continue;

        stringstream ss(input);
        string command;
        ss >> command;

	for (char &ch : command) {
    	ch = tolower(ch);
	}

        if(command == "exit") {
            break;
        }
        else if(command == "about") {
            cout << R"(
  _____            _   _            _ 
 / ____|          | | (_)          | |
| (___   ___ _ __ | |_ _ _ __   ___| |
 \___ \ / _ \ '_ \| __| | '_ \ / _ \ |
 ____) |  __/ | | | |_| | | | |  __/ |
|_____/ \___|_| |_|\__|_|_| |_|\___|_|
            Built by: Rohit (@thisisrohit01)
            )" << endl;
        }
        else if(command == "date") {
            time_t now = time(0);
            char* dt = ctime(&now);
            cout << "Current System Time: " << dt;
        }
        else if(command == "clear") {
            system("clear");
        }
        else if(command == "help") {
            cout << "Available commands: about, date, say, clear, exit" << endl;
        }
        else if(command == "say") {
            string remainder;
            ss >> ws;
            getline(ss, remainder);
            cout << remainder << endl;
        }
        else {
            cout << "sentinel: command not found: " << command << endl;
        }
    }
    return 0;
}
    

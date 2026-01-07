#include<iostream>
#include<fstream>
#include<sstream>
#include<ctime>
#include<cctype>
using namespace std;
int main()
{
    string input;
    while(true)
    {
        cout<<"sentinel>";
        if(!getline(cin,input))break;
        if(input.empty())continue;

        string command;
        stringstream ss(input);
        ss>>command;

        for(char &ch : command)
        {
            ch = tolower(ch);
        }

        if (command=="exit")
        {
            break;
        }
        else if(command=="help")
        {
            cout<<"available command: say ,clear ,time ,help ,create ,write, about ,exit,read"<<endl;
        }
        else if (command == "about")
        {
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
        else if(command=="time")
        {
            time_t now=time(0);
            char* dt =ctime(&now);
            cout<<"current system time: "<<dt<<endl;
        }   
        else if(command=="clear")
        {
            system("clear");
        }   
        else if(command=="say")
        {
            ss>>ws;
            string remainder;
            getline(ss,remainder);
            cout<<remainder<<endl;
        }
        else if(command=="create")
        {
            string fileName;
            ss>>fileName;
            ofstream file(fileName);
            if(file)
            {
                cout<<"Successfully created file: "<<fileName<<endl;
                file.close();
            } 
            else
            {
                cout<<"Error in creating file: "<<fileName<<endl;
            }
        }
        else if(command=="write")
        {
            string fileName;
            ss>>fileName;

            string content;
            ss>>ws;
            getline(ss,content);

            ofstream file(fileName,ios::app);
            if(file)
            {
                file<<content<<endl;
                cout<<"written to file: "<<fileName<<endl;
            }
            else
            {
                cout<<"error could not write in file: "<<fileName<<endl;
            }
        }
        else if(command=="read")
        {
            ss>>ws;
            string fileName;
            ss>>fileName;

            string myText;
            ifstream file(fileName);
            if (!file.is_open()) { cout << "File not found!"; }
            while(getline(file,myText))
            {
                cout<<myText<<endl;
            }
        }
        else
        {
            cout<<"sentinel command not found"<<endl;
        }


    }
    return 0;
}

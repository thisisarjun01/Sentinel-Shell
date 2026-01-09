#include<iostream>
#include<fstream>
#include<sstream>
#include<ctime>
#include<cctype>
#include<filesystem>
#include<vector>
namespace fs=std::filesystem;
using namespace std;
int main()
{
    string input;
    vector<string> history;
    while(true)
    {
        cout<<"sentinel>"<<fs::current_path().string() <<"> ";
        if(!getline(cin,input))break;
        if(input.empty())continue;

        history.push_back(input);

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
            cout<<"available command: say ,clear ,time ,help ,create ,write, about ,read ,delete.list ,history ,cd ,exit"<<endl;
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
        else if(command=="list")
        {
            cout<<"Listing files in current directory : "<<endl;
            for(const auto & entry :fs::directory_iterator("."))
            {
                cout<<" -"<<entry.path().filename().string()<<endl;
            }
        }
        else if (command=="delete")
        {
            string fileName;
            ss>>fileName;
            if(fs::remove(fileName))
            {
                cout<<"Successfully deleted file: "<<fileName<<endl;
            }
            else
            {
                cout<<"error: file'"<<fileName<<"' not found"<<endl;
            }
        }
        else if(command=="history")
        {
            if (history.empty()){
                cout<<"No commands entered yet"<<endl;
            }
            else
            {
                for(size_t i=0;i<history.size();++i)
                {
                    cout<<i+1<<" "<<history[i]<<endl;
                }
            }
        }
        else if(command=="cd")
        {
            string path;
            ss>>path;
            try
            {
                fs::current_path(path);
            }
            catch(const fs::filesystem_error& e)
            {
                std::cerr <<"Error: "<<e.what() <<endl;
            }
            
        }
        else
        {
            cout<<"sentinel command not found"<<endl;
        }
        



    }
    return 0;
}

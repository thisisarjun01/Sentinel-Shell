#include<iostream>
#include<fstream>
#include<sstream>
#include<ctime>
#include<cctype>
#include<filesystem>
#include<vector>
#include<cstdlib>
#include<map>
namespace fs=std::filesystem;
using namespace std;
#define RESET   "\033[0m"
#define GREEN   "\033[32m"     
#define BLUE    "\033[34m"     
#define RED     "\033[31m"     
#define MAGENTA "\033[35m"  

#ifdef _WIN32
    #include <process.h>
    #define environ _environ 
#else
    extern char **environ; 
#endif

void loadHistory(vector<string>& history) {
    ifstream file(".sentinel_history");
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            history.push_back(line);
        }
        file.close();
    }
}
void saveToHistoryFile(const string& input) {
    ofstream file(".sentinel_history", ios::app);
    if (file.is_open()) {
        file << input << endl;
        file.close();
    }
}
string getUsername() {
    char* user = getenv("USER");      
    if (user == nullptr) {
        user = getenv("USERNAME");  
    }
    return (user != nullptr) ? string(user) : "user";
}
void logError(const string& errorMessage) {
    ofstream logFile(".sentinel_log", ios::app); 
    if (logFile.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now);
        string timestamp(dt);
        timestamp.pop_back(); 

        logFile << "[" << timestamp << "] ERROR: " << errorMessage << endl;
        logFile.close();
    }
}
int main()
{
    string promptColor = MAGENTA;
    string pathColor = BLUE;
    string input;
    vector<string> history;
    loadHistory(history);
    string username = getUsername();
    map<string, string> aliases = {
    {"ls", "list"},
    {"h", "history"},
    {"cls", "clear"},
    {"md", "mkdir"},
    {"rd", "rmdir"}
};
    while(true)
    {
        cout << promptColor << username << "@sentinel" << RESET << ":" << pathColor << fs::current_path().string() << RESET << "> ";
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
              
        if (aliases.count(command)) {
            command = aliases[command];
        }
        
        if (command != "history" && !input.empty()) {
            saveToHistoryFile(input);
        }
        
        if (command=="exit")
        {
            break;
        }
        else if (command == "theme") {
            string colorChoice;
            if (!(ss >> colorChoice)) {
                cout << "Usage: theme <red|green|blue|magenta|cyan|yellow>" << endl;
            } else {
                for (char &c : colorChoice) c = tolower(c);
                
                if (colorChoice == "red") promptColor = RED;
                else if (colorChoice == "green") promptColor = GREEN;
                else if (colorChoice == "blue") promptColor = BLUE;
                else if (colorChoice == "magenta") promptColor = MAGENTA;
                else if (colorChoice == "cyan") promptColor = "\033[36m";
                else if (colorChoice == "yellow") promptColor = "\033[33m";
                else cout << RED << "Unknown color choice!" << RESET << endl;
                
                cout << "Theme updated!" << endl;
            }
        }
        else if(command=="help")
        {
            cout << "\n--- Sentinel Built-in Commands ---" << endl;
            cout << "File Ops:  create, write, read, delete, list, mkdir, rmdir, export, lock, info" << endl;
            cout << "System:    cd, time, clear, history, about, stats, sysinfo, env" << endl;
            cout << "Utils:     say, help, exit, theme" << endl;
            cout << "External:  Any system command (e.g., python, mkdir)\n" << endl;
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
            #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
}
            else if (command == "export") {
            string exportFileName;
            if (!(ss >> exportFileName)) {
                cout << RED << "Error: Provide a filename (e.g., export my_session.txt)" << RESET << endl;
            } else {
                ofstream outFile(exportFileName);
                if (outFile.is_open()) {
                    outFile << "# Sentinel Session Export - " << __DATE__ << endl;
                    for (const auto& cmd : history) {
                        outFile << cmd << endl;
                    }
                    outFile.close();
                    cout << GREEN << "Session history exported to " << exportFileName << RESET << endl;
                } else {
                    cout << RED << "Error: Could not create export file." << RESET << endl;
                }
            }
        }
        else if (command == "lock") {
            string fileName;
            int key;
            if (!(ss >> fileName >> key)) {
                cout << RED << "Usage: lock <filename> <numeric_key>" << RESET << endl;
            } else {
                ifstream inFile(fileName, ios::binary);
                if (!inFile) {
                    cout << RED << "Error: File not found." << RESET << endl;
                } else {
                    
                    string content((istreambuf_iterator<char>(inFile)), (istreambuf_iterator<char>()));
                    inFile.close();
                
                    for (char &c : content) {
                        c ^= key; 
                    }

                    ofstream outFile(fileName, ios::binary);
                    outFile << content;
                    outFile.close();

                    cout << GREEN << "File '" << fileName << "' processed with key " << key << RESET << endl;
                    cout << MAGENTA << "Note: Use the same command and key to unlock it." << RESET << endl;
                }
            }
        }
        else if (command == "info") {
            string fileName;
            if (!(ss >> fileName)) {
                cout << RED << "Usage: info <filename>" << RESET << endl;
            } else if (!fs::exists(fileName)) {
                cout << RED << "Error: File does not exist." << RESET << endl;
            } else {
                auto path = fs::path(fileName);
                
                
                auto ftime = fs::last_write_time(path);
                
                auto sctp = chrono::time_point_cast<chrono::system_clock::duration>(
                            ftime - decltype(ftime)::clock::now() + chrono::system_clock::now());
                time_t cftime = chrono::system_clock::to_time_t(sctp);

                auto perms = fs::status(path).permissions();
                
                cout << "\n--- File Information: " << fileName << " ---" << endl;
                cout << "Full Path: " << fs::absolute(path).string() << endl;
                cout << "Size:      " << fs::file_size(path) << " bytes" << endl;
                cout << "Modified:  " << asctime(localtime(&cftime));
                
                cout << "Access:    ";
                cout << ((perms & fs::perms::owner_read) != fs::perms::none ? "R" : "-");
                cout << ((perms & fs::perms::owner_write) != fs::perms::none ? "W" : "-");
                cout << "\n------------------------------------" << endl;
            }
        }
	else if (command == "sysinfo") {
            cout << "\n--- Sentinel System Report ---" << endl;
            cout << "OS:       ";
            #ifdef _WIN32
                cout << "Windows (64-bit/32-bit)" << endl;
            #elif __APPLE__
                cout << "macOS / OSX" << endl;
            #elif __linux__
                cout << "Linux Kernel" << endl;
            #else
                cout << "Unknown OS" << endl;
            #endif

            cout << "Arch:     ";
            #if defined(__x86_64__) || defined(_M_X64)
                cout << "x86_64 (Intel/AMD)" << endl;
            #elif defined(__aarch64__) || defined(_M_ARM64)
                cout << "ARM64 (Apple Silicon/Snapdragon)" << endl;
            #else
                cout << "Standard 32-bit / Other" << endl;
            #endif

            // System Time
            time_t now = time(0);
            cout << "Kernel Time: " << ctime(&now);
            cout << "------------------------------" << endl;
        }
	else if (command == "run") {
            string scriptName;
            if (!(ss >> scriptName)) {
                cout << RED << "Error: Provide a script file name (e.g., run setup.txt)" << RESET << endl;
            } else {
                ifstream scriptFile(scriptName);
                if (!scriptFile.is_open()) {
                    cout << RED << "Error: Could not open script file '" << scriptName << "'" << RESET << endl;
                } else {
                    string scriptLine;
                    cout << MAGENTA << "Executing script: " << scriptName << "..." << RESET << endl;
                    while (getline(scriptFile, scriptLine)) {
                        if (scriptLine.empty() || scriptLine[0] == '#') continue;
                        cout << BLUE << " > " << RESET << scriptLine << endl;
                        system(scriptLine.c_str()); 
                    }
                    cout << GREEN << "Script execution finished." << RESET << endl;
                }
            }
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
        else if(command == "list")
{
    cout << "Type\tSize\t\tName" << endl;
    cout << "----\t----\t\t----" << endl;
    
    for(const auto & entry : fs::directory_iterator("."))
    {
        auto path = entry.path();
        string name = path.filename().string();
        
        if (fs::is_directory(path)) {
            cout << "[DIR]\t---\t\t" << BLUE << name << RESET << endl;
        } else {
            // Convert bytes to KB for readability
            uintmax_t size = fs::file_size(path) / 1024; 
            cout << "[FILE]\t" << size << " KB\t\t" << name << endl;
        }
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
        else if (command == "mkdir")
        {
            string dirName;
            if (!(ss >> dirName)) {
                cout << RED << "Error: Provide a directory name." << RESET << endl;
            } else {
                if (fs::create_directory(dirName)) {
                    cout << "Successfully created directory: " << dirName << endl;
                } else {
                    cout << RED << "Error: Could not create directory (it might already exist)." << RESET << endl;
                }
            }
        }
        else if (command == "rmdir")
        {
            string dirName;
            if (!(ss >> dirName)) {
                cout << RED << "Error: Provide a directory name." << RESET << endl;
            } else {
                if (fs::remove_all(dirName) > 0) {
                    cout << "Successfully removed directory and its contents: " << dirName << endl;
                } else {
                    cout << RED << "Error: Directory not found or could not be removed." << RESET << endl;
                }
            }
        }
        else if (command == "stats") {
            try {
                
                fs::space_info si = fs::space(".");

                
                double total = static_cast<double>(si.capacity) / (1024 * 1024 * 1024);
                double available = static_cast<double>(si.available) / (1024 * 1024 * 1024);
                double used = total - available;

                cout << "\n--- Drive Statistics ---" << endl;
                cout << "Total Capacity: " << total << " GB" << endl;
                cout << "Used Space:     " << used << " GB" << endl;
                cout << "Free Available: " << available << " GB" << endl;
                
                
                double percentUsed = (used / total) * 100;
                cout << "Disk Usage:     " << percentUsed << "%" << endl;
            }
            catch (const fs::filesystem_error& e) {
                cout << RED << "Error fetching disk stats: " << e.what() << RESET << endl;
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
        else if (command == "search") {
    string target;
    if (!(ss >> target)) {
        cout << RED << "Error: Provide a search term." << RESET << endl;
    } else {
        try {
            bool found = false;
            
            for (const auto& entry : fs::recursive_directory_iterator(".")) {
                if (entry.path().filename().string().find(target) != string::npos) {
                    cout << GREEN << "[FOUND] " << RESET << entry.path().string() << endl;
                    found = true;
                }
            }
            if (!found) cout << "No matches found." << endl;
        } 
        
        catch (const fs::filesystem_error& e) {
            cout << RED << "Access Error: " << e.what() << RESET << endl;
        }
        
        catch (const exception& e) {
            cout << RED << "Unexpected Error: " << e.what() << RESET << endl;
        }
    }
}
        else if (command == "grep") {
            string target;
            if (!(ss >> target)) {
                cout << RED << "Usage: grep <keyword>" << RESET << endl;
            } else {
                bool foundAny = false;
                cout << "Searching for content: '" << target << "'..." << endl;

                for (const auto& entry : fs::directory_iterator(".")) {
                    if (fs::is_regular_file(entry.path())) {
                        ifstream file(entry.path());
                        string line;
                        int lineNum = 1;
                        
                        while (getline(file, line)) {
                            if (line.find(target) != string::npos) {
                                cout << GREEN << "[MATCH] " << RESET 
                                     << entry.path().filename().string() 
                                     << " (Line " << lineNum << "): " << line << endl;
                                foundAny = true;
                            }
                            lineNum++;
                        }
                    }
                }
                if (!foundAny) {
                    cout << MAGENTA << "No files contain the keyword: " << target << RESET << endl;
                }
            }
        }
        else if (command == "env") {
            cout << "\n--- System Environment Variables ---" << endl;
            for (char **env = environ; *env != 0; env++) {
                cout << BLUE << *env << RESET << endl;
            }
            cout << "------------------------------------" << endl;
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
        else {
            int result = system(input.c_str());
            if(result != 0) {
                string err = "Unrecognized command: " + command;
                cout << RED << "sentinel: '" << command << "' is not recognized." << RESET << endl;
                logError(err);
            }
        }
    }
    return 0;
}

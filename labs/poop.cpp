#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <string>

//fork.
//exec.
#include <unistd.h>

//wait
#include <sys/types.h>
#include <sys/wait.h>

#include "Com.h"

#include "boost/algorithm/string.hpp"
#include "boost/tokenizer.hpp"
#include "boost/foreach.hpp"

using namespace std;
using namespace boost;

//forking of child and executing command in child.
void execute(char* args[]);

//split string into pieces and store in vector.
void seperate(vector<Com> &v, string s);

//takes in vector of strings and modifies a char* name[].
char* convert(const vector<string> &v);


int main()
{

    //login.
    char* login = getlogin();
    bool login_check = true;
    if((!login) != 0)
    {
        login_check = false;
        //cout << "Error could not retrieve login name." << endl;
        perror("Error could not retrieve login name.");
    }

    //host name.
    char host[150];
    bool host_check = true;
    if(gethostname(host,sizeof(host)) != 0)
    {
        host_check = false;
        //cout << "Error could not retrieve host name." << endl;
        perror("Error could not retrieve host name.");
    }

    //warn user that not all info will come out.
    if(login_check == false || host_check == false)
        cout << "Unable to display login and host information." << endl;

    //user input.
    string input;

    //place to store all actions.
    vector<Com> commands;

    //c-string to hold string command.
    //char* c_inp[2048];

    //main loop.
    while(true)
    {
        //command line prompt.
        if(login_check && host_check)
            cout << login << '@' << host << ' ';

        //bash money.
        cout << "$ ";

        //input line.
        getline(cin,input);

        //get rid of unwanted space.
        trim(input);

        //break out of loop if exit. (temp).
        if(input == "exit")
            exit(0);

        //seperate(commands,input);

        // cout << endl << endl;
        // for(int i = 0; i < commands.size(); ++i)
        //     cout << i + 1 << ": " << commands.at(i) << endl;
        // cout << endl;

        //converts to c-string.
        // for(int i = 0; i < commands.size(); ++i)
        //     c_inp[i] = (char*)commands.at(i).c_str();
        // c_inp[commands.size()] = NULL;

        //execute(c_inp);

        //clearing stuff.
        cin.clear();
        input.clear();
        commands.clear();

    }

    cout << endl << "--------------------" << endl;
    cout << "ending program" << endl;
    cout << "--------------------" << endl << endl;

    return 0;
}

void seperate(vector<Com> &v, string s)
{

    char_separator<char> sep("&&");
    tokenizer< char_separator<char> > tokens(s, sep);
    BOOST_FOREACH (const string& t, tokens)
    {
        Com temp;
        cout << " (" << t << ") " << endl;
        temp.push_back(t);
        temp.display();
    }

}

void execute(char* args[])
{
    pid_t pid = fork();

    if(pid == -1)
    {
        //error code.
        perror("fork");
    }
    if(pid == 0)
    {
        //child.
        //cout << "Child: " << pid << endl;

        if(execvp(args[0], args) == -1)
        {
            perror("execvp");

            //kill ghost process.
            exit(1);
        }

    }
    if(pid > 0)
    {
        //parent.

        if(wait(0) == -1)
            perror("wait");

        //cout  << "Parent: " << pid << endl;

    }

    return;
}

// CommandLineParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CommandLineParser.h"
#include "C:\Users\Steven_dev\Desktop\CS_Stuff\TableClass\TableClass\TableClass\Table.h"
using namespace std;

int main() 
{
    char s[] = "select first,name,age from other where age < 30 or name = chris ";
    Parser p(s);
    MMap<string,string> ptree = p.parse_tree();
    if (ptree["command"][0] == "select") {
        string table_name = ptree["table"][0];
        //Table t(table_name);

    }
}
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>
//#include <cstring>

#include "../include/sup.h"
#include "../shapes/shapes"

using namespace std;

void solve_nonlinear_system(sPoint p01, int r1, sPoint p02, int r2, 
sPoint *res1_p1, sPoint *res1_p2, 
sPoint *res2_p1, sPoint *res2_p2, 
sPoint *res3_p1, sPoint *res3_p2, 
sPoint *res4_p1, sPoint *res4_p2
)
{
    const char* fileName = "crutch_file";
    const string pyFileName = "./tools/crutch.py";

    ifstream myfile;
    string buffS;

    ostringstream sys_command;

    sys_command << "python" << " " << pyFileName << " ";
    sys_command << p01.getX() << " " << p01.getY() << " ";
    sys_command << p02.getX() << " " << p02.getY() << " ";
    sys_command << r1 << " " << r2 << " ";
    sys_command << fileName;

    system(sys_command.str().c_str());

    //system("python pr.py 29 181 41 139 23 13 file");
    //system("python pr.py 7 11 97 101 13 17 file");

    while(1)
    {
        buffS = "";
        myfile.open(fileName, ios::in);
        //myfile >> buffS;
        buffS.assign( (std::istreambuf_iterator<char>(myfile) ),
                (std::istreambuf_iterator<char>()    ) );

        myfile.close();
        if(buffS != "")
            break;
    }

/*
rootNum
x1 y1 x2 y2
x1 y1 x2 y2
x1 y1 x2 y2
x1 y1 x2 y2
*/
    myfile.open(fileName, ios::in);
    int rootNum, xbuff, ybuff;
    myfile >> rootNum;
    if(rootNum >= 1)
    {
        myfile >> xbuff;
        myfile >> ybuff;
        (*res1_p1).setX(xbuff);
        (*res1_p1).setY(ybuff);
        myfile >> xbuff;
        myfile >> ybuff;
        (*res1_p2).setX(xbuff);
        (*res1_p2).setY(ybuff);
    }
    if(rootNum >= 2)
    {
        myfile >> xbuff;
        myfile >> ybuff;
        (*res2_p1).setX(xbuff);
        (*res2_p1).setY(ybuff);
        myfile >> xbuff;
        myfile >> ybuff;
        (*res2_p2).setX(xbuff);
        (*res2_p2).setY(ybuff);
    }
    if(rootNum >= 3)
    {
        myfile >> xbuff;
        myfile >> ybuff;
        (*res3_p1).setX(xbuff);
        (*res3_p1).setY(ybuff);
        myfile >> xbuff;
        myfile >> ybuff;
        (*res3_p2).setX(xbuff);
        (*res3_p2).setY(ybuff);
    }
    if(rootNum >= 4)
    {
        myfile >> xbuff;
        myfile >> ybuff;
        (*res4_p1).setX(xbuff);
        (*res4_p1).setY(ybuff);
        myfile >> xbuff;
        myfile >> ybuff;
        (*res4_p2).setX(xbuff);
        (*res4_p2).setY(ybuff);
    }

    myfile.close();

    ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    cout << "\"" << buffS << "\"" << endl;
}

int rightRound(double num)
{
    return (int)(num<0?num-0.5:num+0.5);
}
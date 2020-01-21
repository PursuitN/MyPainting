#ifndef CMDCONTROL_H
#define CMDCONTROL_H

#include<QString>
#include<cstring>
#include<iostream>
#include<fstream>
using namespace std;
#include<QDebug>
#include<vector>
#include<sstream>


class cmdcontrol{

private:
    string readfromPath;                //存储命令待执行的文件路径
    string savetoPath;                  //生成位图需要保存的路径
    vector<string> cmdPacket;           //存储读到的cmd指令


public:
    cmdcontrol();
    void setreadPath(string r);             //设置读取的文件路径
    void setsavePath(string s);             //设置保存生成图像的路径
    void readCmd();                         //读取文件中每个指令并存储
    vector<string> cmdtheOne(string sen);  //对传入的一句话进行解析
    vector<string> getPacket();            //获得cmdpacket
    string getSavepath();              //获得QString savetoPath;
};

#endif // CMDCONTROL_H

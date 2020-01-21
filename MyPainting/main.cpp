#include<QApplication>
#include<QLabel>

#include"mainwindow.h"

#include<iostream>
#include<fstream>
#include<string>
#include<bits/stdc++.h>
#include"cmdcontrol.h"


int main(int argc,char *argv[]){

    /* 这是学习qt入门的尝试代码
    QLabel *label = new QLabel("hello QT");
    label->show();
    */

    /* 增加主界面对象 */
    if(argc==1){
         QApplication painting(argc,argv);
        MainWindow window;
        window.show();

        return painting.exec();
    }

    else{

        argv[1]="E:/CUR/computergraph/MyPainting/cmd/input.txt";
        argv[2]="E:/CUR/computergraph/MyPainting/cmd";
        //argv[1]="..\\MyPainting\\cmd\\input.txt";
        //argv[2]="\\cmd";

//        argv[1]="E:\CUR\computergraph\MyPainting\cmd\input.txt";
//        argv[2]="E:\CUR\computergraph\MyPainting\cmd";

//        char *p=argv[1];
//        string s1=argv[1];
//        string tmp1="";
//        for(int i=0;i<s1.length();i++){
//            cout<<p[i]<<endl;
//            if(p[i]=='\\'){
//                  tmp1+="\\";
//             }
//            else{
//                tmp1+=p[i];
//            }
//        }
//        cout<<tmp1<<endl;

        cmdcontrol cmdfunc;
        cmdfunc.setreadPath(argv[1]);
        cmdfunc.setsavePath(argv[2]);
        cmdfunc.readCmd();

        QApplication painting(argc,argv);
        MainWindow window(nullptr,&cmdfunc);

        return 0;
    }
}

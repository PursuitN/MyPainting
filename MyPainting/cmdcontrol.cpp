#include"cmdcontrol.h"


cmdcontrol::cmdcontrol(){

}



void cmdcontrol::setreadPath(string r){
    readfromPath=r;
}

void cmdcontrol::setsavePath(string s){
    savetoPath=s;
}


void cmdcontrol::readCmd(){

    ifstream myf;
    myf.open(readfromPath);

    if(!myf.is_open()){
        qDebug()<<"Open file failed."<<endl;
    }
    else{
        while(!myf.eof()){
            string oneline;
            getline(myf,oneline);
            cmdPacket.push_back(oneline);
        }
    }

//    for(int i=0;i<cmdPacket.size();i++){
//        cout<<cmdPacket[i]<<endl;
//    }
//    cmdtheOne(cmdPacket[0]);

}

vector<string> cmdcontrol::cmdtheOne(string sen){

    vector<string>oneword;
    istringstream iss;
    iss.str(sen);
    string tmp;
    while(iss>>tmp){
        oneword.push_back(tmp);
    }
    return oneword;
//    for(int i=0;i<oneword.size();i++){
//        cout<<oneword[i]<<endl;
//    }

}

vector<string> cmdcontrol::getPacket(){
    return cmdPacket;
}

string cmdcontrol::getSavepath(){
    return savetoPath;
}


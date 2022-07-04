#include <iostream>
#include <fstream>
using namespace std;
void initM(int **,int);//初始化矩阵
void initMbyInput(int **,int);//根据输入初始化矩阵
void initMbyFile(int **,int);
void dispM(int **,int);//打印矩阵
void delM(int **,int);//清除动态数组
int** cloneM(int **,int);//为不改变原矩阵，创建一个相同的矩阵
void reflexive(int **,int);//自反
void symmetric(int **,int);//对称
void transitive(int **,int);//传递
int main(){
    int d=0;
    cout<<"Please input the order of the matrix :";//输入矩阵阶数
    cin>>d;
    int **m=new int*[d];
    for(int i=0;i<d;i++){
        m[i]=new int[d];//分别创建一维动态数组
    }
    initM(m,d);//从文件或标准输入初始化
    cout<<"The raw matrix:"<<endl;
    dispM(m,d);//显示原始矩阵
    reflexive(m,d);//显示其自反闭包
    symmetric(m,d);//显示其对称闭包
    transitive(m,d);//显示其传递闭包
    delM(m,d);//删除原数组
    return 0;
}
void initM(int ** m,int d){
    char useFile;
    cout<<"Load from file?[y/N]";
    cin.get();
    cin.get(useFile);
    switch(useFile){//y或者Y来从文件读取
			case'Y':
			case'y':initMbyFile(m,d);break;
			case'n':
			case'N':
			default:initMbyInput(m,d);
	}
}
void initMbyInput(int ** m,int d){
    cout<<"Please input every value, spliting with space or enter ("<<d<<"*"<<d<<"="<<d*d<<")"<<endl;
    for(int i=0;i<d;i++){
        for(int j=0;j<d;j++)
            cin>>m[i][j];//获取用户输入并写入数组
    }
}
void initMbyFile(int ** m,int d){
    char filename[100];
    cout<<"Please input the name of your file(default: example.txt):";
    cin.get();
    cin.getline(filename,100,'\n');
    ifstream infile;
    if(filename[0]=='\0'){//默认使用example.txt
        cout<<"Loading from example.txt"<<endl;
        infile.open("example.txt",ios::in);
    }
    else{
        cout<<"Loading from "<<filename<<"..."<<endl;
        infile.open(filename,ios::in);
    }
    if(infile){
        cout<<"File Loaded successfully!"<<endl;
        for(int i=0;i<d;i++){
            for(int j=0;j<d;j++)
                infile>>m[i][j];
        }
    }
    else{
        cout<<"Error:Opening file failed\nPlease input manually!"<<endl;//处理错误，改为手动输入
        initMbyInput(m,d);
    }
    infile.close();
}
void dispM(int ** m,int d){
    for(int i=0;i<d;i++){
        for(int j=0;j<d;j++)
            cout<<m[i][j]<<'\t';
        cout<<endl;
    }
}
void delM(int ** m,int d){
    for(int i=0;i<d;i++)
        delete[] m[i];
    delete[] m;
    //cout<<"deleted"<<endl;
}
int** cloneM(int ** m,int d){
    int **mm=new int*[d];
    for(int i=0;i<d;i++){
        mm[i]=new int[d];
    }
    for(int i=0;i<d;i++){
        for(int j=0;j<d;j++)
            mm[i][j]=m[i][j];
    }
    return mm;
}
void reflexive(int ** m,int d){
    int **mm=cloneM(m,d);
    for(int i=0;i<d;i++){
        mm[i][i]=1;
    }
    cout<<"The reflexive closure:"<<endl;
    dispM(mm,d);
    delM(mm,d);
}
void symmetric(int ** m,int d){
    int **mm=cloneM(m,d);
    for(int i=0;i<d;i++){
        for(int j=i+1;j<d;j++)
            if(mm[i][j] != mm[j][i])//如果两者不相等则都赋值为1
                mm[i][j] = mm[j][i] = 1;
    }
    cout<<"The symmetric closure:"<<endl;
    dispM(mm,d);
    delM(mm,d);
}
void transitive(int ** m,int d){
    int **mm=cloneM(m,d);
    for(int i=0;i<d;i++)
        for(int j=0;j<d;j++)
            if(mm[j][i])
                for(int k=0;k<d;k++)
                    mm[j][k]=mm[j][k]|mm[i][k];//逻辑加
    cout<<"The transitive closure:"<<endl;
    dispM(mm,d);
    delM(mm,d);
}
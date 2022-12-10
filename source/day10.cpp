#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int part1(const string path);
void part2(const string path);
map<unsigned int,bool> createTriggers(const unsigned int nbCycle,const unsigned int start,const unsigned int step);
int parseCommand( string line,int& x,unsigned int& cycle,map<unsigned int,bool>& triggers);
int checkCycle(unsigned int cycle,map<unsigned int,bool>& triggers,int x);
char drawPixel(int x, unsigned int cycle);
void printImage(string lineImage,const int width,const int height);

map<unsigned int,bool> createTriggers(const unsigned int nbCycle,const unsigned int start,const unsigned int step)
{
    map<unsigned int,bool> triggers;
    triggers[start] = false;
    for(unsigned int i = 1;i<nbCycle;i++)
    {
        triggers[start+i*step] = false;
        //cout<<"Pos : "<<start+i*step<<"\n";
    }
    return triggers;
}

int checkCycle(unsigned int cycle,map<unsigned int,bool>& triggers,int x)
{
    int signalStrength = 0;
    if(triggers.find(cycle-1) != triggers.end() && !triggers[cycle -1])
    {
        cout << "At cycle " << cycle << "\n";
        signalStrength = (cycle-1)*x;
        triggers[cycle -1] = true;
        cout << (cycle-1)*x<<"\n";
    }else if (triggers.find(cycle) != triggers.end() && !triggers[cycle])
    {
        cout << "At cycle " << cycle << "\n";
        signalStrength = (cycle)*x;
        triggers[cycle] = true;
        cout << cycle*x<<"\n";
    }
    return signalStrength;
}

int parseCommand( string line,int& x,unsigned int& cycle,map<unsigned int,bool>& triggers)
{
    int signalStrength = 0;
    string command = line.substr(0,line.find(" "));
    
    if(command == "addx")
    {
        cycle+=1;
        signalStrength = checkCycle(cycle,triggers,x);
        int valToAdd = stoi(line.substr(line.find(" ")+1));
        x+=valToAdd;
        cycle+=1;
    }else{
        signalStrength = checkCycle(cycle,triggers,x);
        cycle+=1;
    }
    return signalStrength;
}


int part1(const string path)
{
    int totalSignal = 0;
    ifstream myFile(path);
    if(!myFile.is_open())
    {
        cerr << "Couldn't read file at : " << path << " stopping \n";
        return EXIT_FAILURE;
    }
    string line;
    unsigned int cycle = 1;
    int x = 1;
    map<unsigned int,bool> triggers = createTriggers(6,20,40);
    
    while(getline(myFile,line))
    {
        //checkCycle(cycle,triggers,x);
        totalSignal += parseCommand(line,x,cycle,triggers);
    }
    myFile.close();
    return totalSignal;
}

char drawPixel(int x, unsigned int cycle)
{
    if(x-1 <= cycle && cycle<= x+1)
    {
        return '#';
    }else{
        return '.';
    }
}

void part2(const string path,const int width,const int height)
{
    int totalSignal = 0;
    ifstream myFile(path);
    if(!myFile.is_open())
    {
        cerr << "Couldn't read file at : " << path << " stopping \n";
        return;
    }
    string line;
    string image;
    unsigned int cycle = 0;
    int x = 1;
    while(getline(myFile,line))
    {
        string command = line.substr(0,line.find(" "));
        if(command == "addx")
        {
            //cout<< "Sprite posiion " << x <<"\n";
            //cout << "At begining addx "<< cycle<<"\n";
            image.push_back(drawPixel(x,cycle%40));
            //cout << image <<"\n";
            cycle+=1;
            //cout<< "Sprite posiion" << x <<"\n";
            image.push_back(drawPixel(x,cycle%40));
            //cout << image <<"\n";
            int valToAdd = stoi(line.substr(line.find(" ")+1));
            //cout << "Val to add is : " << valToAdd<<"\n";
            x+=valToAdd;
            //cout << "At end add x"<< cycle<<"\n";
            cycle+=1;
        }else{
            image.push_back(drawPixel(x,cycle%40));
            //cout << image <<"\n";
            cycle+=1;
        }
    }
    printImage(image,width,height);
}

void printImage(string lineImage,const int width,const int height)
{
    unsigned int cnt = 0;
    vector<string> image;
    while(cnt<height*width)
    {
        string line;
        if(cnt%width == 0)
        {
            //New line
            line = "";
            for(unsigned int j = 0;j<width;j++)
            {
                line.push_back(lineImage[cnt]);
                cnt++;
            }
        }
        image.push_back(line);
    }
    for(auto it = image.begin();it!=image.end();it++)
    {
        cout<<*it<<"\n";
    }

}



int main()
{
    //part1 is part2 with a smaller cord so res1 part(string,2)
    //int res1 = part1("./files/day10/input.txt");
    //cout <<"Res 1 is : "<< res1 <<"\n";
    part2("./files/day10/input.txt",40,6);
    //cout <<"Res 2 is : "<< res2 <<"\n";
    return EXIT_SUCCESS;
}
#include <iostream>
#include <fstream>
#include <cmath>
#include <set>
#include <vector>
using namespace std;

bool checkIfTailIsAttached(const int iTail,const int jTail,const int iHead,const int jHead);
bool isPositive(const int val);
pair<int,int> moveTail(const int iTail,const int jTail,const int iHead,const int jHead);
unsigned int part1(const string path);
unsigned int part2(const string path);


bool checkIfTailIsAttached(const int iTail,const int jTail,const int iHead,const int jHead)
{
    return (abs(iTail-iHead)<=1 && abs(jTail-jHead)<=1);
}

bool isPositive(const int val)
{
    return val>=0;
}

pair<int,int> moveTail(const int iTail,const int jTail,const int iHead,const int jHead)
{
    unsigned int distIAxis = abs(iHead-iTail);
    unsigned int distJAxis = abs(jHead-jTail);
    int movementI = 0;
    int movementJ = 0;
    if(iHead != iTail && jHead != jTail)
    {
        //Diagonal
        if(iHead > iTail)
        {
            movementI = 1;
        }else{
            movementI = -1;
        }

        if(jHead > jTail)
        {
            movementJ = 1;
        }else{
            movementJ = -1;
        }
    }
    else if(distIAxis>=2)
    {
        if(isPositive(iHead-iTail))
        {
            //Head is too far up
            movementI = 1;
        }else
        {
            //Head is too far down
            movementI = -1;
        }
    }
    else if(distJAxis>=2)
    {
        if(isPositive(jHead-jTail))
        {
            //Head is too far right

            movementJ = 1;
        }else
        {

            movementJ = -1;
        }
    }

    return make_pair(iTail+movementI,jTail+movementJ);
}
void moveHead(const string direction, pair<int,int>& headPos)
{
    if(direction == "L")
    {
        headPos.second -=1;
    }else if(direction == "R")
    {
        headPos.second +=1;
    }else if(direction == "D")
    {
        headPos.first -=1;
    }else if(direction == "U")
    {
        headPos.first +=1;
    }else
    {
        cout << "Unknown direction\n";
    }
}

void computeMove(const string direction,const int movements,pair<int,int>& headPos, pair<int,int>& tailPos,set<pair<int,int>>& seenPos,bool isTail)
{
    //cout <<"Moving " << direction << " in "<< movements << "\n";
    for(unsigned int cnt = 0;cnt<movements;cnt++)
    {
        moveHead(direction,headPos);
        //cout << "Head :["<<headPos.first<<"]:["<<headPos.second<<"]\n";
        if(!checkIfTailIsAttached(tailPos.first,tailPos.second,headPos.first,headPos.second))
        {
            tailPos = moveTail(tailPos.first,tailPos.second,headPos.first,headPos.second);
        }
        if(isTail)
        {
            seenPos.insert(tailPos);
        }
    }
}


void computeRope(const string direction,const int movements,pair<int,int>& headPos, vector<pair<int,int>>& rope,set<pair<int,int>>& seenPos)
{
    for(unsigned int cnt = 0;cnt<movements;cnt++)
    {
        moveHead(direction,rope[0]);
        for(unsigned int i = 1;i<rope.size();i++)
        {
            if(!checkIfTailIsAttached(rope[i].first,rope[i].second,rope[i-1].first,rope[i-1].second))
            {
                rope[i] = moveTail(rope[i].first,rope[i].second,rope[i-1].first,rope[i-1].second);
            }
            if(i == rope.size()-1)
            {
                seenPos.insert(rope[i]);
            }
        }
    }

}

//PART 2 CAN DO PART 1
unsigned int part1(const string path){
    ifstream myFile(path);
    if(!myFile.is_open())
    {
        cerr << "Couldn't read file at : " << path << " stopping \n";
        return EXIT_FAILURE;
    }
    string line;
    set<pair<int,int>> seenPos;
    pair<int,int> headPos = make_pair(0,0);
    pair<int,int> tailPos = make_pair(0,0);
    seenPos.insert(tailPos);
    while(getline(myFile,line))
    {
        string direction = line.substr(0,line.find(" "));
        int movements = stoi(line.substr(line.find(" ")+1));
        computeMove(direction,movements,headPos,tailPos,seenPos,true);
    }
    return seenPos.size();
}

unsigned int part2(const string path,int ropeSize){
    ifstream myFile(path);
    if(!myFile.is_open())
    {
        cerr << "Couldn't read file at : " << path << " stopping \n";
        return EXIT_FAILURE;
    }
    string line;
    set<pair<int,int>> seenPos;
    pair<int,int> headPos = make_pair(0,0);
    pair<int,int> tailPos = make_pair(0,0);
    vector<pair<int,int>> rope(ropeSize,make_pair(0,0));
    while(getline(myFile,line))
    {
        string direction = line.substr(0,line.find(" "));
        int movements = stoi(line.substr(line.find(" ")+1));
        computeRope(direction,movements,headPos,rope,seenPos);
    }
    return seenPos.size();
}


int main()
{
    //part1 is part2 with a smaller cord so res1 part(string,2)
    unsigned int res1 = part2("./files/day9/input.txt",2);
    cout <<"Res 1 is : "<< res1 <<"\n";
    unsigned int res2 = part2("./files/day9/input.txt",10);
    cout <<"Res 2 is : "<< res2 <<"\n";
    return EXIT_SUCCESS;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <cctype>


using namespace std;

vector<vector<char>> getGrid(const string path);
pair<int,int> getStartPos(vector<vector<char>> grid);
vector<pair<int,int>> getStartPoss(vector<vector<char>> grid);
pair<int,int> getEndPos(vector<vector<char>> grid);

class Part1
{
    public:
    vector<vector<char>> grid;
    map<pair<int,int>,int> dpMap;
    pair<int,int> startPos;
    pair<int,int> endPos;
    map<pair<int,int>,int> toVisit;

    Part1(string path)
    {
        this->grid = getGrid(path);
        this->startPos = getStartPos(grid);
        this->endPos = getEndPos(grid);
    }

    Part1(vector<vector<char>> _grid,pair<int,int> _startPos,pair<int,int> _endPos)
    {
        this->grid = _grid;
        this->startPos = _startPos;
        this->endPos = _endPos;
    }

    void clear()
    {
        this->toVisit.clear();
        this->dpMap.clear();
    }



    bool canGoThere(int startI,int startJ,int targetI,int targetJ)
    {
        //cout<<"checking if can go from "<<start<<" to "<<target<<"\n";
        //cout << (int(tolower(target))<=int(tolower(start))+1)<<"\n";
        if(targetI<0 || targetI>=this->grid.size() || targetJ<0 || targetJ>this->grid[0].size())
        {
            return false;
        }
        if(this->grid[targetI][targetJ] == 'E')
        {
            char replacedTarget = 'z';
            return(int(tolower(replacedTarget))<=int(tolower(this->grid[startI][startJ]))+1);
        }
        return(int(tolower(this->grid[targetI][targetJ]))<=int(tolower(this->grid[startI][startJ]))+1);
    }

    void exploreD(const int i,const int j,int pathLength)
    {
        //cout << "At : ["<<i<<"]["<<j<<"] = "<<this->grid[i][j] << " Pathlength is " << pathLength <<"\n";
        this->dpMap[(make_pair(i,j))] = pathLength;
        if(canGoThere(i,j,i+1,j) && this->dpMap.find(make_pair(i+1,j)) == this->dpMap.end())
        {
            //cout<<"Checking down\n";
            if(this->toVisit.find(make_pair(i+1,j)) == this->toVisit.end())
            {
                this->toVisit[make_pair(i+1,j)] = pathLength+1;
            }
        }

        if(canGoThere(i,j,i-1,j) && this->dpMap.find(make_pair(i-1,j)) == this->dpMap.end())
        {
            //cout<<"Checking up\n";
            if(this->toVisit.find(make_pair(i-1,j)) == this->toVisit.end())
            {
                this->toVisit[make_pair(i-1,j)] = pathLength+1;
            }
        }

        if(canGoThere(i,j,i,j+1) && this->dpMap.find(make_pair(i,j+1)) == this->dpMap.end())
        {
            //cout<<"Checking right\n";
            if(this->toVisit.find(make_pair(i,j+1)) == this->toVisit.end())
            {
                this->toVisit[make_pair(i,j+1)] = pathLength+1;
            }
        }

        if(canGoThere(i,j,i,j-1) && this->dpMap.find(make_pair(i,j-1)) == this->dpMap.end())
        {
            //cout<<"Checking left\n";
            if(this->toVisit.find(make_pair(i,j-1)) == this->toVisit.end())
            {
                this->toVisit[make_pair(i,j-1)] = pathLength+1;
            }
        }
        map<pair<int,int>,int> nextVist;
        int minDist = -1;
        pair<int,int> nextPos(-1,-1);
        for(auto it = this->toVisit.begin();it!=this->toVisit.end();it++)
        {
            if(this->dpMap.find(it->first) == this->dpMap.end())
            {
                nextVist[it->first]=it->second;
                if(it->second<minDist || minDist == -1)
                {
                    minDist = it->second;
                    nextPos = it->first;
                }
            }
        }
        this->toVisit=nextVist;
        if(minDist !=-1)
        {
            exploreD(nextPos.first,nextPos.second,minDist);
        }
    }
};

vector<vector<char>> getGrid(const string path)
{
    vector<vector<char>> grid;
    ifstream myFile(path);
    if(!myFile.is_open())
    {
        cerr << "Couldn't read file at : " << path << " stopping \n";
        return grid;
    }
    
    string line;
    while(getline(myFile,line))
    {
        vector<char> gridLine(line.begin(),line.end());
        grid.push_back(gridLine);
    }
    myFile.close();
    return grid;
}

pair<int,int> getStartPos(vector<vector<char>> grid)
{
    for(unsigned int i = 0;i < grid.size();i++)
    {
        for(unsigned int j = 0;j < grid[0].size();j++)
        {
            if(grid[i][j] == 'S')
            {
                return(make_pair(i,j));
            }
        }
    }
    cerr << "Couldn't find start pos\n";
    return(make_pair(-1,-1));
}


vector<pair<int,int>> getStartPoss(vector<vector<char>> grid)
{
    vector<pair<int,int>> inits;
    for(unsigned int i = 0;i < grid.size();i++)
    {
        for(unsigned int j = 0;j < grid[0].size();j++)
        {
            if(grid[i][j] == 'a')
            {
                inits.push_back(make_pair(i,j));
            }
        }
    }
    return(inits);
}

pair<int,int> getEndPos(vector<vector<char>> grid)
{
    for(unsigned int i = 0;i < grid.size();i++)
    {
        for(unsigned int j = 0;j < grid[0].size();j++)
        {
            if(grid[i][j] == 'E')
            {
                return(make_pair(i,j));
            }
        }
    }
    cerr << "Couldn't find end pos\n";
    return(make_pair(-1,-1));
}






void printGrid(vector<vector<char>> grid)
{
    for(vector<vector<char>>::iterator it = grid.begin();it != grid.end();it++)
    {
        for(vector<char>::iterator jt=it->begin();jt != it->end();jt++)
        {
            cout<<*jt;
        }
        cout<<"\n";
    }
}


int main()
{
    Part1 res1 = Part1("./files/day12/input.txt");
    res1.exploreD(res1.startPos.first,res1.startPos.second,0);
    cout <<"Res 1 is : "<< res1.dpMap[make_pair(res1.endPos.first,res1.endPos.second)] <<"\n";
    int bestRes = res1.dpMap[make_pair(res1.endPos.first,res1.endPos.second)];
    vector<pair<int,int>> startPoss = getStartPoss(res1.grid);
    pair<int,int> endPos = getEndPos(res1.grid);
    for(unsigned int i = 0;i<startPoss.size();i++)
    {
        Part1 resTemp = Part1(res1.grid,startPoss[i],endPos);
        //cout << "Starting at : ["<<startPoss[i].first<<"]["<<startPoss[i].second<<"] = " << resTemp.grid[startPoss[i].first][startPoss[i].second]<<"\n";
        resTemp.exploreD(resTemp.startPos.first,resTemp.startPos.second,0);
        //cout << "res is " <<resTemp.dpMap[make_pair(resTemp.endPos.first,resTemp.endPos.second)]<<"\n";
        if(resTemp.dpMap[make_pair(resTemp.endPos.first,resTemp.endPos.second)]<bestRes && resTemp.dpMap[make_pair(resTemp.endPos.first,resTemp.endPos.second)] >0)
        {
            bestRes = res1.dpMap[make_pair(resTemp.endPos.first,resTemp.endPos.second)];
        }
    }
    cout <<"Res 2 is : "<< bestRes <<"\n";
    /*int res2 = part1("./files/day11/input.txt",20,true);
    cout <<"Res 2 is : "<< res2 <<"\n";*/
    return EXIT_SUCCESS;
}
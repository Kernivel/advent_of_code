#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
using namespace std;
/*
class Forest
{
    public:
        unordered_map<pair<int,int>,bool> arrayTreeSeen;
        vector<vector<int>> arrayTree;
        
        Forest(vector<vector<int>> _arrayTree;)
        {
            this.arrayTree = _arrayTree;
        }
};*/

bool isVisible(const vector<vector<int>> arrayTree,pair<int,int> pos,map<pair<int,int>,bool>& arrayTreeSeen,set<pair<int,int>>& visited)
{
    visited.insert(pos);
    bool res = false;
    int currentHeight = arrayTree[pos.first][pos.second];
    cout << "At " <<pos.first<<" : "<<pos.second<<" heigth : "<<arrayTree[pos.first][pos.second]<<"\n";
    if(arrayTreeSeen.find(pos) != arrayTreeSeen.end())
    {
        cout << "Already in map " << arrayTreeSeen[pos] <<"\n";
        return arrayTreeSeen[pos];
    }
    if(pos.first == 0 || pos.first == arrayTree.size()-1 || pos.second == 0 || pos.second == arrayTree[0].size()-1)
    {
        arrayTreeSeen[pos] = true;
        return true;
    }
    //Check left
    if(pos.first-1>=0 && arrayTree[pos.first-1][pos.second] < currentHeight && visited.find(make_pair(pos.first-1,pos.second)) == visited.end())
    {
        res = res || isVisible(arrayTree,make_pair(pos.first-1,pos.second),arrayTreeSeen,visited);
    }
    //Right
    if(pos.first+1<arrayTree.size() && arrayTree[pos.first+1][pos.second] < currentHeight && visited.find(make_pair(pos.first+1,pos.second)) == visited.end())
    {
        res = res || isVisible(arrayTree,make_pair(pos.first+1,pos.second),arrayTreeSeen,visited);
    }
    //Up
    if(pos.second-1>=0 && arrayTree[pos.first][pos.second-1] < currentHeight && visited.find(make_pair(pos.first,pos.second-1)) == visited.end())
    {
        res = res || isVisible(arrayTree,make_pair(pos.first,pos.second-1),arrayTreeSeen,visited);
    }
    //Up
    if(pos.first+1<arrayTree[0].size() && arrayTree[pos.first][pos.second+1] < currentHeight && visited.find(make_pair(pos.first,pos.second)) == visited.end())
    {
        res = res || isVisible(arrayTree,make_pair(pos.first,pos.second+1),arrayTreeSeen,visited);
    }
    arrayTreeSeen[pos] = res;
    return arrayTreeSeen[pos];
}

unsigned int part1(vector<vector<int>> arrayTree)
{
    map<pair<int,int>,bool> arrayTreeSeen;
    vector<int> maxLeft(arrayTree[0].size(),0);
    vector<int> maxRight(arrayTree[0].size(),0);
    vector<int> maxUp(arrayTree.size(),0);
    vector<int> maxDown(arrayTree.size(),0);
    vector<vector<bool>> visibleRight(arrayTree.size(),vector<bool>(arrayTree[0].size(),false));
    vector<vector<bool>> visibleDown(arrayTree.size(),vector<bool>(arrayTree[0].size(),false));
    vector<vector<bool>> visibleUp(arrayTree.size(),vector<bool>(arrayTree[0].size(),false));
    vector<vector<bool>> visibleLeft(arrayTree.size(),vector<bool>(arrayTree[0].size(),false));

    unsigned int res = 0;
    //Left
    int left = 0;
    for(unsigned int i = 0;i<arrayTree.size();i++)
    {
        for(unsigned int j = 0;j<arrayTree[0].size();j++)
        {
            if(j == 0){
                visibleLeft[i][j] = true;
                maxLeft[j] = arrayTree[i][j];
                left++;
                continue;
            }else if(arrayTree[i][j]>maxLeft[j-1])
            {
                //cout << arrayTree[i][j]<<":"<<maxLeft[j-1]<<"\n";
                left++;
                visibleLeft[i][j] = true;
            }else
            {
                visibleLeft[i][j] = false;
            }
            maxLeft[j] = maxLeft[j-1]>arrayTree[i][j]?maxLeft[j-1]:arrayTree[i][j];
        }
    }
    //Right
    int right = 0;
    for(unsigned int i = 0;i<arrayTree.size();i++)
    {
        for(int j = arrayTree[0].size()-1;j>=0;j--)
        {
            //cout<<"At " << i<<":"<<j<<"\n";
            if(j == arrayTree[0].size()-1){
                visibleRight[i][j] = true;
                maxRight[j] = arrayTree[i][j];
                right++;
                continue;
            }else if(arrayTree[i][j]>maxRight[j+1])
            {
                visibleRight[i][j] = true;
                right++;
            }else
            {
                visibleRight[i][j] = false;
            }
            maxRight[j] = maxRight[j+1]>arrayTree[i][j]?maxRight[j+1]:arrayTree[i][j];
        }
    }
    cout << right << "\n";

    //Down
    int down = 0;
    for(unsigned int j = 0;j<arrayTree[0].size();j++)
    {
        for(unsigned int i = 0;i<arrayTree.size();i++)
        {
            if(i == 0){
                visibleDown[i][j] = true;
                maxDown[i] = arrayTree[i][j];
                down++;
                continue;
            }else if(arrayTree[i][j]>maxDown[i-1])
            {
                visibleDown[i][j] = true;
                down++;
            }else
            {
                visibleDown[i][j] = false;
            }
            //cout << "Status ["<<i<<"]["<<j<<"] : " << visibleDown[i][j]<<"\n"; 
            maxDown[i] = maxDown[i-1]>arrayTree[i][j]?maxDown[i-1]:arrayTree[i][j];
        }
    }
    int up = 0;
    for(unsigned int j = 0;j<arrayTree[0].size();j++)
    {
        for(int i = arrayTree.size()-1;i>=0;i--)
        {
            if(i == arrayTree.size()-1){
                visibleUp[i][j] = true;
                maxUp[i] = arrayTree[i][j];
                up++;
                continue;
            }else if(arrayTree[i][j]>maxUp[i+1])
            {
                visibleUp[i][j] = true;
                up++;
            }else
            {
                visibleUp[i][j] = false;
            }
            maxUp[i] = maxUp[i+1]>arrayTree[i][j]?maxUp[i+1]:arrayTree[i][j];
        }
    }


    for(unsigned int i = 0;i<arrayTree.size();i++)
    {
        for(unsigned int j = 0;j<arrayTree[0].size();j++)
        {
            if(visibleLeft[i][j] || visibleRight[i][j] || visibleUp[i][j] || visibleDown[i][j])
            {
                res+=1;
            }
        }
    }

    return res;
}

unsigned int part2(vector<vector<int>> arrayTree)
{
    unsigned int maxScore = 0;
    for(unsigned int i = 0;i<arrayTree.size();i++)
    {
        for(unsigned int j = 0;j<arrayTree[0].size();j++)
        {
            unsigned int scoreLeft = 0;
            unsigned int scoreRight = 0;
            unsigned int scoreUp = 0;
            unsigned int scoreDown = 0;
            //Check left
            //cout<<"checkleft\n";
            for(int posLeft = j-1;posLeft>=0;posLeft--)
            {
                scoreLeft+=1;
                if(arrayTree[i][j]<=arrayTree[i][posLeft])
                {
                    break;
                }
            }
            //Check right
            //cout<<"checkright\n";
            for(int posRight = j+1;posRight<arrayTree[0].size();posRight++)
            {
                scoreRight+=1;
                if(arrayTree[i][j]<=arrayTree[i][posRight])
                {
                    break;
                }
            }
            //Check down
            //cout<<"checkdown\n";
            for(int posDown = i+1;posDown<arrayTree.size();posDown++)
            {
                scoreDown+=1;
                if(arrayTree[i][j]<=arrayTree[posDown][j])
                {
                    break;
                }
            }

            //Check up
            //cout<<"checkup\n";
            for(int posUp = i-1;posUp<arrayTree.size();posUp--)
            {
                scoreUp+=1;
                if(arrayTree[i][j]<=arrayTree[posUp][j])
                {
                    break;
                }
            }
            unsigned int score = scoreLeft*scoreRight*scoreDown*scoreUp;
            //cout << "Score at ["<<i<<"]["<<j<<"] is : " <<score <<" prev max score is : " << maxScore << "\n";
            maxScore = maxScore>score?maxScore:score;

        }
    }
    return maxScore;
}


vector<vector<int>> createTreeArray(const string path)
{
    vector<vector<int>>arrayTree;
    ifstream myFile(path);
    if(!myFile.is_open())
    {
        cerr << "Couldn't read file at : " << path << "\n";
        return arrayTree;
    }
    string line;
    while(getline(myFile,line))
    {
        vector<int> values;
        for(unsigned int i = 0;i<line.length();i++)
        {
            values.push_back(line[i]-'0');
        }
        arrayTree.push_back(values);
    }
    return arrayTree;
}

int main()
{
    string path = "./files/day8/input.txt";
    vector<vector<int>> arrayTree = createTreeArray(path);
    unsigned int res1 = part1(arrayTree);
    cout << "Res 1 is " << res1 <<"\n";
    unsigned int res2 = part2(arrayTree);
    cout << "Res 2 is " << res2 <<"\n";
    return EXIT_SUCCESS;
}
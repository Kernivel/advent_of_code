#include <fstream>
#include <iostream>
#include <unordered_map>
using namespace std;
#include <chrono>
using namespace std::chrono;



/*
A,X are rock
B,Y are paper
C,Z are scissors
*/

int part1()
    {
    unordered_map<string,string> winningCombinations = {{"A","Y"},{"B","Z"},{"C","X"}};
    unordered_map<string,string> losingCombinations = {{"A","Z"},{"B","X"},{"C","Y"}};
    unordered_map<string,int> points = {{"X",1},{"Y",2},{"Z",3}};
    ifstream myFile;
    myFile.open("./files/day2/input.txt");
    string line;
    string opponent;
    string me;
    int totalScore = 0;
    while(getline(myFile,line))
    {
        opponent = line.substr(0,line.find(" "));
        me = line.substr(line.find(" ")+1,line.length()-1);
        
        unordered_map<string,string>::const_iterator winningMatch = winningCombinations.find(opponent);
        unordered_map<string,string>::const_iterator losingMatch = losingCombinations.find(opponent);
        unordered_map<string,int>::const_iterator possiblePoints = points.find(me);
        cout<<"Me :|"<<me<<"| opponent : |"<<opponent<<"|\n";
        if(winningMatch->second == me)
        {
            //Win
            totalScore += possiblePoints->second+6;
            cout<<"Win new score : "<< totalScore << "Points added " <<possiblePoints->second+6<<"\n";
        }else if(losingMatch->second == me)
        {
            totalScore += possiblePoints->second;
            cout<<"lose new score : "<< totalScore << "Points added " <<possiblePoints->second<<"\n";
            //Lose
        }else
        {
            totalScore += possiblePoints->second+3;
            cout<<"Draw new score : "<< totalScore << "Points added " <<possiblePoints->second+3<<"\n";
            //Draw
        }
    }
    cout << "Total points : " << totalScore << "\n";
    myFile.close();
    return totalScore;
}


/*
A,X are rock
B,Y are paper
C,Z are scissors
*/

int part2(){
    unordered_map<string,string> winningCombinations = {{"A","Y"},{"B","Z"},{"C","X"}};
    unordered_map<string,string> losingCombinations = {{"A","Z"},{"B","X"},{"C","Y"}};
    unordered_map<string,string> drawCombinations = {{"A","X"},{"B","Y"},{"C","Z"}};
    unordered_map <string,int> points = {{"X",1},{"Y",2},{"Z",3}};
    ifstream myFile;
    myFile.open("./files/day2/input.txt");
    string line;
    string opponent;
    string me;
    int totalScore = 0;
    while(getline(myFile,line)){
        opponent = line.substr(0,line.find(" "));
        me = line.substr(line.find(" ")+1,line.length()-1);
        if(me == "X")
        {   
            //Lose
            unordered_map<string,string>::const_iterator choice = losingCombinations.find(opponent);
            cout << "LOSE Opponent played " << opponent << " I need to play " << choice->second<< "\n";
            int myPlayScore = points.find(choice->second)->second;
            totalScore += myPlayScore;
            cout<<"Lose new score : "<< totalScore << " Points added " <<myPlayScore<<"\n";
            
        }else if(me == "Y")
        {
            //Draw
            unordered_map<string,string>::const_iterator choice = drawCombinations.find(opponent);
            cout << "DRAW Opponent played " << opponent << " I need to play " << choice->second<< "\n";
            int myPlayScore = points.find(choice->second)->second+3;
            totalScore += myPlayScore;
            cout<<"Draw new score : "<< totalScore << " Points added " <<myPlayScore<<"\n";
        }else
        {
            //Win
            unordered_map<string,string>::const_iterator choice = winningCombinations.find(opponent);
            cout << "WIN Opponent played " << opponent << " I need to play " << choice->second << "\n";
            int myPlayScore = points.find(choice->second)->second+6;
            totalScore += myPlayScore;
            cout<<"Win new score : "<< totalScore << " Points added " <<myPlayScore<<"\n";
        }
    }
    cout << "Total points : " << totalScore << "\n";
    myFile.close();
    return totalScore;
}

int main()
{
    auto start = high_resolution_clock::now();
    int p1 = part1();
    int p2 = part2();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
    return EXIT_SUCCESS;
}
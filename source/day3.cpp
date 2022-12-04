#include <iostream>
#include <fstream>
#include <set>
#include <vector>
using namespace std;


pair<string,string> splitStringHalf(string baseString)
{
    int mid = baseString.length()/2;
    string part1 = baseString.substr(0,mid);
    string part2 = baseString.substr(mid,baseString.length());
    return make_pair(part1,part2);
}

set<char> createSetFromString(string baseString)
{
    set<char> resultingSet;
    for(int i = 0;i<baseString.length();i++)
    {
        resultingSet.insert(baseString[i]);
    }
    return resultingSet;
}

char findDuplicateValueInTwoSets(set<char> setFirstHalf,set<char> setSecondHalf){
    for(set<char>::iterator it = setFirstHalf.begin();it!= setFirstHalf.end();it++)
    {
        if(setSecondHalf.find(*it)!=setSecondHalf.end()){
            return *it;
        }
    }
    return '$';
}

char findDuplicateValueInThreeSets(set<char> setFirst,set<char> setSecond,set<char> setThird){
    for(set<char>::iterator it = setFirst.begin();it!= setFirst.end();it++)
    {
        if(setSecond.find(*it)!=setSecond.end() && setThird.find(*it)!=setThird.end()){
            return *it;
        }
    }
    return '$';
}

int getScoreFromChar(char letter){
    int baseValue = int(letter);
    //default error value -1;
    int score = -1;
    if (baseValue>=97 && baseValue <= 122)
    {
        //Char is lowercase
        score = baseValue-97+1;
        //Scale the value back to 0 and then add 1 because uppercase letter are worth between 1 and 26
    }else if(baseValue>=65 && baseValue <= 90)
    {
        //Char is upper case
        score = baseValue-65+27;
        //Scale the value back to zero and then add 27 because uppercase letter are worth between 27 and 52
    }
    return score;
}

int part1()
{
    int totalScore = 0;
    ifstream myFile;
    myFile.open("./files/day3/input.txt");
    if(myFile.is_open() == false)
    {
        cerr<<"Couldn't open file\n";
        return EXIT_FAILURE;
    }
    string line;
    while(getline(myFile,line))
    {
        pair<string,string> splitHalfLine = splitStringHalf(line);
        cout << "H1 : " << splitHalfLine.first << " H2 : " << splitHalfLine.second<<"\n";
        //cout << "H1 : " << splitHalfLine.first.length() << " H2 : " << splitHalfLine.second.length()<<"\n";
        set<char> setFirstHalf = createSetFromString(splitHalfLine.first);
        set<char> setSecondHalf = createSetFromString(splitHalfLine.second);
        char dupe = findDuplicateValueInTwoSets(setFirstHalf,setSecondHalf);
        cout << "Duplicate value is : " << dupe << "\n";
        int value =  getScoreFromChar(dupe);
        cout << "Value is :" << value <<"\n";
        totalScore += value;
    }
    myFile.close();
    return totalScore;
}

int part2(){
    int totalScore = 0;
    ifstream myFile;
    myFile.open("./files/day3/input.txt");
    if(myFile.is_open() == false){
        cerr <<"Couldn't open file\n";
        return EXIT_FAILURE;
    }
    string line;
    int loop = 0;
    vector <string> tripletElves;
    while(getline(myFile,line))
    {
        tripletElves.push_back(line);
        if(loop == 2){
            cout << "H1 : " << tripletElves[0] << " H2 : " << tripletElves[1] <<" H3 :" << tripletElves[2] << "\n";
            set<char> setFirstElve = createSetFromString(tripletElves[0]);
            set<char> setSecondElve = createSetFromString(tripletElves[1]);
            set<char> setThirdElve = createSetFromString(tripletElves[2]);
            char dupe = findDuplicateValueInThreeSets(setFirstElve,setSecondElve,setThirdElve);
            cout << "Duplicate value is : " << dupe << "\n";
            int value = getScoreFromChar(dupe);
            totalScore += value;
            tripletElves.clear();
            loop = 0;
        }else{
            loop++;
        }
        
    }
    myFile.close();
    return totalScore;
}


int main()
{
    int res1 = part1();
    cout <<"Res 1 is : " << res1 << "\n";
    int res2 = part2();
    cout <<"Res 2 is : " << res2 << "\n";
    return EXIT_SUCCESS;
}
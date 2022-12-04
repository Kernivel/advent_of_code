#include <iostream>
#include <fstream>
using namespace std;


pair<unsigned int,unsigned int> getPair(const string input,const bool firstPair)
{
    string parsedInput,parsedMin,parsedMax;
    pair<unsigned int,unsigned int> sectionRange;
    if(firstPair)
    {
        parsedInput = input.substr(0,input.find(","));
        cout << "First parsed is |"<<parsedInput<<"|\n";
        
    }else
    {
        parsedInput = input.substr(input.find(",")+1,input.length());
        cout << "Second parsed is |"<<parsedInput<<"|\n";
    }
    
    parsedMin = parsedInput.substr(0,parsedInput.find("-"));
    parsedMax = parsedInput.substr(parsedInput.find("-")+1,parsedInput.length());
    sectionRange.first = stoi(parsedMin);
    sectionRange.second = stoi(parsedMax);
    //cout << sectionRange.first << ":" << sectionRange.second << "\n";
    return sectionRange;
}

bool isPairContained(const pair<unsigned int,unsigned int> firstPair,const pair<unsigned int,unsigned int> secondPair)
{
    if(firstPair.first <= secondPair.first && firstPair.second >= secondPair.second)
    {
        return true;
    }
    return false;
}

bool isOverlap(const pair<unsigned int,unsigned int> firstPair,const pair<unsigned int,unsigned int> secondPair)
{
    if(firstPair.first >= secondPair.first && firstPair.first <= secondPair.second){
        return true;
    }
    return false;
}

unsigned int part1()
{
    unsigned int sumCompleteOverlap = 0;
    ifstream myFile;
    myFile.open("./files/day4/input.txt");
    if(myFile.is_open() == false)
    {
        cerr<< "Couldn't open file\n";
        return EXIT_FAILURE;
    }
    string line;
    while (getline(myFile,line))
    {
        const pair<unsigned int,unsigned int> firstElve = getPair(line,true);
        const pair<unsigned int,unsigned int> secondElve = getPair(line,false);
        if(isPairContained(firstElve,secondElve) || isPairContained(secondElve,firstElve))
        {
            sumCompleteOverlap+=1;
        }
        
    }
    
    myFile.close();
    return sumCompleteOverlap;
}

unsigned int part2()
{
    unsigned int sumOverlap = 0;
    ifstream myFile;
    myFile.open("./files/day4/input.txt");
    if(myFile.is_open() == false)
    {
        cerr<< "Couldn't open file\n";
        return EXIT_FAILURE;
    }
    string line;
    while (getline(myFile,line))
    {
        const pair<unsigned int,unsigned int> firstElve = getPair(line,true);
        const pair<unsigned int,unsigned int> secondElve = getPair(line,false);
        if(isOverlap(firstElve,secondElve) || isOverlap(secondElve,firstElve))
        {
            sumOverlap+=1;
            cout <<"Overlap : " << sumOverlap << "\n";
        }
        
    }
    
    myFile.close();
    return sumOverlap;
}

int main()
{
    const unsigned int res1 = part1();
    cout << "Res 1 is : " << res1 << "\n";
    const unsigned int res2 = part2();
    cout << "Res 2 is : " << res2 << "\n";
    return EXIT_SUCCESS;
}
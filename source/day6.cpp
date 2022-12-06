#include <fstream>
#include <iostream>
#include <unordered_map>
#include <chrono>
using namespace std;
using namespace std::chrono;


string readInput(const string path){
    ifstream myFile;
    myFile.open(path);
    if(!myFile.is_open())
    {
        cerr << "Couldn't open path : " << path << "\n"; 
        return "ERR";
    }
    string line;
    getline(myFile,line);
    myFile.close();
    return line;
}

unsigned int slidingWindowUnique(const string input,const unsigned int windowSize)
{
    unsigned int transmissionStart = 0;
    //sliding window;
    unsigned int left = 0;
    unsigned int right = 0;
    string tempo;
    unordered_map<char,int> letters;
    while(left < input.length() && right < input.length())
    {
        
        unsigned int dist = right-left+1;
        //string currString = input.substr(left+1,dist);
        //cout << "currString is " << currString << "\n";
        //cout << "Left is " << left+1 << "["<< input[left+1]<<"]"<<" Right is " << right << "["<< input[right]<<"]""\n";
         
        if(dist<windowSize+1)
        {
            //Increase or add new letter
            if(letters.find(input[right]) == letters.end())
            {
                letters[input[right]] = 1;
            }else
            {
                letters[input[right]] += 1;
            }
            right+=1;
        }else
        {
            //Increase or add new letter
            if(letters.find(input[right]) == letters.end())
            {
                letters[input[right]] = 1;
            }else
            {
                letters[input[right]] += 1;
            }
            //Decrease or delete prev letter
            letters[input[left]] -=1;
            if(letters[input[left]] <= 0)
            {
                letters.erase(input[left]);
            }
            if(letters.size() == windowSize)
            {
                //+1 because input is indexed 0 and required ans is indexed 1
                return right+1;
            }

            right+=1;
            left+=1;
        }
        //cout << "Map size is :" << letters.size() << "\n";
    }
    return transmissionStart;
}

unsigned int part1(const string input)
{
    const unsigned int answer = slidingWindowUnique(input,4);
    return answer;
}

int part2(const string input)
{
    const unsigned int answer = slidingWindowUnique(input,14);
    return answer;
}

int main()
{
    auto start = high_resolution_clock::now();
    const string input = readInput("./files/day6/input.txt");
    const unsigned int res1 = part1(input);
    const unsigned int res2 = part2(input);
    cout << "Res 1 is " << res1 << "\n";
    cout << "Res 2 is " << res2 << "\n";
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by main: "<< duration.count() << " microseconds" << endl;
    return EXIT_SUCCESS;
}
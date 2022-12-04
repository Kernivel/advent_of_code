#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include<bits/stdc++.h> 
#include <chrono>
using namespace std;
using namespace std::chrono;


int part1(){
    ifstream myFile;
    string line;
    int lineInt;
    int maxCalories = 0,currentElfCalories = 0;
    myFile.open("./files/day1/input.txt");
    if(!myFile){
        cout<< "No files opened\n";
        return EXIT_FAILURE;
    }
    while(getline(myFile,line)){
        if(line == ""){
            maxCalories = maxCalories<currentElfCalories?currentElfCalories:maxCalories;
            currentElfCalories = 0;            
        }else{
            lineInt = stoi(line);
            currentElfCalories+=lineInt;
        }
    }
    maxCalories = maxCalories<currentElfCalories?currentElfCalories:maxCalories;
    cout<<"The elve with the most calories is carrying "<< maxCalories << " calories.\n";
    myFile.close();
    return maxCalories;
}

int part2(){
    vector<int> heap = {};
    make_heap(heap.begin(),heap.end());
    ifstream myFile;
    string line;
    int lineInt;
    int currentValue = 0;
    int total = 0;
    myFile.open("./files/day1/input.txt");
    if(!myFile){
        cout << "No files opened " << "\n";
        return EXIT_FAILURE;
    }
    string wait;
    while(getline(myFile,line)){
        
        if(line == ""){
            heap.push_back(-currentValue);
            push_heap(heap.begin(),heap.end());
            while(heap.size()>3){
                pop_heap(heap.begin(),heap.end());
                heap.pop_back();
            }
            currentValue = 0;
        }else{
            lineInt = stoi(line);
            currentValue+=lineInt;
        }
    }
    cout<<"Top 3 carrying elves are : \n";
    for(auto it = heap.begin();it!=heap.end();it++){
        cout << "val " << -*it<<"\n";
        total+=-*it;
    }
    cout << "Total is : " << total <<"\n";
    myFile.close();
    return total;
}

int main(){
    auto start = high_resolution_clock::now();
    int answer1 = part1();
    int answer2 = part2();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
    return EXIT_SUCCESS;
}
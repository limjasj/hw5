// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include <string>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(const std::set<std::string>& dict, std::map<char, int> & checkStatic, 
    std::vector<char> & checkFloating,
    std::set<std::string>& answerSet, int length, int index, std::string curr);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::map<char, int> checkStatic;
    for(unsigned int i=0; i<in.length(); i++)
    {
      if(in[i] != '-')
      {
        checkStatic[in[i]] = i;
      }
    }
    
    std::vector<char> checkFloating; //puts all floating letters into set
    for(unsigned int j=0; j<floating.length(); j++)
    {
        checkFloating.push_back(floating[j]);
    }
    std::set<std::string> answerSet;
    wordleHelper(dict, checkStatic, checkFloating, answerSet, in.length(), 0, in);
    
    return answerSet;
}

// Define any helper functions here
void wordleHelper(const std::set<std::string>& dict, std::map<char, int> & checkStatic, 
    std::vector<char> & checkFloating, 
    std::set<std::string>& answerSet, int length, int index, std::string curr)
{
    if(index == length) //see if our word is done
    {
      if((dict.find(curr) != dict.end()) && checkFloating.empty())
      {
        answerSet.insert(curr);
      }
      return;
    }
    bool inStatic=checkStatic.find(curr[index]) != checkStatic.end();

    //check if we are at a static letter, then keep going to next index
    if(inStatic )
    {
      wordleHelper(dict, checkStatic, checkFloating, answerSet, length, index+1, curr);    
    }

    //change vector to a set (faster)
    //insert floating letter
    if(!checkFloating.empty() && (!inStatic))
    {
      std::vector<char> floatingChanged=checkFloating;
      for(unsigned int i=0; i < checkFloating.size(); i++)
      {
        curr[index] = checkFloating[i]; //set index to floating letter
        floatingChanged.erase(std::find(floatingChanged.begin(), floatingChanged.end(), checkFloating[i])); //take letter out of vector  
        wordleHelper(dict, checkStatic, floatingChanged, answerSet, length, index+1, curr);
        floatingChanged=checkFloating;  
      }
    }
    //else return;

    //no more space for the rest of floating letters
    unsigned int lettersLeft= length-index;
    if(lettersLeft < checkFloating.size()) 
    {
      return; 
    }
    
    //dont use floating
    //set that has used chars, if the letter is in the set then continue
    //in the for loop, so we don't need to find in the 
    //bool inFloating=std::find(checkFloating.begin(), checkFloating.end(), curr[index-1]) != checkFloating.end();
    if(!inStatic )
    {
      for(char currChar='a'; currChar<='z'; currChar++)
      {
          curr[index]=currChar;
          wordleHelper(dict, checkStatic, checkFloating, answerSet, length, index+1, curr);
      }
    }
    else 
    {
      return;
    }
    //2 for loops, 1 places down the static letters, the next makes combinations
    //for loop to place floating letter, for loop to go through recursive calls for the rest of the letter
    //change vector to set
}
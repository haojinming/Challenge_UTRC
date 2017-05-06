/*This is the main function file for SW_challenge_UTRC*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include "SocialNetworkGraph.h"

using namespace std;

// Split the input string to two strings conatining the first name and second name.
// Return true is success, false is fails or conatains more than two names.
static bool SplitLineToNames(string &inputLine, string &first, string &second)
{
    //cout << inputLine << endl;
    bool isFirst = true;
    first.clear();
    second.clear();
    for (auto iter : inputLine)
    {
        if (iter == ',')
        {
            if (!isFirst)
            {
                return false;
            }
            isFirst = false;
        }
        else if (isFirst)
        {
            first.push_back(iter);
        }
        else
        {
            second.push_back(iter);
        }
    }
    return true;
}

static void GetAllLinesAndMembers
(
const char* fileName,
multimap<string, string> &allLines,
unordered_map<string, int> &allMembers
)
{
    ifstream inFile;
    inFile.open(fileName);
    assert(inFile.is_open());

    string line, first, second;
    int ii = 0;
    while (getline(inFile, line))
    {
        if (SplitLineToNames(line, first, second))
        {
            allLines.insert(std::make_pair(first, second));
            if (allMembers.find(first) == allMembers.end())
            {
                allMembers.insert(std::make_pair(first, ii));
                ii++;
            }
            if (allMembers.find(second) == allMembers.end())
            {
                allMembers.insert(std::make_pair(second, ii));
                ii++;
            }
        }
    }
    inFile.close();
}

static void CalulateMatrix
(
multimap<string, string> &allLines,
unordered_map<string, int> &allMembers,
vector<vector<int>> &adjacentMatrix
)
{
    //Initilize the weight value of all relationshio is zero.
    //adjacentMatrix.reserve(allMembers.size());
    vector<int> row;
    //row.reserve(allMembers.size());
    for (auto iter1 : allMembers)
    {
        row.push_back(0);
    }

    for (auto iter1 : allMembers)
    {
        adjacentMatrix.push_back(row);
    }

    // The weight value of the existing relationshio is 1.
    /*
    for (unsigned int ii = 0; ii < allLines.size(); ii++)
    {
        int row = allMembers.find(allLines[ii].first)->second;
        int column = allMembers.find(allLines[ii].second)->second;
        adjacentMatrix[row][column] = 1;
        adjacentMatrix[column][row] = 1;
    }
    */
    for (auto iter : allLines)
    {
        int row = allMembers.find(iter.first)->second;
        int column = allMembers.find(iter.second)->second;
        adjacentMatrix[row][column] = 1;
        adjacentMatrix[column][row] = 1;
    }
}

int main()
{
    const char* fileName = "D:\\SocialNetwork.txt";
    const string nameA = "MYLES_JEFFCOAT";
    const string nameB = "MARTIN_OMERSA";
    multimap<string, string> allLines;
    unordered_map<string, int> allMembers;
    vector<vector<int>> adjacentMatrix;
    GetAllLinesAndMembers(fileName, allLines, allMembers);
    CalulateMatrix(allLines, allMembers, adjacentMatrix);

    SocialNetworkGraph relationgraph;
    relationgraph.SetMember(allMembers);
    relationgraph.SetAdjacentMatrix(adjacentMatrix);

    vector<string> path;
    int distance = relationgraph.GetMinDistance(nameA, nameB, path);

    cout << "There are " << relationgraph.GetSize() << " peoples in this social network." << endl;
    cout << "The distance between " << nameA << " and " << nameB << " is : " << distance << endl;
    for (int ii = path.size() - 1; ii >= 0; ii--)
    {
        cout << path[ii];
        if (ii)
        {
            cout << " --> ";
        }
        else
        {
            cout << endl;
        }
    }
    system("pause");
    return 0;
}


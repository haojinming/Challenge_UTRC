/*This is the main function file for SW_challenge_UTRC by Jinming Hao in May-04-2017*/

#include <iostream>
#include "SocialNetworkGraph.h"

using namespace std;

int main()
{
    const string fileName = "./SocialNetwork.txt";
    const string nameA = "MYLES_JEFFCOAT";
    const string nameB = "ARON_OHAIR";
    unordered_map<int, pair<string, string>> allLines;
    bool directFriend = false;

    SocialNetworkGraph relationGraph;
    relationGraph.GetAllLinesAndMembers(fileName, allLines, nameA, nameB, directFriend);
    //If they are direct friend, just return the result.
    if (directFriend)
    {
        cout << "There are " << relationGraph.GetSize() << " peoples in this social network." << endl;
        cout << "The distance between " << nameA << " and " << nameB << " is : " << 1 << endl;
        return 0;
    }
    relationGraph.CalulateRelationMap(allLines);

    vector<string> path;
    int distance = relationGraph.GetMinDistanceWithBFS(nameA, nameB, path);

    cout << "There are " << relationGraph.GetSize() << " peoples in this social network." << endl;
    cout << "The distance between " << nameA << " and " << nameB << " is : " << distance << endl;
    for (int ii = path.size() - 1; ii >= 0; ii--)
    {
        cout << path[ii];
        if (ii)
        {
            cout << " <--> ";
        }
        else
        {
            cout << endl;
        }
    }
    return 0;
}


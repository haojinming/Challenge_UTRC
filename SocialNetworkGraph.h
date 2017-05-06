#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class SocialNetworkGraph
{
public:
    SocialNetworkGraph();
    ~SocialNetworkGraph();

    //The size of members.
    int GetSize();

    // Get all lines and members from input file.
    void GetAllLinesAndMembers
        (
        const string fileName,
        unordered_map<int, pair<string, string>> &allLines,
        const string nameA,
        const string nameB,
        bool &directFriend
        );
    // Get the direct firend map. multi_map.
    void CalulateRelationMap(unordered_map<int, pair<string, string>> &allLines);
    // Find direct friends of given people and record the parent relation.
    void FindAdjacentNode
        (
        const int input,                                          // I: number to serach
        const unordered_map<int, bool> &visited,                  // I: cached visited value
        unordered_set<int> &adjResult,                            // O: adjacent result
        unordered_map<int, int> &parentRelation                   // O: record the parent
        ) const;
    // BFS traverse until find the destination.
    int GetMinDistanceWithBFS
        (
        const string inputA,                                // I: search original
        const string inputB,                                // I: search destination
        vector<string> &path                                // O: search path if found
        ) const;

private:
    unordered_map<string, int> allMembers;
    unordered_multimap<int, int> adjacentMap;
};


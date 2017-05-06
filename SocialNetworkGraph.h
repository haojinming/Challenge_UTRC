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

    // Get all members and adjacent maps(multimap) from input file.
    void GetAllMembersAndAdjacentMap
        (
        const string fileName,
        const string nameA,
        const string nameB,
        bool &directFriend
        );
    // Find direct friends of given people and record the parent relation.
    void FindAdjacentNode
        (
        const string input,                                          // I: number to serach
        const unordered_map<string, bool> &visited,                  // I: cached visited value
        unordered_set<string> &adjResult,                            // O: adjacent result
        unordered_map<string, string> &parentRelation                // O: record the parent
        ) const;
    // BFS traverse until the destination is found.
    int GetMinDistanceWithBFS
        (
        const string inputA,                                // I: search original
        const string inputB,                                // I: search destination
        vector<string> &path                                // O: search path if found
        ) const;

private:
    unordered_set<string> allMembers;
    unordered_multimap<string, string> adjacentMap;
};


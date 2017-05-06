# Challenge_UTRC
This a challenge from UTRC, which is a social network problem.

The method to solve the mininum distance of two peoples is:
1. Traverse all lines in the file and build a map between people and number.
2. Build a map of direct friend, this is a multimap.
3. Use graph BFS algorithm to traverse all members until the destination is found. 
   Because the weight of every relation is one and no direction, the path should be the mininum.
4. To get the path from A to B, record the parent-child relation when get the adjacent node.

To get a better performance,befor BFS, we can identify whether two given people are direct friends or not,
if yes, the distance is one. If not, then call BFS.

*********All maps are uing hash map to improve performance.***********

To test the code, please place the SocialNetwork.txt in same folder.

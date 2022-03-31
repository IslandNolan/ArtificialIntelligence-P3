#define maxAttributes 10
#include <bits/stdc++.h>

/**
 * Feed it a list of positions and bools, it will return true if all are true,
 * else returns false;
 * @author Francisco Romero
 * @param toCheck the string to check
 * @param values first value is position, second value is true or false
 * @return
 */
int checkAnd(std::bitset<maxAttributes> toCheck, std::vector<std::pair<int, int>> values) {
    for (int i = 0; i < values.size(); i++){
        if (toCheck.test(values[i].first) != values[i].second) {
            //printf("rejecting and: %s = %d at %d %d\n", toCheck.to_string().c_str(), toCheck.test(i), values[i].first, values[i].second);
            return 0;
        }
        //printf("continuing an: %s = %d at %d %d\n", toCheck.to_string().c_str(), toCheck.test(i), values[i].first, values[i].second);
    }
    //std::cout << "Made it throug and\n" << std::endl;
    return 1;
}
/**
 * Runs through the ands, if any of them are true returns true
 * @param toCheck the binary value containing the state to check against
 * @param values the values to try to match
 * @return true if matches atleast one of the OR's, false if no
 */
int checkOr(std::bitset<maxAttributes> toCheck, std::vector<std::vector<std::pair<int, int>>> values) {
    //std::cout << "Values: " << values.size() << std::endl;
    for (int i = 0; i < values.size(); i++) {
        if (checkAnd(toCheck, values[i])) {
            //std::cout << "Fuck Reject\n";
            return 1;
        }
    }
    //std::cout << "Fuck accept\n";
    return 0;
}

void testing() {

    //Construct texting binary numbers;
    std::vector<std::pair<int, int>> test1;
    std::vector<std::pair<int, int>> test2;
    std::bitset<maxAttributes> bTest("1001");

    /** test1 test data: "1111" */
    test1.push_back(std::make_pair(0, 1));
    test1.push_back(std::make_pair(1, 1));
    test1.push_back(std::make_pair(2, 1));
    test1.push_back(std::make_pair(3, 1));

    /** test2 test data: "1001" */
    test2.push_back(std::make_pair(0, 1));
    test2.push_back(std::make_pair(1, 0));
    test2.push_back(std::make_pair(2, 0));
    test2.push_back(std::make_pair(3, 1));

}
void testing2(std::vector<std::vector<std::pair<int,int>>> hardConstraints) {

    //Construct texting binary numbers;
    std::vector<std::pair<int, int>> test1;
    std::vector<std::pair<int, int>> test2;
    //std::bitset<maxAttributes> bTest("1001");

    for (int i = 0; i < hardConstraints.size(); i++){
        for (int j = 0; j < hardConstraints[i].size(); j++){
            std::cout << hardConstraints[i][j].first << ' ' << hardConstraints[i][j].second << std::endl;
        }
        std::cout << std::endl;
    }
    std::vector<int> toTest;
    for(int i = 0; i < 5; i++)
        toTest.emplace_back(i);

    for(int i = 0; i < toTest.size();i++){
        std::bitset<maxAttributes> bTest(toTest[i]);
        std::string s = bTest.to_string();
        //std::reverse(s.begin(),s.end());
        //std::cout << "Test S: " << s << std::endl;
        int nolan = checkOr(bTest, hardConstraints);
        if(nolan){
            std::cout << "Reject: " << bTest.to_string() << std::endl;
        }
        else{
            std::cout << "Accept: " << bTest.to_string() << std::endl;
        }
        bTest = 0;
        s = "";
    }

}

/**
 *
 * @param attributeNames
 * @param hardConstraints
 * @return
 */
std::vector<int> blacklistFunction(int attributeCount, std::vector<std::vector<std::pair<int,int>>> hardConstraints) {
    /*
    for (int i = 0; i < hardConstraints.size(); i++){
        for (int j = 0; j < hardConstraints[i].size(); j++){
            std::cout << hardConstraints[i][j].first << ' ' << hardConstraints[i][j].second << std::endl;
        }
        std::cout << std::endl;
    }
    */
    std::vector<int> blacklist;
    for(int i = 0; i < attributeCount*attributeCount;i++){
        std::bitset<maxAttributes> bTest(i);
        std::string s = bTest.to_string();
        //std::reverse(s.begin(),s.end());
        //std::cout << "Test S: " << s << std::endl;
        if(checkOr(bTest, hardConstraints)){
            //std::cout << "Blacklist: " << i << ' ' << bTest.to_string() << std::endl;
            blacklist.emplace_back(i);
        }
        else{
            //std::cout << "Allow: " << i << ' ' << bTest.to_string() << std::endl;
        }
    }
    return blacklist;
}
/** Calculates Penalty Logic, */
void penaltiesFunction(std::unordered_map<std::string, std::pair<std::string,std::string>> attributeNames, std::vector<std::vector<std::pair<int,int>>> hardConstraints, std::vector<std::vector<std::pair<int,int>>> penalties, std::vector<int> penaltyCosts) {

    //Construct texting binary numbers;
    /*
     *
     * /std::cout << hardConstraints[j][k].first << ' ';
                //
                // td::cout << hardConstraints[j][k].second << '\n';
                if(s[hardConstraints[j][k].first]==hardConstraints[j][k].second){
                    //checkOr(bTest,)
                    //std::cout << "Hard constraint detected!" << s << std::endl;

                }
                //std::cout << "Hard constraint legit " << s[hardConstraints[j][k].first] << std::endl;
     */


    /*
    for(int i = 0; i < attributeNames.size()*attributeNames.size();i++){
        std::bitset<maxAttributes> bTest(i);
        std::string s = bTest.to_string();
        std::reverse(s.begin(),s.end());
        //std::cout << "Test S: " << s << std::endl;
        for(int j=0;j<hardConstraints.size()-1;j++){
            for(int k=0;k<hardConstraints[j].size();k++){

            }
        }
    }
    */

}
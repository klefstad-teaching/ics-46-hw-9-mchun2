#include "ladder.h"

using namespace std;

#define my_assert(e) {cout << #e << ((e) ? " passed" : " failed") << endl;}

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();
    if (abs(len1 - len2) > 1) return false;

    int i = 0;
    int j = 0;
    int cnt = 0;
     while (j < len2 && i < len1) {
        if (str2[j] != str1[i]) {
            if (++cnt > d) return false;

            if (len1 > len2) ++i; 
            else if (len2 > len1) ++j;
            else {
                ++i; ++j; 
            } 
        }
        else {
            ++i; ++j;
        }
    }
    return true;
}

bool is_adjacent(const string &word1, const string &word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue <vector<string>> ladderQueue;
    ladderQueue.push({begin_word});

    set<string> visited;
    visited.insert(begin_word);

    while (!ladderQueue.empty()) {
        vector<string> ladder = ladderQueue.front();
        ladderQueue.pop();

        string lastWord = ladder.back();

        for (const string word : word_list) {
            if (is_adjacent(lastWord,word) && !visited.count(word) ) {
               visited.insert(word);
               vector <string> newLadder = ladder;
               newLadder.push_back(word);

               if (word == end_word) {
                return newLadder;
               }
               ladderQueue.push(newLadder);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file (file_name);
    
    if (!file) {
        error("","", "file not opened");
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }

    cout << "Word ladder found: ";
    for (const string & word : ladder) {
        cout << word << " ";
    }
    cout << endl;
}

// void verify_word_ladder() {
//     set<string> word_list;
//     vector <string> ladder;
//     cout << "loading words" << endl;
//     load_words(word_list, "src/words.txt");
//     cout << "loaded words" << endl;
//     if (word_list.empty()) error("", "", "wordListEmpty");
//     string beginWord = "marty";
//     string endWord = "curls";


//     cout << "generating ladder" << endl;
//     ladder = generate_word_ladder(beginWord, endWord, word_list);
//     cout << "generated ladder" << endl;
//     if (ladder.empty()) error("", "", "ladderEmpty");
//     cout << ladder.size() << endl;
//     print_word_ladder(ladder);
//     cout << endl;
// }

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}


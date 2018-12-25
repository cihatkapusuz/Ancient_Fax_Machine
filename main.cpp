#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
long long int m = 1000000007;
long long int dynamic [1003];
string given_string;
string words[1003];
int n_of_words_in_vocab;
long long int string_hash_table [1003];
long long int words_hash_table [1003];
long long int hasherinho[1003][1003];
long long int power_of_26[1003];

void find_string_hash(){
        string_hash_table[0]=given_string[0]-96;
    for(int i=1; i< given_string.size();i++){
        string_hash_table[i]=(string_hash_table[i-1]*26 + given_string[i]-96)%m;
        if(string_hash_table[i]<0){
            string_hash_table[i] += m;
        }
    }
}
void find_word_hash(){
    for(int i=0; i<n_of_words_in_vocab; i++){
        hasherinho[i][0]= words[i][0]-96;
        for(int j=1; j< words[i].size(); j++){
            hasherinho[i][j]=(hasherinho[i][j-1]*26 + words[i][j]-96)%m;
            if(hasherinho[i][j]<0){
                hasherinho[i][j] +=m;
            }
        }
        words_hash_table[i]=hasherinho[i][words[i].size()-1];
        if(words_hash_table[i]<0){
            words_hash_table[i] += m;
        }
    }

}
long long int particular_hash(int start, int finish){
    if(start==0){
        return string_hash_table[finish];
    }
    long long int part_hash =(string_hash_table[finish]-string_hash_table[start-1]*power_of_26[finish-start+1])%m;
    if(part_hash<0){
        part_hash += m;
    }
    return part_hash;
}
long long int recursive_call(int index){
    if(index == given_string.size()){
        return 1;
    }
    long long int count = 0;
    if(dynamic[index]!=-1){
        return dynamic[index];
    }
    for(int i=0; i<n_of_words_in_vocab; i++){
        if(words[i].size()<= given_string.size() - index && words_hash_table[i]==particular_hash(index,index + (int)words[i].size()-1) && words[i]==given_string.substr(index,(int)words[i].size())){
            count = (count + recursive_call(index + (int)words[i].size()))%m;
            if(count<0){
                count += m;
            }
        }
    }
    dynamic[index]=count;
    return count;
}

int main(int argc, char* argv[]) {

    for (int i = 0; i < 1003; i++) {
        dynamic[i] = -1;
    }
    ifstream infile(argv[1]);
    infile >> given_string >> n_of_words_in_vocab;
    for (int i = 0; i < n_of_words_in_vocab; i++) {
        infile >> words[i];
    }
    power_of_26[0]=1;
    for (int i = 1; i < 1003; i++) {
        power_of_26[i]=(power_of_26[i-1]*26)%m;
    }
    find_string_hash();
    find_word_hash();
    long long int abuse = recursive_call(0);
    ofstream myfile;
    myfile.open(argv[2]);
    myfile<< abuse << endl;
    myfile.close();
    return 0;
}

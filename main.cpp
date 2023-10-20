#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

vector<string> readTxtInLine(const string& inputfile){
    ifstream ifs;
    ifs.open(inputfile.data());
    assert(ifs.is_open());
    
    string sLine;
    vector<string> txtLines;
    while(getline(ifs, sLine)){
        // cout<<sLine<<endl;
        txtLines.push_back(sLine);
    }
    
    ifs.close();
    return txtLines;

}


void readTxtByChar1 (string inputfile){
    ifstream ifs;
    ifs.open(inputfile.data());
    assert(ifs.is_open());

    char cChar;
    while(! ifs.eof()){
        ifs>>cChar;
        cout<<cChar<<endl;
    }
}

void readTxtByChar2(string inputfile){
    ifstream ifs;
    ifs.open(inputfile.data());
    assert(ifs.is_open());

    char cChar;
    while(! ifs.eof()){
        ifs>>noskipws>>cChar;
        cout<<cChar<<endl;
    }
}

vector<int> findWords(const vector<string>& txtLines, string keyword){
    vector<int> linePos;
    int count = 0;
    // for(vector<string>::const_iterator it = txtLines.begin(); it != txtLines.end(); it++)
    for (const auto &line : txtLines){
        bool checkprevAlpha = (line.find(keyword) == 0) || !isalpha(line[line.find(keyword) -1]);
        bool checkendAlpha = !isalpha(line[line.find(keyword) + keyword.size()]);
        
        if(line.find(keyword) != string::npos && checkendAlpha && checkprevAlpha){
            // cout<<line<<endl;
            linePos.push_back(count);
        }
        
        count++;
    }
    return linePos;
}

vector<string> extractQuotedContent(const vector<string> txtLines, const vector<int>& linePos){
    bool startFound = false;
    string accumulated;
    vector<string> result;
    for (const auto& Pos : linePos){
        for (auto i = Pos; i != txtLines.size(); i++) {
                if (!startFound) {
                    size_t startPos = txtLines[i].find('"');
                    if (startPos != string::npos) {
                        size_t endPos = txtLines[i].find('"', startPos + 1);
                        if(endPos != string::npos){
                            result.push_back(txtLines[i].substr(0 , endPos + 1));
                        }else{

                        
                        startFound = true;
                        accumulated += txtLines[i];
                        }
                    }
                } else {
                    size_t endPos = txtLines[i].find('"');
                if (endPos == string::npos) {
                    accumulated += "\n" + txtLines[i];
                } else {
                    accumulated += "\n" + txtLines[i].substr(0, endPos + 1);
                    result.push_back(accumulated);
                    break;  // Exit the inner loop
                }
            }
        }
    }
    return result;
    
}

int main(){

    auto txtcontent = readTxtInLine("example_git.text");
    auto linePos = findWords(txtcontent, "DEPENDS");
    auto QuotedContent = extractQuotedContent(txtcontent, linePos);
    for(auto &i : QuotedContent){
        cout<< i<<endl;
    }
    
    return 0;

};
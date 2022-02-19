#include "../src/RecordLoader.h"
#include "../src/JSONPathParser.h"
#include "../src/StreamProcessor.h"

int main() {
    char* file_path = "../dataset/twitter_sample_small_records.json";
    cout<<"start loading a sequence of small records from "<<file_path<<endl;
    RecordSet* record_set = RecordLoader::loadRecords(file_path);
    if (record_set->size() == 0) {
        cout<<"record loading fails."<<endl;
        return -1;
    }
    cout<<"finish loading a sequence of small records"<<endl;

    string query = "$.entities.urls[*].url";
    cout<<"start generating query automaton for query "<<query<<endl;
    QueryAutomaton qa;
    // update query automaton
    JSONPathParser::updateQueryAutomaton(query, qa);
    cout<<"finish generating query automaton"<<endl;

    cout<<"\nstart executing query "<<query<<endl;
    StreamProcessor processor(qa);
    // process small records one by one
    int num_recs = record_set->size();
    string output = "";
    for (int i = 0; i < num_recs; i++) {
        output.append(processor.runQuery((*record_set)[i]));
    }
    cout<<"finish query execution"<<endl;
    cout<<"matches are: "<<output<<endl;
    return 0;
}

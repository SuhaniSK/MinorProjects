#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to randomly select an element from a vector
string selectRandom(const vector<string>& options) {
    return options[rand() % options.size()];
}

// Function to generate a question based on the CFG
string generateQuestion() {
    // Terminal symbols
    vector<string> aux;
    aux.push_back("is");
    aux.push_back("are");
    aux.push_back("do");
    aux.push_back("does");
    aux.push_back("did");
    aux.push_back("can");
    aux.push_back("will");

    vector<string> pronoun;
    pronoun.push_back("he");
    pronoun.push_back("she");
    pronoun.push_back("it");
    pronoun.push_back("they");
    pronoun.push_back("we");
    pronoun.push_back("you");
    pronoun.push_back("I");

    vector<string> noun;
    noun.push_back("cat");
    noun.push_back("dog");
    noun.push_back("book");
    noun.push_back("movie");
    noun.push_back("song");
    noun.push_back("person");
    noun.push_back("apple");
    noun.push_back("car");

    vector<string> adj;
    adj.push_back("big");
    adj.push_back("small");
    adj.push_back("red");
    adj.push_back("blue");
    adj.push_back("old");
    adj.push_back("new");

    vector<string> verb;
    verb.push_back("run");
    verb.push_back("eat");
    verb.push_back("like");
    verb.push_back("see");
    verb.push_back("know");
    verb.push_back("play");
    verb.push_back("write");
    verb.push_back("read");

    vector<string> wh;
    wh.push_back("who");
    wh.push_back("what");
    wh.push_back("where");
    wh.push_back("when");
    wh.push_back("why");
    wh.push_back("how");

    

    // Randomly select elements to form a question
    /*
   1) S
     →   Q
     → Aux Subj Verb Obj ?
      → can he read the book ?
    2)S
     → Q
     → WH- Aux Subj Verb ?
     → what did you see ?
    3)S
     → Q
     → WH- Verb Subj ?
     → where is the car ?

    
    */
    vector<string> questionTypes;
    questionTypes.push_back("aux");
    questionTypes.push_back("wh-aux");
    questionTypes.push_back("wh-verb");

    string questionType = selectRandom(questionTypes);
    string question;

    if (questionType == "aux") {
        string auxVerb = selectRandom(aux);
        string subj = selectRandom(pronoun);
        string mainVerb;

        if (auxVerb == "do" || auxVerb == "does" || auxVerb == "did") {
            vector<string> baseVerbs;
            baseVerbs.push_back("run");
            baseVerbs.push_back("eat");
            baseVerbs.push_back("like");
            baseVerbs.push_back("see");
            baseVerbs.push_back("know");
            baseVerbs.push_back("play");
            baseVerbs.push_back("write");
            baseVerbs.push_back("read");
            mainVerb = selectRandom(baseVerbs);
        } else {
            mainVerb = selectRandom(verb);
        }

        vector<string> objOptions;
        for (const string& n : noun) {
            objOptions.push_back("the " + n);
            objOptions.push_back("a " + n);
            objOptions.push_back("an " + n);
            objOptions.push_back(n);
        }
        string obj = selectRandom(objOptions);
        question = auxVerb + " " + subj + " " + mainVerb + " " + obj + "?";
    } else if (questionType == "wh-aux") {
        string whWord = selectRandom(wh);
        string auxVerb = selectRandom(aux);
        string subj = selectRandom(pronoun);
        string mainVerb = selectRandom(verb);
        question = whWord + " " + auxVerb + " " + subj + " " + mainVerb + "?";
    } else if (questionType == "wh-verb") {
        string whWord = selectRandom(wh);
        string mainVerb = selectRandom(verb);

        vector<string> subjs;
        for (const string& n : noun) {
            subjs.push_back("the " + n);
        }
        for (const string& p : pronoun) {
            subjs.push_back(p);
        }

        string subj = selectRandom(subjs);
        question = whWord + " " + mainVerb + " " + subj + "?";
    }

    return question;
}

int main() {
    // Initialize random seed
    srand(static_cast<unsigned int>(time(0)));

    // Generate and print 10 random questions
    for (int i = 0; i < 10; ++i) {
        cout << generateQuestion() << endl;
    }

    return 0;
}

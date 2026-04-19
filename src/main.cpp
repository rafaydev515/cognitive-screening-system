#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

enum Trait {
    PATTERN_HUNTER,
    SOCIAL_SMART,
    EXPLORER,
    STABILIZER
};

class Option
{
private:
    string text;
    map<Trait, int> weights;
public:
    Option(string t, map<Trait, int> w) {
        text = t;
        weights = w;
    }

    string getText() const {
        return text;
    }

    const map<Trait, int>& getWeights() const {
        return weights;
    }

};

class Question {
private:
    string text;
    vector<Option> options;

public:
    // Constructor
    Question(string t, const vector<Option>& optionsList) {
        text = t;
        options = optionsList;
    }

    // Getter for text
    string getText() const {
        return text;
    }

    // Getter for options
    const vector<Option>& getOptions() const {
        return options;
    }
};

class Response {
private:
    const Option* selectedOption;

public:
    // Constructor
    Response(const Option* option) {
        selectedOption = option;
    }

    const Option* getSelectedOption() const {
        return selectedOption;
    }
};


class TraitProfile {
private:
    int patternHunter;
    int socialSmart;
    int explorer;
    int stabilizer;

public:
    // Constructor
    TraitProfile() {
        patternHunter = 0;
        socialSmart = 0;
        explorer = 0;
        stabilizer = 0;
    }

    // Add score based on trait
    void addScore(Trait trait, int value) {
        switch(trait) {
            case PATTERN_HUNTER:
                patternHunter += value;
                break;
            case SOCIAL_SMART:
                socialSmart += value;
                break;
            case EXPLORER:
                explorer += value;
                break;
            case STABILIZER:
                stabilizer += value;
                break;
        }
    }

    // Getters
    int getPatternHunter() const 
    { return patternHunter; }
    int getSocialSmart() const 
    { return socialSmart; }
    int getExplorer() const 
    { return explorer; }
    int getStabilizer() const 
    { return stabilizer; }
};

class ScoringEngine {
public:
    void processResponse(Response& response, TraitProfile& profile) {
       const Option* option = response.getSelectedOption();
        const map<Trait, int>& weights = option->getWeights();

        for (auto& pair : weights) {
            Trait trait = pair.first;
            int weight = pair.second;

           int score = weight; // direct mapping from selected option

            profile.addScore(trait, score);
        }
    }
};
void printRawScores(const TraitProfile& profile) {
    cout << "\n\t\tRaw Trait Scores:\n";
    cout << "\t\t\tPattern Hunter: " << profile.getPatternHunter() << endl;
    cout << "\t\t\tSocial Smart: " << profile.getSocialSmart() << endl;
    cout << "\t\t\tExplorer: " << profile.getExplorer() << endl;
    cout << "\t\t\tStabilizer: " << profile.getStabilizer() << endl;
}

class NormalizedProfile
{
private:
    double patternHunter;
    double socialSmart;
    double explorer;
    double stabilizer;
public:
    NormalizedProfile(double ph, double ss, double ex, double st) {
        patternHunter = ph;
        socialSmart = ss;
        explorer = ex;
        stabilizer = st;
    } 
    
    
    double getPatternHunter ()
    { return patternHunter; }
    double getSocialSmart ()
    { return socialSmart; } 
    double getExplorer ()
    { return explorer; }
    double getStabilizer ()
    { return stabilizer; }

    };

    class MaxScoreCalculator {
        public:
            map<Trait, int> compute(const vector<Question>& questions);
};
	map<Trait, int> MaxScoreCalculator::compute(const vector<Question>& questions) {
    map<Trait, int> maxScores;

    for (auto& q : questions) {

        int maxPH = 0, maxSS = 0, maxEX = 0, maxST = 0;

        const vector<Option>& options = q.getOptions();

        for (auto& opt : options) {
            const map<Trait, int>& weights = opt.getWeights();

            for (auto& pair : weights) {
                Trait trait = pair.first;
                int weight = pair.second;

                switch(trait) {
                    case PATTERN_HUNTER: maxPH = max(maxPH, weight); break;
                    case SOCIAL_SMART:   maxSS = max(maxSS, weight); break;
                    case EXPLORER:       maxEX = max(maxEX, weight); break;
                    case STABILIZER:     maxST = max(maxST, weight); break;
                }
            }
        }

        maxScores[PATTERN_HUNTER] += maxPH;
        maxScores[SOCIAL_SMART] += maxSS;
        maxScores[EXPLORER] += maxEX;
        maxScores[STABILIZER] += maxST;
    }

    return maxScores;
}

    class NormalizationEngine {
public:
    NormalizedProfile normalize(const TraitProfile& profile,
                                const map<Trait,int>& maxScores);
};
NormalizedProfile NormalizationEngine::normalize(
    const TraitProfile& profile,
    const map<Trait,int>& maxScores)
{
    double ph =0;
    double ss =0;
    double ex =0;
    double st =0;
    {
    if (maxScores.at(PATTERN_HUNTER) != 0)
        ph = (profile.getPatternHunter() / (double)maxScores.at(PATTERN_HUNTER)) * 100;
    else
        ph = 0;
    if(maxScores.at(SOCIAL_SMART) != 0)
         ss = (profile.getSocialSmart() / (double)maxScores.at(SOCIAL_SMART)) * 100;
    else
        ss = 0;
    if(maxScores.at(EXPLORER) != 0)
         ex = (profile.getExplorer() / (double)maxScores.at(EXPLORER)) * 100;
    else
        ex = 0;
    if(maxScores.at(STABILIZER) != 0)
         st = (profile.getStabilizer() / (double)maxScores.at(STABILIZER)) * 100;
    else
        st = 0;
    }     
    return NormalizedProfile(ph, ss, ex, st);
}
struct ClassificationResult {
    Trait dominant;
    Trait secondary;
    string profileType;
};

class ClassificationEngine {
    private:
            

    public:

    ClassificationResult classify( NormalizedProfile& profile) {

    vector<pair<Trait, double>> scores = {
        {PATTERN_HUNTER, profile.getPatternHunter()},
        {SOCIAL_SMART,   profile.getSocialSmart()},
        {EXPLORER,       profile.getExplorer()},
        {STABILIZER,     profile.getStabilizer()}
    };

    sort(scores.begin(), scores.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

 int count60 = 0, count35 = 0, count29 = 0;
    for (const auto& s : scores) {
        if (s.second >= 60) count60++;  // clearly dominant
        if (s.second >= 35) count35++;  // meaningfully elevated
        if (s.second >= 29) count29++;  // present
}

    string profileType;

    if      (count60 >= 1) profileType = "Dominant"; // 1 trait clearly leads
    else if (count35 >= 2) profileType = "Dual";     // 2 traits both elevated
    else if (count29 >= 3) profileType = "Triad";    // spread across 3 traits
    else                   profileType = "Mixed";    // no clear pattern
    
    return {scores[0].first, scores[1].first, profileType};
}
};

     //helper function to convert trait enum to string for display
     string traitToString(Trait t) {
    switch(t) {
        case PATTERN_HUNTER: return "Pattern Hunter";
        case SOCIAL_SMART: return "Social Smart";
        case EXPLORER: return "Explorer";
        case STABILIZER: return "Stabilizer";
        default: return "Unknown";
    }
}
class InterpretationEngine {
public:
    string interpret(ClassificationResult& result) {

        string interpretation = "";

        // -------- Profile Type Base Meaning --------
        if (result.profileType == "Triad") {
            interpretation += "You are highly adaptable with strengths across multiple cognitive styles.\n";
        }
        else if (result.profileType == "Dual") {
            interpretation += "You have two strong cognitive drivers that shape your behavior.\n";
        }
        else if (result.profileType == "Dominant") {
            interpretation += "You rely heavily on a single dominant cognitive approach.\n";
        }
        else {
            interpretation += "You show a balanced but less pronounced cognitive pattern.\n";
        }

        // -------- Dominant + Secondary Combination --------
        Trait d = result.dominant;
        Trait s = result.secondary;

        interpretation += "\n\t\tYour cognitive style: ";

// PH dominant
        if (d == PATTERN_HUNTER && s == SOCIAL_SMART)
            interpretation += "\n\t\t\tStrategic Communicator - You combine logic with social awareness.";

        else if (d == PATTERN_HUNTER && s == EXPLORER)
            interpretation += "\n\t\t\tAnalytical Explorer - You seek patterns while exploring new ideas.";

        else if (d == PATTERN_HUNTER && s == STABILIZER)
            interpretation += "\n\t\t\tStructured Thinker - You value logic with stability.";

// SS dominant
        else if (d == SOCIAL_SMART && s == PATTERN_HUNTER)
            interpretation += "\n\t\t\tEmpathic Analyst - You read people deeply and back it with sharp logical thinking.";

        else if (d == SOCIAL_SMART && s == EXPLORER)
            interpretation += "\n\t\t\tAdaptive Connector - You explore through people and interaction.";

        else if (d == SOCIAL_SMART && s == STABILIZER)
            interpretation += "\n\t\t\tSupportive Organizer - You balance people and structure.";

// EX dominant
        else if (d == EXPLORER && s == PATTERN_HUNTER)
            interpretation += "\n\t\t\tCurious Investigator - You experiment freely but always search for the underlying logic.";

        else if (d == EXPLORER && s == SOCIAL_SMART)
            interpretation += "\n\t\t\tCreative Collaborator - You chase new ideas and bring others along with you.";

        else if (d == EXPLORER && s == STABILIZER)
            interpretation += "\n\t\t\tBalanced Executor - You explore but maintain control and consistency.";

// ST dominant
        else if (d == STABILIZER && s == PATTERN_HUNTER)
            interpretation += "\n\t\t\tPrecise Planner - You build reliable systems grounded in deep analytical thinking.";

        else if (d == STABILIZER && s == SOCIAL_SMART)
            interpretation += "\n\t\t\tSteady Supporter - You create safe, consistent environments where people feel secure.";

        else if (d == STABILIZER && s == EXPLORER)
            interpretation += "\n\t\t\tCautious Innovator - You are open to new ideas but only move when the ground feels solid.";

        else
            interpretation += "\n\t\t\tUnique combination of traits.";

        // -------- Add trait-specific reinforcement --------
        interpretation += "\n\n\t\tDominant Trait Insight: ";

        switch(result.dominant) {
            case PATTERN_HUNTER:
                interpretation += "\n\t\t\tYou naturally analyze patterns and systems.";
                break;
            case SOCIAL_SMART:
                interpretation += "\n\t\t\tYou understand and navigate social dynamics effectively.";
                break;
            case EXPLORER:
                interpretation += "\n\t\t\tYou are driven by curiosity and experimentation.";
                break;
            case STABILIZER:
                interpretation += "\n\t\t\tYou value consistency, structure, and reliability.";
                break;
        }

        return interpretation;
    }
};

   class QuestionLoader
   {
    public :
    vector<Question> loadQuestions(const string& filename) {
        
        ifstream file(filename);
        string line;
        string currentquestiontext;
        vector<Option> currentOptions;
        string currentOptionText;
        vector<Question> questions;

        if (!file) {
        cout << "Error: File not found\n";
        return {};
}

        while (getline(file, line)) {

            if (line.empty() || line[0] == '#') 
            continue; // skip empty lines

            if (line.rfind("[Q]", 0) == 0) {
                // New question
                if (!currentquestiontext.empty()) {
                    questions.push_back(Question(currentquestiontext, currentOptions));
                    currentOptions.clear();
                }
                string content = line.substr(4);  // removes "[Q] "
                    size_t pos = content.find('|');

                    if (pos != string::npos)
                    currentquestiontext = content.substr(pos + 1);
            }
            else if (line.rfind("[OPT]", 0) == 0) {
                    string content = line.substr(6);
                    size_t pos = content.find('|');

                    if (pos != string::npos)
                    currentOptionText = content.substr(pos + 1);
                    }

            else if (line.rfind("[SCORE]", 0) == 0) {
                    string content = line.substr(8);

                    stringstream ss(content);
                    string a, b, c, d;

                    getline(ss, a, '|');
                    getline(ss, b, '|');
                    getline(ss, c, '|');
                    getline(ss, d, '|');

                map<Trait, int> weights;
                weights[PATTERN_HUNTER] = stoi(a);
                weights[SOCIAL_SMART] = stoi(b);
                weights[EXPLORER] = stoi(c);
                weights[STABILIZER] = stoi(d);

                currentOptions.push_back(Option(currentOptionText, weights));

        }

    }
    if (!currentquestiontext.empty()) {
    questions.push_back(Question(currentquestiontext, currentOptions));
}
         return questions;
     }            
    
  };

class ScreeningSystem {
    private:
        QuestionLoader loader;
        ScoringEngine scorer;
        NormalizationEngine normalizer;
        ClassificationEngine classifier;
        InterpretationEngine interpreter;

        vector<Question> questions;
        TraitProfile profile;

    public:

        void run();
            
};
void ScreeningSystem::run() {
    questions = loader.loadQuestions("data/questions.txt");

    if (questions.empty()) {
        cout << "No questions loaded.\n";
        return;
    }


    for (auto& q : questions) {
        cout << "\n\n\t\t" << q.getText() << endl;

        const vector<Option>& options = q.getOptions();

        for (size_t i = 0; i < options.size(); i++) {
            cout<<"\t\t" << i + 1 << ". " << options[i].getText() << endl;
        }

        int input;
        cout << "Select an option (1-" << options.size() << "): ";

        while (!(cin >> input) || input < 1 || (size_t)input > options.size()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again: ";
        }

        const Option* selectedOption = &options[input - 1];

        Response response(selectedOption);
        scorer.processResponse(response, profile);
    }

    cout << "\n\t\t\t===== RESULTS =====\n";

    printRawScores(profile);
    
    MaxScoreCalculator calculator;
    NormalizationEngine normalizer;
    ClassificationEngine classifier;

    map<Trait,int> maxScores = calculator.compute(questions);
    NormalizedProfile norm = normalizer.normalize(profile, maxScores);
    ClassificationResult result = classifier.classify(norm);

    cout << "\n\t\tNormalized Scores:\n";
    cout << fixed << setprecision(2); // format to 2 decimal places
    cout << "\t\t\tPattern Hunter: " << norm.getPatternHunter() <<"%"<< endl;
    cout << "\t\t\tSocial Smart: " << norm.getSocialSmart() <<"%"<< endl;
    cout << "\t\t\tExplorer: " << norm.getExplorer() <<"%"<< endl;
    cout << "\t\t\tStabilizer: " << norm.getStabilizer() <<"%"<< endl;

    cout << "\n\t\tProfile Type: " << result.profileType << endl;
    cout << "\t\t\tDominant Trait: " << traitToString(result.dominant) << endl;
    cout << "\t\t\tSecondary Trait: " << traitToString(result.secondary) << endl;

    cout << "\n\t\tInterpretation:\n";
    cout <<"\t\t\t"<< interpreter.interpret(result) << endl;
};
void startScreening() {
    int startChoice = 0;
            cout << "\n\tWelcome to the Cognitive Screening System!\n";
            cout << "\tYou have to answer the given questions to determine your cognitive profile.\n";
            cout << "\tPress 1 to start the screening or 0 to exit: ";
            while (!(cin >> startChoice) || (startChoice != 0 && startChoice != 1)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter 1 to start or 0 to exit: ";
            }
            if (startChoice == 1) {
                
                ScreeningSystem system;
                system.run();
                    }
            else {
                cout << "Exiting the program. Goodbye!\n";        
    
            }
        }

    int main()
{
    startScreening();
    
    return 0;
}


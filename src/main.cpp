#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
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
    cout << "\nRaw Trait Scores:\n";
    cout << "Pattern Hunter: " << profile.getPatternHunter() << endl;
    cout << "Social Smart: " << profile.getSocialSmart() << endl;
    cout << "Explorer: " << profile.getExplorer() << endl;
    cout << "Stabilizer: " << profile.getStabilizer() << endl;
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

    ClassificationResult classify(NormalizedProfile& profile) {

    vector<pair<Trait, double>> scores = {
        {PATTERN_HUNTER, profile.getPatternHunter()},
        {SOCIAL_SMART, profile.getSocialSmart()},
        {EXPLORER, profile.getExplorer()},
        {STABILIZER, profile.getStabilizer()}
    };

    int count65 = 0;
    int count55 = 0;

    for (auto& s : scores) {
        if (s.second >= 65) count65++;
        if (s.second >= 55) count55++;
    }

    sort(scores.begin(), scores.end(),
        [](auto& a, auto& b) {
            return a.second > b.second;
        });

    Trait dominant = scores[0].first;
    Trait secondary = scores[1].first;

    string profileType;

    if (count55 >= 2)
        profileType = "Dual";
    else if (count65 >= 1)
        profileType = "Dominant";
    else
        profileType = "Mixed";

    return {dominant, secondary, profileType};
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

        interpretation += "\nYour cognitive style: ";

        if (d == PATTERN_HUNTER && s == SOCIAL_SMART)
            interpretation += "Strategic Communicator – You combine logic with social awareness.";

        else if (d == PATTERN_HUNTER && s == EXPLORER)
            interpretation += "Analytical Explorer – You seek patterns while exploring new ideas.";

        else if (d == PATTERN_HUNTER && s == STABILIZER)
            interpretation += "Structured Thinker – You value logic with stability.";

        else if (d == SOCIAL_SMART && s == EXPLORER)
            interpretation += "Adaptive Connector – You explore through people and interaction.";

        else if (d == SOCIAL_SMART && s == STABILIZER)
            interpretation += "Supportive Organizer – You balance people and structure.";

        else if (d == EXPLORER && s == STABILIZER)
            interpretation += "Balanced Executor – You explore but maintain control and consistency.";

        else
            interpretation += "Unique combination of traits.";

        // -------- Add trait-specific reinforcement --------
        interpretation += "\n\nDominant Trait Insight: ";

        switch(result.dominant) {
            case PATTERN_HUNTER:
                interpretation += "You naturally analyze patterns and systems.";
                break;
            case SOCIAL_SMART:
                interpretation += "You understand and navigate social dynamics effectively.";
                break;
            case EXPLORER:
                interpretation += "You are driven by curiosity and experimentation.";
                break;
            case STABILIZER:
                interpretation += "You value consistency, structure, and reliability.";
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
                    int pos = content.find('|');

                    if (pos != string::npos)
                    currentquestiontext = content.substr(pos + 1);
            }
            else if (line.rfind("[OPT]", 0) == 0) {
                    string content = line.substr(6);
                    int pos = content.find('|');

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
        cout << "\n" << q.getText() << endl;

        const vector<Option>& options = q.getOptions();

        for (size_t i = 0; i < options.size(); i++) {
            cout << i + 1 << ". " << options[i].getText() << endl;
        }

        int input;
        cout << "Select an option (1-" << options.size() << "): ";

        while (!(cin >> input) || input < 1 || input > options.size()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again: ";
        }

        const Option* selectedOption = &options[input - 1];

        Response response(selectedOption);
        scorer.processResponse(response, profile);
    }

    cout << "\n===== RESULTS =====\n";

    printRawScores(profile);
    
    MaxScoreCalculator calculator;
    NormalizationEngine normalizer;
    ClassificationEngine classifier;

    map<Trait,int> maxScores = calculator.compute(questions);
    NormalizedProfile norm = normalizer.normalize(profile, maxScores);
    ClassificationResult result = classifier.classify(norm);

    cout << "\nNormalized Scores:\n";
    cout << "Pattern Hunter: " << norm.getPatternHunter() << endl;
    cout << "Social Smart: " << norm.getSocialSmart() << endl;
    cout << "Explorer: " << norm.getExplorer() << endl;
    cout << "Stabilizer: " << norm.getStabilizer() << endl;

    cout << "\nProfile Type: " << result.profileType << endl;
    cout << "Dominant Trait: " << traitToString(result.dominant) << endl;
    cout << "Secondary Trait: " << traitToString(result.secondary) << endl;

    cout << "\nInterpretation:\n";
    cout << interpreter.interpret(result) << endl;
};


    int main()
{
    ScreeningSystem system;
    system.run();
    return 0;
}


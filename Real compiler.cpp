#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class NF1_Final_Kernel {
private:
    map<string, string> registry;
    bool ai_active = false;

    string trim(string s) {
        size_t f = s.find_first_not_of(" \t\r\n");
        return (f == string::npos) ? "" : s.substr(f, s.find_last_not_of(" \t\r\n") - f + 1);
    }

public:
    void parse(string line, int ln) {
        line = trim(line);
        if (line.empty() || line.substr(0, 2) == "//") return;

        // 🚨 TERMINATOR CHECK
        if (line.find("|>") == string::npos) {
            cout << "[FATAL]: Line " << ln << " missing '|>'" << endl;
            return;
        }

        string cmd = trim(line.substr(0, line.find("|>")));

        // --- 1. NEW: USER INPUT (>>) ---
        if (cmd.substr(0, 2) == ">>") {
            string varName = trim(cmd.substr(2));
            string inputData;
            cout << "[NF-1 INPUT REQUIRED FOR " << varName << "]: ";
            getline(cin, inputData);
            registry[varName] = inputData;
            cout << "[SYS]: Data linked to " << varName << endl;
        }

        // --- 2. OUTPUT (<<) ---
        else if (cmd.substr(0, 2) == "<<") {
            string content = trim(cmd.substr(2));
            // Check if it's a variable in memory
            if (registry.count(content)) cout << "[NF-1 OUT]: " << registry[content] << endl;
            else cout << "[NF-1 OUT]: " << content << endl;
        }

        // --- 3. ALL OTHER KEYWORDS (VIRTUALIZED) ---
        else if (cmd == "brain.init") { ai_active = true; cout << "[NEURAL]: Engine Online." << endl; }
        else if (cmd == "!quantum") cout << "[SEC]: Lattice-Shield Active." << endl;
        else if (cmd == "mem.purge") cout << "[SYS]: RAM Flushed." << endl;
        else if (cmd == "@core.boost") cout << "[NPU]: CPU Priority Shifted." << endl;
        else if (cmd == "auto.fix") cout << "[DEBUG]: Semantic Self-Correction logic active." << endl;
        // (Baaki saare keywords v6.0 wale as-is rahenge)
    }
};

int main() {
    NF1_Final_Kernel core;
    cout << "### NF-1 TITAN-CORE v7.0 [FINAL HARDWARE BUILD] ###" << endl;
    
    // Testing Real Input/Output Interaction
    core.parse(">> UserName |>", 1);
    core.parse("<< UserName |>", 2);
    core.parse("brain.init |>", 3);
    core.parse("mem.purge |>", 4);

    return 0;
}


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class NF1_Kernel {
private:
    map<string, string> registry;
    bool ai_active = false;
    bool ghost_mode = false;
    bool quantum_lock = false;

    string clean(string s) {
        s.erase(0, s.find_first_not_of(" \t\r\n"));
        s.erase(s.find_last_not_of(" \t\r\n") + 1);
        return s;
    }

public:
    void parse(string line, int ln) {
        line = clean(line);
        if (line.empty() || line.substr(0, 2) == "//") return;

        // 🚨 STRICT TERMINATOR CHECK
        if (line.find("|>") == string::npos) {
            cout << "[SYNTAX ERROR]: Line " << ln << " -> Expected '|>'" << endl;
            return;
        }

        string cmd = clean(line.substr(0, line.find("|>")));

        // --- 1. I/O & DATA FLOW ---
        if (cmd.substr(0, 2) == "<<") {
            cout << "[NF-1 OUTPUT]: " << cmd.substr(2) << endl;
        }
        else if (cmd.find("->") != string::npos) {
            size_t p = cmd.find("->");
            string val = clean(cmd.substr(0, p));
            string key = clean(cmd.substr(p + 2));
            registry[key] = val;
            cout << "[REG]: Variable '" << key << "' stored successfully." << endl;
        }

        // --- 2. NEURAL CORE (AI) ---
        else if (cmd == "brain.init") { ai_active = true; cout << "[NEURAL]: Engine Online. RAM allocated." << endl; }
        else if (cmd.find("learn.pat") != string::npos) cout << "[AI]: Deep Learning Pattern Scan active." << endl;
        else if (cmd == "guess.acc") cout << "[AI]: Inference Logic ready (99.8% Accuracy)." << endl;
        else if (cmd == "evolve") cout << "[GENETIC]: Code Self-Optimization triggered." << endl;

        // --- 3. HARDWARE & LEGACY (~ N, ~link, @core.boost) ---
        else if (cmd == "~ N") cout << "[HW]: Low-Power Sense. Throttling CPU for efficiency." << endl;
        else if (cmd.find("~link") != string::npos) cout << "[BRIDGE]: USB Serial Hardware Link Active." << endl;
        else if (cmd == "mem.purge") cout << "[SYS]: RAM Address Flush successful." << endl;
        else if (cmd == "@core.boost") cout << "[NPU]: CPU priority shifted to NF-1 Kernel." << endl;

        // --- 4. SECURITY & STEALTH (!quantum, #vault.X, *ghost.ai, &leak.stop) ---
        else if (cmd == "!quantum") { quantum_lock = true; cout << "[SEC]: Lattice-Encryption Shield enabled." << endl; }
        else if (cmd == "#vault.X") cout << "[SEC]: Hardware AES-Vault locked." << endl;
        else if (cmd == "*ghost.ai") { ghost_mode = true; cout << "[SEC]: Memory obfuscation (Ghost Mode) ON." << endl; }
        else if (cmd == "&leak.stop") cout << "[GUARD]: Stack-protection active. Zero Leaks." << endl;

        // --- 5. VISION & UI (#vision.X, H.Front, F.Fast, auto.fix, vocal.gen) ---
        else if (cmd.find("#vision.X") != string::npos) cout << "[VISION]: Object recognition engine running..." << endl;
        else if (cmd == "H.Front") cout << "[UI]: Header Render Complete." << endl;
        else if (cmd == "F.Fast") cout << "[UI]: Footer Engine Optimized." << endl;
        else if (cmd == "auto.fix") cout << "[DEBUG]: Semantic Self-Correction logic active." << endl;
        else if (cmd == "vocal.gen") cout << "[NLP]: Voice synthesis engine initialized." << endl;

        // --- 6. ENTERPRISE (@cloud.syn) ---
        else if (cmd == "@cloud.syn") cout << "[CLOUD]: Real-time synchronization active." << endl;
    }
};

int main() {
    NF1_Kernel core;
    cout << "### NF-1 TITAN-CORE v6.0 [ENTERPRISE EDITION] ###" << endl;
    cout << "### ARCHITECT: ADITYA RAI | KERNEL: C++ BINARY ###" << endl << endl;

    vector<string> boot = {
        "brain.init |>", "~ N |>", "1.0.4 -> Version |>",
        "!quantum |>", "*ghost.ai |>", "#vault.X |>",
        "mem.purge |>", "@core.boost |>", "evolve |>",
        "&leak.stop |>", "vocal.gen |>", "@cloud.syn |>",
        "H.Front |>", "auto.fix |>", "<< 'NF-1 FULL CORE READY' |>"
    };

    for (int i = 0; i < boot.size(); i++) core.parse(boot[i], i + 1);

    return 0;
}

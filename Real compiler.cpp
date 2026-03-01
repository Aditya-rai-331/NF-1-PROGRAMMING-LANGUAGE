#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

// ================= OPCODES (UPDATED) =================
enum OpCode {
    OP_BOOT   = 0x01, OP_PUSH   = 0x02,
    OP_ADD    = 0x03, OP_SUB    = 0x0E, OP_MUL    = 0x0F, OP_DIV    = 0x10, // Math Core
    OP_STORE  = 0x04, OP_LOAD   = 0x05, OP_PRINT  = 0x06,
    OP_INPUT  = 0x07, OP_PURGE  = 0x08, OP_STATS  = 0x09,
    OP_SNAP   = 0x0A, OP_SYNC   = 0x0B, OP_GUARD  = 0x0C,
    OP_BOOST  = 0x0D, 
    OP_THEME  = 0x11, OP_GRAD     = 0x12, OP_BTN      = 0x13, // UI Core
    OP_HALT   = 0xFF
};

// ================= VIRTUAL MACHINE =================
class NF1_VM {
private:
    stack<int> st;
    int memory[1024] = {0};
    chrono::high_resolution_clock::time_point start;

public:
    void boot() {
        start = chrono::high_resolution_clock::now();
        cout << "[NF1] Engine Booted v10.0\n";
    }

    void run(const vector<uint8_t>& code) {
        boot();
        size_t pc = 0;
        while (pc < code.size()) {
            uint8_t op = code[pc++];
            switch (op) {
                case OP_BOOT: cout << "[SYS] brain.init complete\n"; break;
                case OP_PUSH: {
                    int val = 0;
                    for(int i=0;i<4;i++) val |= code[pc++] << (i*8);
                    st.push(val); break;
                }
                // --- MATH LOGIC ---
                case OP_ADD: { int b=st.top(); st.pop(); int a=st.top(); st.pop(); st.push(a+b); break; }
                case OP_SUB: { int b=st.top(); st.pop(); int a=st.top(); st.pop(); st.push(a-b); break; }
                case OP_MUL: { int b=st.top(); st.pop(); int a=st.top(); st.pop(); st.push(a*b); break; }
                case OP_DIV: {
                    int b=st.top(); st.pop(); int a=st.top(); st.pop();
                    if(b==0) { cout << "[ERR] Math Error: Div by 0\n"; return; }
                    st.push(a/b); break;
                }
                // --- UI LOGIC ---
                case OP_THEME: cout << "[UI] Theme Applied (~n): Interface Color Updated.\n"; break;
                case OP_GRAD:  cout << "[UI] Gradient Set (~i): Dual-Tone Background Active.\n"; break;
                case OP_BTN:   cout << "[UI] Component Rendered (btn): Action Button Created.\n"; break;
                
                case OP_STORE: {
                    int addr = st.top(); st.pop(); int val = st.top(); st.pop();
                    if(addr>=0 && addr<1024) memory[addr]=val; break;
                }
                case OP_LOAD: {
                    int addr = st.top(); st.pop();
                    if(addr>=0 && addr<1024) st.push(memory[addr]); break;
                }
                case OP_PRINT: if(!st.empty()) cout << "[OUT] " << st.top() << endl; break;
                case OP_INPUT: { int x; cout << "[IN] Enter Value: "; cin>>x; st.push(x); break; }
                case OP_PURGE: for(int i=0;i<1024;i++) memory[i]=0; while(!st.empty()) st.pop(); cout<<"[MEM] cleared\n"; break;
                case OP_STATS: cout<<"[STAT] stack="<<st.size()<<" memory=1024\n"; break;
                case OP_BOOST: cout<<"[PERF] performance hint enabled\n"; break;
                case OP_HALT: {
                    auto end = chrono::high_resolution_clock::now();
                    auto dur = chrono::duration_cast<chrono::milliseconds>(end-start);
                    cout<<"[EXIT] "<<dur.count()<<" ms\n"; return;
                }
                default: cout<<"[ERR] invalid opcode\n"; return;
            }
        }
    }
};

// ================= COMPILER =================
class NF1_Compiler {
public:
    vector<uint8_t> compile(const string& file) {
        ifstream in(file);
        vector<uint8_t> bc;
        string token;
        while(in >> token) {
            if(token=="brain.init") bc.push_back(OP_BOOT);
            else if(token=="PUSH") {
                int v; in >> v; bc.push_back(OP_PUSH);
                for(int i=0;i<4;i++) bc.push_back((v>>(i*8))&0xFF);
            }
            else if(token=="ADD") bc.push_back(OP_ADD);
            else if(token=="SUB") bc.push_back(OP_SUB);
            else if(token=="MUL") bc.push_back(OP_MUL);
            else if(token=="DIV") bc.push_back(OP_DIV);
            else if(token=="~n")  bc.push_back(OP_THEME); // Color Theme
            else if(token=="~i")  bc.push_back(OP_GRAD);  // Gradient Theme
            else if(token=="btn") bc.push_back(OP_BTN);   // Button
            else if(token=="STORE") bc.push_back(OP_STORE);
            else if(token=="LOAD") bc.push_back(OP_LOAD);
            else if(token=="<<") bc.push_back(OP_PRINT);
            else if(token==">>") bc.push_back(OP_INPUT);
            else if(token=="mem.purge") bc.push_back(OP_PURGE);
            else if(token=="stats.show") bc.push_back(OP_STATS);
            else if(token=="core.boost") bc.push_back(OP_BOOST);
            else if(token=="exit") bc.push_back(OP_HALT);
        }
        return bc;
    }
};

int main(int argc, char* argv[]) {
    if(argc<2){ cout<<"Usage: nf1 program.nf1\n"; return 0; }
    NF1_Compiler compiler; NF1_VM vm;
    auto bytecode = compiler.compile(argv[1]);
    ofstream out("program.nfb", ios::binary);
    out.write((char*)bytecode.data(), bytecode.size());
    out.close();
    cout<<"Compiled → program.nfb ("<<bytecode.size()<<" bytes)\n";
    vm.run(bytecode);
    return 0;
}

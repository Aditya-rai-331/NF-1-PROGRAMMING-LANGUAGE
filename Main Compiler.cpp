#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

// ================= OPCODES (FINAL v11.0) =================
enum OpCode {
    OP_BOOT   = 0x01, OP_PUSH   = 0x02,
    OP_ADD    = 0x03, OP_SUB    = 0x0E, OP_MUL    = 0x0F, OP_DIV    = 0x10, // Math Core
    OP_STORE  = 0x04, OP_LOAD   = 0x05, OP_PRINT  = 0x06,
    OP_INPUT  = 0x07, OP_PURGE  = 0x08, OP_STATS  = 0x09,
    OP_THEME  = 0x11, OP_GRAD    = 0x12, OP_BTN     = 0x13, // UI Core
    OP_MARK   = 0x14, OP_LOOPIF = 0x15, // Loop Core (NEW)
    OP_HALT   = 0xFF
};

// ================= VIRTUAL MACHINE =================
class NF1_VM {
private:
    stack<int> st;
    int memory[1024] = {0};
    chrono::high_resolution_clock::time_point start;

public:
    void run(const vector<uint8_t>& code) {
        start = chrono::high_resolution_clock::now();
        cout << "[NF1] Engine v11.0 Online\n";
        size_t pc = 0;

        while (pc < code.size()) {
            uint8_t op = code[pc++];
            switch (op) {
                case OP_BOOT: cout << "[SYS] brain.init: Kernels Ready\n"; break;
                case OP_PUSH: {
                    int val = 0;
                    for(int i=0;i<4;i++) val |= code[pc++] << (i*8);
                    st.push(val); break;
                }
                case OP_ADD: if(st.size()>=2){ int b=st.top(); st.pop(); int a=st.top(); st.pop(); st.push(a+b); } break;
                case OP_SUB: if(st.size()>=2){ int b=st.top(); st.pop(); int a=st.top(); st.pop(); st.push(a-b); } break;
                case OP_MUL: if(st.size()>=2){ int b=st.top(); st.pop(); int a=st.top(); st.pop(); st.push(a*b); } break;
                case OP_DIV: if(st.size()>=2 && st.top()!=0){ int b=st.top(); st.pop(); int a=st.top(); st.pop(); st.push(a/b); } 
                             else { if(!st.empty() && st.top()==0) cout<<"[ERR] DivByZero\n"; } break;
                
                case OP_THEME: cout << "[UI] Theme Updated (~n)\n"; break;
                case OP_GRAD:  cout << "[UI] Gradient Mesh Applied (~i)\n"; break;
                case OP_BTN:   cout << "[UI] Button Component Rendered\n"; break;

                case OP_MARK: break; // Mark is a placeholder for compiler
                case OP_LOOPIF: {
                    int target = 0;
                    for(int i=0;i<4;i++) target |= code[pc++] << (i*8);
                    if(!st.empty() && st.top() > 1) {
                        st.top()--; // Decrement counter
                        pc = target; // JUMP BACK
                    } else if (!st.empty()) { st.pop(); } // Exit loop
                    break;
                }

                case OP_PRINT: if(!st.empty()) cout << "[OUT] " << st.top() << endl; break;
                case OP_PURGE: for(int i=0;i<1024;i++) memory[i]=0; while(!st.empty()) st.pop(); cout<<"[MEM] Purged\n"; break;
                case OP_HALT: {
                    auto dur = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now()-start);
                    cout<<"[EXIT] Done in "<<dur.count()<<" ms\n"; return;
                }
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
        map<string, int> labels;

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
            else if(token=="~n")  bc.push_back(OP_THEME);
            else if(token=="~i")  bc.push_back(OP_GRAD);
            else if(token=="btn") bc.push_back(OP_BTN);
            else if(token=="MARK") { string n; in >> n; labels[n] = bc.size(); }
            else if(token=="LOOP") {
                string n; in >> n; bc.push_back(OP_LOOPIF);
                int target = labels[n];
                for(int i=0;i<4;i++) bc.push_back((target>>(i*8))&0xFF);
            }
            else if(token=="<<" ) bc.push_back(OP_PRINT);
            else if(token=="mem.purge") bc.push_back(OP_PURGE);
            else if(token=="exit") bc.push_back(OP_HALT);
        }
        return bc;
    }
};

int main(int argc, char* argv[]) {
    if(argc<2) { cout<<"Usage: nf1 source.nf1\n"; return 0; }
    NF1_Compiler comp; NF1_VM vm;
    auto bc = comp.compile(argv[1]);
    vm.run(bc);
    return 0;
}

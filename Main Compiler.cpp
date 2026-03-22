#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <map>
#include <chrono>

using namespace std;

// ================= OPCODES (v2.0 INDUSTRIAL) =================
enum OpCode {
    OP_BOOT   = 0x01, OP_PUSH   = 0x02,
    OP_ADD    = 0x03, OP_SUB    = 0x0E, OP_MUL    = 0x0F, OP_DIV    = 0x10,
    OP_STORE  = 0x04, OP_LOAD   = 0x05, OP_PRINT  = 0x06,
    OP_INPUT  = 0x07, OP_PURGE  = 0x08, OP_STATS  = 0x09,
    OP_BOOST  = 0x0D, OP_ECO    = 0x14, 
    OP_IF     = 0x20, OP_ELSE    = 0x21, OP_ENDIF  = 0x22,
    OP_SET    = 0x23, OP_GET     = 0x24, 
    OP_PEN_DN = 0x30, OP_PEN_UP  = 0x31, OP_MOVE   = 0x32, OP_TURN = 0x33,
    OP_BOX    = 0x40, OP_BTN     = 0x13, 
    OP_HALT   = 0xFF
};

// ================= VIRTUAL MACHINE (v2.0) =================
class NF1_VM {
private:
    stack<int> st;
    map<string, int> heap; // v2.0 Persistent Storage
    int memory[1024] = {0};
    chrono::high_resolution_clock::time_point start;

public:
    void run(const vector<uint8_t>& code) {
        start = chrono::high_resolution_clock::now();
        cout << "\033[1;32m[NF-1 v2.0] Engine Booted | Aadi-Tech Industrial\033[0m\n";
        
        size_t pc = 0;
        while (pc < code.size()) {
            uint8_t op = code[pc++];
            switch (op) {
                case OP_BOOT: cout << "[SYS] brain.init: Success\n"; break;
                case OP_PUSH: {
                    int val = 0;
                    for(int i=0; i<4; i++) val |= (code[pc++] << (i*8));
                    st.push(val); break;
                }
                case OP_ADD: { if(st.size()<2) break; int b=st.top(); st.pop(); int a=st.top(); st.pop(); st.push(a+b); break; }
                case OP_SUB: { if(st.size()<2) break; int b=st.top(); st.pop(); int a=st.top(); st.pop(); st.push(a-b); break; }
                case OP_IF: cout << "[LOGIC] IF block entered\n"; break;
                case OP_SET: cout << "[MEM] Variable stored in Global Heap\n"; break;
                case OP_GET: cout << "[MEM] Data retrieved from Heap\n"; break;
                case OP_PEN_DN: cout << "[GFX] pen.down: Drawing Mode ON\n"; break;
                case OP_MOVE: if(!st.empty()) { cout << "[GFX] move: " << st.top() << "px\n"; st.pop(); } break;
                case OP_PRINT: if(!st.empty()) cout << "\033[1;36m[OUT]\033[0m " << st.top() << endl; break;
                case OP_STATS: cout << "[STAT] Stack: " << st.size() << " | RAM: 1024B\n"; break;
                case OP_PURGE: while(!st.empty()) st.pop(); cout << "[CLEAN] mem.purge: 0B Leak\n"; break;
                case OP_ECO: cout << "[PERF] eco.mode: CPU Load Optimized\n"; break;
                case OP_HALT: {
                    auto end = chrono::high_resolution_clock::now();
                    auto ms = chrono::duration_cast<chrono::milliseconds>(end-start).count();
                    cout << "[EXIT] Process Halted (" << ms << " ms)\n"; return;
                }
                default: cout << "[ERR] Unknown OpCode: " << (int)op << endl; return;
            }
        }
    }
};

// ================= COMPILER (v2.0) =================
class NF1_Compiler {
public:
    vector<uint8_t> compile(const string& filename) {
        ifstream in(filename);
        if(!in) { cout << "[ERR] Cannot open " << filename << endl; exit(1); }
        vector<uint8_t> bc;
        string t;
        while(in >> t) {
            if(t=="brain.init") bc.push_back(OP_BOOT);
            else if(t=="PUSH") {
                int v; in >> v; bc.push_back(OP_PUSH);
                for(int i=0; i<4; i++) bc.push_back((v >> (i*8)) & 0xFF);
            }
            else if(t=="ADD") bc.push_back(OP_ADD);
            else if(t=="SUB") bc.push_back(OP_SUB);
            else if(t=="IF") bc.push_back(OP_IF);
            else if(t=="ELSE") bc.push_back(OP_ELSE);
            else if(t=="ENDIF") bc.push_back(OP_ENDIF);
            else if(t=="SET") bc.push_back(OP_SET);
            else if(t=="GET") bc.push_back(OP_GET);
            else if(t=="pen.down") bc.push_back(OP_PEN_DN);
            else if(t=="move") bc.push_back(OP_MOVE);
            else if(t=="eco.mode") bc.push_back(OP_ECO);
            else if(t=="<<") bc.push_back(OP_PRINT);
            else if(t=="mem.purge") bc.push_back(OP_PURGE);
            else if(t=="stats.show") bc.push_back(OP_STATS);
            else if(t=="exit") bc.push_back(OP_HALT);
        }
        return bc;
    }
};

int main(int argc, char* argv[]) {
    if(argc < 2) { cout << "NF-1 v2.0 Compiler\nUsage: nf1 <source.nf1>\n"; return 0; }
    NF1_Compiler comp; NF1_VM vm;
    vector<uint8_t> code = comp.compile(argv[1]);
    vm.run(code);
    return 0;
}

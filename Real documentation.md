====================================================================================================
                        NF-1 (Nano Flash-1) v10.0 ENTERPRISE EDITION 
                             Official Technical Specifications
====================================================================================================
Developer: Aditya Rai (Aadi-Tech) | Architecture: 32-Bit Stack Virtual Machine (VM)
Toolchain: Native Compiler (.nf1 -> .nfb) | Status: STABLE v10.0 [UI + MATH ENABLED]
====================================================================================================

| CATEGORY       | KEYWORD      | TECHNICAL NAME    | FUNCTION / MACHINE ACTION                      |
|----------------|--------------|-------------------|------------------------------------------------|
| I/O Logic      | <<           | Standard Out      | Stack data ko screen/console par display karta hai.|
| I/O Logic      | >>           | Standard In       | User se real-time input (integer) collect karta hai|
| Math Core      | ADD          | Addition          | Stack se 2 values ko jodne (Add) ka logic.     |
| Math Core      | SUB          | Subtraction       | Stack values ko ghatane (Subtract) ka logic.   |
| Math Core      | MUL          | Multiplication    | Fast Integer Multiplication logic.             |
| Math Core      | DIV          | Division          | Zero-Safe Integer Division logic.              |
| Interface      | ~n           | Theme Flag        | Single-Color background theme set karta hai.   |
| Interface      | ~i           | Gradient Flag     | Dual-Tone Gradient background apply karta hai.  |
| Interface      | btn          | UI Render         | APK interface ke liye screen par button banata hai|
| Memory         | STORE        | RAM Write         | Data ko specific address (0-1023) par save krta hai|
| Memory         | LOAD         | RAM Read          | Save kiya data wapas stack par calculation ke liye|
| Neural Core    | brain.init   | Neural Bootstrap  | RAM aur VM Engine ko initialize karta hai.     |
| Hardware       | @core.boost  | Priority Shift    | Thread ko High-Performance mode mein dalta hai. |
| Diagnostic     | stats.show   | System Stats      | Stack depth aur memory usage ka live data dikhata hai|
| Cleanup        | mem.purge    | RAM Purge         | Junk saaf karke 0B Memory Leak maintain krta hai|
| Terminator     | |>           | End-of-Line       | Current instruction ko terminate karta hai.    |
| Exit           | exit         | Safe Halt         | Shutdown karke Performance Log (ms) dikhata hai. |

====================================================================================================
[ SAMPLE HYBRID APP SCRIPT ]

brain.init |>
~n = darkblue |>      // UI: Background Theme
btn = Calculate |>    // UI: Action Button
PUSH 500 |>           // Math: Load Value
>> |>                 // I/O: User Input
MUL |>                // Math: Multiply Logic
<< "Result Saved" |>  // I/O: Status Message
stats.show |>         // Diagnostic: Performance
mem.purge |>          // Cleanup: RAM Optimization
exit |>               // Exit: Safe Resource Release

====================================================================================================
(c) 2026 Aditya Rai Enterprises. "Processor in the Mind, Not in the Machine."
====================================================================================================

# ==========================================
# NF-1 (Nano Flash-1) MASTER INTERPRETER v2.0
# Developed by: Aditya Rai (9th Grade)
# Purpose: AI, ML & Hardware-Level Execution
# ==========================================

import time
import random

class NF1_Engine:
    def __init__(self):
        self.memory = {}
        self.ai_active = False
        self.hardware_link = False
        self.thermal_safe = True

    def execute(self, line):
        line = line.strip()
        if not line or line.startswith("//"): return
        if not line.endswith("|>"):
            print(f" [Syntax Error]: Line must end with '|>' -> {line}")
            return
        
        # Cleanup line for processing
        cmd = line.replace("|>", "").strip()

        # --- 1. Basic Output (<<) ---
        if cmd.startswith("<<"):
            content = cmd.replace("<<", "").strip().strip('"')
            print(f" [NF-1 OUTPUT]: {content}")

        # --- 2. Advanced Math Engine ([ | ]) ---
        elif "[" in cmd and "|" in cmd and "]" in cmd:
            parts = cmd.split("]")
            nums = parts[0].replace("[", "").split("|")
            var_name = parts[1].replace("->", "").strip()
            result = int(nums[0]) * int(nums[1])
            self.memory[var_name] = result
            print(f" [MATH]: Calculated {nums[0]} * {nums[1]} = {result}. Stored in {var_name}")

        # --- 3. Hardware & Power Protocol (~ N, ~link) ---
        elif "~ N" in cmd:
            print(" [HARDWARE]: ~N Protocol Active. Optimizing for Low Battery...")
        elif "~link" in cmd:
            self.hardware_link = True
            print(f" [LINK]: Establishing Bridge via {cmd.split('(')[1].split(')')[0]}...")

        # --- 4. Machine Learning & AI (brain, learn, auto.fix) ---
        elif "brain.init" in cmd:
            self.ai_active = True
            print(" [AI-CORE]: Neural Engine Initialized. Ready for Tensors.")
        elif "learn.pat" in cmd:
            print(" [LEARNING]: Analyzing Data Patterns... Model Saved.")
        elif "auto.fix" in cmd:
            print(" [SELF-HEAL]: Real-time Debugger Active. Errors will be auto-corrected.")

        # --- 5. UI & Graphics (H.Front, #img) ---
        elif "H.Front" in cmd:
            title = cmd.split("(")[1].split(")")[0]
            print(f" [UI]: Setting Header Title -> {title}")
        elif "#img" in cmd:
            print(f" [GRAPHICS]: Rendering Image Data...")

        # --- 6. Cybersecurity (*crypt, @sys) ---
        elif "*crypt" in cmd:
            print(" [SECURITY]: AES-256 Encryption Applied to Memory Stream.")
        elif "@sys" in cmd:
            print(f" [SYSTEM]: Kernel Call Executed -> {cmd}")

# --- Test NF-1 Run ---
if __name__ == "__main__":
    nf1 = NF1_Engine()
    print("--- NF-1 PROGRAMMING LANGUAGE ENGINE v2.0 ---")
    
    # Ye hai NF-1 ka asali code jo ye interpreter chalayega
    test_script = [
        '<< "NF-1 Artificial Intelligence Starting..." |>',
        'brain.init(NF1_Core) |>',
        '~ N (Battery_Safe) |>',
        '[50 | 2] -> Speed |>',
        'H.Front(Aadi Tech Portal) |>',
        'auto.fix(Active) |>',
        '*crypt(Secure_Data) |>',
        '<< "System status: Optimizing Logic..." |>'
    ]

    for line in test_script:
        nf1.execute(line)
        time.sleep(0.3) # Simulation delay for hardware feel
        

import os
from kivy.app import App
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.textinput import TextInput
from kivy.uix.button import Button
from kivy.uix.label import Label
from kivy.core.window import Window
from kivy.uix.popup import Popup
from kivy.uix.scrollview import ScrollView

# Premium Dark Interface
Window.clearcolor = (0.01, 0.01, 0.02, 1)

class NF1_Royal_IDE(App):
    def build(self):
        self.title = "AADI-TECH NF-1 ROYAL v11.0"
        self.save_dir = "/sdcard/Download/"
        
        # Root Layout
        root = BoxLayout(orientation='vertical', padding=10, spacing=10)

        # 1. Professional File Manager Bar
        top_bar = BoxLayout(size_hint_y=0.08, spacing=10)
        top_bar.add_widget(Label(text="FILE NAME:", size_hint_x=0.2, font_size='12sp', color=(0, 0.7, 1, 1), bold=True))
        
        self.file_name_input = TextInput(
            text="main.nf1", 
            multiline=False, 
            size_hint_x=0.5,
            background_color=(0.1, 0.1, 0.15, 1),
            foreground_color=(1, 1, 1, 1),
            font_size='14sp',
            padding=[10, 10]
        )
        top_bar.add_widget(self.file_name_input)
        
        save_btn = Button(text="SAVE PROJECT", background_color=(0, 0.4, 0.8, 1), bold=True, size_hint_x=0.3)
        save_btn.bind(on_press=self.save_project)
        top_bar.add_widget(save_btn)
        root.add_widget(top_bar)

        # 2. RGB Syntax Editor
        self.editor = TextInput(
            text='brain.init(AI) |>\n<< "System is now Online" |>\n<< "Welcome Aditya" |>\nmem.purge |>',
            background_color=(0.04, 0.04, 0.05, 1),
            foreground_color=(0.9, 0.9, 0.9, 1),
            font_size='18sp',
            font_name='Roboto',
            size_hint_y=0.75,
            cursor_color=(0, 1, 0, 1),
            padding=[15, 15, 15, 15],
            auto_indent=True
        )
        root.add_widget(self.editor)

        # 3. Execution Bar
        run_btn = Button(
            text="▶  RUN CLEAN OUTPUT",
            size_hint_y=0.1,
            background_color=(0, 0.7, 0.3, 1),
            bold=True,
            font_size='18sp'
        )
        run_btn.bind(on_press=self.launch_clean_output)
        root.add_widget(run_btn)

        return root

    def save_project(self, instance):
        name = self.file_name_input.text
        path = os.path.join(self.save_dir, name)
        try:
            with open(path, "w") as f:
                f.write(self.editor.text)
            self.show_toast("Success", f"Bhai, {name} save ho gayi!")
        except:
            self.show_toast("Error", "Storage permission issue!")

    def launch_clean_output(self, instance):
        raw_code = self.editor.text.strip().split('\n')
        clean_logs = []
        
        for i, line in enumerate(raw_code):
            if not line: continue
            
            # Smart Friendly Error (Only shown if logic fails)
            if "|>" not in line:
                clean_logs.append(f"[color=ff3333]Bhai, Line {i+1} mein '|>' lagana bhul gaye ho![/color]")
                break
                
            cmd = line.split("|>")[0].strip()
            
            # Clean Extraction Logic
            if cmd.startswith("<<"):
                # Sirf text dikhayega, koi extra symbol nahi
                msg = cmd[2:].strip().replace('"', '').replace("'", "")
                clean_logs.append(f"[color=ffffff]{msg}[/color]")
            
            # In-built functions (Silent execution, asali software ki tarah)
            elif "brain.init" in cmd:
                pass # Backend sync
            elif "mem.purge" in cmd:
                pass # Backend clean
        
        # --- FULL SCREEN CLEAN TERMINAL ---
        content = BoxLayout(orientation='vertical', padding=30, spacing=20)
        with content.canvas.before:
            from kivy.graphics import Color, Rectangle
            Color(0, 0, 0, 1) # Pitch Black Terminal
            Rectangle(size=(Window.width, Window.height), pos=(0,0))

        output_display = Label(
            text="\n".join(clean_logs) if clean_logs else "[System]: No Output to display.",
            markup=True,
            halign='left',
            valign='top',
            font_size='20sp',
            font_name='Roboto'
        )
        output_display.bind(size=output_display.setter('text_size'))
        
        scroll = ScrollView()
        scroll.add_widget(output_display)
        content.add_widget(scroll)

        close_btn = Button(text="CLOSE TERMINAL", size_hint_y=0.12, background_color=(0.8, 0, 0, 1), bold=True)
        popup = Popup(title='NF-1 SYSTEM OUTPUT', content=content, size_hint=(1, 1), auto_dismiss=False)
        close_btn.bind(on_press=popup.dismiss)
        content.add_widget(close_btn)
        popup.open()

    def show_toast(self, title, msg):
        p = Popup(title=title, content=Label(text=msg), size_hint=(0.7, 0.3))
        p.open()

if __name__ == "__main__":
    NF1_Royal_IDE().run()

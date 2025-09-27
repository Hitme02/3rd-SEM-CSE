import threading
import time
import random
import tkinter as tk
from tkinter import ttk
import math

# Constants
NUM_PHILOSOPHERS = 5
SIMULATION_SPEED = 1  # Default speed multiplier

# Shared resources
state = ["THINKING"] * NUM_PHILOSOPHERS
lock = threading.Lock()
conds = [threading.Condition(lock) for _ in range(NUM_PHILOSOPHERS)]
solution_mode = "Resource Hierarchy"  # Default solution mode

# GUI Setup
class DiningPhilosophersApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Dining Philosophers Simulation")
        self.canvas = tk.Canvas(root, width=600, height=600, bg="black", highlightthickness=0)
        self.canvas.grid(row=0, column=0, columnspan=3, padx=10, pady=10)

        # Control Panel
        self.control_frame = tk.Frame(root, bg="black")
        self.control_frame.grid(row=1, column=0, columnspan=3, pady=10)

        self.caption = tk.Label(
            root, text="Welcome to the Dining Philosophers Simulation!", fg="white", bg="black", font=("Arial", 12)
        )
        self.caption.grid(row=2, column=0, columnspan=3, pady=10)

        self.create_control_panel()

        # Philosopher and Fork Layout
        self.philosopher_positions = self.calculate_positions()
        self.forks_positions = self.calculate_forks()
        self.running = False

        # Initialize graphical elements
        self.philosopher_circles = []
        self.philosopher_texts = []
        self.fork_lines = []
        self.create_graphics()

    def create_control_panel(self):
        """Create the control panel with solution mode, speed, start, stop, and reset buttons."""
        # Solution Mode
        ttk.Label(self.control_frame, text="Solution Mode:", foreground="white", background="black").pack(side=tk.LEFT)
        self.solution_var = tk.StringVar(value="Chandy-Misra")
        self.solution_dropdown = ttk.Combobox(
            self.control_frame, textvariable=self.solution_var, values=[ "Chandy-Misra"]
        )
        self.solution_dropdown.pack(side=tk.LEFT, padx=5)

        # Speed Control
        ttk.Label(self.control_frame, text="Speed:", foreground="white", background="black").pack(side=tk.LEFT)
        self.speed_var = tk.DoubleVar(value=0.5)
        self.speed_slider = ttk.Scale(
            self.control_frame, from_=0.1, to=1.5, variable=self.speed_var, orient=tk.HORIZONTAL
        )
        self.speed_slider.pack(side=tk.LEFT, padx=5)

        # Start Button
        self.start_button = ttk.Button(self.control_frame, text="Start Simulation", command=self.start_simulation)
        self.start_button.pack(side=tk.LEFT, padx=5)

        # Stop Button
        self.stop_button = ttk.Button(self.control_frame, text="Stop Simulation", command=self.stop_simulation)
        self.stop_button.pack(side=tk.LEFT, padx=5)

        # Reset Button
        self.reset_button = ttk.Button(self.control_frame, text="Reset", command=self.reset_simulation)
        self.reset_button.pack(side=tk.LEFT, padx=5)

    def calculate_positions(self):
        """Calculate positions of philosophers in a circular layout."""
        positions = []
        radius = 220
        center = (300, 300)
        for i in range(NUM_PHILOSOPHERS):
            angle = 2 * math.pi * i / NUM_PHILOSOPHERS
            x = center[0] + radius * math.cos(angle)
            y = center[1] + radius * math.sin(angle)
            positions.append((x, y))
        return positions

    def calculate_forks(self):
        """Calculate fork positions between philosophers."""
        forks = []
        for i in range(NUM_PHILOSOPHERS):
            x1, y1 = self.philosopher_positions[i]
            x2, y2 = self.philosopher_positions[(i + 1) % NUM_PHILOSOPHERS]
            forks.append(((x1 + x2) / 2, (y1 + y2) / 2))
        return forks

    def create_graphics(self):
        """Initialize philosopher and fork graphics."""
        for x, y in self.philosopher_positions:
            circle = self.canvas.create_oval(
                x - 30, y - 30, x + 30, y + 30, fill="gray", outline="white", width=2
            )
            text = self.canvas.create_text(x, y, text="THINK", fill="white", font=("Arial", 12, "bold"))
            self.philosopher_circles.append(circle)
            self.philosopher_texts.append(text)

        for (x1, y1), (x2, y2) in zip(self.philosopher_positions, self.forks_positions):
            line = self.canvas.create_line(x1, y1, x2, y2, fill="white", width=2)
            self.fork_lines.append(line)

    def update_display(self):
        """Update philosopher and fork graphics in the simulation."""
        for i, (circle, text) in enumerate(zip(self.philosopher_circles, self.philosopher_texts)):
            color = "gray" if state[i] == "THINKING" else "yellow" if state[i] == "HUNGRY" else "green"
            self.canvas.itemconfig(circle, fill=color)
            self.canvas.itemconfig(text, text=state[i].upper())

        for i, line in enumerate(self.fork_lines):
            color = "white"
            if state[i] == "EATING" or state[(i + 1) % NUM_PHILOSOPHERS] == "EATING":
                color = "yellow"
            self.canvas.itemconfig(line, fill=color)

        self.root.update()

    def update_caption(self, text):
        """Update the caption at the bottom of the screen."""
        self.caption.config(text=text)
        self.root.update()

    def start_simulation(self):
        """Start the simulation."""
        global SIMULATION_SPEED, solution_mode
        SIMULATION_SPEED = self.speed_var.get()
        solution_mode = self.solution_var.get()

        if not self.running:
            self.running = True
            threads = [
                threading.Thread(target=philosopher, args=(i,), daemon=True) for i in range(NUM_PHILOSOPHERS)
            ]
            for thread in threads:
                thread.start()

    def stop_simulation(self):
        """Stop the simulation gracefully."""
        self.running = False
        self.update_caption("Simulation stopped. You can check the current state of philosophers.")

    def reset_simulation(self):
        """Reset the simulation to its initial state."""
        global state
        self.running = False
        state = ["THINKING"] * NUM_PHILOSOPHERS
        self.update_caption("Simulation reset. Choose options and start again!")
        self.update_display()

# Simulation Functions
def think(philosopher_id):
    if not app.running:
        return
    think_time = max(2, random.randint(1, 3))
    state[philosopher_id] = "THINKING"
    app.update_caption(f"Philosopher {philosopher_id} is thinking for {think_time} seconds.")
    app.update_display()
    time.sleep(think_time * SIMULATION_SPEED)


def eat(philosopher_id):
    if not app.running:
        return
    eating_time = max(2, random.randint(1, 3))
    state[philosopher_id] = "EATING"
    app.update_caption(f"Philosopher {philosopher_id} is eating for {eating_time} seconds.")
    app.update_display()
    time.sleep(eating_time * SIMULATION_SPEED)


def philosopher(philosopher_id):
    while app.running:
        think(philosopher_id)
        if not app.running:
            return
        if solution_mode == "Resource Hierarchy":
            pickup_forks(philosopher_id, pickup_forks_resource_hierarchy)
        else:
            pickup_forks(philosopher_id, pickup_forks_chandy_misra)
        if not app.running:
            return
        eat(philosopher_id)
        if not app.running:
            return
        if solution_mode == "Resource Hierarchy":
            return_forks(philosopher_id, return_forks_resource_hierarchy)
        else:
            return_forks(philosopher_id, return_forks_chandy_misra)

def pickup_forks(philosopher_id, pickup_strategy):
    pickup_strategy(philosopher_id)

def return_forks(philosopher_id, return_strategy):
    return_strategy(philosopher_id)

def pickup_forks_resource_hierarchy(philosopher_id):
    left = philosopher_id
    right = (philosopher_id + 1) % NUM_PHILOSOPHERS
    first, second = (left, right) if left < right else (right, left)

    with lock:
        state[philosopher_id] = "HUNGRY"
        app.update_caption(f"Philosopher {philosopher_id} is hungry and trying to pick up forks.")
        app.update_display()
        while state[first] == "EATING" or state[second] == "EATING":
            conds[philosopher_id].wait()
        state[philosopher_id] = "EATING"


def pickup_forks_chandy_misra(philosopher_id):
    left = (philosopher_id - 1 + NUM_PHILOSOPHERS) % NUM_PHILOSOPHERS
    right = (philosopher_id + 1) % NUM_PHILOSOPHERS
    with lock:
        state[philosopher_id] = "HUNGRY"
        app.update_caption(f"Philosopher {philosopher_id} is hungry and trying to pick up forks.")
        app.update_display()
        time.sleep(max(2, 2 * SIMULATION_SPEED))  # Deliberate slowdown for Chandy-Misra
        while state[left] == "EATING" or state[right] == "EATING":
            conds[philosopher_id].wait()
        state[philosopher_id] = "EATING"


def return_forks_resource_hierarchy(philosopher_id):
    left = philosopher_id
    right = (philosopher_id + 1) % NUM_PHILOSOPHERS
    first, second = (left, right) if left < right else (right, left)

    with lock:
        state[philosopher_id] = "THINKING"
        app.update_caption(f"Philosopher {philosopher_id} has finished eating and returned the forks.")
        app.update_display()
        conds[first].notify()
        conds[second].notify()


def return_forks_chandy_misra(philosopher_id):
    left = (philosopher_id - 1 + NUM_PHILOSOPHERS) % NUM_PHILOSOPHERS
    right = (philosopher_id + 1) % NUM_PHILOSOPHERS
    with lock:
        state[philosopher_id] = "THINKING"
        app.update_caption(f"Philosopher {philosopher_id} has finished eating and returned the forks.")
        app.update_display()
        conds[left].notify()
        conds[right].notify()


# Start GUI
if __name__ == "__main__":
    root = tk.Tk()
    app = DiningPhilosophersApp(root)
    root.mainloop()
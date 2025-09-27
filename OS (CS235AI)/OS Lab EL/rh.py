import tkinter as tk
import threading
import time

class DiningPhilosophersVisual:
    def __init__(self, root):
        self.root = root
        self.root.title("Dining Philosophers Visualization")

        # Canvas for visualization
        self.canvas = tk.Canvas(root, width=600, height=400, bg="white")
        self.canvas.pack(pady=10)

        # Caption label
        self.caption = tk.Label(root, text="", font=("Arial", 12))
        self.caption.pack(pady=5)

        # Number of philosophers
        self.num_philosophers = 5
        self.states = ["Thinking"] * self.num_philosophers
        self.forks = [threading.Lock() for _ in range(self.num_philosophers)]

        # Positions for philosophers and forks
        self.philosopher_positions = [
            (300, 50), (500, 150), (400, 300), (200, 300), (100, 150)
        ]
        self.fork_positions = [
            (400, 100), (450, 225), (300, 350), (150, 225), (200, 100)
        ]

        # Draw initial shapes
        self.philosopher_shapes = []
        self.fork_shapes = []

        for i, pos in enumerate(self.philosopher_positions):
            shape = self.canvas.create_oval(
                pos[0] - 30, pos[1] - 30, pos[0] + 30, pos[1] + 30,
                fill="lightblue", outline="black"
            )
            label = self.canvas.create_text(pos[0], pos[1], text=f"P{i}", font=("Arial", 12))
            self.philosopher_shapes.append((shape, label))

        for i, pos in enumerate(self.fork_positions):
            shape = self.canvas.create_rectangle(
                pos[0] - 10, pos[1] - 10, pos[0] + 10, pos[1] + 10,
                fill="gray", outline="black"
            )
            self.fork_shapes.append(shape)

        # Start button
        tk.Button(root, text="Start Simulation", command=self.start_simulation).pack(pady=10)

    def start_simulation(self):
        threads = []
        for i in range(self.num_philosophers):
            t = threading.Thread(target=self.dine, args=(i,))
            threads.append(t)
            t.start()

    def dine(self, philosopher):
        left_fork = philosopher
        right_fork = (philosopher + 1) % self.num_philosophers

        while True:
            # Thinking
            self.update_state(philosopher, "Thinking", "grey")
            time.sleep(2)

            # Hungry
            self.update_state(philosopher, "Hungry", "yellow")

            # Try to pick up forks in a hierarchical order to prevent deadlock
            first_fork, second_fork = (left_fork, right_fork) if left_fork < right_fork else (right_fork, left_fork)

            with self.forks[first_fork]:
                with self.forks[second_fork]:
                    # Eating
                    self.update_state(philosopher, "Eating", "green")
                    time.sleep(2)

    def update_state(self, philosopher, state, color):
        self.states[philosopher] = state
        shape, _ = self.philosopher_shapes[philosopher]
        self.canvas.itemconfig(shape, fill=color)
        self.caption.config(text=f"Philosopher {philosopher} is {state}.")

if __name__ == "__main__":
    root = tk.Tk()
    app = DiningPhilosophersVisual(root)
    root.mainloop()
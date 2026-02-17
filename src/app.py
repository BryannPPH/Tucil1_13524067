import tkinter as tk
import queens_solver
import os
import colorsys
import threading
from tkinter import filedialog, messagebox
from PIL import Image, ImageTk, ImageDraw

current_board = None
current_solution = None
current_input_path = None
current_result = None
BOARD_PIXEL_SIZE = 600

def live_update(state):
    canvas.delete("queen")

    n = len(state)
    cell_size = BOARD_PIXEL_SIZE / n

    for i in range(n):
        for j in range(n):
            if state[i][j] == '#':
                x = j * cell_size + cell_size / 2
                y = i * cell_size + cell_size / 2

                canvas.create_image(
                    x,
                    y,
                    image=queen_img,
                    tags="queen"
                )

    root.update_idletasks()

def generate_colors(n=26):
    colors = []
    for i in range(n):
        hue = i / n
        r, g, b = colorsys.hsv_to_rgb(hue, 0.5, 0.95)
        colors.append(f"#{int(r*255):02x}{int(g*255):02x}{int(b*255):02x}")
    return colors

REGION_COLORS = generate_colors(26)

def load_image(path, width):
    img = Image.open(path).convert("RGBA")
    ratio = width / img.width
    height = int(img.height * ratio)
    img = img.resize((width, height), Image.LANCZOS)
    return ImageTk.PhotoImage(img)

def load_file():
    global current_board, current_input_path

    file_path = filedialog.askopenfilename(
        title="Pilih file input",
        filetypes=[("Text files", "*.txt")]
    )

    if not file_path:
        return

    try:
        current_board = queens_solver.loadBoardFile(file_path)
        current_input_path = file_path
        status_label.config(text="Board loaded", fg="black")
        draw_board_only(current_board)

    except Exception as e:
        messagebox.showerror("Error", str(e))

def show_solution():
    global current_board, current_solution, current_result

    if current_board is None:
        return

    def run_solver():
        try:
            result = queens_solver.solveBoard(
                current_board,
                optimized_var.get(),
                live_update
            )

            current_solution = result.solution
            current_result = result

            if result.found:
                status_label.config(
                    text=f"Solusi ditemukan | Waktu: {result.durationMs} ms | Cases: {result.countCases}",
                    fg="green"
                )
            else:
                status_label.config(
                    text=f"Solusi tidak ditemukan | Waktu: {result.durationMs} ms | Cases: {result.countCases}",
                    fg="red"
                )

        except Exception as e:
            messagebox.showerror("Error", str(e))

    threading.Thread(target=run_solver).start()

def draw_board_only(board):
    canvas.delete("all")

    n = len(board)
    cell_size = BOARD_PIXEL_SIZE / n

    canvas.config(width=BOARD_PIXEL_SIZE, height=BOARD_PIXEL_SIZE)

    for i in range(n):
        for j in range(n):
            letter = board[i][j]
            idx = ord(letter) - ord('A')
            color = REGION_COLORS[idx % 26]

            x1 = j * cell_size
            y1 = i * cell_size
            x2 = x1 + cell_size
            y2 = y1 + cell_size

            canvas.create_rectangle(
                x1, y1, x2, y2,
                fill=color,
                outline="black",
                width=2
            )

def clear_board():
    global current_board, current_solution, current_result, current_input_path

    current_board = None
    current_solution = None
    current_result = None
    current_input_path = None

    canvas.delete("all")
    status_label.config(text="Board cleared", fg="black")

def save_as_txt():
    if current_solution is None or current_input_path is None:
        messagebox.showwarning("Warning", "No solution to save.")
        return

    os.makedirs("test/output", exist_ok=True)

    base_name = os.path.splitext(os.path.basename(current_input_path))[0]
    output_path = os.path.join("test/output", f"{base_name}_solution.txt")

    with open(output_path, "w") as f:
        for row in current_solution:
            f.write("".join(row) + "\n")

        f.write("\n")
        f.write(f"Waktu Pencarian: {current_result.durationMs} ms\n")
        f.write(f"Jumlah Cases: {current_result.countCases}")

    messagebox.showinfo("Success", f"Saved to {output_path}")

def save_as_image():
    if current_solution is None or current_input_path is None:
        messagebox.showwarning("Warning", "No solution to save.")
        return

    os.makedirs("test/output", exist_ok=True)

    base_name = os.path.splitext(os.path.basename(current_input_path))[0]
    output_path = os.path.join("test/output", f"{base_name}_solution.png")

    n = len(current_board)
    board_size = BOARD_PIXEL_SIZE
    cell_size = board_size / n

    img = Image.new("RGB", (board_size, board_size), "#f2dfb2")
    draw = ImageDraw.Draw(img)

    queen_original = Image.open("assets/QLOGO.png").convert("RGBA")
    queen_size = int(cell_size * 0.7)
    queen_img_resized = queen_original.resize((queen_size, queen_size), Image.LANCZOS)

    for i in range(n):
        for j in range(n):
            letter = current_board[i][j]
            idx = ord(letter) - ord('A')
            color = REGION_COLORS[idx % 26]

            x1 = j * cell_size
            y1 = i * cell_size
            x2 = x1 + cell_size
            y2 = y1 + cell_size

            draw.rectangle([x1, y1, x2, y2], fill=color, outline="black", width=2)

            if current_solution[i][j] == '#':
                queen_x = int(x1 + (cell_size - queen_size) / 2)
                queen_y = int(y1 + (cell_size - queen_size) / 2)
                img.paste(queen_img_resized, (queen_x, queen_y), queen_img_resized)

    img.save(output_path)
    messagebox.showinfo("Success", f"Saved to {output_path}")

root = tk.Tk()
root.title("Queens Solver by Bryan")
root.geometry("1200x800")
root.configure(bg="#f2dfb2")
optimized_var = tk.BooleanVar(value=True)

root.grid_columnconfigure(0, weight=0)
root.grid_columnconfigure(1, weight=0)
root.grid_columnconfigure(2, weight=1)
root.grid_rowconfigure(0, weight=1)

sidebar = tk.Frame(root, bg="#f2dfb2", width=380)
sidebar.grid(row=0, column=0, sticky="ns")
sidebar.grid_propagate(False)

inner_sidebar = tk.Frame(sidebar, bg="#f2dfb2")
inner_sidebar.pack(fill="both", expand=True)

logo_img = load_image("assets/QUEENS.png", 320)
queen_img = load_image("assets/QLOGO.png", 65)

logo_label = tk.Label(inner_sidebar, image=logo_img, bg="#f2dfb2")
logo_label.pack(pady=(20, 90))

def image_button(parent, img, command):
    return tk.Button(
        parent,
        image=img,
        command=command,
        bd=0,
        highlightthickness=0,
        relief="flat",
        bg="#f2dfb2",
        activebackground="#f2dfb2",
        cursor="hand2"
    )

load_btn_img = load_image("assets/LOADTXT.png", 240)
solve_btn_img = load_image("assets/SOLVE.png", 240)
save_txt_img = load_image("assets/SAVETXT.png", 240)
save_img_img = load_image("assets/SAVEIMG.png", 240)
clear_btn_img = load_image("assets/CLEAR.png", 240)

button_frame = tk.Frame(inner_sidebar, bg="#f2dfb2")
button_frame.pack()

image_button(button_frame, load_btn_img, load_file).pack(pady=12)
image_button(button_frame, solve_btn_img, show_solution).pack(pady=(12, 4))

# ===== CHECKBOX =====
optimized_checkbox = tk.Checkbutton(
    button_frame,
    text="Optimized",
    variable=optimized_var,
    onvalue=True,
    offvalue=False,
    bg="#f2dfb2",
    activebackground="#f2dfb2",
    font=("Helvetica", 12, "bold"),
    fg="black"
)
optimized_checkbox.pack(pady=(0, 12))

image_button(button_frame, save_txt_img, save_as_txt).pack(pady=12)
image_button(button_frame, save_img_img, save_as_image).pack(pady=12)
image_button(button_frame, clear_btn_img, clear_board).pack(pady=12)

separator = tk.Frame(root, bg="#c5b58a", width=3)
separator.grid(row=0, column=1, sticky="ns")

board_area = tk.Frame(root, bg="#f2dfb2")
board_area.grid(row=0, column=2, sticky="nsew")

status_label = tk.Label(
    board_area,
    text="Load a board to begin",
    font=("Helvetica", 16, "bold"),
    bg="#f2dfb2",
    fg="black"
)
status_label.pack(pady=20)

canvas = tk.Canvas(
    board_area,
    bg="#f2dfb2",
    highlightthickness=0
)
canvas.pack(expand=True)

root.mainloop()
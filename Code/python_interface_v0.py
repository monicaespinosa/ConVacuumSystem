import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import tkinter as tk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# ---------- CONFIGURACIÓN ----------
PORT = 'COM5'         # Ajusta según tu PC
BAUD_RATE = 9600
MAX_CURRENT = 0.4      # mA máximo esperado para mapa de calor
HISTORY_LENGTH = 50    # para el gráfico de línea

# ---------- INICIALIZACIÓN ----------
ser = serial.Serial(PORT, BAUD_RATE)
data_history = [[] for _ in range(10)]  # 9 sensores + 1 total

# ---------- GUI ----------
root = tk.Tk()
root.title("Current Monitor")

# Figura para la grilla
fig1, ax1 = plt.subplots()
matrix_plot = ax1.imshow(np.zeros((3, 3)), cmap='viridis', vmin=0, vmax=MAX_CURRENT)
ax1.set_title("Spatial Distribution of Currents [mA]")
plt.colorbar(matrix_plot, ax=ax1)

# Figura para la gráfica
fig2, ax2 = plt.subplots()
lines = [ax2.plot([], [], label=f"Sensor {i+1}")[0] for i in range(9)]
lines.append(ax2.plot([], [], label="Total current")[0])
ax2.set_xlim(0, HISTORY_LENGTH)
ax2.set_ylim(0, MAX_CURRENT)
ax2.set_title("Currents over time [mA]")
ax2.legend(loc='upper right')

# Agrega ambos plots a la ventana
canvas1 = FigureCanvasTkAgg(fig1, master=root)
canvas1.get_tk_widget().pack()
canvas2 = FigureCanvasTkAgg(fig2, master=root)
canvas2.get_tk_widget().pack()

# ---------- ACTUALIZACIÓN EN TIEMPO REAL ----------
def update(frame):
    global data_history
    line = ser.readline().decode().strip()
    parts = line.split(',')

    if len(parts) != 10:
        return

    try:
        values = list(map(float, parts))
    except ValueError:
        return

    for i in range(10):
        data_history[i].append(values[i])
        if len(data_history[i]) > HISTORY_LENGTH:
            data_history[i].pop(0)

    # Actualiza el gráfico de la grilla
    matrix = np.array(values[:9]).reshape((3, 3))
    matrix_plot.set_data(matrix)

    # Actualiza las líneas
    for i, line in enumerate(lines):
        line.set_data(range(len(data_history[i])), data_history[i])

    ax2.relim()
    ax2.autoscale_view()

    canvas1.draw()
    canvas2.draw()

# ---------- ANIMACIÓN ----------
ani = animation.FuncAnimation(fig2, update, interval=200)
root.mainloop()

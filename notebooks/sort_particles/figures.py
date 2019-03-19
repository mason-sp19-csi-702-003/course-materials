import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np


def make_aabb_figure(dpi=120, figsize=(5, 5)):
    """Generate AABB figure."""
    fig, ax = plt.subplots(dpi=dpi, figsize=figsize)
    box1 = patches.Rectangle(xy=(0.1, 0.1), width=0.02, height=0.02, alpha=0.3, color="tab:blue")
    box2 = patches.Rectangle(xy=(0.112, 0.114), width=0.02, height=0.02, alpha=0.3, color="tab:orange")
    circle1 = patches.Circle(xy=(0.11, 0.11), radius=0.01, color="tab:blue", alpha=0.3)
    circle2 = patches.Circle(xy=(0.122, 0.124), radius=0.01, color="tab:orange", alpha=0.3)
    ax.add_patch(box1)
    ax.add_patch(circle1)
    ax.add_patch(box2)
    ax.add_patch(circle2)
    ax.scatter(0.11, 0.11, color="tab:blue")
    ax.scatter(0.122, 0.124, color="tab:orange")
    ax.tick_params(
        axis="both", bottom=False, left=False, labelbottom=False, labelleft=False
    )
    ax.grid(False)
    ax.axis("off")
    plt.savefig("../../img/particles_aabb_schematic.png")
    
    
def make_particles_sort_figure(particle_history="serial_history.txt", dpi=120, figsize=(5, 5)):
    """Generate figure showing the checking range after a sort."""
    particle_positions = np.loadtxt(particle_history, skiprows=1)

    particle_i = 45
    particle_i_x = particle_positions[2250:2400, 0][particle_i]
    particle_i_y = particle_positions[2250:2400, 1][particle_i]

    fig, ax = plt.subplots(dpi=dpi, figsize=figsize)
    ax.axvspan(particle_i_x - 0.01, particle_i_x + 0.01, alpha=0.30, color="tab:orange")
    ax.scatter(
        particle_positions[2250:2400, 0], particle_positions[2250:2400, 1], color="tab:blue"
    )
    ax.scatter(particle_i_x, particle_i_y, color="tab:orange")
    ax.tick_params(
        axis="both", bottom=False, left=False, labelbottom=False, labelleft=False
    )
    ax.grid(False)
    plt.savefig("../../img/particles_sort_schematic.png")
    
    
if __name__ == "__main__":
    make_aabb_figure()
    make_particles_sort_figure()
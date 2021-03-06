import numpy as np

def cube():
    vert = np.array([
        [-1.0, -1.0,  1.0], # 0
        [ 1.0, -1.0,  1.0], # 1
        [ 1.0,  1.0,  1.0], # 2
        [-1.0,  1.0,  1.0], # 3
        [-1.0, -1.0, -1.0], # 4
        [ 1.0, -1.0, -1.0], # 5
        [ 1.0,  1.0, -1.0], # 6
        [-1.0,  1.0, -1.0]  # 7
    ], dtype=float)
    tri = np.array([
        [0, 1, 2], # front
        [0, 2, 3], # front
        [1, 5, 6], # right
        [1, 6, 2], # right
        [5, 4, 7], # back
        [5, 7, 6], # back
        [4, 0, 3], # left
        [4, 3, 7], # left
        [3, 2, 6], # top
        [3, 6, 7], # top
        [0, 1, 5], # bottom
        [0, 5, 4]  # bottom
    ], dtype=int)
    return vert, tri

def out_vert(vert):
    print(vert.shape[0])
    for v in vert:
        print("{:.6f} {:.6f} {:.6f}".format(*v))

def out_tri(tri):
    print(tri.shape[0] * tri.shape[1])
    for t in tri:
        print(str(t).strip("[]"))


if __name__ == "__main__":
    vert, tri = cube()
    out_vert(vert)
    out_tri(tri)

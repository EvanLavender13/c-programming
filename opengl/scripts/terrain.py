import numpy as np

def flat(div=0):
    nv = (div + 2) ** 2
    n = 1 + div
    vert = np.zeros((nv, 3), dtype=float)
    indx = np.zeros((n + 1, n + 1), dtype=int)
    xspace = np.linspace(-1.0, 1.0, n + 1, dtype=float)
    zspace = np.linspace(-1.0, 1.0, n + 1, dtype=float)
    i = 0

    for j, z in enumerate(zspace):
        for k, x in enumerate(xspace):
            vert[i] = [x, 0.0, z]
            indx[n - j, k] = i
            i += 1
    # print("indx\n", indx)
    # print("vert\n", vert)
    tri = compute_triangles(indx, n + 1, n + 1)
    # print("tri\n", tri)

    norm = np.zeros((nv, 3), dtype=float)
    norm[:] = [0.0, 1.0, 0.0]

    return vert, tri, norm

def compute_triangles(verts, u, v):
    tris = np.zeros((2 * ((u - 1) * (v - 1)), 3), dtype=int)

    index = 0
    for i in range(u - 1):
        for j in range(v - 1):
            # tris[index] = [verts[i, j], verts[i + 1, j], verts[i + 1, j + 1]]
            tris[index] = [verts[i, j], verts[i + 1, j + 1], verts[i + 1, j]]
            index += 1
            # tris[index] = [verts[i, j], verts[i + 1, j + 1], verts[i, j + 1]]
            tris[index] = [verts[i, j], verts[i, j + 1], verts[i + 1, j + 1]]
            index += 1

    return tris

def out_vert(vert):
    print(vert.shape[0] * vert.shape[1])
    for v in vert:
        print("{:.6f} {:.6f} {:.6f}".format(*v))

def out_tri(tri):
    print(tri.shape[0] * tri.shape[1])
    for t in tri:
        print(str(t).strip("[]"))

def out_norm(norm):
    print(norm.shape[0] * norm.shape[1])
    for n in norm:
        print("{:.6f} {:.6f} {:.6f}".format(*n))

if __name__ == "__main__":
    vert, tri, norm = flat(10)
    out_vert(vert)
    out_tri(tri)
    out_norm(norm)
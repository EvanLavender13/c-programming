import cv2
import numpy as np

from argparse import ArgumentParser

def flat(div=0):
    # TODO: I think something is up with this
    n = 2
    # print(n)
    nv = n ** 2
    # print(nv)
    # print("nv, n", nv, n)
    vert = np.zeros((nv, 3), dtype=float)
    indx = np.zeros((n, n), dtype=int)
    xspace = np.linspace(-1.0 * n, 1.0 * n, n, dtype=float)
    zspace = np.linspace(-1.0 * n, 1.0 * n, n, dtype=float)
    i = 0

    y = 0.0
    for j, z in enumerate(zspace):
        for k, x in enumerate(xspace):
            vert[i] = [x, y, z]
            indx[n - 1 - j, k] = i
            i += 1

    tri = compute_triangles(indx, n, n)
    # print("indx\n", indx)
    # print("vert\n", vert)
    # print("tri\n", tri)

    norm = np.zeros((nv, 3), dtype=float)
    norm[:] = [0.0, 1.0, 0.0]

    tex = np.array([
        [0.0, 1.0],
        [1.0, 1.0],
        [0.0, 0.0],
        [1.0, 0.0]
    ], dtype=float)

    return vert, tri, norm, tex

def apply_img(vert, data, max_height):
    n = data.shape[0]
    xspace = range(n)
    zspace = range(n)
    i = 0

    for z in zspace:
        for x in xspace:
            vert[i][1] += (data[n - z - 1][x] / 255.0) * max_height
            i += 1


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

def out_tex(tex):
    print(tex.shape[0] * tex.shape[1])
    for t in tex:
        print("{:.6f} {:.6f}".format(*t))

def get_arguments():
    parser = ArgumentParser(description="terrain script")
    parser.add_argument("-f", type=str, help="heightmap image file")
    parser.add_argument("-n", type=int, default=50, help="number of subdivisions")
    parser.add_argument("-m", type=float, default=50.0, help="maximum height")
    return parser.parse_args()

if __name__ == "__main__":
    args = get_arguments()
    vert, tri, norm, tex = flat(args.n)
    if args.f:
        s = np.sqrt(vert.shape[0]).astype(int)
        img = cv2.imread(args.f, cv2.IMREAD_GRAYSCALE)
        img = cv2.resize(img, (s, s), interpolation=cv2.INTER_CUBIC)
        apply_img(vert, img, args.m)

    out_vert(vert)
    out_tri(tri)
    out_norm(norm)
    out_tex(tex)
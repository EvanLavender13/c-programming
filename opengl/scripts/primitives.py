import numpy as np

def cube():
    vert = np.array([
        # face 1 (front)
        [-1.0, -1.0,  1.0], # 0
        [ 1.0, -1.0,  1.0], # 1
        [ 1.0,  1.0,  1.0], # 2
        [-1.0,  1.0,  1.0], # 3
        # face 2 (right)
        [ 1.0, -1.0,  1.0], # 4
        [ 1.0, -1.0, -1.0], # 5
        [ 1.0,  1.0, -1.0], # 6
        [ 1.0,  1.0,  1.0], # 7
        # face 3 (back)
        [ 1.0, -1.0, -1.0], # 8
        [-1.0, -1.0, -1.0], # 9
        [-1.0,  1.0, -1.0], # 10
        [ 1.0,  1.0, -1.0], # 11
        # face 4 (left)
        [-1.0, -1.0, -1.0], # 12
        [-1.0, -1.0,  1.0], # 13
        [-1.0,  1.0,  1.0], # 14
        [-1.0,  1.0, -1.0], # 15
        # face 5 (top)
        [-1.0,  1.0,  1.0], # 16
        [ 1.0,  1.0,  1.0], # 17
        [ 1.0,  1.0, -1.0], # 18
        [-1.0,  1.0, -1.0], # 19
        # face 6 (bottom)
        [-1.0, -1.0,  1.0], # 20
        [ 1.0, -1.0,  1.0], # 21
        [ 1.0, -1.0, -1.0], # 22
        [-1.0, -1.0, -1.0]  # 23
    ], dtype=float)
    tri = np.array([
        [0, 1, 2],
        [0, 2, 3],
        [4, 5, 6],
        [4, 6, 7],
        [8, 9, 10],
        [8, 10, 11],
        [12, 13, 14],
        [12, 14, 15],
        [16, 17, 18],
        [16, 18, 19],
        [20, 21, 22],
        [20, 22, 23]
    ], dtype=int)
    norm = np.array([
        # face 1 (front)
        [0.0, 0.0, -1.0],
        [0.0, 0.0, -1.0],
        [0.0, 0.0, -1.0],
        [0.0, 0.0, -1.0],
        # face 2 (right)
        [1.0, 0.0, 0.0],
        [1.0, 0.0, 0.0],
        [1.0, 0.0, 0.0],
        [1.0, 0.0, 0.0],
        # face 3 (back)
        [0.0, 0.0, 1.0],
        [0.0, 0.0, 1.0],
        [0.0, 0.0, 1.0],
        [0.0, 0.0, 1.0],
        # face 4 (left)
        [-1.0, 0.0, 0.0],
        [-1.0, 0.0, 0.0],
        [-1.0, 0.0, 0.0],
        [-1.0, 0.0, 0.0],
        # face 5 (top)
        [0.0, 1.0, 0.0],
        [0.0, 1.0, 0.0],
        [0.0, 1.0, 0.0],
        [0.0, 1.0, 0.0],
        # face 6 (bottom)
        [0.0, -1.0, 0.0],
        [0.0, -1.0, 0.0],
        [0.0, -1.0, 0.0],
        [0.0, -1.0, 0.0]
    ], dtype=float)
    return vert, tri, norm

###############################################################################
############# BEGIN SUPERELLIPSOID
###############################################################################

def c(w, m):
    cos_w = np.cos(w)
    return np.sign(cos_w) * np.abs(cos_w) ** m


def s(w, m):
    sin_w = np.sin(w)
    return np.sign(sin_w) * np.abs(sin_w) ** m


def eval_ellipsoid_point(A, B, C, s1, s2, u, v):
    point = np.zeros(3, dtype=float)
    point[0] = A * c(v, s1) * c(u, s2)
    point[1] = B * c(v, s1) * s(u, s2)
    point[2] = C * s(v, s1)

    return point


def eval_ellipsoid_normal(A, B, C, s1, s2, u, v):
    normal = np.zeros(3, dtype=float)
    normal[0] = (1 / A) * c(v, 2 - s1) * c(u, 2 - s2)
    normal[1] = (1 / B) * c(v, 2 - s1) * s(u, 2 - s2)
    normal[2] = (1 / C) * s(v, 2 - s1)

    return normal


def eval_ellipsoid_points(A, B, C, s1, s2, u, v, smooth):
    points = np.zeros((u * v - 2 * u + 2, 3), dtype=float)
    indices = np.zeros((v - 2, u), dtype=int)
    normals = np.zeros_like(points)
    u_space = np.linspace(-np.pi, np.pi, u)
    v_space = np.linspace(-np.pi / 2, np.pi / 2, v)

    index = 0
    for i, dv in enumerate(v_space):
        # check for poles
        if i == 0:
            points[index] = [0, 0, C]
            normals[index] = [0, 0, 1]
            index += 1
            continue
        elif i == v - 1:
            points[index] = [0, 0, -C]
            normals[index] = [0, 0, -1]
            index += 1
            continue

        for j, du in enumerate(u_space):
            points[index] = eval_ellipsoid_point(A, B, C, s1, s2, du, dv)
            normals[index] = eval_ellipsoid_normal(A, B, C, s1, s2, du, dv)
            indices[i - 1, j] = index

            index += 1

    return points, indices, -normals


def eval_ellipsoid(A, B, C, s1, s2, u, v, smooth):
    points, indices, normals = eval_ellipsoid_points(
        A, B, C, s1, s2, u, v, smooth)
    triangles = compute_triangles_ellipse(indices, u, v)

    return points, triangles, normals

###############################################################################
############# END SUPERELLIPSOID
###############################################################################

###############################################################################
############# BEGIN SURFACE OF REVOLUTION
###############################################################################

def compute_bezier_point(control_points, dt):
    bp = np.zeros(4, dtype=float)

    bp[0] = (1 - dt) ** 3
    bp[1] = 3 * dt * (1 - dt) ** 2
    bp[2] = 3 * dt ** 2 * (1 - dt)
    bp[3] = dt ** 3

    return np.dot(bp, control_points)


def compute_bezier_tangent(control_points, dt):
    bp = np.zeros(4, dtype=float)

    bp[0] = -3 * (1 - dt) ** 2
    bp[1] = 9 * dt ** 2 - 12 * dt + 3
    bp[2] = 3 * (2 - 3 * dt) * dt
    bp[3] = 3 * dt ** 2

    return np.dot(bp, control_points)


def compute_bezier_curve(control_points, n):
    # from hw2 and hw4

    def choose(k, i):
        return np.math.factorial(k) / np.math.factorial(i) / np.math.factorial(k - i)

    parameter_space = np.linspace(0, 1, n + 1)
    curve_points = np.zeros((n + 1, 3), dtype=float)
    tangents = np.zeros_like(curve_points)

    for i, du in enumerate(parameter_space):
        point = compute_bezier_point(control_points, du)
        tangent = compute_bezier_tangent(control_points, du)

        curve_points[i] = point
        tangents[i] = tangent

    return curve_points, tangents

def compute_catmull_rom_spline(points, end_tangents, num_u):
    # from hw2

    def compute_tangents(points, end_tangents):
        interior_tangents = np.zeros((points.shape[0] - 2, 3), dtype=float)
        for i in range(1, points.shape[0] - 1):
            interior_tangents[i - 1] = 0.5 * (points[i + 1] - points[i - 1])

        tangents = np.concatenate(
            [[end_tangents[0]], interior_tangents, [end_tangents[1]]])

        return tangents

    def compute_control_points(tangents, points):
        control_point_set = np.zeros((points.shape[0] - 1, 4, 3), dtype=float)

        for i in range(points.shape[0] - 1):
            control_points = np.zeros((4, 3), dtype=float)
            control_points[0] = points[i]
            control_points[3] = points[i + 1]
            control_points[1] = control_points[0] + (1 / 3) * tangents[i]
            control_points[2] = control_points[3] - (1 / 3) * tangents[i + 1]

            control_point_set[i] = control_points

        return control_point_set

    tangents = compute_tangents(points, end_tangents)
    control_point_set = compute_control_points(tangents, points)
    curve_points = np.zeros(
        (control_point_set.shape[0], num_u + 1, 3), dtype=float)
    curve_tangents = np.zeros_like(curve_points)

    for i, control_points in enumerate(control_point_set):
        curve_points[i], curve_tangents[i] = compute_bezier_curve(
            control_points, num_u)

    curve_points = np.reshape(curve_points, (-1, curve_points.shape[-1]))
    curve_tangents = np.reshape(curve_tangents, (-1, curve_tangents.shape[-1]))

    return curve_points, curve_tangents


def compute_surface_point(du, dt):
    s = np.zeros(3, dtype=float)
    s[0] = du[0] * np.cos(dt)
    s[1] = du[0] * np.sin(dt)
    s[2] = du[2]

    return s


def compute_surface_normal(tangent, du, dt):
    ds_du = compute_surface_point(tangent, dt)
    ds_dt = np.zeros_like(ds_du)
    ds_dt[0] = -du[0] * np.sin(dt)
    ds_dt[1] = du[0] * np.cos(dt)
    ds_dt[2] = 0

    return np.cross(ds_du, ds_dt)


def compute_surface(curve, tangents, num_t, smooth):
    points = np.zeros((curve.shape[0] * num_t, 3), dtype=float)
    indices = np.zeros((curve.shape[0], num_t), dtype=int)
    normals = np.zeros_like(points) if smooth else None
    t_space = np.linspace(0, 2 * np.pi, num_t)

    index = 0
    for i, du in enumerate(curve):
        for j, dt in enumerate(t_space):
            point = compute_surface_point(du, dt)

            points[index] = point
            indices[i, j] = index

            if smooth:
                normals[index] = compute_surface_normal(tangents[i], du, dt)

            index += 1

    return points, normals, indices

def eval_surface_rev():
    end_tangents = np.array([[10.0, 0.0, 0.0], [3.0, 0.0, 3.0]])
    points = np.array([
        [3.0, 0.0, 0.0],
        [11.0, 0.0, 2.0],
        [13.0, 0.0, 6.0],
        [11.0, 0.0, 10.0],
        [7.0, 0.0, 15.0],
        [7.0, 0.0, 20.0]
    ])

    u = 4
    t = 32

    curve, tangents = compute_catmull_rom_spline(points, end_tangents, u)
    surface_points, normals, indices = compute_surface(curve, tangents, t + 1, True)
    triangles = compute_triangles(indices, (points.shape[0] - 1) * (u + 1), t + 1)

    return surface_points, triangles, normals

###############################################################################
############# END SURFACE OF REVOLUTION
###############################################################################

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

def compute_triangles_ellipse(verts, u, v):
    num_tris = 2 * (u - 1) * (v - 3)
    num_tris += 2 * (u - 1)
    tris = np.zeros((num_tris, 3), dtype=int)

    # add poles
    index = 0

    vertex_index = u * (v - 2) + 1
    for i in range(1, u):
        # tris[index] = [i, i + 1, vertex_index]
        tris[index] = [i, vertex_index, i + 1]
        index += 1

    for i in range(1, u):
        # tris[index] = [vertex_index - i, vertex_index - 1 - i, 0]
        tris[index] = [vertex_index - i, 0, vertex_index - 1 - i]
        index += 1

    for i in range(v - 3):
        for j in range(u - 1):
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
    # vert, tri, norm = cube()
    # vert, tri, norm = eval_ellipsoid(1, 1, 1, 1, 1, 18 + 1, 9, False)

    vert, tri, norm = eval_surface_rev()
    out_vert(vert)
    out_tri(tri)
    out_norm(norm)
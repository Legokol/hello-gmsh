#include <set>
#include <vector>
#include <gmsh.h>

int main(int argc, char **argv) {
    gmsh::initialize();

    gmsh::model::add("t1");

    double lc = 0.03;
    double r = 0.7;
    double d1 = 0.1;
    double d2 = 0.2;

    // torus center

    gmsh::model::geo::addPoint(0, 0, -d2, lc, 2);
    gmsh::model::geo::addPoint(0, 0, 0, lc, 0);
    gmsh::model::geo::addPoint(0, 0, d2, lc, 1);

    gmsh::model::geo::addPoint(0, 0, d1, lc, 21);
    gmsh::model::geo::addPoint(0, 0, -d1, lc, 22);

    // torus itself
    for (int i = 1; i <= 2; ++i) {
        int a = 3 - 2 * i;

        // outer torus
        gmsh::model::geo::addPoint(a * r, 0, 0, lc, 3 + 5 * (i - 1));
        gmsh::model::geo::addPoint(a * (r + d2), 0, 0, lc, 4 + 5 * (i - 1));
        gmsh::model::geo::addPoint(a * r, 0, d2, lc, 5 + 5 * (i - 1));
        gmsh::model::geo::addPoint(a * (r - d2), 0, 0, lc, 6 + 5 * (i - 1));
        gmsh::model::geo::addPoint(a * r, 0, -d2, lc, 7 + 5 * (i - 1));

        gmsh::model::geo::addCircleArc(4 + 5 * (i - 1), 3 + 5 * (i - 1), 5 + 5 * (i - 1), 1 + 4 * (i - 1), 0, a, 0);
        gmsh::model::geo::addCircleArc(5 + 5 * (i - 1), 3 + 5 * (i - 1), 6 + 5 * (i - 1), 2 + 4 * (i - 1), 0, a, 0);
        gmsh::model::geo::addCircleArc(6 + 5 * (i - 1), 3 + 5 * (i - 1), 7 + 5 * (i - 1), 3 + 4 * (i - 1), 0, a, 0);
        gmsh::model::geo::addCircleArc(7 + 5 * (i - 1), 3 + 5 * (i - 1), 4 + 5 * (i - 1), 4 + 4 * (i - 1), 0, a, 0);

        // inner torus
        gmsh::model::geo::addPoint(a * (r + d1), 0, 0, lc, 13 + 4 * (i - 1));
        gmsh::model::geo::addPoint(a * r, 0, d1, lc, 14 + 4 * (i - 1));
        gmsh::model::geo::addPoint(a * (r - d1), 0, 0, lc, 15 + 4 * (i - 1));
        gmsh::model::geo::addPoint(a * r, 0, -d1, lc, 16 + 4 * (i - 1));

        gmsh::model::geo::addCircleArc(13 + 4 * (i - 1), 3 + 5 * (i - 1), 14 + 4 * (i - 1), 17 + 4 * (i - 1), 0, a, 0);
        gmsh::model::geo::addCircleArc(14 + 4 * (i - 1), 3 + 5 * (i - 1), 15 + 4 * (i - 1), 18 + 4 * (i - 1), 0, a, 0);
        gmsh::model::geo::addCircleArc(15 + 4 * (i - 1), 3 + 5 * (i - 1), 16 + 4 * (i - 1), 19 + 4 * (i - 1), 0, a, 0);
        gmsh::model::geo::addCircleArc(16 + 4 * (i - 1), 3 + 5 * (i - 1), 13 + 4 * (i - 1), 20 + 4 * (i - 1), 0, a, 0);
    }

    std::vector<int> outerSurfaces;
    std::vector<int> innerSurfaces;
    for (int i = 0; i < 8; ++i) {
        outerSurfaces.push_back(i + 1);
        innerSurfaces.push_back(i + 9);
    }

    for (int i = 1; i <= 2; ++i) {
        int a = i / 2;
        int b = i % 2;

        // outer torus
        gmsh::model::geo::addCircleArc(9 * a + 4 * b, 0, 9 * b + 4 * a, 9 + 4 * (i - 1));
        gmsh::model::geo::addCircleArc(10 * a + 5 * b, 1, 10 * b + 5 * a, 10 + 4 * (i - 1));
        gmsh::model::geo::addCircleArc(11 * a + 6 * b, 0, 11 * b + 6 * a, 11 + 4 * (i - 1));
        gmsh::model::geo::addCircleArc(12 * a + 7 * b, 2, 12 * b + 7 * a, 12 + 4 * (i - 1));

        gmsh::model::geo::addCurveLoop({(5 * a + b), 10 + 4 * (i - 1), -(5 * b + a), -(9 + 4 * (i - 1))},
                                       1 + 4 * (i - 1));
        gmsh::model::geo::addSurfaceFilling({1 + 4 * (i - 1)}, 1 + 4 * (i - 1));

        gmsh::model::geo::addCurveLoop({(6 * a + 2 * b), 11 + 4 * (i - 1), -(6 * b + 2 * a), -(10 + 4 * (i - 1))},
                                       2 + 4 * (i - 1));
        gmsh::model::geo::addSurfaceFilling({2 + 4 * (i - 1)}, 2 + 4 * (i - 1));

        gmsh::model::geo::addCurveLoop({(7 * a + 3 * b), 12 + 4 * (i - 1), -(7 * b + 3 * a), -(11 + 4 * (i - 1))},
                                       3 + 4 * (i - 1));
        gmsh::model::geo::addSurfaceFilling({3 + 4 * (i - 1)}, 3 + 4 * (i - 1));

        gmsh::model::geo::addCurveLoop({(8 * a + 4 * b), 9 + 4 * (i - 1), -(8 * b + 4 * a), -(12 + 4 * (i - 1))},
                                       4 + 4 * (i - 1));
        gmsh::model::geo::addSurfaceFilling({4 + 4 * (i - 1)}, 4 + 4 * (i - 1));

        // inner torus
        gmsh::model::geo::addCircleArc(17 * a + 13 * b, 0, 17 * b + 13 * a, 25 + 4 * (i - 1));
        gmsh::model::geo::addCircleArc(18 * a + 14 * b, 21, 18 * b + 14 * a, 26 + 4 * (i - 1));
        gmsh::model::geo::addCircleArc(19 * a + 15 * b, 0, 19 * b + 15 * a, 27 + 4 * (i - 1));
        gmsh::model::geo::addCircleArc(20 * a + 16 * b, 22, 20 * b + 16 * a, 28 + 4 * (i - 1));

        gmsh::model::geo::addCurveLoop({(21 * a + 17 * b), 26 + 4 * (i - 1), -(21 * b + 17 * a), -(25 + 4 * (i - 1))},
                                       9 + 4 * (i - 1));
        gmsh::model::geo::addSurfaceFilling({9 + 4 * (i - 1)}, 9 + 4 * (i - 1));

        gmsh::model::geo::addCurveLoop({(22 * a + 18 * b), 27 + 4 * (i - 1), -(22 * b + 18 * a), -(26 + 4 * (i - 1))},
                                       10 + 4 * (i - 1));
        gmsh::model::geo::addSurfaceFilling({10 + 4 * (i - 1)}, 10 + 4 * (i - 1));

        gmsh::model::geo::addCurveLoop({(23 * a + 19 * b), 28 + 4 * (i - 1), -(23 * b + 19 * a), -(27 + 4 * (i - 1))},
                                       11 + 4 * (i - 1));
        gmsh::model::geo::addSurfaceFilling({11 + 4 * (i - 1)}, 11 + 4 * (i - 1));

        gmsh::model::geo::addCurveLoop({(24 * a + 20 * b), 25 + 4 * (i - 1), -(24 * b + 20 * a), -(28 + 4 * (i - 1))},
                                       12 + 4 * (i - 1));
        gmsh::model::geo::addSurfaceFilling({12 + 4 * (i - 1)}, 12 + 4 * (i - 1));
    }

    gmsh::model::geo::addSurfaceLoop(outerSurfaces, 1);
    gmsh::model::geo::addSurfaceLoop(innerSurfaces, 2);
    gmsh::model::geo::addVolume({1, 2}, 1);
    // meshing and so on
    gmsh::model::geo::synchronize();

    gmsh::model::mesh::generate(3);

    //gmsh::write("t1.msh");

    std::set<std::string> args(argv, argv + argc);
    if (!args.count("-nopopup")) gmsh::fltk::run();

    gmsh::finalize();
    return 0;
}
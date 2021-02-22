#include <set>
#include <gmsh.h>

int main(int argc, char **argv) {
    gmsh::initialize();

    gmsh::model::add("t0");

    double lc = 1e-2;

    // bottom circle
    gmsh::model::geo::addPoint(0, 0, 0, lc, 3);
    gmsh::model::geo::addPoint(.1, 0, 0, lc, 1);
    gmsh::model::geo::addPoint(-.1, 0, 0, lc, 2);

    gmsh::model::geo::addCircleArc(1, 3, 2, 1);
    gmsh::model::geo::addCircleArc(2, 3, 1, 2);

    // top circle
    gmsh::model::geo::addPoint(0, 0, .2, lc, 6);
    gmsh::model::geo::addPoint(.1, 0, .2, lc, 4);
    gmsh::model::geo::addPoint(-.1,  0,.2, lc, 5);

    gmsh::model::geo::addCircleArc(4, 6, 5, 3);
    gmsh::model::geo::addCircleArc(5, 6, 4, 4);

    // cylinder heights

    gmsh::model::geo::addLine(1, 4, 5);
    gmsh::model::geo::addLine(2, 5, 6);

    // curve loops and surfaces
    gmsh::model::geo::addCurveLoop({1, 2}, 1);
    gmsh::model::geo::addPlaneSurface({1}, 1);
    gmsh::model::geo::addCurveLoop({3, 4}, 2);
    gmsh::model::geo::addPlaneSurface({2}, 2);

    gmsh::model::geo::addCurveLoop({1, 6, -3, -5}, 3);
    gmsh::model::geo::addSurfaceFilling({3}, 3);
    gmsh::model::geo::addCurveLoop({2, 5, -4, -6}, 4);
    gmsh::model::geo::addSurfaceFilling({4}, 4);

    // volume
    gmsh::model::geo::addSurfaceLoop({1, 3, 4, 2}, 1);
    gmsh::model::geo::addVolume({1}, 1);

    gmsh::model::geo::synchronize();

    gmsh::model::mesh::generate(3);

    //gmsh::write("t0.msh");

    std::set<std::string> args(argv, argv + argc);
    if (!args.count("-nopopup")) gmsh::fltk::run();

    gmsh::finalize();

    return 0;
}
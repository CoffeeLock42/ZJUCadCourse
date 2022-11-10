#include <iostream>
#include <glm/glm.hpp>
#include "EulerOp.hpp"
#include "Sweep.hpp"
#include "Draw.hpp"

int displayEulerOp = 1; // 1: display each Euler Operation, 0: otherwise

// cube with one triangle hole
Solid *one_hole()
{
    std::cout << "construct cube with one triangle hole:" << std::endl;
    Solid *solid;
    Vertex *v[4];
    solid = EulerOp::mvfs(v[0], glm::vec3(0.0, 0.0, 0.0));
    Face *topFace = solid->Sfaces;
    Loop *top = topFace->Floops;

    EulerOp::mev(v[0], v[1], glm::vec3(2.0, 0.0, 0.0), top);
    EulerOp::mev(v[1], v[2], glm::vec3(2.0, 0.0, 2.0), top);
    EulerOp::mev(v[2], v[3], glm::vec3(0.0, 0.0, 2.0), top);
    Loop *bottom = EulerOp::mef(v[3], v[0], top);

    Vertex *v1[3];
    HalfEdge *tempEdge = EulerOp::mev(v[0], v1[0], glm::vec3(0.5, 0, 0.5), top);
    EulerOp::mev(v1[0], v1[1], glm::vec3(1.5, 0, 0.5), top);
    EulerOp::mev(v1[1], v1[2], glm::vec3(1, 0, 1.5), top);
    Loop *hole_bottom = EulerOp::mef(v1[2], v1[0], top);
    hole_bottom->inner = true;
    EulerOp::kfmrh(bottom, hole_bottom);

    Loop *hole_top = EulerOp::kemr(tempEdge->HEedge, top);
    hole_top->inner = true;

    solid = Sweep::sweep(topFace, glm::vec3(0.0, 1.0, 0.0), 0.5);

    return solid;
}

Solid *three_hole()
{
    std::cout << "construct cube with three triangle holes:" << std::endl;
    Solid *solid;
    Vertex *v[4];
    solid = EulerOp::mvfs(v[0], glm::vec3(0.0, 0.0, 0.0));
    Face *topFace = solid->Sfaces;
    Loop *top = topFace->Floops;

    EulerOp::mev(v[0], v[1], glm::vec3(2.0, 0.0, 0.0), top);
    EulerOp::mev(v[1], v[2], glm::vec3(2.0, 0.0, 2.0), top);
    EulerOp::mev(v[2], v[3], glm::vec3(0.0, 0.0, 2.0), top);
    Loop *bottom = EulerOp::mef(v[3], v[0], top);

    Vertex *v1[4];
    HalfEdge *tempEdge = EulerOp::mev(v[0], v1[0], glm::vec3(0.3, 0, 1.1), top);
    EulerOp::mev(v1[0], v1[1], glm::vec3(0.7, 0, 1.1), top);
    EulerOp::mev(v1[1], v1[2], glm::vec3(0.7, 0, 1.5), top);
    EulerOp::mev(v1[2], v1[3], glm::vec3(0.3, 0, 1.5), top);
    Loop *hole_bottom = EulerOp::mef(v1[3], v1[0], top);
    hole_bottom->inner = true;
    EulerOp::kfmrh(bottom, hole_bottom);

    Loop *hole_top = EulerOp::kemr(tempEdge->HEedge, top);
    hole_top->inner = true;

    Vertex *v2[4];
    tempEdge = EulerOp::mev(v[0], v2[0], glm::vec3(1.3, 0, 1.1), top);
    EulerOp::mev(v2[0], v2[1], glm::vec3(1.7, 0, 1.1), top);
    EulerOp::mev(v2[1], v2[2], glm::vec3(1.7, 0, 1.5), top);
    EulerOp::mev(v2[2], v2[3], glm::vec3(1.3, 0, 1.5), top);
    hole_bottom = EulerOp::mef(v2[3], v2[0], top);
    hole_bottom->inner = true;
    EulerOp::kfmrh(bottom, hole_bottom);

    hole_top = EulerOp::kemr(tempEdge->HEedge, top);
    hole_top->inner = true;

    Vertex *v3[3];
    tempEdge = EulerOp::mev(v[0], v3[0], glm::vec3(0.6, 0, 0.8), top);
    EulerOp::mev(v3[0], v3[1], glm::vec3(1.4, 0, 0.8), top);
    EulerOp::mev(v3[1], v3[2], glm::vec3(1, 0, 0.4), top);

    hole_bottom = EulerOp::mef(v3[2], v3[0], top);
    hole_bottom->inner = true;
    EulerOp::kfmrh(bottom, hole_bottom);

    hole_top = EulerOp::kemr(tempEdge->HEedge, top);
    hole_top->inner = true;

    solid = Sweep::sweep(topFace, glm::vec3(0.0, 1.0, 0.0), 0.8);

    return solid;
}

void debug(Solid *solid)
{
    Solid *ptr = solid;
    int solidID = 0;
    while (ptr != nullptr)
    {
        std::cout << "********************" << std::endl;
        std::cout << "Solid#" << ++solidID << std::endl;

        std::cout << "Number of faces: " << ptr->faceNum << std::endl;
        std::cout << "Number of edges: " << ptr->edgeNum << std::endl;
        std::cout << "--------------------" << std::endl;
        int faceID = 0;
        for (Face *faceI = ptr->Sfaces; faceI != nullptr; faceI = faceI->Fnext)
        {
            std::cout << "Number of loops in Face#" << ++faceID << ": "
                      << faceI->LoopNum << std::endl;
        }
        std::cout << std::endl;
        faceID = 0;
        std::cout << "Loop Information:" << std::endl;
        for (Face *faceI = ptr->Sfaces; faceI != nullptr; faceI = faceI->Fnext)
        {
            std::cout << "Face#" << ++faceID << std::endl;
            int loopID = 0;
            for (Loop *loopI = faceI->Floops; loopI != nullptr; loopI = loopI->Lnext)
            {
                std::cout << "  Loop#" << ++loopID << ": ";
                loopI->debug();
            }
            std::cout << "-----------------" << std::endl;
        }

        std::cout << "*******************" << std::endl
                  << std::endl;
        ptr = ptr->Snext;
    }
}

int main(int argc, char **argv)
{
    int opt = 2;
    if (argc > 1)
    {
        opt = (int)(argv[1][0] - '0');
    }
    Solid *solid;

    switch (opt)
    {
    case 1:
        solid = one_hole();
        break;

    case 2:
        solid = three_hole();
        break;

    default:
        std::cout << "Please input right choice:" << std::endl;
        std::cout << "  1: cube" << std::endl;
        std::cout << "  2: three_hole" << std::endl;
        exit(-1);
    }

    // debug(solid);

    // shading
    Draw::init();
    Draw::draw(solid);
    Draw::end();

    return 0;
}
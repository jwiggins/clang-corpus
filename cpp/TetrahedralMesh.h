/*****************************************************
 * TetrahedralMesh.h
 * 
 * A tetrahedral mesh volume renderer
 *
*/
#ifndef TETRAHEDRAL_MESH_H
#define TETRAHEDRAL_MESH_H

#include <queue>
#include <vector>
#include <utility>
#include <list>

using std::queue;
using std::priority_queue;
using std::vector;
using std::pair;
using std::binary_function;
using std::list;

class VisOctree;

class TetrahedralMesh {
public:
    TetrahedralMesh();
    ~TetrahedralMesh();

    void initRenderer();

    void renderVolume();
    void drawBoundary();

    float getExtentLength() const;

    void loadData(char *file);
    void writeCache(char *file);
    void loadCache(char *file);

private:

/*****************************************************
 * Private Functions
 */
    void drawTetra(int index, float vpnt[3], double t[16], double tinv[16]);
    void draw_class_1(float tv0[4], float tv1[4], float tv2[4], float tv3[4],
                                double tinv[16], bool flip);
    void draw_class_2(float tv0[4], float tv1[4], float tv2[4], float tv3[4],
                                double tinv[16]);
    void draw_class_3(float tv0[3], float tv1[3], float tv2[3], float tv3[3],
                                double tinv[16], bool flip);
    void draw_class_4(float tv0[3], float tv1[3], float tv2[3], float tv3[3],
                                double tinv[16]);

    void drawTetMeshOrderedBFS(); // Breadth First Search
    void drawTetMeshOrderedDFS(); // Depth First Search
    void octreeDFSTraverse(VisOctree *tree, int order[6], float vpnt[3],
                                    double t[16], double tinv[16]);
    void dfs(unsigned int index, float vpnt[3], double t[16], double tinv[16]);

    void octreeTraverse(VisOctree *tree, int order[6]);

    void loadTextures();

    void computeTopology();
    void genBoundaryOctree();
    void allocFaces();

    void getViewPoint(float p[3]);
    void computeNormal(float v0[3], float v1[3], float v2[3], float n[3]);
    bool sameSide(float p0[3], float p1[3], float a[3], float b[3]);
    bool pointInTriangle(float p[3], float a[3], float b[3], float c[3]);
    float triangleArea(float a[3], float b[3], float c[3]);
    float pntDist(float a[3], float b[3]);
    int classifyTetrahedron(int index, float vpnt[3]);
    void computeVisibilityOrdering();

/*****************************************************
 * Member Variables
 */
    float (*mVerts)[4];
    float (*mFplanes)[4];
    unsigned int (*mFaces)[6];

    float mMinExt[3];
    float mMaxExt[3];
    float mMinFunc;
    float mMaxFunc;

    struct Tetra {
        unsigned int verts[4];
        float func;
        unsigned int faces[4];
        float centroid[4]; // centroid[3] is the current distance from the eye
        int nbs[4]; // neighbors
        unsigned char nbsf[4]; // which face on the neighbor?
        unsigned char arrow[4]; // adjacency info
        unsigned char incnt; // inbound arrow count (BFS)
        unsigned char outcnt; // outbound arrow count (DFS)
        bool v; // visited
        bool vtd; // visited this descent
    } *mTets;

    unsigned int mNumverts;
    unsigned int mNumtets;
    unsigned int mNumfaces;
    unsigned int mMaxfaces;
    float mMaxThickness;

    // Visibility ordering related variables
    VisOctree *mOrdTree;
    // priority queue declaration w/ definition of Compare operator
    struct pq_compare
    : public binary_function< pair<unsigned int,float>, pair<unsigned int, float>, bool>
    {
        bool operator ()(const pair<unsigned int,float> & a,
                                         const pair<unsigned int,float> & b) const
        { return a.second < b.second; }
    };
    priority_queue<pair<unsigned int,float>, vector<pair<unsigned int,float> >, pq_compare> mSrcQ;
    queue<unsigned int> mSinkQ;

    // labels for tetrahedron projection classes
    enum { CLASS_1_A, CLASS_1_B, CLASS_2, CLASS_3_A, CLASS_3_B, CLASS_4};
    // labels for adjacency graph edges
    enum { NOT_VISITED, INBOUND, OUTBOUND, NONE };
};

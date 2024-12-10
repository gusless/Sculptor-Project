#include "voxel.hpp"
#ifndef SCULPTOR_H
#define SCULPTOR_H

class Sculptor{
private:
    Voxel ***v; //3D matrix
    int nx, ny, nz; //dimension
    float r,g,b,a; //colors

public:
    Sculptor(int nx, int ny, int nz); //constructor
    ~Sculptor(); //destructor

    //methods
    void setColor(int r, int g, int b, float a);
    void putVoxel(int x, int y, int z);
    void cutVoxel(int x, int y, int z);
    void putBox(int x0, int y0, int z0, int x1, int y1, int z1);
    void cutBox(int x0, int y0, int z0, int x1, int y1, int z1);
    void putSphere(int xcenter, int ycenter, int zcenter, int radius);
    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    //writer
    void writeOFF(const char* filename);
};


#endif // SCULPTOR_H

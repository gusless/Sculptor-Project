#include <iostream>
#include <fstream>
#include "Sculptor.hpp"
#include "voxel.hpp"

Sculptor::Sculptor(int nx, int ny, int nz){
    this->nx = nx;
    this->ny = ny;
    this->nz = nz;


    v = new Voxel **[nx];
    v[0] = new Voxel *[nx*ny];
    v[0][0] = new Voxel [nx*ny*nz];

    for(int i=1; i<nx; i++){
        v[i] = v[i-1]+ny;
    }
    for(int i=1; i<nx*ny; i++){
        v[0][i] = v[0][i-1]+nz;
    }
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<0; k++){
                v[i][j][k].show = false;
            }
        }
    }
}

Sculptor::~Sculptor(){
    delete[] v[0][0];
    delete[] v[0];
    delete[] v;
}

void Sculptor::setColor(int r, int g, int b, float a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Sculptor::putVoxel(int x, int y, int z){
    if((x<nx && x>=0) && (y<ny && y>=0) && (z<nz && z>=0)){
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
        v[x][y][z].show = true;
    }else{
        std::cout<< "O voxel nao foi posicionado no comando putVoxel("
                  << x << ", " << y << ", " << z
                  << "), digite coordenadas que estejam dentro da matriz ("
                  << nx << ", " << ny << ", " << nz << ")" << std::endl;
    }
}

void Sculptor::cutVoxel(int x, int y, int z){
    if((x<nx && x>=0) && (y<ny && y>=0) && (z<nz && z>=0)){
        v[x][y][z].r = 0;
        v[x][y][z].g = 0;
        v[x][y][z].b = 0;
        v[x][y][z].a = a;
        v[x][y][z].show = false;
    }else{
        std::cout<< "O voxel nao foi apagado no comando cutVoxel("
                  << x << ", " << y << ", " << z
                  << "), digite coordenadas que estejam dentro da matriz ("
                  << nx << ", " << ny << ", " << nz << ")" << std::endl;
    }
}

void Sculptor::putBox(int x0, int y0, int z0, int x1, int y1, int z1){
    int verifier = 0;
    for(int i = x0; i<x1; i++){
        for(int j = y0; j<y1; j++){
            for(int k = z0; k<z1; k++){
                if((i<nx && i>=0) && (j<ny && j>=0) && (k<nz && k>=0)){ //Vai colocar a caixa apenas se estiver dentro da matriz principal,
                    v[i][j][k].r = r;                                   //caso não esteja, vai colocar uma caixa cortada.
                    v[i][j][k].g = g;                                   //Isso tambem serve para proteger o programa,
                    v[i][j][k].b = b;                                   //impedindo o uso inadequado da matriz alocada.
                    v[i][j][k].a = a;                                   //isso serve para todos os metodos
                    v[i][j][k].show = true;
                    verifier++;
                }
            }
        }
    }
    if(verifier==0){
        std::cout<< "Nenhum voxel foi posicionado no comando putBox("
                  << x0 << ", " << y0 << ", " << z0 << ", " << x1 << ", " << y1 << ", " << z1
                  << "), digite coordenadas que estejam dentro da matriz ("
                  << nx << ", " << ny << ", " << nz << ")" << std::endl;
    }
}

void Sculptor::cutBox(int x0, int y0, int z0, int x1, int y1, int z1){
    int verifier = 0;
    for(int i = x0; i<x1; i++){
        for(int j = y0; j<y1; j++){
            for(int k = z0; k<z1; k++){
                if((i<nx && i>=0) && (j<ny && j>=0) && (k<nz && k>=0)){
                    v[i][j][k].r = 0;
                    v[i][j][k].g = 0;
                    v[i][j][k].b = 0;
                    v[i][j][k].a = 0;
                    v[i][j][k].show = false;
                    verifier++;
                }
            }
        }
    }
    if(verifier==0){
        std::cout<< "Nenhum voxel foi apagado no comando cutBox("
                  << x0 << ", " << y0 << ", " << z0 << ", " << x1 << ", " << y1 << ", " << z1
                  << "), digite coordenadas que estejam dentro da matriz ("
                  << nx << ", " << ny << ", " << nz << ")" << std::endl;
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    int verifier = 0;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                int sphere = (xcenter-i)*(xcenter-i) + (ycenter-j)*(ycenter-j) + (zcenter-k)*(zcenter-k);
                if((i<nx && i>=0) && (j<ny && j>=0) && (k<nz && k>=0)){
                    if(sphere<=radius*radius){
                        v[i][j][k].r = r;
                        v[i][j][k].g = g;
                        v[i][j][k].b = b;
                        v[i][j][k].a = a;
                        v[i][j][k].show = true;
                        verifier++;
                    }
                }
            }
        }
    }
    if(verifier==0){
        std::cout<< "Nenhum voxel foi posicionado no comando putSphere("
                  << xcenter << ", " << ycenter << ", " << zcenter << ", " << radius
                  << "), digite coordenadas que estejam dentro da matriz ("
                  << nx << ", " << ny << ", " << nz << ")" << std::endl;
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    int verifier = 0;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                int sphere = (xcenter-i)*(xcenter-i) + (ycenter-j)*(ycenter-j) + (zcenter-k)*(zcenter-k);
                if((i<nx && i>=0) && (j<ny && j>=0) && (k<nz && k>=0)){
                    if(sphere<=radius*radius){
                        v[i][j][k].r = 0;
                        v[i][j][k].g = 0;
                        v[i][j][k].b = 0;
                        v[i][j][k].a = 0;
                        v[i][j][k].show = false;
                        verifier++;
                    }
                }
            }
        }
    }
    if(verifier==0){
        std::cout<< "Nenhum voxel foi apagado no comando cutSphere("
                  << xcenter << ", " << ycenter << ", " << zcenter << ", " << radius
                  << "), digite coordenadas que estejam dentro da matriz ("
                  << nx << ", " << ny << ", " << nz << ")" << std::endl;
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int verifier = 0;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                int ellipsoid = ((xcenter-i)*(xcenter-i))/rx + ((ycenter-j)*(ycenter-j))/ry + ((zcenter-k)*(zcenter-k))/rz - 1;
                if((i<nx && i>=0) && (j<ny && j>=0) && (k<nz && k>=0)){
                    if(ellipsoid<=rx && ellipsoid<=ry && ellipsoid<=rz){
                        v[i][j][k].r = r;
                        v[i][j][k].g = g;
                        v[i][j][k].b = b;
                        v[i][j][k].a = a;
                        v[i][j][k].show = true;
                        verifier++;
                    }
                }
            }
        }
    }
    if(verifier==0){
        std::cout<< "Nenhum voxel foi posicionado no comando putEllipsoid("
                  << xcenter << ", " << ycenter << ", " << zcenter << ", " << rx << ", " << ry << ", " << rz
                  << "), digite coordenadas que estejam dentro da matriz ("
                  << nx << ", " << ny << ", " << nz << ")" << std::endl;
    }
}


void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int verifier = 0;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                int ellipsoid = ((xcenter-i)*(xcenter-i))/rx + ((ycenter-j)*(ycenter-j))/ry + ((zcenter-k)*(zcenter-k))/rz - 1;
                if((i<nx && i>=0) && (j<ny && j>=0) && (k<nz && k>=0)){
                    if(ellipsoid<=rx && ellipsoid<=ry && ellipsoid<=rz){
                        v[i][j][k].r = 0;
                        v[i][j][k].g = 0;
                        v[i][j][k].b = 0;
                        v[i][j][k].a = 0;
                        v[i][j][k].show = false;
                        verifier++;
                    }
                }
            }
        }
    }
    if(verifier==0){
        std::cout<< "Nenhum voxel foi apagado no comando cutEllipsoid("
                  << xcenter << ", " << ycenter << ", " << zcenter << ", " << rx << ", " << ry << ", " << rz
                  << "), digite coordenadas que estejam dentro da matriz ("
                  << nx << ", " << ny << ", " << nz << ")" << std::endl;
    }
}


void Sculptor::writeOFF(const char* filename){
    std::ofstream file;
    file.open(filename);

    if(!file.is_open()){
        std::cerr << "Erro ao abrir o arquivo" << std::endl;
        std::cin.get();
        exit(1);
    }

    file << "OFF" << std::endl;

    int voxels = 0, val = 0;

    for(int i=0; i<nx; i++){
        for(int j=0; j<nx; j++){
            for(int k=0; k<nx; k++){
                if(v[i][j][k].show == true){
                    voxels++;
                }
            }
        }
    }

    file << voxels*8 << " " << voxels*6 << " " << 0 << std::endl;

    for(int i=0; i<nx; i++){
        for(int j=0; j<nx; j++){
            for(int k=0; k<nx; k++){
                if(v[i][j][k].show == true){
                    file << -0.5 + i << " " <<  0.5 + j << " " << -0.5 + k << std::endl;
                    file << -0.5 + i << " " << -0.5 + j << " " << -0.5 + k << std::endl;
                    file <<  0.5 + i << " " << -0.5 + j << " " << -0.5 + k << std::endl;
                    file <<  0.5 + i << " " <<  0.5 + j << " " << -0.5 + k << std::endl;
                    file << -0.5 + i << " " <<  0.5 + j << " " <<  0.5 + k << std::endl;
                    file << -0.5 + i << " " << -0.5 + j << " " <<  0.5 + k << std::endl;
                    file <<  0.5 + i << " " << -0.5 + j << " " <<  0.5 + k << std::endl;
                    file <<  0.5 + i << " " <<  0.5 + j << " " <<  0.5 + k << std::endl;
                }
            }
        }
    }

    for(int i=0; i<nx; i++){
        for(int j=0; j<nx; j++){
            for(int k=0; k<nx; k++){
                if(v[i][j][k].show == true){
                    file << 4 << " " << 0 + val << " " << 3 + val  << " " << 2 + val <<  " " << 1 + val << " " <<
                        v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a <<std::endl;
                    file << 4 << " " << 4 + val << " " << 5 + val  << " " << 6 + val <<  " " << 7 + val << " " <<
                        v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a <<std::endl;
                    file << 4 << " " << 0 + val << " " << 1 + val  << " " << 5 + val <<  " " << 4 + val << " " <<
                        v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a <<std::endl;
                    file << 4 << " " << 0 + val << " " << 4 + val  << " " << 7 + val <<  " " << 3 + val << " " <<
                        v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a <<std::endl;
                    file << 4 << " " << 3 + val << " " << 7 + val  << " " << 6 + val <<  " " << 2 + val << " " <<
                        v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a <<std::endl;
                    file << 4 << " " << 1 + val << " " << 2 + val  << " " << 6 + val <<  " " << 5 + val << " " <<
                        v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a <<std::endl;
                    val+=8;
                }
            }
        }
    }
    file.close();
}





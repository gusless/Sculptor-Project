#include "Sculptor.hpp"
#include <fstream>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#endif

namespace fs = std::filesystem;
const int LEN = 150;

//funcao usada para achar o caminho do arquivo a ser aberto
std::string find_path(const std::string &directory, const std::string &filename){
    try{
        for(const auto &entry : fs::recursive_directory_iterator(directory)){
            //std::cout << entry.path().string() << std::endl;
            if(entry.is_regular_file() && entry.path().filename() == filename){
                return fs::absolute(entry.path()).string();
            }
        }
    } catch(const std::filesystem::filesystem_error &e){
    std::cerr << "Erro ao acessar a pasta" << e.what() << std::endl;
    }
    return "";
}

//funcao para abrir o arquvi no windows
void win_open_file(const char* filename){
    std::string file(filename);
    std::string file_local = find_path("../../",file);

    char file_path[200];
    file_local.copy(file_path,file_local.size());
    file_path[file_local.size()] = '\0';

    //std::cout << filename << std::endl;
    //std::cout << file_path << std::endl;

    if(!std::ifstream(file_path)){
        std::cerr << "Arquivo nao encontrado" << std::endl;
        return;
    }
#ifdef _WIN32
    ShellExecute(0, "open", file_path, NULL, NULL, SW_SHOWNORMAL);
#endif
}

int main(){
    Sculptor v(LEN,LEN,LEN);
    char filename[] = "offFile.off";

    //cano
    v.setColor(101, 106, 115, 1);
    for(int i=75; i<148; i++){
        v.putSphere(i,51,50,3);
    }
    for(int i=75; i<150; i++){
        v.cutSphere(i,51,50,2);
    }
    v.cutBox(146,46,46,150,55,55);

    v.setColor(90, 94, 102, 1);
    v.putBox(139,55,50,142,57,51);
    v.cutVoxel(139,56,50);

    //corpo
    v.setColor(101, 106, 115, 1);
    v.putBox(48,36,49,57,56,52);

    //cabo
    v.setColor(105, 77, 79, 1);
    v.putEllipsoid(51,26,50,20,70,2);

    v.setColor(101, 106, 115, 1);
    v.putEllipsoid(50,26,50,19,70,1);

    v.setColor(105, 77, 79, 1);
    v.putBox(44,18,49,45,35,52);
    v.putBox(45,15,49,47,38,52);
    v.cutBox(40,7,47,58,15,53);
    v.putVoxel(47,15,49);
    v.putVoxel(47,15,51);

    for(int j=33;j<38;j++){
        v.putVoxel(53,j,51);
        v.putVoxel(53,j,49);
        v.putVoxel(53,j-18,49);
        v.putVoxel(53,j-18,51);
    }
    for(int j=16;j<33;j++){
        v.putVoxel(52,j,49);
        v.putVoxel(52,j,51);
    }

    v.setColor(101, 106, 115, 1);
    v.putVoxel(45,15,50);
    v.putVoxel(46,15,50);
    v.cutEllipsoid(63,26,50,14,45,6);

    v.putBox(45,37,50,46,41,51);
    v.putBox(47,41,50,48,43,51);

    v.setColor(105, 77, 79, 1);
    v.putBox(55,38,49,57,41,52);

    v.setColor(90, 94, 102,1);
    v.putEllipsoid(49,35,50,2,2,2);
    v.putEllipsoid(49,20,50,2,2,2);

    //gatilho e guarda
    v.setColor(101, 106, 115, 1);
    v.putBox(57,36,49,78,39,52);
    v.cutSphere(79,35,50,5);
    v.cutEllipsoid(57,35,50,2,3,5);
    v.putVoxel(55,38,50);
    v.putVoxel(56,39,50);

    v.putEllipsoid(67,33,50,12,8,2);
    v.cutEllipsoid(67,33,50,7,4,3);

    v.putEllipsoid(68,34,50,3,4,2);
    v.cutEllipsoid(69,34,50,3,3,2);
    v.putBox(65,32,49,66,38,52);
    v.cutBox(66,32,52,68,37,53);
    v.cutBox(66,32,48,68,37,49);

    //corpo (continuacao)
    v.setColor(101, 106, 115, 1);
    for(int i=60; i<75; i++){
        v.putEllipsoid(i,47,50,10,22,1);
    }
    v.cutSphere(45,57,50,13);
    v.cutVoxel(58,55,50);

    //cao
    v.setColor(90, 94, 102, 1);
    v.putEllipsoid(51,50,50,6,3,1);
    v.cutEllipsoid(49,49,50,6,3,1);

    //tambor
    v.setColor(90, 94, 102, 1);
    for(int i=61; i<74; i++){
        v.putEllipsoid(i,47,50,1,19,19);
    }

    for(int i=60; i<80; i++){
        v.cutEllipsoid(i,49,54,1,1,1);
        v.cutEllipsoid(i,44,54,1,1,1);
        v.cutEllipsoid(i,49,46,1,1,1);
        v.cutEllipsoid(i,44,46,1,1,1);
        v.cutEllipsoid(i,51,50,1,1,1);
    }
    v.cutBox(60,46,57,80,48,58);
    v.cutBox(60,46,43,80,48,44);

    //balas
    v.setColor(145, 131, 67, 1);
    for(int i=60; i<73; i++){
        v.putEllipsoid(i,49,54,1,1,1);
        v.putEllipsoid(i,44,54,1,1,1);
        v.putEllipsoid(i,49,46,1,1,1);
        v.putEllipsoid(i,44,46,1,1,1);
        v.putEllipsoid(i,51,50,1,1,1);
    }

    //traseira do tambor
    v.setColor(101, 106, 115, 1);
    v.cutEllipsoid(60,47,50,1,19,19);
    v.cutBox(75,42,45,76,53,55);
    v.putEllipsoid(60,47,50,1,11,11);

    //vareta do extrator
    for(int i=79; i<101; i++){
        v.putSphere(i,46,50,1);
    }
    v.cutVoxel(101,46,50);

    //detalhes
    v.setColor(90, 94, 102,1);
    v.putVoxel(98,44,50);
    v.putEllipsoid(59,47,48,3,1,1);
    v.putBox(53,44,48,55,46,49);
    v.putVoxel(57,42,52);
    v.putVoxel(55,45,52);

    v.writeOFF(filename);

    win_open_file(filename);

    return 0;
}

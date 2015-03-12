#ifndef __SEMD2MESH_H__
#define __SEMD2MESH_H__

#include "SEMesh.h"

#include <string>

#define MD2_IDENT				(('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')

/*** Tipos do formato MD2 ***/
// vetor de 3 floats
//typedef float tMD2Vec[3];

// vértice
struct tMD2Vertex
{
	unsigned char	v[3];				// coordenadas (compressed)
	unsigned char	lightnormalindex;	// índice da normal do vértice

};

// frame
template <class T>
struct tMD2Frame
{
	T   	    scale[3];		// multiplicadores escalares de cada vértice
	T   	    translate[3];	// translação de cada vértice
	char	    name[16];		// nome do frame
	tMD2Vertex	verts[1];		// variável redimensionada

};

// header
typedef struct
{
	int		ident;				// identificador de arquivo MD2 : "IDP2"
	int		version;			// deve ser igual a 8

	int		skinwidth;			// largura da textura
	int		skinheight;			// altura da textura
	int		framesize;			// tamanho em bytes por frame

	int		num_skins;			// numero de texturas
	int		num_xyz;			// numero de vertices
	int		num_st;				// numero de coordenadas de textura
	int		num_tris;			// numero de triangulos
	int		num_glcmds;			// numero de comandos OpenGL
	int		num_frames;			// numero de frames

	int		ofs_skins;			// offset das texturas
	int		ofs_st;				// offset das coordenadas de textura
	int		ofs_tris;			// offset dos triangulos
	int		ofs_frames;			// offset dos frames
	int		ofs_glcmds;			// offset dos comandos OpenGL
	int		ofs_end;			// offset do fim de arquivo

} tMD2;

template <class T> class SEMD2Mesh : public SEMesh<T>
{
  public:
    SEMD2Mesh() : SEMesh<T>() {}
    SEMD2Mesh(std::string filename) : SEMesh<T>() { loadMesh(filename); }
    ~SEMD2Mesh() {}

    virtual bool loadBufferFromFile(std::string f, uint32_t i);

            bool loadMesh(std::string f) { return SEMesh<T>::loadMesh(f); }

  private:
    typedef T tMD2Vec[3];

    enum {
      NUMVERTEXNORMALS = 162,
      SHADEDOT_QUANT = 16,
      MAX_TRIANGLES = 4096,
      MAX_VERTS = 2048,
      MAX_FRAMES = 512,
      MAX_MD2SKINS = 32,
      MAX_SKINNAME = 64,
      MD2_VERSION = 8
    };

    int numFrames;
    int numXYZ;
    int numGlCmds;
    int skinW;
    int skinH;

    tMD2Vec * vertices;
    tMD2Vec * interpolatedVertices;
    int     * glcmds;
    int     * lightnormals;

    static tMD2Vertex vertexNormals[ NUMVERTEXNORMALS ];
    static T          vertexNormalDots[ SHADEDOT_QUANT ][256];

};

template <class T>
tMD2Vertex SEMD2Mesh<T>::vertexNormals[ SEMD2Mesh<T>::NUMVERTEXNORMALS ] = {
  #include "../inc/MD2Normals.h"
};

template <class T>
T          SEMD2Mesh<T>::vertexNormalDots[ SEMD2Mesh<T>::SHADEDOT_QUANT ][256] = {
  #include "../inc/MD2NormalsTab.h"
};


#endif // __SEMD2MESH_H__

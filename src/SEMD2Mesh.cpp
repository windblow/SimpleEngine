#include "../inc/SEMD2Mesh.h"

#include <cstdio>

template <class T>
bool SEMD2Mesh<T>::loadBufferFromFile(std::string f, uint32_t i)
{

	FILE		 *fp;			// ponteiro de arquivo
	tMD2		 *header;		// header do modelo
	char		 *buffer;		// buffer dos frames
	tMD2Frame<T> *frame;		// frame temporário
	tMD2Vertex   *ptrverts;		// ponteiro para vértices
	int			 *ptrnormals;	// ponteiro para normais

	// tenta abrir arquivo
	if( (fp = fopen( f.c_str(), "rb" )) == NULL )
	{
		//printf("\nErro ao abrir arquivo %s", f.c_str());
		return false;
	}

	// aloca memória para o header do modelo
	if( !(header = new tMD2) )
	{
		//printf("\nErro de alocacao do MD2");
		return false;
	}

	// lê o cabeçalho
	fread( header, sizeof( tMD2 ), 1, fp );

	// verifica o número mágico e a versão do arquivo
	if( (header->ident != MD2_IDENT) && (header->version != MD2_VERSION) )
	{
		delete header;
		fclose( fp );
		return false;
	}

	// guarda as variáveis do cabeçalho localmente
	numFrames	= header->num_frames;
	numXYZ		= header->num_xyz;
	numGlCmds	= header->num_glcmds;
	skinW       = header->skinwidth;
	skinH       = header->skinheight;


	// alocação de memória para os dados da geometria
	vertices		= new tMD2Vertex[ numXYZ * numFrames ];
	lightnormals	= new int[ numXYZ * numFrames ];
	buffer			= new char[ numFrames * header->framesize ];
	glcmds			= new int[ numGlCmds ];

	// leitura do arquivo
	fseek( fp, header->ofs_frames, SEEK_SET );	// le frames
	fread( buffer, numFrames * header->framesize, 1, fp );

	fseek( fp, header->ofs_glcmds, SEEK_SET );	// le diretivas opengl
	fread( glcmds, numGlCmds, sizeof( int ), fp );

	// inicializa o vertexbuffer
	SEMesh<T>::vb_[i]=new SEVertexBuffer<T>();

	// inicializa tabela de vértices
	for( int j = 0; j < numFrames; j++ )
	{
		frame			= (tMD2Frame<T>*)&buffer[ header->framesize * j ];
		ptrverts		= &vertices[ numXYZ * j ];
		ptrnormals		= &lightnormals[ numXYZ * j ];

		for( int k = 0; k  < numXYZ; ++k )
		{
            static SEVertex<T> v_;

            // coordenadas do vértice
            v_[0] = (frame->scale[1] * frame->verts[k].v[1] + frame->translate[1]);
            v_[1] = (frame->scale[2] * frame->verts[k].v[2] + frame->translate[2]);
            v_[2] = (frame->scale[0] * frame->verts[k].v[0] + frame->translate[0]);

            // normal do vértice
            v_[3] = vertexNormals[frame->verts[k].lightnormalindex].v[0];
            v_[4] = vertexNormals[frame->verts[k].lightnormalindex].v[1];
            v_[5] = vertexNormals[frame->verts[k].lightnormalindex].v[2];

            v_.l  =

            SEMesh<T>::vb_[i].append(v_);
		}

	}

	// fecha o arquivo
	fclose( fp );

    // limpeza da memória temporária
	delete header;
	delete [] buffer;

	//calculateBoundBox();

	return true;
}

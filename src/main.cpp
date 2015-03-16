#include "../inc/SEMath.h"

#include <cstdlib>
#include <iostream>
#include <iomanip>

#define SE_PRECISION float
#define NUM_LOOPS 1000000

#define SEED      9999
//#define SEED      time(NULL)

int main(int argc, char *argv[])
{
    
           SERandomNumberGenerator<SE_PRECISION> rng(-1000.0f, 1000.0f, SEED);
    //       SEChronometer<SE_PRECISION>           cr;
    
    static SEQuaternion<SE_PRECISION>            q[NUM_LOOPS];
    static SEVec3<SE_PRECISION>                  v[NUM_LOOPS];
    static SEMat4<SE_PRECISION>                  m[NUM_LOOPS];
    
    //const  unsigned long                         numcalcs = NUM_LOOPS * NUM_LOOPS;
    const  clock_t                               interval = (SE_PRECISION)(CLOCKS_PER_SEC/60.0);
           clock_t                               tf;
    
    //       unsigned long                         equals, inequals;
           unsigned long                         quant;
    
    //SEVec3<SE_PRECISION> v0(rng.next(), rng.next(), rng.next());
    
    
    /**/
    std::cout<< "Gerando array de matrizes 4x4....";
    for (unsigned int i=0;i<NUM_LOOPS;++i)
        m[i] = SEMat4<SE_PRECISION>(rng.next(), rng.next(), rng.next(), rng.next(),
                                    rng.next(), rng.next(), rng.next(), rng.next(),
                                    rng.next(), rng.next(), rng.next(), rng.next(),
                                    rng.next(), rng.next(), rng.next(), rng.next());

    std::cout<< " pronto!" << std::endl;

    std::cout<< "Gerando array de quaternions....";
    for (unsigned int i=0;i<NUM_LOOPS;++i)
        q[i] = SEQuaternion<SE_PRECISION>(rng.next(0.0f, 2.0f)*SEMathUtil<SE_PRECISION>::PI, rng.next(), rng.next(), rng.next());

    std::cout<< " pronto!" << std::endl;

    std::cout<< "Gerando array de vetores....";
    for (unsigned int i=0;i<NUM_LOOPS;++i)
        v[i] = SEVec3<SE_PRECISION>(rng.next(), rng.next(), rng.next());
    
    std::cout<< " pronto!" << std::endl;
    std::cout<< std::endl;

    std::cout<< "Iniciando calculos de transposicao de matriz ....";
    quant=0;
    tf = clock() + interval;
    do {
      m[quant++].transpose();// std::cout<< "clock="<< clock() << std::endl;
    } while (tf > clock());
    std::cout << std::endl << " completou " << quant << " transposicoes em 16.66 milissegundos." << std::endl << std::endl;

    std::cout<< "Iniciando calculos de multiplicacao de quaternion por vetor ....";
    quant=0;
    tf = clock() + interval;
    do {
      q[quant].quickmult(v[quant]); ++quant;
    } while (tf > clock());
    std::cout << std::endl << " completou " << quant << " multiplicacoes em 16.66 milissegundos." << std::endl << std::endl;

    std::cout<< "Iniciando calculos de normalizacao de vetor ....";
    quant=0;
    tf = clock() + interval;
    do {
      v[quant++].normalize();
    } while (tf > clock());
    std::cout << std::endl << " completou " << quant << " normalizacoes em 16.66 milissegundos." << std::endl << std::endl;
    /** /
    std::cout<< "Iniciando calculo de transposicoes de matrizes ....";
    quant=0;
    tf = clock() + interval;
    do {
      m[i].transpose(); ++quant;
    } while (clock() < tf);
    std::cout<< " completou " << quant << " transposicoes em 16.66 milissegundos." << std::endl;
        
    /** /
    std::cout<< "Iniciando calculo de " << NUM_LOOPS << " transposicoes de matrizes ....";
    cr.start();
    for (unsigned int i=0;i<NUM_LOOPS;++i)
      m[i].transpose();
    cr.stop();
    std::cout<< " completou em " << cr.read() << " milissegundos." << std::endl;

    //std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2);
    /** /
    std::cout<< "Gerando array de quaternions....";
    
    for (unsigned int i=0;i<NUM_LOOPS;++i)
        q[i] = SEQuaternion<SE_PRECISION>(rng.next(0.0f, 2.0f)*SEMathUtil<SE_PRECISION>::PI, rng.next(), rng.next(), rng.next());

    std::cout<< " pronto!" << std::endl;
    std::cout<< "Gerando array de vetores....";
    
    for (int i=0;i<NUM_LOOPS;++i)
        v[i] = SEVec3<SE_PRECISION>(rng.next(), rng.next(), rng.next());
    
    std::cout<< " pronto!" << std::endl;
    std::cout<< std::endl;
    
    SEVec3<SE_PRECISION> va, vb;
    
    std::cout<< "Iniciando calculo de " << numcalcs << " multiplicacoes de quaternion por vetor ....";
    equals=inequals=0;
    cr.start();
    for (unsigned int i=0;i<NUM_LOOPS;++i)
      for (unsigned int j=0;j<NUM_LOOPS;++j)
      {
        //std::cout << q[i].lmatmult(v[j]) << std::endl;
        va = q[i].lmatmult(v[j]);
        vb = q[i]*v[j];
        if (va==vb) equals++; else inequals++;
      }
    cr.stop();
    std::cout<< " completou em " << cr.read() << " milissegundos." << std::endl;
    std::cout<< "Resultados convergentes: " << equals << "; resultados divergentes: " << inequals << std::endl;
    
    std::cout<< std::endl;
    
    std::cout<< "Iniciando calculo de " << numcalcs << " multiplicacoes de vetor por quaternion ....";
    equals=inequals=0;
    cr.start();
    for (unsigned int i=0;i<NUM_LOOPS;++i)
      for (unsigned int j=0;j<NUM_LOOPS;++j)
      {
        //std::cout << q[i].quickmult(v[j]) << std::endl;
        va = q[i].rmatmult(v[j]);
        vb = v[j]*q[i];
        if (va==vb) equals++; else inequals++;
      }
    cr.stop();
    std::cout<< " completou em " << cr.read() << " milissegundos." << std::endl;
    std::cout<< "Resultados convergentes: " << equals << "; resultados divergentes: " << inequals << std::endl;
    /* /
    std::cout<< "Iniciando calculo de " << numcalcs << " multiplicacoes de quaternion por vetor usando operador * ....";
    cr.start();
    for (unsigned int i=0;i<NUM_LOOPS;++i)
      for (unsigned int j=0;j<NUM_LOOPS;++j)
        //std::cout << q[i]*v[j] << std::endl;
        q[i]*v[j];
    cr.stop();
    std::cout<< " completou em " << cr.read() << " milissegundos." << std::endl;
    
    std::cout<< std::endl;
    
    std::cout<< "Iniciando calculo de " << numcalcs << " multiplicacoes de quaternion por vetor usando lmatmult() ....";
    cr.start();
    for (unsigned int i=0;i<NUM_LOOPS;++i)
      for (unsigned int j=0;j<NUM_LOOPS;++j)
        //std::cout << q[i].lmatmult(v[j]) << std::endl;
        q[i].lmatmult(v[j]);
    cr.stop();
    std::cout<< " completou em " << cr.read() << " milissegundos." << std::endl;
    
    std::cout<< std::endl;
    
    std::cout<< "Iniciando calculo de " << numcalcs << " multiplicacoes de quaternion por vetor usando quickmult() ....";
    cr.start();
    for (unsigned int i=0;i<NUM_LOOPS;++i)
      for (unsigned int j=0;j<NUM_LOOPS;++j)
        //std::cout << q[i].quickmult(v[j]) << std::endl;
        q[i].quickmult(v[j]);
    cr.stop();
    std::cout<< " completou em " << cr.read() << " milissegundos." << std::endl;
    /* /
    SEVec3d v(0,1,0);
    
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2) << "Posicao inicial do vetor v: " << SEVec3d(v) << std::endl << "|v| = " << SEVec3d(v).len() << std::endl << std::endl;
    
    SEQuaterniond q = SEMath::DEFAULT_ORIENTATIONd;
    
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2) << "Estado inicial do quaternion q: " << q << std::endl << "Angulo=" << q.angle() << "; Eixo=" << q.axis() << std::endl << std::endl;
    
    q.rotateByDegreesInZ(90);
    
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2) << "Estado do quaternion q apos rotacao (90 graus em Z): " << q << std::endl << "Angulo=" << q.angle() << "; Eixo=" << q.axis() << std::endl << std::endl;
    
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2) << "v * q: " << std::endl << v*q << std::endl << "|v*q| = " << (v*q).len() << std::endl << std::endl;
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2) << "q * v: " << std::endl << q*v << std::endl << "|q*v| = " << (q*v).len() << std::endl << std::endl;
    
    q.rotateByDegreesInX(45);
    
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2) << "Estado do quaternion q apos nova rotacao (45 graus em X): " << q << std::endl << "Angulo=" << q.angle() << "; Eixo=" << q.axis() << std::endl << std::endl;
    
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2) << "v * q: " << std::endl << v*q << std::endl << "|v*q| = " << (v*q).len() << std::endl << std::endl;
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2) << "q * v: " << std::endl << q*v << std::endl << "|q*v| = " << (q*v).len() << std::endl << std::endl;
    
    q.rotateByDegreesInZ(-90);
    
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2) << "Estado do quaternion q apos nova rotacao (-90 graus em Z): " << q << std::endl << "Angulo=" << q.angle() << "; Eixo=" << q.axis() << std::endl << std::endl;
    
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2) << "v * q: " << std::endl << v*q << std::endl << "|v*q| = " << (v*q).len() << std::endl << std::endl;
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2) << "q * v: " << std::endl << q*v << std::endl << "|q*v| = " << (q*v).len() << std::endl << std::endl;
    
    q.rotateByDegreesInX(-45);
    
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2) << "Estado do quaternion q apos nova rotacao (-45 graus em X): " << q << std::endl << "Angulo=" << q.angle() << "; Eixo=" << q.axis() << std::endl << std::endl;
    
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2) << "v * q: " << std::endl << v*q << std::endl << "|v*q| = " << (v*q).len() << std::endl << std::endl;
    std::cout<< std::setiosflags(std::ios::fixed) << std::setprecision(2) << "q * v: " << std::endl << q*v << std::endl << "|q*v| = " << (q*v).len() << std::endl << std::endl;
    * /
    
    SEVec3f p(0,1,0);
    //SEQuaternionf q, q0(SEMath::PI*0.25,0,0,1), q1(SEMath::PI*-0.25,1,0,0);
    
    SEQuaternionf q, q0, q1;
    
    q0.grotateByDegreesInZ(45); q0.grotateByDegreesInX(-45);
    
    q1.rotateByDegreesInZ(-45); q1.grotateByDegreesInY(90);
    
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);
    
    std::cout << std::endl;
    std::cout << "Ponto inicial p=" << p << std::endl;
    std::cout << std::endl;
    std::cout << "Rotacao inicial q0=" << q0 << " (theta=" << q0.angle() << ", eixo=" << q0.axis() << ")" << std::endl;
    std::cout << "Rotacao final q1=" << q1 << " (theta=" << q1.angle() << ", eixo=" << q1.axis() << ")" << std::endl;
    std::cout << std::endl;
    std::cout << "q0*p=" << q0*p /*<< "; p*q0=" << p*q0* / << std::endl;
    std::cout << "q0.quickmult(p)=" << q0.quickmult(p) << std::endl;
    std::cout << std::endl;
    std::cout << "q1*p=" << q1*p /*<< "; p*q0=" << p*q0* / << std::endl;
    std::cout << "q1.quickmult(p)=" << q1.quickmult(p) << std::endl;
    std::cout << std::endl;
    /*
    std::cout << std::endl;
    std::cout << "Ponto inicial p=" << p << std::endl;
    std::cout << std::endl;
    std::cout << "Rotacao inicial q0=" << q0 << " (theta=" << q0.angle() << ", eixo=" << q0.axis() << ")" << std::endl;
    std::cout << "Rotacao final q1=" << q1 << " (theta=" << q1.angle() << ", eixo=" << q1.axis() << ")" << std::endl;
    std::cout << std::endl;
    std::cout << "q0*p=" << q0*p /*<< "; p*q0=" << p*q0* / << std::endl;
    std::cout << std::endl;
    */
    
    
    return 0;
}

#ifndef GCOP_MBS_H
#define GCOP_MBS_H

#include "body3d.h"
#include "mbsmanifold.h"
#include "function.h"
#include "mbscspace.h"
#include "mbstspace.h"

namespace gcop {
  
  using namespace std;
  using namespace Eigen;


  class Joint {
  public:
    //    Joint();

    Vector6d a;    ///< axis
    Matrix4d gp;   ///< from parent to joint
    Matrix4d gc;   ///< from child to joint

    Matrix6d Ac;   ///< change of frame Ad(gc)
    Matrix4d gpi;  ///< from parent to joint inverse
    Matrix4d gci;  ///< from child to joint inverse

    Vector6d S;    ///< Jacobian S=Ac*a
  };
  
  
  /**
   * Control system modeled as an underactuated rigid body in 3d. It is meant as 
   * a base class for implementing specific vehicles. 
   *
   * The discrete mechanics is
   * based on an implicit symplectic variational integrator which is second-order accurate
   * and momentum-balance preserving. Regularity is guaranteed by choosing a time-step 
   * which does not jump out of the convex region around the initial guess from the previous
   * dynamics iteration.
   *
   * Author: Marin Kobilarov marin(at)jhu.edu
   */
  class Mbs : public System< MbsState, VectorXd> {
    
    /*
    typedef Matrix<double, c, 1> Vectorcd;
    typedef Matrix<double, c, c> Matrixcd;
    typedef Matrix<double, 6, c> Matrix6xcd;
    typedef Matrix<double, MBS_DIM(nb), c> Matrixncd;
    typedef Matrix<double, MBS_DIM(nb), MBS_DIM(nb)> Matrixnd;
    
    typedef Matrix<double, 6 + nb - 1, 1> Vectormd;
    */
    //    typedef pair<Matrix4d, Vector<double, 2*m - 6> > MbsState;
    
  public:
    /*
    class Fq : public Function<MbsState> {
    public:
    Fq(Mbs &sys) :
      Function<MbsState>(sys.cspace), sys(sys), xa(sys.nb) {
      }
      
      void F(VectorXd &f, const MbsState &xa) {
        this->xa = xa;
        sys.FK(this->xa);
        sys.ID(f, t, *xb, this->xa, *u, h);
      }
      
      Mbs &sys;
      
      double t;
      MbsState xa;
      const MbsState *xb;
      const Vectorcd *u;
      double h;
    };

    class Fva : public Function<MbsState> {
    public:
    Fva(Mbs &sys) :
      Function<MbsState>(sys.tspace), sys(sys), x(sys.nb), xa(sys.nb) {        
      }
      
      void F(VectorXd &f, const MbsState &xa) {
        this->xa = xa;
        sys.Rec(this->xa, h);        
        sys.ID(f, t, *xb, this->xa, *u, h);
      }
      
      Mbs &sys;

      MbsState x;      ///< previous state before xa
      double t;      
      MbsState xa;     ///< temporary object for xa
      const MbsState *xb;    ///< pointer to xb
      const Vectorcd *u;         ///< pointer to u
      double h;
    };    

    class Fvb : public Function<MbsState> {
    public:
    Fvb(Mbs &sys) :
      Function<MbsState>(sys.tspace), sys(sys), xb(sys.nb) {  
      }
      
      void F(VectorXd &f, const MbsState &xb) {
        this->xb = xb;
        sys.KStep(this->xb, *xa, h);
        sys.ID(f, t, this->xb, *xa, *u, h);
      }
      
      Mbs &sys;
      
      double t;
      const MbsState *xa;
      MbsState xb;
      const Vectorcd *u;
      double h;
    };

    class Fu : public Function<VectorXd> {
    public:
    Fu(Mbs &sys) :
      Function<VectorXd>(sys.U), sys(sys) {
      }
      
      void F(VectorXd &f, const VectorXd &u) {
        sys.ID(f, t, *xb, *xa, u, h);
      }
      
      Mbs &sys;
      
      double t;
      const MbsState *xa;
      const MbsState *xb;
      double h;
    };
    */

    Mbs(int nb, int c);

    virtual ~Mbs();

    void Init();

    /*
      double Step(MbsState &xb, double t, const MbsState &xa, 
      const VectorXd &u, double h,
      MatrixXd *A = 0, MatrixXd *B = 0);
    */

    double F(VectorXd &v, double t, const MbsState &xa, 
             const VectorXd &u, double h,
             MatrixXd *A = 0, MatrixXd *B = 0);

    
    void ID(VectorXd &f,
            double t, const MbsState &xb, const MbsState &xa,
            const VectorXd &u, double h);

    void FK(MbsState &x);

    void KStep(MbsState &xb, const MbsState &xa, double h);

    void Mass(MatrixXd &M, const MbsState &x);

    virtual void Force(VectorXd &f, double t, const MbsState &x, const VectorXd &u,
                       MatrixXd *A = 0, MatrixXd *B = 0) = 0;
    
    void Rec(MbsState &x, double h);

    int nb;    

    //    MbsManifold X;
    //    Rn<> U;
    //    MbsCspace cspace;
    //    MbsTspace tspace;

    vector<Body3d<>> links;    ///< link params
    
    vector<Joint> joints;

    //    vector<Vector6d> joints; ///< joint screws (nb-1) vector

    vector<Matrix6d> Ips;    ///< A'*I*A (nb) vector
    //    vector<Matrix4d> g0s;    ///< offsets (nb) vector
    //    vector<Matrix4d> g0is;   ///< their inverses (nb) vector

    vector<int> pis;          ///< parent index

    vector<vector<int> > cs;  ///< child lists

    SE3 &se3;

    bool debug;

    //    Fq fq;
    //    Fva fva;
    //    Fvb fvb;
    //    Fu fu;
    

    /*
    */
  };
}

#endif

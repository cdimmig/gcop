#ifndef GCOP_CARVIEW_H
#define GCOP_CARVIEW_H

#include "car.h"
#include "systemview.h"

namespace gcop {
  using namespace Eigen;

  class CarView : public SystemView<Vector5d> {
  public:

    /**
     *  Create a particle view of trajectory traj
     * @param sys particle
     * @param xs trajectory
     */
    CarView(const Car &sys,
            vector<Vector5d> *xs = 0);

    virtual ~CarView();
       

    void Render(const Vector5d &x);
    
    void Render(const vector<Vector5d> &xs, 
                bool rs = true,
                int is = -1, int ie = -1,
                int dis = 1, int dit = 1,
                bool dl = false);
    
    const Car &sys;
    GLUquadricObj *qobj;
  };
}

#endif

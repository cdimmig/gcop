#ifndef GCOP_GUNICYCLEVIEW_H
#define GCOP_GUNICYCLEVIEW_H

#include "gunicycle.h"
#include "systemview.h"

namespace gcop {
  using namespace Eigen;

  class GunicycleView : public SystemView<pair<Matrix3d, Vector2d> > {
  public:
    /**
     *  Create a particle view of trajectory traj
     * @param sys particle
     * @param xs trajectory
     */
    GunicycleView(const Gunicycle &sys,
                   vector<pair<Matrix3d, Vector2d> > *xs = 0);

    virtual ~GunicycleView();
    
    
    void Render(const pair<Matrix3d, Vector2d> &x);
    
    void Render(const vector<pair<Matrix3d, Vector2d> > &xs, 
                bool rs = true,
                int is = -1, int ie = -1,
                int dis = 1, int dit = 1,
                bool dl = false);
    
    const Gunicycle &sys;
    GLUquadricObj *qobj;
  };
}

#endif

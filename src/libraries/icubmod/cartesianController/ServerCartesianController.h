/**
 * \defgroup servercartesiancontroller servercartesiancontroller
 * @ingroup icub_hardware_modules 
 *  
 * Implements the server part of the <a 
 * href="http://eris.liralab.it/yarpdoc/dd/de6/classyarp_1_1dev_1_1ICartesianControl.html">Cartesian 
 * Interface</a>.
 *
 * Copyright (C) 2009 RobotCub Consortium.
 *
 * Author: Ugo Pattacini
 *
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 * This file can be edited at 
 * src/modules/cartesianController/ServerCartesianController.h 
 */

#ifndef __SERVERCARTESIANCONTROLLER_H__
#define __SERVERCARTESIANCONTROLLER_H__

#include <yarp/os/BufferedPort.h>
#include <yarp/os/RateThread.h>
#include <yarp/os/Semaphore.h>
#include <yarp/os/Stamp.h>
#include <yarp/sig/Vector.h>

#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/Wrapper.h>
#include <yarp/dev/CartesianControl.h>

#include <iCub/iKin/iKinFwd.h>
#include <iCub/iKin/iKinInv.h>

#include <deque>


class ServerCartesianController;


struct DriverDescriptor
{
    yarp::os::ConstString key;
    bool jointsDirectOrder;

    yarp::sig::Vector minAbsVels;
    bool useDefaultMinAbsVel;
};


class CartesianCtrlRpcProcessor : public yarp::os::PortReader
{
protected:
    ServerCartesianController *ctrl;

    virtual bool read(yarp::os::ConnectionReader &connection);

public:
    CartesianCtrlRpcProcessor(ServerCartesianController *_ctrl);
};


class CartesianCtrlCommandPort : public yarp::os::BufferedPort<yarp::os::Bottle>
{
protected:
    ServerCartesianController *ctrl;

    virtual void onRead(yarp::os::Bottle &command);

public:
    CartesianCtrlCommandPort(ServerCartesianController *_ctrl);
};


class ServerCartesianController : public yarp::dev::DeviceDriver,
                                  public yarp::dev::IMultipleWrapper,
                                  public yarp::dev::ICartesianControl,
                                  public yarp::os::RateThread
{
protected:
    yarp::dev::PolyDriverList drivers;
    bool attached;
    bool connected;
    bool closed;
    bool trackingMode;
    bool executingTraj;
    bool motionDone;

    yarp::os::ConstString ctrlName;
    yarp::os::ConstString slvName;
    yarp::os::ConstString kinPart;
    yarp::os::ConstString kinType;
    int numDrv;

    iCub::iKin::iKinLimb            *limb;
    iCub::iKin::iKinChain           *chain;
    iCub::iKin::MultiRefMinJerkCtrl *ctrl;
    
    std::deque<DriverDescriptor>             lDsc;
    std::deque<yarp::dev::IControlLimits*>   lLim;
    std::deque<yarp::dev::IEncoders*>        lEnc;
    std::deque<yarp::dev::IVelocityControl*> lVel;
    std::deque<int>                          lJnt;
    std::deque<int*>                         lRmp;

    unsigned int connectCnt;
    unsigned int ctrlPose;
    int          maxPartJoints;
    double       targetTol;
    double       trajTime;

    double       txToken;
    double       rxToken;
    double       txTokenLatched;
    bool         skipSlvRes;

    yarp::os::Semaphore mutex;
    yarp::os::Stamp     txInfo;

    yarp::sig::Vector xdes;
    yarp::sig::Vector qdes;
    yarp::sig::Vector velOld;
    yarp::sig::Vector fb;

    yarp::os::BufferedPort<yarp::os::Bottle>  *portSlvIn;
    yarp::os::BufferedPort<yarp::os::Bottle>  *portSlvOut;
    yarp::os::Port                            *portSlvRpc;

    CartesianCtrlCommandPort                  *portCmd;
    yarp::os::BufferedPort<yarp::sig::Vector> *portState;
    CartesianCtrlRpcProcessor                 *rpcProcessor;
    yarp::os::Port                            *portRpc;

    void init();
    void openPorts();
    void closePorts();
    bool respond(const yarp::os::Bottle &command, yarp::os::Bottle &reply);
    void stopLimbVel();
    void alignJointsBounds();
    void getFeedback(yarp::sig::Vector &_fb);
    void newController();
    bool getNewTarget();
    void sendVelocity(const yarp::sig::Vector &v);
    bool goTo(unsigned int _ctrlPose, const yarp::sig::Vector &xd, const double t);

    virtual bool threadInit();
    virtual void afterStart(bool s);
    virtual void run();
    virtual void threadRelease();

    friend class CartesianCtrlRpcProcessor;
    friend class CartesianCtrlCommandPort;

public:
    ServerCartesianController();
    ServerCartesianController(yarp::os::Searchable &config);

    virtual bool open(yarp::os::Searchable &config);
    virtual bool close();

    virtual bool pingSolver();
    virtual bool connectToSolver();

    virtual bool attachAll(const yarp::dev::PolyDriverList &p);
    virtual bool detachAll();

    virtual bool setTrackingMode(const bool f);
    virtual bool getTrackingMode(bool *f);
    virtual bool getPose(yarp::sig::Vector &x, yarp::sig::Vector &o);
    virtual bool goToPose(const yarp::sig::Vector &xd, const yarp::sig::Vector &od, const double t=0.0);
    virtual bool goToPosition(const yarp::sig::Vector &xd, const double t=0.0);
    virtual bool goToPoseSync(const yarp::sig::Vector &xd, const yarp::sig::Vector &od, const double t=0.0);
    virtual bool goToPositionSync(const yarp::sig::Vector &xd, const double t=0.0);
    virtual bool getDesired(yarp::sig::Vector &xdhat, yarp::sig::Vector &odhat, yarp::sig::Vector &qdhat);
    virtual bool getDOF(yarp::sig::Vector &curDof);
    virtual bool setDOF(const yarp::sig::Vector &newDof, yarp::sig::Vector &curDof);
    virtual bool getRestPos(yarp::sig::Vector &curRestPos);
    virtual bool setRestPos(const yarp::sig::Vector &newRestPos, yarp::sig::Vector &curRestPos);
    virtual bool getRestWeights(yarp::sig::Vector &curRestWeights);
    virtual bool setRestWeights(const yarp::sig::Vector &newRestWeights, yarp::sig::Vector &curRestWeights);
    virtual bool getLimits(int axis, double *min, double *max);
    virtual bool setLimits(int axis, const double min, const double max);
    virtual bool getTrajTime(double *t);
    virtual bool setTrajTime(const double t);
    virtual bool getInTargetTol(double *tol);
    virtual bool setInTargetTol(const double tol);
    virtual bool checkMotionDone(bool *f);
    virtual bool stopControl();

    virtual ~ServerCartesianController();
};


#endif



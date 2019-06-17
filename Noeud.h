
#ifndef NOEUD_H_
#define NOEUD_H_
#include <omnetpp.h>

using namespace omnetpp;

class Noeud : public cSimpleModule
{
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual void finish();
};
#endif

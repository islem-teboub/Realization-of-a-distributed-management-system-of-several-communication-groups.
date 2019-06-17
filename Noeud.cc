
#include <Noeud.h>
#include <string.h>
#include <omnetpp.h>
#include <Segment_m.h>

Define_Module(Noeud);


int horlogeL[100];//les horloge locales des noeuds
int estampille_source=0;
cQueue queue[100];//chaque noeud possede son propore buffer
int address_c[100][4];//les address des noeuds

void Noeud::initialize()
{
    int nbr_noeud = getParentModule() -> par("x");
address_c[getIndex()][0]=10;
address_c[getIndex()][1]=0;
address_c[getIndex()][2]= rand()%(2);//choix aléatoire de l'ID ss réseau
if(getIndex()==0){address_c[getIndex()][3]=254;}else {address_c[getIndex()][3]=getIndex();}
    //initialisation horloge
    int nbr_msg = 2;

    for (int j = 0; j < nbr_noeud; j++){
    horlogeL[j]=1;
    }

    if (getIndex()==0){
         for (int j = 1; j <= nbr_msg; j++){

             estampille_source++;

             Segment *msg = new Segment();
             msg->estampille=estampille_source;
             msg->grp_destination=0;//les messages sont destinés au noeuds appartenants au groupe 0
         for (int i = 0; i < nbr_noeud; i++)
         {
             Segment *copy = msg->dup();
             send(copy, "outport", i);
         }}
}
}

void Noeud::handleMessage(cMessage *msg)
{
    int nbr_noeud = getParentModule() -> par("x");
    Segment *m = check_and_cast<Segment *>(msg);
    ////////////////////////////////////////////////////////
    if((m->horloge_definitve==NULL)&&(m->horloge_temporaire==NULL)){
       //cest un message envoyé par la source aux destination
        if(m->grp_destination==address_c[getIndex()][2]){
 if(horlogeL[getIndex()]>m->estampille){m->horloge_temporaire=horlogeL[getIndex()]+1;}else{m->horloge_temporaire=m->estampille+1;}
 EV <<" Noeud " <<  getIndex() <<" > J'envoi un message de diffusion avec une horloge temporaire = "<< m->horloge_temporaire<<"\n";
 for (int i = 0; i < nbr_noeud; i++)
          {
              Segment *copy = m->dup();
              send(copy, "outport", i);
          }
        }else{//les noeuds qui n'appartient pas au groupe de destination indiqué dans le message vont ignoré le msg
            }
        }


 //////////////////////////////////////////////////////////

 if((m->horloge_definitve==NULL)&&(m->horloge_temporaire!=NULL)){
     if (getIndex()==0){
     //cest un message envoyé par les destination à la source
  m->horloge_definitve=m->estampille;
  int cmp = m->horloge_temporaire;
  m->horloge_temporaire=NULL;
  if(cmp>m->horloge_definitve){m->horloge_definitve=cmp+1;}

     for (int i = 0; i < nbr_noeud; i++)
  {
      Segment *copy = m->dup();
      send(copy, "outport", i);
  }

 }else {//tout les noeud autres que n0 vont ignoré le message avec lestammpille temporaire
     }
 }

 ///////////////////////////////////////////////////////////
 if(m->horloge_definitve!=NULL){
     if(m->grp_destination==address_c[getIndex()][2]){
         queue[getIndex()].insert(m);
}}}

void Noeud::finish()
{
    int nbr_noeud = getParentModule() -> par("x");
 Segment vect[50][50];
 int i=0;
for(int affiche=0;affiche<nbr_noeud;affiche++){
if(getIndex()==affiche){
////////////////
    EV <<" Noeud " <<  getIndex() <<" > Mon addresse est : " << address_c[getIndex()][0] << "." << address_c[getIndex()][1] << "."<< address_c[getIndex()][2] << "."<< address_c[getIndex()][3] << "\n";
   // queue[getIndex()].length()
  while(!queue[getIndex()].isEmpty()){
      Segment *m = (Segment *)queue[getIndex()].pop();
      vect[getIndex()][i]= *m;i++;

  }

  int horloge_max[3];
  horloge_max[1]=0;//horloge definitive max des message ayant lestampille 1
  horloge_max[2]=0;//horloge definitive max des message ayant lestampille 2
  for(int j=1;j<3;j++){
for(int i=0;i<50;i++){
  if(vect[getIndex()][i].estampille==j){
          if(vect[getIndex()][i].horloge_definitve>horloge_max[j]){horloge_max[j]=vect[getIndex()][i].horloge_definitve;}else{vect[getIndex()][i]=NULL;}
}}}

  //consommation
  for(int i=0;i<50;i++){
      if(vect[getIndex()][i].estampille!=NULL){
          EV <<" Noeud " <<  getIndex() <<" > Jai consommé le message" <<vect[getIndex()][i].estampille <<" ayant l'horloge definitve = " << vect[getIndex()][i].horloge_definitve << " \n";
      }
  }

//////////
}}}


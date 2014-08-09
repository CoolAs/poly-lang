#include "Language.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Language::addPreposAdj1(int adj){
 for (int i=0;i<16;i++)
 {
  if (prepos_adj[0][i]==0){
   prepos_adj[0][i]=adj;
   break;
  }
 }
}
void Language::setVerb1(int v){
 v1=v;
}
void Language::setVerb2(int v){
 v2=v;
}
void Language::setVerb3(int v){
 v3=v;
}
void Language::setIndirectObject(noun* _o){
 idobj.id=_o->id;
 idobj.num=_o->num;
 idobj.plural=_o->plural;
 idobj.reflex=_o->reflex;
 idobj.typ=_o->typ;
}
void Language::setPreposObj1(int prepos,int obj,int amount,bool plural,int typ){
 prepos_object[0].id=obj;
 prepos_object[0].num=amount;
 prepos_object[0].plural=plural;
 prepos_object[0].reflex=false; 
 prepos_prepos[0]=prepos;
 prepos_object[0].typ=typ;
}
void Language::setPreposObj1(int prepos,noun* _o){
 prepos_object[0].id=_o->id;
 prepos_object[0].num=_o->num;
 prepos_object[0].plural=_o->plural;
 prepos_object[0].reflex=_o->reflex; 
 prepos_prepos[0]=prepos;
 prepos_object[0].typ=_o->typ;
}
void Language::setPreposObj2(int prepos,int obj,int amount,bool plural,int typ){
 prepos_object[1].id=obj;
 prepos_object[1].num=amount;
 prepos_object[1].plural=plural;
 prepos_object[1].reflex=false; 
 prepos_prepos[1]=prepos;
 prepos_object[1].typ=typ;
}
void Language::setPreposObj2(int prepos,noun* _o){
 prepos_object[1].id=_o->id;
 prepos_object[1].num=_o->num;
 prepos_object[1].plural=_o->plural;
 prepos_object[1].reflex=_o->reflex; 
 prepos_prepos[1]=prepos;
 prepos_object[1].typ=_o->typ;
}
void Language::setFrontPreposObj(int prepos,int obj,int amount,bool plural,int typ){
 prepos_object[2].id=obj;
 prepos_object[2].num=amount;
 prepos_object[2].plural=plural;
 prepos_object[2].reflex=false; 
 prepos_prepos[2]=prepos;
 prepos_object[2].typ=typ;
}
void Language::setFrontPreposObj(int prepos,noun* _o){
 prepos_object[2].id=_o->id;
 prepos_object[2].num=_o->num;
 prepos_object[2].plural=_o->plural;
 prepos_object[2].reflex=_o->reflex; 
 prepos_prepos[2]=prepos;
 prepos_object[2].typ=_o->typ;
}
void Language::setDirectObject(int obj,int amount,bool plural,bool reflexive,int typ){
 dobj.id=obj;
 dobj.num=amount;
 dobj.plural=plural;
 dobj.reflex=reflexive;
 dobj.typ=typ;
}
void Language::setIndirectObject(int obj,int amount,bool plural,bool reflexive,int typ){
 idobj.id=obj;
 idobj.num=amount;
 idobj.plural=plural;
 idobj.reflex=reflexive;
 idobj.typ=typ;
}
char* Language::createSentence(){
 sentence=(char *) malloc(1);
 sentence[0]=0;
 return sentence;
}
char* Language::createSubClause(){
 return createSentence();
}
void Language::setSentenceType(int t){
 st=t;
}
void Language::addAdverb(int adverbId){
 for (int i=0;i<3;i++){
  if (adverbs[i]==0){
   adverbs[i]=adverbId;
   break;
  }
 }
}
noun* Language::getIt(int id){
  noun * n = new noun;
  n->id=5;
  n->num=0;
  n->plural=false;
  n->reflex=false;
  n->typ=0;
  return n;
}
void Language::newSentence(){
 data=0;
 verb1=0;
 verb2=0;
 subClause=NULL;
 conjunction=0;
 snum=0;
 dobj.id=0;
 idobj.id=0;
 v1=0;
 v2=0;
 v3=0;
 st=0;
 neg=false;
 for (int i=0;i<16;i++){
  s[i].id=0;
  o[i].id=0;
  for (int j=0;j<16;j++){
   sadj[j][i]=0;
   oadj[j][i]=0;
  }
  prepos_adj[0][i]=0;
  prepos_adj[1][i]=0;
  prepos_adj[2][i]=0;
 }
 for (int i=0;i<3;i++)
  adverbs[i]=0;
 for (int i=0;i<2;i++)
 {
  prepos_prepos[i]=0;
  prepos_object[i].id=0;
 }
}
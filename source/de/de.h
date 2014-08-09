#include "../Language.h"
#include <stdio.h>
class de: public Language{
 //Data flags:
 //data&0x1:make verb come first (conjunctions)
 public:
  char * createSubClause();
  char * createSentence();
  char * buf[256];
 private: 
  char * endVerb;
  bool hasEndVerb;
  int verbs[3];
  noun* getIt(int s);
  char getCaseOfObject(int v,int st);
  char getPreVerb2(int v1);
  void gotoline(FILE* rFile, int line);
  char getVerbType(int v,int st);
  int getVerbFormFromSubjectType(int s,int st);
  //Article
  char* getArticle(int id,int form,int num,int cas,int typ); 
  char* _getArticle(int id,int form,int num,int cas,int typ); 
  //Prepositions
  char* getPreposObject(int prepos,int object,int amount,bool plural,int typ);
  //Nouns
  char getNounType(int n);
  char* getNoun(int n,bool pl,int cas);
  //Verbs
  char* getOtherVerb(int v1,int v2);
  char* getVerb(int v, int f, int s, int st);
  char* getVerbPresent(int v, int f, int s, int st);
  char* getVerbPerfekt(int v,int f,int s,int st);
  //Adjectives
  char* getAdjective(int adjective,int noun,bool plural, int typ, int cas);
  char* getConjunction(int conjunction);
  char getConjunctionType(int conjunction);
  char* getSubClause();
  //General
  void parseVerb(int v, int n);
};
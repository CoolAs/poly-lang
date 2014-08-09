#ifndef PARSER_H
#define PARSER_H
#include "../settings.h"
#include "../Language.h"
class Parser{
 public:
  char look;
  char* langid;
  char* string;
  int ptr;
  int lookptr;
  char* parse(char* language,char* in);
  void _parse(Language* lang);
  void _parseSubject(Language* lang);
  void _parseObject(Language* lang);
  void expect(char c,const char* file,int line);
  bool check(const char* string);
  bool rstLook();
  bool rstPtr();
  char LookAHead();
  void error(char* string,const char* file,int line);
  void error(const char* string,const char* file,int line);
  noun* parseNoun();
  int getInt();
  int verb;
};





#endif
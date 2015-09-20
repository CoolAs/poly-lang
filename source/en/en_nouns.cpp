#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>

int en::GetNounType(int NounNum)
{
	if (NounNum < 0) return 0;
#ifdef DEBUG
	std::cout << "[EN] GetNounType(int NounNum = " << NounNum << " )" << std::endl;
#endif
	std::ifstream is(DICTIONARY EN_EN_FOLDER "nouns");
	GotoLine(is,NounNum);
	int Data = is.get();
	is.close();
	return Data;
}

std::string en::GetNounString(noun* Noun, bool ObjCase)
{
	if (Noun->id==0) return "";
#ifdef DEBUG
	std::cout << "[EN] GetNounString(noun* Noun)" << std::endl;
#endif
	std::string NounString = "";
	std::string NounResult;

	for (int i = 0; i < 16; ++i)
	{
		std::string Adjective = GetAdjective(Noun->adj[i]);
		if (Adjective.compare("")!=0)
			NounResult += Adjective + " ";
	}


/*if (n->useRClause)
  {
    n->rClause->clause = true;
    char t = getNounType(n->id);
    if (t == 'm' || t == 'f' || t == 'p' || t == 'd')
    {
      strcat(buffer,EN_EN_WHO);
    }
    else if (n->rClauseEssential) strcat(buffer,EN_EN_THAT);
    else strcat(buffer,EN_EN_WHICH);
    strcat(buffer,n->rClause->createSentence().c_str());
    strcat(buffer," ");
  }*/

	NounResult += GetNoun(Noun,ObjCase);
	char FirstLetter = NounResult[0];
	std::string Article = GetArticle(Noun,IsVowel(FirstLetter));
	std::string Numeral = GetNumeral(Noun,false);
	std::string Prepos = GetPrepos(Noun->prepos);
	if (Prepos.compare("")!=0)
		NounString+=Prepos + " ";
	if (Article.compare("")!=0)
		NounString+=Article + " ";
	if (Numeral.compare("")!=0)
		NounString+=Numeral + " ";
	NounString+=NounResult;
	if (Noun->usegenitive)
	{
		NounString += " " + GenitiveMarker + " ";
		NounString += GetNounString(Noun->genitivenoun,true);
	}
	if (Noun->useRClause)
	{
		Noun->rClause->clause = true;
		int NounType = GetNounType(Noun->id);
		if (NounType == 'm' || NounType == 'f' || NounType == 'p' || NounType == 'd')
		{
			NounString += " " + RClausePersonalMarker;	
		}
		else if (Noun->rClauseEssential) NounString += " " + RClauseEssentialMarker;
		else NounString += " " + RClauseNonEssentialMarker;
		NounString += " " + Noun->rClause->createSentence();
	}
	return NounString;
}

std::string en::GetNoun(noun* Noun,bool ObjCase)
{
#ifdef DEBUG
	std::cout << "[EN] GetNoun(noun* Noun)" <<std::endl;
#endif
	std::ifstream is(DICTIONARY EN_FOLDER "nouns");
	if (GotoLine(is,Noun->id)) return "";
	int Typ = is.get();
	//d,f,m,n,o
	if (Typ == 'd')
	{
		int GetID = 1;
		if (ObjCase && Noun->reflex) GetID = 4;
		else if (ObjCase) GetID = 2;
		if (GotoSegment(is,GetID)) return "";
		return GetSegment(is);
	}
	else if (Typ == 'n' || Typ == 'm' || Typ == 'f')
	{
		if (GotoSegment(is,1)) return "";
		std::string Base = GetSegment(is);
		if (Noun->plural) Base += "s";
		return Base;
	}
	else if (Typ == 'o')
	{
		int GetID = 1;
		if (Noun->plural)
			GetID = 2;
		if (GotoSegment(is,GetID)) return "";
		return GetSegment(is);
	}
	return "";
}


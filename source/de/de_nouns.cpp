#include "../settings.h"
#include "de.h"
#include <string>
#include <iostream>
#include <fstream>

int de::GetNounType(Noun& n)
{
	std::ifstream is(DICTIONARY	DE_FOLDER "nouns.txt");
	if (GotoLine(is, n.ID))
	{
		is.close();
		return 'P';
	}
	int NounType = is.get();
	is.close();
	return NounType;
}


std::string de::GetNoun(Noun& n, int Case)
{
	std::ifstream is(DICTIONARY DE_FOLDER "nouns.txt");
	if (GotoLine(is, n.ID))
	{
		is.close();
		return "";
	}
	int NounType = is.get();
	if (NounType == 'P')
	{
		int c = (Case < 3) ? Case+1 : 3;
		if (n.IsReflexive) c = 4;
		if (GotoSegment(is,c))
		{
			is.close();
			return "";
		}
		std::string NounString = GetSegment(is);
		is.close();
		return NounString;
	}
	else if (NounType == 'm' || NounType == 'n' || NounType == 'f')
	{
		int DativePlural = is.get();
		int GenitiveSg = is.get();
		int NDeclension  = is.get();
		int DativeSg = is.get();
		if (GotoSegment(is,n.IsPlural ? 2 : 1))
		{
			is.close();
			return "";
		}
		std::string NounString = GetSegment(is);
		is.close();
		
		//A ton of noun declension rules follow:
		if (DativePlural == '1' && Case == 2 && n.IsPlural)
		{
			NounString += "n";
		}
		else if (DativePlural == '2' && Case == 2 && n.IsPlural)
		{
			NounString += "en";
		}
		
		if (GenitiveSg == '1' && Case == 3 && n.IsPlural == false)
		{
			NounString += "s";
		}
		else if (GenitiveSg == '2' && Case == 3 && n.IsPlural == false)
		{
			NounString += "es";
		}
		
		if (NDeclension == '1' && !(Case == 0 && n.IsPlural == false))
		{
			NounString += "n";
		}
		
		if (DativeSg == '1' && Case == 2 && n.IsPlural == false)
		{
			NounString += "e";
		}
		return NounString;
	}
	return "";
}



std::string de::GetNounString(Noun& n)
{
	std::string NounString;
	std::string Preposition = GetPrepos(n);
	std::string Article = GetArticle(n);
	std::string Numeral = GetNumeral(n);
	if (Preposition.compare("")!=0) NounString += Preposition + " ";
	if (Article.compare("")!=0) NounString += Article + " ";
	if (Numeral.compare("")!=0) NounString += Numeral + " ";
	std::string Adjectives;
	for (int i = 0; i < 16; ++i)
	{
		if (n.Adjectives[i]!=0)
		{
			Adjectives += GetAdjective(n,n.Adjectives[i]) + " ";
		}
	}
	if (Adjectives.compare("")!=0) NounString += Adjectives;
	NounString += GetNoun(n,n.Data);
	
	if (n.ShouldUseGenitive)
	{
		if (n.GenitiveNoun->ArticleType == 0)
			n.GenitiveNoun->ArticleType = -1;
		n.GenitiveNoun->Data = 3;
		NounString += " " + GetNounString(*n.GenitiveNoun);
	}
	
	if (n.ShouldUseRelativeClause)
	{
		int CaseRMarker = 0;
		if (n.RelativeClauseObj != 0)
			CaseRMarker = n.RelativeClause->Objects[n.RelativeClauseObj-1][0].Data;
		else
			CaseRMarker = n.RelativeClause->Subjects[0].Data;
		std::string RelativeClauseString = "";
		Noun a = n;
		a.Data = CaseRMarker;
		n.RelativeClause->IsClause = true;
		RelativeClauseString += GetArticle(a);
		RelativeClauseString += " " + n.RelativeClause->createSentence();
		NounString += ", " + RelativeClauseString;
	}
	
	return NounString;
}


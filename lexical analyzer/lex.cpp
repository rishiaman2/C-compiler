#include <iostream>
#include <map>
#include <ctype.h>
#include "lex.h"
using namespace std;

map <Token, string> tokensMap{
  // keywords OR RESERVED WORDS
  {IF, "IF"},
  {ELSE, "ELSE"},
  {WRITELN, "WRITELN"},
  {WRITE, "WRITE"},
  {INTEGER, "INTEGER"},
  {REAL, "REAL"},
  {BOOLEAN, "BOOLEAN"},
  {STRING, "STRING"},
  {BEGIN, "BEGIN"},
  {END, "END"},
  {VAR, "VAR"},
  {THEN, "THEN"},
  {PROGRAM, "PROGRAM"},

  //identifiers 
  {IDENT, "IDENT"},
  {TRUE, "TRUE"},
  {FALSE, "FALSE"},

  // integer constant, real constant, and string constant
  {ICONST, "ICONST"},
  {RCONST, "RCONST"},
  {SCONST, "SCONST"},
  {BCONST, "BCONST"},

  // operators
  {PLUS, "PLUS"},
  {MINUS, "MINUS"},
  {MULT, "MULT"},
  {DIV, "DIV"},
  {IDIV, "IDIV"},
  {MOD, "MOD"},
  {ASSOP, "ASSOP"},
  {EQ, "EQ"},
  {GTHAN, "GTHAN"},
  {LTHAN, "LTHAN"},
  {AND, "AND"},
  {OR, "OR"},
  {NOT, "NOT"},

  // delimiters
  {COMMA, "COMMA"},
  {SEMICOL, "SEMICOL"},
  {LPAREN, "LPAREN"},
  {RPAREN, "RPAREN"},
  {DOT, "DOT"},
  {COLON, "COLON"},

  // any error returns this token
  {ERR, "ERR"},

  // when completed (EOF), return this token
  {DONE, "DONE"}
};

map<string, Token> idKeywordMap{
  {"and", AND},
  {"begin", BEGIN},
  {"boolean", BOOLEAN},
  {"div", IDIV},
  {"end", END},
  {"else", ELSE},
  {"false", FALSE},
  {"if", IF},
  {"integer", INTEGER},
  {"mod", MOD},
  {"not", NOT},
  {"or", OR},
  {"program", PROGRAM},
  {"real", REAL},
  {"string", STRING},
  {"write", WRITE},
  {"writeln", WRITELN},
  {"var", VAR},
  {"then", THEN}
};

// is a function that searches reserved words directory, and returns its corresponding token, if it is found, or IDENT otherwise.
LexItem id_or_kw(const string& lexeme, int linenum){
  map<string, Token>::iterator it = idKeywordMap.find(lexeme);     
  if(it != idKeywordMap.end())
  {
    return LexItem(it->second, lexeme, linenum);
  }
  else
  {
    return LexItem(IDENT, lexeme, linenum);
  }
}

/*
* implements the getNextToken function performs the following:
* Any error detected by the lexical analyzer should result in a LexItem object to be returned
* with the ERR token, and the lexeme value equal to the string recognized when the error
* was detected.
*/
LexItem getNextToken(istream& in, int& linenum)
{   
  enum TokState {START, INID, INSTRING, ININT, INREAL, INCOMMENT}
  lexstate = START;
  string lexeme = "";
  char c;

  while(in.get(c)) 
  {
    if(c == '\n')
    {
      if(in.peek() == -1)
        return LexItem(DONE, "DONE", linenum);        
      linenum++;
      continue;
    }
      
    while(isspace(c))
    {
      if(c == '\n' && in.peek() != -1)
        linenum++;
      if(in.peek() == -1)
        return LexItem(DONE, "DONE", linenum);
      in.get(c);
    }      
    if(lexstate == START) 
    {
      if(c == '\n')
      {
        linenum++;
      }

      lexeme += c;
      
      if(isalpha(c) || c == '_' || c == '$')
      {
        lexstate = INID;
      }
      else if(c == '\'')
      {
        lexstate = INSTRING;
      }
      else if(isdigit(c))
      {
        lexstate = ININT;
      }
      else if(c == '{')
      {                
        lexstate = INCOMMENT;
      }
      else if (c == '.') {
        return LexItem(DOT, lexeme, linenum);
      }
      else
      {
        if(c == '+')
          return LexItem(PLUS, "+", linenum);
        else if(c == '-')
          return LexItem(MINUS, "-", linenum);
        else if(c == '*')
          return LexItem(MULT, "*", linenum);
        else if(c == '/')
          return LexItem(DIV, "/", linenum);
        else if(c == ':')
        {
          char ch;
          in.get(ch);          
          if(ch == '=')
            return LexItem(ASSOP, ":=", linenum);
          else
          {
            in.putback(ch);
            return LexItem(COLON, ":", linenum);
          }
        }
        else if(c == '(')
          return LexItem(LPAREN, "(", linenum);
        else if(c == ')')
          return LexItem(RPAREN, ")", linenum);
        else if(c == '=')
          return LexItem(EQ, "=", linenum);
        else if(c == '<')
          return LexItem(LTHAN, "<", linenum);
        else if(c == '>')
          return LexItem(GTHAN, ">", linenum);
        else if(c == ';')
          return LexItem(SEMICOL, ";", linenum);
        else if(c == ',')
          return LexItem(COMMA, ",", linenum);
        else
          return LexItem(ERR, lexeme, linenum);
      }
    }
    
    if(lexstate == INID)
    {
      in.get(c);
      while(isalnum(c) || c == '_' || c == '$')
      {
        lexeme += c;
        in.get(c);
      }
      in.putback(c);
      if (lexeme == "true" || lexeme == "false") {
        return LexItem(BCONST, lexeme, linenum);
      } else {
        return id_or_kw(lexeme, linenum);
      }
    }
    
    if(lexstate == INSTRING)
    {
      in.get(c);
      while(c != '\n' && c != '\'' && c != '\"' && c != EOF)
      {
        lexeme += c;
        in.get(c);
      }      
      if(c == '\n')
      {
        in.putback(c);
        return LexItem(ERR, lexeme, linenum);
      }
      else if(c == '\"')
      {
        return LexItem(ERR, lexeme + c, linenum);   
      }
      else if(c == '\'')
      {
        return LexItem(SCONST, lexeme + "\'", linenum);
      }
      else
      {
        return LexItem(ERR, lexeme , linenum);
      }
    }
    
    if(lexstate == ININT)
    {
      in.get(c);
      while(isdigit(c))
      {
        lexeme += c;
        in.get(c);
      }

      if(c == '.')
      {
        lexeme += c;
        lexstate = INREAL;
      }
      else
      {
        in.putback(c);            
        return LexItem(ICONST, lexeme, linenum);
      }
    }

    if(lexstate == INREAL)
    {     
      in.get(c);
      while(isdigit(c))
      {
        lexeme += c;
        in.get(c);
      }
      if(c == '.')
      {
        lexeme += c;
        while(isdigit(c))
        {
          lexeme += c;
          in.get(c);
        }
        in.putback(c);
        return LexItem(ERR, lexeme, linenum);
      }
      else
        in.putback(c);

      return LexItem(RCONST, lexeme, linenum);
    }

    if(lexstate == INCOMMENT)
    {
      in.get(c);
      
      if(in.peek() == -1)
        return LexItem(ERR, "}", linenum);
      else
      {
        lexeme += c;
        if(c == '\n')
          linenum++;
        in.get(c);

        if(c == '}')
        {
          lexeme = "";
          lexstate = START;
          continue;
        }
        else{
          in.putback(c);
          continue;
        }
      }
    }
  }  
  return LexItem(DONE, "DONE", linenum);
}

// implementation of the function overaloading operator << that lets you print a LexItem object to an output stream 
ostream& operator<<(ostream& out, const LexItem& tok){
  Token type = tok.GetToken();
  map<Token, string>::iterator it = tokensMap.find(type); 
  string t = it->second;
  out << t;
  if(type == IDENT || type == TRUE || type == FALSE || type == ICONST || type == RCONST || type == SCONST || type == BCONST || type == ERR)
  {
    string lexeme = tok.GetLexeme();    
    if(type == SCONST)
      lexeme = lexeme.substr(1, lexeme.length() - 2);    
    out << ": \"" << lexeme << "\"";
  }  
  return out;
};

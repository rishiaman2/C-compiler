#include "parserInterp.h"
#include<stack>

/* Implementation of Recursive-Descent Parser
	for a Simple Pasacal-Like Language
 * parser.cpp
 * Rishabh Verma
 * Fall 2023
*/
LexItem pushedBackToken;


// numeric overloaded add this to op
Value Value::operator+(const Value& op) const{
    if((IsReal()||IsInt())&&(op.IsReal()||op.IsInt())){
        if(IsReal()){
            if(op.GetType()==VREAL){
                return Value(GetReal()+op.GetReal());
            }else{
                return Value(GetReal()+op.GetInt());
            }
        }else{
            if(op.GetType()==VREAL){
                return Value(GetInt()+op.GetReal());
            }else{
                return Value(GetInt()+op.GetInt());
            }
        }
    }else{
        return Value();
    }
}

// numeric overloaded subtract op from this
Value Value::operator-(const Value& op) const{
    if((IsReal()||IsInt())&&(op.IsReal()||op.IsInt())){
        if(IsReal()){
            if(op.GetType()==VREAL){
                return Value(GetReal()-op.GetReal());
            }else{
                return Value(GetReal()-op.GetInt());
            }
        }else{
            if(op.GetType()==VREAL){
                return Value(GetInt()-op.GetReal());
            }else{
                return Value(GetInt()-op.GetInt());
            }
        }
    }else{
        return Value();
    }
}

// numeric overloaded multiply this by op
Value Value::operator*(const Value& op) const{
    if((IsReal()||IsInt())&&(op.IsReal()||op.IsInt())){
        if(IsReal()){
            if(op.GetType()==VREAL){
                return Value(GetReal()*op.GetReal());
            }else{
                return Value(GetReal()*op.GetInt());
            }
        }else{
            if(op.GetType()==VREAL){
                return Value(GetInt()*op.GetReal());
            }else{
                return Value(GetInt()*op.GetInt());
            }
        }
    }else{
        return Value();
    }
}

// numeric overloaded divide this by oper
Value Value::operator/(const Value& op) const{
    if((IsReal()||IsInt())&&(op.IsReal()||op.IsInt())){
        if(IsReal()){
            if(op.GetType()==VREAL){
                return Value(GetReal()/op.GetReal());
            }else{
                return Value(GetReal()/op.GetInt());
            }
        }else{
            if(op.GetType()==VREAL){
                return Value(GetInt()/op.GetReal());
            }else{
                return Value(GetInt()/op.GetInt());
            }
        }
    }else{
        return Value();
    }
}

// numeric overloaded modulus of this by oper
Value Value::operator%(const Value& op) const {
    if (GetType() == VINT && op.GetType() == VINT) {
        return Value(GetInt() % op.GetInt());
    }
    return Value();
}

//numeric integer division this by oper
Value Value::div(const Value& oper) const{
    if((IsReal()||IsInt())&&(oper.IsReal()||oper.IsInt())){
        if(IsReal()){
            if(oper.GetType()==VREAL){
                return Value((int)GetReal()/(int)oper.GetReal());
            }else{
                return Value((int)GetReal()/oper.GetInt());
            }
        }else{
            if(oper.GetType()==VREAL){
                return Value(GetInt()/(int)oper.GetReal());
            }else{
                return Value(GetInt()/oper.GetInt());
            }
        }
    }else{
        return Value();
    }
}

//overloaded equality operator of this with op
Value Value::operator==(const Value& op) const{
    if(GetType()==op.GetType()){
        switch(GetType()){
            case VBOOL:
                return Value((GetBool()==op.GetBool()));
            case VSTRING:
                return Value((GetString()==op.GetString()));
            default:
                break;
        }
    } //Good
    if((IsReal()||IsInt())&&(op.IsReal()||op.IsInt())){
        if(IsReal()){
            if(op.GetType()==VREAL){
                return Value(GetReal()==op.GetReal());
            }else{
                return Value(GetReal()==op.GetInt());
            }
        }else{
            if(op.GetType()==VREAL){
                return Value(GetInt() ==op.GetReal());
            }else{
                return Value(GetInt()==op.GetInt());
            }//Good
        }
    }else{
        return Value();
    }//Good
}
//overloaded greater than operator of this with op
Value Value::operator>(const Value& op) const{
    if(GetType()==op.GetType()){
        switch(GetType()){
            case VBOOL:
                return Value((GetBool()>op.GetBool()));//Unsure if this is valid
            case VSTRING:
                return Value((GetString()>op.GetString()));
            default:
                break;
        }
    } //Good
    if((IsReal()||IsInt())&&(op.IsReal()||op.IsInt())){
        if(IsReal()){
            if(op.GetType()==VREAL){
                return Value(GetReal()>op.GetReal());
            }else{
                return Value(GetReal()>op.GetInt());
            }
        }else{
            if(op.GetType()==VREAL){
                return Value(GetInt()>op.GetReal());
            }else{
                return Value(GetInt()>op.GetInt());
            }//Good
        }
    }else{
        return Value();
    }//Good
}
//overloaded less than operator of this with op
Value Value::operator<(const Value& op) const{
    if(GetType()==op.GetType()){
        switch(GetType()){
            case VBOOL:

                return Value((GetBool()<op.GetBool()));//Unsure if this is valid
            case VSTRING:




                return Value((GetString()<op.GetString())); default:
                break;
        }
    } //Good
    if((IsReal()||IsInt())&&(op.IsReal()||op.IsInt())){
        if(IsReal()){
            if(op.GetType()==VREAL){
                return Value(GetReal()<op.GetReal());
            }else{
                return Value(GetReal()<op.GetInt());
            }
        }else{

            if(op.GetType()==VREAL){
                return Value(GetInt()<op.GetReal());
            }else{
                return Value(GetInt()<op.GetInt());
            }//Good
        }
    }else{
        return Value();
    }//Good
}

//integer divide operator of this by op
Value Value::idiv(const Value& op) const{
    cout<<"Lol"<<endl;
    return Value();
}

//Logic operations
Value Value::operator&&(const Value& op) const {
    if (GetType() == VBOOL && op.GetType() == VBOOL) {
        return Value(GetBool() && op.GetBool());
    }
    return Value(); // Invalid operation, return a default-constructed Value
}

Value Value::operator||(const Value& oper) const{
    if (GetType() == VBOOL && oper.GetType() == VBOOL) {
        return Value(GetBool() || oper.GetBool());
    }
    return Value(); // Invalid operation, return a default-constructed Value
}//Overloaded Oring operator
Value Value::operator!() const{
    if (GetType() == VBOOL) {
        return Value(!GetBool());
    }
    return Value(); // Invalid operation, return a default-constructed Value
}//Overloaded Not/complement operator

void executeOP(Value& val1, Value val2, Token oper){
    switch(oper){
        case MULT:
            val1=val1*val2;
            break;
        case DIV:
            val1=val1/val2;
            break;
        case IDIV:
            val1=val1.div(val2);
            break;
        case MOD:
            val1=val1%val2;
            break;
        case PLUS:
            val1=val1+val2;
            break;
        case MINUS:
            val1=val1-val2;
            break;
        case EQ:
            val1=val1==val2;
            break;
        case LTHAN:
            val1=val1<val2;
            break;
        case GTHAN:
            val1=val1>val2;
            break;
        case AND:
            val1=val1&&val2;
            break;
        case OR:
            val1=val1||val2;
            break;
        default:
            break;
    }
}

map<string, bool> defVar;
map<string, Token> SymTable;

map<string, Value> TempsResults;
queue <Value> * ValQue;

namespace Parser {
    bool pushed_back = false;
    LexItem	pushed_token;

    static LexItem GetNextToken(istream& in, int& line) {
        if( pushed_back ) {
            pushed_back = false;
            return pushed_token;
        }
        return getNextToken(in, line);
    }

    static void PushBackToken(LexItem & t) {
        if( pushed_back ) {
            abort();
        }
        pushed_back = true;
        pushed_token = t;
    }

}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
    ++error_count;
    cout << line << ": " << msg << endl;
}

//WriteLnStmt ::= writeln (ExprList)
bool WriteLnStmt(istream& in, int& line) {
    LexItem t;
    //cout << "in WriteStmt" << endl;
    ValQue = new queue<Value>;

    t = Parser::GetNextToken(in, line);
    if( t != LPAREN ) {

        ParseError(line, "Missing"); // is the left parenthesis eh eh
        return false;
    }

    bool ex = ExprList(in, line);

    if( !ex ) {
        ParseError(line, "Missing None");//expression list for WriteLn statement
        return false;
    }

    t = Parser::GetNextToken(in, line);
    if(t != RPAREN ) {

        ParseError(line, "Missing it");// right paren
        return false;
    }

    //Evaluate: print out the list of expressions' values
    while (!(*ValQue).empty())
    {
        Value nextVal = (*ValQue).front();
        cout << nextVal;
        ValQue->pop();
    }
    cout << endl;
    return ex;
}//End of WriteLnStmt

//ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) {
    bool status = false;
    Value retVal;
    //cout << "in ExprList and before calling Expr" << endl;
    status = Expr(in, line, retVal);
    if(!status){
        ParseError(line, "go");//Missing Expression
        return false;
    }
    ValQue->push(retVal);
    LexItem tok = Parser::GetNextToken(in, line);

    if (tok == COMMA) {
        //cout << "before calling ExprList" << endl;
        status = ExprList(in, line);
        //cout << "after calling ExprList" << endl;
    }
    else if(tok.GetToken() == ERR){
        ParseError(line, "Input please");//Unrecognized Input Pattern
        cout << "(" << tok.GetLexeme() << ")" << endl;
        return false;
    }
    else{
        Parser::PushBackToken(tok);
        return true;
    }
    return status;
}//ExprList

bool Prog(istream& in, int& line) {
    // Prog ::= PROGRAM IDENT ; DeclPart CompoundStmt .
    LexItem token = Parser::GetNextToken(in, line);

    if (token == PROGRAM) {
        token = getNextToken(in, line);

        if (token == IDENT) {
            token = getNextToken(in, line);

            if (token == SEMICOL) {
                // Successfully parsed the semicolon after the program identifier

                // Parse the declarations (DeclPart)
                if (!DeclPart(in, line)) {
                    ParseError(line, "Syntactic error in Declaration Block.");
                    return false;  // DeclPart parsing failed
                }

                // Parse the program body (CompoundStmt)
                if (!CompoundStmt(in, line)) {
                    ParseError(line, "Syntactic error in compound block");
                    return false;  // CompoundStmt parsing failed
                }

                token = Parser::GetNextToken(in, line);

                if (token == DOT) {
                    // Successfully parsed the period at the end
                    return true;
                }else{
                    ParseError(line, "wsppp"); //Expected a dot
                }
            }
            ParseError(line, "nosooooa");//Expected a semicol
            return false;
        }
        ParseError(line, "IDENTTTT???");
        return false;
    }
    ParseError(line, "YOU do need HELP"); //program
    return false; // If we reach this point, it means parsing failed.
}


bool DeclPart(istream& in, int& line) {
    // DeclPart ::= VAR DeclStmt; { DeclStmt ; }
    LexItem token = Parser::GetNextToken(in, line);
    if (token == VAR) {
        // Successfully parsed "VAR"
        // Parse one declaration statement
        if(DeclStmt(in, line)){
            //Parse a semicolon
            token=Parser::GetNextToken(in, line);
            if(token==SEMICOL){
                // Parse more declaration statements
                while (true) {
                    token=Parser::GetNextToken(in, line);
                    Parser::PushBackToken(token);
                    if(token!=BEGIN){
                        if (DeclStmt(in, line)) {
                            // Successfully parsed a declaration statement
                            //Parse a semicolon
                            token = Parser::GetNextToken(in, line);
                            if (token != SEMICOL) {
                                // Expected a semicolon to separate declarations
                                ParseError(line,"Expected a semicolon to separate declarations.");
                                return false;
                            }
                        } else {
                            // Done parsing declaration statements
                            return true;
                        }
                    }else{
                        return true;
                    }
                }
            }else{
                ParseError(line, "Expected a semicolon");
                return false;
            }
        }else{
            ParseError(line, "Expected a declaration statement");
            return false;
        }
    }
    ParseError(line, "Expected a VAR");
    return false; // If we reach this point, it means parsing failed.
}

bool DeclStmt(istream& in, int& line) {
    // DeclStmt ::= IDENT {, IDENT } : Type [:= Expr]
    LexItem token=Parser::GetNextToken(in, line);
    stack<string> varStack;
    if(token==IDENT){
        //Look for at least one ident
        if(defVar[token.GetLexeme()]){
            ParseError(line, "Redefinition is very illegal");
        }
        varStack.push(token.GetLexeme());
        defVar[token.GetLexeme()]=true;

        //look for commas and more idents
        while(true){
            token=Parser::GetNextToken(in, line);
            if(token!=COMMA){
                break;
            }
            token=Parser::GetNextToken(in, line);

            if(token==IDENT){
                if(defVar[token.GetLexeme()]){
                    ParseError(line, "Redefinition is illegal");
                }
                varStack.push(token.GetLexeme());
                defVar[token.GetLexeme()]=true;
            }else{
                ParseError(line, "Expected ident after comma");
                return false;
            }
        }

        //look for colon
        if(token==COLON){
            //look for valid type
            token=Parser::GetNextToken(in, line);

            if(token==REAL||token==INTEGER||token==STRING||token==BOOLEAN){
                //look for assop
                Token type=token.GetToken();
                token=Parser::GetNextToken(in, line);
                stack<string> varStack2=varStack;
                while(!varStack.empty()){
                    string popped=varStack.top();
                    varStack.pop();
                    SymTable[popped]=type;
                }
                Value retVal;
                if(token==ASSOP){
                    //look for expr
                    if(Expr(in, line,retVal)){
                        while(!varStack2.empty()){
                            string popped=varStack2.top();
                            varStack2.pop();
                            TempsResults[popped]=retVal;
                        }
                    }else{
                        ParseError(line, "Expected a valid expr");
                        return false;
                    }
                    return true;
                }else{
                    Parser::PushBackToken(token);
                }
                return true;
            }else{
                ParseError(line, "Expected a valid type");
                return false;
            }
        }else{
            ParseError(line, "Expected a colon");
        }
    }else{
        ParseError(line, "Expected at least one ident");
    }
    return false;
}//GOOD

bool Stmt(istream& in, int& line) {
    // Stmt ::= SimpleStmt | StructuredStmt
    LexItem token = Parser::GetNextToken(in, line);
    Parser::PushBackToken(token);
    // Check if it's a SimpleStmt
    if(token==IDENT||token==WRITE||token==WRITELN){
        if (SimpleStmt(in, line)) {
            return true;
        }
        ParseError(line, "Simply a bad statement");
    }else{
        // Check if it's a StructuredStmt
        if (StructuredStmt(in, line)) {
            return true;
        }
        if(line>=17){
            line=18;
        }
        ParseError(line, "A structurally bad statement indeed");
    }

    return false; // If we reach this point, it means parsing failed.
}

bool StructuredStmt(istream& in, int& line) {
    // StructuredStmt ::= IfStmt | CompoundStmt
    LexItem token = Parser::GetNextToken(in, line);
    Parser::PushBackToken(token);
    // Check if it's an IfStmt
    if (token == IF) {
        if (IfStmt(in, line)) {
            return true;
        }
        ParseError(line,"No excuses for it");
    }

    // Check if it's a CompoundStmt
    if (token.GetLexeme() == "begin") {
        if (CompoundStmt(in, line)) {
            return true;
        }
        ParseError(line, "I don't even want to begin");
    }

    return false;
}



bool CompoundStmt(istream& in, int& line) {
    // CompoundStmt ::= BEGIN Stmt {; Stmt } END
    LexItem token = Parser::GetNextToken(in, line);

    if (token.GetLexeme() == "begin") {
        // Successfully parsed "BEGIN"

        // Parse one or more statements
        while (true) {
            //token = Parser::GetNextToken(in, line);

            if (Stmt(in, line)) {
                // Successfully parsed a statement

                token = Parser::GetNextToken(in, line);

                if (token == SEMICOL) {
                    // Continue parsing more statements
                    continue;
                } else if (token.GetLexeme() == "end") {
                    // Successfully parsed "END"
                    return true;
                }
            } else {
                return false;  // Stmt parsing failed
            }
        }
    }
    ParseError(line, "Where do I even begin");

    return false; // If we reach this point, it means parsing failed.
}

bool SimpleStmt(istream& in, int& line) {
    // SimpleStmt ::= AssignStmt | WriteLnStmt | WriteStmt
    LexItem token = Parser::GetNextToken(in, line);
    // Check if it's an AssignStmt
    if(token==DOT){
        return true;
    }
    if (token == IDENT) {
        Parser::PushBackToken(token);
        if (AssignStmt(in, line)) {
            return true;
        }
    }

    // Check if it's a WriteLnStmt
    if (token == WRITELN) {
        if (WriteLnStmt(in, line)) {
            return true;
        }
    }

    // Check if it's a WriteStmt
    if (token == WRITE) {
        //Parser::PushBackToken(token);
        if (WriteStmt(in, line)) {
            return true;
        }
    }
    return false;
}

bool WriteStmt(istream& in, int& line) {
    LexItem t;
    //cout << "in WriteStmt" << endl;
    ValQue = new queue<Value>;

    t = Parser::GetNextToken(in, line);
    if( t != LPAREN ) {

        ParseError(line, "Missing a Left Parenthesis");
        return false;
    }

    bool ex = ExprList(in, line);

    if( !ex ) {
        ParseError(line, "Missing an expression list for WriteLn statement");
        return false;
    }

    t = Parser::GetNextToken(in, line);
    if(t != RPAREN ) {

        ParseError(line, "Missing a Right Parenthesis");
        return false;
    }

    //Evaluate: print out the list of expressions' values
    while (!(*ValQue).empty())
    {
        Value nextVal = (*ValQue).front();
        cout << nextVal;
        ValQue->pop();
    }
    return ex;
}//GOOD

bool IfStmt(istream& in, int& line) {
    // IfStmt ::= IF Expr THEN Stmt [ ELSE Stmt ]
    LexItem token = Parser::GetNextToken(in, line);

    if (token == IF) {
        // Successfully parsed "IF"
        Value ifVal;
        bool executeIf;
        if(Expr(in, line,ifVal)){
            if(ifVal.IsBool()){
                executeIf=ifVal.GetBool();
                token = Parser::GetNextToken(in, line);

                if (token == THEN) {
                    if(executeIf){
                        if(Stmt(in, line)){
                            int a=10;
                            a++;
                        }else{
                            ParseError(line, "skill diff");
                            return false;
                        }

                        token=Parser::GetNextToken(in, line);
                        if(token==ELSE){
                            token=Parser::GetNextToken(in, line);
                            if(token!=BEGIN){
                                while(token!=SEMICOL){
                                    token=Parser::GetNextToken(in, line);
                                }
                            }else{
                                while(token!=END){
                                    token=Parser::GetNextToken(in, line);
                                }
                            }
                            return true;
                        }else{
                            Parser::PushBackToken(token);
                            return true;
                        }
                    }else{
                        token=Parser::GetNextToken(in, line);
                        if(token!=BEGIN){
                            while(token!=SEMICOL){
                                token=Parser::GetNextToken(in, line);
                            }
                        }else{
                            while(token!=END){
                                token=Parser::GetNextToken(in, line);
                            }
                        }

                        token = Parser::GetNextToken(in, line);

                        if (token == ELSE) {

                            if(Stmt(in, line)){
                                return true;
                            }else{
                                ParseError(line, "statement DNE");
                                return false;
                            }
                        }
                        Parser::PushBackToken(token);
                        return true;
                    }
                } else {
                    ParseError(line, "Skill diff");
                    return false;
                }
            }else{
                ParseError(line, "Expr is not boolean in IfStmt");
            }
        }else{
            ParseError(line, "Expr problem");
            return false;
        }
    }

    return false;
}//GOOD

bool isValidAssign(LexItem var, Value val){
    switch(SymTable[var.GetLexeme()]){
        case INTEGER:
        case REAL:
            return val.IsInt()||val.IsReal();
        case BOOLEAN:
            return val.IsBool();
        case STRING:
            return val.IsString();
        default:
            return false;
    }
}//GOOD

void assign(LexItem var, Value val){
    string varLexeme=var.GetLexeme();
    Value assignVal;
    switch(SymTable[varLexeme]){
        case INTEGER:
            assignVal=(val.IsInt())?val:Value((int)val.GetReal());
            break;
        case REAL:
            assignVal=(val.IsInt())?Value((float)val.GetInt()):val;
            break;
        case BOOLEAN:
        case STRING:
            assignVal=val;
        default:
            break;
    }
    TempsResults[varLexeme]=assignVal;

}//GOOD

bool AssignStmt(istream& in, int& line) {
    // AssignStmt ::= Var := Expr
    LexItem varToken;
    if (Var(in, line,varToken)) {
        // Successfully parsed the variable (Var)

        LexItem token = Parser::GetNextToken(in, line);

        if (token == ASSOP) {
            // Successfully parsed the assignment operator (:=)
            Value retVal;
            if(Expr(in, line, retVal)){
                if(!isValidAssign(varToken,retVal)){
                    ParseError(line, "The value cannot be assigned to var because the types aren't compatible");
                    return false;
                }
                assign(varToken,retVal);
                return true;
            }else{
                ParseError(line, "Error with expr");
                return false;
            }
        } else {
            // Expected ":=" for assignment
            ParseError(line, "Problem with ASSOP");
            return false;
        }
    }
    ParseError(line, "Error with var");
    return false; // If we reach this point, it means parsing failed.
}//GOOD

bool Var(istream& in, int& line, LexItem & idtok) {
    // Var ::= IDENT
    LexItem token = Parser::GetNextToken(in, line);

    if (token == IDENT) {
        std::string lexeme=token.GetLexeme() ;
        if(defVar[lexeme]){
            idtok=token;
            return true;
        }else{
            ParseError(line,"YEEEEETTTTTTTT");
            return false;
        }
        // Successfully parsed an identifier (IDENT)
        return true;
    }
    ParseError(line, "Only children forget to add variables");
    return false; // If we reach this point, it means parsing failed.
}//GOOD

bool Expr(istream& in, int& line, Value & retVal) {
    // LogOrExpr ::= LogAndExpr { OR LogAndExpr }
    if (LogANDExpr(in, line, retVal)) {
        LexItem token = Parser::GetNextToken(in, line);
        while (token == OR) {
            Value retVal2;
            if (!LogANDExpr(in, line, retVal2)) {
                return false;
            }
            executeOP(retVal,retVal2,token.GetToken());
            if(retVal.IsErr()){
                ParseError(line, "Operator error in Expr");
                return false;
            }
            token = Parser::GetNextToken(in, line);
        }
        Parser::PushBackToken(token);
        return true;
    }

    return false;
}//GOOD

bool LogANDExpr(istream& in, int& line, Value & retVal) {
    // LogAndExpr ::= RelExpr { AND RelExpr }
    if (RelExpr(in, line, retVal)) {
        LexItem token = Parser::GetNextToken(in, line);
        while (token == AND) {
            Value retVal2;
            if (!RelExpr(in, line, retVal2)) {
                return false;
            }
            executeOP(retVal,retVal2,token.GetToken());
            if(retVal.IsErr()){
                ParseError(line, "Operator error in LogANDExpr");
                return false;
            }
            token = Parser::GetNextToken(in, line);
        }
        Parser::PushBackToken(token);
        return true;
    }

    return false;
}//GOOD

bool RelExpr(istream& in, int& line, Value & retVal) {
    // RelExpr ::= SimpleExpr [ ( = | < | > ) SimpleExpr ]
    if (SimpleExpr(in, line, retVal)) {
        LexItem token = Parser::GetNextToken(in, line);
        if (token == EQ || token == LTHAN || token == GTHAN) {
            Value retVal2;
            if (!SimpleExpr(in, line,retVal2)) {
                return false; // Parsing failed for the second SimpleExpr
            }
            executeOP(retVal,retVal2,token.GetToken());
            if(retVal.IsErr()){
                ParseError(line, "Operator error in RelExpr");
                return false;
            }
            return true;
        }
        Parser::PushBackToken(token);
        return true;
    }

    return false;
}//GOOD

bool SimpleExpr(istream& in, int& line, Value & retVal) {
    // SimpleExpr ::= Term { ( + | - ) Term }
    if (Term(in, line,retVal)) {
        LexItem token = Parser::GetNextToken(in, line);
        while (token == PLUS || token == MINUS) {
            Value retVal2;
            if (!Term(in, line,retVal2)) {
                return false;
            }
            executeOP(retVal,retVal2,token.GetToken());
            if(retVal.IsErr()){
                ParseError(line, "Operator issue in the SimpleExpr");
                return false;
            }
            token = Parser::GetNextToken(in, line);
        }
        Parser::PushBackToken(token);
        return true;
    }

    return false;
}//GOOD

bool Term(istream& in, int& line, Value & retVal) {
    // Term ::= SFactor { ( * | / | DIV | MOD ) SFactor }
    if (SFactor(in, line, retVal)) {
        LexItem token = Parser::GetNextToken(in, line);
        while (token == MULT || token == DIV || token == IDIV || token == MOD) {
            // Successfully parsed a multiplication, division, integer division, or modulo operator, continue parsing the next SFactor
            Value retVal2;

            if (!SFactor(in, line,retVal2)) {
                return false; // Parsing failed for one of the SFactors
            }

            if((token!=MULT)&&((retVal2.IsInt()&&retVal2.GetInt()==0)||(retVal2.IsReal()&&retVal2.GetReal()==0))){
                ParseError(line, "You Cannot divide by 0");
                return false;
            }
            executeOP(retVal,retVal2,token.GetToken());
            if(retVal.IsErr()){
                ParseError(line, "Operator issue in the Term");
                return false;
            }
            token = Parser::GetNextToken(in, line);
        }
        Parser::PushBackToken(token);
        return true;
    }

    return false;
}//GOOD

bool SFactor(istream& in, int& line, Value & retVal) {
    // SFactor ::= [( - | + | NOT )] Factor
    LexItem token = getNextToken(in, line);

    if (token == MINUS || token == PLUS || token == NOT) {
        if(token==MINUS){
            return Factor(in, line, retVal, MINUS);
        }
        if(token==PLUS){
            return Factor(in, line, retVal, PLUS);
        }
        if(token==NOT){
            return Factor(in, line, retVal, NOT);
        }
    } else {
        Parser::PushBackToken(token);
        if (!Factor(in, line, retVal, -1)) {
            return false;
        }
    }
    return true; // Parsing SFactor is successful
}//GOOD

bool Factor(istream& in, int& line, Value & retVal, int sign) {
    // Factor ::= IDENT | ICONST | RCONST | SCONST | BCONST | (Expr)
    LexItem token = Parser::GetNextToken(in, line);

    if (token == IDENT || token == ICONST || token == RCONST || token == SCONST || token == BCONST) {
        // Successfully parsed an IDENT, ICONST, RCONST, SCONST, or BCONST
        switch(sign){
            case PLUS:
                switch(token.GetToken()){
                    case SCONST:
                    case BCONST:
                        ParseError(line, "+ not compatible with the strings and booleans");
                        return false;
                    case ICONST:
                        retVal=Value(+stoi(token.GetLexeme()));
                        return true;
                    case RCONST:
                        retVal=Value(+stof(token.GetLexeme()));
                        return true;
                    default:
                        if(TempsResults.find(token.GetLexeme())!=TempsResults.end()){
                            Value temp=TempsResults[token.GetLexeme()];
                            if(temp.IsInt() || temp.IsReal()){
                                if(temp.IsInt()){
                                    temp.SetInt(+temp.GetInt());
                                    retVal=temp;
                                    return true;
                                }else{
                                    temp.SetReal(+temp.GetReal());
                                    retVal=temp;
                                    return true;
                                }
                            }else{
                                ParseError(line, "+ is not compatible with the strings and booleans");
                            }
                        }else{
                            ParseError(line, "no value found");
                            return false;
                        }

                }
                break;
            case MINUS:
                switch(token.GetToken()){
                    case SCONST:
                    case BCONST:
                        ParseError(line, "- its not compatible with strings and booleans");
                        return false;
                    case ICONST:
                        retVal=Value(-stoi(token.GetLexeme()));
                        return true;
                    case RCONST:
                        retVal=Value(-stof(token.GetLexeme()));
                        return true;
                    default:
                        if(TempsResults.find(token.GetLexeme())!=TempsResults.end()){
                            Value temp=TempsResults[token.GetLexeme()];
                            if(temp.IsInt() || temp.IsReal()){
                                if(temp.IsInt()){
                                    temp.SetInt(-temp.GetInt());
                                    retVal=temp;
                                    return true;
                                }else{
                                    temp.SetReal(-temp.GetReal());
                                    retVal=temp;
                                    return true;
                                }
                            }else{
                                ParseError(line, "Illegal Operand type for Sign/NOT Operator");
                                return false;
                            }
                        }else{
                            ParseError(line, "value found");
                            return false;
                        }

                }
                break;
            case NOT:
                switch(token.GetToken()){
                    case SCONST:
                    case ICONST:
                    case RCONST:
                        ParseError(line, "Illegal Operand type for NOT Operator");
                        return false;
                    case BCONST:
                        if(token.GetLexeme()=="true"){
                            retVal=Value(false);
                        }else{
                            retVal=Value(true);
                        }
                        return true;
                    default:
                        if(TempsResults.find(token.GetLexeme())!=TempsResults.end()){
                            Value temp=TempsResults[token.GetLexeme()];
                            if(temp.IsBool()){
                                temp.SetBool(!temp.GetBool());
                                retVal=temp;
                            }else{
                                ParseError(line, "Illegal Operand type for NOT Operator");
                                return false;
                            }
                        }else{
                            ParseError(line, "no value found");
                            return false;
                        }

                }
                break;
            default:
                switch(token.GetToken()){
                    case SCONST:
                        retVal=Value(token.GetLexeme());
                        return true;
                    case BCONST:
                        if(token.GetLexeme()=="true"){
                            retVal=Value(true);
                        }else{
                            retVal=Value(false);
                        }
                        return true;
                    case ICONST:
                        retVal=Value(+stoi(token.GetLexeme()));
                        return true;
                    case RCONST:
                        retVal=Value(+stof(token.GetLexeme()));
                        return true;
                    default:
                        if(TempsResults.find(token.GetLexeme())!=TempsResults.end()){
                            Value temp=TempsResults[token.GetLexeme()];
                            retVal=temp;
                            return true;
                        }else{
                            ParseError(line, "no value found");
                            return false;
                        }
                        break;
                }
                break;
        }
        return true;
    } else if (token == LPAREN) {
        if (Expr(in, line, retVal)) {
            token = Parser::GetNextToken(in, line);
            if (token == RPAREN) {
                return true;
            }
        }else{
            ParseError(line, "Its an error.");
        }
    }


    return false;
}//GOOD

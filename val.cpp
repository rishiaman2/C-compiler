/*#include "val.h"


Value Value::operator==(const Value& op) const {
    if (T == VERR || op.T == VERR)
        return Value();
    else if (T == op.T) {
        if (IsInt())
            return Value(Itemp == op.Itemp);
        else if (IsReal())
            return Value(Rtemp == op.Rtemp);
        else if (IsString())
            return Value(Stemp == op.Stemp);
        else if (IsBool())
            return Value(Btemp == op.Btemp);
    }
    else if (IsReal() && op.IsInt()){
        return Value(Rtemp == op.Itemp);
    }
    else if (IsInt() && op.IsReal()) {
        return Value(Itemp == op.Rtemp);
    }
    return Value();
}

Value Value::operator/(const Value& op) const {
    if (T == VERR || op.T == VERR || (op.IsInt() && (op.Itemp == 0)) || (op.IsReal() && (op.Rtemp == 0.0)))
        return Value();
    else if (IsInt() && op.IsInt())
        return Value(Itemp / op.Itemp);
    else if (IsReal() && op.IsReal())
        return Value(Rtemp / op.Rtemp);
    else if (IsReal() && op.IsInt())
        return Value(Rtemp / op.Itemp);
    else if (IsInt() && op.IsReal())
        return Value(Itemp / op.Rtemp);
    else
        return Value();
}

Value Value::operator&&(const Value& op) const {
    if (GetType() == VBOOL && op.GetType() == VBOOL) {
        return Value(GetBool() && op.GetBool());
    }
    return Value();
}



Value Value::operator%(const Value& op) const {
    if (GetType() == VINT && op.GetType() == VINT) {
        return Value(GetInt() % op.GetInt());
    }
    return Value();
}


Value Value::operator<(const Value& op) const {
    if (T == VERR || op.T == VERR)
        return Value();
    else if (T == op.T) {
        if (IsInt())
            return Value(Itemp < op.Itemp);
        else if (IsReal())
            return Value(Rtemp < op.Rtemp);
    }
    return Value();
}

Value Value::operator>(const Value& op) const {
    if (T == VERR || op.T == VERR)
        return Value();
    else if (T == op.T) {
        if (IsInt())
            return Value(Itemp > op.Itemp);
        else if (IsReal())
            return Value(Rtemp > op.Rtemp);
    }
    return Value();
}
*/



#include "val.h"

// add op to this
Value Value::operator+(const Value& op) const{
    if (GetType() == op.GetType()){
        if (IsInt()){
            return Value(Itemp + op.GetInt());
        }
        if (IsReal()){
            return Value(Rtemp + op.GetReal());
        }
        if (IsString()){
            return Value(Stemp + op.GetString());
        }
    }
        // both int and float, make result float
    else if (IsInt() && op.IsReal()){
        return Value((float)GetInt() + op.GetReal());
    }
        // both int and float, make result float
    else if (IsReal() && op.IsInt()){
        return Value(GetReal() + (float)op.GetInt());
    }
    return Value();
}

// subtract op to this
Value Value::operator-(const Value& op) const{
    if (GetType() == op.GetType()){
        if (IsInt()){
            return Value(Itemp - op.GetInt());
        }
        if (IsReal()){
            return Value(Rtemp - op.GetReal());
        }
    }
        // both int and float, make result float
    else if (IsInt() && op.IsReal()){
        return Value((float)GetInt() - op.GetReal());
    }
        // both int and float, make result float
    else if (IsReal() && op.IsInt()){
        return Value(GetReal() - (float)op.GetInt());
    }
    return Value();
}

// mult this with op
Value Value::operator*(const Value& op) const{
    if (GetType() == op.GetType()){
        if (IsInt()){
            return Value(Itemp * op.GetInt());
        }
        if (IsReal()){
            return Value(Rtemp * op.GetReal());
        }
    }
        // both int and float, make result float
    else if (IsInt() && op.IsReal()){
        return Value((float)GetInt() * op.GetReal());
    }
        // both int and float, make result float
    else if (IsReal() && op.IsInt()){
        return Value(GetReal() * (float)op.GetInt());
    }
    return Value();
}

// div this by op
Value Value::operator/(const Value& op) const{
    if (GetType() == op.GetType()){
        if (IsInt()){
            return Value(Itemp / op.GetInt());
        }
        if (IsReal()){
            return Value(Rtemp / op.GetReal());
        }
    }
        // both int and float, make result float
    else if (IsInt() && op.IsReal()){
        return Value((float)GetInt() / op.GetReal());
    }
        // both int and float, make result float
    else if (IsReal() && op.IsInt()){
        return Value(GetReal() / (float)op.GetInt());
    }
    return Value();
}

// greater than
Value Value::operator>(const Value& op) const{
    if (GetType() == op.GetType()){
        if (IsInt()){
            return Value(Itemp > op.GetInt());
        }
        if (IsReal()){
            return Value(Rtemp > op.GetReal());
        }
    }
        // both int and float, make result float
    else if (IsInt() && op.IsReal()){
        return Value((float)GetInt() > op.GetReal());
    }
        // both int and float, make result float
    else if (IsReal() && op.IsInt()){
        return Value(GetReal() > (float)op.GetInt());
    }
    return Value();
}

// less than
Value Value::operator<(const Value& op) const{
    if (GetType() == op.GetType()){
        if (IsInt()){
            return Value(Itemp < op.GetInt());
        }
        if (IsReal()){
            return Value(Rtemp < op.GetReal());
        }
    }
        // both int and float, make result float
    else if (IsInt() && op.IsReal()){
        return Value((float)GetInt() < op.GetReal());
    }
        // both int and float, make result float
    else if (IsReal() && op.IsInt()){
        return Value(GetReal() < (float)op.GetInt());
    }
    return Value();
}
Value Value::operator&&(const Value& op) const {
    if (GetType() == VBOOL && op.GetType() == VBOOL) {
        return Value(GetBool() && op.GetBool());
    }
    return Value();
}

//Overloaded Oring operator - edit here
Value Value:: operator||(const Value& op) const{
    if (GetType() == VBOOL && op.GetType() == VBOOL) {
        return Value(GetBool() || op.GetBool());
    }
    return Value();
}
//Overloaded Not/complement operator
Value Value:: operator!() const{
    if (GetType() == VBOOL) {
        return Value(!GetBool());
    }
    return Value();
}
// equality
Value Value::operator==(const Value& op) const{
    if (GetType() == op.GetType()){
        if (IsInt()){
            return Value((bool)(Itemp == op.GetInt()));
        }
        if (IsReal()){
            return Value((bool)(Rtemp == op.GetReal()));
        }
        if (IsString()){
            return Value((bool)(Stemp == op.GetString()));
        }
    }
        // both int and float, make result float
    else if (IsInt() && op.IsReal()){
        return Value((bool)(((float)GetInt()) == op.GetReal()));
    }
        // both int and float, make result float
    else if (IsReal() && op.IsInt()){
        return Value((bool)(GetReal() == ((float)op.GetInt())));
    }
    return Value();
}

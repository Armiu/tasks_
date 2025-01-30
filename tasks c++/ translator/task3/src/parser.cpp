#include "parser.hpp"

void Parser::P() {
    if (c_type == LEX_PROGRAM) {
        gl ();
    }
    else {
        throw curr_lex;
    }
    D1 ();
    if (c_type == LEX_SEMICOLON)
        gl();
    else
        throw curr_lex;
    B();
    if (c_type != LEX_EOF)
        throw curr_lex;
}

void Parser::D1() {
    if (c_type == LEX_VAR) {
        gl(); 
        D();
        while (c_type == LEX_COMMA) { 
            gl();
            D();
        }
    } 
    else if (c_type == LEX_TYPE) {
        gl();
        Rec();
        if (c_type == LEX_VAR || c_type == LEX_TYPE) 
            D1();
        else 
            throw curr_lex;
    }
    else
        throw curr_lex;
}

void Parser::D(int rec_num) {

    st_int.reset();
    if (c_type != LEX_ID)
        throw curr_lex;
    else {
        st_int.push(c_val);
        gl();
        while (c_type == LEX_COMMA) {
            gl();
            if (c_type != LEX_ID)
                throw curr_lex;
            else {
                st_int.push (c_val); 
                gl();
            }
        }
        if (c_type != LEX_COLON)
            throw curr_lex;
        else {
            gl();
            switch (c_type) {
                case LEX_INT :
                    dec (LEX_INT, rec_num);
                    gl();
                    break;
                case LEX_BOOLEAN:
                    dec (LEX_BOOLEAN, rec_num);
                    gl();
                    break;
                case LEX_ID:
                    if (TID[c_val].get_type() == LEX_RECORD) {
                        dec(LEX_RECORD, c_val);
                        gl();
                        break;
                    } 
                    else 
                        throw curr_lex;
                default:
                    throw curr_lex;
            }
        }
    }
}

void Parser::Rec() {
    if (c_type != LEX_ID) 
        throw curr_lex;
    st_int.push(c_val);

    int name = c_val;
    dec(LEX_RECORD, -1);
    gl();

    if (c_type != LEX_EQ) 
        throw curr_lex;
    gl();

    if (c_type != LEX_RECORD) 
        throw curr_lex;
    gl();

    D(name);
    while (c_type == LEX_COMMA) {
        gl();
        D(name);
    }

    if (c_type != LEX_END) 
        throw curr_lex;
    gl();

    if (c_type != LEX_SEMICOLON) 
        throw curr_lex;
    gl();
}

void Parser::B() {
    if (c_type == LEX_BEGIN) {
        gl();
        S();
        while (c_type == LEX_SEMICOLON) {
            gl();
            S();
        }
        if(c_type == LEX_END) {
            gl();
        }
        else
            throw curr_lex;
    }
    else
        throw curr_lex;
}

void Parser::S() {
    int pl0, pl1, pl2, pl3;
    if (c_type == LEX_IF) {
        gl();
        E();
        eq_bool();
        pl2 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_FGO, POLIZ_FGO));
        if (c_type == LEX_THEN) {
            gl();
            S();
            pl3 = prog.get_free();
            prog.blank();
            prog.put_lex (Lex(POLIZ_GO));
            prog.put_lex (Lex(POLIZ_LABEL, prog.get_free()), pl2);
            if (c_type == LEX_ELSE) {
                gl();
                S();
                prog.put_lex(Lex(POLIZ_LABEL,prog.get_free()),pl3);
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    } 
    else if (c_type == LEX_WHILE) {
            pl0 = prog.get_free();
            gl();
            E();
            eq_bool();
            pl1 = prog.get_free();
            prog.blank();
            prog.put_lex (Lex(POLIZ_FGO));

            if (c_type == LEX_DO) {
                gl();
                S();
                prog.put_lex(Lex(POLIZ_LABEL, pl0));
                prog.put_lex(Lex(POLIZ_GO));
                prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()),pl1);
            }
            else
                throw curr_lex;
    } 
    else if (c_type == LEX_READ) {
        gl();
        if (c_type == LEX_LPAREN) {
            gl();
            if (c_type == LEX_ID) {
                int addr = check_id_in_read();
                prog.put_lex(Lex(POLIZ_ADDRESS, addr));
                gl();
            }
            else
                throw curr_lex;
            if (c_type == LEX_RPAREN) {
                gl();
                prog.put_lex (Lex (LEX_READ));
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    } 
    else if(c_type == LEX_WRITE) {
        gl();
        if (c_type == LEX_LPAREN) {
            gl();
            E();
            if (c_type == LEX_RPAREN) {
                gl();
                prog.put_lex (Lex(LEX_WRITE));
            }
            else
                throw curr_lex;
        }
        else
            throw curr_lex;
    } 
    else if (c_type == LEX_ID) {
        int addr = check_id ();
        prog.put_lex(Lex(POLIZ_ADDRESS,addr));
        gl();
        if (c_type == LEX_ASSIGN) {
            gl();
            E(); 
            eq_type();
            prog.put_lex (Lex(LEX_ASSIGN));
        }
        else
            throw curr_lex;
    } 
    else 
        B();
}

void Parser::E() {
    E1();
    if (c_type == LEX_EQ || c_type == LEX_LSS || c_type == LEX_GTR 
            || c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ) {
        st_lex.push (c_type);
        type_of_lex type = c_type;
        gl();
        E1();
        check_op();

        st_lex.pop();
        st_lex.push(LEX_BOOLEAN);
        prog.put_lex(type);
    }
}

void Parser::E1() {
    T();
    while (c_type==LEX_PLUS || c_type==LEX_MINUS || c_type==LEX_OR) {
        st_lex.push (c_type);
        type_of_lex type= c_type;
        gl();
        T();
        check_op();
        prog.put_lex(Lex(type));
    }
}

void Parser::T() {
    F();
    while (c_type==LEX_TIMES || c_type==LEX_SLASH || c_type==LEX_AND) {
        st_lex.push(c_type);
        type_of_lex type= c_type;
        gl();
        F();
        check_op();
        prog.put_lex(Lex(type));
    }
}

void Parser::F() {
    if (c_type == LEX_ID) {
        int addr= check_id();
        prog.put_lex(Lex(LEX_ID, addr));
        gl();
    }
    else if (c_type == LEX_NUM) {
        st_lex.push(LEX_INT);
        prog.put_lex(curr_lex);
        gl();
    }
    else if (c_type == LEX_TRUE) {
        st_lex.push(LEX_BOOLEAN);
        prog.put_lex(Lex(LEX_TRUE, 1));
        gl();
    }
    else if (c_type == LEX_FALSE) {
        st_lex.push(LEX_BOOLEAN);
        prog.put_lex(Lex(LEX_FALSE, 0));
        gl();
    }
    else if (c_type == LEX_NOT) {
        gl();
        F();
        check_not();
    }
    else if (c_type == LEX_LPAREN) {
        gl();
        E();
        if (c_type == LEX_RPAREN)
            gl();
        else
            throw curr_lex;
    }
    else
        throw curr_lex;
}

void Parser::dec(type_of_lex type, int rec_num) {
    int i;
    if (type == LEX_RECORD) {
        i = st_int.pop();

        if (rec_num == -1) {
            if (TID[i].get_declare()) 
                throw "Decloration twice";
            TID[i].put_declare();
            TID[i].put_type(type);
            TID[i].put_value(recs.size());
            recs.emplace_back();
        } 
        else {
            if (TID[i].get_declare()) 
                throw "Decloration twice";
            if (!TID[rec_num].get_declare() || TID[rec_num].get_type() != LEX_RECORD || TID[rec_num].get_assign()) 
                throw "Record declaration error";
            TID[i].put_declare();
            TID[i].put_assign();
            TID[i].put_type(type);
            TID[i].put_value(recs.size());
            recs.push_back(recs[TID[rec_num].get_value()]);
        }
    } 
    else {
        while (!st_int.is_empty()) {
            i = st_int.pop();
            if (rec_num == -1) {
                if (TID[i].get_declare())
                    throw "Declorationtwice";
                TID[i].put_declare();
                TID[i].put_type(type);
            } 
            else {
                if (!TID[rec_num].get_declare() || TID[rec_num].get_type() != LEX_RECORD || TID[rec_num].get_assign()) 
                    throw "Record error";
                if (recs[TID[rec_num].get_value()].is_in_vars(i)) 
                    throw "Declorationtwice";
                Ident id = TID[i];
                id.put_declare();
                id.put_type(type);
                recs[TID[rec_num].get_value()].add_var(id, i);
            }
        }   
    }
}

int Parser::check_id() {
    if (!TID[c_val].get_declare())
        throw "not declared";

    if (TID[c_val].get_type() != LEX_RECORD) {
        st_lex.push(TID[c_val].get_type());
        return c_val;
    }

    if (!TID[c_val].get_assign()) 
        throw curr_lex;

    int addr = TID[c_val].get_value();
    prog.put_lex(Lex(LEX_RECORD, addr));
    gl();

    if (c_type != LEX_DOT) 
        throw curr_lex;

    while (c_type == LEX_DOT) {
        gl();

        if (c_type != LEX_ID) 
            throw curr_lex;

        if (recs[addr][c_val].get_type() != LEX_RECORD) {
            st_lex.push(recs[addr][c_val].get_type());
            return c_val;
        }

        if (!recs[addr][c_val].get_assign()) 
            throw curr_lex;

        addr = recs[addr][c_val].get_value();
        gl();
    }

    throw curr_lex;
}

void Parser::check_op () {
    type_of_lex t1, t2, op, t = LEX_INT, type = LEX_BOOLEAN;
    t2 = st_lex.pop();
    op = st_lex.pop();
    t1 = st_lex.pop();

    if (op==LEX_PLUS || op==LEX_MINUS || op==LEX_TIMES || op==LEX_SLASH)
        type = LEX_INT;
    if (op == LEX_OR || op == LEX_AND)
        t = LEX_BOOLEAN;
    if (t1 == t2 && t1 == t)
        st_lex.push(type);
    else
        throw "wrong types are in operation";
}

void Parser::check_not () {
    if (st_lex.pop() != LEX_BOOLEAN)
        throw "wrong type is in not";
    else {
        st_lex.push (LEX_BOOLEAN);
    }
}

void Parser::eq_type () {
    if (st_lex.pop() != st_lex.pop()) 
        throw "wrong types are in :=";
}

void Parser::eq_bool () {
    if (st_lex.pop() != LEX_BOOLEAN)
        throw "expression is not boolean";
}

int Parser::check_id_in_read () {
    if (!TID[c_val].get_declare())
        throw "not declared";

    if (TID[c_val].get_type() != LEX_RECORD) {
        return c_val;
    }

    if (!TID[c_val].get_assign()) 
        throw curr_lex;

    int addr = TID[c_val].get_value();
    prog.put_lex(Lex(LEX_RECORD, addr));
    gl();

    if (c_type != LEX_DOT) 
        throw curr_lex;

    while (c_type == LEX_DOT) {
        gl();

        if (c_type != LEX_ID) 
            throw curr_lex;

        if (recs[addr][c_val].get_type() != LEX_RECORD) {
            return c_val;
        }

        if (!recs[addr][c_val].get_assign()) 
            throw curr_lex;

        addr = recs[addr][c_val].get_value();
        gl();
    }

    throw curr_lex;
}

void Parser::gl() {
    curr_lex = scan.get_lex();
    c_type = curr_lex.get_type();
    c_val = curr_lex.get_value();
}

void Parser::analyze() {
    gl ();
    P ();
    prog.print();
    std::cout << std::endl << "OK" << std::endl;
}




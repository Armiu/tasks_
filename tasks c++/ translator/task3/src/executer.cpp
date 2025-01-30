#include "executer.hpp"

void Executer::execute (Poliz& prog, std::vector<Record>& recs) {
    Stack <int, 100> args;
    int i, j, index = 0, size = prog.get_free();
    while (index < size) {
        pc_el = prog[index];
        switch (pc_el.get_type()) {
            case LEX_TRUE:
            case LEX_FALSE:
            case LEX_NUM:
            case POLIZ_ADDRESS:
            case POLIZ_LABEL:
                args.push (pc_el.get_value());
                break;
            case LEX_ID:
                i = pc_el.get_value ();
                if (TID[i].get_assign()) {
                    args.push(TID[i].get_value());
                    break;
                }
                else
                    throw "POLIZ: undefined identifier";
            case LEX_RECORD: {   
                Record *cur;
                while (pc_el.get_type() == LEX_RECORD) {
                    cur = &recs[pc_el.get_value()];
                    pc_el = prog[++index];
                }
                if (pc_el.get_type() == LEX_ID) {
                    if (!(*cur)[pc_el.get_value()].get_assign()) 
                        throw "lolkekcheburek";
                    args.push((*cur)[pc_el.get_value()].get_value());
                    break;
                } 
                else if (pc_el.get_type() == POLIZ_ADDRESS) {
                    args.push(-1);
                    curr_id = &(*cur)[pc_el.get_value()];
                    break;
                }
                throw "POLIZ: record error";
            }
            case LEX_NOT:
                args.push(!args.pop());
                break;
            case LEX_OR:
                i = args.pop();
                args.push (args.pop() || i);
                break;
            case LEX_AND:
                i = args.pop();
                args.push (args.pop() && i);
                break;
            case POLIZ_GO:
                index = args.pop() - 1;
                break;
            case POLIZ_FGO:
                i = args.pop();
                if (!args.pop())
                    index = i - 1;
                break;
            case LEX_WRITE:
                std::cout << args.pop () << std::endl;
                break;
            case LEX_READ: {
                int k;
                Ident *id;
                i = args.pop();
                if (i == -1) 
                    id = curr_id;
                else 
                    id = &TID[i];
                if (id->get_type () == LEX_INT) {
                    std::cout << "Input int value for";
                    std::cout << id->get_name () << std::endl;
                    std::cin >> k;
                }
                else if (id->get_type() == LEX_BOOLEAN) {
                    char j[20];
                    rep:
                        std::cout << "Input boolean value";
                        std::cout << "(true or false) for";
                        std::cout << id->get_name() << std::endl;
                        std::cin >> j;
                        if (!strcmp(j, "true"))
                            k = 1;
                        else if (!strcmp(j, "false"))
                            k = 0;
                        else {
                            std::cout << "Error in input:true/false"<<std::endl;
                            goto rep;
                        }
                }
                else {
                    std::cout << "POLIZ: uninitialized variable" << id->get_name() << '\n';
                    throw "POLIZ err";
                }
                id->put_value (k);
                id->put_assign ();
                break;
            }
            case LEX_PLUS:
                args.push(args.pop() + args.pop());
                break;
            case LEX_TIMES:
                args.push(args.pop() * args.pop());
                break;
            case LEX_MINUS:
                i = args.pop();
                args.push(args.pop() - i);
                break;
            case LEX_SLASH:
                i = args.pop();
                if (i) {
                    args.push (args.pop() / i);
                    break;
                }
                else 
                    throw "POLIZ:divide by zero";
            case LEX_EQ:
                args.push(args.pop() == args.pop());
                break;
            case LEX_LSS:
                i = args.pop();
                args.push(args.pop() < i);
                break;
            case LEX_GTR:
                i = args.pop();
                args.push(args.pop() > i);
                break;
            case LEX_LEQ:
                i = args.pop();
                args.push(args.pop() <= i);
                break;
            case LEX_GEQ:
                i = args.pop();
                args.push(args.pop() >= i);
                break;
            case LEX_NEQ:
                i = args.pop();
                args.push(args.pop() != i);
                break;
            case LEX_ASSIGN: {
                Ident *id;
                i = args.pop();
                j = args.pop();
                if (j == -1) 
                    id = curr_id;
                else 
                    id = &TID[j];
                id->put_value(i);
                id->put_assign();
                break;
            }
            default:
                throw "POLIZ: unexpected elem";
        } 
        ++index;
    }; 
    std::cout << "Baby shark todo todo todo todo" << std::endl;
}
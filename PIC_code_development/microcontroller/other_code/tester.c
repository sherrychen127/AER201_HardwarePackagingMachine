#if _pragma_once_support
#    pragma once
#endif
#include "tester.h"

Instruction* initInstruction(){
    Instruction *in = (Instruction*)malloc(sizeof(Instruction));
    in->label = 0;
    in->diet = 0;
    in->amount = 0;
    in->next = NULL;
    return in;
}

char* get_diet_name(DIET diet){

    switch(diet) {
        case NONE :
            return "    ";
            break;
        case R :
            return " R  ";
            break;
        case F :
            return " F  ";
            break;
        case L :
            return " L  ";
            break;
        case RF :
            return " RF ";
            break;
        case RL :
            return " RL ";
            break;
        case FL :
            return " FL ";
            break;
        case RRF :
            return "RRF ";
            break;
        case RRL :
            return "RRL ";
            break;
        case RFF :
            return "RFF ";
            break;
        case RLL :
            return "RLL ";
            break;
        case RFL :
            return "RFL ";
            break;
        case FFL :
            return "FFL ";
            break;
        case FLL :
            return "FLL ";
            break;
        case RRFL :
            return "RRFL";
            break;
        case RFFL :
            return "RFFL";
            break;
        case RFLL :
            return "RFLL";
            break;
        case RLLL :
            return "RLLL";
            break;
        case FLLL :
            return "FLLL";
            break;
        default:
            return "????";
   }
}
void printDrawer(Drawer dr){
    if(dr.taped){
        fprintf(stdout,
            "|      |\n| TAPE |\n|      |\n|      |\n-------"
            );
    } //if

    else{
        fprintf(stdout,
            "| %s |\n| %s |\n| %s |\n| %s |\n--------",
            get_diet_name(dr.diet[3]), get_diet_name(dr.diet[2]), get_diet_name(dr.diet[1]), get_diet_name(dr.diet[0])
            );
    } //else
}

void printContainer(Drawer *cont){

    fprintf(stdout,
            "| %s | %s | %s | %s |\n| %s | %s | %s | %s |\n| %s | %s | %s | %s |\n| %s | %s | %s | %s |\n-----------------------------\n"
            "| %s | %s | %s | %s |\n| %s | %s | %s | %s |\n| %s | %s | %s | %s |\n| %s | %s | %s | %s |\n-----------------------------\n"
            "| %s | %s | %s | %s |\n| %s | %s | %s | %s |\n| %s | %s | %s | %s |\n| %s | %s | %s | %s |\n-----------------------------\n"
            "| %s | %s | %s | %s |\n| %s | %s | %s | %s |\n| %s | %s | %s | %s |\n| %s | %s | %s | %s |\n-----------------------------\n"

            ,get_diet_name(cont[0].diet[3]), get_diet_name(cont[1].diet[3]), get_diet_name(cont[2].diet[3]), get_diet_name(cont[3].diet[3])
            ,get_diet_name(cont[0].diet[2]), get_diet_name(cont[1].diet[2]), get_diet_name(cont[2].diet[2]), get_diet_name(cont[3].diet[2])
            ,get_diet_name(cont[0].diet[1]), get_diet_name(cont[1].diet[1]), get_diet_name(cont[2].diet[1]), get_diet_name(cont[3].diet[1])
            ,get_diet_name(cont[0].diet[0]), get_diet_name(cont[1].diet[0]), get_diet_name(cont[2].diet[0]), get_diet_name(cont[3].diet[0])

            ,get_diet_name(cont[4].diet[3]), get_diet_name(cont[5].diet[3]), get_diet_name(cont[6].diet[3]), get_diet_name(cont[7].diet[3])
            ,get_diet_name(cont[4].diet[2]), get_diet_name(cont[5].diet[2]), get_diet_name(cont[6].diet[2]), get_diet_name(cont[7].diet[2])
            ,get_diet_name(cont[4].diet[1]), get_diet_name(cont[5].diet[1]), get_diet_name(cont[6].diet[1]), get_diet_name(cont[7].diet[1])
            ,get_diet_name(cont[4].diet[0]), get_diet_name(cont[5].diet[0]), get_diet_name(cont[6].diet[0]), get_diet_name(cont[7].diet[0])

            ,get_diet_name(cont[8].diet[3]), get_diet_name(cont[9].diet[3]), get_diet_name(cont[10].diet[3]), get_diet_name(cont[11].diet[3])
            ,get_diet_name(cont[8].diet[2]), get_diet_name(cont[9].diet[2]), get_diet_name(cont[10].diet[2]), get_diet_name(cont[11].diet[2])
            ,get_diet_name(cont[8].diet[1]), get_diet_name(cont[9].diet[1]), get_diet_name(cont[10].diet[1]), get_diet_name(cont[11].diet[1])
            ,get_diet_name(cont[8].diet[0]), get_diet_name(cont[9].diet[0]), get_diet_name(cont[10].diet[0]), get_diet_name(cont[11].diet[0])

            ,get_diet_name(cont[12].diet[3]), get_diet_name(cont[13].diet[3]), get_diet_name(cont[14].diet[3]), get_diet_name(cont[15].diet[3])
            ,get_diet_name(cont[12].diet[2]), get_diet_name(cont[13].diet[2]), get_diet_name(cont[14].diet[2]), get_diet_name(cont[15].diet[2])
            ,get_diet_name(cont[12].diet[1]), get_diet_name(cont[13].diet[1]), get_diet_name(cont[14].diet[1]), get_diet_name(cont[15].diet[1])
            ,get_diet_name(cont[12].diet[0]), get_diet_name(cont[13].diet[0]), get_diet_name(cont[14].diet[0]), get_diet_name(cont[15].diet[0])
            );

}

void printKeypad(){
    fprintf(stdout, "\n 1 2 3 R     Format multiple parameters seperated by spaces and semi-colons:\n" \
            " 4 5 6 F     e.g. 9 RF 2; 12 RFLL 1 for \n" \
            " 7 8 9 L\n * 0 # D     2 RF in drawer 9 and 1 RFLL in drawer 12\n");
}

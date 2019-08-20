#include "tester.h"

char* errorMsg(int i){
    if(i==1)
        return "Number of R pills exceeds 2";

    else if(i==2)
        return "Number of F pills exceeds 2";

    else if(i==3)
        return "Number of L pills exceeds 3";

    else if(i==4)
        return "Total number of pills exceeds 4";

    else if(i==5)
        return "Drawer is taped.\n";
    else
        return "Something very weird happened";
}
Instruction* getInstructions(){  ///returns a pointer to list of instructions. Last is 0 0 0
    /// A: R, B: F, C: L
    Instruction *ret=initInstruction();
    char str1[80];  //holds entire string
    char str2[8][10];  //holds seperate instructions
    printKeypad();
    fprintf(stdout, "\nParameters: ");
    fgets(str1, sizeof(str1), stdin);

    int ctr=0, j=0;
    for(int i=0;i<strlen(str1);i++){
        if(str1[i]==';'|| str1[i]=='\0'){
            str2[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else{
            str2[ctr][j]=str1[i];
            j++;
        }
    } //for loop

    //now ctr holds number of different instructions
    Instruction *temp = ret;
    for(int i=0;i<ctr+1;i++){
        ///assume only three entities: label, diet type, amount
        char *pch;
        pch = strtok(str2[i], " ");
        temp->label = atoi(pch);

        pch = strtok(NULL, " ");

        if(strcmp(pch, "R")==0){temp->diet = R;}
        else if(strcmp(pch, "F")==0){temp->diet = F;}
        else if(strcmp(pch, "L")==0){temp->diet = L;}
        else if(strcmp(pch, "RF")==0){temp->diet = RF;}
        else if(strcmp(pch, "RL")==0){temp->diet = RL;}
        else if(strcmp(pch, "FL")==0){temp->diet = FL;}
        else if(strcmp(pch, "RRF")==0){temp->diet = RRF;}
        else if(strcmp(pch, "RRL")==0){temp->diet = RRL;}
        else if(strcmp(pch, "RFF")==0){temp->diet = RFF;}
        else if(strcmp(pch, "RLL")==0){temp->diet = RLL;}
        else if(strcmp(pch, "RFL")==0){temp->diet = RFL;}
        else if(strcmp(pch, "FFL")==0){temp->diet = FFL;}
        else if(strcmp(pch, "FLL")==0){temp->diet = FLL;}
        else if(strcmp(pch, "RRFL")==0){temp->diet = RRFL;}
        else if(strcmp(pch, "RFFL")==0){temp->diet = RFFL;}
        else if(strcmp(pch, "RFLL")==0){temp->diet = RFLL;}
        else if(strcmp(pch, "RLLL")==0){temp->diet = RLLL;}
        else if(strcmp(pch, "FLLL")==0){temp->diet = FLLL;}
        else{temp->diet = NONE;}  ///none if invalid input

        pch = strtok(NULL, " ");
        temp->amount = atoi(pch);
        temp->next = initInstruction();
        temp = temp->next;
    }


    return ret;
}

int isValid(Drawer *container, Instruction *inst){
    ///match error messages to errorMsg()
    DIET *check = container[inst->label].diet;
    if(container[inst->label].taped == 1)
        return 5;
    else{
        unsigned short R_count = 0, F_count = 0, L_count = 0;
        for(int i=0; i<4; i++){
            switch(check[i]) {
                case NONE :
                    break;
                case R :
                    R_count += 1;
                    break;
                case F :
                    F_count += 1;
                    break;
                case L :
                    L_count += 1;
                    break;
                case RF :
                    R_count += 1;
                    F_count += 1;
                    break;
                case RL :
                    R_count += 1;
                    L_count += 1;
                    break;
                case FL :
                    F_count += 1;
                    L_count += 1;
                    break;
                case RRF :
                    R_count += 2;
                    F_count += 1;
                    break;
                case RRL :
                    R_count += 2;
                    L_count += 1;
                    break;
                case RFF :
                    R_count += 1;
                    F_count += 2;
                    break;
                case RLL :
                    R_count += 1;
                    L_count += 2;
                    break;
                case RFL :
                    R_count += 1;
                    F_count += 1;
                    L_count += 1;
                    break;
                case FFL :
                    F_count += 2;
                    L_count += 1;
                    break;
                case FLL :
                    F_count += 1;
                    L_count += 2;
                    break;
                case RRFL :
                    R_count += 2;
                    F_count += 1;
                    L_count += 1;
                    break;
                case RFFL :
                    R_count += 1;
                    F_count += 2;
                    L_count += 1;
                    break;
                case RFLL :
                    R_count += 1;
                    F_count += 1;
                    L_count += 2;
                    break;
                case RLLL :
                    R_count += 1;
                    L_count += 3;
                    break;
                case FLLL :
                    F_count += 1;
                    L_count += 3;
                    break;
                default:
                    return -1;  //unknown pill type in box
            }
        }

        switch(inst->diet) {
            case NONE :
                break;
            case R :
                R_count += 1;
                break;
            case F :
                F_count += 1;
                break;
            case L :
                L_count += 1;
                break;
            case RF :
                R_count += 1;
                F_count += 1;
                break;
            case RL :
                R_count += 1;
                L_count += 1;
                break;
            case FL :
                F_count += 1;
                L_count += 1;
                break;
            case RRF :
                R_count += 2;
                F_count += 1;
                break;
            case RRL :
                R_count += 2;
                L_count += 1;
                break;
            case RFF :
                R_count += 1;
                F_count += 2;
                break;
            case RLL :
                R_count += 1;
                L_count += 2;
                break;
            case RFL :
                R_count += 1;
                F_count += 1;
                L_count += 1;
                break;
            case FFL :
                F_count += 2;
                L_count += 1;
                break;
            case FLL :
                F_count += 1;
                L_count += 2;
                break;
            case RRFL :
                R_count += 2;
                F_count += 1;
                L_count += 1;
                break;
            case RFFL :
                R_count += 1;
                F_count += 2;
                L_count += 1;
                break;
            case RFLL :
                R_count += 1;
                F_count += 1;
                L_count += 2;
                break;
            case RLLL :
                R_count += 1;
                L_count += 3;
                break;
            case FLLL :
                F_count += 1;
                L_count += 3;
                break;
            default:
                return -1;  //unknown pill type in box
        }

        if(R_count + F_count + L_count > 4)
            return 4;

        else if(R_count > 2)
            return 1;

        else if(F_count > 2)
            return 2;

        else if(L_count > 3)
            return 3;

        else
            return 0;
    }
}

int execInstruction(Drawer *container, Instruction *inst){
    int check = isValid(container, inst);
    if(check==0){
        for(int i=0; i<4; i++){
            if(container[inst->label].diet[i]!=NONE){

                //do nothing
            }
            else{
                for(int j=i; j<inst->amount+i; j++){
                    container[inst->label].diet[i] = inst->diet;
                }
                break;

            }
        }
    }

    return check;
}
int main(void){
    Instruction *all_instructions = getInstructions();
    //initialize a container
    Drawer container[16];
    for(int i=0;i<16;i++){
        container[i].diet[0] = NONE;
        container[i].diet[1] = NONE;
        container[i].diet[2] = NONE;
        container[i].diet[3] = NONE;
        container[i].label = i;
        container[i].taped = 0;
    }

    //operation code begin
    Instruction *temp = all_instructions;
    while(temp!=NULL){
        printf("exec instruction %d %d %d\n", temp->label, temp->diet, temp->amount);
        int rc = execInstruction(container, temp);
        if(rc!=0){
            if(rc ==5)
                fprintf(stdout, "%s", errorMsg(rc));
            else
                fprintf(stdout, "%s when trying to put %d%s in drawer %d.\n", errorMsg(rc), temp->amount, get_diet_name(temp->diet), temp->label);
        }
        temp = temp->next;

    }
    printContainer(container);
    free(all_instructions);

    return 0;

}


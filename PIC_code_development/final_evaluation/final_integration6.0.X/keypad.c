
#include "keypad.h"



/*
 * check if the entered number is valid
 * update B_array, S_arrray, W_array, N_array
 
 
 */
int is_valid(){
    //initLCD();
    //printf("ffffff");
    //__delay_ms(1000);
    if (strcmp(current_set2,"B")==0){
        B=1*number;
        total_number = 1*number;
        
        B_array[compartment_number[counter_step]] = B;
        
    }
    
    else if (strcmp(current_set2,"N")==0){
        N=1*number;
        total_number = 1*number;
        N_array[compartment_number[counter_step]] = N;
    }
    else if (strcmp(current_set2,"S")==0){
        S=1*number;
        total_number = 1*number;
        S_array[compartment_number[counter_step]] = S;
    }
    else if (strcmp(current_set2,"W")==0){
        W=1*number;
        total_number = 1*number;
        W_array[compartment_number[counter_step]] = W;
    }
    else if (strcmp(current_set2,"BN")==0){
        B = 1*number;
        //S = 1*number;
        N = 1*number;
        total_number = 2*number;
        
        B_array[compartment_number[counter_step]] = B;
        N_array[compartment_number[counter_step]] = N;
    }
    else if (strcmp(current_set2,"BS")==0){
        B = 1*number;
        //S = 1*number;
        S = 1*number;
        total_number = 2*number;
        
        B_array[compartment_number[counter_step]] = B;
        S_array[compartment_number[counter_step]] = S;
        
    }
    
    else if (strcmp(current_set2,"BW")==0){
        B = 1*number;
        //S = 1*number;
        W = 1*number;
        total_number = 2*number;
        
        B_array[compartment_number[counter_step]] = B;
        W_array[compartment_number[counter_step]] = W;
    }
    else if (strcmp(current_set2,"BBN")==0){
        B = 2*number;
        //S = 1*number;
        N = 1*number;
        total_number = 3*number;
        
        B_array[compartment_number[counter_step]] = B;
        N_array[compartment_number[counter_step]] = N;
    }
    else if (strcmp(current_set2,"BBS")==0){
        B = 2*number;
        // = 1*number;
        S = 1*number;
        total_number = 3*number;
        
        B_array[compartment_number[counter_step]] = B;
        S_array[compartment_number[counter_step]] = S;
    }
    else if (strcmp(current_set2,"BBW")==0){
        B = 2*number;
        //S = 1*number;
        W = 1*number;
        total_number = 3*number;
        
        B_array[compartment_number[counter_step]] = B;
        W_array[compartment_number[counter_step]] = W;
    }
    else if (strcmp(current_set2,"BNW")==0){
        B = 1*number;
        W = 1*number;
        N = 1*number;
        total_number = 3*number;
        
        B_array[compartment_number[counter_step]] = B;
        W_array[compartment_number[counter_step]] = W;
        N_array[compartment_number[counter_step]] = N;
        
    }
    else if (strcmp(current_set2,"BSW")==0){
        B = 1*number;
        S = 1*number;
        W = 1*number;
        total_number = 3*number;
        
        B_array[compartment_number[counter_step]] = B;
        S_array[compartment_number[counter_step]] = S;
        W_array[compartment_number[counter_step]] = W;
        
    }
    else if (strcmp(current_set2,"BWW")==0){
        B = 1*number;
        W = 2*number;
        total_number = 3*number;
        
        B_array[compartment_number[counter_step]] = B;
        W_array[compartment_number[counter_step]] = W;
    }
    else if (strcmp(current_set2,"BNWW")==0){
        B = 1*number;
        N = 1*number;
        W = 2*number;
        total_number = 4*number;
        
        B_array[compartment_number[counter_step]] = B;
        N_array[compartment_number[counter_step]] = N;
        W_array[compartment_number[counter_step]] = W;
    }
    else if (strcmp(current_set2,"BSWW")==0){
        B = 1*number;
        S = 1*number;
        W = 2*number;
        total_number = 4*number;
        
        B_array[compartment_number[counter_step]] = B;
        S_array[compartment_number[counter_step]] = S;
        W_array[compartment_number[counter_step]] = W;
        
    }
    else if (strcmp(current_set2,"BBSW")==0){
        B = 2*number;
        S = 1*number;
        W = number;
        total_number = 4*number;
        
        B_array[compartment_number[counter_step]] = B;
        S_array[compartment_number[counter_step]] = S;
        W_array[compartment_number[counter_step]] = W;
    }
    else if (strcmp(current_set2,"BBNW")==0){
        B = 2*number;
        N = 1*number;
        W = 1*number;
        total_number = 4*number;
        
        B_array[compartment_number[counter_step]] = B;
        N_array[compartment_number[counter_step]] = N;
        W_array[compartment_number[counter_step]] = W;
    }
    else if (strcmp(current_set2,"BNNW")==0){
        B = 1*number;
        N = 2*number;
        W = 1*number;
        total_number = 4*number;
        
        B_array[compartment_number[counter_step]] = B;
        N_array[compartment_number[counter_step]] = N;
        W_array[compartment_number[counter_step]] = W;
    }
    else if (strcmp(current_set2,"BNNN")==0){
        B = 1*number;
        N = 3*number;
        total_number = 4*number;
        
        B_array[compartment_number[counter_step]] = B;
        N_array[compartment_number[counter_step]] = N;
        
    }
    else if (strcmp(current_set2,"BWWW")==0){
        B = 1*number;
        W = 3*number;
        total_number = 4*number;
        
        B_array[compartment_number[counter_step]] = B;
        //N_array[counter_step] = N;
        W_array[compartment_number[counter_step]] = W;
        
    }
    
    //else {
    //    initLCD();
    //    printf("wrong set!!");
    //    __delay_ms(1000);
    //}
    
    //strcpy(current_set2,"");
    return 1;
    
    
}

int check(){
    if (B>2||N>3||S>2||W>4||total_number >4){
        //initLCD();
        //__lcd_home();
        //printf("TOO MANY");
        return 0; 
        }
    return 1;
}

//generate_compartment_array and compartment_number

void generate_compartment_array(int step){
    
    switch(step){
        case 4:
            compartment_array[0] = 1;
            compartment_array[2] = 1;
            compartment_array[4] = 1;
            compartment_array[6] = 1;
            //{0,1,0,1,0,1,0,1};
            
            compartment_number[0] = 0;
            compartment_number[1] = 2;
            compartment_number[2] = 4;
            compartment_number[3] = 6;
            
            break;
        case 5:
            compartment_array[0] = 1;
            compartment_array[1] = 1;
            compartment_array[3] = 1;
            compartment_array[4] = 1;
            compartment_array[6] = 1;
            //int compartment_array[] = {1,1,0,1,1,0,1,0};
            
            
            compartment_number[0] = 0;
            compartment_number[1] = 1;
            compartment_number[2] = 3;
            compartment_number[3] = 4;
            compartment_number[4] = 6;
            //{0,1,3,4,6,0,0,0}
            break;
        case 6:
            
            compartment_array[0] = 1;
            compartment_array[1] = 1;
            compartment_array[2] = 1;
            compartment_array[4] = 1;
            compartment_array[5] = 1;
            compartment_array[6] = 1;
            //int compartment_array[] = {1,1,1,0,1,1,1,0};
            
            compartment_number[0] = 0;
            compartment_number[1] = 1;
            compartment_number[2] = 2;
            compartment_number[3] = 4;
            compartment_number[4] = 5;
            compartment_number[5] = 6;
            
            break;
        case 7:
            compartment_array[0] = 1;
            compartment_array[1] = 1;
            compartment_array[2] = 1;
            compartment_array[3] = 1;
            compartment_array[4] = 1;
            compartment_array[5] = 1;
            compartment_array[6] = 1;
            //int compartment_array[] = {1,1,1,1,1,1,1,0};
            
            compartment_number[0] = 0;
            compartment_number[1] = 1;
            compartment_number[2] = 2;
            compartment_number[3] = 3;
            compartment_number[4] = 4;
            compartment_number[5] = 5;
            compartment_number[6] = 6;
            
            break;
        case 8:
            compartment_array[0] = 1;
            compartment_array[1] = 1;
            compartment_array[2] = 1;
            compartment_array[3] = 1;
            compartment_array[4] = 1;
            compartment_array[5] = 1;
            compartment_array[6] = 1;
            compartment_array[7] = 1;
            //int compartment_array[]= {1,1,1,1,1,1,1,0};
            
            compartment_number[0] = 0;
            compartment_number[1] = 1;
            compartment_number[2] = 2;
            compartment_number[3] = 3;
            compartment_number[4] = 4;
            compartment_number[5] = 5;
            compartment_number[6] = 6;
            compartment_number[7] = 7;
            
            break;
        default:
            compartment_array[0] = 0;
            compartment_array[1] = 0;
            compartment_array[2] = 0;
            compartment_array[3] = 0;
            compartment_array[4] = 0;
            compartment_array[5] = 0;
            compartment_array[6] = 0;
            compartment_array[7] = 0;
            //int compartment_array[] = {0,0,0,0,0,0,0,0};
    }
}


void store_prev(){
    for (int i = 0; i<8; i++){
        strncpy(prev_set[i],final_set[i],5);
        prev_number[i] = final_number[i];
    }

}





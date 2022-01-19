#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INITIALPOPULATIONNUMBER 40000
#define RANGE 60
#define RESULT 164
#define LIMIT 12000
#define MUTATECHANGE 20

int order = 0;
int worstOrder1 = 0;
int worstOrder2 = 0;
int version = 1;
int mutateChange = 20;

typedef struct Equation{

    int a,b,c,d,e,f;
    int score;

}equation;

typedef struct Fitness{

    equation* equation;
    int i;

}Fitness;

void createEquationsRandomly(equation* array);
int calculateEquation(int a,int b, int c, int d, int e, int f);
Fitness* fitness(equation* array);
int crossOver(equation* array);
Fitness* unFitness(equation* array);
int createRandomNumber();
void mutate(equation* member);

int main() {

    equation* equationList = (equation*) malloc(INITIALPOPULATIONNUMBER * sizeof(equation));
    createEquationsRandomly(equationList);
    printf("The best %d \n", fitness(equationList)->equation->score);
    int a = 0;
    while (crossOver(equationList) != 0){
        if (a > LIMIT) break;
        a++;
    }
    if(a>LIMIT) printf("We could not found the result, please change population or range number ... \n");

    return 0;
}
void createEquationsRandomly(equation* array){
    //Population number 20
    equation* equation1 = (equation*) malloc(sizeof(equation));

    for (int i = 0; i < INITIALPOPULATIONNUMBER; ++i) {

        equation1->a = createRandomNumber();
        equation1->b = createRandomNumber();
        equation1->c = createRandomNumber();
        equation1->d = createRandomNumber();
        equation1->e = createRandomNumber();
        equation1->f = createRandomNumber();

        int result = calculateEquation(equation1->a,equation1->b,equation1->c,equation1->d,equation1->e,equation1->f);
        //printf(" %d. result is %d \n",i+1,result);
        equation1->score = abs(RESULT-result);
        array[i] = *equation1;
        //printf(" %d , %d \n",result,array[i].score);

    }

}
int calculateEquation(int a,int b, int c, int d, int e, int f){
    return a+2*b-3*c+d+4*e+f;
}
Fitness* fitness(equation* array){
    Fitness* fitness1 = malloc(sizeof(Fitness));
    fitness1->equation = &array[0];
    fitness1->i = 0;
    for (int i = 1; i < INITIALPOPULATIONNUMBER; i++) {
        //printf("Array score %d, current score %d\n",array[i]->score,best1->score);
        if (array[i].score < fitness1 -> equation->score) {
            fitness1->equation = &array[i];
            fitness1->i = i;
        }
    }
    return fitness1;
}
int crossOver(equation* array){

    mutateChange++;
    equation* child = malloc(sizeof(equation));
    Fitness* equation1 = malloc(sizeof(Fitness));

    if (worstOrder1 == 0){
        equation1 = fitness(array);
        worstOrder1 = 1;
    }else{
        equation1 = unFitness(array);
        worstOrder1 = 0;
    }

    int score = equation1->equation->score;
    Fitness* equation2 = malloc(sizeof (Fitness));
    if (worstOrder2 == 1){
        equation2 = unFitness(array);
        worstOrder2 = 0;
    }

    equation1 -> equation-> score = 1000000000;
    if (worstOrder2 == 0){
        equation2 = fitness(array);
        worstOrder2 = 1;
    }
    equation1 -> equation->score = score;

    child->a = equation2->equation->d;
    child->b = equation2->equation->e;
    child->c = equation2->equation->f;
    child->d = equation1->equation->a;
    child->e = equation1->equation->b;
    child->f = equation1->equation->c;

    int result = calculateEquation(child->a,child->b,child->c,child->d,child->e,child->f);
    child->score = abs(RESULT-result);

    if (mutateChange == MUTATECHANGE){
        printf("(Mutated) ");
        mutate(child);
        mutateChange = 0;
    }

    if(order == 0){
        array[equation1->i] = *child;
        order = 1;
    }else {
        array[equation2->i] = *child;
        order = 0;
    }

    printf("%d. Generation a : %d, b : %d, c : %d, d : %d, e : %d, f : %d , Result : %d\n",
           version,child->a,child->b,child->c,child->d,child->e,child->f,
           calculateEquation(child->a,child->b,child->c,child->d,child->e,child->f));
    version++;
    return child->score;

}
Fitness* unFitness(equation* array){
    Fitness* worst = malloc(sizeof(Fitness));
    worst->equation = &array[0];
    worst->i = 0;
    int a = 0;
    for (int i = 1; i < INITIALPOPULATIONNUMBER; ++i) {
        if (array[i].score > worst->equation->score){
            worst->equation = &array[i];
            a = i;
        }
    }
    return worst;
}
int createRandomNumber(){
    return rand() % RANGE;
}
void mutate(equation* member){
    int b = member->b;
    member->b = member->f;
    member->f = b;
    int result = calculateEquation(member->a,member->b,member->c,member->d,member->e,member->f);
    member->score = abs(RESULT - result);

}


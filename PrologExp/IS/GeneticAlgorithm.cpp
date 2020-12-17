/****************************************/
//功能：使用遗传算法求解y = -x^2 + 5的最大值
//遗传算法细节：
//编码：二进制
//选择：轮转赌轮
//交叉：单点交叉，交叉概率固定
//变异：平均随机变异，变异概率固定
//具体参数可以事先给定

/****************************************/
#include <stdio.h>  
#include <conio.h>  
#include <stdlib.h>  
#include <math.h>
#include <time.h>  
#include <iostream>  

using namespace std;

/*****初始化一些参数*****/
const int Population_size = 100;        //种群规模
const int Chromosome_length = 6;    //假定有64个网络节点，用64位表示每一个节点
double rate_crossover = 0.5;                //交叉率
double rate_mutation = 0.001;           //变异率
int iteration_num = 50;                     //进化50代                                     
/****************************************/

//将染色体定义为结构体类型
typedef struct Chromosome                          
{   
    short int bit[Chromosome_length];           //染色体二进制码串
    double value;                                           //二进制代码对应的实际值
    double fitness;                                     //适应值  
    double rate_fit;                                        //相对的fit值，即所占的百分比
    double cumu_fit;                                    //积累概率  
}chromosome;


/*****函数声明*****/
//初始化得到个体的二进制字符串
void population_initialize(chromosome (&population_current)[Population_size]);
//对染色体进行解码
void decode(chromosome &population_current) ;   
//计算染色体的适应度值
double objective_function(double x);
//更新种群内个体的属性值
void fresh_property(chromosome(&population_current)[Population_size]);
//基于旋转赌轮的选择操作    proportional roulette wheel selection
void seletc_prw(chromosome(&population_current)[Population_size], chromosome(&population_next_generation)[Population_size], chromosome &best_individual);
//交叉操作
void crossover(chromosome (&population_next_generation)[Population_size]);  
//突变操作
void mutation(chromosome (&population_next_generation)[Population_size]);
/****************************************/

// 主函数
int main()                                   
{
    /*****初始化定义的种群和个体*****/
    clock_t start, end;//开始计时,精确到秒
    start = clock();
    /****************************************/


    /*****初始化定义的种群和个体*****/
    chromosome population_current[Population_size];                    //当前种群  
    chromosome population_next_generation[Population_size];       //产生的下一代的种群                        
    chromosome best_individual;                                                 //记录适应度的最大值
    chromosome zeros_chromosome;                                                //定义一个全为0的个体，用于群体中某个个体的重置
    /****************************************/

    int i = 0,j = 0;//循环变量

    //*****初始化定义的种群和个体*****
    //首先初始化zeros_chromosome，后使用之初始化其他个体
    for (i = 0; i < Chromosome_length; i++)
        zeros_chromosome.bit[i] = 0;
    zeros_chromosome.fitness = 0.0;
    zeros_chromosome.value = 0.0;
    zeros_chromosome.rate_fit = 0.0;
    zeros_chromosome.cumu_fit = 0.0;

    best_individual = zeros_chromosome;
    for (i = 0; i < Population_size; i++)
    {
        population_current[i] = zeros_chromosome;
        population_next_generation[i] = zeros_chromosome;
    }
    /****************************************/


    printf("\nWelcome to the Genetic Algorithm！\n");  //   
    printf("The Algorithm is based on the function y = -x^2 + 5 to find the maximum value of the function.\n");

enter:printf("\nPlease enter the no. of iterations\n请输入您要设定的迭代数 : ");
    // 输入迭代次数，传送给参数 iteration_num
    scanf("%d", &iteration_num);                           

    // 判断输入的迭代次数是否为负或零，是的话重新输入
    if (iteration_num <1)
        goto enter;


    //种群初始化，得到个体的二进制字符串
    population_initialize(population_current); 
    //更新种群内个体的属性值
    fresh_property(population_current);
    // 开始迭代
    for (i = 0; i< iteration_num; i++)                            
    {
        // 输出当前迭代次数
        //printf("\ni = %d\n", i); 
        //挑选优秀个体组成新的种群
        seletc_prw(population_current,population_next_generation,best_individual);                 
        //对选择后的种群进行交叉操作
        crossover(population_next_generation);              
        //对交叉后的种群进行变异操作
        mutation(population_next_generation);                      
        //更新种群内个体的属性值
        fresh_property(population_next_generation);
        //将population_next_generation的值赋给population_current，并清除population_next_generation的值
        for (i = 0; i < Population_size; i++)
        {
            population_current[i] = population_next_generation[i];
            population_next_generation[i] = zeros_chromosome;
        }
        //检验时间是否到90s
        end = clock();
        if (double(end - start) / CLK_TCK> 89)
            break;
    } 
    //输出所用时间
    printf("\n 迭代%d次所用时间为： %f\n", iteration_num, double(end - start) / CLK_TCK);

    //输出结果
    printf("\n 函数得到最大值为： %f ,适应度为：%f \n", best_individual.value, best_individual.fitness);

    for (i = 0; i<Population_size; i++)
    {
        printf(" population_current[%d]=", i);
        for (j = 0; j < Chromosome_length; j++)
            printf(" %d", population_current[i].bit[j]);
        printf("        value=%f    fitness = %f\n", population_current[i].value, population_current[i].fitness);
    }
    printf("\nPress any key to end ! ");


    // 清除所有缓冲区
//  flushall();                                   
    system("pause");
}


//函数：种群初始化  
//输入是数组的引用
//调用时，只需输入数组名
void population_initialize(chromosome (&population_current)[Population_size])   
{
    int i = 0, j = 0;

    //产生随机数种子
    srand((unsigned)time(NULL));
    //遍历种群中的每个染色体
    for (j = 0; j<Population_size; j++)                              
    {
        //随机初始化染色体的每一位
        for (i = 0; i<Chromosome_length; i++)                       
        {
            // 随机产生染色体上每一个基因位的值，0或1
            population_current[j].bit[i] = rand()% 2;         
        }

    }

}


// 函数：将二进制换算为十进制 
void decode(chromosome &population_current)   
{//此处的染色体长度为，其中个表示符号位  
    int i = 0;
    population_current.value = 0;
    //地位在前，高位再后
    for( i = 0 ; i < Chromosome_length -1; i++ ) 
        population_current.value += (double)pow(2, i) * (double)population_current.bit[i];    //遍历染色体二进制编码, 
    //最高位为符号位，如果是1代表负数
    if (population_current.bit[Chromosome_length - 1] == 1)
        population_current.value = 0 - population_current.value;

}

//函数:计算适应度
double objective_function(double x)
{
    double y;
    // 目标函数：y= - ( (x-1)^ 2 ) +5
    y = -((x - 1) *(x - 1)) + 5;                                
    return(y);
}

//函数：更新种群内个体的属性值
//说明：当种群中个体的二进制串确定后，就可以计算每个个体fitness、value、rate_fit 、cumu_fit
//输入：
//chromosome (&population_current)[Population_size] 当前代种群的引用
void fresh_property(chromosome (&population_current)[Population_size])
{
    int j = 0;
    double sum = 0;

    for (j = 0; j < Population_size; j++)
    {

    //染色体解码，将二进制换算为十进制，得到一个整数值
        //计算二进制串对应的10进制数值
        decode(population_current[j]);                 
        //计算染色体的适应度
        population_current[j].fitness = objective_function(population_current[j].value); 
        sum = sum + population_current[j].fitness;

    }


    //计算每条染色体的适应值百分比及累计适应度值的百分比，在轮盘赌选择法时用它选择染色体  
    population_current[0].rate_fit = population_current[0].fitness / sum;
    population_current[0].cumu_fit = population_current[0].rate_fit;
    for (j = 1; j < Population_size; j++)
    {
        population_current[j].rate_fit = population_current[j].fitness / sum;
        population_current[j].cumu_fit = population_current[j].rate_fit + population_current[j-1].cumu_fit;
    }


}

//函数：基于轮盘赌选择方法，对种群中的染色体进行选择  
//输入：
//chromosome (&population_current)[Population_size] 当前代种群的引用
//chromosome (&population_next_generation)[Population_size] 选择出的下一代种群的引用
//chromosome &best_individual 当前代种群中的最优个体
void seletc_prw(chromosome (&population_current)[Population_size],chromosome (&population_next_generation)[Population_size],chromosome &best_individual)
{

    int i = 0, j = 0;
    double rate_rand = 0.0;
    best_individual = population_current[0];
    //产生随机数种子
    srand((unsigned)time(NULL));
    for (i = 0; i < Population_size; i++)
    {
        rate_rand = (float)rand() / (RAND_MAX);
        if (rate_rand < population_current[0].cumu_fit)
            population_next_generation[i] = population_current[0];      
        else
        {
            for (j = 0; j < Population_size; j++)
            {
                if (population_current[j].cumu_fit <= rate_rand && rate_rand < population_current[j + 1].cumu_fit)
                {
                    population_next_generation[i] = population_current[j + 1];
                    break;
                }
            }
        }

        //如果当前个体比目前的最有个体还要优秀，则将当前个体设为最优个体
        if(population_current[i].fitness > best_individual.fitness)
            best_individual = population_current[i];
    }

}


// 函数：交叉操作
void crossover(chromosome (&population_next_generation)[Population_size])          
{   
    int i = 0,j = 0;
    double rate_rand = 0.0;
    short int bit_temp = 0;
    int num1_rand = 0, num2_rand = 0, position_rand = 0;
    //产生随机数种子
    srand((unsigned)time(NULL));
    //应当交叉变异多少次呢？先设定为种群数量
    for (j = 0; j<Population_size; j++)
    {
        rate_rand = (float)rand()/(RAND_MAX);
        //如果大于交叉概率就进行交叉操作
        if(rate_rand <= rate_crossover)
        {
            num1_rand = (int)rand()%(Population_size);
            num2_rand = (int)rand()%(Population_size);
            //随机产生两个染色体的交叉位置
            position_rand = (int)rand()%(Chromosome_length - 1);
            //采用单点交叉，交叉点之后的位数交换
            for (i = position_rand; i<Chromosome_length; i++)
            {
                bit_temp = population_next_generation[num1_rand].bit[i];
                population_next_generation[num1_rand].bit[i] = population_next_generation[num2_rand].bit[i];     
                population_next_generation[num2_rand].bit[i] = bit_temp;     
            }

        }
    }

}

// 函数：变异操作
void mutation(chromosome (&population_next_generation)[Population_size])               
{
    int position_rand = 0;
    int i = 0;
    double rate_rand = 0.0;
    //产生随机数种子
    srand((unsigned)time(NULL));
    //变异次数设定为种群数量
    for (i = 0; i<Population_size; i++)
    {
        rate_rand = (float)rand()/(RAND_MAX);
        //如果大于交叉概率就进行变异操作
        if(rate_rand <= rate_mutation)
        {
            //随机产生突变位置
            position_rand = (int)rand()%(Chromosome_length);
            //突变
            if (population_next_generation[i].bit[position_rand] == 0)
                population_next_generation[i].bit[position_rand] = 1;
            else
                population_next_generation[i].bit[position_rand] = 0;

        }

    }
}



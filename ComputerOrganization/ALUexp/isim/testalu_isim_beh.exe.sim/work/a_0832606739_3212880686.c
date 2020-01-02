/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/Users/Raibows/Desktop/2 ALU/alu.vhd";
extern char *IEEE_P_2592010699;
extern char *IEEE_P_3620187407;

char *ieee_p_2592010699_sub_1837678034_503743352(char *, char *, char *, char *);
char *ieee_p_3620187407_sub_436279890_3965413181(char *, char *, char *, char *, int );
char *ieee_p_3620187407_sub_767668596_3965413181(char *, char *, char *, char *, char *, char *);


static void work_a_0832606739_3212880686_p_0(char *t0)
{
    char t10[16];
    char t11[16];
    char *t1;
    char *t2;
    unsigned char t3;
    unsigned char t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    int t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    char *t16;
    char *t17;
    unsigned char t18;
    unsigned char t19;
    unsigned int t20;

LAB0:    xsi_set_current_line(59, ng0);
    t1 = (t0 + 1192U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)2);
    if (t4 != 0)
        goto LAB2;

LAB4:    t1 = (t0 + 992U);
    t4 = xsi_signal_has_event(t1);
    if (t4 == 1)
        goto LAB9;

LAB10:    t3 = (unsigned char)0;

LAB11:    if (t3 != 0)
        goto LAB7;

LAB8:
LAB3:    t1 = (t0 + 5320);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(59, ng0);
    t1 = (t0 + 5416);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((int *)t8) = 0;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(59, ng0);
    t1 = (t0 + 8308);
    t5 = (t0 + 5480);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 16U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(59, ng0);
    t1 = (t0 + 8324);
    t5 = (t0 + 5544);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 16U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(59, ng0);
    t1 = (t0 + 8340);
    t5 = (t0 + 5608);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 4U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(59, ng0);
    t1 = xsi_get_transient_memory(16U);
    memset(t1, 0, 16U);
    t2 = t1;
    memset(t2, (unsigned char)2, 16U);
    t5 = (t0 + 5672);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 16U);
    xsi_driver_first_trans_fast_port(t5);
    xsi_set_current_line(59, ng0);
    t1 = (t0 + 8344);
    t5 = (t11 + 0U);
    t6 = (t5 + 0U);
    *((int *)t6) = 0;
    t6 = (t5 + 4U);
    *((int *)t6) = 6;
    t6 = (t5 + 8U);
    *((int *)t6) = 1;
    t12 = (6 - 0);
    t13 = (t12 * 1);
    t13 = (t13 + 1);
    t6 = (t5 + 12U);
    *((unsigned int *)t6) = t13;
    t6 = ieee_p_2592010699_sub_1837678034_503743352(IEEE_P_2592010699, t10, t1, t11);
    t7 = (t10 + 12U);
    t13 = *((unsigned int *)t7);
    t14 = (1U * t13);
    t3 = (7U != t14);
    if (t3 == 1)
        goto LAB5;

LAB6:    t8 = (t0 + 5736);
    t9 = (t8 + 56U);
    t15 = *((char **)t9);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    memcpy(t17, t6, 7U);
    xsi_driver_first_trans_fast_port(t8);
    goto LAB3;

LAB5:    xsi_size_not_matching(7U, t14, 0);
    goto LAB6;

LAB7:    xsi_set_current_line(61, ng0);
    t2 = (t0 + 2312U);
    t6 = *((char **)t2);
    t12 = *((int *)t6);
    if (t12 == 0)
        goto LAB13;

LAB17:    if (t12 == 1)
        goto LAB14;

LAB18:    if (t12 == 2)
        goto LAB15;

LAB19:
LAB16:    xsi_set_current_line(66, ng0);
    t1 = (t0 + 5416);
    t2 = (t1 + 56U);
    t5 = *((char **)t2);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((int *)t7) = 0;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(66, ng0);
    t1 = (t0 + 2792U);
    t2 = *((char **)t1);
    t1 = (t0 + 5672);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 16U);
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(66, ng0);
    t1 = (t0 + 8372);
    t5 = (t11 + 0U);
    t6 = (t5 + 0U);
    *((int *)t6) = 0;
    t6 = (t5 + 4U);
    *((int *)t6) = 6;
    t6 = (t5 + 8U);
    *((int *)t6) = 1;
    t12 = (6 - 0);
    t13 = (t12 * 1);
    t13 = (t13 + 1);
    t6 = (t5 + 12U);
    *((unsigned int *)t6) = t13;
    t6 = ieee_p_2592010699_sub_1837678034_503743352(IEEE_P_2592010699, t10, t1, t11);
    t7 = (t10 + 12U);
    t13 = *((unsigned int *)t7);
    t14 = (1U * t13);
    t3 = (7U != t14);
    if (t3 == 1)
        goto LAB27;

LAB28:    t8 = (t0 + 5736);
    t9 = (t8 + 56U);
    t15 = *((char **)t9);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    memcpy(t17, t6, 7U);
    xsi_driver_first_trans_fast_port(t8);

LAB12:    goto LAB3;

LAB9:    t2 = (t0 + 1032U);
    t5 = *((char **)t2);
    t18 = *((unsigned char *)t5);
    t19 = (t18 == (unsigned char)3);
    t3 = t19;
    goto LAB11;

LAB13:    xsi_set_current_line(63, ng0);
    t2 = (t0 + 5416);
    t7 = (t2 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t15 = *((char **)t9);
    *((int *)t15) = 1;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(63, ng0);
    t1 = (t0 + 1352U);
    t2 = *((char **)t1);
    t1 = (t0 + 5480);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 16U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(63, ng0);
    t1 = (t0 + 8351);
    t5 = (t11 + 0U);
    t6 = (t5 + 0U);
    *((int *)t6) = 0;
    t6 = (t5 + 4U);
    *((int *)t6) = 6;
    t6 = (t5 + 8U);
    *((int *)t6) = 1;
    t12 = (6 - 0);
    t13 = (t12 * 1);
    t13 = (t13 + 1);
    t6 = (t5 + 12U);
    *((unsigned int *)t6) = t13;
    t6 = ieee_p_2592010699_sub_1837678034_503743352(IEEE_P_2592010699, t10, t1, t11);
    t7 = (t10 + 12U);
    t13 = *((unsigned int *)t7);
    t14 = (1U * t13);
    t3 = (7U != t14);
    if (t3 == 1)
        goto LAB21;

LAB22:    t8 = (t0 + 5736);
    t9 = (t8 + 56U);
    t15 = *((char **)t9);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    memcpy(t17, t6, 7U);
    xsi_driver_first_trans_fast_port(t8);
    xsi_set_current_line(63, ng0);
    t1 = (t0 + 2472U);
    t2 = *((char **)t1);
    t1 = (t0 + 5672);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 16U);
    xsi_driver_first_trans_fast_port(t1);
    goto LAB12;

LAB14:    xsi_set_current_line(64, ng0);
    t1 = (t0 + 5416);
    t2 = (t1 + 56U);
    t5 = *((char **)t2);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((int *)t7) = 2;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(64, ng0);
    t1 = (t0 + 1352U);
    t2 = *((char **)t1);
    t1 = (t0 + 5544);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 16U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(64, ng0);
    t1 = (t0 + 8358);
    t5 = (t11 + 0U);
    t6 = (t5 + 0U);
    *((int *)t6) = 0;
    t6 = (t5 + 4U);
    *((int *)t6) = 6;
    t6 = (t5 + 8U);
    *((int *)t6) = 1;
    t12 = (6 - 0);
    t13 = (t12 * 1);
    t13 = (t13 + 1);
    t6 = (t5 + 12U);
    *((unsigned int *)t6) = t13;
    t6 = ieee_p_2592010699_sub_1837678034_503743352(IEEE_P_2592010699, t10, t1, t11);
    t7 = (t10 + 12U);
    t13 = *((unsigned int *)t7);
    t14 = (1U * t13);
    t3 = (7U != t14);
    if (t3 == 1)
        goto LAB23;

LAB24:    t8 = (t0 + 5736);
    t9 = (t8 + 56U);
    t15 = *((char **)t9);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    memcpy(t17, t6, 7U);
    xsi_driver_first_trans_fast_port(t8);
    xsi_set_current_line(64, ng0);
    t1 = (t0 + 2632U);
    t2 = *((char **)t1);
    t1 = (t0 + 5672);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 16U);
    xsi_driver_first_trans_fast_port(t1);
    goto LAB12;

LAB15:    xsi_set_current_line(65, ng0);
    t1 = (t0 + 5416);
    t2 = (t1 + 56U);
    t5 = *((char **)t2);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((int *)t7) = 3;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(65, ng0);
    t1 = (t0 + 1352U);
    t2 = *((char **)t1);
    t13 = (15 - 3);
    t14 = (t13 * 1U);
    t20 = (0 + t14);
    t1 = (t2 + t20);
    t5 = (t0 + 5608);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 4U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(65, ng0);
    t1 = (t0 + 8365);
    t5 = (t11 + 0U);
    t6 = (t5 + 0U);
    *((int *)t6) = 0;
    t6 = (t5 + 4U);
    *((int *)t6) = 6;
    t6 = (t5 + 8U);
    *((int *)t6) = 1;
    t12 = (6 - 0);
    t13 = (t12 * 1);
    t13 = (t13 + 1);
    t6 = (t5 + 12U);
    *((unsigned int *)t6) = t13;
    t6 = ieee_p_2592010699_sub_1837678034_503743352(IEEE_P_2592010699, t10, t1, t11);
    t7 = (t10 + 12U);
    t13 = *((unsigned int *)t7);
    t14 = (1U * t13);
    t3 = (7U != t14);
    if (t3 == 1)
        goto LAB25;

LAB26:    t8 = (t0 + 5736);
    t9 = (t8 + 56U);
    t15 = *((char **)t9);
    t16 = (t15 + 56U);
    t17 = *((char **)t16);
    memcpy(t17, t6, 7U);
    xsi_driver_first_trans_fast_port(t8);
    xsi_set_current_line(65, ng0);
    t1 = (t0 + 1352U);
    t2 = *((char **)t1);
    t1 = (t0 + 5672);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 16U);
    xsi_driver_first_trans_fast_port(t1);
    goto LAB12;

LAB20:;
LAB21:    xsi_size_not_matching(7U, t14, 0);
    goto LAB22;

LAB23:    xsi_size_not_matching(7U, t14, 0);
    goto LAB24;

LAB25:    xsi_size_not_matching(7U, t14, 0);
    goto LAB26;

LAB27:    xsi_size_not_matching(7U, t14, 0);
    goto LAB28;

}

static void work_a_0832606739_3212880686_p_1(char *t0)
{
    char t8[16];
    char t23[16];
    char t24[16];
    char *t1;
    char *t2;
    char *t3;
    int t4;
    char *t5;
    char *t6;
    int t7;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    unsigned int t15;
    unsigned int t16;
    unsigned char t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;

LAB0:    xsi_set_current_line(75, ng0);
    t1 = (t0 + 2952U);
    t2 = *((char **)t1);
    t1 = (t0 + 8379);
    t4 = xsi_mem_cmp(t1, t2, 4U);
    if (t4 == 1)
        goto LAB3;

LAB6:    t5 = (t0 + 8383);
    t7 = xsi_mem_cmp(t5, t2, 4U);
    if (t7 == 1)
        goto LAB4;

LAB7:
LAB5:    xsi_set_current_line(82, ng0);
    t1 = (t0 + 8387);
    t3 = (t0 + 5800);
    t5 = (t3 + 56U);
    t6 = *((char **)t5);
    t9 = (t6 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t1, 16U);
    xsi_driver_first_trans_fast(t3);

LAB2:    t1 = (t0 + 5336);
    *((int *)t1) = 1;

LAB1:    return;
LAB3:    xsi_set_current_line(76, ng0);
    t9 = (t0 + 2472U);
    t10 = *((char **)t9);
    t9 = (t0 + 8188U);
    t11 = (t0 + 2632U);
    t12 = *((char **)t11);
    t11 = (t0 + 8188U);
    t13 = ieee_p_3620187407_sub_767668596_3965413181(IEEE_P_3620187407, t8, t10, t9, t12, t11);
    t14 = (t8 + 12U);
    t15 = *((unsigned int *)t14);
    t16 = (1U * t15);
    t17 = (16U != t16);
    if (t17 == 1)
        goto LAB9;

LAB10:    t18 = (t0 + 5800);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    t21 = (t20 + 56U);
    t22 = *((char **)t21);
    memcpy(t22, t13, 16U);
    xsi_driver_first_trans_fast(t18);
    goto LAB2;

LAB4:    xsi_set_current_line(77, ng0);
    t1 = (t0 + 2472U);
    t2 = *((char **)t1);
    t1 = (t0 + 8188U);
    t3 = (t0 + 2632U);
    t5 = *((char **)t3);
    t3 = (t0 + 8188U);
    t6 = ieee_p_2592010699_sub_1837678034_503743352(IEEE_P_2592010699, t24, t5, t3);
    t9 = ieee_p_3620187407_sub_767668596_3965413181(IEEE_P_3620187407, t23, t2, t1, t6, t24);
    t10 = ieee_p_3620187407_sub_436279890_3965413181(IEEE_P_3620187407, t8, t9, t23, 1);
    t11 = (t8 + 12U);
    t15 = *((unsigned int *)t11);
    t16 = (1U * t15);
    t17 = (16U != t16);
    if (t17 == 1)
        goto LAB11;

LAB12:    t12 = (t0 + 5800);
    t13 = (t12 + 56U);
    t14 = *((char **)t13);
    t18 = (t14 + 56U);
    t19 = *((char **)t18);
    memcpy(t19, t10, 16U);
    xsi_driver_first_trans_fast(t12);
    goto LAB2;

LAB8:;
LAB9:    xsi_size_not_matching(16U, t16, 0);
    goto LAB10;

LAB11:    xsi_size_not_matching(16U, t16, 0);
    goto LAB12;

}


extern void work_a_0832606739_3212880686_init()
{
	static char *pe[] = {(void *)work_a_0832606739_3212880686_p_0,(void *)work_a_0832606739_3212880686_p_1};
	xsi_register_didat("work_a_0832606739_3212880686", "isim/testalu_isim_beh.exe.sim/work/a_0832606739_3212880686.didat");
	xsi_register_executes(pe);
}

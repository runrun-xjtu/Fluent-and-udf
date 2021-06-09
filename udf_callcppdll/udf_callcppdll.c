#include "udf.h"

double tin = 293;

extern void CppDynamicLinkLibrary();
extern double inTem(double inTem);

DEFINE_PROFILE(tt_profile,t,i)
{
    face_t f;
    begin_f_loop(f,t)
    {
        F_PROFILE(f, t, i) = tin;
    }
    end_f_loop(f,t)
}

DEFINE_EXECUTE_AT_END(execute_at_end)
{
    Domain* d;
    Thread *f_thread;
    face_t f;
	int zone_ID = 7;
    int n=0;
	double temsum=0,avetem=0,ave=tin;
    double flow_time = CURRENT_TIME;
    Message("Last timestep tin value: %g\n", tin);

    d = Get_Domain(1); /* mixture domain if multiphase */
	Thread* thread_name = Lookup_Thread(d, zone_ID);

    begin_f_loop(f, thread_name) /* loops over faces in a face thread */
    {
        temsum = temsum + F_T(f, thread_name);
        n = n + 1;
    }
    end_f_loop(f, thread_name)

    temsum = PRF_GISUM1(temsum);
    n = PRF_GISUM1(n);
    avetem = temsum / n;
    tin = inTem(avetem);
    node_to_host_real_1(tin);

    Message("The n value : %d\n", n);
	Message("The average temperature of the outlet surface: %g\n", avetem);
    Message("New tin value: %g  in flowtime %g \n", tin, flow_time);
}

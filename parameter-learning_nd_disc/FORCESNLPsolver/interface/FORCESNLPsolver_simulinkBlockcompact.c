/*
FORCESNLPsolver : A fast customized optimization solver.

Copyright (C) 2013-2018 EMBOTECH AG [info@embotech.com]. All rights reserved.


This software is intended for simulation and testing purposes only. 
Use of this software for any commercial purpose is prohibited.

This program is distributed in the hope that it will be useful.
EMBOTECH makes NO WARRANTIES with respect to the use of the software 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
PARTICULAR PURPOSE. 

EMBOTECH shall not have any liability for any damage arising from the use
of the software.

This Agreement shall exclusively be governed by and interpreted in 
accordance with the laws of Switzerland, excluding its principles
of conflict of laws. The Courts of Zurich-City shall have exclusive 
jurisdiction in case of any dispute.

*/


#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME FORCESNLPsolver_simulinkBlockcompact

#include "simstruc.h"



/* SYSTEM INCLUDES FOR TIMING ------------------------------------------ */


/* include FORCES functions and defs */
#include "../include/FORCESNLPsolver.h" 

#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

typedef FORCESNLPsolverinterface_float FORCESNLPsolvernmpc_float;

extern void FORCESNLPsolver_casadi2forces(double *x, double *y, double *l, double *p, double *f, double *nabla_f, double *c, double *nabla_c, double *h, double *nabla_h, double *hess, solver_int32_default stage);
FORCESNLPsolver_extfunc pt2function = &FORCESNLPsolver_casadi2forces;




/*====================*
 * S-function methods *
 *====================*/
/* Function: mdlInitializeSizes =========================================
 * Abstract:
 *   Setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S)
{

    DECL_AND_INIT_DIMSINFO(inputDimsInfo);
    DECL_AND_INIT_DIMSINFO(outputDimsInfo);
    ssSetNumSFcnParams(S, 0);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) 
	{
		return; /* Parameter mismatch will be reported by Simulink */
    }

	/* initialize size of continuous and discrete states to zero */
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

	/* initialize input ports - there are 4 in total */
    if (!ssSetNumInputPorts(S, 4)) return;
    	
	/* Input Port 0 */
    ssSetInputPortMatrixDimensions(S,  0, 1464, 1);
    ssSetInputPortDataType(S, 0, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 0, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 0, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 0, 1); /*direct input signal access*/	
	/* Input Port 1 */
    ssSetInputPortMatrixDimensions(S,  1, 16, 1);
    ssSetInputPortDataType(S, 1, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 1, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 1, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 1, 1); /*direct input signal access*/	
	/* Input Port 2 */
    ssSetInputPortMatrixDimensions(S,  2, 11, 1);
    ssSetInputPortDataType(S, 2, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 2, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 2, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 2, 1); /*direct input signal access*/	
	/* Input Port 3 */
    ssSetInputPortMatrixDimensions(S,  3, 2501, 1);
    ssSetInputPortDataType(S, 3, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 3, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 3, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 3, 1); /*direct input signal access*/ 


	/* initialize output ports - there are 1 in total */
    if (!ssSetNumOutputPorts(S, 1)) return;    
		
	/* Output Port 0 */
    ssSetOutputPortMatrixDimensions(S,  0, 1464, 1);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 0, COMPLEX_NO); /* no complex signals suppported */


	/* set sampling time */
    ssSetNumSampleTimes(S, 1);

	/* set internal memory of block */
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
	/* SS_OPTION_USE_TLC_WITH_ACCELERATOR removed */ 
	/* SS_OPTION_USE_TLC_WITH_ACCELERATOR removed */ 
    /* ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE |
		             SS_OPTION_WORKS_WITH_CODE_REUSE)); */
	ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE );

	
}

#if defined(MATLAB_MEX_FILE)
#define MDL_SET_INPUT_PORT_DIMENSION_INFO
static void mdlSetInputPortDimensionInfo(SimStruct        *S, 
                                         int_T            port,
                                         const DimsInfo_T *dimsInfo)
{
    if(!ssSetInputPortDimensionInfo(S, port, dimsInfo)) return;
}
#endif

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_OUTPUT_PORT_DIMENSION_INFO)
static void mdlSetOutputPortDimensionInfo(SimStruct        *S, 
                                          int_T            port, 
                                          const DimsInfo_T *dimsInfo)
{
    if (!ssSetOutputPortDimensionInfo(S, port, dimsInfo)) return;
}
#endif
# define MDL_SET_INPUT_PORT_FRAME_DATA
static void mdlSetInputPortFrameData(SimStruct  *S, 
                                     int_T      port,
                                     Frame_T    frameData)
{
    ssSetInputPortFrameData(S, port, frameData);
}
/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy  the sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}

#define MDL_SET_INPUT_PORT_DATA_TYPE
static void mdlSetInputPortDataType(SimStruct *S, solver_int32_default port, DTypeId dType)
{
    ssSetInputPortDataType( S, 0, dType);
}
#define MDL_SET_OUTPUT_PORT_DATA_TYPE
static void mdlSetOutputPortDataType(SimStruct *S, solver_int32_default port, DTypeId dType)
{
    ssSetOutputPortDataType(S, 0, dType);
}

#define MDL_SET_DEFAULT_PORT_DATA_TYPES
static void mdlSetDefaultPortDataTypes(SimStruct *S)
{
    ssSetInputPortDataType( S, 0, SS_DOUBLE);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
}





/* Function: mdlOutputs =======================================================
 *
*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
	solver_int32_default i, j, k;
	
	/* file pointer for printing */
	FILE *fp = NULL;

	/* Simulink data */
	const real_T *x0 = (const real_T*) ssGetInputPortSignal(S,0);
	const real_T *xinit = (const real_T*) ssGetInputPortSignal(S,1);
	const real_T *xfinal = (const real_T*) ssGetInputPortSignal(S,2);
	const real_T *all_parameters = (const real_T*) ssGetInputPortSignal(S,3);
	
    real_T *outputs = (real_T*) ssGetOutputPortSignal(S,0);
	
	

	/* Solver data */
	FORCESNLPsolver_params params;
	FORCESNLPsolver_output output;
	FORCESNLPsolver_info info;	
	solver_int32_default exitflag;

	/* Extra NMPC data */
	

	/* Copy inputs */
	for( i=0; i<1464; i++)
	{ 
		params.x0[i] = (double) x0[i]; 
	}

	for( i=0; i<16; i++)
	{ 
		params.xinit[i] = (double) xinit[i]; 
	}

	for( i=0; i<11; i++)
	{ 
		params.xfinal[i] = (double) xfinal[i]; 
	}

	for( i=0; i<2501; i++)
	{ 
		params.all_parameters[i] = (double) all_parameters[i]; 
	}

	

	

    #if FORCESNLPsolver_SET_PRINTLEVEL > 0
		/* Prepare file for printfs */
        fp = fopen("stdout_temp","w+");
		if( fp == NULL ) 
		{
			mexErrMsgTxt("freopen of stdout did not work.");
		}
		rewind(fp);
	#endif

	/* Call solver */
	exitflag = FORCESNLPsolver_solve(&params, &output, &info, fp , pt2function);

	#if FORCESNLPsolver_SET_PRINTLEVEL > 0
		/* Read contents of printfs printed to file */
		rewind(fp);
		while( (i = fgetc(fp)) != EOF ) 
		{
			ssPrintf("%c",i);
		}
		fclose(fp);
	#endif

	

	/* Copy outputs */
	for( i=0; i<24; i++)
	{ 
		outputs[i] = (real_T) output.x01[i]; 
	}

	k=24; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x02[i]; 
	}

	k=48; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x03[i]; 
	}

	k=72; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x04[i]; 
	}

	k=96; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x05[i]; 
	}

	k=120; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x06[i]; 
	}

	k=144; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x07[i]; 
	}

	k=168; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x08[i]; 
	}

	k=192; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x09[i]; 
	}

	k=216; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x10[i]; 
	}

	k=240; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x11[i]; 
	}

	k=264; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x12[i]; 
	}

	k=288; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x13[i]; 
	}

	k=312; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x14[i]; 
	}

	k=336; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x15[i]; 
	}

	k=360; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x16[i]; 
	}

	k=384; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x17[i]; 
	}

	k=408; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x18[i]; 
	}

	k=432; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x19[i]; 
	}

	k=456; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x20[i]; 
	}

	k=480; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x21[i]; 
	}

	k=504; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x22[i]; 
	}

	k=528; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x23[i]; 
	}

	k=552; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x24[i]; 
	}

	k=576; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x25[i]; 
	}

	k=600; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x26[i]; 
	}

	k=624; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x27[i]; 
	}

	k=648; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x28[i]; 
	}

	k=672; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x29[i]; 
	}

	k=696; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x30[i]; 
	}

	k=720; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x31[i]; 
	}

	k=744; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x32[i]; 
	}

	k=768; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x33[i]; 
	}

	k=792; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x34[i]; 
	}

	k=816; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x35[i]; 
	}

	k=840; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x36[i]; 
	}

	k=864; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x37[i]; 
	}

	k=888; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x38[i]; 
	}

	k=912; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x39[i]; 
	}

	k=936; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x40[i]; 
	}

	k=960; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x41[i]; 
	}

	k=984; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x42[i]; 
	}

	k=1008; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x43[i]; 
	}

	k=1032; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x44[i]; 
	}

	k=1056; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x45[i]; 
	}

	k=1080; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x46[i]; 
	}

	k=1104; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x47[i]; 
	}

	k=1128; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x48[i]; 
	}

	k=1152; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x49[i]; 
	}

	k=1176; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x50[i]; 
	}

	k=1200; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x51[i]; 
	}

	k=1224; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x52[i]; 
	}

	k=1248; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x53[i]; 
	}

	k=1272; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x54[i]; 
	}

	k=1296; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x55[i]; 
	}

	k=1320; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x56[i]; 
	}

	k=1344; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x57[i]; 
	}

	k=1368; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x58[i]; 
	}

	k=1392; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x59[i]; 
	}

	k=1416; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x60[i]; 
	}

	k=1440; 
	for( i=0; i<24; i++)
	{ 
		outputs[k++] = (real_T) output.x61[i]; 
	}

	
}





/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
}
#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif



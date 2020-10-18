/*
Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it andor
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http:www.gnu.org/licenses/>. 
*/
/*
This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it. 
*/
/* We do support the IEC 559 math functionality, real and complex.  */
/*
wchar_t uses ISOIEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0. 
*/
/* We do not support C11 <threads.h>.  */
/*


                 Copyright (c) 2010.
      Lawrence Livermore National Security, LLC.
Produced at the Lawrence Livermore National Laboratory.
                  LLNL-CODE-461231
                All rights reserved.

This file is part of LULESH, Version 1.0.
Please also read this link -- http:www.opensource.orglicenses/index.php

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the disclaimer below.

   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the disclaimer (as noted below)
     in the documentation and/or other materials provided with the
     distribution.

   * Neither the name of the LLNS/LLNL nor the names of its contributors
     may be used to endorse or promote products derived from this software
     without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY, LLC,
THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


Additional BSD Notice

1. This notice is required to be provided under our contract with the U.S.
   Department of Energy (DOE). This work was produced at Lawrence Livermore
   National Laboratory under Contract No. DE-AC52-07NA27344 with the DOE.

2. Neither the United States Government nor Lawrence Livermore National
   Security, LLC nor any of their employees, makes any warranty, express
   or implied, or assumes any liability or responsibility for the accuracy,
   completeness, or usefulness of any information, apparatus, product, or
   process disclosed, or represents that its use would not infringe
   privately-owned rights.

3. Also, reference herein to any specific commercial products, process, or
   services by trade name, trademark, manufacturer or otherwise does not
   necessarily constitute or imply its endorsement, recommendation, or
   favoring by the United States Government or Lawrence Livermore National
   Security, LLC. The views and opinions of authors expressed herein do not
   necessarily state or reflect those of the United States Government or
   Lawrence Livermore National Security, LLC, and shall not be used for
   advertising or product endorsement purposes.


*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
/* #define _OPENACCM */
#include <openacc.h>
#pragma aspen  declare param(aspen_param_sizeof_double:8)
#pragma aspen  declare param(aspen_param_sizeof_int:4)
#pragma openarc #define T_EDGEELEM 45 
#pragma openarc #define T_EDGENODES (T_EDGEELEM+1) 
#pragma openarc #define T_NUMELEM (T_EDGEELEM*T_EDGEELEM*T_EDGEELEM) 
#pragma openarc #define T_NUMNODE (T_EDGENODES*T_EDGENODES*T_EDGENODES) 
double my_timer()
{
struct timeval time;
double _ret_val_0;
gettimeofday(( & time), 0);
_ret_val_0=(time.tv_sec+(time.tv_usec/1000000.0));
return _ret_val_0;
}

enum lulesh_c_24131 { VolumeError = ( - 1), QStopError = ( - 2) };
/*  */
/* Allow flexibility for arithmetic representations */
/*  */
/* Could also support fixed point and interval arithmetic types */
/* typedef float        real4 ; */
/* typedef double       real8 ; */
/* typedef long double  real10 ;  10 bytes on x86 */
/* typedef int    Index_t ; array subscript and loop index */
/* typedef real8  Real_t ;  floating point representation */
/* typedef int    Int_t ;   integer representation */
inline float SQRT4(float arg)
{
float _ret_val_0;
_ret_val_0=sqrtf(arg);
return _ret_val_0;
}

inline double SQRT8(double arg)
{
double _ret_val_0;
#pragma aspen  control execute label(block_SQRT83) flops(1:traits(dp))
_ret_val_0=sqrt(arg);
return _ret_val_0;
}

inline long double SQRT10(long double arg)
{
long double _ret_val_0;
_ret_val_0=sqrtl(arg);
return _ret_val_0;
}

inline float CBRT4(float arg)
{
float _ret_val_0;
_ret_val_0=cbrtf(arg);
return _ret_val_0;
}

inline double CBRT8(double arg)
{
double _ret_val_0;
#pragma aspen  control execute label(block_CBRT83) flops(1:traits(dp))
_ret_val_0=cbrt(arg);
return _ret_val_0;
}

inline long double CBRT10(long double arg)
{
long double _ret_val_0;
_ret_val_0=cbrtl(arg);
return _ret_val_0;
}

inline float FABS4(float arg)
{
float _ret_val_0;
_ret_val_0=fabsf(arg);
return _ret_val_0;
}

inline double FABS8(double arg)
{
double _ret_val_0;
#pragma aspen  control execute label(block_FABS83) flops(1:traits(dp))
_ret_val_0=fabs(arg);
return _ret_val_0;
}

inline long double FABS10(long double arg)
{
long double _ret_val_0;
_ret_val_0=fabsl(arg);
return _ret_val_0;
}

/*  */
/* Allow for flexible data layout experiments by separating */
/* array interface from underlying implementation.          */
/*  */
/* struct Domain { */
/* This first implementation allows for runnable code */
/* and is not meant to be optimal. Final implementation */
/* should separate declaration and allocation phases */
/* so that allocation can be scheduled in a cache conscious */
/* manner. */
/* private: */
/*  */
/* Implementation */
/*  */
/* Node-centered */
#pragma aspen  declare data(m_x:traits(Array(m_numNode, aspen_param_sizeof_double)))
double * m_x;
/* coordinates */
#pragma aspen  declare data(m_y:traits(Array(m_numNode, aspen_param_sizeof_double)))
double * m_y;
#pragma aspen  declare data(m_z:traits(Array(m_numNode, aspen_param_sizeof_double)))
double * m_z;
#pragma aspen  declare data(m_xd:traits(Array(m_numNode, aspen_param_sizeof_double)))
double * m_xd;
/* velocities */
#pragma aspen  declare data(m_yd:traits(Array(m_numNode, aspen_param_sizeof_double)))
double * m_yd;
#pragma aspen  declare data(m_zd:traits(Array(m_numNode, aspen_param_sizeof_double)))
double * m_zd;
#pragma aspen  declare data(m_xdd:traits(Array(m_numNode, aspen_param_sizeof_double)))
double * m_xdd;
/* accelerations */
#pragma aspen  declare data(m_ydd:traits(Array(m_numNode, aspen_param_sizeof_double)))
double * m_ydd;
#pragma aspen  declare data(m_zdd:traits(Array(m_numNode, aspen_param_sizeof_double)))
double * m_zdd;
#pragma aspen  declare data(m_fx:traits(Array(m_numNode, aspen_param_sizeof_double)))
double * m_fx;
/* forces */
#pragma aspen  declare data(m_fy:traits(Array(m_numNode, aspen_param_sizeof_double)))
double * m_fy;
#pragma aspen  declare data(m_fz:traits(Array(m_numNode, aspen_param_sizeof_double)))
double * m_fz;
#pragma aspen  declare data(m_nodalMass:traits(Array(m_numNode, aspen_param_sizeof_double)))
double * m_nodalMass;
/* mass */
#pragma aspen  declare data(m_symmX:traits(Array(size_renamed, aspen_param_sizeof_int)))
int * m_symmX;
/* symmetry plane nodesets */
#pragma aspen  declare data(m_symmY:traits(Array(size_renamed, aspen_param_sizeof_int)))
int * m_symmY;
#pragma aspen  declare data(m_symmZ:traits(Array(size_renamed, aspen_param_sizeof_int)))
int * m_symmZ;
#pragma aspen  declare data(m_nodeElemCount:traits(Array(m_numNode, aspen_param_sizeof_int)))
int * m_nodeElemCount;
#pragma aspen  declare data(m_nodeElemStart:traits(Array(m_numNode, aspen_param_sizeof_int)))
int * m_nodeElemStart;
/*   Index_t m_nodeElemList ; */
int * m_nodeElemCornerList;
/* Element-centered */
#pragma aspen  declare data(m_matElemlist:traits(Array(m_numElem, aspen_param_sizeof_int)))
int * m_matElemlist;
/* material indexset */
#pragma aspen  declare data(m_nodelist:traits(Array((8*m_numElem), aspen_param_sizeof_int)))
int * m_nodelist;
/* elemToNode connectivity */
#pragma aspen  declare data(m_lxim:traits(Array(m_numElem, aspen_param_sizeof_int)))
int * m_lxim;
/* element connectivity across each face */
#pragma aspen  declare data(m_lxip:traits(Array(m_numElem, aspen_param_sizeof_int)))
int * m_lxip;
#pragma aspen  declare data(m_letam:traits(Array(m_numElem, aspen_param_sizeof_int)))
int * m_letam;
#pragma aspen  declare data(m_letap:traits(Array(m_numElem, aspen_param_sizeof_int)))
int * m_letap;
#pragma aspen  declare data(m_lzetam:traits(Array(m_numElem, aspen_param_sizeof_int)))
int * m_lzetam;
#pragma aspen  declare data(m_lzetap:traits(Array(m_numElem, aspen_param_sizeof_int)))
int * m_lzetap;
#pragma aspen  declare data(m_elemBC:traits(Array(m_numElem, aspen_param_sizeof_int)))
int * m_elemBC;
/* symmetryfree-surface flags for each elem face */
#pragma aspen  declare data(m_dxx:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_dxx;
/* principal strains -- temporary */
#pragma aspen  declare data(m_dyy:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_dyy;
#pragma aspen  declare data(m_dzz:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_dzz;
#pragma aspen  declare data(m_delv_xi:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_delv_xi;
/* velocity gradient -- temporary */
#pragma aspen  declare data(m_delv_eta:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_delv_eta;
#pragma aspen  declare data(m_delv_zeta:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_delv_zeta;
#pragma aspen  declare data(m_delx_xi:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_delx_xi;
/* coordinate gradient -- temporary */
#pragma aspen  declare data(m_delx_eta:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_delx_eta;
#pragma aspen  declare data(m_delx_zeta:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_delx_zeta;
#pragma aspen  declare data(m_e:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_e;
/* energy */
#pragma aspen  declare data(m_p:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_p;
/* pressure */
#pragma aspen  declare data(m_q:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_q;
/* q */
#pragma aspen  declare data(m_ql:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_ql;
/* linear term for q */
#pragma aspen  declare data(m_qq:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_qq;
/* quadratic term for q */
#pragma aspen  declare data(m_v:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_v;
/* relative volume */
#pragma aspen  declare data(m_volo:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_volo;
/* reference volume */
#pragma aspen  declare data(m_vnew:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_vnew;
/* new relative volume -- temporary */
#pragma aspen  declare data(m_delv:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_delv;
/* m_vnew - m_v */
#pragma aspen  declare data(m_vdov:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_vdov;
/* volume derivative over volume */
#pragma aspen  declare data(m_arealg:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_arealg;
/* characteristic length of an element */
#pragma aspen  declare data(m_ss:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_ss;
/* "sound speed" */
#pragma aspen  declare data(m_elemMass:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * m_elemMass;
/* mass */
/* Temporary variables from IntegrateStressForElems() and CalcFBHourglassForceForElems() */
#pragma aspen  declare data(fx_elem:traits(Array(m_numElem8, aspen_param_sizeof_double)))
double * fx_elem;
#pragma aspen  declare data(fy_elem:traits(Array(m_numElem8, aspen_param_sizeof_double)))
double * fy_elem;
#pragma aspen  declare data(fz_elem:traits(Array(m_numElem8, aspen_param_sizeof_double)))
double * fz_elem;
/* Temporary variables from CalcHourglassControlForElems() */
#pragma aspen  declare data(dvdx:traits(Array(m_numElem8, aspen_param_sizeof_double)))
double * dvdx;
#pragma aspen  declare data(dvdy:traits(Array(m_numElem8, aspen_param_sizeof_double)))
double * dvdy;
#pragma aspen  declare data(dvdz:traits(Array(m_numElem8, aspen_param_sizeof_double)))
double * dvdz;
#pragma aspen  declare data(x8n:traits(Array(m_numElem8, aspen_param_sizeof_double)))
double * x8n;
#pragma aspen  declare data(y8n:traits(Array(m_numElem8, aspen_param_sizeof_double)))
double * y8n;
#pragma aspen  declare data(z8n:traits(Array(m_numElem8, aspen_param_sizeof_double)))
double * z8n;
/* Temporary variables from EvalEOSForElems() */
#pragma aspen  declare data(e_old:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * e_old;
#pragma aspen  declare data(delvc:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * delvc;
#pragma aspen  declare data(p_old:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * p_old;
#pragma aspen  declare data(q_old:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * q_old;
#pragma aspen  declare data(compression:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * compression;
#pragma aspen  declare data(compHalfStep:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * compHalfStep;
#pragma aspen  declare data(qq:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * qq;
#pragma aspen  declare data(ql:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * ql;
#pragma aspen  declare data(work:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * work;
#pragma aspen  declare data(p_new:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * p_new;
#pragma aspen  declare data(e_new:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * e_new;
#pragma aspen  declare data(q_new:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * q_new;
#pragma aspen  declare data(bvc:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * bvc;
#pragma aspen  declare data(pbvc:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * pbvc;
/* Temporary variables from ApplyMaterialPropertiesForElems() */
#pragma aspen  declare data(vnewc:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * vnewc;
/* Temporary variables from CalcVolumeForceForElems() */
#pragma aspen  declare data(sigxx:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * sigxx;
#pragma aspen  declare data(sigyy:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * sigyy;
#pragma aspen  declare data(sigzz:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * sigzz;
#pragma aspen  declare data(determ:traits(Array(m_numElem, aspen_param_sizeof_double)))
double * determ;
/* Parameters */
double m_dtfixed;
/* fixed time increment */
double m_time;
/* current time */
double m_deltatime;
/* variable time increment */
double m_deltatimemultlb;
double m_deltatimemultub;
double m_stoptime;
/* end time for simulation */
double m_u_cut;
/* velocity tolerance */
double m_hgcoef;
/* hourglass control */
double m_qstop;
/* excessive q indicator */
double m_monoq_max_slope;
double m_monoq_limiter_mult;
double m_e_cut;
/* energy tolerance */
double m_p_cut;
/* pressure tolerance */
double m_ss4o3;
double m_q_cut;
/* q tolerance */
double m_v_cut;
/* relative volume tolerance */
double m_qlc_monoq;
/* linear term coef for q */
double m_qqc_monoq;
/* quadratic term coef for q */
double m_qqc;
double m_eosvmax;
double m_eosvmin;
double m_pmin;
/* pressure floor */
double m_emin;
/* energy floor */
double m_dvovmax;
/* maximum allowable volume change */
double m_refdens;
/* reference density */
double m_dtcourant;
/* courant constraint */
double m_dthydro;
/* volume change constraint */
double m_dtmax;
/* maximum allowable time increment */
int m_cycle;
/* iteration count for simulation */
/* [DEBUG] Moved from main() for easy model generation. */
#pragma aspen  declare param(edgeElems:45)
int edgeElems;
#pragma aspen  declare param(edgeNodes:(edgeElems+1))
int edgeNodes;
/* #pragma aspen declare param(m_sizeX:edgeElems) */
#pragma aspen  declare param(m_sizeX:edgeElems)
int m_sizeX;
/* X,Y,Z extent of this block */
int m_sizeY;
int m_sizeZ;
/* #pragma aspen declare param(m_numElem:T_NUMELEM) */
#pragma aspen  declare param(m_numElem:((edgeElems*edgeElems)*edgeElems))
int m_numElem;
/* ElementsNodes in this domain */
/* #pragma aspen declare param(m_numElem8:m_numElem8) */
#pragma aspen  declare param(m_numElem8:(m_numElem*8))
int m_numElem8;
/* #pragma aspen declare param(m_numNode:T_NUMNODE) */
#pragma aspen  declare param(m_numNode:((edgeNodes*edgeNodes)*edgeNodes))
int m_numNode;
#pragma aspen  declare param(m_nCorner:m_numElem8)
int m_nCorner;
/* public: */
/*  */
/* Allocation */
/*  */
void AllocateNodalPersistent(size_t m_numNode)
{
m_x=((double *)malloc((m_numNode*sizeof (double))));
m_y=((double *)malloc((m_numNode*sizeof (double))));
m_z=((double *)malloc((m_numNode*sizeof (double))));
m_xd=((double *)calloc(m_numNode, sizeof (double)));
m_yd=((double *)calloc(m_numNode, sizeof (double)));
m_zd=((double *)calloc(m_numNode, sizeof (double)));
m_xdd=((double *)calloc(m_numNode, sizeof (double)));
m_ydd=((double *)calloc(m_numNode, sizeof (double)));
m_zdd=((double *)calloc(m_numNode, sizeof (double)));
m_fx=((double *)malloc((m_numNode*sizeof (double))));
m_fy=((double *)malloc((m_numNode*sizeof (double))));
m_fz=((double *)malloc((m_numNode*sizeof (double))));
m_nodalMass=((double *)calloc(m_numNode, sizeof (double)));
return ;
}

void AllocateElemPersistent(size_t m_numElem)
{
int i;
m_matElemlist=((int *)malloc((m_numElem*sizeof (int))));
m_nodelist=((int *)malloc(((8*m_numElem)*sizeof (int))));
m_lxim=((int *)malloc((m_numElem*sizeof (int))));
m_lxip=((int *)malloc((m_numElem*sizeof (int))));
m_letam=((int *)malloc((m_numElem*sizeof (int))));
m_letap=((int *)malloc((m_numElem*sizeof (int))));
m_lzetam=((int *)malloc((m_numElem*sizeof (int))));
m_lzetap=((int *)malloc((m_numElem*sizeof (int))));
m_elemBC=((int *)malloc((m_numElem*sizeof (int))));
m_e=((double *)calloc(m_numElem, sizeof (double)));
m_p=((double *)calloc(m_numElem, sizeof (double)));
m_q=((double *)malloc((m_numElem*sizeof (double))));
m_ql=((double *)malloc((m_numElem*sizeof (double))));
m_qq=((double *)malloc((m_numElem*sizeof (double))));
m_v=((double *)malloc((m_numElem*sizeof (double))));
for (i=0; i<m_numElem;  ++ i)
{
m_v[i]=1.0;
}
m_volo=((double *)malloc((m_numElem*sizeof (double))));
m_delv=((double *)malloc((m_numElem*sizeof (double))));
m_vdov=((double *)malloc((m_numElem*sizeof (double))));
m_arealg=((double *)malloc((m_numElem*sizeof (double))));
m_ss=((double *)malloc((m_numElem*sizeof (double))));
m_elemMass=((double *)malloc((m_numElem*sizeof (double))));
return ;
}

/* Temporaries should not be initialized in bulk but */
/* this is a runnable placeholder for now */
void AllocateElemTemporary(size_t m_numElem)
{
m_dxx=((double *)malloc((m_numElem*sizeof (double))));
m_dyy=((double *)malloc((m_numElem*sizeof (double))));
m_dzz=((double *)malloc((m_numElem*sizeof (double))));
m_delv_xi=((double *)malloc((m_numElem*sizeof (double))));
m_delv_eta=((double *)malloc((m_numElem*sizeof (double))));
m_delv_zeta=((double *)malloc((m_numElem*sizeof (double))));
m_delx_xi=((double *)malloc((m_numElem*sizeof (double))));
m_delx_eta=((double *)malloc((m_numElem*sizeof (double))));
m_delx_zeta=((double *)malloc((m_numElem*sizeof (double))));
m_vnew=((double *)malloc((m_numElem*sizeof (double))));
return ;
}

void AllocateNodesets(size_t size_renamed)
{
#pragma aspen  declare param(size_renamed:((edgeElems+1)*(edgeElems+1)))
m_symmX=((int *)malloc((size_renamed*sizeof (int))));
m_symmY=((int *)malloc((size_renamed*sizeof (int))));
m_symmZ=((int *)malloc((size_renamed*sizeof (int))));
return ;
}

void AllocateNodeElemIndexes()
{
int m;
int i;
int j;
int clSize;
/* set up node-centered indexing of elements */
m_nodeElemCount=((int *)malloc((m_numNode*sizeof (int))));
for (i=0; i<m_numNode;  ++ i)
{
m_nodeElemCount[i]=0;
}
for (i=0; i<m_numElem;  ++ i)
{
int * nl;
nl= & m_nodelist[(8*i)];
for (j=0; j<8;  ++ j)
{
 ++ m_nodeElemCount[nl[j]];
}
}
m_nodeElemStart=((int *)malloc((m_numNode*sizeof (int))));
m_nodeElemStart[0]=0;
for (i=1; i<m_numNode;  ++ i)
{
m_nodeElemStart[i]=(m_nodeElemStart[(i-1)]+m_nodeElemCount[(i-1)]);
}
m_nCorner=(m_nodeElemStart[(m_numNode-1)]+m_nodeElemCount[(m_numNode-1)]);
/*       m_nodeElemList.resize(nodeElemStart(m_numNode-1) + */
/*                             nodeElemCount(m_numNode-1)); */
#pragma aspen  declare data(m_nodeElemCornerList:traits(Array(m_nCorner, aspen_param_int)))
m_nodeElemCornerList=((int *)malloc(((m_nodeElemStart[(m_numNode-1)]+m_nodeElemCount[(m_numNode-1)])*sizeof (int))));
for (i=0; i<m_numNode;  ++ i)
{
m_nodeElemCount[i]=0;
}
for (i=0; i<m_numElem;  ++ i)
{
int * nl;
nl= & m_nodelist[(8*i)];
for (j=0; j<8;  ++ j)
{
int m;
m=nl[j];
int k;
k=(i*8)+j;
int offset;
offset=m_nodeElemStart[m]+m_nodeElemCount[m];
/*             nodeElemList(offset) = i; */
m_nodeElemCornerList[offset]=k;
 ++ m_nodeElemCount[m];
}
}
clSize=(m_nodeElemStart[(m_numNode-1)]+m_nodeElemCount[(m_numNode-1)]);
#pragma aspen  control ignore
for (i=0; i<clSize;  ++ i)
{
int clv;
clv=m_nodeElemCornerList[i];
if ((clv<0)||(clv>(m_numElem*8)))
{
fprintf(stderr, "AllocateNodeElemIndexes(): nodeElemCornerList entry out of range!\n");
exit(1);
}
}
return ;
}

/* } domain ; */
double *Allocate(size_t size)
{
double * _ret_val_0;
_ret_val_0=((double *)malloc((sizeof (double)*size)));
return _ret_val_0;
}

void Release(double * * pHalfStep)
{
#pragma aspen  control label(block_Release1964) probability(1) flops(1:traits(dp)) loads((1*aspen_param_sizeof_double):from(pHalfStep))
if (( * pHalfStep)!=0)
{
#pragma aspen  control execute label(block_Release1) stores((1*aspen_param_sizeof_double):to(pHalfStep))
free(( * pHalfStep));
#pragma aspen  control execute label(block_Release2) stores((1*aspen_param_sizeof_double):to(pHalfStep))
( * pHalfStep)=0;
}
return ;
}

void AllocateTemporary(size_t m_numElem8)
{
fx_elem=Allocate(m_numElem8);
fy_elem=Allocate(m_numElem8);
fz_elem=Allocate(m_numElem8);
dvdx=Allocate(m_numElem8);
dvdy=Allocate(m_numElem8);
dvdz=Allocate(m_numElem8);
x8n=Allocate(m_numElem8);
y8n=Allocate(m_numElem8);
z8n=Allocate(m_numElem8);
return ;
}

void AllocateTemporary2(size_t m_numElem)
{
e_old=Allocate(m_numElem);
delvc=Allocate(m_numElem);
p_old=Allocate(m_numElem);
q_old=Allocate(m_numElem);
compression=Allocate(m_numElem);
compHalfStep=Allocate(m_numElem);
qq=Allocate(m_numElem);
ql=Allocate(m_numElem);
work=Allocate(m_numElem);
p_new=Allocate(m_numElem);
e_new=Allocate(m_numElem);
q_new=Allocate(m_numElem);
bvc=Allocate(m_numElem);
pbvc=Allocate(m_numElem);
vnewc=Allocate(m_numElem);
sigxx=Allocate(m_numElem);
sigyy=Allocate(m_numElem);
sigzz=Allocate(m_numElem);
determ=Allocate(m_numElem);
return ;
}

/* Stuff needed for boundary conditions */
/* 2 BCs on each of 6 hexahedral faces (12 bits) */
static inline void TimeIncrement()
{
double targetdt;
#pragma aspen  control execute label(block_TimeIncrement2) flops(1:traits(dp))
targetdt=m_stoptime-m_time;
/* [DEBUG] Current ASPEN does not accept "<=" operator. */
#pragma aspen  control label(block_TimeIncrement451) probability(1) flops(1:traits(dp), 1:traits(integer))
if ((m_dtfixed<=0.0)&&(m_cycle!=0))
{
double ratio;
double olddt;
#pragma aspen  control ignore
olddt=m_deltatime;
/* This will require a reduction in parallel */
double newdt = 1.0E20;
#pragma aspen  control label(block_TimeIncrement457) probability(1) flops(1:traits(dp))
if (m_dtcourant<newdt)
{
#pragma aspen  control execute label(block_TimeIncrement14) flops(1:traits(dp))
newdt=(m_dtcourant/2.0);
}
#pragma aspen  control label(block_TimeIncrement459) probability(1) flops(1:traits(dp))
if (m_dthydro<newdt)
{
#pragma aspen  control execute label(block_TimeIncrement16) flops(2:traits(dp))
newdt=((m_dthydro*2.0)/3.0);
}
#pragma aspen  control execute label(block_TimeIncrement17) flops(1:traits(dp))
ratio=(newdt/olddt);
#pragma aspen  control execute label(block_TimeIncrement462) flops(3:traits(dp))
if (ratio>=1.0)
{
if (ratio<m_deltatimemultlb)
{
newdt=olddt;
}
else
{
if (ratio>m_deltatimemultub)
{
newdt=(olddt*m_deltatimemultub);
}
}
}
#pragma aspen  control label(block_TimeIncrement19) if(newdt>m_dtmax) flops(1:traits(dp))
if (newdt>m_dtmax)
{
#pragma aspen  control ignore
newdt=m_dtmax;
}
#pragma aspen  control ignore
m_deltatime=newdt;
}
/* TRY TO PREVENT VERY SMALL SCALING ON THE NEXT CYCLE */
#pragma aspen  control execute label(block_TimeIncrement467) flops(6:traits(dp))
if ((targetdt>m_deltatime)&&(targetdt<((4.0*m_deltatime)/3.0)))
{
targetdt=((2.0*m_deltatime)/3.0);
}
#pragma aspen  control ignore
if (targetdt<m_deltatime)
{
m_deltatime=targetdt;
}
#pragma aspen  control execute label(block_TimeIncrement25) flops(1:traits(dp))
m_time+=m_deltatime;
#pragma aspen  control execute label(block_TimeIncrement26) flops(1:traits(integer))
 ++ m_cycle;
return ;
}

static inline void InitStressTermsForElems(int numElem_CalcVolumeForceForElems, double sigxx[((45*45)*45)], double sigyy[((45*45)*45)], double sigzz[((45*45)*45)], double m_p[((45*45)*45)], double m_q[((45*45)*45)])
{
/*  */
/* pull in the stresses appropriate to the hydro integration */
/*  */
int i;
#pragma acc  parallel loop gang worker independent present(m_p, m_q, sigxx, sigyy, sigzz) private(i) firstprivate(numElem_CalcVolumeForceForElems)
#pragma aspen  control label(block_InitStressTermsForElems6) loop(numElem_CalcVolumeForceForElems) parallelism(numElem_CalcVolumeForceForElems) flops(1:traits(integer))
for (i=0; i<numElem_CalcVolumeForceForElems;  ++ i)
{
#pragma aspen  control execute label(block_InitStressTermsForElems7) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_p):traits(stride(1)), (1*aspen_param_sizeof_double):from(m_q):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(sigxx):traits(stride(1)), (1*aspen_param_sizeof_double):to(sigyy):traits(stride(1)), (1*aspen_param_sizeof_double):to(sigzz):traits(stride(1)))
sigxx[i]=(sigyy[i]=(sigzz[i]=(( - m_p[i])-m_q[i])));
}
return ;
}

static inline void CalcElemShapeFunctionDerivatives(const double * const x, const double * const y, const double * const z, double b[][8], double * const volume)
{
const double x0 = x[0];
const double x1 = x[1];
const double x2 = x[2];
const double x3 = x[3];
const double x4 = x[4];
const double x5 = x[5];
const double x6 = x[6];
const double x7 = x[7];
const double y0 = y[0];
const double y1 = y[1];
const double y2 = y[2];
const double y3 = y[3];
const double y4 = y[4];
const double y5 = y[5];
const double y6 = y[6];
const double y7 = y[7];
const double z0 = z[0];
const double z1 = z[1];
const double z2 = z[2];
const double z3 = z[3];
const double z4 = z[4];
const double z5 = z[5];
const double z6 = z[6];
const double z7 = z[7];
double fjxxi;
double fjxet;
double fjxze;
double fjyxi;
double fjyet;
double fjyze;
double fjzxi;
double fjzet;
double fjzze;
double cjxxi;
double cjxet;
double cjxze;
double cjyxi;
double cjyet;
double cjyze;
double cjzxi;
double cjzet;
double cjzze;
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives84) flops(8:traits(dp))
fjxxi=(0.125*((((x6-x0)+(x5-x3))-(x7-x1))-(x4-x2)));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives85) flops(8:traits(dp))
fjxet=(0.125*((((x6-x0)-(x5-x3))+(x7-x1))-(x4-x2)));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives86) flops(8:traits(dp))
fjxze=(0.125*((((x6-x0)+(x5-x3))+(x7-x1))+(x4-x2)));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives87) flops(8:traits(dp))
fjyxi=(0.125*((((y6-y0)+(y5-y3))-(y7-y1))-(y4-y2)));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives88) flops(8:traits(dp))
fjyet=(0.125*((((y6-y0)-(y5-y3))+(y7-y1))-(y4-y2)));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives89) flops(8:traits(dp))
fjyze=(0.125*((((y6-y0)+(y5-y3))+(y7-y1))+(y4-y2)));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives90) flops(8:traits(dp))
fjzxi=(0.125*((((z6-z0)+(z5-z3))-(z7-z1))-(z4-z2)));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives91) flops(8:traits(dp))
fjzet=(0.125*((((z6-z0)-(z5-z3))+(z7-z1))-(z4-z2)));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives92) flops(8:traits(dp))
fjzze=(0.125*((((z6-z0)+(z5-z3))+(z7-z1))+(z4-z2)));
/* compute cofactors */
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives94) flops(3:traits(dp))
cjxxi=((fjyet*fjzze)-(fjzet*fjyze));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives95) flops(3:traits(dp))
cjxet=(( - (fjyxi*fjzze))+(fjzxi*fjyze));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives96) flops(3:traits(dp))
cjxze=((fjyxi*fjzet)-(fjzxi*fjyet));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives97) flops(3:traits(dp))
cjyxi=(( - (fjxet*fjzze))+(fjzet*fjxze));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives98) flops(3:traits(dp))
cjyet=((fjxxi*fjzze)-(fjzxi*fjxze));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives99) flops(3:traits(dp))
cjyze=(( - (fjxxi*fjzet))+(fjzxi*fjxet));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives100) flops(3:traits(dp))
cjzxi=((fjxet*fjyze)-(fjyet*fjxze));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives101) flops(3:traits(dp))
cjzet=(( - (fjxxi*fjyze))+(fjyxi*fjxze));
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives102) flops(3:traits(dp))
cjzze=((fjxxi*fjyet)-(fjyxi*fjxet));
/*
calculate partials :
     this need only be done for l = 0,1,2,3   since , by symmetry ,
     (6,7,4,5) = - (0,1,2,3) .
 
*/
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives104) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[0][0]=((( - cjxxi)-cjxet)-cjxze);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives105) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[0][1]=((cjxxi-cjxet)-cjxze);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives106) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[0][2]=((cjxxi+cjxet)-cjxze);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives107) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[0][3]=((( - cjxxi)+cjxet)-cjxze);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives108) loads((1*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[0][4]=( - b[0][2]);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives109) loads((1*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[0][5]=( - b[0][3]);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives110) loads((1*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[0][6]=( - b[0][0]);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives111) loads((1*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[0][7]=( - b[0][1]);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives112) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[1][0]=((( - cjyxi)-cjyet)-cjyze);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives113) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[1][1]=((cjyxi-cjyet)-cjyze);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives114) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[1][2]=((cjyxi+cjyet)-cjyze);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives115) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[1][3]=((( - cjyxi)+cjyet)-cjyze);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives116) loads((1*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[1][4]=( - b[1][2]);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives117) loads((1*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[1][5]=( - b[1][3]);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives118) loads((1*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[1][6]=( - b[1][0]);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives119) loads((1*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[1][7]=( - b[1][1]);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives120) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[2][0]=((( - cjzxi)-cjzet)-cjzze);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives121) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[2][1]=((cjzxi-cjzet)-cjzze);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives122) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[2][2]=((cjzxi+cjzet)-cjzze);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives123) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[2][3]=((( - cjzxi)+cjzet)-cjzze);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives124) loads((1*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[2][4]=( - b[2][2]);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives125) loads((1*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[2][5]=( - b[2][3]);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives126) loads((1*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[2][6]=( - b[2][0]);
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives127) loads((1*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
b[2][7]=( - b[2][1]);
/* calculate jacobian determinant (volume) */
#pragma aspen  control execute label(block_CalcElemShapeFunctionDerivatives129) flops(6:traits(dp)) stores((1*aspen_param_sizeof_double))
( * volume)=(8.0*(((fjxet*cjxet)+(fjyet*cjyet))+(fjzet*cjzet)));
return ;
}

static inline void SumElemFaceNormal(double * normalX0, double * normalY0, double * normalZ0, double * normalX1, double * normalY1, double * normalZ1, double * normalX2, double * normalY2, double * normalZ2, double * normalX3, double * normalY3, double * normalZ3, const double x0, const double y0, const double z0, const double x1, const double y1, const double z1, const double x2, const double y2, const double z2, const double x3, const double y3, const double z3)
{
double bisectX0;
#pragma aspen  control execute label(block_SumElemFaceNormal14) flops(4:traits(dp))
bisectX0=0.5*(((x3+x2)-x1)-x0);
double bisectY0;
#pragma aspen  control execute label(block_SumElemFaceNormal17) flops(4:traits(dp))
bisectY0=0.5*(((y3+y2)-y1)-y0);
double bisectZ0;
#pragma aspen  control execute label(block_SumElemFaceNormal20) flops(4:traits(dp))
bisectZ0=0.5*(((z3+z2)-z1)-z0);
double bisectX1;
#pragma aspen  control execute label(block_SumElemFaceNormal23) flops(4:traits(dp))
bisectX1=0.5*(((x2+x1)-x3)-x0);
double bisectY1;
#pragma aspen  control execute label(block_SumElemFaceNormal26) flops(4:traits(dp))
bisectY1=0.5*(((y2+y1)-y3)-y0);
double bisectZ1;
#pragma aspen  control execute label(block_SumElemFaceNormal29) flops(4:traits(dp))
bisectZ1=0.5*(((z2+z1)-z3)-z0);
double areaX;
#pragma aspen  control execute label(block_SumElemFaceNormal32) flops(4:traits(dp))
areaX=0.25*((bisectY0*bisectZ1)-(bisectZ0*bisectY1));
double areaY;
#pragma aspen  control execute label(block_SumElemFaceNormal35) flops(4:traits(dp))
areaY=0.25*((bisectZ0*bisectX1)-(bisectX0*bisectZ1));
double areaZ;
#pragma aspen  control execute label(block_SumElemFaceNormal38) flops(4:traits(dp))
areaZ=0.25*((bisectX0*bisectY1)-(bisectY0*bisectX1));
#pragma aspen  control execute label(block_SumElemFaceNormal39) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * normalX0)+=areaX;
#pragma aspen  control execute label(block_SumElemFaceNormal40) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * normalX1)+=areaX;
#pragma aspen  control execute label(block_SumElemFaceNormal41) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * normalX2)+=areaX;
#pragma aspen  control execute label(block_SumElemFaceNormal42) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * normalX3)+=areaX;
#pragma aspen  control execute label(block_SumElemFaceNormal43) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * normalY0)+=areaY;
#pragma aspen  control execute label(block_SumElemFaceNormal44) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * normalY1)+=areaY;
#pragma aspen  control execute label(block_SumElemFaceNormal45) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * normalY2)+=areaY;
#pragma aspen  control execute label(block_SumElemFaceNormal46) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * normalY3)+=areaY;
#pragma aspen  control execute label(block_SumElemFaceNormal47) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * normalZ0)+=areaZ;
#pragma aspen  control execute label(block_SumElemFaceNormal48) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * normalZ1)+=areaZ;
#pragma aspen  control execute label(block_SumElemFaceNormal49) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * normalZ2)+=areaZ;
#pragma aspen  control execute label(block_SumElemFaceNormal50) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * normalZ3)+=areaZ;
return ;
}

static inline void CalcElemNodeNormals(double pfx[8], double pfy[8], double pfz[8], const double x[8], const double y[8], const double z[8])
{
int i;
#pragma aspen  control label(block_CalcElemNodeNormals2) loop(8) flops(1:traits(integer))
for (i=0; i<8;  ++ i)
{
#pragma aspen  control execute label(block_CalcElemNodeNormals3) stores(((1*aspen_param_sizeof_double)*8):traits(stride(1)))
pfx[i]=0.0;
#pragma aspen  control execute label(block_CalcElemNodeNormals4) stores(((1*aspen_param_sizeof_double)*8):traits(stride(1)))
pfy[i]=0.0;
#pragma aspen  control execute label(block_CalcElemNodeNormals5) stores(((1*aspen_param_sizeof_double)*8):traits(stride(1)))
pfz[i]=0.0;
}
/* evaluate face one: nodes 0, 1, 2, 3 */
#pragma aspen  control label(block_CalcElemNodeNormals7) loads((16*aspen_param_sizeof_double):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
SumElemFaceNormal(( & pfx[0]), ( & pfy[0]), ( & pfz[0]), ( & pfx[1]), ( & pfy[1]), ( & pfz[1]), ( & pfx[2]), ( & pfy[2]), ( & pfz[2]), ( & pfx[3]), ( & pfy[3]), ( & pfz[3]), x[0], y[0], z[0], x[1], y[1], z[1], x[2], y[2], z[2], x[3], y[3], z[3]);
/* evaluate face two: nodes 0, 4, 5, 1 */
#pragma aspen  control label(block_CalcElemNodeNormals9) loads((16*aspen_param_sizeof_double):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
SumElemFaceNormal(( & pfx[0]), ( & pfy[0]), ( & pfz[0]), ( & pfx[4]), ( & pfy[4]), ( & pfz[4]), ( & pfx[5]), ( & pfy[5]), ( & pfz[5]), ( & pfx[1]), ( & pfy[1]), ( & pfz[1]), x[0], y[0], z[0], x[4], y[4], z[4], x[5], y[5], z[5], x[1], y[1], z[1]);
/* evaluate face three: nodes 1, 5, 6, 2 */
#pragma aspen  control label(block_CalcElemNodeNormals11) loads((16*aspen_param_sizeof_double):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
SumElemFaceNormal(( & pfx[1]), ( & pfy[1]), ( & pfz[1]), ( & pfx[5]), ( & pfy[5]), ( & pfz[5]), ( & pfx[6]), ( & pfy[6]), ( & pfz[6]), ( & pfx[2]), ( & pfy[2]), ( & pfz[2]), x[1], y[1], z[1], x[5], y[5], z[5], x[6], y[6], z[6], x[2], y[2], z[2]);
/* evaluate face four: nodes 2, 6, 7, 3 */
#pragma aspen  control label(block_CalcElemNodeNormals13) loads((16*aspen_param_sizeof_double):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
SumElemFaceNormal(( & pfx[2]), ( & pfy[2]), ( & pfz[2]), ( & pfx[6]), ( & pfy[6]), ( & pfz[6]), ( & pfx[7]), ( & pfy[7]), ( & pfz[7]), ( & pfx[3]), ( & pfy[3]), ( & pfz[3]), x[2], y[2], z[2], x[6], y[6], z[6], x[7], y[7], z[7], x[3], y[3], z[3]);
/* evaluate face five: nodes 3, 7, 4, 0 */
#pragma aspen  control label(block_CalcElemNodeNormals15) loads((16*aspen_param_sizeof_double):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
SumElemFaceNormal(( & pfx[3]), ( & pfy[3]), ( & pfz[3]), ( & pfx[7]), ( & pfy[7]), ( & pfz[7]), ( & pfx[4]), ( & pfy[4]), ( & pfz[4]), ( & pfx[0]), ( & pfy[0]), ( & pfz[0]), x[3], y[3], z[3], x[7], y[7], z[7], x[4], y[4], z[4], x[0], y[0], z[0]);
/* evaluate face six: nodes 4, 7, 6, 5 */
#pragma aspen  control label(block_CalcElemNodeNormals17) loads((16*aspen_param_sizeof_double):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
SumElemFaceNormal(( & pfx[4]), ( & pfy[4]), ( & pfz[4]), ( & pfx[7]), ( & pfy[7]), ( & pfz[7]), ( & pfx[6]), ( & pfy[6]), ( & pfz[6]), ( & pfx[5]), ( & pfy[5]), ( & pfz[5]), x[4], y[4], z[4], x[7], y[7], z[7], x[6], y[6], z[6], x[5], y[5], z[5]);
return ;
}

static inline void SumElemStressesToNodeForces(const double B[][8], const double stress_xx, const double stress_yy, const double stress_zz, double * const fx_elem, double * const fy_elem, double * const fz_elem)
{
double pfx0;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces5) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfx0=B[0][0];
double pfx1;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces8) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfx1=B[0][1];
double pfx2;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces11) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfx2=B[0][2];
double pfx3;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces14) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfx3=B[0][3];
double pfx4;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces17) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfx4=B[0][4];
double pfx5;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces20) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfx5=B[0][5];
double pfx6;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces23) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfx6=B[0][6];
double pfx7;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces26) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfx7=B[0][7];
double pfy0;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces29) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfy0=B[1][0];
double pfy1;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces32) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfy1=B[1][1];
double pfy2;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces35) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfy2=B[1][2];
double pfy3;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces38) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfy3=B[1][3];
double pfy4;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces41) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfy4=B[1][4];
double pfy5;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces44) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfy5=B[1][5];
double pfy6;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces47) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfy6=B[1][6];
double pfy7;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces50) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfy7=B[1][7];
double pfz0;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces53) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfz0=B[2][0];
double pfz1;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces56) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfz1=B[2][1];
double pfz2;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces59) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfz2=B[2][2];
double pfz3;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces62) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfz3=B[2][3];
double pfz4;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces65) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfz4=B[2][4];
double pfz5;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces68) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfz5=B[2][5];
double pfz6;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces71) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfz6=B[2][6];
double pfz7;
#pragma aspen  control execute label(block_SumElemStressesToNodeForces74) loads((1*aspen_param_sizeof_double):traits(stride(0)))
pfz7=B[2][7];
#pragma aspen  control execute label(block_SumElemStressesToNodeForces75) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fx_elem):traits(stride(0)))
fx_elem[0]=( - (stress_xx*pfx0));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces76) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fx_elem):traits(stride(0)))
fx_elem[1]=( - (stress_xx*pfx1));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces77) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fx_elem):traits(stride(0)))
fx_elem[2]=( - (stress_xx*pfx2));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces78) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fx_elem):traits(stride(0)))
fx_elem[3]=( - (stress_xx*pfx3));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces79) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fx_elem):traits(stride(0)))
fx_elem[4]=( - (stress_xx*pfx4));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces80) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fx_elem):traits(stride(0)))
fx_elem[5]=( - (stress_xx*pfx5));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces81) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fx_elem):traits(stride(0)))
fx_elem[6]=( - (stress_xx*pfx6));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces82) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fx_elem):traits(stride(0)))
fx_elem[7]=( - (stress_xx*pfx7));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces83) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fy_elem):traits(stride(0)))
fy_elem[0]=( - (stress_yy*pfy0));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces84) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fy_elem):traits(stride(0)))
fy_elem[1]=( - (stress_yy*pfy1));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces85) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fy_elem):traits(stride(0)))
fy_elem[2]=( - (stress_yy*pfy2));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces86) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fy_elem):traits(stride(0)))
fy_elem[3]=( - (stress_yy*pfy3));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces87) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fy_elem):traits(stride(0)))
fy_elem[4]=( - (stress_yy*pfy4));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces88) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fy_elem):traits(stride(0)))
fy_elem[5]=( - (stress_yy*pfy5));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces89) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fy_elem):traits(stride(0)))
fy_elem[6]=( - (stress_yy*pfy6));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces90) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fy_elem):traits(stride(0)))
fy_elem[7]=( - (stress_yy*pfy7));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces91) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fz_elem):traits(stride(0)))
fz_elem[0]=( - (stress_zz*pfz0));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces92) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fz_elem):traits(stride(0)))
fz_elem[1]=( - (stress_zz*pfz1));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces93) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fz_elem):traits(stride(0)))
fz_elem[2]=( - (stress_zz*pfz2));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces94) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fz_elem):traits(stride(0)))
fz_elem[3]=( - (stress_zz*pfz3));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces95) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fz_elem):traits(stride(0)))
fz_elem[4]=( - (stress_zz*pfz4));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces96) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fz_elem):traits(stride(0)))
fz_elem[5]=( - (stress_zz*pfz5));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces97) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fz_elem):traits(stride(0)))
fz_elem[6]=( - (stress_zz*pfz6));
#pragma aspen  control execute label(block_SumElemStressesToNodeForces98) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(fz_elem):traits(stride(0)))
fz_elem[7]=( - (stress_zz*pfz7));
return ;
}

static inline void IntegrateStressForElems(int numElem_CalcVolumeForceForElems, double sigxx[((45*45)*45)], double sigyy[((45*45)*45)], double sigzz[((45*45)*45)], double determ[((45*45)*45)], int p_nodelist[(((45*45)*45)*8)], double m_x[(((45+1)*(45+1))*(45+1))], double m_y[(((45+1)*(45+1))*(45+1))], double m_z[(((45+1)*(45+1))*(45+1))], int m_nodeElemCount[(((45+1)*(45+1))*(45+1))], int m_nodeElemStart[(((45+1)*(45+1))*(45+1))], int m_nodeElemCornerList[(((45*45)*45)*8)], double m_fx[(((45+1)*(45+1))*(45+1))], double m_fy[(((45+1)*(45+1))*(45+1))], double m_fz[(((45+1)*(45+1))*(45+1))])
{
int k;
int lnode;
int gnode;
int i;
/*

   Real_tfx_elem = Allocate(numElem8) ;
   Real_t *fy_elem = Allocate(numElem8) ;
   Real_t *fz_elem = Allocate(numElem8) ;

*/
/* loop over all elements */
#pragma acc  parallel loop gang worker independent present(determ, fx_elem, fy_elem, fz_elem, m_x, m_y, m_z, p_nodelist, sigxx, sigyy, sigzz) private(k) firstprivate(lnode, numElem_CalcVolumeForceForElems)
#pragma aspen  control label(block_IntegrateStressForElems11) loop(numElem_CalcVolumeForceForElems) parallelism(numElem_CalcVolumeForceForElems) flops(1:traits(integer))
for (k=0; k<numElem_CalcVolumeForceForElems;  ++ k)
{
double B[3][8];
/* shape function derivatives */
double x_local[8];
double y_local[8];
double z_local[8];
#pragma aspen  declare data(elemNodes:traits(Array(8, aspen_param_int)))
const int * const elemNodes =  & p_nodelist[(8*k)];
/* get nodal coordinates from global arrays and copy into local arrays. */
#pragma aspen  control label(block_IntegrateStressForElems20) loop(8) flops(1:traits(integer))
for (lnode=0; lnode<8;  ++ lnode)
{
int gnode;
#pragma aspen  control execute label(block_IntegrateStressForElems23) loads(((1*aspen_param_sizeof_int)*8):from(elemNodes):traits(stride(1)))
gnode=elemNodes[lnode];
#pragma aspen  control execute label(block_IntegrateStressForElems24) loads(((1*aspen_param_sizeof_double)*8):from(m_x))
x_local[lnode]=m_x[gnode];
#pragma aspen  control execute label(block_IntegrateStressForElems25) loads(((1*aspen_param_sizeof_double)*8):from(m_y))
y_local[lnode]=m_y[gnode];
#pragma aspen  control execute label(block_IntegrateStressForElems26) loads(((1*aspen_param_sizeof_double)*8):from(m_z))
z_local[lnode]=m_z[gnode];
}
/* Volume calculation involves extra work for numerical consistency. */
#pragma aspen  control label(block_IntegrateStressForElems28) loads((1*aspen_param_sizeof_double):from(determ):traits(stride(1)))
CalcElemShapeFunctionDerivatives(x_local, y_local, z_local, B, ( & determ[k]));
CalcElemNodeNormals(B[0], B[1], B[2], x_local, y_local, z_local);
#pragma aspen  control label(block_IntegrateStressForElems30) flops(3:traits(integer)) loads((1*aspen_param_sizeof_double):from(fx_elem), (1*aspen_param_sizeof_double):from(fy_elem), (1*aspen_param_sizeof_double):from(fz_elem), (1*aspen_param_sizeof_double):from(sigxx):traits(stride(1)), (1*aspen_param_sizeof_double):from(sigyy):traits(stride(1)), (1*aspen_param_sizeof_double):from(sigzz):traits(stride(1)))
SumElemStressesToNodeForces(B, sigxx[k], sigyy[k], sigzz[k], ( & fx_elem[(k*8)]), ( & fy_elem[(k*8)]), ( & fz_elem[(k*8)]));
}
{
int numNode;
#pragma aspen  control ignore
numNode=m_numNode;
#pragma acc  kernels loop gang worker independent copy(i, numNode) present(fx_elem, fy_elem, fz_elem, m_fx, m_fy, m_fz, m_nodeElemCornerList, m_nodeElemCount, m_nodeElemStart) private(gnode)
#pragma aspen  control label(block_IntegrateStressForElems35) loop(m_numNode) parallelism(m_numNode) flops(1:traits(integer))
for (gnode=0; gnode<numNode;  ++ gnode)
{
int count;
#pragma aspen  control execute label(block_IntegrateStressForElems38) loads((1*aspen_param_sizeof_int):from(m_nodeElemCount):traits(stride(1)))
count=m_nodeElemCount[gnode];
int start;
#pragma aspen  control execute label(block_IntegrateStressForElems41) loads((1*aspen_param_sizeof_int):from(m_nodeElemStart):traits(stride(1)))
start=m_nodeElemStart[gnode];
double fx = 0.0;
double fy = 0.0;
double fz = 0.0;
#pragma aspen  declare param(aspen_param_elemCount:1)
#pragma aspen  control label(block_IntegrateStressForElems775) loop(aspen_param_elemCount) flops(1:traits(integer))
for (i=0; i<count;  ++ i)
{
int elem;
#pragma aspen  control execute label(block_IntegrateStressForElems52) flops((1*aspen_param_elemCount):traits(integer)) loads(((1*aspen_param_sizeof_int)*aspen_param_elemCount):from(m_nodeElemCornerList):traits(stride(1)))
elem=m_nodeElemCornerList[(start+i)];
#pragma aspen  control execute label(block_IntegrateStressForElems53) flops((1*aspen_param_elemCount):traits(dp)) loads(((1*aspen_param_sizeof_double)*aspen_param_elemCount):from(fx_elem))
fx+=fx_elem[elem];
#pragma aspen  control execute label(block_IntegrateStressForElems54) flops((1*aspen_param_elemCount):traits(dp)) loads(((1*aspen_param_sizeof_double)*aspen_param_elemCount):from(fy_elem))
fy+=fy_elem[elem];
#pragma aspen  control execute label(block_IntegrateStressForElems55) flops((1*aspen_param_elemCount):traits(dp)) loads(((1*aspen_param_sizeof_double)*aspen_param_elemCount):from(fz_elem))
fz+=fz_elem[elem];
}
#pragma aspen  control execute label(block_IntegrateStressForElems56) stores((1*aspen_param_sizeof_double):to(m_fx):traits(stride(1)))
m_fx[gnode]=fx;
#pragma aspen  control execute label(block_IntegrateStressForElems57) stores((1*aspen_param_sizeof_double):to(m_fy):traits(stride(1)))
m_fy[gnode]=fy;
#pragma aspen  control execute label(block_IntegrateStressForElems58) stores((1*aspen_param_sizeof_double):to(m_fz):traits(stride(1)))
m_fz[gnode]=fz;
}
}
/*

  Release(&fz_elem) ;
  Release(&fy_elem) ;
  Release(&fx_elem) ;

*/
return ;
}

static inline void CollectDomainNodesToElemNodes(const int * elemToNode_CalcHourglassControlForElems, double elemX[8], double elemY[8], double elemZ[8])
{
int nd0i;
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes2) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcHourglassControlForElems):traits(stride(0)))
nd0i=elemToNode_CalcHourglassControlForElems[0];
int nd1i;
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes5) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcHourglassControlForElems):traits(stride(0)))
nd1i=elemToNode_CalcHourglassControlForElems[1];
int nd2i;
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes8) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcHourglassControlForElems):traits(stride(0)))
nd2i=elemToNode_CalcHourglassControlForElems[2];
int nd3i;
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes11) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcHourglassControlForElems):traits(stride(0)))
nd3i=elemToNode_CalcHourglassControlForElems[3];
int nd4i;
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes14) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcHourglassControlForElems):traits(stride(0)))
nd4i=elemToNode_CalcHourglassControlForElems[4];
int nd5i;
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes17) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcHourglassControlForElems):traits(stride(0)))
nd5i=elemToNode_CalcHourglassControlForElems[5];
int nd6i;
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes20) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcHourglassControlForElems):traits(stride(0)))
nd6i=elemToNode_CalcHourglassControlForElems[6];
int nd7i;
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes23) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcHourglassControlForElems):traits(stride(0)))
nd7i=elemToNode_CalcHourglassControlForElems[7];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes24) loads((1*aspen_param_sizeof_double):from(m_x):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemX[0]=m_x[nd0i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes25) loads((1*aspen_param_sizeof_double):from(m_x):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemX[1]=m_x[nd1i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes26) loads((1*aspen_param_sizeof_double):from(m_x):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemX[2]=m_x[nd2i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes27) loads((1*aspen_param_sizeof_double):from(m_x):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemX[3]=m_x[nd3i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes28) loads((1*aspen_param_sizeof_double):from(m_x):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemX[4]=m_x[nd4i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes29) loads((1*aspen_param_sizeof_double):from(m_x):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemX[5]=m_x[nd5i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes30) loads((1*aspen_param_sizeof_double):from(m_x):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemX[6]=m_x[nd6i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes31) loads((1*aspen_param_sizeof_double):from(m_x):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemX[7]=m_x[nd7i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes32) loads((1*aspen_param_sizeof_double):from(m_y):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemY[0]=m_y[nd0i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes33) loads((1*aspen_param_sizeof_double):from(m_y):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemY[1]=m_y[nd1i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes34) loads((1*aspen_param_sizeof_double):from(m_y):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemY[2]=m_y[nd2i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes35) loads((1*aspen_param_sizeof_double):from(m_y):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemY[3]=m_y[nd3i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes36) loads((1*aspen_param_sizeof_double):from(m_y):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemY[4]=m_y[nd4i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes37) loads((1*aspen_param_sizeof_double):from(m_y):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemY[5]=m_y[nd5i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes38) loads((1*aspen_param_sizeof_double):from(m_y):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemY[6]=m_y[nd6i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes39) loads((1*aspen_param_sizeof_double):from(m_y):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemY[7]=m_y[nd7i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes40) loads((1*aspen_param_sizeof_double):from(m_z):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemZ[0]=m_z[nd0i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes41) loads((1*aspen_param_sizeof_double):from(m_z):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemZ[1]=m_z[nd1i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes42) loads((1*aspen_param_sizeof_double):from(m_z):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemZ[2]=m_z[nd2i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes43) loads((1*aspen_param_sizeof_double):from(m_z):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemZ[3]=m_z[nd3i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes44) loads((1*aspen_param_sizeof_double):from(m_z):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemZ[4]=m_z[nd4i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes45) loads((1*aspen_param_sizeof_double):from(m_z):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemZ[5]=m_z[nd5i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes46) loads((1*aspen_param_sizeof_double):from(m_z):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemZ[6]=m_z[nd6i];
#pragma aspen  control execute label(block_CollectDomainNodesToElemNodes47) loads((1*aspen_param_sizeof_double):from(m_z):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
elemZ[7]=m_z[nd7i];
return ;
}

static inline void VoluDer(const double x0, const double x1, const double x2, const double x3, const double x4, const double x5, const double y0, const double y1, const double y2, const double y3, const double y4, const double y5, const double z0, const double z1, const double z2, const double z3, const double z4, const double z5, double * dvdx, double * dvdy, double * dvdz)
{
const double twelfth = 1.0/12.0;
#pragma aspen  control execute label(block_VoluDer20) flops(23:traits(dp)) stores((1*aspen_param_sizeof_double))
( * dvdx)=(((((((y1+y2)*(z0+z1))-((y0+y1)*(z1+z2)))+((y0+y4)*(z3+z4)))-((y3+y4)*(z0+z4)))-((y2+y5)*(z3+z5)))+((y3+y5)*(z2+z5)));
#pragma aspen  control execute label(block_VoluDer21) flops(23:traits(dp)) stores((1*aspen_param_sizeof_double))
( * dvdy)=((((((( - (x1+x2))*(z0+z1))+((x0+x1)*(z1+z2)))-((x0+x4)*(z3+z4)))+((x3+x4)*(z0+z4)))+((x2+x5)*(z3+z5)))-((x3+x5)*(z2+z5)));
#pragma aspen  control execute label(block_VoluDer22) flops(23:traits(dp)) stores((1*aspen_param_sizeof_double))
( * dvdz)=((((((( - (y1+y2))*(x0+x1))+((y0+y1)*(x1+x2)))-((y0+y4)*(x3+x4)))+((y3+y4)*(x0+x4)))+((y2+y5)*(x3+x5)))-((y3+y5)*(x2+x5)));
#pragma aspen  control execute label(block_VoluDer23) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * dvdx)*=twelfth;
#pragma aspen  control execute label(block_VoluDer24) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * dvdy)*=twelfth;
#pragma aspen  control execute label(block_VoluDer25) flops(1:traits(dp)) stores((1*aspen_param_sizeof_double))
( * dvdz)*=twelfth;
return ;
}

static inline void CalcElemVolumeDerivative(double dvdx[8], double dvdy[8], double dvdz[8], const double x[8], const double y[8], const double z[8])
{
#pragma aspen  control label(block_CalcElemVolumeDerivative0) loads((1*aspen_param_sizeof_double):traits(stride(0)), (12*aspen_param_sizeof_double):traits(stride(0)), (2*aspen_param_sizeof_double):traits(stride(0)), (6*aspen_param_sizeof_double):traits(stride(0)))
VoluDer(x[1], x[2], x[3], x[4], x[5], x[7], y[1], y[2], y[3], y[4], y[5], y[7], z[1], z[2], z[3], z[4], z[5], z[7], ( & dvdx[0]), ( & dvdy[0]), ( & dvdz[0]));
#pragma aspen  control label(block_CalcElemVolumeDerivative1) loads((1*aspen_param_sizeof_double):traits(stride(0)), (12*aspen_param_sizeof_double):traits(stride(0)), (2*aspen_param_sizeof_double):traits(stride(0)), (6*aspen_param_sizeof_double):traits(stride(0)))
VoluDer(x[0], x[1], x[2], x[7], x[4], x[6], y[0], y[1], y[2], y[7], y[4], y[6], z[0], z[1], z[2], z[7], z[4], z[6], ( & dvdx[3]), ( & dvdy[3]), ( & dvdz[3]));
#pragma aspen  control label(block_CalcElemVolumeDerivative2) loads((1*aspen_param_sizeof_double):traits(stride(0)), (12*aspen_param_sizeof_double):traits(stride(0)), (2*aspen_param_sizeof_double):traits(stride(0)), (6*aspen_param_sizeof_double):traits(stride(0)))
VoluDer(x[3], x[0], x[1], x[6], x[7], x[5], y[3], y[0], y[1], y[6], y[7], y[5], z[3], z[0], z[1], z[6], z[7], z[5], ( & dvdx[2]), ( & dvdy[2]), ( & dvdz[2]));
#pragma aspen  control label(block_CalcElemVolumeDerivative3) loads((1*aspen_param_sizeof_double):traits(stride(0)), (12*aspen_param_sizeof_double):traits(stride(0)), (2*aspen_param_sizeof_double):traits(stride(0)), (6*aspen_param_sizeof_double):traits(stride(0)))
VoluDer(x[2], x[3], x[0], x[5], x[6], x[4], y[2], y[3], y[0], y[5], y[6], y[4], z[2], z[3], z[0], z[5], z[6], z[4], ( & dvdx[1]), ( & dvdy[1]), ( & dvdz[1]));
#pragma aspen  control label(block_CalcElemVolumeDerivative4) loads((1*aspen_param_sizeof_double):traits(stride(0)), (12*aspen_param_sizeof_double):traits(stride(0)), (2*aspen_param_sizeof_double):traits(stride(0)), (6*aspen_param_sizeof_double):traits(stride(0)))
VoluDer(x[7], x[6], x[5], x[0], x[3], x[1], y[7], y[6], y[5], y[0], y[3], y[1], z[7], z[6], z[5], z[0], z[3], z[1], ( & dvdx[4]), ( & dvdy[4]), ( & dvdz[4]));
#pragma aspen  control label(block_CalcElemVolumeDerivative5) loads((1*aspen_param_sizeof_double):traits(stride(0)), (12*aspen_param_sizeof_double):traits(stride(0)), (2*aspen_param_sizeof_double):traits(stride(0)), (6*aspen_param_sizeof_double):traits(stride(0)))
VoluDer(x[4], x[7], x[6], x[1], x[0], x[2], y[4], y[7], y[6], y[1], y[0], y[2], z[4], z[7], z[6], z[1], z[0], z[2], ( & dvdx[5]), ( & dvdy[5]), ( & dvdz[5]));
#pragma aspen  control label(block_CalcElemVolumeDerivative6) loads((1*aspen_param_sizeof_double):traits(stride(0)), (12*aspen_param_sizeof_double):traits(stride(0)), (2*aspen_param_sizeof_double):traits(stride(0)), (6*aspen_param_sizeof_double):traits(stride(0)))
VoluDer(x[5], x[4], x[7], x[2], x[1], x[3], y[5], y[4], y[7], y[2], y[1], y[3], z[5], z[4], z[7], z[2], z[1], z[3], ( & dvdx[6]), ( & dvdy[6]), ( & dvdz[6]));
#pragma aspen  control label(block_CalcElemVolumeDerivative7) loads((1*aspen_param_sizeof_double):traits(stride(0)), (12*aspen_param_sizeof_double):traits(stride(0)), (2*aspen_param_sizeof_double):traits(stride(0)), (6*aspen_param_sizeof_double):traits(stride(0)))
VoluDer(x[6], x[5], x[4], x[3], x[2], x[0], y[6], y[5], y[4], y[3], y[2], y[0], z[6], z[5], z[4], z[3], z[2], z[0], ( & dvdx[7]), ( & dvdy[7]), ( & dvdz[7]));
return ;
}

static inline void CalcElemFBHourglassForce(double * xd, double * yd, double * zd, double * hourgam0, double * hourgam1, double * hourgam2, double * hourgam3, double * hourgam4, double * hourgam5, double * hourgam6, double * hourgam7, double coefficient, double * hgfx, double * hgfy, double * hgfz)
{
int i00 = 0;
int i01 = 1;
int i02 = 2;
int i03 = 3;
double h00;
#pragma aspen  control execute label(block_CalcElemFBHourglassForce11) flops(15:traits(dp, simd)) loads((16*aspen_param_sizeof_double):traits(stride(0)))
h00=(((((((hourgam0[i00]*xd[0])+(hourgam1[i00]*xd[1]))+(hourgam2[i00]*xd[2]))+(hourgam3[i00]*xd[3]))+(hourgam4[i00]*xd[4]))+(hourgam5[i00]*xd[5]))+(hourgam6[i00]*xd[6]))+(hourgam7[i00]*xd[7]);
double h01;
#pragma aspen  control execute label(block_CalcElemFBHourglassForce14) flops(15:traits(dp, simd)) loads((16*aspen_param_sizeof_double):traits(stride(0)))
h01=(((((((hourgam0[i01]*xd[0])+(hourgam1[i01]*xd[1]))+(hourgam2[i01]*xd[2]))+(hourgam3[i01]*xd[3]))+(hourgam4[i01]*xd[4]))+(hourgam5[i01]*xd[5]))+(hourgam6[i01]*xd[6]))+(hourgam7[i01]*xd[7]);
double h02;
#pragma aspen  control execute label(block_CalcElemFBHourglassForce17) flops(15:traits(dp, simd)) loads((16*aspen_param_sizeof_double):traits(stride(0)))
h02=(((((((hourgam0[i02]*xd[0])+(hourgam1[i02]*xd[1]))+(hourgam2[i02]*xd[2]))+(hourgam3[i02]*xd[3]))+(hourgam4[i02]*xd[4]))+(hourgam5[i02]*xd[5]))+(hourgam6[i02]*xd[6]))+(hourgam7[i02]*xd[7]);
double h03;
#pragma aspen  control execute label(block_CalcElemFBHourglassForce20) flops(15:traits(dp, simd)) loads((16*aspen_param_sizeof_double):traits(stride(0)))
h03=(((((((hourgam0[i03]*xd[0])+(hourgam1[i03]*xd[1]))+(hourgam2[i03]*xd[2]))+(hourgam3[i03]*xd[3]))+(hourgam4[i03]*xd[4]))+(hourgam5[i03]*xd[5]))+(hourgam6[i03]*xd[6]))+(hourgam7[i03]*xd[7]);
#pragma aspen  control execute label(block_CalcElemFBHourglassForce21) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfx[0]=(coefficient*((((hourgam0[i00]*h00)+(hourgam0[i01]*h01))+(hourgam0[i02]*h02))+(hourgam0[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce22) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfx[1]=(coefficient*((((hourgam1[i00]*h00)+(hourgam1[i01]*h01))+(hourgam1[i02]*h02))+(hourgam1[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce23) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfx[2]=(coefficient*((((hourgam2[i00]*h00)+(hourgam2[i01]*h01))+(hourgam2[i02]*h02))+(hourgam2[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce24) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfx[3]=(coefficient*((((hourgam3[i00]*h00)+(hourgam3[i01]*h01))+(hourgam3[i02]*h02))+(hourgam3[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce25) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfx[4]=(coefficient*((((hourgam4[i00]*h00)+(hourgam4[i01]*h01))+(hourgam4[i02]*h02))+(hourgam4[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce26) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfx[5]=(coefficient*((((hourgam5[i00]*h00)+(hourgam5[i01]*h01))+(hourgam5[i02]*h02))+(hourgam5[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce27) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfx[6]=(coefficient*((((hourgam6[i00]*h00)+(hourgam6[i01]*h01))+(hourgam6[i02]*h02))+(hourgam6[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce28) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfx[7]=(coefficient*((((hourgam7[i00]*h00)+(hourgam7[i01]*h01))+(hourgam7[i02]*h02))+(hourgam7[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce29) flops(15:traits(dp, simd)) loads((16*aspen_param_sizeof_double):traits(stride(0)))
h00=((((((((hourgam0[i00]*yd[0])+(hourgam1[i00]*yd[1]))+(hourgam2[i00]*yd[2]))+(hourgam3[i00]*yd[3]))+(hourgam4[i00]*yd[4]))+(hourgam5[i00]*yd[5]))+(hourgam6[i00]*yd[6]))+(hourgam7[i00]*yd[7]));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce30) flops(15:traits(dp, simd)) loads((16*aspen_param_sizeof_double):traits(stride(0)))
h01=((((((((hourgam0[i01]*yd[0])+(hourgam1[i01]*yd[1]))+(hourgam2[i01]*yd[2]))+(hourgam3[i01]*yd[3]))+(hourgam4[i01]*yd[4]))+(hourgam5[i01]*yd[5]))+(hourgam6[i01]*yd[6]))+(hourgam7[i01]*yd[7]));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce31) flops(15:traits(dp, simd)) loads((16*aspen_param_sizeof_double):traits(stride(0)))
h02=((((((((hourgam0[i02]*yd[0])+(hourgam1[i02]*yd[1]))+(hourgam2[i02]*yd[2]))+(hourgam3[i02]*yd[3]))+(hourgam4[i02]*yd[4]))+(hourgam5[i02]*yd[5]))+(hourgam6[i02]*yd[6]))+(hourgam7[i02]*yd[7]));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce32) flops(15:traits(dp, simd)) loads((16*aspen_param_sizeof_double):traits(stride(0)))
h03=((((((((hourgam0[i03]*yd[0])+(hourgam1[i03]*yd[1]))+(hourgam2[i03]*yd[2]))+(hourgam3[i03]*yd[3]))+(hourgam4[i03]*yd[4]))+(hourgam5[i03]*yd[5]))+(hourgam6[i03]*yd[6]))+(hourgam7[i03]*yd[7]));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce33) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfy[0]=(coefficient*((((hourgam0[i00]*h00)+(hourgam0[i01]*h01))+(hourgam0[i02]*h02))+(hourgam0[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce34) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfy[1]=(coefficient*((((hourgam1[i00]*h00)+(hourgam1[i01]*h01))+(hourgam1[i02]*h02))+(hourgam1[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce35) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfy[2]=(coefficient*((((hourgam2[i00]*h00)+(hourgam2[i01]*h01))+(hourgam2[i02]*h02))+(hourgam2[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce36) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfy[3]=(coefficient*((((hourgam3[i00]*h00)+(hourgam3[i01]*h01))+(hourgam3[i02]*h02))+(hourgam3[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce37) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfy[4]=(coefficient*((((hourgam4[i00]*h00)+(hourgam4[i01]*h01))+(hourgam4[i02]*h02))+(hourgam4[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce38) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfy[5]=(coefficient*((((hourgam5[i00]*h00)+(hourgam5[i01]*h01))+(hourgam5[i02]*h02))+(hourgam5[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce39) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfy[6]=(coefficient*((((hourgam6[i00]*h00)+(hourgam6[i01]*h01))+(hourgam6[i02]*h02))+(hourgam6[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce40) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfy[7]=(coefficient*((((hourgam7[i00]*h00)+(hourgam7[i01]*h01))+(hourgam7[i02]*h02))+(hourgam7[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce41) flops(15:traits(dp, simd)) loads((16*aspen_param_sizeof_double):traits(stride(0)))
h00=((((((((hourgam0[i00]*zd[0])+(hourgam1[i00]*zd[1]))+(hourgam2[i00]*zd[2]))+(hourgam3[i00]*zd[3]))+(hourgam4[i00]*zd[4]))+(hourgam5[i00]*zd[5]))+(hourgam6[i00]*zd[6]))+(hourgam7[i00]*zd[7]));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce42) flops(15:traits(dp, simd)) loads((16*aspen_param_sizeof_double):traits(stride(0)))
h01=((((((((hourgam0[i01]*zd[0])+(hourgam1[i01]*zd[1]))+(hourgam2[i01]*zd[2]))+(hourgam3[i01]*zd[3]))+(hourgam4[i01]*zd[4]))+(hourgam5[i01]*zd[5]))+(hourgam6[i01]*zd[6]))+(hourgam7[i01]*zd[7]));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce43) flops(15:traits(dp, simd)) loads((16*aspen_param_sizeof_double):traits(stride(0)))
h02=((((((((hourgam0[i02]*zd[0])+(hourgam1[i02]*zd[1]))+(hourgam2[i02]*zd[2]))+(hourgam3[i02]*zd[3]))+(hourgam4[i02]*zd[4]))+(hourgam5[i02]*zd[5]))+(hourgam6[i02]*zd[6]))+(hourgam7[i02]*zd[7]));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce44) flops(15:traits(dp, simd)) loads((16*aspen_param_sizeof_double):traits(stride(0)))
h03=((((((((hourgam0[i03]*zd[0])+(hourgam1[i03]*zd[1]))+(hourgam2[i03]*zd[2]))+(hourgam3[i03]*zd[3]))+(hourgam4[i03]*zd[4]))+(hourgam5[i03]*zd[5]))+(hourgam6[i03]*zd[6]))+(hourgam7[i03]*zd[7]));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce45) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfz[0]=(coefficient*((((hourgam0[i00]*h00)+(hourgam0[i01]*h01))+(hourgam0[i02]*h02))+(hourgam0[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce46) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfz[1]=(coefficient*((((hourgam1[i00]*h00)+(hourgam1[i01]*h01))+(hourgam1[i02]*h02))+(hourgam1[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce47) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfz[2]=(coefficient*((((hourgam2[i00]*h00)+(hourgam2[i01]*h01))+(hourgam2[i02]*h02))+(hourgam2[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce48) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfz[3]=(coefficient*((((hourgam3[i00]*h00)+(hourgam3[i01]*h01))+(hourgam3[i02]*h02))+(hourgam3[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce49) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfz[4]=(coefficient*((((hourgam4[i00]*h00)+(hourgam4[i01]*h01))+(hourgam4[i02]*h02))+(hourgam4[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce50) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfz[5]=(coefficient*((((hourgam5[i00]*h00)+(hourgam5[i01]*h01))+(hourgam5[i02]*h02))+(hourgam5[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce51) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfz[6]=(coefficient*((((hourgam6[i00]*h00)+(hourgam6[i01]*h01))+(hourgam6[i02]*h02))+(hourgam6[i03]*h03)));
#pragma aspen  control execute label(block_CalcElemFBHourglassForce52) flops(8:traits(dp, simd)) loads((4*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
hgfz[7]=(coefficient*((((hourgam7[i00]*h00)+(hourgam7[i01]*h01))+(hourgam7[i02]*h02))+(hourgam7[i03]*h03)));
return ;
}

static inline void CalcFBHourglassForceForElems(double determ[((45*45)*45)], double x8n[(((45*45)*45)*8)], double y8n[(((45*45)*45)*8)], double z8n[(((45*45)*45)*8)], double dvdx[(((45*45)*45)*8)], double dvdy[(((45*45)*45)*8)], double dvdz[(((45*45)*45)*8)], double hourg, double m_ss[((45*45)*45)], int m_nodelist[(((45*45)*45)*8)], double m_elemMass[((45*45)*45)], double m_xd[(((45+1)*(45+1))*(45+1))], double m_yd[(((45+1)*(45+1))*(45+1))], double m_zd[(((45+1)*(45+1))*(45+1))], int m_nodeElemCount[(((45+1)*(45+1))*(45+1))], int m_nodeElemStart[(((45+1)*(45+1))*(45+1))], int m_nodeElemCornerList[(((45*45)*45)*8)], double m_fx[(((45+1)*(45+1))*(45+1))], double m_fy[(((45+1)*(45+1))*(45+1))], double m_fz[(((45+1)*(45+1))*(45+1))])
{
/*

    *
    *     FUNCTION: Calculates the Flanagan-Belytschko anti-hourglass
    *               force.
    *

*/
int i1;
int i2;
int gnode;
int i;
int numElem;
#pragma aspen  control ignore
numElem=m_numElem;
int numElem8;
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems15) flops(1:traits(integer))
numElem8=numElem*8;
/*

   Real_tfx_elem = Allocate(numElem8) ;
   Real_t *fy_elem = Allocate(numElem8) ;
   Real_t *fz_elem = Allocate(numElem8) ;

*/
double gamma[4][8];
#pragma aspen  control ignore
gamma[0][0]=1.0;
#pragma aspen  control ignore
gamma[0][1]=1.0;
#pragma aspen  control ignore
gamma[0][2]=( - 1.0);
#pragma aspen  control ignore
gamma[0][3]=( - 1.0);
#pragma aspen  control ignore
gamma[0][4]=( - 1.0);
#pragma aspen  control ignore
gamma[0][5]=( - 1.0);
#pragma aspen  control ignore
gamma[0][6]=1.0;
#pragma aspen  control ignore
gamma[0][7]=1.0;
#pragma aspen  control ignore
gamma[1][0]=1.0;
#pragma aspen  control ignore
gamma[1][1]=( - 1.0);
#pragma aspen  control ignore
gamma[1][2]=( - 1.0);
#pragma aspen  control ignore
gamma[1][3]=1.0;
#pragma aspen  control ignore
gamma[1][4]=( - 1.0);
#pragma aspen  control ignore
gamma[1][5]=1.0;
#pragma aspen  control ignore
gamma[1][6]=1.0;
#pragma aspen  control ignore
gamma[1][7]=( - 1.0);
#pragma aspen  control ignore
gamma[2][0]=1.0;
#pragma aspen  control ignore
gamma[2][1]=( - 1.0);
#pragma aspen  control ignore
gamma[2][2]=1.0;
#pragma aspen  control ignore
gamma[2][3]=( - 1.0);
#pragma aspen  control ignore
gamma[2][4]=1.0;
#pragma aspen  control ignore
gamma[2][5]=( - 1.0);
#pragma aspen  control ignore
gamma[2][6]=1.0;
#pragma aspen  control ignore
gamma[2][7]=( - 1.0);
#pragma aspen  control ignore
gamma[3][0]=( - 1.0);
#pragma aspen  control ignore
gamma[3][1]=1.0;
#pragma aspen  control ignore
gamma[3][2]=( - 1.0);
#pragma aspen  control ignore
gamma[3][3]=1.0;
#pragma aspen  control ignore
gamma[3][4]=1.0;
#pragma aspen  control ignore
gamma[3][5]=( - 1.0);
#pragma aspen  control ignore
gamma[3][6]=1.0;
#pragma aspen  control ignore
gamma[3][7]=( - 1.0);
/*  */
/*    compute the hourglass modes */
#pragma acc  kernels loop gang worker independent copy(hourg, i1, numElem) copyin(gamma[0:4][0:8]) present(determ, dvdx, dvdy, dvdz, fx_elem, fy_elem, fz_elem, m_elemMass, m_nodelist, m_ss, m_xd, m_yd, m_zd, x8n, y8n, z8n) private(i2)
#pragma aspen  control label(block_CalcFBHourglassForceForElems52) loop(m_numElem) parallelism(m_numElem) flops(1:traits(integer)) intracomm(((aspen_param_sizeof_double*4)*8):traits(copyin))
for (i2=0; i2<numElem;  ++ i2)
{
double * fx_local;
double * fy_local;
double * fz_local;
double hgfx[8];
double hgfy[8];
double hgfz[8];
double coefficient;
double hourgam0[4];
double hourgam1[4];
double hourgam2[4];
double hourgam3[4];
double hourgam4[4];
double hourgam5[4];
double hourgam6[4];
double hourgam7[4];
double xd1[8];
double yd1[8];
double zd1[8];
#pragma aspen  declare data(elemToNode_CalcFBHourglassForceForElems:traits(Array(8, aspen_param_int)))
const int * elemToNode_CalcFBHourglassForceForElems;
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems74) flops(1:traits(integer)) loads((1*aspen_param_sizeof_int):from(m_nodelist))
elemToNode_CalcFBHourglassForceForElems= & m_nodelist[(8*i2)];
int i3;
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems77) flops(1:traits(integer))
i3=8*i2;
double volinv;
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems80) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(determ):traits(stride(1)))
volinv=1.0/determ[i2];
double ss1;
double mass1;
double volume13;
int n0si2;
int n1si2;
int n2si2;
int n3si2;
int n4si2;
int n5si2;
int n6si2;
int n7si2;
#pragma aspen  control label(block_CalcFBHourglassForceForElems103) loop(4) flops(1:traits(integer))
for (i1=0; i1<4;  ++ i1)
{
double hourmodx;
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems106) flops((15*4):traits(dp), (7*4):traits(integer)) loads(((8*aspen_param_sizeof_double)*4):from(x8n))
hourmodx=(((((((x8n[i3]*gamma[i1][0])+(x8n[(i3+1)]*gamma[i1][1]))+(x8n[(i3+2)]*gamma[i1][2]))+(x8n[(i3+3)]*gamma[i1][3]))+(x8n[(i3+4)]*gamma[i1][4]))+(x8n[(i3+5)]*gamma[i1][5]))+(x8n[(i3+6)]*gamma[i1][6]))+(x8n[(i3+7)]*gamma[i1][7]);
double hourmody;
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems109) flops((15*4):traits(dp), (7*4):traits(integer)) loads(((8*aspen_param_sizeof_double)*4):from(y8n))
hourmody=(((((((y8n[i3]*gamma[i1][0])+(y8n[(i3+1)]*gamma[i1][1]))+(y8n[(i3+2)]*gamma[i1][2]))+(y8n[(i3+3)]*gamma[i1][3]))+(y8n[(i3+4)]*gamma[i1][4]))+(y8n[(i3+5)]*gamma[i1][5]))+(y8n[(i3+6)]*gamma[i1][6]))+(y8n[(i3+7)]*gamma[i1][7]);
double hourmodz;
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems112) flops((15*4):traits(dp), (7*4):traits(integer)) loads(((8*aspen_param_sizeof_double)*4):from(z8n))
hourmodz=(((((((z8n[i3]*gamma[i1][0])+(z8n[(i3+1)]*gamma[i1][1]))+(z8n[(i3+2)]*gamma[i1][2]))+(z8n[(i3+3)]*gamma[i1][3]))+(z8n[(i3+4)]*gamma[i1][4]))+(z8n[(i3+5)]*gamma[i1][5]))+(z8n[(i3+6)]*gamma[i1][6]))+(z8n[(i3+7)]*gamma[i1][7]);
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems113) flops((7*4):traits(dp, simd)) loads(((1*aspen_param_sizeof_double)*4):from(dvdx), ((1*aspen_param_sizeof_double)*4):from(dvdy), ((1*aspen_param_sizeof_double)*4):from(dvdz))
hourgam0[i1]=(gamma[i1][0]-(volinv*(((dvdx[i3]*hourmodx)+(dvdy[i3]*hourmody))+(dvdz[i3]*hourmodz))));
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems114) flops((3*4):traits(integer), (7*4):traits(dp, simd)) loads(((1*aspen_param_sizeof_double)*4):from(dvdx), ((1*aspen_param_sizeof_double)*4):from(dvdy), ((1*aspen_param_sizeof_double)*4):from(dvdz))
hourgam1[i1]=(gamma[i1][1]-(volinv*(((dvdx[(i3+1)]*hourmodx)+(dvdy[(i3+1)]*hourmody))+(dvdz[(i3+1)]*hourmodz))));
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems115) flops((3*4):traits(integer), (7*4):traits(dp, simd)) loads(((1*aspen_param_sizeof_double)*4):from(dvdx), ((1*aspen_param_sizeof_double)*4):from(dvdy), ((1*aspen_param_sizeof_double)*4):from(dvdz))
hourgam2[i1]=(gamma[i1][2]-(volinv*(((dvdx[(i3+2)]*hourmodx)+(dvdy[(i3+2)]*hourmody))+(dvdz[(i3+2)]*hourmodz))));
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems116) flops((3*4):traits(integer), (7*4):traits(dp, simd)) loads(((1*aspen_param_sizeof_double)*4):from(dvdx), ((1*aspen_param_sizeof_double)*4):from(dvdy), ((1*aspen_param_sizeof_double)*4):from(dvdz))
hourgam3[i1]=(gamma[i1][3]-(volinv*(((dvdx[(i3+3)]*hourmodx)+(dvdy[(i3+3)]*hourmody))+(dvdz[(i3+3)]*hourmodz))));
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems117) flops((3*4):traits(integer), (7*4):traits(dp, simd)) loads(((1*aspen_param_sizeof_double)*4):from(dvdx), ((1*aspen_param_sizeof_double)*4):from(dvdy), ((1*aspen_param_sizeof_double)*4):from(dvdz))
hourgam4[i1]=(gamma[i1][4]-(volinv*(((dvdx[(i3+4)]*hourmodx)+(dvdy[(i3+4)]*hourmody))+(dvdz[(i3+4)]*hourmodz))));
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems118) flops((3*4):traits(integer), (7*4):traits(dp, simd)) loads(((1*aspen_param_sizeof_double)*4):from(dvdx), ((1*aspen_param_sizeof_double)*4):from(dvdy), ((1*aspen_param_sizeof_double)*4):from(dvdz))
hourgam5[i1]=(gamma[i1][5]-(volinv*(((dvdx[(i3+5)]*hourmodx)+(dvdy[(i3+5)]*hourmody))+(dvdz[(i3+5)]*hourmodz))));
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems119) flops((3*4):traits(integer), (7*4):traits(dp, simd)) loads(((1*aspen_param_sizeof_double)*4):from(dvdx), ((1*aspen_param_sizeof_double)*4):from(dvdy), ((1*aspen_param_sizeof_double)*4):from(dvdz))
hourgam6[i1]=(gamma[i1][6]-(volinv*(((dvdx[(i3+6)]*hourmodx)+(dvdy[(i3+6)]*hourmody))+(dvdz[(i3+6)]*hourmodz))));
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems120) flops((3*4):traits(integer), (7*4):traits(dp, simd)) loads(((1*aspen_param_sizeof_double)*4):from(dvdx), ((1*aspen_param_sizeof_double)*4):from(dvdy), ((1*aspen_param_sizeof_double)*4):from(dvdz))
hourgam7[i1]=(gamma[i1][7]-(volinv*(((dvdx[(i3+7)]*hourmodx)+(dvdy[(i3+7)]*hourmody))+(dvdz[(i3+7)]*hourmodz))));
}
/* compute forces */
/* store forces into h arrays (force arrays) */
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems123) loads((1*aspen_param_sizeof_double):from(m_ss):traits(stride(1)))
ss1=m_ss[i2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems124) loads((1*aspen_param_sizeof_double):from(m_elemMass):traits(stride(1)))
mass1=m_elemMass[i2];
#pragma aspen  control label(block_CalcFBHourglassForceForElems125) loads((1*aspen_param_sizeof_double):from(determ):traits(stride(1)))
volume13=CBRT8(determ[i2]);
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems126) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcFBHourglassForceForElems):traits(stride(0)))
n0si2=elemToNode_CalcFBHourglassForceForElems[0];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems127) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcFBHourglassForceForElems):traits(stride(0)))
n1si2=elemToNode_CalcFBHourglassForceForElems[1];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems128) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcFBHourglassForceForElems):traits(stride(0)))
n2si2=elemToNode_CalcFBHourglassForceForElems[2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems129) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcFBHourglassForceForElems):traits(stride(0)))
n3si2=elemToNode_CalcFBHourglassForceForElems[3];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems130) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcFBHourglassForceForElems):traits(stride(0)))
n4si2=elemToNode_CalcFBHourglassForceForElems[4];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems131) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcFBHourglassForceForElems):traits(stride(0)))
n5si2=elemToNode_CalcFBHourglassForceForElems[5];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems132) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcFBHourglassForceForElems):traits(stride(0)))
n6si2=elemToNode_CalcFBHourglassForceForElems[6];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems133) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcFBHourglassForceForElems):traits(stride(0)))
n7si2=elemToNode_CalcFBHourglassForceForElems[7];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems134) loads((1*aspen_param_sizeof_double):from(m_xd))
xd1[0]=m_xd[n0si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems135) loads((1*aspen_param_sizeof_double):from(m_xd))
xd1[1]=m_xd[n1si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems136) loads((1*aspen_param_sizeof_double):from(m_xd))
xd1[2]=m_xd[n2si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems137) loads((1*aspen_param_sizeof_double):from(m_xd))
xd1[3]=m_xd[n3si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems138) loads((1*aspen_param_sizeof_double):from(m_xd))
xd1[4]=m_xd[n4si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems139) loads((1*aspen_param_sizeof_double):from(m_xd))
xd1[5]=m_xd[n5si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems140) loads((1*aspen_param_sizeof_double):from(m_xd))
xd1[6]=m_xd[n6si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems141) loads((1*aspen_param_sizeof_double):from(m_xd))
xd1[7]=m_xd[n7si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems142) loads((1*aspen_param_sizeof_double):from(m_yd))
yd1[0]=m_yd[n0si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems143) loads((1*aspen_param_sizeof_double):from(m_yd))
yd1[1]=m_yd[n1si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems144) loads((1*aspen_param_sizeof_double):from(m_yd))
yd1[2]=m_yd[n2si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems145) loads((1*aspen_param_sizeof_double):from(m_yd))
yd1[3]=m_yd[n3si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems146) loads((1*aspen_param_sizeof_double):from(m_yd))
yd1[4]=m_yd[n4si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems147) loads((1*aspen_param_sizeof_double):from(m_yd))
yd1[5]=m_yd[n5si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems148) loads((1*aspen_param_sizeof_double):from(m_yd))
yd1[6]=m_yd[n6si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems149) loads((1*aspen_param_sizeof_double):from(m_yd))
yd1[7]=m_yd[n7si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems150) loads((1*aspen_param_sizeof_double):from(m_zd))
zd1[0]=m_zd[n0si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems151) loads((1*aspen_param_sizeof_double):from(m_zd))
zd1[1]=m_zd[n1si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems152) loads((1*aspen_param_sizeof_double):from(m_zd))
zd1[2]=m_zd[n2si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems153) loads((1*aspen_param_sizeof_double):from(m_zd))
zd1[3]=m_zd[n3si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems154) loads((1*aspen_param_sizeof_double):from(m_zd))
zd1[4]=m_zd[n4si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems155) loads((1*aspen_param_sizeof_double):from(m_zd))
zd1[5]=m_zd[n5si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems156) loads((1*aspen_param_sizeof_double):from(m_zd))
zd1[6]=m_zd[n6si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems157) loads((1*aspen_param_sizeof_double):from(m_zd))
zd1[7]=m_zd[n7si2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems158) flops(4:traits(dp))
coefficient=((((( - hourg)*0.01)*ss1)*mass1)/volume13);
CalcElemFBHourglassForce(xd1, yd1, zd1, hourgam0, hourgam1, hourgam2, hourgam3, hourgam4, hourgam5, hourgam6, hourgam7, coefficient, hgfx, hgfy, hgfz);
#pragma aspen  declare data(fx_local:traits(Array(8, aspen_param_double)))
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems161) loads((1*aspen_param_sizeof_double):from(fx_elem))
fx_local=( & fx_elem[i3]);
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems162) stores((1*aspen_param_sizeof_double):to(fx_local):traits(stride(0)))
fx_local[0]=hgfx[0];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems163) stores((1*aspen_param_sizeof_double):to(fx_local):traits(stride(0)))
fx_local[1]=hgfx[1];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems164) stores((1*aspen_param_sizeof_double):to(fx_local):traits(stride(0)))
fx_local[2]=hgfx[2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems165) stores((1*aspen_param_sizeof_double):to(fx_local):traits(stride(0)))
fx_local[3]=hgfx[3];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems166) stores((1*aspen_param_sizeof_double):to(fx_local):traits(stride(0)))
fx_local[4]=hgfx[4];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems167) stores((1*aspen_param_sizeof_double):to(fx_local):traits(stride(0)))
fx_local[5]=hgfx[5];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems168) stores((1*aspen_param_sizeof_double):to(fx_local):traits(stride(0)))
fx_local[6]=hgfx[6];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems169) stores((1*aspen_param_sizeof_double):to(fx_local):traits(stride(0)))
fx_local[7]=hgfx[7];
#pragma aspen  declare data(fy_local:traits(Array(8, aspen_param_double)))
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems171) loads((1*aspen_param_sizeof_double):from(fy_elem))
fy_local=( & fy_elem[i3]);
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems172) stores((1*aspen_param_sizeof_double):to(fy_local):traits(stride(0)))
fy_local[0]=hgfy[0];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems173) stores((1*aspen_param_sizeof_double):to(fy_local):traits(stride(0)))
fy_local[1]=hgfy[1];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems174) stores((1*aspen_param_sizeof_double):to(fy_local):traits(stride(0)))
fy_local[2]=hgfy[2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems175) stores((1*aspen_param_sizeof_double):to(fy_local):traits(stride(0)))
fy_local[3]=hgfy[3];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems176) stores((1*aspen_param_sizeof_double):to(fy_local):traits(stride(0)))
fy_local[4]=hgfy[4];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems177) stores((1*aspen_param_sizeof_double):to(fy_local):traits(stride(0)))
fy_local[5]=hgfy[5];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems178) stores((1*aspen_param_sizeof_double):to(fy_local):traits(stride(0)))
fy_local[6]=hgfy[6];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems179) stores((1*aspen_param_sizeof_double):to(fy_local):traits(stride(0)))
fy_local[7]=hgfy[7];
#pragma aspen  declare data(fz_local:traits(Array(8, aspen_param_double)))
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems181) loads((1*aspen_param_sizeof_double):from(fz_elem))
fz_local=( & fz_elem[i3]);
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems182) stores((1*aspen_param_sizeof_double):to(fz_local):traits(stride(0)))
fz_local[0]=hgfz[0];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems183) stores((1*aspen_param_sizeof_double):to(fz_local):traits(stride(0)))
fz_local[1]=hgfz[1];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems184) stores((1*aspen_param_sizeof_double):to(fz_local):traits(stride(0)))
fz_local[2]=hgfz[2];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems185) stores((1*aspen_param_sizeof_double):to(fz_local):traits(stride(0)))
fz_local[3]=hgfz[3];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems186) stores((1*aspen_param_sizeof_double):to(fz_local):traits(stride(0)))
fz_local[4]=hgfz[4];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems187) stores((1*aspen_param_sizeof_double):to(fz_local):traits(stride(0)))
fz_local[5]=hgfz[5];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems188) stores((1*aspen_param_sizeof_double):to(fz_local):traits(stride(0)))
fz_local[6]=hgfz[6];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems189) stores((1*aspen_param_sizeof_double):to(fz_local):traits(stride(0)))
fz_local[7]=hgfz[7];
}
{
int numNode;
#pragma aspen  control ignore
numNode=m_numNode;
#pragma acc  kernels loop gang worker independent copy(i, numNode) present(fx_elem, fy_elem, fz_elem, m_fx, m_fy, m_fz, m_nodeElemCornerList, m_nodeElemCount, m_nodeElemStart) private(gnode)
#pragma aspen  control label(block_CalcFBHourglassForceForElems194) loop(m_numNode) parallelism(m_numNode) flops(1:traits(integer))
for (gnode=0; gnode<numNode;  ++ gnode)
{
int count;
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems197) loads((1*aspen_param_sizeof_int):from(m_nodeElemCount):traits(stride(1)))
count=m_nodeElemCount[gnode];
int start;
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems200) loads((1*aspen_param_sizeof_int):from(m_nodeElemStart):traits(stride(1)))
start=m_nodeElemStart[gnode];
double fx = 0.0;
double fy = 0.0;
double fz = 0.0;
#pragma aspen  declare param(aspen_param_elemCount:1)
#pragma aspen  control label(block_CalcFBHourglassForceForElems1139) loop(aspen_param_elemCount) flops(1:traits(integer))
for (i=0; i<count;  ++ i)
{
int elem;
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems211) flops((1*aspen_param_elemCount):traits(integer)) loads(((1*aspen_param_sizeof_int)*aspen_param_elemCount):from(m_nodeElemCornerList):traits(stride(1)))
elem=m_nodeElemCornerList[(start+i)];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems212) flops((1*aspen_param_elemCount):traits(dp)) loads(((1*aspen_param_sizeof_double)*aspen_param_elemCount):from(fx_elem))
fx+=fx_elem[elem];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems213) flops((1*aspen_param_elemCount):traits(dp)) loads(((1*aspen_param_sizeof_double)*aspen_param_elemCount):from(fy_elem))
fy+=fy_elem[elem];
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems214) flops((1*aspen_param_elemCount):traits(dp)) loads(((1*aspen_param_sizeof_double)*aspen_param_elemCount):from(fz_elem))
fz+=fz_elem[elem];
}
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems215) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_fx):traits(stride(1)))
m_fx[gnode]+=fx;
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems216) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_fy):traits(stride(1)))
m_fy[gnode]+=fy;
#pragma aspen  control execute label(block_CalcFBHourglassForceForElems217) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_fz):traits(stride(1)))
m_fz[gnode]+=fz;
}
}
/*

  Release(&fz_elem) ;
  Release(&fy_elem) ;
  Release(&fx_elem) ;

*/
return ;
}

static inline void CalcHourglassControlForElems(double determ[((45*45)*45)], double hgcoef, int m_nodelist[(((45*45)*45)*8)], double m_volo[((45*45)*45)], double m_v[((45*45)*45)])
{
int i;
int ii;
int numElem;
#pragma aspen  control ignore
numElem=m_numElem;
int numElem8;
#pragma aspen  control execute label(block_CalcHourglassControlForElems10) flops(1:traits(integer))
numElem8=numElem*8;
/*

   Real_tdvdx = Allocate(numElem8) ;
   Real_t *dvdy = Allocate(numElem8) ;
   Real_t *dvdz = Allocate(numElem8) ;
   Real_t *x8n  = Allocate(numElem8) ;
   Real_t *y8n  = Allocate(numElem8) ;
   Real_t *z8n  = Allocate(numElem8) ;

*/
/* start loop over elements */
int abort = 0;
#pragma acc  parallel loop gang worker independent reduction(||: abort) present(determ, dvdx, dvdy, dvdz, m_nodelist, m_v, m_volo, m_x, m_y, m_z, x8n, y8n, z8n) private(i) firstprivate(ii, numElem)
#pragma aspen  control label(block_CalcHourglassControlForElems15) loop(m_numElem) parallelism(m_numElem) flops(1:traits(integer))
for (i=0; i<numElem;  ++ i)
{
double x1[8];
double y1[8];
double z1[8];
double pfx[8];
double pfy[8];
double pfz[8];
#pragma aspen  declare data(elemToNode_CalcHourglassControlForElems:traits(Array(8, aspen_param_int)))
int * elemToNode_CalcHourglassControlForElems;
#pragma aspen  control execute label(block_CalcHourglassControlForElems24) flops(1:traits(integer)) loads((1*aspen_param_sizeof_int):from(m_nodelist))
elemToNode_CalcHourglassControlForElems= & m_nodelist[(8*i)];
CollectDomainNodesToElemNodes(elemToNode_CalcHourglassControlForElems, x1, y1, z1);
CalcElemVolumeDerivative(pfx, pfy, pfz, x1, y1, z1);
/* load into temporary storage for FB Hour Glass control */
#pragma aspen  control label(block_CalcHourglassControlForElems28) loop(8) flops(1:traits(integer))
for (ii=0; ii<8;  ++ ii)
{
int jj;
#pragma aspen  control execute label(block_CalcHourglassControlForElems31) flops((2*8):traits(integer))
jj=(8*i)+ii;
#pragma aspen  control execute label(block_CalcHourglassControlForElems32) stores(((1*aspen_param_sizeof_double)*8):to(dvdx))
dvdx[jj]=pfx[ii];
#pragma aspen  control execute label(block_CalcHourglassControlForElems33) stores(((1*aspen_param_sizeof_double)*8):to(dvdy))
dvdy[jj]=pfy[ii];
#pragma aspen  control execute label(block_CalcHourglassControlForElems34) stores(((1*aspen_param_sizeof_double)*8):to(dvdz))
dvdz[jj]=pfz[ii];
#pragma aspen  control execute label(block_CalcHourglassControlForElems35) stores(((1*aspen_param_sizeof_double)*8):to(x8n))
x8n[jj]=x1[ii];
#pragma aspen  control execute label(block_CalcHourglassControlForElems36) stores(((1*aspen_param_sizeof_double)*8):to(y8n))
y8n[jj]=y1[ii];
#pragma aspen  control execute label(block_CalcHourglassControlForElems37) stores(((1*aspen_param_sizeof_double)*8):to(z8n))
z8n[jj]=z1[ii];
}
#pragma aspen  control execute label(block_CalcHourglassControlForElems38) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_v):traits(stride(1)), (1*aspen_param_sizeof_double):from(m_volo):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(determ):traits(stride(1)))
determ[i]=(m_volo[i]*m_v[i]);
/* Do a check for negative volumes */
#pragma aspen  control ignore
if (m_v[i]<=0.0)
{
abort=1;
}
}
#pragma aspen  control label(block_CalcHourglassControlForElems41) if(abort!=0)
if (abort)
{
#pragma aspen  control ignore
fprintf(stderr, "VolumeError in CalcHourglassControlForElems(); exit\n");
#pragma aspen  control ignore
exit(VolumeError);
}
#pragma aspen  control label(block_CalcHourglassControlForElems907) probability(1) flops(1:traits(dp))
if (hgcoef>0.0)
{
CalcFBHourglassForceForElems(determ, x8n, y8n, z8n, dvdx, dvdy, dvdz, hgcoef, m_ss, m_nodelist, m_elemMass, m_xd, m_yd, m_zd, m_nodeElemCount, m_nodeElemStart, m_nodeElemCornerList, m_fx, m_fy, m_fz);
}
/*

   Release(&z8n) ;
   Release(&y8n) ;
   Release(&x8n) ;
   Release(&dvdz) ;
   Release(&dvdy) ;
   Release(&dvdx) ;

*/
return ;
}

static inline void CalcVolumeForceForElems()
{
int k;
#pragma aspen  declare param(numElem_CalcVolumeForceForElems:m_numElem)
int numElem_CalcVolumeForceForElems;
#pragma aspen  control ignore
numElem_CalcVolumeForceForElems=m_numElem;
int abort = 0;
#pragma aspen  control label(block_CalcVolumeForceForElems494) probability(1) flops(1:traits(integer))
if (numElem_CalcVolumeForceForElems!=0)
{
double hgcoef;
#pragma aspen  control ignore
hgcoef=m_hgcoef;
/*

      Real_tsigxx  = Allocate(numElem) ;
      Real_t *sigyy  = Allocate(numElem) ;
      Real_t *sigzz  = Allocate(numElem) ;
      Real_t *determ = Allocate(numElem) ;

*/
/* Sum contributions to total stress tensor */
InitStressTermsForElems(numElem_CalcVolumeForceForElems, sigxx, sigyy, sigzz, m_p, m_q);
/* call elemlib stress integration loop to produce nodal forces from */
/* material stresses. */
IntegrateStressForElems(numElem_CalcVolumeForceForElems, sigxx, sigyy, sigzz, determ, m_nodelist, m_x, m_y, m_z, m_nodeElemCount, m_nodeElemStart, m_nodeElemCornerList, m_fx, m_fy, m_fz);
/* check for negative element volume */
#pragma aspen  control ignore
#pragma acc  parallel loop gang worker independent reduction(||: abort) present(determ) private(k) firstprivate(numElem_CalcVolumeForceForElems)
for (k=0; k<numElem_CalcVolumeForceForElems;  ++ k)
{
if (determ[k]<=0.0)
{
abort=1;
}
}
#pragma aspen  control label(block_CalcVolumeForceForElems19) if(abort==1) flops(1:traits(integer))
if (abort==1)
{
#pragma aspen  control ignore
fprintf(stderr, "VolumeError in CalcVolumeForceForElems(); exit\n");
#pragma aspen  control ignore
exit(VolumeError);
}
CalcHourglassControlForElems(determ, hgcoef, m_nodelist, m_volo, m_v);
/*

      Release(&determ) ;
      Release(&sigzz) ;
      Release(&sigyy) ;
      Release(&sigxx) ;

*/
}
return ;
}

static inline void CalcForceForNodes(double m_fx[(((45+1)*(45+1))*(45+1))], double m_fy[(((45+1)*(45+1))*(45+1))], double m_fz[(((45+1)*(45+1))*(45+1))])
{
int i;
int numNode;
#pragma aspen  control ignore
numNode=m_numNode;
#pragma acc  parallel loop gang worker independent present(m_fx, m_fy, m_fz) private(i) firstprivate(numNode)
#pragma aspen  control label(block_CalcForceForNodes5) loop(m_numNode) parallelism(m_numNode) flops(1:traits(integer))
for (i=0; i<numNode;  ++ i)
{
#pragma aspen  control execute label(block_CalcForceForNodes6) stores((1*aspen_param_sizeof_double):to(m_fx):traits(stride(1)))
m_fx[i]=0.0;
#pragma aspen  control execute label(block_CalcForceForNodes7) stores((1*aspen_param_sizeof_double):to(m_fy):traits(stride(1)))
m_fy[i]=0.0;
#pragma aspen  control execute label(block_CalcForceForNodes8) stores((1*aspen_param_sizeof_double):to(m_fz):traits(stride(1)))
m_fz[i]=0.0;
}
/* Calcforce calls partial, force, hourq */
CalcVolumeForceForElems();
/* Calculate Nodal Forces at domain boundaries */
/* problem->commSBN->Transfer(CommSBN::forces); */
return ;
}

static inline void CalcAccelerationForNodes(double m_fx[(((45+1)*(45+1))*(45+1))], double m_fy[(((45+1)*(45+1))*(45+1))], double m_fz[(((45+1)*(45+1))*(45+1))], double m_xdd[(((45+1)*(45+1))*(45+1))], double m_ydd[(((45+1)*(45+1))*(45+1))], double m_zdd[(((45+1)*(45+1))*(45+1))], double m_nodalMass[(((45+1)*(45+1))*(45+1))])
{
int i;
int numNode;
#pragma aspen  control ignore
numNode=m_numNode;
#pragma acc  parallel loop gang worker independent present(m_fx, m_fy, m_fz, m_nodalMass, m_xdd, m_ydd, m_zdd) private(i) firstprivate(numNode)
#pragma aspen  control label(block_CalcAccelerationForNodes5) loop(m_numNode) parallelism(m_numNode) flops(1:traits(integer))
for (i=0; i<numNode;  ++ i)
{
#pragma aspen  control execute label(block_CalcAccelerationForNodes6) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_fx):traits(stride(1)), (1*aspen_param_sizeof_double):from(m_nodalMass):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_xdd):traits(stride(1)))
m_xdd[i]=(m_fx[i]/m_nodalMass[i]);
#pragma aspen  control execute label(block_CalcAccelerationForNodes7) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_fy):traits(stride(1)), (1*aspen_param_sizeof_double):from(m_nodalMass):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_ydd):traits(stride(1)))
m_ydd[i]=(m_fy[i]/m_nodalMass[i]);
#pragma aspen  control execute label(block_CalcAccelerationForNodes8) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_fz):traits(stride(1)), (1*aspen_param_sizeof_double):from(m_nodalMass):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_zdd):traits(stride(1)))
m_zdd[i]=(m_fz[i]/m_nodalMass[i]);
}
return ;
}

static inline void ApplyAccelerationBoundaryConditionsForNodes(double m_xdd[(((45+1)*(45+1))*(45+1))], double m_ydd[(((45+1)*(45+1))*(45+1))], double m_zdd[(((45+1)*(45+1))*(45+1))], int m_symmX[((45+1)*(45+1))], int m_symmY[((45+1)*(45+1))], int m_symmZ[((45+1)*(45+1))])
{
int i;
int numNodeBC;
#pragma aspen  control execute label(block_ApplyAccelerationBoundaryConditionsForNodes4) flops(3:traits(integer))
numNodeBC=(m_sizeX+1)*(m_sizeX+1);
#pragma acc  parallel present(m_symmX, m_symmY, m_symmZ, m_xdd, m_ydd, m_zdd) private(i) firstprivate(numNodeBC)
{
#pragma acc  loop gang worker independent
#pragma aspen  control label(block_ApplyAccelerationBoundaryConditionsForNodes6) loop(((1+(2*m_sizeX))+(m_sizeX*m_sizeX))) parallelism(((1+(2*m_sizeX))+(m_sizeX*m_sizeX))) flops(1:traits(integer))
for (i=0; i<numNodeBC;  ++ i)
{
#pragma aspen  control execute label(block_ApplyAccelerationBoundaryConditionsForNodes7) loads((1*aspen_param_sizeof_int):from(m_symmX):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_xdd):traits(random))
m_xdd[m_symmX[i]]=0.0;
}
#pragma acc  loop gang worker independent
#pragma aspen  control label(block_ApplyAccelerationBoundaryConditionsForNodes8) loop(((1+(2*m_sizeX))+(m_sizeX*m_sizeX))) parallelism(((1+(2*m_sizeX))+(m_sizeX*m_sizeX))) flops(1:traits(integer))
for (i=0; i<numNodeBC;  ++ i)
{
#pragma aspen  control execute label(block_ApplyAccelerationBoundaryConditionsForNodes9) loads((1*aspen_param_sizeof_int):from(m_symmY):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_ydd):traits(random))
m_ydd[m_symmY[i]]=0.0;
}
#pragma acc  loop gang worker independent
#pragma aspen  control label(block_ApplyAccelerationBoundaryConditionsForNodes10) loop(((1+(2*m_sizeX))+(m_sizeX*m_sizeX))) parallelism(((1+(2*m_sizeX))+(m_sizeX*m_sizeX))) flops(1:traits(integer))
for (i=0; i<numNodeBC;  ++ i)
{
#pragma aspen  control execute label(block_ApplyAccelerationBoundaryConditionsForNodes11) loads((1*aspen_param_sizeof_int):from(m_symmZ):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_zdd):traits(random))
m_zdd[m_symmZ[i]]=0.0;
}
}
return ;
}

static inline void CalcVelocityForNodes(const double dt, const double u_cut, double m_xd[(((45+1)*(45+1))*(45+1))], double m_yd[(((45+1)*(45+1))*(45+1))], double m_zd[(((45+1)*(45+1))*(45+1))], double m_xdd[(((45+1)*(45+1))*(45+1))], double m_ydd[(((45+1)*(45+1))*(45+1))], double m_zdd[(((45+1)*(45+1))*(45+1))])
{
int i;
int numNode;
#pragma aspen  control ignore
numNode=m_numNode;
#pragma acc  parallel loop gang worker independent present(m_xd, m_xdd, m_yd, m_ydd, m_zd, m_zdd) private(i) firstprivate(dt, numNode, u_cut)
#pragma aspen  control label(block_CalcVelocityForNodes7) loop(m_numNode) parallelism(m_numNode) flops(1:traits(integer))
for (i=0; i<numNode;  ++ i)
{
double xdtmp;
double ydtmp;
double zdtmp;
#pragma aspen  control execute label(block_CalcVelocityForNodes14) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_xd):traits(stride(1)), (1*aspen_param_sizeof_double):from(m_xdd):traits(stride(1)))
xdtmp=(m_xd[i]+(m_xdd[i]*dt));
#pragma aspen  control label(block_CalcVelocityForNodes1189) probability(1) flops(1:traits(dp))
if (FABS8(xdtmp)<u_cut)
{
#pragma aspen  control ignore
xdtmp=0.0;
}
#pragma aspen  control execute label(block_CalcVelocityForNodes17) stores((1*aspen_param_sizeof_double):to(m_xd):traits(stride(1)))
m_xd[i]=xdtmp;
#pragma aspen  control execute label(block_CalcVelocityForNodes18) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_yd):traits(stride(1)), (1*aspen_param_sizeof_double):from(m_ydd):traits(stride(1)))
ydtmp=(m_yd[i]+(m_ydd[i]*dt));
#pragma aspen  control label(block_CalcVelocityForNodes1197) probability(1) flops(1:traits(dp))
if (FABS8(ydtmp)<u_cut)
{
#pragma aspen  control ignore
ydtmp=0.0;
}
#pragma aspen  control execute label(block_CalcVelocityForNodes21) stores((1*aspen_param_sizeof_double):to(m_yd):traits(stride(1)))
m_yd[i]=ydtmp;
#pragma aspen  control execute label(block_CalcVelocityForNodes22) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_zd):traits(stride(1)), (1*aspen_param_sizeof_double):from(m_zdd):traits(stride(1)))
zdtmp=(m_zd[i]+(m_zdd[i]*dt));
#pragma aspen  control label(block_CalcVelocityForNodes1201) probability(1) flops(1:traits(dp))
if (FABS8(zdtmp)<u_cut)
{
#pragma aspen  control ignore
zdtmp=0.0;
}
#pragma aspen  control execute label(block_CalcVelocityForNodes25) stores((1*aspen_param_sizeof_double):to(m_zd):traits(stride(1)))
m_zd[i]=zdtmp;
}
return ;
}

static inline void CalcPositionForNodes(const double dt, double m_x[(((45+1)*(45+1))*(45+1))], double m_y[(((45+1)*(45+1))*(45+1))], double m_z[(((45+1)*(45+1))*(45+1))], double m_xd[(((45+1)*(45+1))*(45+1))], double m_yd[(((45+1)*(45+1))*(45+1))], double m_zd[(((45+1)*(45+1))*(45+1))])
{
int i;
int numNode;
#pragma aspen  control ignore
numNode=m_numNode;
#pragma acc  parallel loop gang worker independent present(m_x, m_xd, m_y, m_yd, m_z, m_zd) private(i) firstprivate(dt, numNode)
#pragma aspen  control label(block_CalcPositionForNodes6) loop(m_numNode) parallelism(m_numNode) flops(1:traits(integer))
for (i=0; i<numNode;  ++ i)
{
#pragma aspen  control execute label(block_CalcPositionForNodes7) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_xd):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_x):traits(stride(1)))
m_x[i]+=(m_xd[i]*dt);
#pragma aspen  control execute label(block_CalcPositionForNodes8) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_yd):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_y):traits(stride(1)))
m_y[i]+=(m_yd[i]*dt);
#pragma aspen  control execute label(block_CalcPositionForNodes9) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_zd):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_z):traits(stride(1)))
m_z[i]+=(m_zd[i]*dt);
}
return ;
}

static inline void LagrangeNodal()
{
const double delt = m_deltatime;
double u_cut;
#pragma aspen  control ignore
u_cut=m_u_cut;
/*
time of boundary condition evaluation is beginning of step for force and
 acceleration boundary conditions.
*/
CalcForceForNodes(m_fx, m_fy, m_fz);
CalcAccelerationForNodes(m_fx, m_fy, m_fz, m_xdd, m_ydd, m_zdd, m_nodalMass);
ApplyAccelerationBoundaryConditionsForNodes(m_xdd, m_ydd, m_zdd, m_symmX, m_symmY, m_symmZ);
CalcVelocityForNodes(delt, u_cut, m_xd, m_yd, m_zd, m_xdd, m_ydd, m_zdd);
CalcPositionForNodes(delt, m_x, m_y, m_z, m_xd, m_yd, m_zd);
return ;
}

static inline double CalcElemVolumeI(const double x0, const double x1, const double x2, const double x3, const double x4, const double x5, const double x6, const double x7, const double y0, const double y1, const double y2, const double y3, const double y4, const double y5, const double y6, const double y7, const double z0, const double z1, const double z2, const double z3, const double z4, const double z5, const double z6, const double z7)
{
double twelveth;
twelveth=1.0/12.0;
double dx61;
dx61=x6-x1;
double dy61;
dy61=y6-y1;
double dz61;
dz61=z6-z1;
double dx70;
dx70=x7-x0;
double dy70;
dy70=y7-y0;
double dz70;
dz70=z7-z0;
double dx63;
dx63=x6-x3;
double dy63;
dy63=y6-y3;
double dz63;
dz63=z6-z3;
double dx20;
dx20=x2-x0;
double dy20;
dy20=y2-y0;
double dz20;
dz20=z2-z0;
double dx50;
dx50=x5-x0;
double dy50;
dy50=y5-y0;
double dz50;
dz50=z5-z0;
double dx64;
dx64=x6-x4;
double dy64;
dy64=y6-y4;
double dz64;
dz64=z6-z4;
double dx31;
dx31=x3-x1;
double dy31;
dy31=y3-y1;
double dz31;
dz31=z3-z1;
double dx72;
dx72=x7-x2;
double dy72;
dy72=y7-y2;
double dz72;
dz72=z7-z2;
double dx43;
dx43=x4-x3;
double dy43;
dy43=y4-y3;
double dz43;
dz43=z4-z3;
double dx57;
dx57=x5-x7;
double dy57;
dy57=y5-y7;
double dz57;
dz57=z5-z7;
double dx14;
dx14=x1-x4;
double dy14;
dy14=y1-y4;
double dz14;
dz14=z1-z4;
double dx25;
dx25=x2-x5;
double dy25;
dy25=y2-y5;
double dz25;
dz25=z2-z5;
double volume;
volume=(((((dx31+dx72)*((dy63*dz20)-(dy20*dz63)))+((dy31+dy72)*((dx20*dz63)-(dx63*dz20))))+((dz31+dz72)*((dx63*dy20)-(dx20*dy63))))+((((dx43+dx57)*((dy64*dz70)-(dy70*dz64)))+((dy43+dy57)*((dx70*dz64)-(dx64*dz70))))+((dz43+dz57)*((dx64*dy70)-(dx70*dy64)))))+((((dx14+dx25)*((dy61*dz50)-(dy50*dz61)))+((dy14+dy25)*((dx50*dz61)-(dx61*dz50))))+((dz14+dz25)*((dx61*dy50)-(dx50*dy61))));
volume*=twelveth;
return volume;
}

static inline double CalcElemVolume(const double x[8], const double y[8], const double z[8])
{
double _ret_val_0;
_ret_val_0=CalcElemVolumeI(x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7], y[0], y[1], y[2], y[3], y[4], y[5], y[6], y[7], z[0], z[1], z[2], z[3], z[4], z[5], z[6], z[7]);
return _ret_val_0;
}

static inline double AreaFace(const double x0, const double x1, const double x2, const double x3, const double y0, const double y1, const double y2, const double y3, const double z0, const double z1, const double z2, const double z3)
{
double fx;
#pragma aspen  control execute label(block_AreaFace14) flops(3:traits(dp))
fx=(x2-x0)-(x3-x1);
double fy;
#pragma aspen  control execute label(block_AreaFace17) flops(3:traits(dp))
fy=(y2-y0)-(y3-y1);
double fz;
#pragma aspen  control execute label(block_AreaFace20) flops(3:traits(dp))
fz=(z2-z0)-(z3-z1);
double gx;
#pragma aspen  control execute label(block_AreaFace23) flops(3:traits(dp))
gx=(x2-x0)+(x3-x1);
double gy;
#pragma aspen  control execute label(block_AreaFace26) flops(3:traits(dp))
gy=(y2-y0)+(y3-y1);
double gz;
#pragma aspen  control execute label(block_AreaFace29) flops(3:traits(dp))
gz=(z2-z0)+(z3-z1);
double area;
#pragma aspen  control execute label(block_AreaFace32) flops(23:traits(dp))
area=((((fx*fx)+(fy*fy))+(fz*fz))*(((gx*gx)+(gy*gy))+(gz*gz)))-((((fx*gx)+(fy*gy))+(fz*gz))*(((fx*gx)+(fy*gy))+(fz*gz)));
return area;
}

static inline double CalcElemCharacteristicLength(const double x[8], const double y[8], const double z[8], const double volume)
{
double a;
double charLength = 0.0;
#pragma aspen  control label(block_CalcElemCharacteristicLength5) loads((4*aspen_param_sizeof_double):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
a=AreaFace(x[0], x[1], x[2], x[3], y[0], y[1], y[2], y[3], z[0], z[1], z[2], z[3]);
#pragma aspen  control execute label(block_CalcElemCharacteristicLength6) flops(1:traits(dp))
charLength=((a>charLength) ? a : charLength);
#pragma aspen  control label(block_CalcElemCharacteristicLength7) loads((4*aspen_param_sizeof_double):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
a=AreaFace(x[4], x[5], x[6], x[7], y[4], y[5], y[6], y[7], z[4], z[5], z[6], z[7]);
#pragma aspen  control execute label(block_CalcElemCharacteristicLength8) flops(1:traits(dp))
charLength=((a>charLength) ? a : charLength);
#pragma aspen  control label(block_CalcElemCharacteristicLength9) loads((4*aspen_param_sizeof_double):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
a=AreaFace(x[0], x[1], x[5], x[4], y[0], y[1], y[5], y[4], z[0], z[1], z[5], z[4]);
#pragma aspen  control execute label(block_CalcElemCharacteristicLength10) flops(1:traits(dp))
charLength=((a>charLength) ? a : charLength);
#pragma aspen  control label(block_CalcElemCharacteristicLength11) loads((4*aspen_param_sizeof_double):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
a=AreaFace(x[1], x[2], x[6], x[5], y[1], y[2], y[6], y[5], z[1], z[2], z[6], z[5]);
#pragma aspen  control execute label(block_CalcElemCharacteristicLength12) flops(1:traits(dp))
charLength=((a>charLength) ? a : charLength);
#pragma aspen  control label(block_CalcElemCharacteristicLength13) loads((4*aspen_param_sizeof_double):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
a=AreaFace(x[2], x[3], x[7], x[6], y[2], y[3], y[7], y[6], z[2], z[3], z[7], z[6]);
#pragma aspen  control execute label(block_CalcElemCharacteristicLength14) flops(1:traits(dp))
charLength=((a>charLength) ? a : charLength);
#pragma aspen  control label(block_CalcElemCharacteristicLength15) loads((4*aspen_param_sizeof_double):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
a=AreaFace(x[3], x[0], x[4], x[7], y[3], y[0], y[4], y[7], z[3], z[0], z[4], z[7]);
#pragma aspen  control execute label(block_CalcElemCharacteristicLength16) flops(1:traits(dp))
charLength=((a>charLength) ? a : charLength);
#pragma aspen  control label(block_CalcElemCharacteristicLength17) flops(2:traits(dp))
charLength=((4.0*volume)/SQRT8(charLength));
return charLength;
}

static inline void CalcElemVelocityGrandient(const double * const xvel, const double * const yvel, const double * const zvel, const double b[][8], const double detJ, double * const d)
{
const double inv_detJ = 1.0/detJ;
double dyddx;
double dxddy;
double dzddx;
double dxddz;
double dzddy;
double dyddz;
#pragma aspen  declare data(pfx:traits(Array(8, aspen_param_double)))
const double * const pfx = b[0];
#pragma aspen  declare data(pfy:traits(Array(8, aspen_param_double)))
const double * const pfy = b[1];
#pragma aspen  declare data(pfz:traits(Array(8, aspen_param_double)))
const double * const pfz = b[2];
#pragma aspen  control execute label(block_CalcElemVelocityGrandient21) flops(12:traits(dp, simd)) loads((4*aspen_param_sizeof_double):from(pfx):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
d[0]=(inv_detJ*((((pfx[0]*(xvel[0]-xvel[6]))+(pfx[1]*(xvel[1]-xvel[7])))+(pfx[2]*(xvel[2]-xvel[4])))+(pfx[3]*(xvel[3]-xvel[5]))));
#pragma aspen  control execute label(block_CalcElemVelocityGrandient22) flops(12:traits(dp, simd)) loads((4*aspen_param_sizeof_double):from(pfy):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
d[1]=(inv_detJ*((((pfy[0]*(yvel[0]-yvel[6]))+(pfy[1]*(yvel[1]-yvel[7])))+(pfy[2]*(yvel[2]-yvel[4])))+(pfy[3]*(yvel[3]-yvel[5]))));
#pragma aspen  control execute label(block_CalcElemVelocityGrandient23) flops(12:traits(dp, simd)) loads((4*aspen_param_sizeof_double):from(pfz):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0))) stores((1*aspen_param_sizeof_double):traits(stride(0)))
d[2]=(inv_detJ*((((pfz[0]*(zvel[0]-zvel[6]))+(pfz[1]*(zvel[1]-zvel[7])))+(pfz[2]*(zvel[2]-zvel[4])))+(pfz[3]*(zvel[3]-zvel[5]))));
#pragma aspen  control execute label(block_CalcElemVelocityGrandient24) flops(12:traits(dp, simd)) loads((4*aspen_param_sizeof_double):from(pfx):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
dyddx=(inv_detJ*((((pfx[0]*(yvel[0]-yvel[6]))+(pfx[1]*(yvel[1]-yvel[7])))+(pfx[2]*(yvel[2]-yvel[4])))+(pfx[3]*(yvel[3]-yvel[5]))));
#pragma aspen  control execute label(block_CalcElemVelocityGrandient25) flops(12:traits(dp, simd)) loads((4*aspen_param_sizeof_double):from(pfy):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
dxddy=(inv_detJ*((((pfy[0]*(xvel[0]-xvel[6]))+(pfy[1]*(xvel[1]-xvel[7])))+(pfy[2]*(xvel[2]-xvel[4])))+(pfy[3]*(xvel[3]-xvel[5]))));
#pragma aspen  control execute label(block_CalcElemVelocityGrandient26) flops(12:traits(dp, simd)) loads((4*aspen_param_sizeof_double):from(pfx):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
dzddx=(inv_detJ*((((pfx[0]*(zvel[0]-zvel[6]))+(pfx[1]*(zvel[1]-zvel[7])))+(pfx[2]*(zvel[2]-zvel[4])))+(pfx[3]*(zvel[3]-zvel[5]))));
#pragma aspen  control execute label(block_CalcElemVelocityGrandient27) flops(12:traits(dp, simd)) loads((4*aspen_param_sizeof_double):from(pfz):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
dxddz=(inv_detJ*((((pfz[0]*(xvel[0]-xvel[6]))+(pfz[1]*(xvel[1]-xvel[7])))+(pfz[2]*(xvel[2]-xvel[4])))+(pfz[3]*(xvel[3]-xvel[5]))));
#pragma aspen  control execute label(block_CalcElemVelocityGrandient28) flops(12:traits(dp, simd)) loads((4*aspen_param_sizeof_double):from(pfy):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
dzddy=(inv_detJ*((((pfy[0]*(zvel[0]-zvel[6]))+(pfy[1]*(zvel[1]-zvel[7])))+(pfy[2]*(zvel[2]-zvel[4])))+(pfy[3]*(zvel[3]-zvel[5]))));
#pragma aspen  control execute label(block_CalcElemVelocityGrandient29) flops(12:traits(dp, simd)) loads((4*aspen_param_sizeof_double):from(pfz):traits(stride(0)), (8*aspen_param_sizeof_double):traits(stride(0)))
dyddz=(inv_detJ*((((pfz[0]*(yvel[0]-yvel[6]))+(pfz[1]*(yvel[1]-yvel[7])))+(pfz[2]*(yvel[2]-yvel[4])))+(pfz[3]*(yvel[3]-yvel[5]))));
#pragma aspen  control execute label(block_CalcElemVelocityGrandient30) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
d[5]=(0.5*(dxddy+dyddx));
#pragma aspen  control execute label(block_CalcElemVelocityGrandient31) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
d[4]=(0.5*(dxddz+dzddx));
#pragma aspen  control execute label(block_CalcElemVelocityGrandient32) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):traits(stride(0)))
d[3]=(0.5*(dzddy+dyddz));
return ;
}

static inline void CalcKinematicsForElems(int numElem_CalcLagrangeElements, double dt, int p_nodelist[(((45*45)*45)*8)], double m_x[(((45+1)*(45+1))*(45+1))], double m_y[(((45+1)*(45+1))*(45+1))], double m_z[(((45+1)*(45+1))*(45+1))], double m_volo[((45*45)*45)], double m_v[((45*45)*45)], double m_vnew[((45*45)*45)], double m_delv[((45*45)*45)], double m_arealg[((45*45)*45)], double m_xd[(((45+1)*(45+1))*(45+1))], double m_yd[(((45+1)*(45+1))*(45+1))], double m_zd[(((45+1)*(45+1))*(45+1))], double m_dxx[((45*45)*45)], double m_dyy[((45*45)*45)], double m_dzz[((45*45)*45)])
{
int k;
int lnode;
int j;
/* loop over all elements */
#pragma acc  parallel loop gang worker independent present(m_arealg, m_delv, m_dxx, m_dyy, m_dzz, m_v, m_vnew, m_volo, m_x, m_xd, m_y, m_yd, m_z, m_zd, p_nodelist) private(k) firstprivate(dt, j, lnode, numElem_CalcLagrangeElements)
#pragma aspen  control label(block_CalcKinematicsForElems9) loop(numElem_CalcLagrangeElements) parallelism(numElem_CalcLagrangeElements) flops(1:traits(integer))
for (k=0; k<numElem_CalcLagrangeElements;  ++ k)
{
double B[3][8];
/*  shape function derivatives */
double D[6];
double x_local[8];
double y_local[8];
double z_local[8];
double xd_local[8];
double yd_local[8];
double zd_local[8];
#pragma aspen  declare param(detJ:0.0)
double detJ = 0.0;
double volume;
double relativeVolume;
#pragma aspen  declare data(elemToNode_CalcKinematicsForElems:traits(Array(8, aspen_param_int)))
const int * const elemToNode_CalcKinematicsForElems =  & p_nodelist[(8*k)];
double dt2;
/* get nodal coordinates from global arrays and copy into local arrays. */
#pragma aspen  control label(block_CalcKinematicsForElems30) loop(8) flops(1:traits(integer))
for (lnode=0; lnode<8;  ++ lnode)
{
int gnode;
#pragma aspen  control execute label(block_CalcKinematicsForElems33) loads(((1*aspen_param_sizeof_int)*8):from(elemToNode_CalcKinematicsForElems):traits(stride(1)))
gnode=elemToNode_CalcKinematicsForElems[lnode];
#pragma aspen  control execute label(block_CalcKinematicsForElems34) loads(((1*aspen_param_sizeof_double)*8):from(m_x))
x_local[lnode]=m_x[gnode];
#pragma aspen  control execute label(block_CalcKinematicsForElems35) loads(((1*aspen_param_sizeof_double)*8):from(m_y))
y_local[lnode]=m_y[gnode];
#pragma aspen  control execute label(block_CalcKinematicsForElems36) loads(((1*aspen_param_sizeof_double)*8):from(m_z))
z_local[lnode]=m_z[gnode];
}
/* volume calculations */
volume=CalcElemVolume(x_local, y_local, z_local);
#pragma aspen  control execute label(block_CalcKinematicsForElems39) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_volo):traits(stride(1)))
relativeVolume=(volume/m_volo[k]);
#pragma aspen  control execute label(block_CalcKinematicsForElems40) stores((1*aspen_param_sizeof_double):to(m_vnew):traits(stride(1)))
m_vnew[k]=relativeVolume;
#pragma aspen  control execute label(block_CalcKinematicsForElems41) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_v):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_delv):traits(stride(1)))
m_delv[k]=(relativeVolume-m_v[k]);
/* set characteristic length */
#pragma aspen  control label(block_CalcKinematicsForElems43) stores((1*aspen_param_sizeof_double):to(m_arealg):traits(stride(1)))
m_arealg[k]=CalcElemCharacteristicLength(x_local, y_local, z_local, volume);
/* get nodal velocities from global array and copy into local arrays. */
#pragma aspen  control label(block_CalcKinematicsForElems45) loop(8) flops(1:traits(integer))
for (lnode=0; lnode<8;  ++ lnode)
{
int gnode;
#pragma aspen  control execute label(block_CalcKinematicsForElems48) loads(((1*aspen_param_sizeof_int)*8):from(elemToNode_CalcKinematicsForElems):traits(stride(1)))
gnode=elemToNode_CalcKinematicsForElems[lnode];
#pragma aspen  control execute label(block_CalcKinematicsForElems49) loads(((1*aspen_param_sizeof_double)*8):from(m_xd))
xd_local[lnode]=m_xd[gnode];
#pragma aspen  control execute label(block_CalcKinematicsForElems50) loads(((1*aspen_param_sizeof_double)*8):from(m_yd))
yd_local[lnode]=m_yd[gnode];
#pragma aspen  control execute label(block_CalcKinematicsForElems51) loads(((1*aspen_param_sizeof_double)*8):from(m_zd))
zd_local[lnode]=m_zd[gnode];
}
#pragma aspen  control execute label(block_CalcKinematicsForElems52) flops(1:traits(dp))
dt2=(0.5*dt);
#pragma aspen  control label(block_CalcKinematicsForElems53) loop(8) flops(1:traits(integer))
for (j=0; j<8;  ++ j)
{
#pragma aspen  control execute label(block_CalcKinematicsForElems54) flops((2*8):traits(dp, simd))
x_local[j]-=(dt2*xd_local[j]);
#pragma aspen  control execute label(block_CalcKinematicsForElems55) flops((2*8):traits(dp, simd))
y_local[j]-=(dt2*yd_local[j]);
#pragma aspen  control execute label(block_CalcKinematicsForElems56) flops((2*8):traits(dp, simd))
z_local[j]-=(dt2*zd_local[j]);
}
CalcElemShapeFunctionDerivatives(x_local, y_local, z_local, B, ( & detJ));
CalcElemVelocityGrandient(xd_local, yd_local, zd_local, B, detJ, D);
/* put velocity gradient quantities into their global arrays. */
#pragma aspen  control execute label(block_CalcKinematicsForElems60) stores((1*aspen_param_sizeof_double):to(m_dxx):traits(stride(1)))
m_dxx[k]=D[0];
#pragma aspen  control execute label(block_CalcKinematicsForElems61) stores((1*aspen_param_sizeof_double):to(m_dyy):traits(stride(1)))
m_dyy[k]=D[1];
#pragma aspen  control execute label(block_CalcKinematicsForElems62) stores((1*aspen_param_sizeof_double):to(m_dzz):traits(stride(1)))
m_dzz[k]=D[2];
}
return ;
}

static inline void CalcLagrangeElements(double deltatime, double p_vnew[((45*45)*45)], double m_vdov[((45*45)*45)], double m_dxx[((45*45)*45)], double m_dyy[((45*45)*45)], double m_dzz[((45*45)*45)])
{
int k;
#pragma aspen  declare param(numElem_CalcLagrangeElements:m_numElem)
int numElem_CalcLagrangeElements;
#pragma aspen  control ignore
numElem_CalcLagrangeElements=m_numElem;
int abort = 0;
#pragma aspen  control label(block_CalcLagrangeElements1225) probability(1) flops(1:traits(integer))
if (numElem_CalcLagrangeElements>0)
{
CalcKinematicsForElems(numElem_CalcLagrangeElements, deltatime, m_nodelist, m_x, m_y, m_z, m_volo, m_v, p_vnew, m_delv, m_arealg, m_xd, m_yd, m_zd, m_dxx, m_dyy, m_dzz);
/* element loop to do some stuff not included in the elemlib function. */
#pragma acc  parallel loop gang worker independent reduction(||: abort) present(m_dxx, m_dyy, m_dzz, m_vdov, p_vnew) private(k) firstprivate(numElem_CalcLagrangeElements)
#pragma aspen  control label(block_CalcLagrangeElements11) loop(numElem_CalcLagrangeElements) parallelism(numElem_CalcLagrangeElements) flops(1:traits(integer))
for (k=0; k<numElem_CalcLagrangeElements;  ++ k)
{
/* calc strain rate and apply as constraint (only done in FB element) */
double vdov;
#pragma aspen  control execute label(block_CalcLagrangeElements15) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_dxx):traits(stride(1)), (1*aspen_param_sizeof_double):from(m_dyy):traits(stride(1)), (1*aspen_param_sizeof_double):from(m_dzz):traits(stride(1)))
vdov=(m_dxx[k]+m_dyy[k])+m_dzz[k];
double vdovthird;
#pragma aspen  control execute label(block_CalcLagrangeElements18) flops(1:traits(dp))
vdovthird=vdov/3.0;
/* make the rate of deformation tensor deviatoric */
#pragma aspen  control execute label(block_CalcLagrangeElements20) stores((1*aspen_param_sizeof_double):to(m_vdov):traits(stride(1)))
m_vdov[k]=vdov;
#pragma aspen  control execute label(block_CalcLagrangeElements21) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_dxx):traits(stride(1)))
m_dxx[k]-=vdovthird;
#pragma aspen  control execute label(block_CalcLagrangeElements22) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_dyy):traits(stride(1)))
m_dyy[k]-=vdovthird;
#pragma aspen  control execute label(block_CalcLagrangeElements23) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_dzz):traits(stride(1)))
m_dzz[k]-=vdovthird;
/* See if any volumes are negative, and take appropriate action. */
#pragma aspen  control ignore
if (p_vnew[k]<=0.0)
{
abort=1;
}
}
#pragma aspen  control label(block_CalcLagrangeElements26) if(abort==1) flops(1:traits(integer))
if (abort==1)
{
#pragma aspen  control ignore
fprintf(stderr, "VolumeError in CalcLagrangeElements(); exit\n");
#pragma aspen  control ignore
exit(VolumeError);
}
}
return ;
}

static inline void CalcMonotonicQGradientsForElems(int m_nodelist[(((45*45)*45)*8)], double m_x[(((45+1)*(45+1))*(45+1))], double m_y[(((45+1)*(45+1))*(45+1))], double m_z[(((45+1)*(45+1))*(45+1))], double m_xd[(((45+1)*(45+1))*(45+1))], double m_yd[(((45+1)*(45+1))*(45+1))], double m_zd[(((45+1)*(45+1))*(45+1))], double m_volo[((45*45)*45)], double m_vnew[((45*45)*45)], double m_delx_zeta[((45*45)*45)], double m_delv_zeta[((45*45)*45)], double m_delx_xi[((45*45)*45)], double m_delv_xi[((45*45)*45)], double m_delx_eta[((45*45)*45)], double m_delv_eta[((45*45)*45)])
{
int i;
int numElem;
#pragma aspen  control ignore
numElem=m_numElem;
#pragma acc  parallel loop gang worker independent present(m_delv_eta, m_delv_xi, m_delv_zeta, m_delx_eta, m_delx_xi, m_delx_zeta, m_nodelist, m_vnew, m_volo, m_x, m_xd, m_y, m_yd, m_z, m_zd) private(i) firstprivate(numElem)
#pragma aspen  control label(block_CalcMonotonicQGradientsForElems5) loop(m_numElem) parallelism(m_numElem) flops(1:traits(integer))
for (i=0; i<numElem;  ++ i)
{
const double ptiny = 1.0E-36;
double ax;
double ay;
double az;
double dxv;
double dyv;
double dzv;
#pragma aspen  declare data(elemToNode_CalcMonotonicQGradientsForElems:traits(Array(8, aspen_param_int)))
const int * elemToNode_CalcMonotonicQGradientsForElems;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems22) flops(1:traits(integer)) loads((1*aspen_param_sizeof_int):from(m_nodelist))
elemToNode_CalcMonotonicQGradientsForElems= & m_nodelist[(8*i)];
int n0;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems25) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcMonotonicQGradientsForElems):traits(stride(0)))
n0=elemToNode_CalcMonotonicQGradientsForElems[0];
int n1;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems28) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcMonotonicQGradientsForElems):traits(stride(0)))
n1=elemToNode_CalcMonotonicQGradientsForElems[1];
int n2;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems31) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcMonotonicQGradientsForElems):traits(stride(0)))
n2=elemToNode_CalcMonotonicQGradientsForElems[2];
int n3;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems34) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcMonotonicQGradientsForElems):traits(stride(0)))
n3=elemToNode_CalcMonotonicQGradientsForElems[3];
int n4;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems37) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcMonotonicQGradientsForElems):traits(stride(0)))
n4=elemToNode_CalcMonotonicQGradientsForElems[4];
int n5;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems40) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcMonotonicQGradientsForElems):traits(stride(0)))
n5=elemToNode_CalcMonotonicQGradientsForElems[5];
int n6;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems43) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcMonotonicQGradientsForElems):traits(stride(0)))
n6=elemToNode_CalcMonotonicQGradientsForElems[6];
int n7;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems46) loads((1*aspen_param_sizeof_int):from(elemToNode_CalcMonotonicQGradientsForElems):traits(stride(0)))
n7=elemToNode_CalcMonotonicQGradientsForElems[7];
double x0;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems49) loads((1*aspen_param_sizeof_double):from(m_x))
x0=m_x[n0];
double x1;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems52) loads((1*aspen_param_sizeof_double):from(m_x))
x1=m_x[n1];
double x2;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems55) loads((1*aspen_param_sizeof_double):from(m_x))
x2=m_x[n2];
double x3;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems58) loads((1*aspen_param_sizeof_double):from(m_x))
x3=m_x[n3];
double x4;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems61) loads((1*aspen_param_sizeof_double):from(m_x))
x4=m_x[n4];
double x5;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems64) loads((1*aspen_param_sizeof_double):from(m_x))
x5=m_x[n5];
double x6;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems67) loads((1*aspen_param_sizeof_double):from(m_x))
x6=m_x[n6];
double x7;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems70) loads((1*aspen_param_sizeof_double):from(m_x))
x7=m_x[n7];
double y0;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems73) loads((1*aspen_param_sizeof_double):from(m_y))
y0=m_y[n0];
double y1;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems76) loads((1*aspen_param_sizeof_double):from(m_y))
y1=m_y[n1];
double y2;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems79) loads((1*aspen_param_sizeof_double):from(m_y))
y2=m_y[n2];
double y3;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems82) loads((1*aspen_param_sizeof_double):from(m_y))
y3=m_y[n3];
double y4;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems85) loads((1*aspen_param_sizeof_double):from(m_y))
y4=m_y[n4];
double y5;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems88) loads((1*aspen_param_sizeof_double):from(m_y))
y5=m_y[n5];
double y6;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems91) loads((1*aspen_param_sizeof_double):from(m_y))
y6=m_y[n6];
double y7;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems94) loads((1*aspen_param_sizeof_double):from(m_y))
y7=m_y[n7];
double z0;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems97) loads((1*aspen_param_sizeof_double):from(m_z))
z0=m_z[n0];
double z1;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems100) loads((1*aspen_param_sizeof_double):from(m_z))
z1=m_z[n1];
double z2;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems103) loads((1*aspen_param_sizeof_double):from(m_z))
z2=m_z[n2];
double z3;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems106) loads((1*aspen_param_sizeof_double):from(m_z))
z3=m_z[n3];
double z4;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems109) loads((1*aspen_param_sizeof_double):from(m_z))
z4=m_z[n4];
double z5;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems112) loads((1*aspen_param_sizeof_double):from(m_z))
z5=m_z[n5];
double z6;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems115) loads((1*aspen_param_sizeof_double):from(m_z))
z6=m_z[n6];
double z7;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems118) loads((1*aspen_param_sizeof_double):from(m_z))
z7=m_z[n7];
double xv0;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems121) loads((1*aspen_param_sizeof_double):from(m_xd))
xv0=m_xd[n0];
double xv1;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems124) loads((1*aspen_param_sizeof_double):from(m_xd))
xv1=m_xd[n1];
double xv2;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems127) loads((1*aspen_param_sizeof_double):from(m_xd))
xv2=m_xd[n2];
double xv3;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems130) loads((1*aspen_param_sizeof_double):from(m_xd))
xv3=m_xd[n3];
double xv4;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems133) loads((1*aspen_param_sizeof_double):from(m_xd))
xv4=m_xd[n4];
double xv5;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems136) loads((1*aspen_param_sizeof_double):from(m_xd))
xv5=m_xd[n5];
double xv6;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems139) loads((1*aspen_param_sizeof_double):from(m_xd))
xv6=m_xd[n6];
double xv7;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems142) loads((1*aspen_param_sizeof_double):from(m_xd))
xv7=m_xd[n7];
double yv0;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems145) loads((1*aspen_param_sizeof_double):from(m_yd))
yv0=m_yd[n0];
double yv1;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems148) loads((1*aspen_param_sizeof_double):from(m_yd))
yv1=m_yd[n1];
double yv2;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems151) loads((1*aspen_param_sizeof_double):from(m_yd))
yv2=m_yd[n2];
double yv3;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems154) loads((1*aspen_param_sizeof_double):from(m_yd))
yv3=m_yd[n3];
double yv4;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems157) loads((1*aspen_param_sizeof_double):from(m_yd))
yv4=m_yd[n4];
double yv5;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems160) loads((1*aspen_param_sizeof_double):from(m_yd))
yv5=m_yd[n5];
double yv6;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems163) loads((1*aspen_param_sizeof_double):from(m_yd))
yv6=m_yd[n6];
double yv7;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems166) loads((1*aspen_param_sizeof_double):from(m_yd))
yv7=m_yd[n7];
double zv0;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems169) loads((1*aspen_param_sizeof_double):from(m_zd))
zv0=m_zd[n0];
double zv1;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems172) loads((1*aspen_param_sizeof_double):from(m_zd))
zv1=m_zd[n1];
double zv2;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems175) loads((1*aspen_param_sizeof_double):from(m_zd))
zv2=m_zd[n2];
double zv3;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems178) loads((1*aspen_param_sizeof_double):from(m_zd))
zv3=m_zd[n3];
double zv4;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems181) loads((1*aspen_param_sizeof_double):from(m_zd))
zv4=m_zd[n4];
double zv5;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems184) loads((1*aspen_param_sizeof_double):from(m_zd))
zv5=m_zd[n5];
double zv6;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems187) loads((1*aspen_param_sizeof_double):from(m_zd))
zv6=m_zd[n6];
double zv7;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems190) loads((1*aspen_param_sizeof_double):from(m_zd))
zv7=m_zd[n7];
double vol;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems193) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_vnew):traits(stride(1)), (1*aspen_param_sizeof_double):from(m_volo):traits(stride(1)))
vol=m_volo[i]*m_vnew[i];
double norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems196) flops(2:traits(dp))
norm=1.0/(vol+ptiny);
double dxj;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems199) flops(8:traits(dp))
dxj=( - 0.25)*((((x0+x1)+x5)+x4)-(((x3+x2)+x6)+x7));
double dyj;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems202) flops(8:traits(dp))
dyj=( - 0.25)*((((y0+y1)+y5)+y4)-(((y3+y2)+y6)+y7));
double dzj;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems205) flops(8:traits(dp))
dzj=( - 0.25)*((((z0+z1)+z5)+z4)-(((z3+z2)+z6)+z7));
double dxi;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems208) flops(8:traits(dp))
dxi=0.25*((((x1+x2)+x6)+x5)-(((x0+x3)+x7)+x4));
double dyi;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems211) flops(8:traits(dp))
dyi=0.25*((((y1+y2)+y6)+y5)-(((y0+y3)+y7)+y4));
double dzi;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems214) flops(8:traits(dp))
dzi=0.25*((((z1+z2)+z6)+z5)-(((z0+z3)+z7)+z4));
double dxk;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems217) flops(8:traits(dp))
dxk=0.25*((((x4+x5)+x6)+x7)-(((x0+x1)+x2)+x3));
double dyk;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems220) flops(8:traits(dp))
dyk=0.25*((((y4+y5)+y6)+y7)-(((y0+y1)+y2)+y3));
double dzk;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems223) flops(8:traits(dp))
dzk=0.25*((((z4+z5)+z6)+z7)-(((z0+z1)+z2)+z3));
/* find delvk and delxk ( i cross j ) */
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems225) flops(3:traits(dp))
ax=((dyi*dzj)-(dzi*dyj));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems226) flops(3:traits(dp))
ay=((dzi*dxj)-(dxi*dzj));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems227) flops(3:traits(dp))
az=((dxi*dyj)-(dyi*dxj));
#pragma aspen  control label(block_CalcMonotonicQGradientsForElems228) flops(7:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_delx_zeta):traits(stride(1)))
m_delx_zeta[i]=(vol/SQRT8(((((ax*ax)+(ay*ay))+(az*az))+ptiny)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems229) flops(1:traits(dp))
ax*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems230) flops(1:traits(dp))
ay*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems231) flops(1:traits(dp))
az*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems232) flops(8:traits(dp))
dxv=(0.25*((((xv4+xv5)+xv6)+xv7)-(((xv0+xv1)+xv2)+xv3)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems233) flops(8:traits(dp))
dyv=(0.25*((((yv4+yv5)+yv6)+yv7)-(((yv0+yv1)+yv2)+yv3)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems234) flops(8:traits(dp))
dzv=(0.25*((((zv4+zv5)+zv6)+zv7)-(((zv0+zv1)+zv2)+zv3)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems235) flops(5:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_delv_zeta):traits(stride(1)))
m_delv_zeta[i]=(((ax*dxv)+(ay*dyv))+(az*dzv));
/* find delxi and delvi ( j cross k ) */
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems237) flops(3:traits(dp))
ax=((dyj*dzk)-(dzj*dyk));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems238) flops(3:traits(dp))
ay=((dzj*dxk)-(dxj*dzk));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems239) flops(3:traits(dp))
az=((dxj*dyk)-(dyj*dxk));
#pragma aspen  control label(block_CalcMonotonicQGradientsForElems240) flops(7:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_delx_xi):traits(stride(1)))
m_delx_xi[i]=(vol/SQRT8(((((ax*ax)+(ay*ay))+(az*az))+ptiny)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems241) flops(1:traits(dp))
ax*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems242) flops(1:traits(dp))
ay*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems243) flops(1:traits(dp))
az*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems244) flops(8:traits(dp))
dxv=(0.25*((((xv1+xv2)+xv6)+xv5)-(((xv0+xv3)+xv7)+xv4)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems245) flops(8:traits(dp))
dyv=(0.25*((((yv1+yv2)+yv6)+yv5)-(((yv0+yv3)+yv7)+yv4)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems246) flops(8:traits(dp))
dzv=(0.25*((((zv1+zv2)+zv6)+zv5)-(((zv0+zv3)+zv7)+zv4)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems247) flops(5:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_delv_xi):traits(stride(1)))
m_delv_xi[i]=(((ax*dxv)+(ay*dyv))+(az*dzv));
/* find delxj and delvj ( k cross i ) */
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems249) flops(3:traits(dp))
ax=((dyk*dzi)-(dzk*dyi));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems250) flops(3:traits(dp))
ay=((dzk*dxi)-(dxk*dzi));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems251) flops(3:traits(dp))
az=((dxk*dyi)-(dyk*dxi));
#pragma aspen  control label(block_CalcMonotonicQGradientsForElems252) flops(7:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_delx_eta):traits(stride(1)))
m_delx_eta[i]=(vol/SQRT8(((((ax*ax)+(ay*ay))+(az*az))+ptiny)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems253) flops(1:traits(dp))
ax*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems254) flops(1:traits(dp))
ay*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems255) flops(1:traits(dp))
az*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems256) flops(8:traits(dp))
dxv=(( - 0.25)*((((xv0+xv1)+xv5)+xv4)-(((xv3+xv2)+xv6)+xv7)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems257) flops(8:traits(dp))
dyv=(( - 0.25)*((((yv0+yv1)+yv5)+yv4)-(((yv3+yv2)+yv6)+yv7)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems258) flops(8:traits(dp))
dzv=(( - 0.25)*((((zv0+zv1)+zv5)+zv4)-(((zv3+zv2)+zv6)+zv7)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems259) flops(5:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_delv_eta):traits(stride(1)))
m_delv_eta[i]=(((ax*dxv)+(ay*dyv))+(az*dzv));
}
return ;
}

/* parameters */
/* the elementset length */
static inline void CalcMonotonicQRegionForElems(double qlc_monoq, double qqc_monoq, double monoq_limiter_mult, double monoq_max_slope, double ptiny, int elength, int m_matElemlist[((45*45)*45)], int m_elemBC[((45*45)*45)], double p_delx_xi[((45*45)*45)], double p_delx_eta[((45*45)*45)], double p_delx_zeta[((45*45)*45)], double m_delv_xi[((45*45)*45)], double m_delv_eta[((45*45)*45)], double m_delv_zeta[((45*45)*45)], int m_lxim[((45*45)*45)], int m_lxip[((45*45)*45)], int m_letam[((45*45)*45)], int m_letap[((45*45)*45)], int m_lzetam[((45*45)*45)], int m_lzetap[((45*45)*45)], double p_vnew[((45*45)*45)], double m_vdov[((45*45)*45)], double p_volo[((45*45)*45)], double p_elemMass[((45*45)*45)], double m_qq[((45*45)*45)], double m_ql[((45*45)*45)])
{
int ielem;
#pragma acc  parallel loop gang worker independent present(m_delv_eta, m_delv_xi, m_delv_zeta, m_elemBC, m_letam, m_letap, m_lxim, m_lxip, m_lzetam, m_lzetap, m_matElemlist, m_ql, m_qq, m_vdov, p_delx_eta, p_delx_xi, p_delx_zeta, p_elemMass, p_vnew, p_volo) private(ielem) firstprivate(elength, monoq_limiter_mult, monoq_max_slope, ptiny, qlc_monoq, qqc_monoq)
#pragma aspen  control label(block_CalcMonotonicQRegionForElems8) loop(elength) parallelism(elength) flops(1:traits(integer))
for (ielem=0; ielem<elength;  ++ ielem)
{
double qlin;
double qquad;
double phixi;
double phieta;
double phizeta;
int i;
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems21) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
i=m_matElemlist[ielem];
int bcMask;
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems24) loads((1*aspen_param_sizeof_int):from(m_elemBC))
bcMask=m_elemBC[i];
double delvm;
double delvp;
/*  phixi     */
double norm;
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems32) flops(2:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_delv_xi))
norm=1.0/(m_delv_xi[i]+ptiny);
switch ((bcMask&0x3))
{
case 0:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems35) loads((1*aspen_param_sizeof_double):from(m_delv_xi):traits(random), (1*aspen_param_sizeof_int):from(m_lxim))
delvm=m_delv_xi[m_lxim[i]];
break;
case 0x1:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems38) loads((1*aspen_param_sizeof_double):from(m_delv_xi))
delvm=m_delv_xi[i];
break;
case 0x2:
#pragma aspen  control ignore
delvm=0.0;
break;
/* ERROR */
default:
;
break;
}
switch ((bcMask&0xc))
{
case 0:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems49) loads((1*aspen_param_sizeof_double):from(m_delv_xi):traits(random), (1*aspen_param_sizeof_int):from(m_lxip))
delvp=m_delv_xi[m_lxip[i]];
break;
case 0x4:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems52) loads((1*aspen_param_sizeof_double):from(m_delv_xi))
delvp=m_delv_xi[i];
break;
case 0x8:
#pragma aspen  control ignore
delvp=0.0;
break;
/* ERROR */
default:
;
break;
}
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems61) flops(1:traits(dp))
delvm=(delvm*norm);
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems62) flops(1:traits(dp))
delvp=(delvp*norm);
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems63) flops(2:traits(dp))
phixi=(0.5*(delvm+delvp));
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems64) flops(1:traits(dp))
delvm*=monoq_limiter_mult;
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems65) flops(1:traits(dp))
delvp*=monoq_limiter_mult;
#pragma aspen  control label(block_CalcMonotonicQRegionForElems66) if(delvm<phixi) flops(1:traits(dp))
if (delvm<phixi)
{
#pragma aspen  control ignore
phixi=delvm;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems68) if(delvp<phixi) flops(1:traits(dp))
if (delvp<phixi)
{
#pragma aspen  control ignore
phixi=delvp;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems70) if(phixi<0.0) flops(1:traits(dp))
if (phixi<0.0)
{
#pragma aspen  control ignore
phixi=0.0;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems72) if(phixi>monoq_max_slope) flops(1:traits(dp))
if (phixi>monoq_max_slope)
{
#pragma aspen  control ignore
phixi=monoq_max_slope;
}
/*  phieta     */
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems75) flops(2:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_delv_eta))
norm=(1.0/(m_delv_eta[i]+ptiny));
switch ((bcMask&0x30))
{
case 0:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems78) loads((1*aspen_param_sizeof_double):from(m_delv_eta):traits(random), (1*aspen_param_sizeof_int):from(m_letam))
delvm=m_delv_eta[m_letam[i]];
break;
case 0x10:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems81) loads((1*aspen_param_sizeof_double):from(m_delv_eta))
delvm=m_delv_eta[i];
break;
case 0x20:
#pragma aspen  control ignore
delvm=0.0;
break;
/* ERROR */
default:
;
break;
}
switch ((bcMask&0xc0))
{
case 0:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems92) loads((1*aspen_param_sizeof_double):from(m_delv_eta):traits(random), (1*aspen_param_sizeof_int):from(m_letap))
delvp=m_delv_eta[m_letap[i]];
break;
case 0x40:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems95) loads((1*aspen_param_sizeof_double):from(m_delv_eta))
delvp=m_delv_eta[i];
break;
case 0x80:
#pragma aspen  control ignore
delvp=0.0;
break;
/* ERROR */
default:
;
break;
}
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems104) flops(1:traits(dp))
delvm=(delvm*norm);
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems105) flops(1:traits(dp))
delvp=(delvp*norm);
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems106) flops(2:traits(dp))
phieta=(0.5*(delvm+delvp));
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems107) flops(1:traits(dp))
delvm*=monoq_limiter_mult;
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems108) flops(1:traits(dp))
delvp*=monoq_limiter_mult;
#pragma aspen  control label(block_CalcMonotonicQRegionForElems109) if(delvm<phieta) flops(1:traits(dp))
if (delvm<phieta)
{
#pragma aspen  control ignore
phieta=delvm;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems111) if(delvp<phieta) flops(1:traits(dp))
if (delvp<phieta)
{
#pragma aspen  control ignore
phieta=delvp;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems113) if(phieta<0.0) flops(1:traits(dp))
if (phieta<0.0)
{
#pragma aspen  control ignore
phieta=0.0;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems115) if(phieta>monoq_max_slope) flops(1:traits(dp))
if (phieta>monoq_max_slope)
{
#pragma aspen  control ignore
phieta=monoq_max_slope;
}
/*  phizeta     */
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems118) flops(2:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_delv_zeta))
norm=(1.0/(m_delv_zeta[i]+ptiny));
switch ((bcMask&0x300))
{
case 0:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems121) loads((1*aspen_param_sizeof_double):from(m_delv_zeta):traits(random), (1*aspen_param_sizeof_int):from(m_lzetam))
delvm=m_delv_zeta[m_lzetam[i]];
break;
case 0x100:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems124) loads((1*aspen_param_sizeof_double):from(m_delv_zeta))
delvm=m_delv_zeta[i];
break;
case 0x200:
#pragma aspen  control ignore
delvm=0.0;
break;
/* ERROR */
default:
;
break;
}
switch ((bcMask&0xc00))
{
case 0:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems135) loads((1*aspen_param_sizeof_double):from(m_delv_zeta):traits(random), (1*aspen_param_sizeof_int):from(m_lzetap))
delvp=m_delv_zeta[m_lzetap[i]];
break;
case 0x400:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems138) loads((1*aspen_param_sizeof_double):from(m_delv_zeta))
delvp=m_delv_zeta[i];
break;
case 0x800:
#pragma aspen  control ignore
delvp=0.0;
break;
/* ERROR */
default:
;
break;
}
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems147) flops(1:traits(dp))
delvm=(delvm*norm);
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems148) flops(1:traits(dp))
delvp=(delvp*norm);
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems149) flops(2:traits(dp))
phizeta=(0.5*(delvm+delvp));
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems150) flops(1:traits(dp))
delvm*=monoq_limiter_mult;
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems151) flops(1:traits(dp))
delvp*=monoq_limiter_mult;
#pragma aspen  control label(block_CalcMonotonicQRegionForElems152) if(delvm<phizeta) flops(1:traits(dp))
if (delvm<phizeta)
{
#pragma aspen  control ignore
phizeta=delvm;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems154) if(delvp<phizeta) flops(1:traits(dp))
if (delvp<phizeta)
{
#pragma aspen  control ignore
phizeta=delvp;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems156) if(phizeta<0.0) flops(1:traits(dp))
if (phizeta<0.0)
{
#pragma aspen  control ignore
phizeta=0.0;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems158) if(phizeta>monoq_max_slope) flops(1:traits(dp))
if (phizeta>monoq_max_slope)
{
#pragma aspen  control ignore
phizeta=monoq_max_slope;
}
/* Remove length scale */
#pragma aspen  control label(block_CalcMonotonicQRegionForElems1746) probability(1) flops(1:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_vdov))
if (m_vdov[i]>0.0)
{
#pragma aspen  control ignore
qlin=0.0;
#pragma aspen  control ignore
qquad=0.0;
}
else
{
#pragma aspen  declare param(delvxxi)
double delvxxi;
#pragma aspen  control execute flops(1:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_delv_xi), (1*aspen_param_sizeof_double):from(p_delx_xi))
delvxxi=m_delv_xi[i]*p_delx_xi[i];
#pragma aspen  declare param(delvxeta)
double delvxeta;
#pragma aspen  control execute flops(1:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_delv_eta), (1*aspen_param_sizeof_double):from(p_delx_eta))
delvxeta=m_delv_eta[i]*p_delx_eta[i];
#pragma aspen  declare param(delvxzeta)
double delvxzeta;
#pragma aspen  control execute flops(1:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_delv_zeta), (1*aspen_param_sizeof_double):from(p_delx_zeta))
delvxzeta=m_delv_zeta[i]*p_delx_zeta[i];
#pragma aspen  declare param(rho)
double rho;
#pragma aspen  control ignore
if (delvxxi>0.0)
{
delvxxi=0.0;
}
#pragma aspen  control ignore
if (delvxeta>0.0)
{
delvxeta=0.0;
}
#pragma aspen  control ignore
if (delvxzeta>0.0)
{
delvxzeta=0.0;
}
#pragma aspen  control execute flops(2:traits(dp)) loads((1*aspen_param_sizeof_double):from(p_elemMass), (1*aspen_param_sizeof_double):from(p_vnew), (1*aspen_param_sizeof_double):from(p_volo))
rho=(p_elemMass[i]/(p_volo[i]*p_vnew[i]));
#pragma aspen  control execute flops(10:traits(dp))
qlin=((( - qlc_monoq)*rho)*(((delvxxi*(1.0-phixi))+(delvxeta*(1.0-phieta)))+(delvxzeta*(1.0-phizeta))));
#pragma aspen  control execute flops(16:traits(dp))
qquad=((qqc_monoq*rho)*((((delvxxi*delvxxi)*(1.0-(phixi*phixi)))+((delvxeta*delvxeta)*(1.0-(phieta*phieta))))+((delvxzeta*delvxzeta)*(1.0-(phizeta*phizeta)))));
}
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems164) stores((1*aspen_param_sizeof_double):to(m_qq))
m_qq[i]=qquad;
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems165) stores((1*aspen_param_sizeof_double):to(m_ql))
m_ql[i]=qlin;
}
return ;
}

static inline void CalcMonotonicQForElems()
{
/*  */
/* initialize parameters */
/*  */
const double ptiny = 1.0E-36;
double monoq_max_slope;
#pragma aspen  control ignore
monoq_max_slope=m_monoq_max_slope;
double monoq_limiter_mult;
#pragma aspen  control ignore
monoq_limiter_mult=m_monoq_limiter_mult;
/*  */
/* calculate the monotonic q for pure regions */
/*  */
#pragma aspen  declare param(elength:m_numElem)
int elength;
#pragma aspen  control ignore
elength=m_numElem;
#pragma aspen  control label(block_CalcMonotonicQForElems1588) probability(1) flops(1:traits(integer))
if (elength>0)
{
double qlc_monoq;
#pragma aspen  control ignore
qlc_monoq=m_qlc_monoq;
double qqc_monoq;
#pragma aspen  control ignore
qqc_monoq=m_qqc_monoq;
/* parameters */
/* the elemset length */
CalcMonotonicQRegionForElems(qlc_monoq, qqc_monoq, monoq_limiter_mult, monoq_max_slope, ptiny, elength, m_matElemlist, m_elemBC, m_delx_xi, m_delx_eta, m_delx_zeta, m_delv_xi, m_delv_eta, m_delv_zeta, m_lxim, m_lxip, m_letam, m_letap, m_lzetam, m_lzetap, m_vnew, m_vdov, m_volo, m_elemMass, m_qq, m_ql);
}
return ;
}

static inline void CalcQForElems()
{
int i;
double qstop;
#pragma aspen  control ignore
qstop=m_qstop;
int numElem;
#pragma aspen  control ignore
numElem=m_numElem;
/*  */
/* MONOTONIC Q option */
/*  */
/* Calculate velocity gradients */
CalcMonotonicQGradientsForElems(m_nodelist, m_x, m_y, m_z, m_xd, m_yd, m_zd, m_volo, m_vnew, m_delx_zeta, m_delv_zeta, m_delx_xi, m_delv_xi, m_delx_eta, m_delv_eta);
/* Transfer veloctiy gradients in the first order elements */
/* problem->commElements->Transfer(CommElements::monoQ) ; */
CalcMonotonicQForElems();
/* Don't allow excessive artificial viscosity */
#pragma aspen  control ignore
if (numElem!=0)
{
/* Index_t idx = -1;  */
int idx = 0;
#pragma acc  parallel loop gang worker independent reduction(||: idx) present(m_q) private(i) firstprivate(numElem, qstop)
for (i=0; i<numElem;  ++ i)
{
if (m_q[i]>qstop)
{
idx=1;
/* break ; */
}
}
if (idx==1)
{
fprintf(stderr, "QStopError in CalcQForElems(); exit\n");
exit(QStopError);
}
}
return ;
}

static inline void CalcPressureForElems(double pHalfStep[((45*45)*45)], double bvc[((45*45)*45)], double pbvc[((45*45)*45)], double e_new[((45*45)*45)], double compHalfStep[((45*45)*45)], double vnewc[((45*45)*45)], double pmin, double p_cut, double eosvmax, int length)
{
int i;
#pragma acc  parallel loop gang worker independent present(bvc, compHalfStep, pbvc) private(i) firstprivate(length)
#pragma aspen  control label(block_CalcPressureForElems6) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
double c1s;
#pragma aspen  control execute label(block_CalcPressureForElems9) flops(1:traits(dp))
c1s=2.0/3.0;
#pragma aspen  control execute label(block_CalcPressureForElems10) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(compHalfStep):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(bvc):traits(stride(1)))
bvc[i]=(c1s*(compHalfStep[i]+1.0));
#pragma aspen  control execute label(block_CalcPressureForElems11) stores((1*aspen_param_sizeof_double):to(pbvc):traits(stride(1)))
pbvc[i]=c1s;
}
#pragma acc  parallel loop gang worker independent present(bvc, e_new, pHalfStep, vnewc) private(i) firstprivate(eosvmax, length, p_cut, pmin)
#pragma aspen  control label(block_CalcPressureForElems12) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  control execute label(block_CalcPressureForElems13) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(bvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_new):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(pHalfStep):traits(stride(1)))
pHalfStep[i]=(bvc[i]*e_new[i]);
#pragma aspen  control label(block_CalcPressureForElems1876) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(pHalfStep):traits(stride(1)))
if (FABS8(pHalfStep[i])<p_cut)
{
#pragma aspen  control execute label(block_CalcPressureForElems15) stores((1*aspen_param_sizeof_double):to(pHalfStep):traits(stride(1)))
pHalfStep[i]=0.0;
}
/* impossible condition here? */
#pragma aspen  control ignore
if (vnewc[i]>=eosvmax)
{
pHalfStep[i]=0.0;
}
#pragma aspen  control label(block_CalcPressureForElems1880) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(pHalfStep):traits(stride(1)))
if (pHalfStep[i]<pmin)
{
#pragma aspen  control execute label(block_CalcPressureForElems19) stores((1*aspen_param_sizeof_double):to(pHalfStep):traits(stride(1)))
pHalfStep[i]=pmin;
}
}
return ;
}

static inline void CalcPressureForElems_clnd2(double p_new[((45*45)*45)], double bvc[((45*45)*45)], double pbvc[((45*45)*45)], double e_new[((45*45)*45)], double compression[((45*45)*45)], double vnewc[((45*45)*45)], double pmin, double p_cut, double eosvmax, int length)
{
int i;
#pragma acc  parallel loop gang worker independent present(bvc, compression, pbvc) private(i) firstprivate(length)
#pragma aspen  control label(block_CalcPressureForElems_clnd26) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
double c1s;
#pragma aspen  control execute label(block_CalcPressureForElems_clnd29) flops(1:traits(dp))
c1s=2.0/3.0;
#pragma aspen  control execute label(block_CalcPressureForElems_clnd210) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(compression):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(bvc):traits(stride(1)))
bvc[i]=(c1s*(compression[i]+1.0));
#pragma aspen  control execute label(block_CalcPressureForElems_clnd211) stores((1*aspen_param_sizeof_double):to(pbvc):traits(stride(1)))
pbvc[i]=c1s;
}
#pragma acc  parallel loop gang worker independent present(bvc, e_new, p_new, vnewc) private(i) firstprivate(eosvmax, length, p_cut, pmin)
#pragma aspen  control label(block_CalcPressureForElems_clnd212) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  control execute label(block_CalcPressureForElems_clnd213) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(bvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_new):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(p_new):traits(stride(1)))
p_new[i]=(bvc[i]*e_new[i]);
#pragma aspen  control label(block_CalcPressureForElems_clnd21947) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(p_new):traits(stride(1)))
if (FABS8(p_new[i])<p_cut)
{
#pragma aspen  control execute label(block_CalcPressureForElems_clnd215) stores((1*aspen_param_sizeof_double):to(p_new):traits(stride(1)))
p_new[i]=0.0;
}
/* impossible condition here? */
#pragma aspen  control ignore
if (vnewc[i]>=eosvmax)
{
p_new[i]=0.0;
}
#pragma aspen  control label(block_CalcPressureForElems_clnd21951) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(p_new):traits(stride(1)))
if (p_new[i]<pmin)
{
#pragma aspen  control execute label(block_CalcPressureForElems_clnd219) stores((1*aspen_param_sizeof_double):to(p_new):traits(stride(1)))
p_new[i]=pmin;
}
}
return ;
}

static inline void CalcPressureForElems_clnd1(double p_new[((45*45)*45)], double bvc[((45*45)*45)], double pbvc[((45*45)*45)], double e_new[((45*45)*45)], double compression[((45*45)*45)], double vnewc[((45*45)*45)], double pmin, double p_cut, double eosvmax, int length)
{
int i;
#pragma acc  parallel loop gang worker independent present(bvc, compression, pbvc) private(i) firstprivate(length)
#pragma aspen  control label(block_CalcPressureForElems_clnd16) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
double c1s;
#pragma aspen  control execute label(block_CalcPressureForElems_clnd19) flops(1:traits(dp))
c1s=2.0/3.0;
#pragma aspen  control execute label(block_CalcPressureForElems_clnd110) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(compression):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(bvc):traits(stride(1)))
bvc[i]=(c1s*(compression[i]+1.0));
#pragma aspen  control execute label(block_CalcPressureForElems_clnd111) stores((1*aspen_param_sizeof_double):to(pbvc):traits(stride(1)))
pbvc[i]=c1s;
}
#pragma acc  parallel loop gang worker independent present(bvc, e_new, p_new, vnewc) private(i) firstprivate(eosvmax, length, p_cut, pmin)
#pragma aspen  control label(block_CalcPressureForElems_clnd112) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  control execute label(block_CalcPressureForElems_clnd113) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(bvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_new):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(p_new):traits(stride(1)))
p_new[i]=(bvc[i]*e_new[i]);
#pragma aspen  control label(block_CalcPressureForElems_clnd11913) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(p_new):traits(stride(1)))
if (FABS8(p_new[i])<p_cut)
{
#pragma aspen  control execute label(block_CalcPressureForElems_clnd115) stores((1*aspen_param_sizeof_double):to(p_new):traits(stride(1)))
p_new[i]=0.0;
}
/* impossible condition here? */
#pragma aspen  control ignore
if (vnewc[i]>=eosvmax)
{
p_new[i]=0.0;
}
#pragma aspen  control label(block_CalcPressureForElems_clnd11917) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(p_new):traits(stride(1)))
if (p_new[i]<pmin)
{
#pragma aspen  control execute label(block_CalcPressureForElems_clnd119) stores((1*aspen_param_sizeof_double):to(p_new):traits(stride(1)))
p_new[i]=pmin;
}
}
return ;
}

static inline void CalcEnergyForElems(double p_new[((45*45)*45)], double e_new[((45*45)*45)], double q_new[((45*45)*45)], double bvc[((45*45)*45)], double pbvc[((45*45)*45)], double p_old[((45*45)*45)], double e_old[((45*45)*45)], double q_old[((45*45)*45)], double compression[((45*45)*45)], double compHalfStep[((45*45)*45)], double vnewc[((45*45)*45)], double * work, double * delvc, double pmin, double p_cut, double e_cut, double q_cut, double emin, double * qq, double * ql, double rho0, double eosvmax, int length)
{
int i;
#pragma aspen  declare data(pHalfStep:traits(Array(length, aspen_param_sizeof_double)))
double * pHalfStep;
pHalfStep=Allocate(length);
#pragma acc  data create(pHalfStep[0:length])
{
#pragma acc  parallel loop gang worker independent present(delvc, e_new, e_old, p_old, q_old, work) private(i) firstprivate(emin, length)
#pragma aspen  control label(block_CalcEnergyForElems14) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  control execute label(block_CalcEnergyForElems15) flops(6:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(delvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_old):traits(stride(1)), (1*aspen_param_sizeof_double):from(p_old):traits(stride(1)), (1*aspen_param_sizeof_double):from(q_old):traits(stride(1)), (1*aspen_param_sizeof_double):from(work):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]=((e_old[i]-((0.5*delvc[i])*(p_old[i]+q_old[i])))+(0.5*work[i]));
#pragma aspen  control label(block_CalcEnergyForElems1861) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(e_new):traits(stride(1)))
if (e_new[i]<emin)
{
#pragma aspen  control execute label(block_CalcEnergyForElems17) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]=emin;
}
}
CalcPressureForElems(pHalfStep, bvc, pbvc, e_new, compHalfStep, vnewc, pmin, p_cut, eosvmax, length);
#pragma acc  parallel loop gang worker independent present(bvc, compHalfStep, delvc, e_new, pHalfStep, p_old, pbvc, q_new, q_old, ql, qq) private(i) firstprivate(length, rho0)
#pragma aspen  control label(block_CalcEnergyForElems19) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
double vhalf;
#pragma aspen  control execute label(block_CalcEnergyForElems22) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(compHalfStep):traits(stride(1)))
vhalf=1.0/(1.0+compHalfStep[i]);
#pragma aspen  control label(block_CalcEnergyForElems1886) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(delvc):traits(stride(1)))
if (delvc[i]>0.0)
{
/* = qq[i] = ql[i] */
#pragma aspen  control execute label(block_CalcEnergyForElems25) stores((1*aspen_param_sizeof_double):to(q_new):traits(stride(1)))
q_new[i]=0.0;
}
else
{
#pragma aspen  declare param(ssc)
double ssc;
#pragma aspen  control execute flops(6:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(bvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(pHalfStep):traits(stride(1)), (1*aspen_param_sizeof_double):from(pbvc):traits(stride(1)))
ssc=((pbvc[i]*e_new[i])+(((vhalf*vhalf)*bvc[i])*pHalfStep[i]))/rho0;
#pragma aspen  control ignore
if (ssc<=0.0)
{
ssc=3.33333E-37;
}
else
{
ssc=SQRT8(ssc);
}
#pragma aspen  control execute flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(ql):traits(stride(1)), (1*aspen_param_sizeof_double):from(qq):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(q_new):traits(stride(1)))
q_new[i]=((ssc*ql[i])+qq[i]);
}
#pragma aspen  control execute label(block_CalcEnergyForElems26) flops(8:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(delvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(pHalfStep):traits(stride(1)), (1*aspen_param_sizeof_double):from(p_old):traits(stride(1)), (1*aspen_param_sizeof_double):from(q_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(q_old):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]=(e_new[i]+((0.5*delvc[i])*((3.0*(p_old[i]+q_old[i]))-(4.0*(pHalfStep[i]+q_new[i])))));
}
#pragma acc  parallel loop gang worker independent present(e_new, work) private(i) firstprivate(e_cut, emin, length)
#pragma aspen  control label(block_CalcEnergyForElems27) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  control execute label(block_CalcEnergyForElems28) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(work):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]+=(0.5*work[i]);
#pragma aspen  control label(block_CalcEnergyForElems1896) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(e_new):traits(stride(1)))
if (FABS8(e_new[i])<e_cut)
{
#pragma aspen  control execute label(block_CalcEnergyForElems30) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]=0.0;
}
#pragma aspen  control label(block_CalcEnergyForElems1898) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(e_new):traits(stride(1)))
if (e_new[i]<emin)
{
#pragma aspen  control execute label(block_CalcEnergyForElems32) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]=emin;
}
}
CalcPressureForElems_clnd1(p_new, bvc, pbvc, e_new, compression, vnewc, pmin, p_cut, eosvmax, length);
#pragma acc  parallel loop gang worker independent present(bvc, delvc, e_new, pHalfStep, p_new, p_old, pbvc, q_new, q_old, ql, qq, vnewc) private(i) firstprivate(e_cut, emin, length, rho0)
#pragma aspen  control label(block_CalcEnergyForElems34) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
const double sixth = 1.0/6.0;
double q_tilde;
#pragma aspen  control label(block_CalcEnergyForElems1923) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(delvc):traits(stride(1)))
if (delvc[i]>0.0)
{
#pragma aspen  control ignore
q_tilde=0.0;
}
else
{
#pragma aspen  declare param(ssc)
double ssc;
#pragma aspen  control execute flops(6:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(bvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(p_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(pbvc):traits(stride(1)), (2*aspen_param_sizeof_double):from(vnewc):traits(stride(1)))
ssc=((pbvc[i]*e_new[i])+(((vnewc[i]*vnewc[i])*bvc[i])*p_new[i]))/rho0;
#pragma aspen  control ignore
if (ssc<=0.0)
{
ssc=3.33333E-37;
}
else
{
ssc=SQRT8(ssc);
}
#pragma aspen  control execute flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(ql):traits(stride(1)), (1*aspen_param_sizeof_double):from(qq):traits(stride(1)))
q_tilde=((ssc*ql[i])+qq[i]);
}
#pragma aspen  control execute label(block_CalcEnergyForElems41) flops(10:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(delvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(pHalfStep):traits(stride(1)), (1*aspen_param_sizeof_double):from(p_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(p_old):traits(stride(1)), (1*aspen_param_sizeof_double):from(q_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(q_old):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]=(e_new[i]-(((((7.0*(p_old[i]+q_old[i]))-(8.0*(pHalfStep[i]+q_new[i])))+(p_new[i]+q_tilde))*delvc[i])*sixth));
#pragma aspen  control label(block_CalcEnergyForElems1930) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(e_new):traits(stride(1)))
if (FABS8(e_new[i])<e_cut)
{
#pragma aspen  control execute label(block_CalcEnergyForElems43) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]=0.0;
}
#pragma aspen  control label(block_CalcEnergyForElems1932) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(e_new):traits(stride(1)))
if (e_new[i]<emin)
{
#pragma aspen  control execute label(block_CalcEnergyForElems45) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]=emin;
}
}
CalcPressureForElems_clnd2(p_new, bvc, pbvc, e_new, compression, vnewc, pmin, p_cut, eosvmax, length);
#pragma acc  parallel loop gang worker independent present(bvc, delvc, e_new, p_new, pbvc, q_new, ql, qq, vnewc) private(i) firstprivate(length, q_cut, rho0)
#pragma aspen  control label(block_CalcEnergyForElems47) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  control label(block_CalcEnergyForElems1955) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(delvc):traits(stride(1)))
if (delvc[i]<=0.0)
{
double ssc;
#pragma aspen  control execute label(block_CalcEnergyForElems51) flops(6:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(bvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(p_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(pbvc):traits(stride(1)), (2*aspen_param_sizeof_double):from(vnewc):traits(stride(1)))
ssc=((pbvc[i]*e_new[i])+(((vnewc[i]*vnewc[i])*bvc[i])*p_new[i]))/rho0;
#pragma aspen  control ignore
if (ssc<=0.0)
{
ssc=3.33333E-37;
}
else
{
ssc=SQRT8(ssc);
}
#pragma aspen  control execute label(block_CalcEnergyForElems53) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(ql):traits(stride(1)), (1*aspen_param_sizeof_double):from(qq):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(q_new):traits(stride(1)))
q_new[i]=((ssc*ql[i])+qq[i]);
#pragma aspen  control label(block_CalcEnergyForElems1960) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(q_new):traits(stride(1)))
if (FABS8(q_new[i])<q_cut)
{
#pragma aspen  control execute label(block_CalcEnergyForElems55) stores((1*aspen_param_sizeof_double):to(q_new):traits(stride(1)))
q_new[i]=0.0;
}
}
}
}
/* end acc data */
Release(( & pHalfStep));
return ;
}

static inline void CalcSoundSpeedForElems(double vnewc[((45*45)*45)], double rho0, double * e_new, double * p_new, double * pbvc, double * bvc, double ss4o3, int length, int m_matElemlist[((45*45)*45)], double m_ss[((45*45)*45)])
{
int i;
#pragma acc  parallel loop gang worker independent present(bvc, e_new, m_matElemlist, m_ss, p_new, pbvc, vnewc) private(i) firstprivate(length, rho0)
#pragma aspen  control label(block_CalcSoundSpeedForElems5) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
int iz;
#pragma aspen  control execute label(block_CalcSoundSpeedForElems8) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
iz=m_matElemlist[i];
double ssTmp;
#pragma aspen  control execute label(block_CalcSoundSpeedForElems11) flops(6:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(bvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(p_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(pbvc):traits(stride(1)), (2*aspen_param_sizeof_double):from(vnewc):traits(stride(1)))
ssTmp=((pbvc[i]*e_new[i])+(((vnewc[i]*vnewc[i])*bvc[i])*p_new[i]))/rho0;
#pragma aspen  control label(block_CalcSoundSpeedForElems12) if(ssTmp<=1.111111E-36) flops(1:traits(dp))
if (ssTmp<=1.111111E-36)
{
#pragma aspen  control ignore
ssTmp=1.111111E-36;
}
#pragma aspen  control label(block_CalcSoundSpeedForElems14) stores((1*aspen_param_sizeof_double):to(m_ss))
m_ss[iz]=SQRT8(ssTmp);
}
return ;
}

static inline void EvalEOSForElems(double vnewc[((45*45)*45)], int length, int m_matElemlist[((45*45)*45)], double m_e[((45*45)*45)], double m_delv[((45*45)*45)], double m_p[((45*45)*45)], double m_q[((45*45)*45)], double m_qq[((45*45)*45)], double m_ql[((45*45)*45)], double p_ss[((45*45)*45)])
{
double e_cut;
#pragma aspen  control ignore
e_cut=m_e_cut;
double p_cut;
#pragma aspen  control ignore
p_cut=m_p_cut;
double ss4o3;
#pragma aspen  control ignore
ss4o3=m_ss4o3;
double q_cut;
#pragma aspen  control ignore
q_cut=m_q_cut;
double eosvmax;
#pragma aspen  control ignore
eosvmax=m_eosvmax;
double eosvmin;
#pragma aspen  control ignore
eosvmin=m_eosvmin;
double pmin;
#pragma aspen  control ignore
pmin=m_pmin;
double emin;
#pragma aspen  control ignore
emin=m_emin;
double rho0;
#pragma aspen  control ignore
rho0=m_refdens;
/*

   Real_te_old = Allocate(length) ;
   Real_t *delvc = Allocate(length) ;
   Real_t *p_old = Allocate(length) ;
   Real_t *q_old = Allocate(length) ;
   Real_t *compression = Allocate(length) ;
   Real_t *compHalfStep = Allocate(length) ;
   Real_t *qq = Allocate(length) ;
   Real_t *ql = Allocate(length) ;
   Real_t *work = Allocate(length) ;
   Real_t *p_new = Allocate(length) ;
   Real_t *e_new = Allocate(length) ;
   Real_t *q_new = Allocate(length) ;
   Real_t *bvc = Allocate(length) ;
   Real_t *pbvc = Allocate(length) ;

*/
int i;
/* compress data, minimal set */
#pragma acc  data present(bvc, compHalfStep, compression, delvc, e_new, e_old, m_matElemlist, p_new, p_old, pbvc, q_new, ql, qq, work)
{
#pragma acc  parallel loop gang worker independent present(delvc, e_old, m_delv, m_e, m_matElemlist, m_p, m_q, p_old, q_old) private(i) firstprivate(length)
#pragma aspen  control label(block_EvalEOSForElems33) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
int zidx;
#pragma aspen  control execute label(block_EvalEOSForElems36) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
zidx=m_matElemlist[i];
#pragma aspen  control execute label(block_EvalEOSForElems37) loads((1*aspen_param_sizeof_double):from(m_e)) stores((1*aspen_param_sizeof_double):to(e_old):traits(stride(1)))
e_old[i]=m_e[zidx];
#pragma aspen  control execute label(block_EvalEOSForElems38) loads((1*aspen_param_sizeof_double):from(m_delv)) stores((1*aspen_param_sizeof_double):to(delvc):traits(stride(1)))
delvc[i]=m_delv[zidx];
#pragma aspen  control execute label(block_EvalEOSForElems39) loads((1*aspen_param_sizeof_double):from(m_p)) stores((1*aspen_param_sizeof_double):to(p_old):traits(stride(1)))
p_old[i]=m_p[zidx];
#pragma aspen  control execute label(block_EvalEOSForElems40) loads((1*aspen_param_sizeof_double):from(m_q)) stores((1*aspen_param_sizeof_double):to(q_old):traits(stride(1)))
q_old[i]=m_q[zidx];
}
#pragma acc  parallel loop gang worker independent present(compHalfStep, compression, delvc, vnewc) private(i) firstprivate(length)
#pragma aspen  control label(block_EvalEOSForElems41) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
double vchalf;
#pragma aspen  control execute label(block_EvalEOSForElems44) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(vnewc):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(compression):traits(stride(1)))
compression[i]=((1.0/vnewc[i])-1.0);
#pragma aspen  control execute label(block_EvalEOSForElems45) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(delvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(vnewc):traits(stride(1)))
vchalf=(vnewc[i]-(delvc[i]*0.5));
#pragma aspen  control execute label(block_EvalEOSForElems46) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(compHalfStep):traits(stride(1)))
compHalfStep[i]=((1.0/vchalf)-1.0);
}
/* Check for v > eosvmax or v < eosvmin */
#pragma acc  parallel loop gang worker independent present(compHalfStep, compression, m_matElemlist, m_ql, m_qq, p_old, ql, qq, vnewc, work) private(i) firstprivate(eosvmax, eosvmin, length)
#pragma aspen  control label(block_EvalEOSForElems48) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
int zidx;
#pragma aspen  control execute label(block_EvalEOSForElems51) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
zidx=m_matElemlist[i];
#pragma aspen  control execute label(block_EvalEOSForElems52) loads((1*aspen_param_sizeof_double):from(m_qq)) stores((1*aspen_param_sizeof_double):to(qq):traits(stride(1)))
qq[i]=m_qq[zidx];
#pragma aspen  control execute label(block_EvalEOSForElems53) loads((1*aspen_param_sizeof_double):from(m_ql)) stores((1*aspen_param_sizeof_double):to(ql):traits(stride(1)))
ql[i]=m_ql[zidx];
#pragma aspen  control execute label(block_EvalEOSForElems54) stores((1*aspen_param_sizeof_double):to(work):traits(stride(1)))
work[i]=0.0;
#pragma aspen  control label(block_EvalEOSForElems1840) probability(1) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(vnewc):traits(stride(1)))
if ((eosvmin!=0.0)&&(vnewc[i]<=eosvmin))
{
#pragma aspen  control execute label(block_EvalEOSForElems56) loads((1*aspen_param_sizeof_double):from(compression):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(compHalfStep):traits(stride(1)))
compHalfStep[i]=compression[i];
}
#pragma aspen  control label(block_EvalEOSForElems1842) probability(1) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(vnewc):traits(stride(1)))
if ((eosvmax!=0.0)&&(vnewc[i]>=eosvmax))
{
#pragma aspen  control execute label(block_EvalEOSForElems58) stores((1*aspen_param_sizeof_double):to(p_old):traits(stride(1)))
p_old[i]=0.0;
#pragma aspen  control execute label(block_EvalEOSForElems59) stores((1*aspen_param_sizeof_double):to(compression):traits(stride(1)))
compression[i]=0.0;
#pragma aspen  control execute label(block_EvalEOSForElems60) stores((1*aspen_param_sizeof_double):to(compHalfStep):traits(stride(1)))
compHalfStep[i]=0.0;
}
}
}
CalcEnergyForElems(p_new, e_new, q_new, bvc, pbvc, p_old, e_old, q_old, compression, compHalfStep, vnewc, work, delvc, pmin, p_cut, e_cut, q_cut, emin, qq, ql, rho0, eosvmax, length);
#pragma acc  parallel loop gang worker independent present(e_new, m_e, m_matElemlist, m_p, m_q, p_new, q_new) private(i) firstprivate(length)
#pragma aspen  control label(block_EvalEOSForElems62) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
int zidx;
#pragma aspen  control execute label(block_EvalEOSForElems65) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
zidx=m_matElemlist[i];
#pragma aspen  control execute label(block_EvalEOSForElems66) loads((1*aspen_param_sizeof_double):from(p_new):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_p))
m_p[zidx]=p_new[i];
#pragma aspen  control execute label(block_EvalEOSForElems67) loads((1*aspen_param_sizeof_double):from(e_new):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_e))
m_e[zidx]=e_new[i];
#pragma aspen  control execute label(block_EvalEOSForElems68) loads((1*aspen_param_sizeof_double):from(q_new):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_q))
m_q[zidx]=q_new[i];
}
CalcSoundSpeedForElems(vnewc, rho0, e_new, p_new, pbvc, bvc, ss4o3, length, m_matElemlist, p_ss);
/*

   Release(&pbvc) ;
   Release(&bvc) ;
   Release(&q_new) ;
   Release(&e_new) ;
   Release(&p_new) ;
   Release(&work) ;
   Release(&ql) ;
   Release(&qq) ;
   Release(&compHalfStep) ;
   Release(&compression) ;
   Release(&q_old) ;
   Release(&p_old) ;
   Release(&delvc) ;
   Release(&e_old) ;

*/
return ;
}

static inline void ApplyMaterialPropertiesForElems(int m_matElemlist[((45*45)*45)], double m_vnew[((45*45)*45)], double m_v[((45*45)*45)], double p_e[((45*45)*45)], double p_delv[((45*45)*45)], double p_p[((45*45)*45)], double p_q[((45*45)*45)], double p_qq[((45*45)*45)], double p_ql[((45*45)*45)], double p_ss[((45*45)*45)])
{
int i;
#pragma aspen  declare param(length:m_numElem)
int length;
#pragma aspen  control ignore
length=m_numElem;
#pragma aspen  control label(block_ApplyMaterialPropertiesForElems1773) probability(1) flops(1:traits(integer))
if (length!=0)
{
/* Expose all of the variables needed for material evaluation */
double eosvmin;
#pragma aspen  control ignore
eosvmin=m_eosvmin;
double eosvmax;
#pragma aspen  control ignore
eosvmax=m_eosvmax;
/*

    Real_tvnewc = Allocate(length) ;

*/
double vc = 1.0;
#pragma acc  data present(m_matElemlist, m_v, vnewc[0:m_numElem])
{
#pragma acc  parallel loop gang worker independent present(m_matElemlist[0:m_numElem], m_vnew[0:m_numElem], vnewc[0:m_numElem]) private(i) firstprivate(eosvmax, eosvmin, length)
#pragma aspen  control label(block_ApplyMaterialPropertiesForElems17) loop(m_numElem) parallelism(m_numElem) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
int zn;
#pragma aspen  control execute label(block_ApplyMaterialPropertiesForElems20) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
zn=m_matElemlist[i];
#pragma aspen  control execute label(block_ApplyMaterialPropertiesForElems21) loads((1*aspen_param_sizeof_double):from(m_vnew)) stores((1*aspen_param_sizeof_double):to(vnewc):traits(stride(1)))
vnewc[i]=m_vnew[zn];
#pragma aspen  control label(block_ApplyMaterialPropertiesForElems1786) probability(1) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(vnewc):traits(stride(1)))
if ((eosvmin!=0.0)&&(vnewc[i]<eosvmin))
{
#pragma aspen  control execute label(block_ApplyMaterialPropertiesForElems23) stores((1*aspen_param_sizeof_double):to(vnewc):traits(stride(1)))
vnewc[i]=eosvmin;
}
#pragma aspen  control label(block_ApplyMaterialPropertiesForElems1788) probability(1) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(vnewc):traits(stride(1)))
if ((eosvmax!=0.0)&&(vnewc[i]>eosvmax))
{
#pragma aspen  control execute label(block_ApplyMaterialPropertiesForElems25) stores((1*aspen_param_sizeof_double):to(vnewc):traits(stride(1)))
vnewc[i]=eosvmax;
}
}
#pragma acc  parallel loop gang worker independent reduction(min: vc) present(m_matElemlist, m_v) private(i) firstprivate(eosvmax, eosvmin, length)
#pragma aspen  control label(block_ApplyMaterialPropertiesForElems26) loop(m_numElem) parallelism(m_numElem) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
int zn;
#pragma aspen  control execute label(block_ApplyMaterialPropertiesForElems29) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
zn=m_matElemlist[i];
#pragma aspen  control execute label(block_ApplyMaterialPropertiesForElems30) loads((1*aspen_param_sizeof_double):from(m_v))
vc=m_v[zn];
#pragma aspen  control execute label(block_ApplyMaterialPropertiesForElems1794) flops(2:traits(dp))
if (eosvmin!=0.0)
{
if (vc<eosvmin)
{
vc=eosvmin;
}
}
#pragma aspen  control execute label(block_ApplyMaterialPropertiesForElems1795) flops(2:traits(dp))
if (eosvmax!=0.0)
{
if (vc>eosvmax)
{
vc=eosvmax;
}
}
}
}
#pragma aspen  control ignore
if (vc<=0.0)
{
fprintf(stderr, "VolumeError in ApplyMaterialPropertiesForElems(); exit\n");
exit(VolumeError);
}
EvalEOSForElems(vnewc, length, m_matElemlist, p_e, p_delv, p_p, p_q, p_qq, p_ql, p_ss);
/*

    Release(&vnewc) ;

*/
}
return ;
}

static inline void UpdateVolumesForElems(double m_vnew[((45*45)*45)], double m_v[((45*45)*45)])
{
int i;
int numElem;
#pragma aspen  control ignore
numElem=m_numElem;
#pragma aspen  control label(block_UpdateVolumesForElems1997) probability(1) flops(1:traits(integer))
if (numElem!=0)
{
double v_cut;
#pragma aspen  control ignore
v_cut=m_v_cut;
#pragma acc  parallel loop gang worker independent present(m_v, m_vnew) private(i) firstprivate(numElem, v_cut)
#pragma aspen  control label(block_UpdateVolumesForElems9) loop(m_numElem) parallelism(m_numElem) flops(1:traits(integer))
for (i=0; i<numElem;  ++ i)
{
double tmpV;
#pragma aspen  control execute label(block_UpdateVolumesForElems12) loads((1*aspen_param_sizeof_double):from(m_vnew):traits(stride(1)))
tmpV=m_vnew[i];
#pragma aspen  control label(block_UpdateVolumesForElems2003) probability(1) flops(2:traits(dp))
if (FABS8((tmpV-1.0))<v_cut)
{
#pragma aspen  control ignore
tmpV=1.0;
}
#pragma aspen  control execute label(block_UpdateVolumesForElems15) stores((1*aspen_param_sizeof_double):to(m_v):traits(stride(1)))
m_v[i]=tmpV;
}
}
return ;
}

static inline void LagrangeElements()
{
const double deltatime = m_deltatime;
CalcLagrangeElements(deltatime, m_vnew, m_vdov, m_dxx, m_dyy, m_dzz);
/* Calculate Q.  (Monotonic q option requires communication) */
CalcQForElems();
ApplyMaterialPropertiesForElems(m_matElemlist, m_vnew, m_v, m_e, m_delv, m_p, m_q, m_qq, m_ql, m_ss);
UpdateVolumesForElems(m_vnew, m_v);
return ;
}

static inline void CalcCourantConstraintForElems(int m_matElemlist[((45*45)*45)], double m_ss[((45*45)*45)], double m_vdov[((45*45)*45)], double m_arealg[((45*45)*45)])
{
int i;
double dtcourant = 1.0E20;
int courant_elem;
#pragma aspen  control ignore
courant_elem= - 1;
double qqc;
#pragma aspen  control ignore
qqc=m_qqc;
int length;
#pragma aspen  control ignore
length=m_numElem;
double qqc2;
#pragma aspen  control execute label(block_CalcCourantConstraintForElems15) flops(2:traits(dp))
qqc2=(64.0*qqc)*qqc;
/* [FIXME] OpenMP pragma is temporarily disabled due to a bug. */
/* #pragma omp parallel for private(i) firstprivate(length,qqc2) shared(dtcourant,courant_elem, p_matElemlist, p_ss, p_vdov, p_arealg) */
#pragma aspen  control label(block_CalcCourantConstraintForElems18) loop(m_numElem) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
int indx;
#pragma aspen  control execute label(block_CalcCourantConstraintForElems21) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
indx=m_matElemlist[i];
double dtf;
#pragma aspen  control execute label(block_CalcCourantConstraintForElems24) flops(1:traits(dp)) loads((2*aspen_param_sizeof_double):from(m_ss))
dtf=m_ss[indx]*m_ss[indx];
#pragma aspen  control label(block_CalcCourantConstraintForElems2029) probability(1) flops(1:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_vdov))
if (m_vdov[indx]<0.0)
{
#pragma aspen  control execute label(block_CalcCourantConstraintForElems26) flops(5:traits(dp)) loads((2*aspen_param_sizeof_double):from(m_arealg), (2*aspen_param_sizeof_double):from(m_vdov))
dtf=(dtf+((((qqc2*m_arealg[indx])*m_arealg[indx])*m_vdov[indx])*m_vdov[indx]));
}
dtf=SQRT8(dtf);
#pragma aspen  control execute label(block_CalcCourantConstraintForElems28) flops(1:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_arealg))
dtf=(m_arealg[indx]/dtf);
/* determine minimum timestep with its corresponding elem */
#pragma aspen  control execute label(block_CalcCourantConstraintForElems2034) flops(2:traits(dp)) loads((1*aspen_param_double):from(m_vdov):traits(stride(1)))
if (m_vdov[indx]!=0.0)
{
if (dtf<dtcourant)
{
/* #pragma omp critical */
{
dtcourant=dtf;
courant_elem=indx;
}
}
}
}
/*
Don't try to register a time constraint if none of the elements
 were active
*/
#pragma aspen  control label(block_CalcCourantConstraintForElems32) if(courant_elem!=( - 1)) flops(1:traits(integer))
if (courant_elem!=( - 1))
{
#pragma aspen  control ignore
m_dtcourant=dtcourant;
}
return ;
}

static inline void CalcHydroConstraintForElems(int m_matElemlist[((45*45)*45)], double m_vdov[((45*45)*45)])
{
int i;
double dthydro = 1.0E20;
int hydro_elem;
#pragma aspen  control ignore
hydro_elem= - 1;
double dvovmax;
#pragma aspen  control ignore
dvovmax=m_dvovmax;
int length;
#pragma aspen  control ignore
length=m_numElem;
/* [FIXME] OpenMP pragma is temporarily disabled due to a bug. */
/* #pragma omp parallel for private(i) firstprivate(length) shared(dthydro,hydro_elem, p_matElemlist, p_vdov) */
#pragma aspen  control label(block_CalcHydroConstraintForElems15) loop(m_numElem) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
int indx;
#pragma aspen  control execute label(block_CalcHydroConstraintForElems18) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
indx=m_matElemlist[i];
#pragma aspen  control label(block_CalcHydroConstraintForElems2054) probability(1) flops(1:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_vdov))
if (m_vdov[indx]!=0.0)
{
double dtdvov;
#pragma aspen  control label(block_CalcHydroConstraintForElems22) flops(2:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_vdov))
dtdvov=dvovmax/(FABS8(m_vdov[indx])+1.0E-20);
#pragma aspen  control ignore
if (dthydro>dtdvov)
{
/* #pragma omp critical */
{
dthydro=dtdvov;
hydro_elem=indx;
}
}
}
}
#pragma aspen  control label(block_CalcHydroConstraintForElems24) if(hydro_elem!=( - 1)) flops(1:traits(integer))
if (hydro_elem!=( - 1))
{
#pragma aspen  control ignore
m_dthydro=dthydro;
}
return ;
}

static inline void CalcTimeConstraintsForElems()
{
#pragma acc  update host(m_arealg[0:m_numElem], m_ss[0:m_numElem], m_vdov[0:m_numElem])
#pragma aspen  control label(block_CalcTimeConstraintsForElems0) intracomm((aspen_param_sizeof_double*m_numElem):to(m_arealg):traits(copyout), (aspen_param_sizeof_double*m_numElem):to(m_ss):traits(copyout), (aspen_param_sizeof_double*m_numElem):to(m_vdov):traits(copyout))
/* evaluate time constraint */
CalcCourantConstraintForElems(m_matElemlist, m_ss, m_vdov, m_arealg);
/* check hydro constraint */
CalcHydroConstraintForElems(m_matElemlist, m_vdov);
return ;
}

static inline void LagrangeLeapFrog()
{
/* #pragma acc wait */
/*
calculate nodal forces, accelerations, velocities, positions, with
 applied boundary conditions and slide surface considerations
*/
LagrangeNodal();
/*
calculate element quantities (i.e. velocity gradient & q), and update
 material states
*/
LagrangeElements();
CalcTimeConstraintsForElems();
/* LagrangeRelease() ;  Creationdestruction of temps may be important to capture  */
return ;
}

int main(int argc, char * argv[])
{
int plane;
int row;
int col;
int i;
int lnode;
int j;
/* Real_t ds = Real_t(1.125)Real_t(edgeElems) ; may accumulate roundoff */
double tx;
double ty;
double tz;
int nidx;
int zidx;
int domElems;
FILE * fp;
double strt_time1;
double end_time1;
double strt_time2;
double end_time2;
int _ret_val_0 = 0;
strt_time1=my_timer();
edgeElems=45;
edgeNodes=(edgeElems+1);
/* get run options to measure various metrics */
/* ... */
/*  */
/*   Initialize Sedov Mesh  */
/*  */
/* construct a uniform box for this processor */
m_sizeX=edgeElems;
m_sizeY=edgeElems;
m_sizeZ=edgeElems;
m_numElem=((edgeElems*edgeElems)*edgeElems);
m_numElem8=(m_numElem*8);
m_numNode=((edgeNodes*edgeNodes)*edgeNodes);
domElems=m_numElem;
/* allocate field memory */
AllocateElemPersistent(m_numElem);
AllocateElemTemporary(m_numElem);
AllocateNodalPersistent(m_numNode);
AllocateNodesets((edgeNodes*edgeNodes));
AllocateTemporary(m_numElem8);
AllocateTemporary2(m_numElem);
/* initialize nodal coordinates */
nidx=0;
tz=0.0;
for (plane=0; plane<edgeNodes;  ++ plane)
{
ty=0.0;
for (row=0; row<edgeNodes;  ++ row)
{
tx=0.0;
for (col=0; col<edgeNodes;  ++ col)
{
m_x[nidx]=tx;
m_y[nidx]=ty;
m_z[nidx]=tz;
 ++ nidx;
/* tx += ds ; may accumulate roundoff... */
tx=((1.125*((double)(col+1)))/((double)edgeElems));
}
/* ty += ds ;  may accumulate roundoff... */
ty=((1.125*((double)(row+1)))/((double)edgeElems));
}
/* tz += ds ;  may accumulate roundoff... */
tz=((1.125*((double)(plane+1)))/((double)edgeElems));
}
/* embed hexehedral elements in nodal point lattice */
nidx=0;
zidx=0;
for (plane=0; plane<edgeElems;  ++ plane)
{
for (row=0; row<edgeElems;  ++ row)
{
for (col=0; col<edgeElems;  ++ col)
{
#pragma aspen  declare data(localNode)
int * localNode;
localNode= & m_nodelist[(8*zidx)];
localNode[0]=nidx;
localNode[1]=(nidx+1);
localNode[2]=((nidx+edgeNodes)+1);
localNode[3]=(nidx+edgeNodes);
localNode[4]=(nidx+(edgeNodes*edgeNodes));
localNode[5]=((nidx+(edgeNodes*edgeNodes))+1);
localNode[6]=(((nidx+(edgeNodes*edgeNodes))+edgeNodes)+1);
localNode[7]=((nidx+(edgeNodes*edgeNodes))+edgeNodes);
 ++ zidx;
 ++ nidx;
}
 ++ nidx;
}
nidx+=edgeNodes;
}
AllocateNodeElemIndexes();
/* Create a material IndexSet (entire domain same material for now) */
for (i=0; i<domElems;  ++ i)
{
m_matElemlist[i]=i;
}
/* initialize material parameters */
m_dtfixed=( - 1.0E-7);
m_deltatime=1.0E-7;
m_deltatimemultlb=1.1;
m_deltatimemultub=1.2;
m_stoptime=0.01;
m_dtcourant=1.0E20;
m_dthydro=1.0E20;
m_dtmax=0.01;
m_time=0.0;
m_cycle=0;
m_e_cut=1.0E-7;
m_p_cut=1.0E-7;
m_q_cut=1.0E-7;
m_u_cut=1.0E-7;
m_v_cut=1.0E-10;
m_hgcoef=3.0;
m_ss4o3=(4.0/3.0);
m_qstop=1.0E12;
m_monoq_max_slope=1.0;
m_monoq_limiter_mult=2.0;
m_qlc_monoq=0.5;
m_qqc_monoq=(2.0/3.0);
m_qqc=2.0;
m_pmin=0.0;
m_emin=( - 1.0E15);
m_dvovmax=0.1;
m_eosvmax=1.0E9;
m_eosvmin=1.0E-9;
m_refdens=1.0;
/* initialize field data */
for (i=0; i<domElems;  ++ i)
{
double x_local[8];
double y_local[8];
double z_local[8];
#pragma aspen  declare data(elemToNode:traits(Array(8, aspen_param_int)))
int * elemToNode;
elemToNode= & m_nodelist[(8*i)];
#pragma aspen  declare param(volume)
double volume;
for (lnode=0; lnode<8;  ++ lnode)
{
#pragma aspen  declare param(gnode)
int gnode;
gnode=elemToNode[lnode];
x_local[lnode]=m_x[gnode];
y_local[lnode]=m_y[gnode];
z_local[lnode]=m_z[gnode];
}
/* volume calculations */
volume=CalcElemVolume(x_local, y_local, z_local);
m_volo[i]=volume;
m_elemMass[i]=volume;
for (j=0; j<8;  ++ j)
{
#pragma aspen  declare param(idx)
int idx;
idx=elemToNode[j];
m_nodalMass[idx]+=(volume/8.0);
}
}
/* deposit energy */
m_e[0]=3.948746E7;
/* set up symmetry nodesets */
nidx=0;
for (i=0; i<edgeNodes;  ++ i)
{
#pragma aspen  declare param(planeInc)
int planeInc;
planeInc=(i*edgeNodes)*edgeNodes;
#pragma aspen  declare param(rowInc)
int rowInc;
rowInc=i*edgeNodes;
for (j=0; j<edgeNodes;  ++ j)
{
m_symmX[nidx]=(planeInc+(j*edgeNodes));
m_symmY[nidx]=(planeInc+j);
m_symmZ[nidx]=(rowInc+j);
 ++ nidx;
}
}
/* set up elemement connectivity information */
m_lxim[0]=0;
for (i=1; i<domElems;  ++ i)
{
m_lxim[i]=(i-1);
m_lxip[(i-1)]=i;
}
m_lxip[(domElems-1)]=(domElems-1);
for (i=0; i<edgeElems;  ++ i)
{
m_letam[i]=i;
m_letap[((domElems-edgeElems)+i)]=((domElems-edgeElems)+i);
}
for (i=edgeElems; i<domElems;  ++ i)
{
m_letam[i]=(i-edgeElems);
m_letap[(i-edgeElems)]=i;
}
for (i=0; i<(edgeElems*edgeElems);  ++ i)
{
m_lzetam[i]=i;
m_lzetap[((domElems-(edgeElems*edgeElems))+i)]=((domElems-(edgeElems*edgeElems))+i);
}
for (i=(edgeElems*edgeElems); i<domElems;  ++ i)
{
m_lzetam[i]=(i-(edgeElems*edgeElems));
m_lzetap[(i-(edgeElems*edgeElems))]=i;
}
/* set up boundary condition information */
for (i=0; i<domElems;  ++ i)
{
m_elemBC[i]=0;
/* clear BCs by default */
}
/* faces on "external" boundaries will be */
/* symmetry plane or free surface BCs */
for (i=0; i<edgeElems;  ++ i)
{
#pragma aspen  declare param(planeInc)
int planeInc;
planeInc=(i*edgeElems)*edgeElems;
#pragma aspen  declare param(rowInc)
int rowInc;
rowInc=i*edgeElems;
for (j=0; j<edgeElems;  ++ j)
{
m_elemBC[(planeInc+(j*edgeElems))]|=0x1;
m_elemBC[(((planeInc+(j*edgeElems))+edgeElems)-1)]|=0x8;
m_elemBC[(planeInc+j)]|=0x10;
m_elemBC[(((planeInc+j)+(edgeElems*edgeElems))-edgeElems)]|=0x80;
m_elemBC[(rowInc+j)]|=0x100;
m_elemBC[(((rowInc+j)+domElems)-(edgeElems*edgeElems))]|=0x800;
}
}
end_time1=my_timer();
strt_time2=my_timer();
i=0;
/* timestep to solution */
/* [DEBUG] while-loop count = 593 for edgeElem == 10 */
/*                         = 1041 for edgeElem == 20 */
/*                         = 1248 for edgeElem == 30 */
/*                         = 1420 for edgeElem == 40 */
/*                         = 1566 for edgeElem == 50 */
/* Use linear regression to estimate loop count using edgeElems. */
#pragma aspen  declare param(aspen_param_whilecnt:((23.25*edgeElems)+476.1))
acc_init(acc_device_default);
#pragma aspen  modelregion label(block_main134)
#pragma acc  data copy(m_e[0:m_numElem], m_p[0:m_numElem], m_x[0:m_numNode], m_xd[0:m_numNode], m_y[0:m_numNode], m_yd[0:m_numNode], m_z[0:m_numNode], m_zd[0:m_numNode]) copyin(m_elemBC[0:m_numElem], m_elemMass[0:m_numElem], m_letam[0:m_numElem], m_letap[0:m_numElem], m_lxim[0:m_numElem], m_lxip[0:m_numElem], m_lzetam[0:m_numElem], m_lzetap[0:m_numElem], m_matElemlist[0:m_numElem], m_nodalMass[0:m_numNode], m_nodeElemCornerList[0:m_nCorner], m_nodeElemCount[0:m_numNode], m_nodeElemStart[0:m_numNode], m_nodelist[0:m_numElem8], m_symmX[0:(edgeNodes*edgeNodes)], m_symmY[0:(edgeNodes*edgeNodes)], m_symmZ[0:(edgeNodes*edgeNodes)], m_v[0:m_numElem], m_volo[0:m_numElem], m_xdd[0:m_numNode], m_ydd[0:m_numNode], m_zdd[0:m_numNode]) create(bvc[0:m_numElem], compHalfStep[0:m_numElem], compression[0:m_numElem], delvc[0:m_numElem], determ[0:m_numElem], dvdx[0:m_numElem8], dvdy[0:m_numElem8], dvdz[0:m_numElem8], e_new[0:m_numElem], e_old[0:m_numElem], fx_elem[0:m_numElem8], fy_elem[0:m_numElem8], fz_elem[0:m_numElem8], m_arealg[0:m_numElem], m_delv[0:m_numElem], m_delv_eta[0:m_numElem], m_delv_xi[0:m_numElem], m_delv_zeta[0:m_numElem], m_delx_eta[0:m_numElem], m_delx_xi[0:m_numElem], m_delx_zeta[0:m_numElem], m_dxx[0:m_numElem], m_dyy[0:m_numElem], m_dzz[0:m_numElem], m_fx[0:m_numNode], m_fy[0:m_numNode], m_fz[0:m_numNode], m_q[0:m_numElem], m_ql[0:m_numElem], m_qq[0:m_numElem], m_ss[0:m_numElem], m_vdov[0:m_numElem], m_vnew[0:m_numElem], p_new[0:m_numElem], p_old[0:m_numElem], pbvc[0:m_numElem], q_new[0:m_numElem], q_old[0:m_numElem], ql[0:m_numElem], qq[0:m_numElem], sigxx[0:m_numElem], sigyy[0:m_numElem], sigzz[0:m_numElem], vnewc[0:m_numElem], work[0:m_numElem], x8n[0:m_numElem8], y8n[0:m_numElem8], z8n[0:m_numElem8])
#pragma aspen  control label(block_main134) intracomm((aspen_param_sizeof_double*m_numElem):to(m_e):traits(copy), (aspen_param_sizeof_double*m_numElem):to(m_elemMass):traits(copyin), (aspen_param_sizeof_double*m_numElem):to(m_p):traits(copy), (aspen_param_sizeof_double*m_numElem):to(m_v):traits(copyin), (aspen_param_sizeof_double*m_numElem):to(m_volo):traits(copyin), (aspen_param_sizeof_double*m_numNode):to(m_nodalMass):traits(copyin), (aspen_param_sizeof_double*m_numNode):to(m_x):traits(copy), (aspen_param_sizeof_double*m_numNode):to(m_xd):traits(copy), (aspen_param_sizeof_double*m_numNode):to(m_xdd):traits(copyin), (aspen_param_sizeof_double*m_numNode):to(m_y):traits(copy), (aspen_param_sizeof_double*m_numNode):to(m_yd):traits(copy), (aspen_param_sizeof_double*m_numNode):to(m_ydd):traits(copyin), (aspen_param_sizeof_double*m_numNode):to(m_z):traits(copy), (aspen_param_sizeof_double*m_numNode):to(m_zd):traits(copy), (aspen_param_sizeof_double*m_numNode):to(m_zdd):traits(copyin), (aspen_param_sizeof_int*(edgeNodes*edgeNodes)):to(m_symmX):traits(copyin), (aspen_param_sizeof_int*(edgeNodes*edgeNodes)):to(m_symmY):traits(copyin), (aspen_param_sizeof_int*(edgeNodes*edgeNodes)):to(m_symmZ):traits(copyin), (aspen_param_sizeof_int*m_nCorner):to(m_nodeElemCornerList):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_elemBC):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_letam):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_letap):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_lxim):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_lxip):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_lzetam):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_lzetap):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_matElemlist):traits(copyin), (aspen_param_sizeof_int*m_numElem8):to(m_nodelist):traits(copyin), (aspen_param_sizeof_int*m_numNode):to(m_nodeElemCount):traits(copyin), (aspen_param_sizeof_int*m_numNode):to(m_nodeElemStart):traits(copyin))
{
#pragma aspen  control label(block_main446) loop(aspen_param_whilecnt) flops(1:traits(dp))
while (m_time<m_stoptime)
{
TimeIncrement();
LagrangeLeapFrog();
#pragma aspen  control execute label(block_main138) flops(1:traits(integer))
i ++ ;
/* problem->commNodes->Transfer(CommNodes::syncposvel) ; */
}
#pragma aspen  control ignore
printf("iterations: %d\n", i);
}
acc_shutdown(acc_device_default);
end_time2=my_timer();
printf("Init time = %lf sec\n", (end_time1-strt_time1));
printf("Main Comp. time = %lf sec\n", (end_time2-strt_time2));
printf("Total elapsed time = %lf sec\n", ((end_time1-strt_time1)+(end_time2-strt_time2)));
fp=fopen("lulesh.out", "w");
for (i=0; i<m_numElem; i ++ )
{
fprintf(fp, "%.6f\n", m_x[i]);
}
for (i=0; i<m_numElem; i ++ )
{
fprintf(fp, "%.6f\n", m_y[i]);
}
for (i=0; i<m_numElem; i ++ )
{
fprintf(fp, "%.6f\n", m_z[i]);
}
fclose(fp);
_ret_val_0=0;
return _ret_val_0;
}


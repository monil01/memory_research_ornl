/*
Copyright (C) 1991-2018 Free Software Foundation, Inc.
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
/*
glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default. 
*/
/*
wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISOIEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters
*/
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
#include "../../../../OpenARC-devel/openarcrt/openacc.h"
#pragma aspen  declare param(aspen_param_sizeof_int:4)
#pragma aspen  declare param(aspen_param_sizeof_double:8)
#pragma openarc #define T_EDGEELEM 300 
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

enum lulesh_c_23917 { VolumeError = ( - 1), QStopError = ( - 2) };
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
double * m_fx;
/* forces */
double * m_fy;
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
double * fx_elem;
double * fy_elem;
double * fz_elem;
/* Temporary variables from CalcHourglassControlForElems() */
double * dvdx;
double * dvdy;
double * dvdz;
double * x8n;
double * y8n;
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
double * sigxx;
double * sigyy;
double * sigzz;
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
#pragma aspen  declare param(edgeElems:300)
int edgeElems;
#pragma aspen  declare param(edgeNodes:(edgeElems+1))
int edgeNodes;
/* #pragma aspen declare param(m_sizeX:edgeElems) */
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

void Release(double * * ptr)
{
#pragma aspen  control label(block_Release1176) probability(1) flops(1:traits(dp)) loads((1*aspen_param_sizeof_double))
if (( * ptr)!=0)
{
#pragma aspen  control execute label(block_Release1) stores((1*aspen_param_sizeof_double))
free(( * ptr));
#pragma aspen  control execute label(block_Release2) stores((1*aspen_param_sizeof_double))
( * ptr)=0;
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
targetdt=m_stoptime-m_time;
/* [DEBUG] Current ASPEN does not accept "<=" operator. */
#pragma aspen  control probability(1)
if ((m_dtfixed<=0.0)&&(m_cycle!=0))
{
double ratio;
double olddt;
olddt=m_deltatime;
/* This will require a reduction in parallel */
double newdt = 1.0E20;
#pragma aspen  control probability(1)
if (m_dtcourant<newdt)
{
newdt=(m_dtcourant/2.0);
}
#pragma aspen  control probability(1)
if (m_dthydro<newdt)
{
newdt=((m_dthydro*2.0)/3.0);
}
ratio=(newdt/olddt);
#pragma aspen  control execute flops(3:traits(dp))
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
if (newdt>m_dtmax)
{
newdt=m_dtmax;
}
m_deltatime=newdt;
}
/* TRY TO PREVENT VERY SMALL SCALING ON THE NEXT CYCLE */
#pragma aspen  control execute flops(6:traits(dp))
if ((targetdt>m_deltatime)&&(targetdt<((4.0*m_deltatime)/3.0)))
{
targetdt=((2.0*m_deltatime)/3.0);
}
#pragma aspen  control ignore
if (targetdt<m_deltatime)
{
m_deltatime=targetdt;
}
m_time+=m_deltatime;
 ++ m_cycle;
return ;
}

static inline void InitStressTermsForElems(int numElem, double sigxx[((300*300)*300)], double sigyy[((300*300)*300)], double sigzz[((300*300)*300)], double p_p[((300*300)*300)], double p_q[((300*300)*300)])
{
/*  */
/* pull in the stresses appropriate to the hydro integration */
/*  */
int i;
for (i=0; i<numElem;  ++ i)
{
sigxx[i]=(sigyy[i]=(sigzz[i]=(( - p_p[i])-p_q[i])));
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
bisectX0=0.5*(((x3+x2)-x1)-x0);
double bisectY0;
bisectY0=0.5*(((y3+y2)-y1)-y0);
double bisectZ0;
bisectZ0=0.5*(((z3+z2)-z1)-z0);
double bisectX1;
bisectX1=0.5*(((x2+x1)-x3)-x0);
double bisectY1;
bisectY1=0.5*(((y2+y1)-y3)-y0);
double bisectZ1;
bisectZ1=0.5*(((z2+z1)-z3)-z0);
double areaX;
areaX=0.25*((bisectY0*bisectZ1)-(bisectZ0*bisectY1));
double areaY;
areaY=0.25*((bisectZ0*bisectX1)-(bisectX0*bisectZ1));
double areaZ;
areaZ=0.25*((bisectX0*bisectY1)-(bisectY0*bisectX1));
( * normalX0)+=areaX;
( * normalX1)+=areaX;
( * normalX2)+=areaX;
( * normalX3)+=areaX;
( * normalY0)+=areaY;
( * normalY1)+=areaY;
( * normalY2)+=areaY;
( * normalY3)+=areaY;
( * normalZ0)+=areaZ;
( * normalZ1)+=areaZ;
( * normalZ2)+=areaZ;
( * normalZ3)+=areaZ;
return ;
}

static inline void CalcElemNodeNormals(double pfx[8], double pfy[8], double pfz[8], const double x[8], const double y[8], const double z[8])
{
int i;
for (i=0; i<8;  ++ i)
{
pfx[i]=0.0;
pfy[i]=0.0;
pfz[i]=0.0;
}
/* evaluate face one: nodes 0, 1, 2, 3 */
SumElemFaceNormal(( & pfx[0]), ( & pfy[0]), ( & pfz[0]), ( & pfx[1]), ( & pfy[1]), ( & pfz[1]), ( & pfx[2]), ( & pfy[2]), ( & pfz[2]), ( & pfx[3]), ( & pfy[3]), ( & pfz[3]), x[0], y[0], z[0], x[1], y[1], z[1], x[2], y[2], z[2], x[3], y[3], z[3]);
/* evaluate face two: nodes 0, 4, 5, 1 */
SumElemFaceNormal(( & pfx[0]), ( & pfy[0]), ( & pfz[0]), ( & pfx[4]), ( & pfy[4]), ( & pfz[4]), ( & pfx[5]), ( & pfy[5]), ( & pfz[5]), ( & pfx[1]), ( & pfy[1]), ( & pfz[1]), x[0], y[0], z[0], x[4], y[4], z[4], x[5], y[5], z[5], x[1], y[1], z[1]);
/* evaluate face three: nodes 1, 5, 6, 2 */
SumElemFaceNormal(( & pfx[1]), ( & pfy[1]), ( & pfz[1]), ( & pfx[5]), ( & pfy[5]), ( & pfz[5]), ( & pfx[6]), ( & pfy[6]), ( & pfz[6]), ( & pfx[2]), ( & pfy[2]), ( & pfz[2]), x[1], y[1], z[1], x[5], y[5], z[5], x[6], y[6], z[6], x[2], y[2], z[2]);
/* evaluate face four: nodes 2, 6, 7, 3 */
SumElemFaceNormal(( & pfx[2]), ( & pfy[2]), ( & pfz[2]), ( & pfx[6]), ( & pfy[6]), ( & pfz[6]), ( & pfx[7]), ( & pfy[7]), ( & pfz[7]), ( & pfx[3]), ( & pfy[3]), ( & pfz[3]), x[2], y[2], z[2], x[6], y[6], z[6], x[7], y[7], z[7], x[3], y[3], z[3]);
/* evaluate face five: nodes 3, 7, 4, 0 */
SumElemFaceNormal(( & pfx[3]), ( & pfy[3]), ( & pfz[3]), ( & pfx[7]), ( & pfy[7]), ( & pfz[7]), ( & pfx[4]), ( & pfy[4]), ( & pfz[4]), ( & pfx[0]), ( & pfy[0]), ( & pfz[0]), x[3], y[3], z[3], x[7], y[7], z[7], x[4], y[4], z[4], x[0], y[0], z[0]);
/* evaluate face six: nodes 4, 7, 6, 5 */
SumElemFaceNormal(( & pfx[4]), ( & pfy[4]), ( & pfz[4]), ( & pfx[7]), ( & pfy[7]), ( & pfz[7]), ( & pfx[6]), ( & pfy[6]), ( & pfz[6]), ( & pfx[5]), ( & pfy[5]), ( & pfz[5]), x[4], y[4], z[4], x[7], y[7], z[7], x[6], y[6], z[6], x[5], y[5], z[5]);
return ;
}

static inline void SumElemStressesToNodeForces(const double B[][8], const double stress_xx, const double stress_yy, const double stress_zz, double * const fx, double * const fy, double * const fz)
{
double pfx0;
pfx0=B[0][0];
double pfx1;
pfx1=B[0][1];
double pfx2;
pfx2=B[0][2];
double pfx3;
pfx3=B[0][3];
double pfx4;
pfx4=B[0][4];
double pfx5;
pfx5=B[0][5];
double pfx6;
pfx6=B[0][6];
double pfx7;
pfx7=B[0][7];
double pfy0;
pfy0=B[1][0];
double pfy1;
pfy1=B[1][1];
double pfy2;
pfy2=B[1][2];
double pfy3;
pfy3=B[1][3];
double pfy4;
pfy4=B[1][4];
double pfy5;
pfy5=B[1][5];
double pfy6;
pfy6=B[1][6];
double pfy7;
pfy7=B[1][7];
double pfz0;
pfz0=B[2][0];
double pfz1;
pfz1=B[2][1];
double pfz2;
pfz2=B[2][2];
double pfz3;
pfz3=B[2][3];
double pfz4;
pfz4=B[2][4];
double pfz5;
pfz5=B[2][5];
double pfz6;
pfz6=B[2][6];
double pfz7;
pfz7=B[2][7];
fx[0]=( - (stress_xx*pfx0));
fx[1]=( - (stress_xx*pfx1));
fx[2]=( - (stress_xx*pfx2));
fx[3]=( - (stress_xx*pfx3));
fx[4]=( - (stress_xx*pfx4));
fx[5]=( - (stress_xx*pfx5));
fx[6]=( - (stress_xx*pfx6));
fx[7]=( - (stress_xx*pfx7));
fy[0]=( - (stress_yy*pfy0));
fy[1]=( - (stress_yy*pfy1));
fy[2]=( - (stress_yy*pfy2));
fy[3]=( - (stress_yy*pfy3));
fy[4]=( - (stress_yy*pfy4));
fy[5]=( - (stress_yy*pfy5));
fy[6]=( - (stress_yy*pfy6));
fy[7]=( - (stress_yy*pfy7));
fz[0]=( - (stress_zz*pfz0));
fz[1]=( - (stress_zz*pfz1));
fz[2]=( - (stress_zz*pfz2));
fz[3]=( - (stress_zz*pfz3));
fz[4]=( - (stress_zz*pfz4));
fz[5]=( - (stress_zz*pfz5));
fz[6]=( - (stress_zz*pfz6));
fz[7]=( - (stress_zz*pfz7));
return ;
}

static inline void IntegrateStressForElems(int numElem, double sigxx[((300*300)*300)], double sigyy[((300*300)*300)], double sigzz[((300*300)*300)], double determ[((300*300)*300)], int p_nodelist[(((300*300)*300)*8)], double p_x[(((300+1)*(300+1))*(300+1))], double p_y[(((300+1)*(300+1))*(300+1))], double p_z[(((300+1)*(300+1))*(300+1))], int p_nodeElemCount[(((300+1)*(300+1))*(300+1))], int p_nodeElemStart[(((300+1)*(300+1))*(300+1))], int p_nodeElemCornerList[(((300*300)*300)*8)], double p_fx[(((300+1)*(300+1))*(300+1))], double p_fy[(((300+1)*(300+1))*(300+1))], double p_fz[(((300+1)*(300+1))*(300+1))])
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
for (k=0; k<numElem;  ++ k)
{
double B[3][8];
/* shape function derivatives */
double x_local[8];
double y_local[8];
double z_local[8];
#pragma aspen  declare data(elemNodes:traits(Array(8, aspen_param_int)))
const int * const elemNodes =  & p_nodelist[(8*k)];
/* get nodal coordinates from global arrays and copy into local arrays. */
/* Monil this is a stencil loop. Here is some reuse factors. Two 4 point stencil are read in this loop */
/* #pragma aspen control ignore */
/*  */
for (lnode=0; lnode<8;  ++ lnode)
{
/* #pragma aspen  control loads(((1aspen_param_sizeof_int)):from(elemNodes):traits(pattern(stencil4))) */
/* #pragma aspen control ignore */
/* #pragma aspen  control loads(((1aspen_param_sizeof_int)):from(elemNodes):traits(pattern(stencil4))) */
#pragma aspen  control ignore
{
int gnode;
gnode=elemNodes[lnode];
}
#pragma aspen  control loads((1*aspen_param_sizeof_int):from(elemNodes):traits(pattern(stencil4)))
#pragma aspen  control loads(0:from(p_x):traits(pattern(stencil4)))
x_local[lnode]=p_x[gnode];
#pragma aspen  control loads(0:from(p_y):traits(pattern(stencil4)))
y_local[lnode]=p_y[gnode];
#pragma aspen  control loads(0:from(p_z):traits(pattern(stencil4)))
z_local[lnode]=p_z[gnode];
}
/* Volume calculation involves extra work for numerical consistency.  */
/* Monil this function is ignored becuase this will only be 8X3 accesses and rest of it will be served from cache since same location is repeated numElem times. */
/* only the determ is written to memory */
/*  */
CalcElemShapeFunctionDerivatives(x_local, y_local, z_local, B, ( & determ[k]));
CalcElemNodeNormals(B[0], B[1], B[2], x_local, y_local, z_local);
/* SumElemStressesToNodeForces( B, sigxx[k], sigyy[k], sigzz[k], */
/*                             &fx_elem[k8], &fy_elem[k*8], &fz_elem[k*8] ) ; */
SumElemStressesToNodeForces(B, sigxx[k], sigyy[k], sigzz[k], fx_local, fy_local, fz_local);
/* #if 0 */
/* copy nodal force contributions to global force arrray. */
for (lnode=0; lnode<8;  ++ lnode)
{
#pragma aspen  control ignore
{
int gnode;
gnode=elemNodes[lnode];
}
#pragma aspen  control loads((1*aspen_param_sizeof_int):from(elemNodes):traits(pattern(stencil4)))
#pragma aspen  control stores(0:from(p_fx):traits(pattern(stencil4)))
p_fx(gnode)+=fx_local[lnode];
#pragma aspen  control stores(0:from(p_fy):traits(pattern(stencil4)))
p_fy(gnode)+=fy_local[lnode];
#pragma aspen  control stores(0:from(p_fz):traits(pattern(stencil4)))
p_fz(gnode)+=fz_local[lnode];
}
/* #endif */
}
/*

  {
     Index_t numNode = m_numNode;
#ifdef _OPENACC
#pragma acc kernels loop independent present(fx_elem, fy_elem, fz_elem, p_fx, p_fy, p_fz, p_nodeElemCount, p_nodeElemCornerList, p_nodeElemStart)
rt)
#else
#pragma omp parallel for private(gnode) firstprivate(numNode)
#endif
     for( gnode=0 ; gnode<numNode ; ++gnode )
     {
        Index_t count = p_nodeElemCount[gnode];
        Index_t start = p_nodeElemStart[gnode];
        Real_t fx = 0.0 ;
        Real_t fy = 0.0 ;
        Real_t fz = 0.0 ;
#pragma aspen declare param(aspen_param_elemCount:1)
#pragma aspen control loop(aspen_param_elemCount)
        for (i=0 ; i < count ; ++i) {
           Index_t elem = p_nodeElemCornerList[start+i];
           fx += fx_elem[elem] ;
           fy += fy_elem[elem] ;
           fz += fz_elem[elem] ;
        }
        p_fx[gnode] = fx ;
        p_fy[gnode] = fy ;
        p_fz[gnode] = fz ;
     }
  }

*/
/*

  Release(&fz_elem) ;
  Release(&fy_elem) ;
  Release(&fx_elem) ;

*/
return ;
}

static inline void CollectDomainNodesToElemNodes(const int * elemToNode, double elemX[8], double elemY[8], double elemZ[8])
{
int nd0i;
nd0i=elemToNode[0];
int nd1i;
nd1i=elemToNode[1];
int nd2i;
nd2i=elemToNode[2];
int nd3i;
nd3i=elemToNode[3];
int nd4i;
nd4i=elemToNode[4];
int nd5i;
nd5i=elemToNode[5];
int nd6i;
nd6i=elemToNode[6];
int nd7i;
nd7i=elemToNode[7];
elemX[0]=m_x[nd0i];
elemX[1]=m_x[nd1i];
elemX[2]=m_x[nd2i];
elemX[3]=m_x[nd3i];
elemX[4]=m_x[nd4i];
elemX[5]=m_x[nd5i];
elemX[6]=m_x[nd6i];
elemX[7]=m_x[nd7i];
elemY[0]=m_y[nd0i];
elemY[1]=m_y[nd1i];
elemY[2]=m_y[nd2i];
elemY[3]=m_y[nd3i];
elemY[4]=m_y[nd4i];
elemY[5]=m_y[nd5i];
elemY[6]=m_y[nd6i];
elemY[7]=m_y[nd7i];
elemZ[0]=m_z[nd0i];
elemZ[1]=m_z[nd1i];
elemZ[2]=m_z[nd2i];
elemZ[3]=m_z[nd3i];
elemZ[4]=m_z[nd4i];
elemZ[5]=m_z[nd5i];
elemZ[6]=m_z[nd6i];
elemZ[7]=m_z[nd7i];
return ;
}

static inline void VoluDer(const double x0, const double x1, const double x2, const double x3, const double x4, const double x5, const double y0, const double y1, const double y2, const double y3, const double y4, const double y5, const double z0, const double z1, const double z2, const double z3, const double z4, const double z5, double * dvdx, double * dvdy, double * dvdz)
{
const double twelfth = 1.0/12.0;
( * dvdx)=(((((((y1+y2)*(z0+z1))-((y0+y1)*(z1+z2)))+((y0+y4)*(z3+z4)))-((y3+y4)*(z0+z4)))-((y2+y5)*(z3+z5)))+((y3+y5)*(z2+z5)));
( * dvdy)=((((((( - (x1+x2))*(z0+z1))+((x0+x1)*(z1+z2)))-((x0+x4)*(z3+z4)))+((x3+x4)*(z0+z4)))+((x2+x5)*(z3+z5)))-((x3+x5)*(z2+z5)));
( * dvdz)=((((((( - (y1+y2))*(x0+x1))+((y0+y1)*(x1+x2)))-((y0+y4)*(x3+x4)))+((y3+y4)*(x0+x4)))+((y2+y5)*(x3+x5)))-((y3+y5)*(x2+x5)));
( * dvdx)*=twelfth;
( * dvdy)*=twelfth;
( * dvdz)*=twelfth;
return ;
}

static inline void CalcElemVolumeDerivative(double dvdx[8], double dvdy[8], double dvdz[8], const double x[8], const double y[8], const double z[8])
{
VoluDer(x[1], x[2], x[3], x[4], x[5], x[7], y[1], y[2], y[3], y[4], y[5], y[7], z[1], z[2], z[3], z[4], z[5], z[7], ( & dvdx[0]), ( & dvdy[0]), ( & dvdz[0]));
VoluDer(x[0], x[1], x[2], x[7], x[4], x[6], y[0], y[1], y[2], y[7], y[4], y[6], z[0], z[1], z[2], z[7], z[4], z[6], ( & dvdx[3]), ( & dvdy[3]), ( & dvdz[3]));
VoluDer(x[3], x[0], x[1], x[6], x[7], x[5], y[3], y[0], y[1], y[6], y[7], y[5], z[3], z[0], z[1], z[6], z[7], z[5], ( & dvdx[2]), ( & dvdy[2]), ( & dvdz[2]));
VoluDer(x[2], x[3], x[0], x[5], x[6], x[4], y[2], y[3], y[0], y[5], y[6], y[4], z[2], z[3], z[0], z[5], z[6], z[4], ( & dvdx[1]), ( & dvdy[1]), ( & dvdz[1]));
VoluDer(x[7], x[6], x[5], x[0], x[3], x[1], y[7], y[6], y[5], y[0], y[3], y[1], z[7], z[6], z[5], z[0], z[3], z[1], ( & dvdx[4]), ( & dvdy[4]), ( & dvdz[4]));
VoluDer(x[4], x[7], x[6], x[1], x[0], x[2], y[4], y[7], y[6], y[1], y[0], y[2], z[4], z[7], z[6], z[1], z[0], z[2], ( & dvdx[5]), ( & dvdy[5]), ( & dvdz[5]));
VoluDer(x[5], x[4], x[7], x[2], x[1], x[3], y[5], y[4], y[7], y[2], y[1], y[3], z[5], z[4], z[7], z[2], z[1], z[3], ( & dvdx[6]), ( & dvdy[6]), ( & dvdz[6]));
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
h00=(((((((hourgam0[i00]*xd[0])+(hourgam1[i00]*xd[1]))+(hourgam2[i00]*xd[2]))+(hourgam3[i00]*xd[3]))+(hourgam4[i00]*xd[4]))+(hourgam5[i00]*xd[5]))+(hourgam6[i00]*xd[6]))+(hourgam7[i00]*xd[7]);
double h01;
h01=(((((((hourgam0[i01]*xd[0])+(hourgam1[i01]*xd[1]))+(hourgam2[i01]*xd[2]))+(hourgam3[i01]*xd[3]))+(hourgam4[i01]*xd[4]))+(hourgam5[i01]*xd[5]))+(hourgam6[i01]*xd[6]))+(hourgam7[i01]*xd[7]);
double h02;
h02=(((((((hourgam0[i02]*xd[0])+(hourgam1[i02]*xd[1]))+(hourgam2[i02]*xd[2]))+(hourgam3[i02]*xd[3]))+(hourgam4[i02]*xd[4]))+(hourgam5[i02]*xd[5]))+(hourgam6[i02]*xd[6]))+(hourgam7[i02]*xd[7]);
double h03;
h03=(((((((hourgam0[i03]*xd[0])+(hourgam1[i03]*xd[1]))+(hourgam2[i03]*xd[2]))+(hourgam3[i03]*xd[3]))+(hourgam4[i03]*xd[4]))+(hourgam5[i03]*xd[5]))+(hourgam6[i03]*xd[6]))+(hourgam7[i03]*xd[7]);
hgfx[0]=(coefficient*((((hourgam0[i00]*h00)+(hourgam0[i01]*h01))+(hourgam0[i02]*h02))+(hourgam0[i03]*h03)));
hgfx[1]=(coefficient*((((hourgam1[i00]*h00)+(hourgam1[i01]*h01))+(hourgam1[i02]*h02))+(hourgam1[i03]*h03)));
hgfx[2]=(coefficient*((((hourgam2[i00]*h00)+(hourgam2[i01]*h01))+(hourgam2[i02]*h02))+(hourgam2[i03]*h03)));
hgfx[3]=(coefficient*((((hourgam3[i00]*h00)+(hourgam3[i01]*h01))+(hourgam3[i02]*h02))+(hourgam3[i03]*h03)));
hgfx[4]=(coefficient*((((hourgam4[i00]*h00)+(hourgam4[i01]*h01))+(hourgam4[i02]*h02))+(hourgam4[i03]*h03)));
hgfx[5]=(coefficient*((((hourgam5[i00]*h00)+(hourgam5[i01]*h01))+(hourgam5[i02]*h02))+(hourgam5[i03]*h03)));
hgfx[6]=(coefficient*((((hourgam6[i00]*h00)+(hourgam6[i01]*h01))+(hourgam6[i02]*h02))+(hourgam6[i03]*h03)));
hgfx[7]=(coefficient*((((hourgam7[i00]*h00)+(hourgam7[i01]*h01))+(hourgam7[i02]*h02))+(hourgam7[i03]*h03)));
h00=((((((((hourgam0[i00]*yd[0])+(hourgam1[i00]*yd[1]))+(hourgam2[i00]*yd[2]))+(hourgam3[i00]*yd[3]))+(hourgam4[i00]*yd[4]))+(hourgam5[i00]*yd[5]))+(hourgam6[i00]*yd[6]))+(hourgam7[i00]*yd[7]));
h01=((((((((hourgam0[i01]*yd[0])+(hourgam1[i01]*yd[1]))+(hourgam2[i01]*yd[2]))+(hourgam3[i01]*yd[3]))+(hourgam4[i01]*yd[4]))+(hourgam5[i01]*yd[5]))+(hourgam6[i01]*yd[6]))+(hourgam7[i01]*yd[7]));
h02=((((((((hourgam0[i02]*yd[0])+(hourgam1[i02]*yd[1]))+(hourgam2[i02]*yd[2]))+(hourgam3[i02]*yd[3]))+(hourgam4[i02]*yd[4]))+(hourgam5[i02]*yd[5]))+(hourgam6[i02]*yd[6]))+(hourgam7[i02]*yd[7]));
h03=((((((((hourgam0[i03]*yd[0])+(hourgam1[i03]*yd[1]))+(hourgam2[i03]*yd[2]))+(hourgam3[i03]*yd[3]))+(hourgam4[i03]*yd[4]))+(hourgam5[i03]*yd[5]))+(hourgam6[i03]*yd[6]))+(hourgam7[i03]*yd[7]));
hgfy[0]=(coefficient*((((hourgam0[i00]*h00)+(hourgam0[i01]*h01))+(hourgam0[i02]*h02))+(hourgam0[i03]*h03)));
hgfy[1]=(coefficient*((((hourgam1[i00]*h00)+(hourgam1[i01]*h01))+(hourgam1[i02]*h02))+(hourgam1[i03]*h03)));
hgfy[2]=(coefficient*((((hourgam2[i00]*h00)+(hourgam2[i01]*h01))+(hourgam2[i02]*h02))+(hourgam2[i03]*h03)));
hgfy[3]=(coefficient*((((hourgam3[i00]*h00)+(hourgam3[i01]*h01))+(hourgam3[i02]*h02))+(hourgam3[i03]*h03)));
hgfy[4]=(coefficient*((((hourgam4[i00]*h00)+(hourgam4[i01]*h01))+(hourgam4[i02]*h02))+(hourgam4[i03]*h03)));
hgfy[5]=(coefficient*((((hourgam5[i00]*h00)+(hourgam5[i01]*h01))+(hourgam5[i02]*h02))+(hourgam5[i03]*h03)));
hgfy[6]=(coefficient*((((hourgam6[i00]*h00)+(hourgam6[i01]*h01))+(hourgam6[i02]*h02))+(hourgam6[i03]*h03)));
hgfy[7]=(coefficient*((((hourgam7[i00]*h00)+(hourgam7[i01]*h01))+(hourgam7[i02]*h02))+(hourgam7[i03]*h03)));
h00=((((((((hourgam0[i00]*zd[0])+(hourgam1[i00]*zd[1]))+(hourgam2[i00]*zd[2]))+(hourgam3[i00]*zd[3]))+(hourgam4[i00]*zd[4]))+(hourgam5[i00]*zd[5]))+(hourgam6[i00]*zd[6]))+(hourgam7[i00]*zd[7]));
h01=((((((((hourgam0[i01]*zd[0])+(hourgam1[i01]*zd[1]))+(hourgam2[i01]*zd[2]))+(hourgam3[i01]*zd[3]))+(hourgam4[i01]*zd[4]))+(hourgam5[i01]*zd[5]))+(hourgam6[i01]*zd[6]))+(hourgam7[i01]*zd[7]));
h02=((((((((hourgam0[i02]*zd[0])+(hourgam1[i02]*zd[1]))+(hourgam2[i02]*zd[2]))+(hourgam3[i02]*zd[3]))+(hourgam4[i02]*zd[4]))+(hourgam5[i02]*zd[5]))+(hourgam6[i02]*zd[6]))+(hourgam7[i02]*zd[7]));
h03=((((((((hourgam0[i03]*zd[0])+(hourgam1[i03]*zd[1]))+(hourgam2[i03]*zd[2]))+(hourgam3[i03]*zd[3]))+(hourgam4[i03]*zd[4]))+(hourgam5[i03]*zd[5]))+(hourgam6[i03]*zd[6]))+(hourgam7[i03]*zd[7]));
hgfz[0]=(coefficient*((((hourgam0[i00]*h00)+(hourgam0[i01]*h01))+(hourgam0[i02]*h02))+(hourgam0[i03]*h03)));
hgfz[1]=(coefficient*((((hourgam1[i00]*h00)+(hourgam1[i01]*h01))+(hourgam1[i02]*h02))+(hourgam1[i03]*h03)));
hgfz[2]=(coefficient*((((hourgam2[i00]*h00)+(hourgam2[i01]*h01))+(hourgam2[i02]*h02))+(hourgam2[i03]*h03)));
hgfz[3]=(coefficient*((((hourgam3[i00]*h00)+(hourgam3[i01]*h01))+(hourgam3[i02]*h02))+(hourgam3[i03]*h03)));
hgfz[4]=(coefficient*((((hourgam4[i00]*h00)+(hourgam4[i01]*h01))+(hourgam4[i02]*h02))+(hourgam4[i03]*h03)));
hgfz[5]=(coefficient*((((hourgam5[i00]*h00)+(hourgam5[i01]*h01))+(hourgam5[i02]*h02))+(hourgam5[i03]*h03)));
hgfz[6]=(coefficient*((((hourgam6[i00]*h00)+(hourgam6[i01]*h01))+(hourgam6[i02]*h02))+(hourgam6[i03]*h03)));
hgfz[7]=(coefficient*((((hourgam7[i00]*h00)+(hourgam7[i01]*h01))+(hourgam7[i02]*h02))+(hourgam7[i03]*h03)));
return ;
}

static inline void CalcFBHourglassForceForElems(double determ[((300*300)*300)], double x8n[(((300*300)*300)*8)], double y8n[(((300*300)*300)*8)], double z8n[(((300*300)*300)*8)], double dvdx[(((300*300)*300)*8)], double dvdy[(((300*300)*300)*8)], double dvdz[(((300*300)*300)*8)], double hourg, double p_ss[((300*300)*300)], int p_nodelist[(((300*300)*300)*8)], double p_elemMass[((300*300)*300)], double p_xd[(((300+1)*(300+1))*(300+1))], double p_yd[(((300+1)*(300+1))*(300+1))], double p_zd[(((300+1)*(300+1))*(300+1))], int p_nodeElemCount[(((300+1)*(300+1))*(300+1))], int p_nodeElemStart[(((300+1)*(300+1))*(300+1))], int p_nodeElemCornerList[(((300*300)*300)*8)], double p_fx[(((300+1)*(300+1))*(300+1))], double p_fy[(((300+1)*(300+1))*(300+1))], double p_fz[(((300+1)*(300+1))*(300+1))])
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
numElem=m_numElem;
#pragma aspen  declare param(numElem8:(m_numElem*8))
int numElem8;
numElem8=numElem*8;
/*

   Real_tfx_elem = Allocate(numElem8) ;
   Real_t *fy_elem = Allocate(numElem8) ;
   Real_t *fz_elem = Allocate(numElem8) ;

*/
double gamma[4][8];
gamma[0][0]=1.0;
gamma[0][1]=1.0;
gamma[0][2]=( - 1.0);
gamma[0][3]=( - 1.0);
gamma[0][4]=( - 1.0);
gamma[0][5]=( - 1.0);
gamma[0][6]=1.0;
gamma[0][7]=1.0;
gamma[1][0]=1.0;
gamma[1][1]=( - 1.0);
gamma[1][2]=( - 1.0);
gamma[1][3]=1.0;
gamma[1][4]=( - 1.0);
gamma[1][5]=1.0;
gamma[1][6]=1.0;
gamma[1][7]=( - 1.0);
gamma[2][0]=1.0;
gamma[2][1]=( - 1.0);
gamma[2][2]=1.0;
gamma[2][3]=( - 1.0);
gamma[2][4]=1.0;
gamma[2][5]=( - 1.0);
gamma[2][6]=1.0;
gamma[2][7]=( - 1.0);
gamma[3][0]=( - 1.0);
gamma[3][1]=1.0;
gamma[3][2]=( - 1.0);
gamma[3][3]=1.0;
gamma[3][4]=1.0;
gamma[3][5]=( - 1.0);
gamma[3][6]=1.0;
gamma[3][7]=( - 1.0);
/*  */
/*    compute the hourglass modes */
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
#pragma aspen  declare data(elemToNode:traits(Array(8, aspen_param_int)))
const int * elemToNode;
elemToNode= & p_nodelist[(8*i2)];
int i3;
i3=8*i2;
double volinv;
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
for (i1=0; i1<4;  ++ i1)
{
double hourmodx;
hourmodx=(((((((x8n[i3]*gamma[i1][0])+(x8n[(i3+1)]*gamma[i1][1]))+(x8n[(i3+2)]*gamma[i1][2]))+(x8n[(i3+3)]*gamma[i1][3]))+(x8n[(i3+4)]*gamma[i1][4]))+(x8n[(i3+5)]*gamma[i1][5]))+(x8n[(i3+6)]*gamma[i1][6]))+(x8n[(i3+7)]*gamma[i1][7]);
double hourmody;
hourmody=(((((((y8n[i3]*gamma[i1][0])+(y8n[(i3+1)]*gamma[i1][1]))+(y8n[(i3+2)]*gamma[i1][2]))+(y8n[(i3+3)]*gamma[i1][3]))+(y8n[(i3+4)]*gamma[i1][4]))+(y8n[(i3+5)]*gamma[i1][5]))+(y8n[(i3+6)]*gamma[i1][6]))+(y8n[(i3+7)]*gamma[i1][7]);
double hourmodz;
hourmodz=(((((((z8n[i3]*gamma[i1][0])+(z8n[(i3+1)]*gamma[i1][1]))+(z8n[(i3+2)]*gamma[i1][2]))+(z8n[(i3+3)]*gamma[i1][3]))+(z8n[(i3+4)]*gamma[i1][4]))+(z8n[(i3+5)]*gamma[i1][5]))+(z8n[(i3+6)]*gamma[i1][6]))+(z8n[(i3+7)]*gamma[i1][7]);
hourgam0[i1]=(gamma[i1][0]-(volinv*(((dvdx[i3]*hourmodx)+(dvdy[i3]*hourmody))+(dvdz[i3]*hourmodz))));
hourgam1[i1]=(gamma[i1][1]-(volinv*(((dvdx[(i3+1)]*hourmodx)+(dvdy[(i3+1)]*hourmody))+(dvdz[(i3+1)]*hourmodz))));
hourgam2[i1]=(gamma[i1][2]-(volinv*(((dvdx[(i3+2)]*hourmodx)+(dvdy[(i3+2)]*hourmody))+(dvdz[(i3+2)]*hourmodz))));
hourgam3[i1]=(gamma[i1][3]-(volinv*(((dvdx[(i3+3)]*hourmodx)+(dvdy[(i3+3)]*hourmody))+(dvdz[(i3+3)]*hourmodz))));
hourgam4[i1]=(gamma[i1][4]-(volinv*(((dvdx[(i3+4)]*hourmodx)+(dvdy[(i3+4)]*hourmody))+(dvdz[(i3+4)]*hourmodz))));
hourgam5[i1]=(gamma[i1][5]-(volinv*(((dvdx[(i3+5)]*hourmodx)+(dvdy[(i3+5)]*hourmody))+(dvdz[(i3+5)]*hourmodz))));
hourgam6[i1]=(gamma[i1][6]-(volinv*(((dvdx[(i3+6)]*hourmodx)+(dvdy[(i3+6)]*hourmody))+(dvdz[(i3+6)]*hourmodz))));
hourgam7[i1]=(gamma[i1][7]-(volinv*(((dvdx[(i3+7)]*hourmodx)+(dvdy[(i3+7)]*hourmody))+(dvdz[(i3+7)]*hourmodz))));
}
/* compute forces */
/* store forces into h arrays (force arrays) */
ss1=p_ss[i2];
mass1=p_elemMass[i2];
volume13=CBRT8(determ[i2]);
n0si2=elemToNode[0];
n1si2=elemToNode[1];
n2si2=elemToNode[2];
n3si2=elemToNode[3];
n4si2=elemToNode[4];
n5si2=elemToNode[5];
n6si2=elemToNode[6];
n7si2=elemToNode[7];
xd1[0]=p_xd[n0si2];
xd1[1]=p_xd[n1si2];
xd1[2]=p_xd[n2si2];
xd1[3]=p_xd[n3si2];
xd1[4]=p_xd[n4si2];
xd1[5]=p_xd[n5si2];
xd1[6]=p_xd[n6si2];
xd1[7]=p_xd[n7si2];
yd1[0]=p_yd[n0si2];
yd1[1]=p_yd[n1si2];
yd1[2]=p_yd[n2si2];
yd1[3]=p_yd[n3si2];
yd1[4]=p_yd[n4si2];
yd1[5]=p_yd[n5si2];
yd1[6]=p_yd[n6si2];
yd1[7]=p_yd[n7si2];
zd1[0]=p_zd[n0si2];
zd1[1]=p_zd[n1si2];
zd1[2]=p_zd[n2si2];
zd1[3]=p_zd[n3si2];
zd1[4]=p_zd[n4si2];
zd1[5]=p_zd[n5si2];
zd1[6]=p_zd[n6si2];
zd1[7]=p_zd[n7si2];
coefficient=((((( - hourg)*0.01)*ss1)*mass1)/volume13);
CalcElemFBHourglassForce(xd1, yd1, zd1, hourgam0, hourgam1, hourgam2, hourgam3, hourgam4, hourgam5, hourgam6, hourgam7, coefficient, hgfx, hgfy, hgfz);
#pragma aspen  declare data(fx_local:traits(Array(8, aspen_param_double)))
fx_local=( & fx_elem[i3]);
fx_local[0]=hgfx[0];
fx_local[1]=hgfx[1];
fx_local[2]=hgfx[2];
fx_local[3]=hgfx[3];
fx_local[4]=hgfx[4];
fx_local[5]=hgfx[5];
fx_local[6]=hgfx[6];
fx_local[7]=hgfx[7];
#pragma aspen  declare data(fy_local:traits(Array(8, aspen_param_double)))
fy_local=( & fy_elem[i3]);
fy_local[0]=hgfy[0];
fy_local[1]=hgfy[1];
fy_local[2]=hgfy[2];
fy_local[3]=hgfy[3];
fy_local[4]=hgfy[4];
fy_local[5]=hgfy[5];
fy_local[6]=hgfy[6];
fy_local[7]=hgfy[7];
#pragma aspen  declare data(fz_local:traits(Array(8, aspen_param_double)))
fz_local=( & fz_elem[i3]);
fz_local[0]=hgfz[0];
fz_local[1]=hgfz[1];
fz_local[2]=hgfz[2];
fz_local[3]=hgfz[3];
fz_local[4]=hgfz[4];
fz_local[5]=hgfz[5];
fz_local[6]=hgfz[6];
fz_local[7]=hgfz[7];
}
{
int numNode;
numNode=m_numNode;
for (gnode=0; gnode<numNode;  ++ gnode)
{
int count;
count=p_nodeElemCount[gnode];
int start;
start=p_nodeElemStart[gnode];
double fx = 0.0;
double fy = 0.0;
double fz = 0.0;
#pragma aspen  declare param(aspen_param_elemCount:1)
#pragma aspen  control loop(aspen_param_elemCount)
for (i=0; i<count;  ++ i)
{
int elem;
elem=p_nodeElemCornerList[(start+i)];
fx+=fx_elem[elem];
fy+=fy_elem[elem];
fz+=fz_elem[elem];
}
p_fx[gnode]+=fx;
p_fy[gnode]+=fy;
p_fz[gnode]+=fz;
}
}
/*

  Release(&fz_elem) ;
  Release(&fy_elem) ;
  Release(&fx_elem) ;

*/
return ;
}

static inline void CalcHourglassControlForElems(double determ[((300*300)*300)], double hgcoef, int p_nodelist[(((300*300)*300)*8)], double p_volo[((300*300)*300)], double p_v[((300*300)*300)])
{
int i;
int ii;
int numElem;
numElem=m_numElem;
#pragma aspen  declare param(numElem8:(m_numElem*8))
int numElem8;
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
for (i=0; i<numElem;  ++ i)
{
double x1[8];
double y1[8];
double z1[8];
double pfx[8];
double pfy[8];
double pfz[8];
#pragma aspen  declare data(elemToNode:traits(Array(8, aspen_param_int)))
int * elemToNode;
elemToNode= & p_nodelist[(8*i)];
CollectDomainNodesToElemNodes(elemToNode, x1, y1, z1);
CalcElemVolumeDerivative(pfx, pfy, pfz, x1, y1, z1);
/* load into temporary storage for FB Hour Glass control */
for (ii=0; ii<8;  ++ ii)
{
int jj;
jj=(8*i)+ii;
dvdx[jj]=pfx[ii];
dvdy[jj]=pfy[ii];
dvdz[jj]=pfz[ii];
x8n[jj]=x1[ii];
y8n[jj]=y1[ii];
z8n[jj]=z1[ii];
}
determ[i]=(p_volo[i]*p_v[i]);
/* Do a check for negative volumes */
#pragma aspen  control ignore
if (p_v[i]<=0.0)
{
abort=1;
}
}
if (abort)
{
fprintf(stderr, "VolumeError in CalcHourglassControlForElems(); exit\n");
exit(VolumeError);
}
#pragma aspen  control probability(1)
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
int numElem;
numElem=m_numElem;
int abort = 0;
#pragma aspen  control probability(1)
if (numElem!=0)
{
double hgcoef;
hgcoef=m_hgcoef;
/*

      Real_tsigxx  = Allocate(numElem) ;
      Real_t *sigyy  = Allocate(numElem) ;
      Real_t *sigzz  = Allocate(numElem) ;
      Real_t *determ = Allocate(numElem) ;

*/
/* Sum contributions to total stress tensor */
InitStressTermsForElems(numElem, sigxx, sigyy, sigzz, m_p, m_q);
/* call elemlib stress integration loop to produce nodal forces from */
/* material stresses. */
IntegrateStressForElems(numElem, sigxx, sigyy, sigzz, determ, m_nodelist, m_x, m_y, m_z, m_nodeElemCount, m_nodeElemStart, m_nodeElemCornerList, m_fx, m_fy, m_fz);
/* check for negative element volume */
#pragma aspen  control ignore
for (k=0; k<numElem;  ++ k)
{
if (determ[k]<=0.0)
{
abort=1;
}
}
if (abort==1)
{
fprintf(stderr, "VolumeError in CalcVolumeForceForElems(); exit\n");
exit(VolumeError);
}
/* CalcHourglassControlForElems(determ,hgcoef,m_nodelist,m_volo,m_v) ; */
/*

      Release(&determ) ;
      Release(&sigzz) ;
      Release(&sigyy) ;
      Release(&sigxx) ;

*/
}
return ;
}

static inline void CalcForceForNodes(double p_fx[(((300+1)*(300+1))*(300+1))], double p_fy[(((300+1)*(300+1))*(300+1))], double p_fz[(((300+1)*(300+1))*(300+1))])
{
int i;
int numNode;
numNode=m_numNode;
for (i=0; i<numNode;  ++ i)
{
p_fx[i]=0.0;
p_fy[i]=0.0;
p_fz[i]=0.0;
}
/* Calcforce calls partial, force, hourq */
CalcVolumeForceForElems();
/* Calculate Nodal Forces at domain boundaries */
/* problem->commSBN->Transfer(CommSBN::forces); */
return ;
}

static inline void CalcAccelerationForNodes(double p_fx[(((300+1)*(300+1))*(300+1))], double p_fy[(((300+1)*(300+1))*(300+1))], double p_fz[(((300+1)*(300+1))*(300+1))], double p_xdd[(((300+1)*(300+1))*(300+1))], double p_ydd[(((300+1)*(300+1))*(300+1))], double p_zdd[(((300+1)*(300+1))*(300+1))], double p_nodalMass[(((300+1)*(300+1))*(300+1))])
{
int i;
int numNode;
numNode=m_numNode;
for (i=0; i<numNode;  ++ i)
{
#pragma aspen  control stores(0:from(p_xdd):traits(initialized(0)))
p_xdd[i]=(p_fx[i]/p_nodalMass[i]);
#pragma aspen  control stores(0:from(p_ydd):traits(initialized(0)))
p_ydd[i]=(p_fy[i]/p_nodalMass[i]);
#pragma aspen  control stores(0:from(p_zdd):traits(initialized(0)))
p_zdd[i]=(p_fz[i]/p_nodalMass[i]);
}
return ;
}

static inline void ApplyAccelerationBoundaryConditionsForNodes(double p_xdd[(((300+1)*(300+1))*(300+1))], double p_ydd[(((300+1)*(300+1))*(300+1))], double p_zdd[(((300+1)*(300+1))*(300+1))], int p_symmX[((300+1)*(300+1))], int p_symmY[((300+1)*(300+1))], int p_symmZ[((300+1)*(300+1))])
{
int i;
int numNodeBC;
numNodeBC=(m_sizeX+1)*(m_sizeX+1);
{
for (i=0; i<numNodeBC;  ++ i)
{
p_xdd[p_symmX[i]]=0.0;
}
for (i=0; i<numNodeBC;  ++ i)
{
p_ydd[p_symmY[i]]=0.0;
}
for (i=0; i<numNodeBC;  ++ i)
{
p_zdd[p_symmZ[i]]=0.0;
}
}
return ;
}

static inline void CalcVelocityForNodes(const double dt, const double u_cut, double p_xd[(((300+1)*(300+1))*(300+1))], double p_yd[(((300+1)*(300+1))*(300+1))], double p_zd[(((300+1)*(300+1))*(300+1))], double p_xdd[(((300+1)*(300+1))*(300+1))], double p_ydd[(((300+1)*(300+1))*(300+1))], double p_zdd[(((300+1)*(300+1))*(300+1))])
{
int i;
int numNode;
numNode=m_numNode;
for (i=0; i<numNode;  ++ i)
{
double xdtmp;
double ydtmp;
double zdtmp;
xdtmp=(p_xd[i]+(p_xdd[i]*dt));
#pragma aspen  control probability(1)
if (FABS8(xdtmp)<u_cut)
{
xdtmp=0.0;
}
#pragma aspen  control stores(0:from(p_xd):traits(initialized(0)))
p_xd[i]=xdtmp;
ydtmp=(p_yd[i]+(p_ydd[i]*dt));
#pragma aspen  control probability(1)
if (FABS8(ydtmp)<u_cut)
{
ydtmp=0.0;
}
#pragma aspen  control stores(0:from(p_yd):traits(initialized(0)))
p_yd[i]=ydtmp;
zdtmp=(p_zd[i]+(p_zdd[i]*dt));
#pragma aspen  control probability(1)
if (FABS8(zdtmp)<u_cut)
{
zdtmp=0.0;
}
#pragma aspen  control stores(0:from(p_zd):traits(initialized(0)))
p_zd[i]=zdtmp;
}
return ;
}

static inline void CalcPositionForNodes(const double dt, double p_x[(((300+1)*(300+1))*(300+1))], double p_y[(((300+1)*(300+1))*(300+1))], double p_z[(((300+1)*(300+1))*(300+1))], double p_xd[(((300+1)*(300+1))*(300+1))], double p_yd[(((300+1)*(300+1))*(300+1))], double p_zd[(((300+1)*(300+1))*(300+1))])
{
int i;
int numNode;
numNode=m_numNode;
for (i=0; i<numNode;  ++ i)
{
p_x[i]+=(p_xd[i]*dt);
p_y[i]+=(p_yd[i]*dt);
p_z[i]+=(p_zd[i]*dt);
}
return ;
}

static inline void LagrangeNodal()
{
const double delt = m_deltatime;
double u_cut;
u_cut=m_u_cut;
/*
time of boundary condition evaluation is beginning of step for force and
 acceleration boundary conditions.
*/
/* Monil CalcForceForNodes(m_fx,m_fy,m_fz); */
CalcForceForNodes(m_fx, m_fy, m_fz);
/* Monil CalcAccelerationForNodes(m_fx,m_fy,m_fz,m_xdd,m_ydd,m_zdd,m_nodalMass); */
CalcAccelerationForNodes(m_fx, m_fy, m_fz, m_xdd, m_ydd, m_zdd, m_nodalMass);
/* Monil ApplyAccelerationBoundaryConditionsForNodes(m_xdd,m_ydd,m_zdd,m_symmX,m_symmY,m_symmZ); */
ApplyAccelerationBoundaryConditionsForNodes(m_xdd, m_ydd, m_zdd, m_symmX, m_symmY, m_symmZ);
/* CalcVelocityForNodes(delt,u_cut,m_xd,m_yd,m_zd,m_xdd,m_ydd,m_zdd); */
CalcVelocityForNodes(delt, u_cut, m_xd, m_yd, m_zd, m_xdd, m_ydd, m_zdd);
/* Monil CalcPositionForNodes(delt,m_x,m_y,m_z,m_xd,m_yd,m_zd); */
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
d[0]=(inv_detJ*((((pfx[0]*(xvel[0]-xvel[6]))+(pfx[1]*(xvel[1]-xvel[7])))+(pfx[2]*(xvel[2]-xvel[4])))+(pfx[3]*(xvel[3]-xvel[5]))));
d[1]=(inv_detJ*((((pfy[0]*(yvel[0]-yvel[6]))+(pfy[1]*(yvel[1]-yvel[7])))+(pfy[2]*(yvel[2]-yvel[4])))+(pfy[3]*(yvel[3]-yvel[5]))));
d[2]=(inv_detJ*((((pfz[0]*(zvel[0]-zvel[6]))+(pfz[1]*(zvel[1]-zvel[7])))+(pfz[2]*(zvel[2]-zvel[4])))+(pfz[3]*(zvel[3]-zvel[5]))));
dyddx=(inv_detJ*((((pfx[0]*(yvel[0]-yvel[6]))+(pfx[1]*(yvel[1]-yvel[7])))+(pfx[2]*(yvel[2]-yvel[4])))+(pfx[3]*(yvel[3]-yvel[5]))));
dxddy=(inv_detJ*((((pfy[0]*(xvel[0]-xvel[6]))+(pfy[1]*(xvel[1]-xvel[7])))+(pfy[2]*(xvel[2]-xvel[4])))+(pfy[3]*(xvel[3]-xvel[5]))));
dzddx=(inv_detJ*((((pfx[0]*(zvel[0]-zvel[6]))+(pfx[1]*(zvel[1]-zvel[7])))+(pfx[2]*(zvel[2]-zvel[4])))+(pfx[3]*(zvel[3]-zvel[5]))));
dxddz=(inv_detJ*((((pfz[0]*(xvel[0]-xvel[6]))+(pfz[1]*(xvel[1]-xvel[7])))+(pfz[2]*(xvel[2]-xvel[4])))+(pfz[3]*(xvel[3]-xvel[5]))));
dzddy=(inv_detJ*((((pfy[0]*(zvel[0]-zvel[6]))+(pfy[1]*(zvel[1]-zvel[7])))+(pfy[2]*(zvel[2]-zvel[4])))+(pfy[3]*(zvel[3]-zvel[5]))));
dyddz=(inv_detJ*((((pfz[0]*(yvel[0]-yvel[6]))+(pfz[1]*(yvel[1]-yvel[7])))+(pfz[2]*(yvel[2]-yvel[4])))+(pfz[3]*(yvel[3]-yvel[5]))));
d[5]=(0.5*(dxddy+dyddx));
d[4]=(0.5*(dxddz+dzddx));
d[3]=(0.5*(dzddy+dyddz));
return ;
}

/*

#pragma aspen control ignore
    for( lnode=0 ; lnode<8; ++lnode )
    {

#pragma aspen  control loads((0:from(elemToNode):traits(pattern(stencil4)))
#pragma aspen  control loads(0:from(elemToNode):traits(pattern(stencil8)))
      gnode = elemToNode[lnode];
      Index_t gnode = elemToNode[lnode];
#pragma aspen  control loads(((1aspen_param_sizeof_int)):from(elemNodes):traits(pattern(stencil4)))

#pragma aspen control ignore
      {
      Index_t gnode = elemToNode[lnode];
      }
#pragma aspen  control loads(((1*aspen_param_sizeof_int)):from(elemToNode):traits(pattern(stencil8)))



#pragma aspen  control loads(0:from(p_x):traits(pattern(stencil8)))
      x_local[lnode] = p_x[gnode];
#pragma aspen  control loads(0:from(p_y):traits(pattern(stencil8)))
      y_local[lnode] = p_y[gnode];
#pragma aspen  control loads(0:from(p_z):traits(pattern(stencil8)))
      z_local[lnode] = p_z[gnode];
    }

*/
static inline void CalcKinematicsForElems(int numElem, double dt, int p_nodelist[(((300*300)*300)*8)], double m_x[(((300+1)*(300+1))*(300+1))], double m_y[(((300+1)*(300+1))*(300+1))], double m_z[(((300+1)*(300+1))*(300+1))], double m_volo[((300*300)*300)], double m_v[((300*300)*300)], double m_vnew[((300*300)*300)], double m_delv[((300*300)*300)], double m_arealg[((300*300)*300)], double m_xd[(((300+1)*(300+1))*(300+1))], double m_yd[(((300+1)*(300+1))*(300+1))], double m_zd[(((300+1)*(300+1))*(300+1))], double m_dxx[((300*300)*300)], double m_dyy[((300*300)*300)], double m_dzz[((300*300)*300)])
{
int k;
int lnode;
int j;
/* loop over all elements */
#pragma aspen  control label(block_CalcKinematicsForElems9) loop(numElem) parallelism(numElem) flops(1:traits(integer))
for (k=0; k<numElem;  ++ k)
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
double detJ = 0.0;
double volume;
double relativeVolume;
#pragma aspen  declare data(elemToNode:traits(Array(8, aspen_param_int)))
const int * const elemToNode =  & p_nodelist[(8*k)];
#pragma aspen  control label(block_CalcKinematicsForElems486) loads((1*aspen_param_sizeof_int):from(elemToNode))
double dt2;
/*

    for( lnode=0 ; lnode<2; ++lnode )
    {

      Index_t gnode = elemToNode[lnode];
      x_local[lnode] = p_x[gnode];
      y_local[lnode] = p_y[gnode];
      z_local[lnode] = p_z[gnode];
    }

*/
/* get nodal coordinates from global arrays and copy into local arrays. */
#pragma aspen  control label(block_CalcKinematicsForElems31) loop(8) flops(1:traits(integer))
for (lnode=0; lnode<8;  ++ lnode)
{
#pragma aspen  control ignore
{
int gnode;
gnode=elemToNode[lnode];
}
#pragma aspen  control execute label(block_CalcKinematicsForElems491) loads(((1*aspen_param_sizeof_double)*8):from(m_x):traits(pattern(stencil8), reuse_SK_noprefetch(2.5), reuse_SK_prefetch(2.5)))
x_local[lnode]=m_x[gnode];
#pragma aspen  control execute label(block_CalcKinematicsForElems492) loads(((1*aspen_param_sizeof_double)*8):from(m_y):traits(pattern(stencil8), reuse_SK_noprefetch(2.5), reuse_SK_prefetch(2.5)))
y_local[lnode]=m_y[gnode];
#pragma aspen  control execute label(block_CalcKinematicsForElems493) loads(((1*aspen_param_sizeof_double)*8):from(m_z):traits(pattern(stencil8), reuse_SK_noprefetch(2.5), reuse_SK_prefetch(2.5)))
z_local[lnode]=m_z[gnode];
}
/* volume calculations */
volume=CalcElemVolume(x_local, y_local, z_local);
#pragma aspen  control execute label(block_CalcKinematicsForElems38) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_volo):traits(stride(1)))
relativeVolume=(volume/m_volo[k]);
#pragma aspen  control execute label(block_CalcKinematicsForElems39) stores((1*aspen_param_sizeof_double):to(m_vnew):traits(stride(1)))
m_vnew[k]=relativeVolume;
#pragma aspen  control execute label(block_CalcKinematicsForElems40) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_v):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_delv):traits(stride(1)))
m_delv[k]=(relativeVolume-m_v[k]);
/* set characteristic length */
#pragma aspen  control label(block_CalcKinematicsForElems42) stores((1*aspen_param_sizeof_double):to(m_arealg):traits(stride(1)))
m_arealg[k]=CalcElemCharacteristicLength(x_local, y_local, z_local, volume);
/*

    get nodal velocities from global array and copy into local arrays.

    for( lnode=0 ; lnode<2 ; ++lnode )
    {
      Index_t gnode = elemToNode[lnode];
      xd_local[lnode] = p_xd[gnode];
      yd_local[lnode] = p_yd[gnode];
      zd_local[lnode] = p_zd[gnode];
    }

*/
/* get nodal velocities from global array and copy into local arrays. */
#pragma aspen  control label(block_CalcKinematicsForElems45) loop(8) flops(1:traits(integer))
for (lnode=0; lnode<8;  ++ lnode)
{
#pragma aspen  control ignore
{
int gnode;
gnode=elemToNode[lnode];
}
/* #pragma aspen  control loads(((1aspen_param_sizeof_int)):from(elemToNode):traits(pattern(stencil4))) */
#pragma aspen  control execute label(block_CalcKinematicsForElems554) loads(((1*aspen_param_sizeof_double)*8):from(m_xd):traits(pattern(stencil8), reuse_SK_noprefetch(2.5), reuse_SK_prefetch(2.5)))
xd_local[lnode]=m_xd[gnode];
#pragma aspen  control execute label(block_CalcKinematicsForElems555) loads(((1*aspen_param_sizeof_double)*8):from(m_yd):traits(pattern(stencil8), reuse_SK_noprefetch(2.5), reuse_SK_prefetch(2.5)))
yd_local[lnode]=m_yd[gnode];
#pragma aspen  control execute label(block_CalcKinematicsForElems556) loads(((1*aspen_param_sizeof_double)*8):from(m_zd):traits(pattern(stencil8), reuse_SK_noprefetch(2.5), reuse_SK_prefetch(2.5)))
zd_local[lnode]=m_zd[gnode];
}
#pragma aspen  control execute label(block_CalcKinematicsForElems51) flops(1:traits(dp))
dt2=(0.5*dt);
/* #pragma aspen control ignore */
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
/* Monil This function does only local computation and does not create memory traffic.  */
/* #pragma aspen control ignore */
CalcElemShapeFunctionDerivatives(x_local, y_local, z_local, B, ( & detJ));
/* Monil This function is ignored because it only does local computation on local variables of size 8 */
/* For this reason this function does not create any memory traffic and hence ignored. The reason  */
/* because MAPredict counts this function because, there are some variabled defined in the function  */
/* which force MAPredict to calculate the memory access. */
/* However, for execution time prediction this function needs to be take care of */
#pragma aspen  control ignore
CalcElemVelocityGrandient(xd_local, yd_local, zd_local, B, detJ, D);
/* put velocity gradient quantities into their global arrays. */
#pragma aspen  control execute label(block_CalcKinematicsForElems67) stores((1*aspen_param_sizeof_double):to(m_dxx):traits(stride(1)))
m_dxx[k]=D[0];
#pragma aspen  control execute label(block_CalcKinematicsForElems68) stores((1*aspen_param_sizeof_double):to(m_dyy):traits(stride(1)))
m_dyy[k]=D[1];
#pragma aspen  control execute label(block_CalcKinematicsForElems69) stores((1*aspen_param_sizeof_double):to(m_dzz):traits(stride(1)))
m_dzz[k]=D[2];
}
return ;
}

static inline void CalcLagrangeElements(double deltatime, double m_vnew[((300*300)*300)], double m_vdov[((300*300)*300)], double m_dxx[((300*300)*300)], double m_dyy[((300*300)*300)], double m_dzz[((300*300)*300)])
{
int k;
#pragma aspen  declare param(numElem:m_numElem)
int numElem;
#pragma aspen  control ignore
numElem=m_numElem;
int abort = 0;
#pragma aspen  control label(block_CalcLagrangeElements463) probability(1) flops(1:traits(integer))
if (numElem>0)
{
CalcKinematicsForElems(numElem, deltatime, m_nodelist, m_x, m_y, m_z, m_volo, m_v, m_vnew, m_delv, m_arealg, m_xd, m_yd, m_zd, m_dxx, m_dyy, m_dzz);
/* element loop to do some stuff not included in the elemlib function. */
#pragma aspen  control label(block_CalcLagrangeElements11) loop(numElem) parallelism(numElem) flops(1:traits(integer))
for (k=0; k<numElem;  ++ k)
{
/* calc strain rate and apply as constraint (only done in FB element) */
double vdov;
#pragma aspen  control execute label(block_CalcLagrangeElements15) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_dxx):traits(stride(1)), (1*aspen_param_sizeof_double):from(m_dyy):traits(stride(1)), (1*aspen_param_sizeof_double):from(m_dzz):traits(stride(1)))
vdov=(m_dxx[k]+m_dyy[k])+m_dzz[k];
double vdovthird;
#pragma aspen  control execute label(block_CalcLagrangeElements18) flops(1:traits(dp))
vdovthird=vdov/3.0;
/* make the rate of deformation tensor deviatoric */
/* Monil this is a genuine uninitialzed write */
#pragma aspen  control execute label(block_CalcLagrangeElements675) stores((1*aspen_param_sizeof_double):from(m_vdov):traits(initialized(0)))
m_vdov[k]=vdov;
/* Monil here uninitialized traits is used not because it is uninitialized but because  */
/* the variables are already read three lines before and already in the cache and hence */
/* while allocating store they will not be brought to the cache again and hence the behaviour */
/* is totaly like uninitialized variables */
#pragma aspen  control execute label(block_CalcLagrangeElements680) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):from(m_dxx):traits(initialized(0)))
m_dxx[k]-=vdovthird;
#pragma aspen  control execute label(block_CalcLagrangeElements681) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):from(m_dyy):traits(initialized(0)))
m_dyy[k]-=vdovthird;
#pragma aspen  control execute label(block_CalcLagrangeElements682) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):from(m_dzz):traits(initialized(0)))
m_dzz[k]-=vdovthird;
/* See if any volumes are negative, and take appropriate action. */
/* Monil commented out this since the if logic will access the variable */
/* #pragma aspen control ignore */
#pragma aspen  control label(block_CalcLagrangeElements686) probability(0) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_vnew):traits(stride(1)))
if (m_vnew[k]<=0.0)
{
#pragma aspen  control ignore
abort=1;
}
}
#pragma aspen  control ignore
if (abort==1)
{
fprintf(stderr, "VolumeError in CalcLagrangeElements(); exit\n");
exit(VolumeError);
}
}
return ;
}

/* Monil currently working here */
static inline void CalcMonotonicQGradientsForElems(int m_nodelist[(((300*300)*300)*8)], double p_x[(((300+1)*(300+1))*(300+1))], double p_y[(((300+1)*(300+1))*(300+1))], double p_z[(((300+1)*(300+1))*(300+1))], double p_xd[(((300+1)*(300+1))*(300+1))], double p_yd[(((300+1)*(300+1))*(300+1))], double p_zd[(((300+1)*(300+1))*(300+1))], double m_volo[((300*300)*300)], double m_vnew[((300*300)*300)], double m_delx_zeta[((300*300)*300)], double m_delv_zeta[((300*300)*300)], double m_delx_xi[((300*300)*300)], double m_delv_xi[((300*300)*300)], double m_delx_eta[((300*300)*300)], double m_delv_eta[((300*300)*300)])
{
int i;
int numElem;
#pragma aspen  control ignore
numElem=m_numElem;
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
const int * elemToNode;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems22) flops(1:traits(integer)) loads((1*aspen_param_sizeof_int):from(m_nodelist))
elemToNode= & m_nodelist[(8*i)];
#pragma aspen  control ignore
{
int n0;
n0=elemToNode[0];
int n1;
n1=elemToNode[1];
int n2;
n2=elemToNode[2];
int n3;
n3=elemToNode[3];
int n4;
n4=elemToNode[4];
int n5;
n5=elemToNode[5];
int n6;
n6=elemToNode[6];
int n7;
n7=elemToNode[7];
double x0;
x0=p_x[n0];
double x1;
x1=p_x[n1];
double x2;
x2=p_x[n2];
double x3;
x3=p_x[n3];
double x4;
x4=p_x[n4];
double x5;
x5=p_x[n5];
double x6;
x6=p_x[n6];
double x7;
x7=p_x[n7];
double y0;
y0=p_y[n0];
double y1;
y1=p_y[n1];
double y2;
y2=p_y[n2];
double y3;
y3=p_y[n3];
double y4;
y4=p_y[n4];
double y5;
y5=p_y[n5];
double y6;
y6=p_y[n6];
double y7;
y7=p_y[n7];
double z0;
z0=p_z[n0];
double z1;
z1=p_z[n1];
double z2;
z2=p_z[n2];
double z3;
z3=p_z[n3];
double z4;
z4=p_z[n4];
double z5;
z5=p_z[n5];
double z6;
z6=p_z[n6];
double z7;
z7=p_z[n7];
double xv0;
xv0=p_xd[n0];
double xv1;
xv1=p_xd[n1];
double xv2;
xv2=p_xd[n2];
double xv3;
xv3=p_xd[n3];
double xv4;
xv4=p_xd[n4];
double xv5;
xv5=p_xd[n5];
double xv6;
xv6=p_xd[n6];
double xv7;
xv7=p_xd[n7];
double yv0;
yv0=p_yd[n0];
double yv1;
yv1=p_yd[n1];
double yv2;
yv2=p_yd[n2];
double yv3;
yv3=p_yd[n3];
double yv4;
yv4=p_yd[n4];
double yv5;
yv5=p_yd[n5];
double yv6;
yv6=p_yd[n6];
double yv7;
yv7=p_yd[n7];
double zv0;
zv0=p_zd[n0];
double zv1;
zv1=p_zd[n1];
double zv2;
zv2=p_zd[n2];
double zv3;
zv3=p_zd[n3];
double zv4;
zv4=p_zd[n4];
double zv5;
zv5=p_zd[n5];
double zv6;
zv6=p_zd[n6];
double zv7;
zv7=p_zd[n7];
}
/* #pragma aspen  control loads((1aspen_param_sizeof_int):from(elemToNode)) */
/* #pragma aspen  control loads((1aspen_param_sizeof_int*8):from(elemToNode):traits(pattern(stencil4))) */
#pragma aspen  control label(block_CalcMonotonicQGradientsForElems719) loads(((1*aspen_param_sizeof_double)*8):from(m_x):traits(pattern(stencil8), reuse_SK_noprefetch(2.5), reuse_SK_prefetch(2.5)))
#pragma aspen  control label(block_CalcMonotonicQGradientsForElems719) loads(((1*aspen_param_sizeof_double)*8):from(m_y):traits(pattern(stencil8), reuse_SK_noprefetch(2.5), reuse_SK_prefetch(2.5)))
#pragma aspen  control label(block_CalcMonotonicQGradientsForElems719) loads(((1*aspen_param_sizeof_double)*8):from(m_z):traits(pattern(stencil8), reuse_SK_noprefetch(2.5), reuse_SK_prefetch(2.5)))
#pragma aspen  control label(block_CalcMonotonicQGradientsForElems719) loads(((1*aspen_param_sizeof_double)*8):from(m_xd):traits(pattern(stencil8), reuse_SK_noprefetch(2.5), reuse_SK_prefetch(2.5)))
#pragma aspen  control label(block_CalcMonotonicQGradientsForElems719) loads(((1*aspen_param_sizeof_double)*8):from(m_yd):traits(pattern(stencil8), reuse_SK_noprefetch(2.5), reuse_SK_prefetch(2.5)))
#pragma aspen  control label(block_CalcMonotonicQGradientsForElems719) loads(((1*aspen_param_sizeof_double)*8):from(m_zd):traits(pattern(stencil8), reuse_SK_noprefetch(2.5), reuse_SK_prefetch(2.5)))
double vol;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems28) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(m_vnew):traits(stride(1)), (1*aspen_param_sizeof_double):from(m_volo):traits(stride(1)))
vol=m_volo[i]*m_vnew[i];
double norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems31) flops(2:traits(dp))
norm=1.0/(vol+ptiny);
double dxj;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems34) flops(1:traits(dp), 7:traits(integer))
dxj=( - 0.25)*((((x0+x1)+x5)+x4)-(((x3+x2)+x6)+x7));
double dyj;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems37) flops(3:traits(integer), 5:traits(dp))
dyj=( - 0.25)*((((y0+y1)+y5)+y4)-(((y3+y2)+y6)+y7));
double dzj;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems40) flops(1:traits(dp), 7:traits(integer))
dzj=( - 0.25)*((((z0+z1)+z5)+z4)-(((z3+z2)+z6)+z7));
double dxi;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems43) flops(1:traits(dp), 7:traits(integer))
dxi=0.25*((((x1+x2)+x6)+x5)-(((x0+x3)+x7)+x4));
double dyi;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems46) flops(8:traits(dp))
dyi=0.25*((((y1+y2)+y6)+y5)-(((y0+y3)+y7)+y4));
double dzi;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems49) flops(1:traits(dp), 7:traits(integer))
dzi=0.25*((((z1+z2)+z6)+z5)-(((z0+z3)+z7)+z4));
double dxk;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems52) flops(1:traits(dp), 7:traits(integer))
dxk=0.25*((((x4+x5)+x6)+x7)-(((x0+x1)+x2)+x3));
double dyk;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems55) flops(3:traits(integer), 5:traits(dp))
dyk=0.25*((((y4+y5)+y6)+y7)-(((y0+y1)+y2)+y3));
double dzk;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems58) flops(1:traits(dp), 7:traits(integer))
dzk=0.25*((((z4+z5)+z6)+z7)-(((z0+z1)+z2)+z3));
/* find delvk and delxk ( i cross j ) */
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems60) flops(3:traits(dp))
ax=((dyi*dzj)-(dzi*dyj));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems61) flops(3:traits(dp))
ay=((dzi*dxj)-(dxi*dzj));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems62) flops(3:traits(dp))
az=((dxi*dyj)-(dyi*dxj));
#pragma aspen  control label(block_CalcMonotonicQGradientsForElems63) flops(7:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_delx_zeta):traits(stride(1)))
m_delx_zeta[i]=(vol/SQRT8(((((ax*ax)+(ay*ay))+(az*az))+ptiny)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems64) flops(1:traits(dp))
ax*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems65) flops(1:traits(dp))
ay*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems66) flops(1:traits(dp))
az*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems67) flops(1:traits(dp), 7:traits(integer))
dxv=(0.25*((((xv4+xv5)+xv6)+xv7)-(((xv0+xv1)+xv2)+xv3)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems68) flops(1:traits(dp), 7:traits(integer))
dyv=(0.25*((((yv4+yv5)+yv6)+yv7)-(((yv0+yv1)+yv2)+yv3)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems69) flops(1:traits(dp), 7:traits(integer))
dzv=(0.25*((((zv4+zv5)+zv6)+zv7)-(((zv0+zv1)+zv2)+zv3)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems70) flops(5:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_delv_zeta):traits(stride(1)))
m_delv_zeta[i]=(((ax*dxv)+(ay*dyv))+(az*dzv));
/* find delxi and delvi ( j cross k ) */
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems72) flops(3:traits(dp))
ax=((dyj*dzk)-(dzj*dyk));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems73) flops(3:traits(dp))
ay=((dzj*dxk)-(dxj*dzk));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems74) flops(3:traits(dp))
az=((dxj*dyk)-(dyj*dxk));
#pragma aspen  control label(block_CalcMonotonicQGradientsForElems75) flops(7:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_delx_xi):traits(stride(1)))
m_delx_xi[i]=(vol/SQRT8(((((ax*ax)+(ay*ay))+(az*az))+ptiny)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems76) flops(1:traits(dp))
ax*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems77) flops(1:traits(dp))
ay*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems78) flops(1:traits(dp))
az*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems79) flops(1:traits(dp), 7:traits(integer))
dxv=(0.25*((((xv1+xv2)+xv6)+xv5)-(((xv0+xv3)+xv7)+xv4)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems80) flops(1:traits(dp), 7:traits(integer))
dyv=(0.25*((((yv1+yv2)+yv6)+yv5)-(((yv0+yv3)+yv7)+yv4)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems81) flops(1:traits(dp), 7:traits(integer))
dzv=(0.25*((((zv1+zv2)+zv6)+zv5)-(((zv0+zv3)+zv7)+zv4)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems82) flops(5:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_delv_xi):traits(stride(1)))
m_delv_xi[i]=(((ax*dxv)+(ay*dyv))+(az*dzv));
/* find delxj and delvj ( k cross i ) */
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems84) flops(3:traits(dp))
ax=((dyk*dzi)-(dzk*dyi));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems85) flops(3:traits(dp))
ay=((dzk*dxi)-(dxk*dzi));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems86) flops(3:traits(dp))
az=((dxk*dyi)-(dyk*dxi));
#pragma aspen  control label(block_CalcMonotonicQGradientsForElems87) flops(7:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_delx_eta):traits(stride(1)))
m_delx_eta[i]=(vol/SQRT8(((((ax*ax)+(ay*ay))+(az*az))+ptiny)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems88) flops(1:traits(dp))
ax*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems89) flops(1:traits(dp))
ay*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems90) flops(1:traits(dp))
az*=norm;
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems91) flops(1:traits(dp), 7:traits(integer))
dxv=(( - 0.25)*((((xv0+xv1)+xv5)+xv4)-(((xv3+xv2)+xv6)+xv7)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems92) flops(1:traits(dp), 7:traits(integer))
dyv=(( - 0.25)*((((yv0+yv1)+yv5)+yv4)-(((yv3+yv2)+yv6)+yv7)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems93) flops(1:traits(dp), 7:traits(integer))
dzv=(( - 0.25)*((((zv0+zv1)+zv5)+zv4)-(((zv3+zv2)+zv6)+zv7)));
#pragma aspen  control execute label(block_CalcMonotonicQGradientsForElems94) flops(5:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(m_delv_eta):traits(stride(1)))
m_delv_eta[i]=(((ax*dxv)+(ay*dyv))+(az*dzv));
}
return ;
}

/* Monil's work done here */
/* parameters */
/* the elementset length */
static inline void CalcMonotonicQRegionForElems(double qlc_monoq, double qqc_monoq, double monoq_limiter_mult, double monoq_max_slope, double ptiny, int elength, int m_matElemlist[((300*300)*300)], int m_elemBC[((300*300)*300)], double m_delx_xi[((300*300)*300)], double m_delx_eta[((300*300)*300)], double m_delx_zeta[((300*300)*300)], double m_delv_xi[((300*300)*300)], double m_delv_eta[((300*300)*300)], double m_delv_zeta[((300*300)*300)], int m_lxim[((300*300)*300)], int m_lxip[((300*300)*300)], int m_letam[((300*300)*300)], int m_letap[((300*300)*300)], int m_lzetam[((300*300)*300)], int m_lzetap[((300*300)*300)], double m_vnew[((300*300)*300)], double m_vdov[((300*300)*300)], double m_volo[((300*300)*300)], double m_elemMass[((300*300)*300)], double m_qq[((300*300)*300)], double m_ql[((300*300)*300)])
{
int ielem;
/* #pragma aspen  control execute label(block_CalcMonotonicQRegionForElems21) traits(initialized(0))) */
#pragma aspen  control label(block_CalcMonotonicQRegionForElems9) loop(elength) parallelism(elength) flops(1:traits(integer))
for (ielem=0; ielem<elength;  ++ ielem)
{
double qlin;
double qquad;
double phixi;
double phieta;
double phizeta;
int i;
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems22) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
i=m_matElemlist[ielem];
int bcMask;
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems25) loads((1*aspen_param_sizeof_int):from(m_elemBC))
bcMask=m_elemBC[i];
double delvm;
double delvp;
#pragma aspen  declare param(aspen_param_reuse_block_CalcMonotonicQRegionForElems22_SK_prefetch:1.75)
/* #pragma aspen declare param(aspen_param_vdov2:0.1) */
/*  phixi     */
double norm;
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems35) flops(2:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_delv_xi))
norm=1.0/(m_delv_xi[i]+ptiny);
switch ((bcMask&0x3))
{
case 0:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems38) loads((1*aspen_param_sizeof_double):from(m_delv_xi):traits(random), (1*aspen_param_sizeof_int):from(m_lxim))
delvm=m_delv_xi[m_lxim[i]];
break;
/* if(1){ delvm = p_delv_xi[i] ; } */
#pragma aspen  control label(block_CalcMonotonicQRegionForElems832) probability(0)
case 0x1:
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
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems52) loads((1*aspen_param_sizeof_double):from(m_delv_xi):traits(random), (1*aspen_param_sizeof_int):from(m_lxip))
delvp=m_delv_xi[m_lxip[i]];
break;
/* if (1) delvp = p_delv_xi[i] ;             */
#pragma aspen  control label(block_CalcMonotonicQRegionForElems846) probability(0)
case 0x4:
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
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems64) flops(1:traits(dp))
delvm=(delvm*norm);
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems65) flops(1:traits(dp))
delvp=(delvp*norm);
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems66) flops(2:traits(dp))
phixi=(0.5*(delvm+delvp));
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems67) flops(1:traits(dp))
delvm*=monoq_limiter_mult;
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems68) flops(1:traits(dp))
delvp*=monoq_limiter_mult;
#pragma aspen  control label(block_CalcMonotonicQRegionForElems69) if(delvm<phixi) flops(1:traits(dp))
if (delvm<phixi)
{
#pragma aspen  control ignore
phixi=delvm;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems71) if(delvp<phixi) flops(1:traits(dp))
if (delvp<phixi)
{
#pragma aspen  control ignore
phixi=delvp;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems73) if(phixi<0.0) flops(1:traits(dp))
if (phixi<0.0)
{
#pragma aspen  control ignore
phixi=0.0;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems75) if(phixi>monoq_max_slope) flops(1:traits(dp))
if (phixi>monoq_max_slope)
{
#pragma aspen  control ignore
phixi=monoq_max_slope;
}
/*  phieta     */
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems78) flops(2:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_delv_eta))
norm=(1.0/(m_delv_eta[i]+ptiny));
switch ((bcMask&0x30))
{
case 0:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems81) loads((1*aspen_param_sizeof_double):from(m_delv_eta):traits(random), (1*aspen_param_sizeof_int):from(m_letam))
delvm=m_delv_eta[m_letam[i]];
break;
/* if(1) delvm = p_delv_eta[i] ;              */
#pragma aspen  control label(block_CalcMonotonicQRegionForElems875) probability(0)
case 0x10:
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
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems95) loads((1*aspen_param_sizeof_double):from(m_delv_eta):traits(random), (1*aspen_param_sizeof_int):from(m_letap))
delvp=m_delv_eta[m_letap[i]];
break;
/* if(1) delvp = p_delv_eta[i] ;              */
#pragma aspen  control label(block_CalcMonotonicQRegionForElems889) probability(0)
case 0x40:
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
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems107) flops(1:traits(dp))
delvm=(delvm*norm);
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems108) flops(1:traits(dp))
delvp=(delvp*norm);
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems109) flops(2:traits(dp))
phieta=(0.5*(delvm+delvp));
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems110) flops(1:traits(dp))
delvm*=monoq_limiter_mult;
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems111) flops(1:traits(dp))
delvp*=monoq_limiter_mult;
#pragma aspen  control label(block_CalcMonotonicQRegionForElems112) if(delvm<phieta) flops(1:traits(dp))
if (delvm<phieta)
{
#pragma aspen  control ignore
phieta=delvm;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems114) if(delvp<phieta) flops(1:traits(dp))
if (delvp<phieta)
{
#pragma aspen  control ignore
phieta=delvp;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems116) if(phieta<0.0) flops(1:traits(dp))
if (phieta<0.0)
{
#pragma aspen  control ignore
phieta=0.0;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems118) if(phieta>monoq_max_slope) flops(1:traits(dp))
if (phieta>monoq_max_slope)
{
#pragma aspen  control ignore
phieta=monoq_max_slope;
}
/*  phizeta     */
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems121) flops(2:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_delv_zeta))
norm=(1.0/(m_delv_zeta[i]+ptiny));
switch ((bcMask&0x300))
{
case 0:
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems124) loads((1*aspen_param_sizeof_double):from(m_delv_zeta):traits(random), (1*aspen_param_sizeof_int):from(m_lzetam))
delvm=m_delv_zeta[m_lzetam[i]];
break;
/* if(1) delvm = p_delv_zeta[i] ;               */
#pragma aspen  control label(block_CalcMonotonicQRegionForElems918) probability(0)
case 0x100:
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
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems138) loads((1*aspen_param_sizeof_double):from(m_delv_zeta):traits(random), (1*aspen_param_sizeof_int):from(m_lzetap))
delvp=m_delv_zeta[m_lzetap[i]];
break;
/* if(1) { delvp = p_delv_zeta[i] ;              } */
#pragma aspen  control label(block_CalcMonotonicQRegionForElems932) probability(0)
case 0x400:
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
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems150) flops(1:traits(dp))
delvm=(delvm*norm);
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems151) flops(1:traits(dp))
delvp=(delvp*norm);
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems152) flops(2:traits(dp))
phizeta=(0.5*(delvm+delvp));
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems153) flops(1:traits(dp))
delvm*=monoq_limiter_mult;
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems154) flops(1:traits(dp))
delvp*=monoq_limiter_mult;
#pragma aspen  control label(block_CalcMonotonicQRegionForElems155) if(delvm<phizeta) flops(1:traits(dp))
if (delvm<phizeta)
{
#pragma aspen  control ignore
phizeta=delvm;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems157) if(delvp<phizeta) flops(1:traits(dp))
if (delvp<phizeta)
{
#pragma aspen  control ignore
phizeta=delvp;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems159) if(phizeta<0.0) flops(1:traits(dp))
if (phizeta<0.0)
{
#pragma aspen  control ignore
phizeta=0.0;
}
#pragma aspen  control label(block_CalcMonotonicQRegionForElems161) if(phizeta>monoq_max_slope) flops(1:traits(dp))
if (phizeta>monoq_max_slope)
{
#pragma aspen  control ignore
phizeta=monoq_max_slope;
}
/* Remove length scale */
#pragma aspen  control label(block_CalcMonotonicQRegionForElems955) probability(0) flops(1:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_vdov))
if (m_vdov[i]>0.0)
{
#pragma aspen  control ignore
qlin=0.0;
#pragma aspen  control ignore
qquad=0.0;
}
else
{
/* #pragma aspen control probability(1) */
/* if ( p_vdov[i] <= 0. )  { */
#pragma aspen  control ignore
{
double delvxxi;
delvxxi=m_delv_xi[i]*m_delx_xi[i];
double delvxeta;
delvxeta=m_delv_eta[i]*m_delx_eta[i];
double delvxzeta;
delvxzeta=m_delv_zeta[i]*m_delx_zeta[i];
}
/* #pragma aspen  control reuse((1aspen_param_sizeof_double):from(p_delx_zeta)) */
#pragma aspen  control label(block_CalcMonotonicQRegionForElems962) loads((1*aspen_param_sizeof_double):from(m_delx_xi))
#pragma aspen  control label(block_CalcMonotonicQRegionForElems962) loads((1*aspen_param_sizeof_double):from(m_delx_eta))
#pragma aspen  control label(block_CalcMonotonicQRegionForElems962) loads((1*aspen_param_sizeof_double):from(m_delx_zeta))
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
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems174) flops(2:traits(dp)) loads((1*aspen_param_sizeof_double):from(m_elemMass), (1*aspen_param_sizeof_double):from(m_vnew), (1*aspen_param_sizeof_double):from(m_volo))
rho=(m_elemMass[i]/(m_volo[i]*m_vnew[i]));
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems175) flops(10:traits(dp))
qlin=((( - qlc_monoq)*rho)*(((delvxxi*(1.0-phixi))+(delvxeta*(1.0-phieta)))+(delvxzeta*(1.0-phizeta))));
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems176) flops(13:traits(dp), 3:traits(integer))
qquad=((qqc_monoq*rho)*((((delvxxi*delvxxi)*(1.0-(phixi*phixi)))+((delvxeta*delvxeta)*(1.0-(phieta*phieta))))+((delvxzeta*delvxzeta)*(1.0-(phizeta*phizeta)))));
}
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems177) stores((1*aspen_param_sizeof_double):to(m_qq))
m_qq[i]=qquad;
#pragma aspen  control execute label(block_CalcMonotonicQRegionForElems178) stores((1*aspen_param_sizeof_double):to(m_ql))
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
#pragma aspen  control label(block_CalcMonotonicQForElems794) probability(1) flops(1:traits(integer))
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
/* Transfer veloctiy gradients in the first order elements  */
/* problem->commElements->Transfer(CommElements::monoQ) ;  */
CalcMonotonicQForElems();
/* Don't allow excessive artificial viscosity  */
#pragma aspen  control ignore
if (numElem!=0)
{
/* Index_t idx = -1;  */
int idx = 0;
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

/* #pragma aspen declare param(aspen_param_reuse_CalcPressureForElems_SK_noprefetch:3.1) */
/* #pragma aspen declare param(aspen_param_reuse_CalcPressureForElems_clnd1_SK_noprefetch:3.1) */
/* #pragma aspen declare param(aspen_param_reuse_CalcPressureForElems_clnd2_SK_noprefetch:3.1) */
/* #pragma aspen declare param(aspen_param_reuse_CalcPressureForElems_SK_prefetch:3.1) */
/* #pragma aspen declare param(aspen_param_reuse_CalcPressureForElems_clnd1_SK_prefetch:3.1) */
/* #pragma aspen declare param(aspen_param_reuse_CalcPressureForElems_clnd2_SK_prefetch:3.1) */
static inline void CalcPressureForElems(double p_new[((300*300)*300)], double bvc[((300*300)*300)], double pbvc[((300*300)*300)], double e_old[((300*300)*300)], double compression[((300*300)*300)], double vnewc[((300*300)*300)], double pmin, double p_cut, double eosvmax, int length)
{
int i;
for (i=0; i<length;  ++ i)
{
double c1s;
c1s=2.0/3.0;
bvc[i]=(c1s*(compression[i]+1.0));
pbvc[i]=c1s;
}
for (i=0; i<length;  ++ i)
{
p_new[i]=(bvc[i]*e_old[i]);
/* #pragma aspen control probability(0) */
#pragma aspen  control ignore
if (FABS8(p_new[i])<p_cut)
{
p_new[i]=0.0;
}
/* impossible condition here?  */
#pragma aspen  control ignore
if (vnewc[i]>=eosvmax)
{
p_new[i]=0.0;
}
/* #pragma aspen control probability(0) */
#pragma aspen  control ignore
if (p_new[i]<pmin)
{
p_new[i]=pmin;
}
}
return ;
}

static inline void CalcPressureForElems_clnd3(double p_new[((300*300)*300)], double bvc[((300*300)*300)], double pbvc[((300*300)*300)], double e_new[((300*300)*300)], double compression[((300*300)*300)], double vnewc[((300*300)*300)], double pmin, double p_cut, double eosvmax, int length)
{
int i;
#pragma aspen  control label(block_CalcPressureForElems_clnd36) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
double c1s;
#pragma aspen  control execute label(block_CalcPressureForElems_clnd39) flops(1:traits(dp))
c1s=2.0/3.0;
#pragma aspen  control execute label(block_CalcPressureForElems_clnd310) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(compression):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(bvc):traits(stride(1)))
bvc[i]=(c1s*(compression[i]+1.0));
#pragma aspen  control execute label(block_CalcPressureForElems_clnd311) stores((1*aspen_param_sizeof_double):to(pbvc):traits(stride(1)))
pbvc[i]=c1s;
}
#pragma aspen  control label(block_CalcPressureForElems_clnd312) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  control execute label(block_CalcPressureForElems_clnd313) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(bvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_new):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(p_new):traits(stride(1)))
p_new[i]=(bvc[i]*e_new[i]);
/* #pragma aspen control probability(0) */
#pragma aspen  control ignore
if (FABS8(p_new[i])<p_cut)
{
p_new[i]=0.0;
}
/* impossible condition here?  */
#pragma aspen  control ignore
if (vnewc[i]>=eosvmax)
{
p_new[i]=0.0;
}
/* #pragma aspen control probability(0) */
#pragma aspen  control ignore
if (p_new[i]<pmin)
{
p_new[i]=pmin;
}
}
return ;
}

static inline void CalcPressureForElems_clnd2(double p_new[((300*300)*300)], double bvc[((300*300)*300)], double pbvc[((300*300)*300)], double e_new[((300*300)*300)], double compression[((300*300)*300)], double vnewc[((300*300)*300)], double pmin, double p_cut, double eosvmax, int length)
{
int i;
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
#pragma aspen  control label(block_CalcPressureForElems_clnd212) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  control execute label(block_CalcPressureForElems_clnd213) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(bvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_new):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(p_new):traits(stride(1)))
p_new[i]=(bvc[i]*e_new[i]);
/* #pragma aspen control probability(0) */
#pragma aspen  control ignore
if (FABS8(p_new[i])<p_cut)
{
p_new[i]=0.0;
}
/* impossible condition here?  */
#pragma aspen  control ignore
if (vnewc[i]>=eosvmax)
{
p_new[i]=0.0;
}
/* #pragma aspen control probability(0) */
#pragma aspen  control ignore
if (p_new[i]<pmin)
{
p_new[i]=pmin;
}
}
return ;
}

static inline void CalcPressureForElems_clnd1(double pHalfStep[((300*300)*300)], double bvc[((300*300)*300)], double pbvc[((300*300)*300)], double e_new[((300*300)*300)], double compHalfStep[((300*300)*300)], double vnewc[((300*300)*300)], double pmin, double p_cut, double eosvmax, int length)
{
int i;
#pragma aspen  control label(block_CalcPressureForElems_clnd16) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
double c1s;
#pragma aspen  control execute label(block_CalcPressureForElems_clnd19) flops(1:traits(dp))
c1s=2.0/3.0;
#pragma aspen  control execute label(block_CalcPressureForElems_clnd110) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(compHalfStep):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(bvc):traits(stride(1)))
bvc[i]=(c1s*(compHalfStep[i]+1.0));
#pragma aspen  control execute label(block_CalcPressureForElems_clnd111) stores((1*aspen_param_sizeof_double):to(pbvc):traits(stride(1)))
pbvc[i]=c1s;
}
#pragma aspen  control label(block_CalcPressureForElems_clnd112) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  control execute label(block_CalcPressureForElems_clnd113) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(bvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_new):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(pHalfStep):traits(stride(1)))
pHalfStep[i]=(bvc[i]*e_new[i]);
/* #pragma aspen control probability(0) */
#pragma aspen  control ignore
if (FABS8(pHalfStep[i])<p_cut)
{
pHalfStep[i]=0.0;
}
/* impossible condition here?  */
#pragma aspen  control ignore
if (vnewc[i]>=eosvmax)
{
pHalfStep[i]=0.0;
}
/* #pragma aspen control probability(0) */
#pragma aspen  control ignore
if (pHalfStep[i]<pmin)
{
pHalfStep[i]=pmin;
}
}
return ;
}

static inline void CalcEnergyForElems11(double p_new[((300*300)*300)], double e_new[((300*300)*300)], double q_new[((300*300)*300)], double bvc[((300*300)*300)], double pbvc[((300*300)*300)], double p_old[((300*300)*300)], double e_old[((300*300)*300)], double q_old[((300*300)*300)], double compression[((300*300)*300)], double compHalfStep[((300*300)*300)], double vnewc[((300*300)*300)], double * work, double * delvc, double pmin, double p_cut, double e_cut, double q_cut, double emin, double * qq, double * ql, double rho0, double eosvmax, int length)
{
/* #pragma aspen declare param(aspen_param_reuse_CalcEnergyForElems_SK_noprefetch:1.8) */
/* #pragma aspen declare param(aspen_param_reuse_CalcEnergyForElems_SK_prefetch:1.8) */
int i;
double * pHalfStep;
pHalfStep=Allocate(length);
{
/*
for (i = 0 ; i < length ; ++i) {
      e_new[i] = e_old[i] - 0.5 delvc[i] * (p_old[i] + q_old[i])
         + 0.5 * work[i]; 

#if ALLOW_ASPENIFSTMT == 1
#pragma aspen declare param(aspen_param_e_new_prob:1)
#pragma aspen control probability(aspen_param_e_new_prob)
#else
#pragma aspen control probability(1)
#endif
      if (e_new[i]  < emin ) {
         e_new[i] = emin ;
      }
   }
*/
CalcPressureForElems(pHalfStep, bvc, pbvc, e_new, compHalfStep, vnewc, pmin, p_cut, eosvmax, length);
/*

#ifdef _OPENACC
#pragma acc parallel loop independent present(compHalfStep, pHalfStep, delvc, p_old,q_old, ql, qq, q_new, pbvc, bvc, e_new)
)
#else
#pragma omp parallel for private(i) firstprivate(length, rho0)
#endif
   for (i = 0 ; i < length ; ++i) {
      Real_t vhalf = 1. (1. + compHalfStep[i]) ;

#if ALLOW_ASPENIFSTMT == 1
#pragma aspen declare param(aspen_param_delvc:0.1)
#pragma aspen control probability(aspen_param_delvc)
#else
#pragma aspen control probability(1)
#endif
      if ( delvc[i] > 0. ) {
         q_new[i]  = 0. ;
         q_new[i] = qq[i] = ql[i] = 0. ;
      }
      else {
         Real_t ssc = ( pbvc[i] * e_new[i]
                 + vhalf * vhalf * bvc[i] * pHalfStep[i] ) / rho0 ;

#pragma aspen control ignore
         if ( ssc <= 0. ) {
            ssc =.333333e-36 ;
         } else {
            ssc = SQRT8(ssc) ;
         }

         q_new[i] = (ssc*ql[i] + qq[i]) ;
      }

      e_new[i] = e_new[i] + 0.5 * delvc[i]
         * (  3.0*(p_old[i]     + q_old[i])
              - 4.0*(pHalfStep[i] + q_new[i])) ;
   }

#ifdef _OPENACC
#pragma acc parallel loop present(e_new, work)
#else
#pragma omp parallel for private(i) firstprivate(length, emin, e_cut)
#endif
   for (i = 0 ; i < length ; ++i) {

      e_new[i] += 0.5 * work[i];

#if ALLOW_ASPENIFSTMT == 1
#pragma aspen declare param(aspen_param_enew:0.1)
#pragma aspen control probability(aspen_param_enew)
#else
#pragma aspen control probability(1)
#endif
      if (FABS8(e_new[i]) < e_cut) {
         e_new[i] = 0.  ;
      }
#if ALLOW_ASPENIFSTMT == 1
#pragma aspen declare param(aspen_param_enew2:0.1)
#pragma aspen control probability(aspen_param_enew2)
#else
#pragma aspen control probability(1)
#endif
      if (     e_new[i]  < emin ) {
         e_new[i] = emin ;
      }
   }

   CalcPressureForElems(p_new, bvc, pbvc, e_new, compression, vnewc,
                   pmin, p_cut, eosvmax, length);

#ifdef _OPENACC
#pragma acc parallel loop present(pHalfStep, delvc, pbvc, e_new, bvc, ql,qq, p_old, q_old, p_new, q_new, vnewc)
)
#else
#pragma omp parallel for private(i) firstprivate(length, rho0, emin, e_cut)
#endif
   for (i = 0 ; i < length ; ++i){
      const Real_t sixth = 1.0 / 6.0 ;
      Real_t q_tilde ;

#if ALLOW_ASPENIFSTMT == 1
#pragma aspen declare param(aspen_param_delvc:0.1)
#pragma aspen control probability(aspen_param_delvc)
#else
#pragma aspen control probability(1)
#endif
      if (delvc[i] > 0.) {
         q_tilde = 0. ;
      }
      else {
         Real_t ssc = ( pbvc[i] * e_new[i]
                 + vnewc[i] * vnewc[i] * bvc[i] * p_new[i] ) / rho0 ;

#pragma aspen control ignore
         if ( ssc <= 0. ) {
            ssc = .333333e-36 ;
         } else {
            ssc = SQRT8(ssc) ;
         }

         q_tilde = (ssc*ql[i] + qq[i]) ;
      }

      e_new[i] = e_new[i] - (  7.0*(p_old[i]     + q_old[i])
                               - 8.0*(pHalfStep[i] + q_new[i])
                               + (p_new[i] + q_tilde)) * delvc[i]*sixth ;

#if ALLOW_ASPENIFSTMT == 1
#pragma aspen declare param(aspen_param_enew3:0.1)
#pragma aspen control probability(aspen_param_enew3)
#else
#pragma aspen control probability(1)
#endif
      if (FABS8(e_new[i]) < e_cut) {
         e_new[i] = 0.  ;
      }
#if ALLOW_ASPENIFSTMT == 1
#pragma aspen declare param(aspen_param_enew4:0.1)
#pragma aspen control probability(aspen_param_enew4)
#else
#pragma aspen control probability(1)
#endif
      if (     e_new[i]  < emin ) {
         e_new[i] = emin ;
      }
   }

   CalcPressureForElems(p_new, bvc, pbvc, e_new, compression, vnewc,
                   pmin, p_cut, eosvmax, length);

#ifdef _OPENACC
#pragma acc parallel loop present(delvc, pbvc, e_new, vnewc, bvc, ql,qq, p_new, q_new)
)
#else
#pragma omp parallel for private(i) firstprivate(length, rho0, q_cut)
#endif
   for (i = 0 ; i < length ; ++i){

#if ALLOW_ASPENIFSTMT == 1
#pragma aspen declare param(aspen_param_delvc2:0.1)
#pragma aspen control probability(aspen_param_delvc2)
#else
#pragma aspen control probability(1)
#endif
      if ( delvc[i] <= 0. ) {
         Real_t ssc = ( pbvc[i] * e_new[i]
                 + vnewc[i] * vnewc[i] * bvc[i] * p_new[i] ) / rho0 ;

#pragma aspen control ignore
         if ( ssc <= 0. ) {
            ssc = .333333e-36 ;
         } else {
            ssc = SQRT8(ssc) ;
         }

         q_new[i] = (ssc*ql[i] + qq[i]) ;

#if ALLOW_ASPENIFSTMT == 1
#pragma aspen declare param(aspen_param_qnew:0.1)
#pragma aspen control probability(aspen_param_qnew)
#else
#pragma aspen control probability(1)
#endif
         if (FABS8(q_new[i]) < q_cut) q_new[i] = 0. ;
      }
   }

*/
}
/* end acc data */
Release(( & pHalfStep));
return ;
}

static inline void CalcEnergyForElems(double p_new[((300*300)*300)], double e_new[((300*300)*300)], double q_new[((300*300)*300)], double bvc[((300*300)*300)], double pbvc[((300*300)*300)], double p_old[((300*300)*300)], double e_old[((300*300)*300)], double q_old[((300*300)*300)], double compression[((300*300)*300)], double compHalfStep[((300*300)*300)], double vnewc[((300*300)*300)], double * work, double * delvc, double pmin, double p_cut, double e_cut, double q_cut, double emin, double * qq, double * ql, double rho0, double eosvmax, int length)
{
/* #pragma aspen declare param(aspen_param_reuse_CalcEnergyForElems_SK_noprefetch:1.8) */
/* #pragma aspen declare param(aspen_param_reuse_CalcEnergyForElems_SK_prefetch:1.8) */
int i;
#pragma aspen  declare data(pHalfStep:traits(Array(length, aspen_param_sizeof_double)))
double * pHalfStep;
pHalfStep=Allocate(length);
{
#pragma aspen  control label(block_CalcEnergyForElems16) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  control execute label(block_CalcEnergyForElems17) flops(6:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(delvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_old):traits(stride(1)), (1*aspen_param_sizeof_double):from(p_old):traits(stride(1)), (1*aspen_param_sizeof_double):from(q_old):traits(stride(1)), (1*aspen_param_sizeof_double):from(work):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]=((e_old[i]-((0.5*delvc[i])*(p_old[i]+q_old[i])))+(0.5*work[i]));
/* #pragma aspen control probability(1) */
#pragma aspen  control ignore
if (e_new[i]<emin)
{
e_new[i]=emin;
}
}
CalcPressureForElems_clnd1(pHalfStep, bvc, pbvc, e_new, compHalfStep, vnewc, pmin, p_cut, eosvmax, length);
#pragma aspen  control label(block_CalcEnergyForElems21) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
double vhalf;
#pragma aspen  control execute label(block_CalcEnergyForElems24) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(compHalfStep):traits(stride(1)))
vhalf=1.0/(1.0+compHalfStep[i]);
/* #pragma aspen control ignore */
#pragma aspen  control label(block_CalcEnergyForElems1100) probability(0) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(delvc):traits(stride(1)))
if (delvc[i]>0.0)
{
#pragma aspen  control execute stores((1*aspen_param_sizeof_double):to(q_new):traits(stride(1)))
q_new[i]=0.0;
/* q_new[i] = qq[i] = ql[i] = 0. ; */
}
else
{
#pragma aspen  control ignore
{
double ssc;
ssc=((pbvc[i]*e_new[i])+(((vhalf*vhalf)*bvc[i])*pHalfStep[i]))/rho0;
/* #pragma aspen control ignore */
if (ssc<=0.0)
{
ssc=3.33333E-37;
}
else
{
ssc=SQRT8(ssc);
}
}
/* ignore statement end */
#pragma aspen  control execute label(block_CalcEnergyForElems29) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(ql):traits(stride(1)), (1*aspen_param_sizeof_double):from(qq):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(q_new):traits(stride(1)))
q_new[i]=((ssc*ql[i])+qq[i]);
}
#pragma aspen  control execute label(block_CalcEnergyForElems30) flops(8:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(delvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(pHalfStep):traits(stride(1)), (1*aspen_param_sizeof_double):from(p_old):traits(stride(1)), (1*aspen_param_sizeof_double):from(q_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(q_old):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]=(e_new[i]+((0.5*delvc[i])*((3.0*(p_old[i]+q_old[i]))-(4.0*(pHalfStep[i]+q_new[i])))));
}
#pragma aspen  control label(block_CalcEnergyForElems31) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  control execute label(block_CalcEnergyForElems32) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(work):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]+=(0.5*work[i]);
#pragma aspen  control label(block_CalcEnergyForElems1109) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(e_new):traits(stride(1)))
if (FABS8(e_new[i])<e_cut)
{
#pragma aspen  control execute label(block_CalcEnergyForElems34) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]=0.0;
}
/* #pragma aspen control probability(1) */
#pragma aspen  control ignore
if (e_new[i]<emin)
{
e_new[i]=emin;
}
}
CalcPressureForElems_clnd2(p_new, bvc, pbvc, e_new, compression, vnewc, pmin, p_cut, eosvmax, length);
#pragma aspen  control label(block_CalcEnergyForElems38) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
const double sixth = 1.0/6.0;
double q_tilde;
/* #pragma aspen control probability(0) */
#pragma aspen  control ignore
if (delvc[i]>0.0)
{
q_tilde=0.0;
}
else
{
#pragma aspen  control ignore
{
double ssc;
ssc=((pbvc[i]*e_new[i])+(((vnewc[i]*vnewc[i])*bvc[i])*p_new[i]))/rho0;
/* #pragma aspen control ignore */
if (ssc<=0.0)
{
ssc=3.33333E-37;
}
else
{
ssc=SQRT8(ssc);
}
}
/* ignore statement end */
q_tilde=((ssc*ql[i])+qq[i]);
}
#pragma aspen  control execute label(block_CalcEnergyForElems45) flops(10:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(delvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(e_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(pHalfStep):traits(stride(1)), (1*aspen_param_sizeof_double):from(p_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(p_old):traits(stride(1)), (1*aspen_param_sizeof_double):from(q_new):traits(stride(1)), (1*aspen_param_sizeof_double):from(q_old):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]=(e_new[i]-(((((7.0*(p_old[i]+q_old[i]))-(8.0*(pHalfStep[i]+q_new[i])))+(p_new[i]+q_tilde))*delvc[i])*sixth));
#pragma aspen  control label(block_CalcEnergyForElems1143) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(e_new):traits(stride(1)))
if (FABS8(e_new[i])<e_cut)
{
#pragma aspen  control execute label(block_CalcEnergyForElems47) stores((1*aspen_param_sizeof_double):to(e_new):traits(stride(1)))
e_new[i]=0.0;
}
/* #pragma aspen control probability(1) */
#pragma aspen  control ignore
if (e_new[i]<emin)
{
e_new[i]=emin;
}
}
CalcPressureForElems_clnd3(p_new, bvc, pbvc, e_new, compression, vnewc, pmin, p_cut, eosvmax, length);
#pragma aspen  control label(block_CalcEnergyForElems51) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  control label(block_CalcEnergyForElems1168) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(delvc):traits(stride(1)))
if (delvc[i]<=0.0)
{
#pragma aspen  control ignore
{
double ssc;
ssc=((pbvc[i]*e_new[i])+(((vnewc[i]*vnewc[i])*bvc[i])*p_new[i]))/rho0;
/* #pragma aspen control ignore */
if (ssc<=0.0)
{
ssc=3.33333E-37;
}
else
{
ssc=SQRT8(ssc);
}
}
/* ignore statement end */
#pragma aspen  control execute label(block_CalcEnergyForElems55) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(ql):traits(stride(1)), (1*aspen_param_sizeof_double):from(qq):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(q_new):traits(stride(1)))
q_new[i]=((ssc*ql[i])+qq[i]);
#pragma aspen  control label(block_CalcEnergyForElems1172) probability(1) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(q_new):traits(stride(1)))
if (FABS8(q_new[i])<q_cut)
{
#pragma aspen  control execute label(block_CalcEnergyForElems57) stores((1*aspen_param_sizeof_double):to(q_new):traits(stride(1)))
q_new[i]=0.0;
}
}
}
}
/* end acc data */
Release(( & pHalfStep));
return ;
}

static inline void CalcSoundSpeedForElems(double vnewc[((300*300)*300)], double rho0, double * e_new, double * p_new, double * pbvc, double * bvc, double ss4o3, int length, int m_matElemlist[((300*300)*300)], double m_ss[((300*300)*300)])
{
int i;
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

static inline void EvalEOSForElems(double vnewc[((300*300)*300)], int length, int m_matElemlist[((300*300)*300)], double m_e[((300*300)*300)], double m_delv[((300*300)*300)], double m_p[((300*300)*300)], double m_q[((300*300)*300)], double m_qq[((300*300)*300)], double m_ql[((300*300)*300)], double p_ss[((300*300)*300)])
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
{
#pragma aspen  control label(block_EvalEOSForElems33) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  declare param(aspen_param_reuse_block_EvalEOSForElems37_SK_prefetch:1.2)
int zidx;
#pragma aspen  control execute label(block_EvalEOSForElems37) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
zidx=m_matElemlist[i];
#pragma aspen  control execute label(block_EvalEOSForElems38) loads((1*aspen_param_sizeof_double):from(m_e)) stores((1*aspen_param_sizeof_double):to(e_old):traits(stride(1)))
e_old[i]=m_e[zidx];
#pragma aspen  control execute label(block_EvalEOSForElems39) loads((1*aspen_param_sizeof_double):from(m_delv)) stores((1*aspen_param_sizeof_double):to(delvc):traits(stride(1)))
delvc[i]=m_delv[zidx];
#pragma aspen  control execute label(block_EvalEOSForElems40) loads((1*aspen_param_sizeof_double):from(m_p)) stores((1*aspen_param_sizeof_double):to(p_old):traits(stride(1)))
p_old[i]=m_p[zidx];
#pragma aspen  control execute label(block_EvalEOSForElems41) loads((1*aspen_param_sizeof_double):from(m_q)) stores((1*aspen_param_sizeof_double):to(q_old):traits(stride(1)))
q_old[i]=m_q[zidx];
/* qq_old[i] = qq[zidx] ; added by monil */
/* ql_old[i] = ql[zidx] ; added by monil */
}
#pragma aspen  control label(block_EvalEOSForElems44) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
/* Index_t ielem = regElemList[i]; added by monil */
double vchalf;
#pragma aspen  control execute label(block_EvalEOSForElems48) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(vnewc):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(compression):traits(stride(1)))
compression[i]=((1.0/vnewc[i])-1.0);
#pragma aspen  control execute label(block_EvalEOSForElems49) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(delvc):traits(stride(1)), (1*aspen_param_sizeof_double):from(vnewc):traits(stride(1)))
vchalf=(vnewc[i]-(delvc[i]*0.5));
#pragma aspen  control execute label(block_EvalEOSForElems50) flops(2:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(compHalfStep):traits(stride(1)))
compHalfStep[i]=((1.0/vchalf)-1.0);
}
/* Check for v > eosvmax or v < eosvmin  */
#pragma aspen  control label(block_EvalEOSForElems52) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  declare param(aspen_param_reuse_block_EvalEOSForElems56_SK_prefetch:1.2)
int zidx;
#pragma aspen  control execute label(block_EvalEOSForElems56) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
zidx=m_matElemlist[i];
#pragma aspen  control execute label(block_EvalEOSForElems57) loads((1*aspen_param_sizeof_double):from(m_qq)) stores((1*aspen_param_sizeof_double):to(qq):traits(stride(1)))
qq[i]=m_qq[zidx];
#pragma aspen  control execute label(block_EvalEOSForElems58) loads((1*aspen_param_sizeof_double):from(m_ql)) stores((1*aspen_param_sizeof_double):to(ql):traits(stride(1)))
ql[i]=m_ql[zidx];
#pragma aspen  control execute label(block_EvalEOSForElems59) stores((1*aspen_param_sizeof_double):to(work):traits(stride(1)))
work[i]=0.0;
#pragma aspen  control label(block_EvalEOSForElems1053) probability(0) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(vnewc):traits(stride(1)))
if ((eosvmin!=0.0)&&(vnewc[i]<=eosvmin))
{
#pragma aspen  control execute loads((1*aspen_param_sizeof_double):from(compression):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(compHalfStep):traits(stride(1)))
compHalfStep[i]=compression[i];
}
/* #pragma aspen control probability(0) */
#pragma aspen  control ignore
if ((eosvmax!=0.0)&&(vnewc[i]>=eosvmax))
{
p_old[i]=0.0;
compression[i]=0.0;
compHalfStep[i]=0.0;
}
}
}
CalcEnergyForElems(p_new, e_new, q_new, bvc, pbvc, p_old, e_old, q_old, compression, compHalfStep, vnewc, work, delvc, pmin, p_cut, e_cut, q_cut, emin, qq, ql, rho0, eosvmax, length);
#pragma aspen  control label(block_EvalEOSForElems64) loop(length) parallelism(length) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
#pragma aspen  declare param(aspen_param_reuse_block_EvalEOSForElems68_SK_prefetch:1.2)
int zidx;
#pragma aspen  control execute label(block_EvalEOSForElems68) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
zidx=m_matElemlist[i];
#pragma aspen  control execute label(block_EvalEOSForElems69) loads((1*aspen_param_sizeof_double):from(p_new):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_p))
m_p[zidx]=p_new[i];
#pragma aspen  control execute label(block_EvalEOSForElems70) loads((1*aspen_param_sizeof_double):from(e_new):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_e))
m_e[zidx]=e_new[i];
#pragma aspen  control execute label(block_EvalEOSForElems71) loads((1*aspen_param_sizeof_double):from(q_new):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(m_q))
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

static inline void ApplyMaterialPropertiesForElems(int m_matElemlist[((300*300)*300)], double m_vnew[((300*300)*300)], double m_v[((300*300)*300)], double p_e[((300*300)*300)], double p_delv[((300*300)*300)], double p_p[((300*300)*300)], double p_q[((300*300)*300)], double p_qq[((300*300)*300)], double p_ql[((300*300)*300)], double p_ss[((300*300)*300)])
{
int i;
#pragma aspen  declare param(length:m_numElem)
int length;
#pragma aspen  control ignore
length=m_numElem;
#pragma aspen  control label(block_ApplyMaterialPropertiesForElems980) probability(1) flops(1:traits(integer))
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
{
#pragma aspen  control label(block_ApplyMaterialPropertiesForElems17) loop(m_numElem) parallelism(m_numElem) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
int zn;
#pragma aspen  control execute label(block_ApplyMaterialPropertiesForElems20) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
zn=m_matElemlist[i];
/* #pragma aspen  control stores(0:from(vnewc):traits(initialized(0))) */
#pragma aspen  control execute label(block_ApplyMaterialPropertiesForElems22) loads((1*aspen_param_sizeof_double):from(m_vnew)) stores((1*aspen_param_sizeof_double):to(vnewc):traits(stride(1)))
vnewc[i]=m_vnew[zn];
/* #pragma aspen control probability(0) */
#pragma aspen  control ignore
if ((eosvmin!=0.0)&&(vnewc[i]<eosvmin))
{
vnewc[i]=eosvmin;
}
/* #pragma aspen control probability(0) */
#pragma aspen  control ignore
if ((eosvmax!=0.0)&&(vnewc[i]>eosvmax))
{
vnewc[i]=eosvmax;
}
}
#pragma aspen  control label(block_ApplyMaterialPropertiesForElems27) loop(m_numElem) parallelism(m_numElem) flops(1:traits(integer))
for (i=0; i<length;  ++ i)
{
int zn;
#pragma aspen  control execute label(block_ApplyMaterialPropertiesForElems30) loads((1*aspen_param_sizeof_int):from(m_matElemlist):traits(stride(1)))
zn=m_matElemlist[i];
#pragma aspen  control execute label(block_ApplyMaterialPropertiesForElems31) loads((1*aspen_param_sizeof_double):from(m_v))
vc=m_v[zn];
#pragma aspen  control execute label(block_ApplyMaterialPropertiesForElems1002) flops(2:traits(dp))
if (eosvmin!=0.0)
{
if (vc<eosvmin)
{
vc=eosvmin;
}
}
#pragma aspen  control execute label(block_ApplyMaterialPropertiesForElems1003) flops(2:traits(dp))
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

static inline void UpdateVolumesForElems(double m_vnew[((300*300)*300)], double m_v[((300*300)*300)])
{
int i;
int numElem;
#pragma aspen  control ignore
numElem=m_numElem;
#pragma aspen  control label(block_UpdateVolumesForElems1210) probability(1) flops(1:traits(integer))
if (numElem!=0)
{
double v_cut;
#pragma aspen  control ignore
v_cut=m_v_cut;
#pragma aspen  control label(block_UpdateVolumesForElems9) loop(m_numElem) parallelism(m_numElem) flops(1:traits(integer))
for (i=0; i<numElem;  ++ i)
{
double tmpV;
#pragma aspen  control execute label(block_UpdateVolumesForElems12) loads((1*aspen_param_sizeof_double):from(m_vnew):traits(stride(1)))
tmpV=m_vnew[i];
#pragma aspen  control label(block_UpdateVolumesForElems1216) probability(1) flops(2:traits(dp))
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

static inline void CalcCourantConstraintForElems(int p_matElemlist[((300*300)*300)], double p_ss[((300*300)*300)], double p_vdov[((300*300)*300)], double p_arealg[((300*300)*300)])
{
int i;
double dtcourant = 1.0E20;
int courant_elem;
courant_elem= - 1;
double qqc;
qqc=m_qqc;
int length;
length=m_numElem;
double qqc2;
qqc2=(64.0*qqc)*qqc;
/* [FIXME] OpenMP pragma is temporarily disabled due to a bug. */
/* #pragma omp parallel for private(i) firstprivate(length,qqc2) shared(dtcourant,courant_elem, p_matElemlist, p_ss, p_vdov, p_arealg) */
for (i=0; i<length;  ++ i)
{
int indx;
indx=p_matElemlist[i];
double dtf;
dtf=p_ss[indx]*p_ss[indx];
#pragma aspen  control probability(1)
if (p_vdov[indx]<0.0)
{
dtf=(dtf+((((qqc2*p_arealg[indx])*p_arealg[indx])*p_vdov[indx])*p_vdov[indx]));
}
dtf=SQRT8(dtf);
dtf=(p_arealg[indx]/dtf);
/* determine minimum timestep with its corresponding elem */
#pragma aspen  control execute flops(2:traits(dp)) loads((1*aspen_param_double):from(p_vdov):traits(stride(1)))
if (p_vdov[indx]!=0.0)
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
if (courant_elem!=( - 1))
{
m_dtcourant=dtcourant;
}
return ;
}

static inline void CalcHydroConstraintForElems(int p_matElemlist[((300*300)*300)], double p_vdov[((300*300)*300)])
{
int i;
double dthydro = 1.0E20;
int hydro_elem;
hydro_elem= - 1;
double dvovmax;
dvovmax=m_dvovmax;
int length;
length=m_numElem;
/* [FIXME] OpenMP pragma is temporarily disabled due to a bug. */
/* #pragma omp parallel for private(i) firstprivate(length) shared(dthydro,hydro_elem, p_matElemlist, p_vdov) */
for (i=0; i<length;  ++ i)
{
int indx;
indx=p_matElemlist[i];
#pragma aspen  control probability(1)
if (p_vdov[indx]!=0.0)
{
double dtdvov;
dtdvov=dvovmax/(FABS8(p_vdov[indx])+1.0E-20);
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
if (hydro_elem!=( - 1))
{
m_dthydro=dthydro;
}
return ;
}

static inline void CalcTimeConstraintsForElems()
{

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
/* LagrangeNodal(); */
/*
calculate element quantities (i.e. velocity gradient & q), and update
 material states
*/
/* Monil LagrangeElements(); */
LagrangeElements();
/* Monil CalcTimeConstraintsForElems(); */
/* Monil LagrangeRelease() ;  Creationdestruction of temps may be important to capture  */
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
edgeElems=300;
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
#pragma aspen  declare param(aspen_param_whilecnt:1)
/* Monil #pragma aspen declare param(aspen_param_whilecnt:23.25edgeElems+476.1) */
acc_init(acc_device_default);
#pragma aspen  modelregion label(block_main135)
#pragma aspen  control label(block_main135) intracomm((aspen_param_sizeof_double*m_numElem):to(m_e):traits(copy), (aspen_param_sizeof_double*m_numElem):to(m_elemMass):traits(copyin), (aspen_param_sizeof_double*m_numElem):to(m_p):traits(copy), (aspen_param_sizeof_double*m_numElem):to(m_v):traits(copyin), (aspen_param_sizeof_double*m_numElem):to(m_volo):traits(copyin), (aspen_param_sizeof_double*m_numNode):to(m_nodalMass):traits(copyin), (aspen_param_sizeof_double*m_numNode):to(m_x):traits(copy), (aspen_param_sizeof_double*m_numNode):to(m_xd):traits(copy), (aspen_param_sizeof_double*m_numNode):to(m_xdd):traits(copyin), (aspen_param_sizeof_double*m_numNode):to(m_y):traits(copy), (aspen_param_sizeof_double*m_numNode):to(m_yd):traits(copy), (aspen_param_sizeof_double*m_numNode):to(m_ydd):traits(copyin), (aspen_param_sizeof_double*m_numNode):to(m_z):traits(copy), (aspen_param_sizeof_double*m_numNode):to(m_zd):traits(copy), (aspen_param_sizeof_double*m_numNode):to(m_zdd):traits(copyin), (aspen_param_sizeof_int*(edgeNodes*edgeNodes)):to(m_symmX):traits(copyin), (aspen_param_sizeof_int*(edgeNodes*edgeNodes)):to(m_symmY):traits(copyin), (aspen_param_sizeof_int*(edgeNodes*edgeNodes)):to(m_symmZ):traits(copyin), (aspen_param_sizeof_int*m_nCorner):to(m_nodeElemCornerList):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_elemBC):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_letam):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_letap):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_lxim):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_lxip):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_lzetam):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_lzetap):traits(copyin), (aspen_param_sizeof_int*m_numElem):to(m_matElemlist):traits(copyin), (aspen_param_sizeof_int*m_numElem8):to(m_nodelist):traits(copyin), (aspen_param_sizeof_int*m_numNode):to(m_nodeElemCount):traits(copyin), (aspen_param_sizeof_int*m_numNode):to(m_nodeElemStart):traits(copyin))
{
#pragma aspen  control label(block_main447) loop(aspen_param_whilecnt) flops(1:traits(dp))
while (m_time<m_stoptime)
{
/* Monil TimeIncrement() ; */
LagrangeLeapFrog();
#pragma aspen  control execute label(block_main139) flops(1:traits(integer))
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

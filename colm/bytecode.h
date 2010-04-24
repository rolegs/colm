/*
 *  Copyright 2007-2010 Adrian Thurston <thurston@complang.org>
 */

/*  This file is part of Colm.
 *
 *  Colm is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  Colm is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with Colm; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

#ifndef _BYTECODE_H
#define _BYTECODE_H

#include "rtvector.h"
#include "config.h"
#include "pool.h"
#include "pdarun.h"
#include "map.h"

#include <iostream>

using std::cerr;
using std::endl;
using std::ostream;

#include "bytecode2.h"

typedef struct _Kid Kid;
typedef struct _Tree Tree;
typedef struct _ParseTree ParseTree;
typedef struct _ListEl ListEl;
typedef struct _MapEl MapEl;
typedef struct _List List;
typedef struct _Map Map;
typedef struct _Ref Ref;
typedef struct _Pointer Pointer;
typedef struct _Str Str;
typedef struct _Int Int;
typedef struct _PdaRun PdaRun;


struct TreePair
{
	TreePair() : key(0), val(0) {}

	Tree *key;
	Tree *val;
};


void rcodeDownref( Program *prg, Tree **sp, Code *instr );



#include "tree.h"


void printTree( ostream &out, Tree **&sp, Program *prg, Tree *tree );
void printXmlTree( Tree **&sp, Program *prg, Tree *tree, bool commAttr );
void printXmlKid( Tree **&sp, Program *prg, Kid *kid, bool commAttr, int depth );

void listAppend( Program *prg, List *list, Tree *val );
Tree *listRemoveEnd( Program *prg, List *list );
Tree *getListMem( List *list, Word field );
Tree *getListMemSplit( Program *prg, List *list, Word field );
Tree *setListMem( List *list, Half field, Tree *value );

Tree *mapFind( Program *prg, Map *map, Tree *key );
long mapLength( Map *map );
int mapInsert( Program *prg, Map *map, Tree *key, Tree *element );
void mapUnremove( Program *prg, Map *map, Tree *key, Tree *element );
Tree *mapUninsert( Program *prg, Map *map, Tree *key );
Tree *mapStore( Program *prg, Map *map, Tree *key, Tree *element );
Tree *mapUnstore( Program *prg, Map *map, Tree *key, Tree *existing );
TreePair mapRemove( Program *prg, Map *map, Tree *key );


Tree *treeIterAdvance( Program *prg, Tree **&sp, TreeIter *iter );
Tree *treeIterNextChild( Program *prg, Tree **&sp, TreeIter *iter );
Tree *treeRevIterPrevChild( Program *prg, Tree **&sp, RevTreeIter *iter );
Tree *treeIterNextRepeat( Program *prg, Tree **&sp, TreeIter *iter );
Tree *treeIterPrevRepeat( Program *prg, Tree **&sp, TreeIter *iter );

void splitIterCur( Tree **&sp, Program *prg, TreeIter *iter );
Tree **stackAlloc();

/*
 * Runtime environment
 */

void initProgram( Program *program, int argc, char **argv,
		bool ctxDepParsing, RuntimeData *rtd );
void clearProgram( Program *prg, Tree **vm_stack, Tree **sp );
void runProgram( Program *prg );
void allocGlobal( Program *prg );

void executeCode( Execution *exec, Tree **sp, Code *instr );
void splitRef( Tree **&sp, Program *prg, Ref *fromRef );

#endif

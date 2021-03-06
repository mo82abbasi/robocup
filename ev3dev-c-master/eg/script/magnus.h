#ifndef _MAGNUS_H_
#define _MAGNUS_H_

#include <stdbool.h>
#include <stdint.h>


typedef enum
{
    B_AND = 0,
    B_OR,
    B_XOR,
	NUM_BOOLEANOPERATOR
} EBooleanOperator;

typedef enum
{
	V_NIL = 0,
	V_SPEED,
	V_ODOMETER,
	V_ANGLE,
	V_TIME,
	V_HEADING,	// heading in degrees relative to north
	V_XPOS,		// X position as eastward value relative to starting point
	V_YPOS,		// Y position as eastward value relative to starting point
	NUM_VARS
} EVar;

typedef enum
{
	K_UNTIL = 0,
	K_CONST,
	K_END,
	NUM_KEYWORDS
} EKeyword;

typedef enum
{
    A_BACKWARD = 0,
    A_FOLLOW,
    A_FOLLOWLEFT,
    A_FOLLOWRIGHT,
    A_FORWARD,
    A_SET,
    A_TURNLEFT,
    A_TURNRIGHT,
    A_WAIT,
	NUM_ACTIONS
} EAction;

typedef enum
{
	C_BRANCHLEFT = 0,
	C_BRANCHRIGHT,
	C_JUNCTIONLEFT,
	C_JUNCTIONRIGHT,
	C_LINE,
	NUM_COND
} ECond;

typedef enum
{
	O_EQUAL = 0,
	O_NOT_EQUAL,
	O_GREATER_EQUAL,
	O_GREATER,
	O_LESS_EQUAL,
	O_LESS,
	NUM_OP
} EOp;

typedef enum
{
	S_ACTION = 0,
	S_KEYVALUE0,
	S_KEYVALUE1,
	S_UNTIL,
	S_CONDITIONA,
	S_COMPARISONA,
	S_KEYVALUE2,
	S_KEYVALUE3,
	S_BOOLEAN,
	S_CONDITIONB,
	S_COMPARISONB,
	S_KEYVALUE4,
	S_KEYVALUE5,
	S_RIGHTB,
	S_END
} ESyntax;

typedef struct
{
	int index;
} SState;

typedef struct _SSequence
{
	EAction eAction;
    bool (*pAction)(SState* s, int noun0, float value0, int noun1, float value1); 
    EVar noun0; 
	float value0; 
	EVar noun1; 
	float value1;
    
	ECond eConditionA;
    bool (*pConditionA)(SState* s, int noun0, float value0, int noun1, float value1); 
    EVar left_noun0; 
	float left_value0; 
	EOp eOpA;
	EVar left_noun1; 
	float left_value1;
    
    EBooleanOperator eBooleanOperator;
    
	ECond eConditionB;
    bool (*pConditionB)(SState* s, int noun0, float value0, int noun1, float value1); 
    EVar right_noun0; 
	float right_value0; 
	EOp eOpB;
	EVar right_noun1; 
	float right_value1;
    
    struct _SSequence* pNext;
} SSequence;

void SequenceInit(SSequence* pSequence);

ECond MatchCondition(const char* token);
EOp MatchOperator(const char* token);
EBooleanOperator MatchBooleanOperator(const char* token);
EAction MatchAction(const char* token);
EVar MatchVar(const char* token);

typedef struct 
{
	const char* name;
    float value; 
} SVarItem;


void SetVar(EVar eVar, float value);
float GetVar(EVar eVar);


SVarItem* GetVars(EVar eVar);

// Condition functions

bool BranchLeft(SState* s, int noun0, float value0, int noun1, float value1);
bool BranchRight(SState* s, int noun0, float value0, int noun1, float value1);
bool JunctionLeft(SState* s, int noun0, float value0, int noun1, float value1);
bool JunctionRight(SState* s, int noun0, float value0, int noun1, float value1);
bool Line(SState* s, int noun0, float value0, int noun1, float value1);
bool Equal(SState* s, int noun0, float value0, int noun1, float value1);
bool NotEqual(SState* s, int noun0, float value0, int noun1, float value1);
bool Greater(SState* s, int noun0, float value0, int noun1, float value1);
bool GreaterEqual(SState* s, int noun0, float value0, int noun1, float value1);
bool Less(SState* s, int noun0, float value0, int noun1, float value1);
bool LessEqual(SState* s, int noun0, float value0, int noun1, float value1);


// Action functions

bool Backward(SState* s, int noun0, float value0, int noun1, float value1);
bool Follow(SState* s, int noun0, float value0, int noun1, float value1);
bool FollowLeft(SState* s, int noun0, float value0, int noun1, float value1);
bool FollowRight(SState* s, int noun0, float value0, int noun1, float value1);
bool Forward(SState* s, int noun0, float value0, int noun1, float value1);
bool Set(SState* s, int noun0, float value0, int noun1, float value1);
bool TurnLeft(SState* s, int noun0, float value0, int noun1, float value1);
bool TurnRight(SState* s, int noun0, float value0, int noun1, float value1);
bool Wait(SState* s, int noun0, float value0, int noun1, float value1);


typedef struct
{
	SSequence* pFirst;
	SSequence* pLast;
} SProgram;

bool Compile(char* in, SProgram* pProgram);
void RunProgram(SProgram* pProgram);
void PrintProgram(SProgram* pProgram);
void DeleteProgram(SProgram* pProgram);


void UpdateVars(float delta);
void AssignVar(int noun, float value);

#endif


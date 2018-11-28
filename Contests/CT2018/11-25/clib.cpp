#include <bits/stdc++.h>
using namespace std;

int MAX_CYCLES = 10000000;

string Code;
long long Memory[2097152];
vector<int> CallStack;
vector<long long> OperandStack;
int ProgramCounter = 0;
int CycleCounter = 0;

void Push(long long v) {
	if (v < LLONG_MIN || v > LLONG_MAX)
		throw string("integer overflow");
	OperandStack.push_back(v);
}

long long Pop() {
	if (OperandStack.empty())
		throw string("stack underflow");
	long long x = OperandStack.back();
	OperandStack.pop_back();
	return x;
}

void DoPush(long long v) {
	Push(v - '0');
}

void DoReadChar(long long v) {
	Push(getchar());
}

void DoReadInt(long long v) {
	long long x;
	scanf("%lld", &x);
	Push(x);
}

void DoPrintChar(long long v) {
	putchar(Pop());
}

void DoPrintInt(long long v) {
	printf("%lld", Pop());
}

void DoAdd(long long v) {
	Push(Pop() + Pop());
}

void DoSub(long long v) {
	long long a = Pop();
	long long b = Pop();
	Push(b - a);
}

void DoMul(long long v) {
	Push(Pop() * Pop());
}

void DoDiv(long long v) {
	long long a = Pop();
	long long b = Pop();
	if (a == 0)
		throw string("divided by zero");
	Push(b / a);
}

void DoCmp(long long v) {
	long long a = Pop();
	long long b = Pop();
	Push(b > a ? 1 : b == a ? 0 : -1);
}

void DoGoto(long long v) {
	ProgramCounter += Pop();
}

void DoGotoIfZero(long long v) {
	long long offset = Pop();
	if (Pop() == 0) 
		ProgramCounter += offset;
}

void DoCall(long long v) {
	CallStack.push_back(ProgramCounter);
	ProgramCounter = Pop();
}

void DoReturn(long long v) {
	if (CallStack.empty())
		throw string("call stack underflow");
	ProgramCounter = CallStack.back();
	CallStack.pop_back();
}

void DoPeek(long long v) {
	long long addr = Pop();
	if (addr < 0 || addr >= 2097152)
		throw string("memory read access violation");
	Push(Memory[(int)addr]);
}

void DoPoke(long long v) {
	long long addr = Pop();
	if (addr < 0 || addr >= 2097152)
		throw string("memory write access violation");
	Memory[(int)addr] = Pop();
}

void DoPick(long long v) {
	long long where = Pop();
	if (where < 0 || where >= (int)OperandStack.size())
		throw string("out of stack bounds");
	Push(OperandStack[OperandStack.size() - 1 - where]);
}

void DoRoll(long long v) {
	long long where = Pop();
	if (where < 0 || where >= (int)OperandStack.size())
		throw string("out of stack");
	v = OperandStack[OperandStack.size() - 1 - where];
	OperandStack.erase(OperandStack.begin() + OperandStack.size() - 1 - where);
	Push(v);
}

void DoDrop(long long v) {
	Pop();
}

void DoEnd(long long v) {
	ProgramCounter = Code.size();
}

void DoNothing(long long v) {
}

map<char, void (*)(long long)> OPS;

void insert_ops(char key, void (*value)(long long)) {
	OPS[key] = value;
}

int main() {
	insert_ops(' ', DoNothing);
	insert_ops('\n',DoNothing);
	insert_ops('p', DoPrintInt);
	insert_ops('P', DoPrintChar);
	insert_ops('r', DoReadInt);
	insert_ops('R', DoReadChar);
	insert_ops('0', DoPush);
	insert_ops('1', DoPush);
	insert_ops('2', DoPush);
	insert_ops('3', DoPush);
	insert_ops('4', DoPush);
	insert_ops('5', DoPush);
	insert_ops('6', DoPush);
	insert_ops('7', DoPush);
	insert_ops('8', DoPush);
	insert_ops('9', DoPush);
	insert_ops('+', DoAdd);
	insert_ops('-', DoSub);
	insert_ops('*', DoMul);
	insert_ops('/', DoDiv);
	insert_ops(':', DoCmp);
	insert_ops('g', DoGoto);
	insert_ops('?', DoGotoIfZero);
	insert_ops('c', DoCall);
	insert_ops('$', DoReturn);
	insert_ops('<', DoPeek);
	insert_ops('>', DoPoke);
	insert_ops('^', DoPick);
	insert_ops('v', DoRoll);
	insert_ops('d', DoDrop);
	insert_ops('!', DoEnd);

    freopen("6", "r", stdin);

	cout << "code:";
	cin >> Code;
	cout << "now please interactive with your program:" << endl;
	char op_code;
	try {
		while (ProgramCounter != (int)Code.size()) {
			op_code = Code[ProgramCounter];

			ProgramCounter++;
			CycleCounter++;
			if (CycleCounter > MAX_CYCLES)
				throw string("too many cycles");
			if (OPS.count(op_code) == 0) 
				throw string("invalid instruction");
			OPS[op_code](op_code);
			if (ProgramCounter < 0 || ProgramCounter > (int)Code.size())
				throw string("out of code bounds");
		}
	} catch (string x) {
		cerr << "!ERROR: exception while executing I=" << op_code
				<< " PC=" << ProgramCounter - 1
				<< " STACK_SIZE=" << OperandStack.size() << endl;
		cerr << x << endl;
		return 1;
	}
    cerr << endl;
    cerr << CycleCounter << endl;
	return 0;
}

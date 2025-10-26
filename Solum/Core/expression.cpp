#include "pch.h"
#include "expression.h"
using namespace std;
using namespace solum;

// Expression Classes Implementation
Expr::Expr(ExprType exprType)
	: SolumObj("Expr"), exprType(move(exprType)) {
}
solum::Expr::~Expr() {
}
ExprType Expr::getExprType() const {
	return exprType;
}
string Expr::asStyledString() const {
	return "Expr.Null";
}

// CstExpr Implementation
CstExpr::CstExpr(Value value)
	: Expr(ExprType::CST), value(move(value)) {
}
CstExpr::~CstExpr() {
}
Value CstExpr::getValue() const {
	return value;
}
string CstExpr::asStyledString() const {
	return "Expr.Cst(value = " + value.asStyledString() + ")";
}

// VarExpr Implementation
VarExpr::VarExpr(Value id)
	: Expr(ExprType::VAR), id(move(id)) {
}
VarExpr::~VarExpr() {
}
Value VarExpr::getId() const {
	return id;
}
string VarExpr::asStyledString() const {
	return "Expr.Var(id = " + id.asStyledString() + ")";
}

// AssignExpr Implementation
AssignExpr::AssignExpr(unique_ptr<Expr> lhs, unique_ptr<Expr> rhs) 
	: Expr(ExprType::OPR_ASSIGN), lhs(move(lhs)), rhs(move(rhs)) {
	if (this->lhs == nullptr || this->rhs == nullptr) {
		throw invalid_argument("AssignExpr constructor received null pointer");
	}
}
AssignExpr::~AssignExpr() {
}
const Expr& AssignExpr::getLhs() const {
	return *lhs;
}
const Expr& AssignExpr::getRhs() const {
	return *rhs;
}
string AssignExpr::asStyledString() const {
	return "Expr.Assign(lhs = " + lhs->asStyledString() + ", rhs = " + rhs->asStyledString() + ")";
}

// FDefExpr Implementation
FDefExpr::FDefExpr(vector<unique_ptr<VarExpr>> params, vector<unique_ptr<Expr>> body)
	: Expr(ExprType::OPR_FDEF), params(move(params)), body(move(body)) {
	if (body.empty()) {
		throw invalid_argument("FDefExpr constructor received empty body");
	}
}
FDefExpr::~FDefExpr() {
}
vector<VarExpr*> FDefExpr::getParams() const {
	vector<VarExpr*> paramPtrs;
	for (const auto& param : params) {
		paramPtrs.push_back(param.get());
	}
	return paramPtrs;
}
vector<Expr*> FDefExpr::getBody() const {
	vector<Expr*> bodyPtrs;
	for (const auto& expr : body) {
		bodyPtrs.push_back(expr.get());
	}
	return bodyPtrs;
}
string FDefExpr::asStyledString() const {
	string paramsStr = "[";
	for (size_t i = 0; i < params.size(); ++i) {
		paramsStr += params[i]->asStyledString();
		if (i < params.size() - 1) {
			paramsStr += ", ";
		}
	}
	paramsStr += "]";
	string bodyStr = "[";
	for (size_t i = 0; i < body.size(); ++i) {
		bodyStr += body[i]->asStyledString();
		if (i < body.size() - 1) {
			bodyStr += ", ";
		}
	}
	bodyStr += "]";
	return "Expr.FDef(params = " + paramsStr + ", body = " + bodyStr + ")";
}

// FCallExpr Implementation
FCallExpr::FCallExpr(unique_ptr<Expr> func, vector<unique_ptr<Expr>> args) 
	: Expr(ExprType::OPR_FCALL), func(move(func)), args(move(args)) {
	if (this->func == nullptr) {
		throw invalid_argument("FCallExpr constructor received null pointer for func");
	}
}
FCallExpr::~FCallExpr() {
}
const Expr& FCallExpr::getFunc() const {
	return *func;
}
vector<Expr*> FCallExpr::getArgs() const {
	vector<Expr*> argPtrs;
	for (const auto& arg : args) {
		argPtrs.push_back(arg.get());
	}
	return argPtrs;
}
string FCallExpr::asStyledString() const {
	string argsStr = "[";
	for (size_t i = 0; i < args.size(); ++i) {
		argsStr += args[i]->asStyledString();
		if (i < args.size() - 1) {
			argsStr += ", ";
		}
	}
	argsStr += "]";
	return "Expr.FCall(func = " + func->asStyledString() + ", args = " + argsStr + ")";
}

// JmpExpr Implementation
JmpExpr::JmpExpr(unique_ptr<Expr> target)
	: Expr(ExprType::OPR_JMP), target(move(target)) {
	if (this->target == nullptr) {
		throw invalid_argument("JmpExpr constructor received null pointer for target");
	}
}
JmpExpr::~JmpExpr() {
}
const Expr& JmpExpr::getTarget() const {
	return *target;
}
string JmpExpr::asStyledString() const {
	return "Expr.Jmp(target = " + target->asStyledString() + ")";
}

// CJmpExpr Implementation
CJmpExpr::CJmpExpr(unique_ptr<Expr> condition, unique_ptr<Expr> target) 
	: Expr(ExprType::OPR_CJMP), condition(move(condition)), target(move(target)) {
	if (this->condition == nullptr || this->target == nullptr) {
		throw invalid_argument("CJmpExpr constructor received null pointer");
	}
}
CJmpExpr::~CJmpExpr() {
}
const Expr& CJmpExpr::getCondition() const {
	return *condition;
}
const Expr& CJmpExpr::getTarget() const {
	return *target;
}
string CJmpExpr::asStyledString() const {
	return "Expr.CJmp(condition = " + condition->asStyledString() + ", target = " + target->asStyledString() + ")";
}

// IdxExpr Implementation
IdxExpr::IdxExpr(unique_ptr<Expr> base, unique_ptr<Expr> index)
	: Expr(ExprType::OPR_IDX), base(move(base)), index(move(index)) {
	if (this->base == nullptr || this->index == nullptr) {
		throw invalid_argument("IdxExpr constructor received null pointer");
	}
}
IdxExpr::~IdxExpr() {
}
const Expr& IdxExpr::getBase() const {
	return *base;
}
const Expr& IdxExpr::getIndex() const {
	return *index;
}
string IdxExpr::asStyledString() const {
	return "Expr.Idx(base = " + base->asStyledString() + ", index = " + index->asStyledString() + ")";
}
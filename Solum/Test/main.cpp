#include <iostream>
#include <value.h>
#include <expression.h>
using namespace std;
using namespace solum;

int main() {
	
	cout << "Notice: This is the test environment for Solum." << endl;

	unique_ptr<Expr> expr1 = make_unique<CstExpr>(Value((string)"101010"));
	unique_ptr<Expr> expr2 = make_unique<VarExpr>(Value((string)"var1"));
	unique_ptr<Expr> expr3 = make_unique<AssignExpr>(
		make_unique<VarExpr>(Value((string)"var2")),
		make_unique<CstExpr>(Value((string)"111000"))
	);

	vector<unique_ptr<VarExpr>> params;
	params.emplace_back(make_unique<VarExpr>(Value((string)"param1")));
	params.emplace_back(make_unique<VarExpr>(Value((string)"param2")));

	vector<unique_ptr<Expr>> body;
	body.push_back(move(expr1));
	body.push_back(move(expr2));
	body.push_back(move(expr3));

	unique_ptr<Expr> expr4 = make_unique<FDefExpr>(
		move(params),
		move(body)
	);

	vector<unique_ptr<Expr>> call_args;
	call_args.emplace_back(make_unique<CstExpr>(Value((string)"000111")));
	call_args.emplace_back(make_unique<CstExpr>(Value((string)"001100")));

	unique_ptr<Expr> expr5 = make_unique<FCallExpr>(
		move(expr4),
		move(call_args)
	);
	unique_ptr<Expr> expr6 = move(expr5);

	cout << expr6->asStyledString() << endl;
	
	return 0;
}
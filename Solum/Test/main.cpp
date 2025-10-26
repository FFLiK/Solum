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
	unique_ptr<Expr> expr4 = make_unique<FDefExpr>(
		vector<unique_ptr<VarExpr>> { 
			make_unique<VarExpr>(Value((string)"param1")), 
			make_unique<VarExpr>(Value((string)"param2")) 
		},
		vector<unique_ptr<Expr>>{ 
			move(expr1), 
			move(expr2), 
			move(expr3) 
		}
	);
	unique_ptr<Expr> expr5 = make_unique<FCallExpr>(
		move(expr4),
		vector<unique_ptr<Expr>>{ 
			make_unique<CstExpr>(Value((string)"000111")), 
			make_unique<CstExpr>(Value((string)"001100")) 
		}
	);
	unique_ptr<Expr> expr6 = move(expr5);

	cout << expr6->asStyledString() << endl;
	return 0;
}
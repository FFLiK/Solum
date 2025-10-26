> Solum은 새로운 언어에 대한 제작 틀이다. Solum은 아래 이념에 따라 개발된다.

- Value는 숫자 형태이며, 그 크기는 무한히 확장된다.
- Value는 Number 혹은 Function으로 작용할 수 있다.
- 변수는 Mutable 하며, 모든 변수는 크기가 무한한 무한 차원 Array이다.
- 모든 변수는 이미 선언되어있다.

Solum은 Solang이라는 이름의 Concrete Syntanx와 이를 AST로 바꾸는 Paser가 존재한다.
Solum을 기반으로 하는 언어는 Custom Syntax를 Solang으로 바꾸는 Translator가 필요하다.

---
## Solang

Solum의 Concrete Syntanx
### Symbols
#### 1. Constants
> 모든 상수는 `0`과 `1`으로 구성된 문자열로 표기된다.
#### 2. Variables
> Variable은 `V`와 `v`로 구성된 문자열로 표기한다.
#### 3. Operators
- **Value Assignment** : `=`
- **Function Definition** : `:`
- **End of Function Definition** : `;`
- **Function Call** : `!`
- **Goto** : `>`
- **Import** : `+`

### BNF of Solang

```
<cst> = 0 | 1 | 0 <cst> | 1 <cst>
<var> = v | V | v <var> | V <var>
<expr> = <cst> | <var> | <var> = <expr> |
		 : <var> ... <expr> ... ; | <expr> ! <expr> , <expr> , ... |
		 > <expr> | <expr> > <expr> | <expr> <expr>
<code> = <expr>. <expr>. ...
```

기본적으로 Nesting 된 구조는 Recursive하게 처리한다.
### Semantics

#### 0. Identies
$$
c \Rightarrow c \quad v \Rightarrow M(v)[0]\\
$$
#### 1. Value Assignment

```
<var> = <expr>
```

$$
\frac{e \Rightarrow c \quad M(v) := c}{v = e \Rightarrow c}
$$
#### 2. Function Definition

```
: <var> ... 
<expr> ...
;
```

$$
\frac{c \notin F \quad F(c):=(v_1, v_2,\dots v_n, e)}{: v_1\;v_2\;\dots\;v_n \; e \Rightarrow c}
$$

#### 3. Function Call

```
<expr> ! <expr> ! <expr> . <expr> .
```

$$
\frac{
\begin{array}{c}
e \Rightarrow c \quad F(c) \Rightarrow (v_1,v_2,\dots,v_n,e_f)\quad\\
e_1 \Rightarrow c_1 \quad \dots \quad e_n \Rightarrow c_n \quad
M_f(v_1)[0] := c_1 \quad \dots \quad M_f(v_n)[0] := c_n\\
e_f \Rightarrow c_f\\
M(v_1)[0] := M_f(v_1)[0] \quad \dots \quad M(v_n)[0] := M(v_f)[0]
\end{array}
}{e\;!\;e_1.e_2.\dots.e_n \Rightarrow c_f}
$$
#### 4. Goto Statement

```
> <expr>
<expr> > <expr>
```

어떤 expression 처리 중 goto statement가 나오면 해당 expression의 stack은 초기화된다.

#### 5. Indexing Statement

```
<expr> <expr>
```

$$
\frac{e_1 \Rightarrow c}{e_1\;e_2 \Rightarrow c} \quad
\frac{e_1 \Rightarrow v \quad e_2 \Rightarrow c}{e_1\;e_2 \Rightarrow M(v)[c]}
$$
#### 6. Import Statement

```
+ <String>
```

완전히 독립된 Statement이다. 해당 파일에 정의된 함수를 가져온다.
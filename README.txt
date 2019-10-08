자료구조의 기초 Project 2
전기정보공학부 2016-18829 이성민

본 과제에서는 memory array tree와 symbol table 출력 부분은 없애고, evaluation 값만을 출력하도록 하였습니다.
더불어, 예외적인 error case를 가진 input(정의되지 않은 symbol, unbalanced parenthesis 등)은 대부분 주어지지 않는다고 가정하며, pseudocode에 명시된 error case만을 고려하였습니다.
memArray에 있는 node들은 필요가 없더라도 free시키지 않았고, 따라서 가득차 예상과는 다른 행동을 보일 수 있으므로 모든 node가 allocate 되었을 때에는 메시지를 출력하고 프로그램을 종료하도록 하였습니다. (exit(0) 사용)
memArraySize는 명시되지 않아, 충분히 크다고 생각된 값인 1000으로 고정하였습니다.

컴파일의 경우,
g++ *.cpp 의 방식으로 컴파일을 하면 a.out 파일이 만들어지며,
./a.out 으로 실행시키는 일반적인 형식을 따라감으로써 컴파일 및 실행을 할 수 있습니다.
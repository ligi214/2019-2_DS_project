자료구조의 기초 Project 3
전기정보공학부 2016-18829 이성민

본 과제에서는 기존 과제에서와 마찬가지로 명령어를 받고 그를 parse tree로 만들지만, memory 공간을 모두 사용할 시 garbage collection을 진행하여 사용하지 않는 공간을 free시킨 뒤 다시 명령어를 수행하도록 하였습니다.
Garbage collection을 할 때, 사용하고 있는 메모리 공간의 flag를 1로 표시함으로써 free시키면 안 됨을 가리켰고, 채점을 위해 memArray 출력 시 해당 flag의 값도 같이 출력되도록 하였습니다.
출력되는 값으로는 evaluation, memArray 구조, hashtable 구조가 있습니다.

더불어, 예외적인 error case를 가진 input(정의되지 않은 symbol, unbalanced parenthesis 등)은 대부분 주어지지 않는다고 가정하였습니다.
특히, garbage collection을 진행하였음에도 불구하고 공간이 부족한 상황은 없다고 가정하였으며, 해당 상황이 발생하였을 경우 garbage collection을 해도 여유 공간이 부족하다는 메시지를 보여주고 종료하도록 하였습니다. (exit(0) 사용)
memArraySize는 예시 입/출력 코드와 마찬가지로 30으로 고정하였으며, hash value는 각 자릿수를 제곱하여 합한 것을 1031로 나눈 나머지로 하였습니다. 이 때, hash table size는 1031로 두었습니다.

컴파일의 경우,
g++ *.cpp 의 방식으로 컴파일을 하면 a.out 파일이 만들어지며,
./a.out 으로 실행시키는 일반적인 형식을 따라감으로써 컴파일 및 실행을 할 수 있습니다.
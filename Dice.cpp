// Dice.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <random>
#include <iostream>

using namespace std;



void rollTheDice(int arr[], int n) {

    int result = 0;
    int nDices = n; 
    int nThrows;
    int nSides;
    int addition;

    for (int i = 0; i < nDices; i++) {

        nThrows = arr[i * 3];
        nSides = arr[i * 3 + 1];
        addition = arr[i * 3 + 2];

        for (int j = 0; j < nThrows; j++) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(1, nSides);

            result += distrib(gen);
            
        }
        result += addition;
    }
    cout << result << endl;
}

int main()
{
    // the function takes an array and a number of dices as arguments. Array elements: number of throws, number of sides, integer to sum (0, if no), and again from the start
    // can take any number of dices, the only thing is to write array elements in the right order

    int Dices[6] = { 1,6,0,2,7,2 };
    rollTheDice(Dices, 2);

    //int Dice[3] = { 3,10,0 };
    //for (int rolls = 0; rolls < 1000; rolls++) {
    //    rollTheDice(Dice, 1);
    //}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

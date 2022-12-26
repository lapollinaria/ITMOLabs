// Hammurabi.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <limits>
#include <ctime>
#include <stdlib.h> // rand(), srand()
#include <stdio.h> // printf()
#include <fstream> // files

using namespace std;


constexpr int whEatenByEachCitizen = 20;
constexpr double seedForAcre = 0.5;
constexpr int workCapacity = 10;

constexpr int default_wheat = 2800;;
constexpr int default_acres = 1000;
constexpr int default_citizens = 100;
constexpr int default_year = 1;
constexpr int default_rounds = 10;

struct Game {
    int wheat;
    int acres;
    int citizens;
    int year;

    int died_of_hunger;
    int newly_arrived;
    int wh_by_acre;
    int wh_destroyed_rats;
    int died_of_plague;
    int acre_price;
    int collected_wheat;
    bool end_game_hunger;

    double P;
};
double P_list[10];
double L_list[10];



int validateInteger()
{
    int input;
    begin:
    cin >> input;
    
    while (!cin.good())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Число должно быть целым, попробуй ещё раз" << endl;
        cin >> input;
    }
    if (input >= 0)
        return input;
    else {
        cout << "Число должно быть целым и неотрицательным, попробуй ещё раз" << endl;
        goto begin;
    }
}

void printReport(Game game)
{
    cout << "Мой повелитель, соизволь поведать тебе" << endl;
    cout << "В году " << game.year << " твоего высочайшего правления" << endl;
    cout << game.died_of_hunger << " человек умерли с голоду;" << endl;
    cout << game.newly_arrived << " человек прибыли в наш великий город;" << endl;
    if (game.died_of_plague > 0)
        cout << "Чума уничтожила половину населения;" << endl;
    cout << "Население города сейчас составляет " << game.citizens << " человек;" << endl;
    cout << "Мы собрали " << game.collected_wheat << " бушелей пшеницы, по " << game.wh_by_acre << " бушелей с акра;" << endl;
    cout << "Крысы истребили " << game.wh_destroyed_rats << " бушелей пшеницы, оставив " << game.wheat << " бушелей в амбарах;" << endl;
    cout << "Город сейчас занимает " << game.acres << " акров;" << endl;
    cout << "1 акр земли стоит сейчас " << game.acre_price << " бушелей" << endl;
}

void Outfile(Game game) {
    //Game game;
    ofstream progress;
    progress.open("autosave.txt");
    progress << game.wheat << "\n";
    progress << game.acres << "\n";
    progress << game.citizens << "\n";
    progress << game.year << "\n";

    progress << game.died_of_hunger << "\n";
    progress << game.newly_arrived << "\n";
    progress << game.wh_by_acre << "\n";
    progress << game.wh_destroyed_rats << "\n";
    progress << game.died_of_plague << "\n";
    progress << game.acre_price << "\n";
    progress << game.collected_wheat << "\n";
    progress << game.end_game_hunger << "\n";

    progress << game.P << "\n";

    progress.close();
}

void Restore(Game game) {
    //Game game;
    ifstream progress;
    progress.open("autosave.txt");
    if (progress.is_open())
    {
        while (!progress.eof())
        {
            progress >> game.wheat;
            progress >> game.acres;
            progress >> game.citizens;
            progress >> game.year;

            progress >> game.died_of_hunger;
            progress >> game.newly_arrived;
            progress >> game.wh_by_acre;
            progress >> game.wh_destroyed_rats;
            progress >> game.died_of_plague;
            progress >> game.acre_price;
            progress >> game.collected_wheat;
            progress >> game.end_game_hunger;

            progress >> game.P;

           
        }
        progress.close();
    }
    else cout << "Unable to open file";
}

void EndGameEarly() {
 
    cout << "Слишком много жителей умерли в этом году, игра будет закончена сейчас" << endl;
    exit(0);
    
}

void UserExit(Game game) {
    int yn;
    cout << "Желаете продолжить игру? (1 - да/0 - нет)" << endl;
    begin:
    cin >> yn;
    if (yn == 0) {
        Outfile(game);
        exit(0);
    }
    else if (yn == 1)
        return;
    else {
        cout << "(1 - да/0 - нет)" << endl;
        goto begin;
    }

}

void Play(Game game) {

    double pre_arr;
    int acres_buy;
    int acres_sell;
    int wheat_eat;
    int acres_plant;
    int temp_wheat;
    double wh_required;

    
    for (game.year; game.year <= default_rounds; game.year++) {
        temp_wheat = game.wheat;
        UserExit(game);
        game.acre_price = (rand() % 10) + 17;

        printReport(game);


        cout << "Что пожелаешь, повелитель?" << endl;
        do {
            cout << "Сколько акров земли повелеваешь купить?" << endl;
            acres_buy = validateInteger();
            if (acres_buy * game.acre_price > game.wheat)
                cout << "Недостаточно пшеницы для покупки " << acres_buy << " акров" << endl;
        } while (acres_buy * game.acre_price > game.wheat);

        temp_wheat -= acres_buy * game.acre_price;
        game.acres += acres_buy;

        do {
            cout << "Сколько акров земли повелеваешь продать?" << endl;
            acres_sell = validateInteger();
            if (acres_sell > game.acres)
                cout << "Невозможно продать " << acres_buy << " акров, в городе недостаточно земли" << endl;
        } while (acres_sell > game.acres);

        temp_wheat += acres_sell * game.acre_price;
        game.acres -= acres_sell;

        do {
            cout << "Сколько бушелей пшеницы повелеваешь съесть?" << endl;
            wheat_eat = validateInteger();
            if (wheat_eat > game.wheat)
                cout << "Невозможно съесть " << wheat_eat << " бушелей, в городе только " << game.wheat << "бушелей." << endl;
        } while (wheat_eat > game.wheat);

        temp_wheat -= wheat_eat;

        do {
            cout << "Сколько акров земли повелеваешь засеять?" << endl;
            acres_plant = validateInteger();
            if (acres_plant * seedForAcre > temp_wheat)
                cout << "Невозможно засеять " << acres_plant << " акров, в городе только " << game.wheat << " бушелей пшеницы." << endl;
        } while (acres_plant > game.acres);

        // died of hunger
        wh_required = wheat_eat / (game.citizens * static_cast<double>(whEatenByEachCitizen));
        if (wh_required < 1) {
            game.died_of_hunger = ceil((game.citizens * whEatenByEachCitizen - wheat_eat) / whEatenByEachCitizen);
            if ((static_cast<double>(game.died_of_hunger) / game.citizens) > 0.45)
                game.end_game_hunger = true;
        }
        else {
            game.died_of_hunger = 0;
        }

        //arrived
        pre_arr = game.died_of_hunger / 2 + (5 - game.wh_by_acre) * game.wheat / 600 + 1;
        if (pre_arr < 0) {
            game.newly_arrived = 0;
        }
        else if (pre_arr > 50) {
            game.newly_arrived = 50;
        }
        else {
            game.newly_arrived = round(pre_arr);
        }

        //plague
        int n = (rand() % 6);
        if (n == 1) {
            game.died_of_plague = 1;
            game.citizens = (int)game.citizens / 2;
        }
        else {
            game.died_of_plague = 0;

        }

        //current citizens
        game.citizens = game.citizens + game.newly_arrived - game.died_of_hunger;

        //all collected wheat and wheat by acre
        game.wh_by_acre = (rand() % 6) + 1;

        game.collected_wheat = acres_plant * game.wh_by_acre;

        //updating wheat value
        game.wheat = temp_wheat + game.collected_wheat - game.wh_destroyed_rats;

        //destroyed by rats
        game.wh_destroyed_rats = (rand() % (int)((0.07 * static_cast<double>(game.wheat))) + 1);

        //current S in acres


        //ending the game if too many deaths
        if (game.citizens <= 0 || game.end_game_hunger) {
            EndGameEarly();
        }

        game.P += (double)(game.died_of_hunger / game.citizens);

        //finishing the game on the 10th round with statistics calculations
        if (game.year == 10) {
            game.P = (double)(game.P / default_rounds);
            double L = game.acres / game.citizens;
            if (game.P > 33 && L < 7)
                cout << "Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города. Теперь вы вынуждены влачить жалкое существование в изгнании" << endl;
            else if (game.P > 10 && L < 9)
                cout << "Вы правили железной рукой, подобно Нерону и Ивану Грозному. Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем" << endl;
            else if (game.P > 3 && L < 10)
                cout << "Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова" << endl;
            else
                cout << "Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше" << endl;
        }
    }
    

}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    Game game{};
    ifstream progress;
    progress.open("autosave.txt");
    if (progress.peek() == EOF) {
        cout << "Нет сохранённого прогресса, будет начата новая игра" << endl;
        //start new game
        game = { default_wheat, default_acres, default_citizens, default_year, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        Play(game);
    }
    else {
        int yesno;
        cout << "Найден сохранённый прогресс, продолжить игру? (1 - да/0 - нет)" << endl;
        begin:
        cin >> yesno;
        if (yesno == 1) {
            Restore(game);
            Play(game);
        }
        else if (yesno == 0) {
            game = { default_wheat, default_acres, default_citizens, default_year, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            Play(game);
        }
        else {
            cout << "(1 - да/0 - нет)" << endl;
            goto begin;
        }

    }
   
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

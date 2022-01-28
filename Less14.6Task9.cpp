/*
Требуется реализовать упрощённую игру в Морской бой. Игровое поле размером 10 на 10 клеток.
Участвует двое игроков.

В арсенале каждого из них: 4 маленьких кораблика размером в одну клетку, 3 небольших корабля размером в две клетки,
2 средних корабля размером в три клетки и один большой корабль размером в четыре клетки.

Для простоты, клетки поля пронумерованы по вертикали от 0 до 9, и по горизонтали также от 0 до 9.
Мы не будем использовать классические наименования клеток, такие как B4, C6, а просто два индекса.

Вначале игроки по очереди расставляют корабли, начиная с самых маленьких и заканчивая большими.
Маленькие корабли в одну клетку расставляются с помощью указания лишь одной клетки-точки на поле, к примеру 2,1.
Корабли размерностью от двух клеток и выше, расставляются с помощью координат их начала и конца, к примеру: 0,1 - 0,3.
Корабли могут быть установлены только строго вертикально, или горизонтально.
Установка корабля по диагонали — недопустимо, в случае которого об этом тоже надо сообщить пользователю.
Если корабль не может быть размещён на заданных клетках из-за того, что он столкнётся с другим кораблём (окажется на его клетках)
или выйдет за пределы поля вообще, то игроку должно быть сделано предупреждение, 
после которого он должен переставить корабль на новые валидные координаты. 
Замечу, в нашем упрощённом варианте игры, мы не будем обсчитывать соприкосновения кораблей друг с другом, 
а потому корабли вполне можно будет размещать друг к другу вплотную — борт к борту. 

После того как все корабли были расставлены начинается игра.
Игроки по очереди атакуют друг друга, называя координаты выстрела.
После выстрела, в консоль выводится информация о его результате: попал или мимо. 
Если выстрел успешен, клетка, на которой был корабль (или его фрагмент) затирается и становится пустой.
Игра заканчивается тогда, когда все корабли одной из сторон будут полностью уничтожены. 
Как только это произойдёт в консоль выводится информация с номером игрока, который победил.
*/

#include <iostream>
using namespace std;

void initialization (bool battlefiel[][10]) {
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            battlefiel[y][x] = 0;
        }
    }
}

void output(bool battlefiel[][10]) {
    for (int y = 9; y >= 0; y--) {
        for (int x = 0; x < 10; x++) {
            cout << battlefiel[y][x]<< " ";
        }
        cout << endl;
    }
}

void inputBattleships(bool battlefield[][10], int numBattleships, int lengthBattleships) {
    for (int ships = 0; ships < numBattleships; ) {
        int x1, y1, x2, y2;
        cout << "Input coordinats start (x y)" << ships + 1 << " ship: ";
        cin >> x1 >> y1;
        cout << "Input coordinats end (x y)" << ships + 1 << " ship: ";
        cin >> x2 >> y2;

        //validation
        if (x1 < 0 || x1 > 9 ||
            y1 < 0 || y1 > 9 ||
            x2 < 0 || x2 > 9 ||
            y2 < 0 || y2 > 9) {
            cout << "Error input, out of the battlefield, try again." << endl;
            continue;
        }
        for (int n = y1; n <= y2; n++) {
            for (int m = x1; m <= x2; m++) {
                if (battlefield[n][m] == 1) {
                    cout << "Error input, here is a ship, try again." << endl;
                    continue;
                }
            }
        }
        int x = abs(x1 - x2), y = abs(y1 - y2);
        if ((x != lengthBattleships-1 || y != 0) && (x != 0 || y != lengthBattleships-1)) { 
            cout << "Error input, wrong ship, try again." << endl;
            continue;                                                                       //don`t continue. why?
        }

        //input 
        for (int n = y1; n <= y2; n++) {
            for (int m = x1; m <= x2; m++) {
                battlefield[n][m] = 1;
            }
        }
        ships++;
    }
}

int main()
{
    bool battlefieldPlayer1[10][10], battlefieldPlayer2[10][10];

    //initialization battlefields;
    initialization(battlefieldPlayer1);
    initialization(battlefieldPlayer2);

    //placement of ships Player 1
    // 4 litle ships
    cout << "Player 1 arrange 4 ships 1x1" << endl;
    for (int ships = 0; ships < 4; ) {
        int x, y;
        cout << "Player 1 input coordinats (x y)" << ships + 1 << " ship: ";
        cin >> x >> y;
        //validation
        if(x < 0 || x > 9 ||
           y < 0 || y > 9) {
            cout << "Error input, out of the battlefield, try again." << endl;
            continue;
        }
        if (battlefieldPlayer1[y][x] == 1) {
            cout << "Error input, here is a ship, try again." << endl;
            continue;
        }

        battlefieldPlayer1[y][x] = 1;
        ++ships;

    }
    output(battlefieldPlayer1);
    // 3 small ships
    cout << "Player 1 arrange 3 ships 2x1" << endl;
    inputBattleships(battlefieldPlayer1, 3, 2);
    output(battlefieldPlayer1);
    // 2 medium ships
    cout << "Player 1 arrange 2 ships 3x1" << endl;
    inputBattleships(battlefieldPlayer1, 2, 3);
    output(battlefieldPlayer1);
    // 1 big ships
    cout << "Player 1 arrange 1 ships 4x1" << endl;
    inputBattleships(battlefieldPlayer1, 1, 4);
    output(battlefieldPlayer1);

    //placement of ships Player 2
    // 4 litle ships
    cout << "Player 2 arrange 4 ships 1x1" << endl;
    for (int ships = 0; ships < 4; ) {
        int x, y;
        cout << "Input coordinats (x y)" << ships + 1 << " ship: ";
        cin >> x >> y;
        //validation
        if (x < 0 || x > 9 ||
            y < 0 || y > 9) {
            cout << "Error input, out of the battlefield, try again." << endl;
            continue;
        }
        if (battlefieldPlayer2[y][x] == 1) {
            cout << "Error input, here is a ship, try again." << endl;
            continue;
        }

        battlefieldPlayer2[y][x] = 1;
        ships++;
    }
    // 3 small ships
    cout << "Player 2 arrange 3 ships 2x1" << endl;
    inputBattleships(battlefieldPlayer2, 3, 2);

    // 2 medium ships
    cout << "Player 2 arrange 2 ships 3x1" << endl;
    inputBattleships(battlefieldPlayer2, 2, 3);

    // 1 big ships
    cout << "Player 2 arrange 1 ships 4x1" << endl;
    inputBattleships(battlefieldPlayer2, 1, 4);

    output(battlefieldPlayer2);

    //start play
    int x, y, nCountP1 = 20, nCountP2 = 20;
    bool bPlayer1Turn = 1;
    while (nCountP1 > 0 || nCountP2 > 0) {
        if (bPlayer1Turn) {
            cout << "Player 1 shot!" << endl << "Enter coordinate (X Y): ";
            cin >> x >> y;
            if (battlefieldPlayer2[y][x] == 0) {
                cout << "miss..." << endl;
                bPlayer1Turn = !bPlayer1Turn;
            }
            else {
                cout << "hit!" << endl;
                battlefieldPlayer2[y][x] = 0;
                nCountP2--;
            }
        }
        else {
            cout << "Player 2 shot!" << endl << "Enter coordinate (X Y): ";
            cin >> x >> y;
            if (battlefieldPlayer1[y][x] == 0) {
                cout << "miss..." << endl;
                bPlayer1Turn = !bPlayer1Turn;
            }
            else {
                cout << "hit!" << endl;
                battlefieldPlayer1[y][x] = 0;
                nCountP1--;
            }
        }
    }

    //output resultat
    cout << "battlefield" << endl;
    cout << "Player 1" << endl;
    output(battlefieldPlayer1);
    cout << "--------------------" << endl;
    cout << "Player 2" << endl;
    output(battlefieldPlayer2);
    cout << endl;

    (nCountP1 == 0) ? (cout << "Player 2 won!") : (cout << "Player 1 won!");
        
}


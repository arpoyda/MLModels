// MLModels.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "LinVector.h"
#include "LinMatrix.h"


int main()
{
    float a[6] = { 1, 2, 3, 4, 5, 6};
    LinMatrix mat2{ 2, 3, a };
    LinMatrix mat{ 2, 3, a };
    //mat.print();
    LinMatrix matT = mat.T();
    //matT.print();
    LinMatrix matF0 = mat.flatten(0);
    //matF0.print();
    LinMatrix matF1 = mat.flatten(1);
    //matF1.print();
    LinMatrix matSm = mat + mat2;
    //matS.print();
    LinMatrix matM = mat.matmul(matT);
    //matM.print();
    LinMatrix matSs = mat + 100;
    //matSs.print();
    LinMatrix matMs = mat - 100;
    //matMs.print();
    mat2 += 100;
    //mat2.print();
    LinMatrix col = mat.getCol(1);
    //col.print();
    LinMatrix row = mat.getRow(0) * 10;
    //row.print();
    LinMatrix mat_col = mat.setRow(0, row);
    //mat_col.print();

    float b[9] = { 2, 1, 3, 1, 3, -3, -2, 4, 4 };
    LinMatrix mat2i{ 3, 3, b };
    LinMatrix matI = mat2i.inverse();
    matI.print();



    


    
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

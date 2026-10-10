#include "add.h"


int main() 
{
    system("chcp 65001 > nul");

    DoublyLinkedList list;

    cout << "=== 1. НАПОВНЕННЯ СПИСКУ ЕЛЕМЕНТАМИ ===\n";
    // Використовуємо pushFront та pushBack (пункт 1 методички)
    list.pushBack(-15);
    list.pushBack(7);
    list.pushBack(42);
    list.pushBack(-3);
    list.pushBack(19);
    list.pushFront(100);  // Додавання на початок
    list.pushBack(-8);

    cout << "Початковий список:\n";
    cout << "Вміст: ";
    list.print();
    cout << "Довжина: " << list.getSize() << "\n";
    list.printTransitionTable();

    cout << "\n=== 2. ЗАВДАННЯ А: ЗАМІНА ВІД'ЄМНИХ ЕЛЕМЕНТІВ НА 0 ===\n";
    list.replaceNegativesWithZero();
    cout << "Вміст після завдання А: ";
    list.print();
    cout << "Довжина: " << list.getSize() << "\n";
    list.printTransitionTable();

    cout << "\n=== 3. ЗАВДАННЯ Б: ВИДАЛЕННЯ МІНІМАЛЬНОГО ТА МАКСИМАЛЬНОГО ЕЛЕМЕНТІВ ===\n";
    cout << "Видаляємо мінімальний елемент...\n";
    list.removeMin();
    cout << "Видаляємо максимальний елемент...\n";
    list.removeMax();

    cout << "Вміст після завдання Б: ";
    list.print();
    cout << "Довжина: " << list.getSize() << "\n";
    list.printTransitionTable();

    cout << "\n=== 4. ЗАВДАННЯ В: ПЕРЕВІРКА ВПОРЯДКОВАНОСТІ ЗА ЗРОСТАННЯМ ===\n";
    if (list.isSortedAscending()) {
        cout << "Результат: Елементи списку впорядковані за зростанням.\n";
    }
    else {
        cout << "Результат: Елементи списку НЕ впорядковані за зростанням.\n";
    }
    cout << "Вміст: ";
    list.print();
    cout << "Довжина: " << list.getSize() << "\n";
    list.printTransitionTable();

    cout << "\n=== 5. ДЕМОНСТРАЦІЯ ЗАВДАННЯ В НА ВІДСОРТОВАНОМУ СПИСКУ ===\n";
    DoublyLinkedList sortedList;
    sortedList.pushBack(10);
    sortedList.pushBack(20);
    sortedList.pushBack(30);
    sortedList.pushBack(40);

    cout << "Вміст нового списку: ";
    sortedList.print();
    cout << "Довжина: " << sortedList.getSize() << "\n";
    if (sortedList.isSortedAscending()) {
        cout << "Результат: Елементи списку впорядковані за зростанням.\n";
    }
    else {
        cout << "Результат: Елементи списку НЕ впорядковані за зростанням.\n";
    }
    sortedList.printTransitionTable();

    return 0;
}
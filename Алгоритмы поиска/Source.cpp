#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

void init(int A[], int n);
void Hoar_sort(int A[], int n);
void Qsort(int A[], int f, int l);
int unsorted_line_search(int A[], int n, int srch_elem);
int unsorted_fast_line_search(int A[], int n, int srch_elem);
int sorted_fast_line_search(int A[], int n, int srch_elem);
int bin_search(int A[], int srch_elem, int begin, int end);
int block_search(int A[], int n, int srch_elem);

int main()
{
	system("chcp 1251"); //Смена кодовой страницы консоли для отображения русской раскладки
	system("cls"); //Очистка окна консоли

	int n, srch_elem;
	cout << "Введите размер массива: ";
	cin >> n;

	int* A = new int[n + 1];

	init(A, n); //Инициализация массива

	cout << "Введите искомый элемент массива: ";
	cin >> srch_elem;
	cout << endl;

	cout << "Поиск числа " << srch_elem << " в массиве..." << endl << endl;

	//Алгоритмы поиска в неупорядоченном массиве:
	cout << "Количество итераций поиска Unsorted_line_search: " << unsorted_line_search(A, n, srch_elem) << endl << endl;
	cout << "Количество итераций поиска Unsorted_fast_line_search: " << unsorted_fast_line_search(A, n, srch_elem) << endl << endl;

	Hoar_sort(A, n); //Сортировка массива
	
	//Алгоритмы поиска в упорядоченном массиве:
	cout << "Количество итераций поиска Sorted_fast_line_search: " << sorted_fast_line_search(A, n, srch_elem) << endl << endl;
	cout << "Количество итераций поиска Bin_search: " << bin_search(A, srch_elem, 0, n - 1) << endl << endl;
	cout << "Количество итераций поиска Block_search: " << block_search(A, n, srch_elem) << endl << endl;

	delete[] A;

	system("pause"); //Задержка окна консоли до нажатия любой клавиши
	return 0;
}

void init(int A[], int n) //Инициализация массива
{
	cout << "Инициализация массива..." << endl;

	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		A[i] = rand() % 100 + 1; //Наполнение массива случайными числами от 1 до 100
		if (n <= 100) //Выводим массив в консоль для наглядности (только если количество чисел в массиве не превышает 100,
			cout << A[i] << " ";								 //чтобы не забивать консоль большим количеством чисел)
	}

	cout << endl << "Завершено" << endl << endl;
}

void Hoar_sort(int A[], int n) //Вход в рекурсивную сортировку Хоара
{
	cout << "Сортировка массива..." << endl;

	Qsort(A, 0, n - 1); //Вход в рекурсию
	
	cout << "Завершено" << endl << endl;
}

void Qsort(int A[], int f, int l) //Сортировка Хоара
{
	int first = f, last = l; //Определяем индексы первого и последнего элементов
	int separator = A[((first + last) / 2)]; //Определяем "разделитель" как центральный элемент

	while (first <= last)
	{
		while (A[first] < separator) //Находим элемент слева от разделителя, больший по значению разделителя
			first++;
		while (A[last] > separator) //Находим элемент справа от разделителя, меньший по значению разделителя
			last--;
		if (first <= last) //Меняем местами найденые элементы
		{
			int buf = A[first];
			A[first] = A[last];
			A[last] = buf;
			first++;
			last--;
		}
	}

	//Рекурсивно сортируем полученные две части массива
	if (f < last)
		Qsort(A, f, last);
	if (first < l)
		Qsort(A, first, l);
}

int unsorted_line_search(int A[], int n, int srch_elem) //Линейный поиск в неупорядоченном массиве
{
	int count;
	bool srch_index = false;
	for (count = 0; count < n; count++) //Проходимся по каждому элементу массива, пока не найдём искомый или не закончится массив
	{
		if (A[count] == srch_elem) //Сравниваем элемент массива с искомым элементом
		{
			srch_index = true;
			count++;
			cout << "Искомый элемент найден." << endl;
			break;
		}
	}

	if (!srch_index)
		cout << "Искомый элемент не найден." << endl;

	return count; //Выводим количество итераций поиска
}

int unsorted_fast_line_search(int A[], int n, int srch_elem) //Быстрый линейный поиск в неупорядоченном массиве
{
	int count = 0;
	A[n] = srch_elem; //Добавляем в конец массива искомый элемент

	while (A[count] != srch_elem) //Проходимся по каждому элементу массива, пока не найдём искомый
		count++;

	if (count != n) //Если искомый элемент найден не последним (добавленным вручную), то мы нашли его среди элементов массива
		cout << "Искомый элемент найден." << endl;
	else //Иначе найден элемент добавленный вручную и среди массива его нет
		cout << "Искомый элемент не найден." << endl;

	return ++count; //Выводим количество итераций поиска
}

int sorted_fast_line_search(int A[], int n, int srch_elem) //Быстрый линейный поиск в упорядоченном массиве
{
	int count = 0;
	A[n] = srch_elem; //Добавляем в конец массива искомый элемент

	while (A[count] < srch_elem) //Проходимся по каждому элементу массива, пока не найдём элемент не меньший искомого
		count++;

	if (A[count] == srch_elem && count != n) //Если искомый элемент найден не последним (добавленным вручную),
		cout << "Искомый элемент найден." << endl;					//то мы нашли его среди элементов массива
	else //Иначе найден элемент больше искомого или добавленный вручную
		cout << "Искомый элемент не найден." << endl;

	return ++count; //Выводим количество итераций поиска
}

int bin_search(int A[], int srch_elem, int begin, int end) //Бинарный поиск
{
	int mid_index = (begin + end) / 2; //Определяем индекс центрального элемента

	if (A[mid_index] == srch_elem) //Если центральный элемент равен искомому, то мы нашли его
	{
		cout << "Искомый элемент найден." << endl;
		return 1; //Выводим количество итераций поиска
	}

	if (begin == end) //Если начальный и конечный индексы равны, значит больше не осталось элементов для проверки
	{
		cout << "Искомый элемент не найден." << endl;
		return 1; //Выводим количество итераций поиска
	}

	//Рекурсивно выполняем поиск
	else if (A[mid_index] < srch_elem) //Если центральный элемент меньше искомого, то определяем левую границу массива
		return bin_search(A, srch_elem, ++mid_index, end) + 1;					//как индекс центрального элемента + 1
	else //Иначе если центральный элемент больше искомого, то определяем правую границу массива, как индекс центрального элемента
		return bin_search(A, srch_elem, begin, mid_index) + 1;
}

int block_search(int A[], int n, int srch_elem) //Блочный поиск
{
	int count = 0, curr_elem = 0;
	int block_amount = (int)(sqrt(n)); //Определяем количество блоков как корень из количества элементов массива
	A[n] = srch_elem; //Добавляем в конец массива искомый элемент (для быстрого линейного поиска)

	while (count < block_amount) //Выполняем пока остались непроверенные блоки
	{
		count++;
		if (A[(block_amount * count) - 1] == srch_elem) //Если последний элемент блока равен искомому, то мы нашли его
		{
			cout << "Искомый элемент найден." << endl;
			return count; //Выводим количество итераций поиска
		}

		if (A[(block_amount * count) - 1] > srch_elem) //Если последний элемент блока больше искомого,
		{											   //то искомый элемент может находиться где-то в этом блоке
			curr_elem = block_amount * count - block_amount; //Определяем начальный элемент поиска как первый элемент блока
			goto line_srch; //Переходим к быстрому линейному поиску
		}
	}

	curr_elem = block_amount * count; //Определяем начальный элемент поиска как первый элемент последнего блока
	line_srch: //Быстрый линейный поиск
	while (A[curr_elem] < srch_elem)
	{
		curr_elem++;
		count++;
	}

	if (A[curr_elem] == srch_elem && curr_elem != n)
		cout << "Искомый элемент найден." << endl;
	else
		cout << "Искомый элемент не найден." << endl;

	return ++count; //Выводим количество итераций поиска
}
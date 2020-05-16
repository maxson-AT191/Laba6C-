#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <string>

using namespace std;

FILE* f_out, * f_in;

struct Executor
{
    char executor[56];
    char album_name[56];
    int edition;
    int year;
    double cost;
};

void medium1()
{
	//Распечатать в бин. файл сведения об исполнителях, тираж альбома которого превышает 1000 экземпляров и цена составляет минимум 50 грн;

	Executor* arr;
	int size;

	//количество исполнителей не может быть меньше 1;
	do
	{
		cout << "Введите количество исполнителей, данные которых вы будете вводить: ";
		cin >> size;
	} while (size < 1);

	arr = new Executor[size];

	//вводим информацию;
	for (int i = 0; i < size; i++)
	{
		cout << "Введите фамилию исполнителя номер " << i + 1 << ": ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].executor, 56);
		cout << endl;

		cout << "Введите название альбома: ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].album_name, 56);
		cout << endl;

		do {
			cout << "Введите тираж: ";
			cin >> arr[i].edition;
			cout << endl;
		} while (arr[i].edition <= 0);

		do {
			cout << "Введите год выпуска: ";
			cin >> arr[i].year;
			cout << endl;
		} while (arr[i].year < 1960);

		do {
			cout << "Введите стоимость альбома: ";
			cin >> arr[i].cost;
			cout << endl;
		} while (arr[i].cost <= 0);

		cout << endl;
	}

	//говорим программе что запись будет в бинарном виде;
	ofstream input("medium1_file.bin", ios::binary | ios::out);

	for (int i = 0; i < size; i++)
	{
		if (arr[i].edition > 1000 && arr[i].cost >= 50)
		{
			//преобразуем данные в тип char для записи, считываем размерность данных для правильной бинарной записи;
			input << "Исполнитель номер " << i + 1 << ":" << endl;
			input.write((char*)&arr[i], sizeof arr[i]) << endl << endl;
		}
	}

	cout << "Соответственные данные записаны в файл" << endl << endl;
}

void medium2()
{
	//Записать построчно в бин. файл двумерный масив 5х5, изменить значения в файле увеличив каждый элемент массива в 1.5 раза;

	const int row = 5, col = 6;
	double arr[row][col];

	//говорим программе что запись будет идти в бин. виде;
	f_out = fopen("medium2_numbers_before.bin", "wb");

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j != col - 1)
			{
				//считываем в файл элементы массива;
				arr[i][j] = rand() % 10;
				fwrite(&arr[i][j], sizeof(double), 1, f_out);
			}
			else
			{
				//элемент перехода на новую строку в файле занимает 6-ю колонку массива - ее мы не будем выводить в консоль;
				fwrite(&"\n", sizeof(double), 1, f_out);
			}
		}
	}

	fclose(f_out);

	double new_arr[row][col];

	//считываем с файла данные в новый массив;
	f_in = fopen("medium2_numbers_before.bin", "rb");
	fread(&new_arr, sizeof(double), row * col, f_in);
	fclose(f_in);

	cout << "Массив до изменений: " << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j != col - 1)
			{				
				cout << new_arr[i][j] << "\t";
				new_arr[i][j] += (new_arr[i][j] / 2);
			}
		}
		cout << endl;
	}

	cout << endl;

	//записываем в новый файл уже измененный массив;
	f_out = fopen("medium2_numbers_after.bin", "wb");

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j != col - 1)
			{
				fwrite(&new_arr[i][j], sizeof(double), 1, f_out);
			}
			else
			{
				fwrite(&"\n", sizeof(double), 1, f_out);
			}
		}
	}

	fclose(f_out);

	//выводим новый массив в консоль;
	f_in = fopen("medium2_numbers_after.bin", "rb");
	fread(&new_arr, sizeof(double), row * col, f_in);
	fclose(f_in);

	cout << "Массив после изменений:" << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j != col - 1)
			{
				cout << new_arr[i][j] << "\t";
			}
		}
		cout << endl;
	}

	cout << endl << endl;
}



struct Book
{
	string fio;
	string book_name;
	int    cost;
	int    count;
};


Book* FillStruct(Book* mas_book, int count)  // заполняет масив структур
{
	if (mas_book == nullptr)
		mas_book = new Book[count];
	for (size_t i = 0; i < count; i++)
	{
		mas_book[i].fio = "FIO" + to_string(i + 1);
		mas_book[i].book_name = "BooksName" + to_string(i + 1);
		mas_book[i].cost = 100 + rand() % 1000;
		mas_book[i].count = 1 + rand() % 100;
	}
	return mas_book;
}
void ShowBooks(Book* mas_books, int count)
{
	cout << "\nИнформация о всех книгах: \n";
	for (size_t i = 0; i < count; i++)
	{
		printf("\nИнформация о %d книге: \n\t", i + 1);
		cout << mas_books[i].fio << " ";
		cout << mas_books[i].book_name << " ";
		cout << mas_books[i].cost << " ";
		cout << mas_books[i].count << "\n";
	}
}
Book* LoadFile(int count)  //Прочитать данные с файла
{
	ifstream f_in; f_in.open("database.bin", ios::binary | ios::in);
	Book* buffer = new Book[count];
	f_in.read((char*)buffer, count * sizeof(Book));
	f_in.close();
	return buffer;
}
void SaveFile(Book* mas_book, int count)
{
	ofstream f_out; f_out.open("database.bin", ios::binary | ios::out);
	int BufferSize = count * sizeof(Book);
	f_out.write((char*)mas_book, BufferSize);
	f_out.close();
}
int IsSetDiscount(int count) //Установление скидки если соблюдается условие 
{
	ifstream f_in; f_in.open("database.bin", ios::binary | ios::in);
	Book* buffer = new Book[count];
	f_in.read((char*)buffer, count * sizeof(Book));
	f_in.close();
	for (size_t i = 0; i < count; i++)
	{
		if (buffer[i].count > 20)
		{
			buffer[i].cost -= buffer[i].cost * 0.05;
		}
	}
	SaveFile(buffer, count);
	return 0;
}
void medium3() {
	cout << "\nHard task level: \n";
	int count = 10;
	Book* mas_book = new Book[count];
	mas_book = FillStruct(mas_book, count);
	SaveFile(mas_book, count);
	mas_book = LoadFile(count);
	cout << "\nСодержимое файла до внесенных изминений: \n";
	cout << "\nВ файле хранится масив структур содержащих следущие поля: \n";
	cout << "\t-ФИО автора\n\t-название книги\n\t-цена за ед.\n\t-количетсво экзэмпляров";
	ShowBooks(mas_book, count);
	cout << "\nСодержимое файла после внесенных изминений: ";
	IsSetDiscount(count);
	Book* buffer = new Book[count];
	buffer = LoadFile(count);
	SaveFile(buffer, count);
	ShowBooks(buffer, count);
	cout << "\nНажмите <Enter> для завершения...";
	while (getchar() != '\n')
		continue;
}

int main()
{
	setlocale(LC_ALL, "RU");

	int a;
	int count = 0;

	do
	{
		cout << "Введите номер задания(medium_1 - 1, medium_2 - 2,medium_3 - 3): ";

		cin >> a;

		cout << endl;

		if (a == 1)
		{
			medium1();
			count++;
		}

		if (a == 2)
		{
			medium2();
			count++;
		}
		if (a == 3)
		{
			medium3();
			count++;
		}
	} while (count == 0);

	int b;

	do
	{
		count = 0;

		cout << "Продолжить ввод? Да - 1, Нет - 2: ";

		cin >> b;

		cout << endl;

		if (b == 1)
		{
			count++;
			main();
		}

		if (b == 2)
		{
			cout << "Вы решили не продолжать";
			count++;
			break;
		}

	} while (count == 0);
}

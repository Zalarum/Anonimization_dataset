#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

string anon_name(string input)
{
    if (input[input.length() - 1] == 'ч') return "М";
    else return "Ж";
}

string anon_symp(string input)
{
    istringstream iss;
    iss.str(input);

    vector<string> elements;

    for (string element; getline(iss, element, ','); ) elements.push_back(element);

    if (elements.size() < 5) return "0--4";
    else return "5--9";
    //return to_string(elements.size());
}

string anon_doct(string input)
{
    if (input == "Психиатр" || input == "Психолог" || input == "Психотерапевт" || input == "Нейропсихолог" || input == "Невролог" || input == "Логопед" || input == "Сексолог")
    {
        return "Психология";
    }
    else if (input == "Косметолог" || input == "Гематолог" || input == "Дерматолог" || input == "Трихолог")
    {
        return "Кожные заболевания";
    }
    else if (input == "Инфекционист" || input == "Стоматолог" || input == "Терапевт" || input == "Хирург" || input == "Эндокринолог" || input == "Фельдшер" || input == "Онколог" || input == "Ортопед" || input == "Отоларинголог" || input == "Офтальмолог" || input == "Педиатр" || input == "Кардиолог" || input == "Аллерголог")
    {
        return "Врачи общей практики";
    }
    else if (input == "Акушер-гинеколог" || input == "Венеролог" || input == "Маммолог" || input == "Проктолог" || input == "Репродуктолог" || input == "Уролог" || input == "Гинеколог" || input == "Андролог")
    {
        return "Проблемы половых органов";
    }
    else if (input == "Гастроэнтеролог" || input == "Гепатолог" || input == "Диетолог" || input == "Нефролог")
    {
        return "Проблемы с желудком";
    }
    else if (input == "Гомеопат " || input == "Иммунолог" || input == "Мануальный терапевт" || input == "Массажист" || input == "Нарколог" || input == "Пластический хирург" || input == "Пульмонолог" || input == "Ревматолог" || input == "УЗИ-специалист" || input == "Флеболог" || input == "Физиотерапевт" || input == "Фтизиатр" || input == "Химиотерапевт")
    {
        return "Узко направленные специалисты";
    }
    else return " ";
}

string anon_data(string input)
{
    int year = (input[2] - '0') * 10 + input[3] - '0';

    int month = (input[5] - '0') * 10 + input[6] - '0';

    if (month == 12 || month < 3) return "20" + to_string(year) + "-зима";
    else if (month > 2 && month < 6) return "20" + to_string(year) + "-весна";
    else if (month > 5 && month < 9) return "20" + to_string(year) + "-лето";
    else if (month > 8 && month < 12) return "20" + to_string(year) + "-осень";
}

string anon_cost(string input)
{
    if (stoi(input) > 1000) return "> 1000";
    else return "<= 1000";
}

string anon_card(string input)
{
    int num = (input[1] - '0') * 10 + input[2] - '0';
    return "<" + to_string(num) + "** **** **** ****>";
}

int main()
{
    setlocale(LC_ALL, "Russian");

    ofstream file_out;

    map <string, int> k;

    file_out.open("Aninymous.csv");

    //file_out << "ФИО" << ';' << "Паспорт" << ';' << "Снилс" << ';' << "Врач" << ';' << "Симптомы" << ';' << "Анализы" << ';' << "Время посещения" << ';' << "Стоимость" << ";" << "Карта" << endl;
    
    string line, element, tmp = "";

    ifstream file_in("Dataset_for_hospital.csv");

    int mas[10] = { 0 };

    int n, t;
    cout << "Введите количество квази-идентефикаторов: ";
    cin >> n;
    cout << "Введите номера столбцов квази-идентефикаторов, где:\n"
         << "1 - имена\n"
         << "2 - паспорта\n"
         << "3 - снилсы\n"
         << "4 - врачи\n"
         << "5 - симптомы\n"
         << "6 - анализы\n"
         << "7 - время\n"
         << "8 - стоимость\n"
         << "9 - карта\n";

    for (int i = 0; i < n; ++i)
    {
        cin >> t;
        mas[t] = 1;
    }
    cout << "Ждите...\n";

    while (getline(file_in, line))
    {
        istringstream iss;
        iss.str(line);

        getline(iss, element, ';'); // имена
        element = anon_name(element);
        file_out << element << ';';
        if (mas[1] == 1) tmp += element;

        getline(iss, element, ';'); // паспорт
        file_out << " ;";
        if (mas[2] == 1) tmp += " ;";

        getline(iss, element, ';'); // снилс
        file_out << " ;";
        if (mas[3] == 1) tmp += " ;";

        getline(iss, element, ';'); // врач
        element = anon_doct(element);
        file_out << element << ';';
        if (mas[4] == 1) tmp += element;

        getline(iss, element, ';'); // симптомы
        element = anon_symp(element);
        file_out << element << ';';
        if (mas[5] == 1) tmp += element;

        getline(iss, element, ';'); // анализы
        file_out << " ;";
        if (mas[6] == 1) tmp += " ;";

        getline(iss, element, ';'); // время
        element = anon_data(element);
        file_out << element << ';';
        if (mas[7] == 1) tmp += element;

        getline(iss, element, ';');

        getline(iss, element, ';'); // стоимость
        element = anon_cost(element);
        file_out << element << ';';
        if (mas[8] == 1) tmp += element;

        getline(iss, element, ';'); // карта
        element = anon_card(element);
        file_out << element << '\n';
        if (mas[9] == 1) tmp += element;

        if (k.find(tmp) == k.end()) k[tmp] = 1;
        else k[tmp]++;

        tmp = "";
    }

    file_in.close();

    file_out.close();

    int min = 9999, j1 = 0, j2 = 0, j3 = 0;

    for (auto it = k.begin(); it != k.end(); it++)
    {
        //if (it->second == 1) j1++;
        //if (it->second == 2) j2++;
        //if (it->second == 3) j3++;
        if (it->second < min) min = it->second;
    }

    cout << "k-anonimity: " << min; //<< ' ' << j1 << ' ' << j2 << ' ' << j3;;

    system("Aninymous.csv");

    return 0;
}
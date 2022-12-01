#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

string anon_name(string input)
{
    if (input[input.length() - 1] == '�') return "�";
    else return "�";
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
    if (input == "��������" || input == "��������" || input == "�������������" || input == "�������������" || input == "��������" || input == "�������" || input == "��������")
    {
        return "����������";
    }
    else if (input == "����������" || input == "���������" || input == "����������" || input == "��������")
    {
        return "������ �����������";
    }
    else if (input == "������������" || input == "����������" || input == "��������" || input == "������" || input == "������������" || input == "��������" || input == "�������" || input == "�������" || input == "�������������" || input == "�����������" || input == "�������" || input == "���������" || input == "����������")
    {
        return "����� ����� ��������";
    }
    else if (input == "������-���������" || input == "���������" || input == "��������" || input == "���������" || input == "�������������" || input == "������" || input == "���������" || input == "��������")
    {
        return "�������� ������� �������";
    }
    else if (input == "���������������" || input == "���������" || input == "��������" || input == "��������")
    {
        return "�������� � ��������";
    }
    else if (input == "�������� " || input == "���������" || input == "���������� ��������" || input == "���������" || input == "��������" || input == "������������ ������" || input == "�����������" || input == "����������" || input == "���-����������" || input == "��������" || input == "�������������" || input == "��������" || input == "�������������")
    {
        return "���� ������������ �����������";
    }
    else return " ";
}

string anon_data(string input)
{
    int year = (input[2] - '0') * 10 + input[3] - '0';

    int month = (input[5] - '0') * 10 + input[6] - '0';

    if (month == 12 || month < 3) return "20" + to_string(year) + "-����";
    else if (month > 2 && month < 6) return "20" + to_string(year) + "-�����";
    else if (month > 5 && month < 9) return "20" + to_string(year) + "-����";
    else if (month > 8 && month < 12) return "20" + to_string(year) + "-�����";
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

    //file_out << "���" << ';' << "�������" << ';' << "�����" << ';' << "����" << ';' << "��������" << ';' << "�������" << ';' << "����� ���������" << ';' << "���������" << ";" << "�����" << endl;
    
    string line, element, tmp = "";

    ifstream file_in("Dataset_for_hospital.csv");

    int mas[10] = { 0 };

    int n, t;
    cout << "������� ���������� �����-���������������: ";
    cin >> n;
    cout << "������� ������ �������� �����-���������������, ���:\n"
         << "1 - �����\n"
         << "2 - ��������\n"
         << "3 - ������\n"
         << "4 - �����\n"
         << "5 - ��������\n"
         << "6 - �������\n"
         << "7 - �����\n"
         << "8 - ���������\n"
         << "9 - �����\n";

    for (int i = 0; i < n; ++i)
    {
        cin >> t;
        mas[t] = 1;
    }
    cout << "�����...\n";

    while (getline(file_in, line))
    {
        istringstream iss;
        iss.str(line);

        getline(iss, element, ';'); // �����
        element = anon_name(element);
        file_out << element << ';';
        if (mas[1] == 1) tmp += element;

        getline(iss, element, ';'); // �������
        file_out << " ;";
        if (mas[2] == 1) tmp += " ;";

        getline(iss, element, ';'); // �����
        file_out << " ;";
        if (mas[3] == 1) tmp += " ;";

        getline(iss, element, ';'); // ����
        element = anon_doct(element);
        file_out << element << ';';
        if (mas[4] == 1) tmp += element;

        getline(iss, element, ';'); // ��������
        element = anon_symp(element);
        file_out << element << ';';
        if (mas[5] == 1) tmp += element;

        getline(iss, element, ';'); // �������
        file_out << " ;";
        if (mas[6] == 1) tmp += " ;";

        getline(iss, element, ';'); // �����
        element = anon_data(element);
        file_out << element << ';';
        if (mas[7] == 1) tmp += element;

        getline(iss, element, ';');

        getline(iss, element, ';'); // ���������
        element = anon_cost(element);
        file_out << element << ';';
        if (mas[8] == 1) tmp += element;

        getline(iss, element, ';'); // �����
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
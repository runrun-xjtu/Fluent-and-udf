#include<iostream>
#include<math.h>
#include"function.h"
#include<fstream>
#include <sstream>


using namespace std;

int main()
{ 
	int num,n,i,k,j,end=0,symbol1[3], symbol2[3],N;
	bool t=0;

	string firstline = { 1 }, testdtr;
	string otherline[50];
	stringstream ss;
	string operate[3];
	double number[3];


	//getFolderDayFile(pathStr,arrStrFile);
	//cout << arrStrFile << endl;

	    readline(&firstline,1);       //读取第一行
		const char *p=firstline.data();  //拆成char数组
		num=findnum( p);                // 读取数字
		cout <<"数据点个数："<< num << endl;
	string * str = new string[num * 6];
	double * statistic = new double[num * 6];
	double * change_statistic = new double[num * 6];
	cout.precision(15);
	ss.precision(15);
	    cout << "读取数据中，请等待..." << endl;
	    for (i = 1; i <= 6; i++)         //读6*num
	{
		k = 0;
		for (n = (i - 1) *(num+2)+1; n <= (i - 1) * (num + 2) + 2; n++)   //读取前两行、中间两行
		{
		//cout << n << endl;
        readline(&otherline[(i - 1) *2+k],n);
		if (otherline[(i - 1) * 2 + k] == ")" && otherline[(i - 1) * 2 + k -1] == ")") end = 1;    //判断结尾
		k++;
		}
		if (end == 1) { N = i; break; }

		j = 0;
		for (n = (i - 1) * (num + 2) + 3; n <= (i - 1) * (num + 2) + num + 2; n++)    //读取数据区
		{
		//	cout << n << endl;
		//	cout << (i - 1) * num + j << endl;
			readline(&str[(i - 1) * num + j], n);
			ss << str[(i - 1) * num + j];     //字符串转化成double数据
			ss >> statistic[(i - 1) * num + j];
			ss.clear();
		//	cout << statistic[(i - 1) * num + j] << endl;
			j++;
		}
		cout << otherline[(i - 1) * 2 + 1] <<"数据读取完成" << endl;
	}
	delete [] str;

	
	do {
		if(t) cout << "输入不合格，请重新输入" << endl;      
     read_operation(operate,&t,symbol1, symbol2);                             //读取坐标变化等式  
	} while (t);
     


		read_number(operate, number);          //读取坐标变化数值
		/*
		for (i = 0; i < 3; i++)
		{
			cout << symbol1[i] << endl;
			cout << symbol2[i] << endl;
			cout <<number[i] << endl;
		}
        */

	for (i = 0; i < 3; i++)
	{
		switch (symbol1[i])
		{
		case 1: for (j = 0; j < num; j++)
		       {
			    change_statistic[i * num + j] = statistic[j];
		       } break;
		case 2: for (j = 0; j < num; j++)
		       {
			    change_statistic[i * num + j] = statistic[num + j];
		       } break;
		case 3: for (j = 0; j < num; j++)
		       {
			    change_statistic[i * num + j] = statistic[2 * num + j];
		       } break;
		case -1: for (j = 0; j < num; j++)
		       {
			    change_statistic[i * num + j] = (-1)*statistic[j];
		        } break;
		case -2: for (j = 0; j < num; j++)
		       {
			    change_statistic[i * num + j] = (-1) * statistic[num + j];
		        } break;
		case -3: for (j = 0; j < num; j++)
		       {
			    change_statistic[i * num + j] = (-1) * statistic[2* num + j];
		        } break;
		default: cout << "计算出错，符号输入不正确" << endl; break;
		}
		if (number[i] != 0)
		{
		switch (symbol2[i])
		 {
		 case 1: for (j = 0; j < num; j++)
		       {
			    change_statistic[i * num + j] = change_statistic[i * num + j]+number[i];
		        } break;
		 case -1: for (j = 0; j < num; j++)
		       {
		     	change_statistic[i * num + j] = change_statistic[i * num + j]-number[i];
		        }break;

		 }
        }
	}
	
	ofstream ofs;
	ofs.open("2.txt", ios::out);
	ofs.precision(15);

	for (i = 1; i <= N; i++)         //输出
	{
		for (k = 0; k < 2; k++)
		{
			//cout << otherline[(i - 1) * 2 + k] << endl;
			ofs << otherline[(i - 1) * 2 + k] << endl;
		}
		if (i != N)
		{
			if (i <= 3)
			{
			
			  for (j = 0; j < num; j++)
			  {
				//cout << change_statistic[(i - 1) * num + j] << endl;
				ofs << change_statistic[(i - 1) * num + j] << endl;
			  }
			  cout << otherline[(i - 1) * 2 +1] <<"输出完成" << endl;
            }
			else
			{
				for (j = 0; j < num; j++)
				{
				//	cout << statistic[(i - 1) * num + j] << endl;
					ofs << statistic[(i - 1) * num + j] << endl;
				}
				cout << otherline[(i - 1) * 2 + 1] << "输出完成" << endl;
			}
		}
	}

	cout << "输出完成" << endl;
	ofs.close();
	return 0;
}


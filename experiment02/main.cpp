#include <iostream>
#include <fstream>
#include "point.h"
#include "Point3D.h"
#include "Curve3D.h"
using namespace std;

void PrintTable()
{
	cout << "1. Display Curve" << endl << "2. Add a point" << endl
		<< "3. Delete a point" << endl << "4. the length of curve" << endl
		<< "5. Write to txt" << endl << "6. Read from txt" << endl
		<< "7. Write to bin" << endl << "8. Read from bin" << endl
		<< "0. Exit" << endl;
	cout << "please Enter your choice:";
}

int main(int argc, char const *argv[])
{
	Curve3D curve;
	ofstream tos("out.txt");
	ofstream bos("out.bin", ios::binary);
	ifstream tis("in.txt");
	ifstream bis("in.txt", ios::binary);
	int x, y, z;
	int choice;
	int flag = 1;
	while (flag)
	{
		PrintTable();
		cin >> choice;
		switch (choice)
		{
			case(0) :
				flag = 0;
				break;
			case(1) :
				curve.DisplayCurve(); break;
			case(2) :
				cout << "Please input x, y and z of the new point(splite by space):";
				cin >> x >> y >> z;
				curve = curve + Point3D(x, y, z);
				break; 
			case(3) :
				cout << "Please input x, y and z of the point to delete(splite by space):";
				cin >> x >> y >> z;
				curve = curve - Point3D(x, y, z);
				break;
			case(4) :
				curve.CurveLen();
				break;
			case(5) :
				curve.write_txt(tos);
				break;
			case(6) :
				curve.read_txt(tis);
				break;
			case(7) :
				curve.write_bin(bos);
				break;
			case(8) :
				curve.read_bin(bis);
				break;
			default:
				break;
		}
	}
	tos.close();
	bos.close();
	tis.close();
	bis.close();
	return 0;
}
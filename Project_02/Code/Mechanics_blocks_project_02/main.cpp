#include <iostream>
#include <iomanip>
#include "body.h"

int  main()
{
	double F = -100;
	double interval = 0.5;
	double mass1 = 10, mass2 = 3, mass3 = 1;
	double myu1 = 0.5, myu2 = 0.3, myu3 = 0.2;
	double *pos;	//pointer to body position

	Body body1 = Body(1, mass1, myu1);
	Body body2 = Body(2, mass2, myu2);
	Body body3 = Body(3, mass3, myu3);
	/*	//Can be uncommented to play with functions
	cout << endl << "=== Body1 ===" << endl;
	cout << "body1 mass : " << body1.get_mass() << " kg" << endl;
	cout << "body1 myu  : " << body1.get_myu() << endl;
	pos = body1.get_pos(body1);
	cout << "body1.get_pos(body1) = [" << pos[0] << ", " << pos[1] << "]" << endl;		//TOBE DELETED - testing: get_pos()
	
	cout << endl << "=== Body2 ===" << endl;
	cout << "body2 mass : " << body2.get_mass() << " kg" << endl;
	cout << "body2 myu  : " << body2.get_myu() << endl;
	pos = body2.get_pos(body2);

	cout << endl << "=== Body3 ===" << endl;
	cout << "body3 mass : " << body3.get_mass() << " kg" << endl;
	cout << "body3 myu  : " << body3.get_myu() << endl;
	pos = body3.get_pos(body3);

	cout << endl << "=== Experiment ===" << endl;
	*/
	//Running and reporting
	body1.update_pos(body1, body2, body3, F, interval);

	
	system("pause");
	return 0;
}
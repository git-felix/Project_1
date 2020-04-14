#include <iostream>
#include <iomanip>
#include "body.h"
using namespace std;

/** Constructors and Distructor */
Body::Body(int index, double mass, double myu)
{
	this->set_mass(mass);
	this->set_myu(myu);
	this->set_v(0);
	this->set_a(0);
	if (index == 1)				// body1 position
	{
		this->update_x(100);
		this->update_y(100);
	}
	else if (index == 2)		// body2 position
	{
		this->update_x(80);
		this->update_y(100);
	}
	else if (index == 3)		// body3 position
	{
		this->update_x(100);
		this->update_y(80);
	}

}
Body::~Body()
{
	this->set_mass(NULL);
	this->set_myu(NULL);
	this->update_x(NULL);
	this->update_y(NULL);
}

/** Getters */
double Body::get_mass()
{
	return _mass;
}
double Body::get_myu()
{
	return _myu;
}
double Body::get_x()
{
	return _x;
}
double Body::get_y()
{
	return _y;
}
double Body::get_v()
{
	return _v;
}
double Body::get_a()
{
	return _a;
}
/** Setters */
void Body::set_mass(double mass)
{
	if ((mass > 0 && mass <= 10) || mass == NULL) { _mass = mass; }
	else if (mass > 10)	{ _mass = 10;	cout << "Body mass exceeded the upper bound, set as 10 kg" << endl; }
	else if (mass < 0)	{ _mass = 0;	cout << "Body mass exceeded the lower bound, set as 0 kg" << endl; }
	else { cout << "Error: body mass is out of bounds" << endl; throw std::exception(); }
}
void Body::set_myu(double myu)
{
	if ((myu >= 0 && myu <= 0.5) || myu == NULL) { _myu = myu; }
	else if (myu > 0.5)	{ _myu = 0.5;	cout << "Body mass exceeded the upper bound, set as 10 kg" << endl; }
	else if (myu < 0)	{ _myu = 0;		cout << "Body mass exceeded the lower bound, set as 0 kg" << endl; }
	else { cout << "Error: friction coefficient is out of bounds" << endl; throw std::exception(); }
}
void Body::set_v(double v)
{
	_v = v;
}
void Body::set_a(double a)
{
	_a = a;
}

/** Position functions update */
double* Body::get_pos(Body body)
{
	static double arr[2];
	arr[0] = body.get_x();
	arr[1] = body.get_y();
	return arr;
}
void Body::update_x(double new_x)
{
	_x = new_x;
}
void Body::update_y(double new_y)
{
	_y = new_y;
}

/** Additional functions definition */
void Body::print_pos(Body body1, Body body2, Body body3, double F)
{
	cout << "[" << std::setprecision(3) << body1.get_x() << ", " << body1.get_y() << "]" << "\t";
	cout << "[" << body2.get_x() << setprecision(3) << ", " << body2.get_y() << "]" << "\t";
	cout << "[" << body3.get_x() << setprecision(3) << ", " << body3.get_y() << setprecision(3) << "]" << "\tF=" << F << endl;
}


double Body::calc_body1_acc(Body body1, Body body2, Body body3, double F)
{
	Direction dir = stand;
	if (F < 0) { dir = left; }
	else if (F > 0) { dir = right; }

	if (dir == stand)
	{
		return 0;
	}
	double abs_F = F;
	if (F < 0)
	{
		abs_F = -1 * F;
	}
	if (abs_F < (body1.get_mass() + body2.get_mass())*body1.get_myu() * 10 + body2.get_mass()*body2.get_myu() * 10)
	{
		return 0;
	}
	double a1 = (abs_F - (body1.get_mass() + body2.get_mass())*body1.get_myu() * 10 - body2.get_mass()*body2.get_myu() * 10) / body1.get_mass();
	
	if (dir == left)
	{
		return -a1;
	}
	return a1;
}

double Body::calc_body23_acc(Body body1, Body body2, Body body3, double F)
{
	Direction dir = stand;
	if (F < 0) { dir = left; }
	else if (F > 0) { dir = right; }

	double f_fric = body2.get_mass() * body2.get_myu() * 10;
	double f_push = f_fric;

	if (dir == stand)
	{
		f_push = 0;
	}
	if (dir == left)
	{
		f_push = -1 * f_push;
	}

	double a23 = (body3.get_mass()*10 - (body1.get_a()*body3.get_mass()*body3.get_myu()) - f_push + f_fric) / (body2.get_mass() + body3.get_mass());

	if (a23 <= 0)
	{
		return 0;		// not enough
	}
	return a23;
}


void Body::update_pos(Body body1, Body body2, Body body3, double F, double interval)
{

	int g = 10;
	double t = 0;
	double x1 = 0;
	double x2 = 0;

	while (t <= 10)
	{
		//accelerations update
		body1.set_a(calc_body1_acc(body1, body2, body3, F));
		body2.set_a(calc_body23_acc(body1, body2, body3, F));
		body3.set_a(calc_body23_acc(body1, body2, body3, F));

		//velocities update
		double dx_1 = ((body1.get_v() * interval) + body1.get_a() * (interval * interval) / 2);
		double dx_23 = ((body2.get_v() * interval) + body2.get_a() * (interval * interval) / 2);
		double dv_1 = body1.get_a() * interval;
		double dv_23 = body2.get_a() * interval;
		double dy_3 = dx_23;
		body1.set_v(body1.get_v() + dv_1);
		body2.set_v(body2.get_v() + dv_23);
		body3.set_v(body3.get_v() + dv_23);

		//positions update
		body1.update_x(body1.get_x() + dx_1);
		body3.update_x(body1.get_x());

		if (body2.get_a() > 0)
		{
			dy_3 = -1 * dy_3;
		}

		if (body2.get_x() + dx_23 + dx_1 < body1.get_x() && body3.get_y() + dy_3 < body1.get_y())
		{
			body2.update_x(body2.get_x() + dx_23 + dx_1);
			body3.update_y(body3.get_y() + dy_3);
		}
		else
		{
			body2.update_x(body1.get_x());
		}

		//print position
		cout << std::setprecision(2) << t << ",\t";
		//print_pos(body1, body2, body3, F);				//to see the positions
		report(body1, body2, body3, F);						//to see the report
		t += interval;

		if (F < 0)
		{
			if (F - interval < -300) { continue; }
			else { F = F - interval; continue; }
		}
		if (F + interval > 300) { continue; }
		
		F = F + interval;
	}
}


void Body::report(Body body1, Body body2, Body body3, double F)
{
	cout << std::setprecision(3) << body1.get_x() << ", " << body1.get_y() << ",\t";
	cout << setprecision(3) << body2.get_x() << ", " << body2.get_y() << ",\t";
	cout << setprecision(3) << body3.get_x() << ", " << body3.get_y() << ",\t" << F << endl;
}
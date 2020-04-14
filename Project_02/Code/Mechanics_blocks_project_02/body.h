#pragma once
using namespace std;

class Body
{
public:
	enum Direction
	{
		left = -1,
		right = 1,
		stand = 0
	};

	Body(int index, double mass, double myu);
	~Body();
	//Getters and Setters
	virtual double get_mass();
	virtual double get_myu();
	virtual double get_x();
	virtual double get_y();
	virtual double get_v();
	virtual double get_a();
	virtual void set_mass(double new_mass);
	virtual void set_myu(double new_myu);
	virtual void set_v(double v);
	virtual void set_a(double a);
	virtual double calc_body1_acc(Body body1, Body body2, Body body3, double F);
	virtual double calc_body23_acc(Body body1, Body body2, Body body3, double F);
	//Additional functions declaration
	virtual double* get_pos(Body body);										// in case of single check (not used in this project)
	virtual void report(Body body1, Body body2, Body body3, double F);
	virtual void print_pos(Body body1, Body body2, Body body3, double F);
	virtual void update_pos(Body body1, Body body2, Body body3, double F, double interval);
protected:
	virtual void update_x(double new_x);
	virtual void update_y(double new_y);
private:
	double _mass;	// body mass
	double _myu;	// friction coefficient
	double _x;		// x-axis coordinate
	double _y;		// y-axis coordinate
	double _v;		// body velocity
	double _a;		// body acceleration
};
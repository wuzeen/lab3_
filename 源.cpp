//Lab 3: 
//Revise the Adapter (object) pattern found in following (all the classes are in that one file) to be an Adapter (class) pattern.



#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// The "Target" class
// (the interface we need)
class Compound
{
protected:
	string _chemical;
	float _boilingPoint;
	float _meltingPoint;
	double _molecularWeight;
	string _molecularFormula;

public:
	Compound(string chemical)
	{
		this->_chemical = chemical;
	}

	virtual void Display()
	{
		cout << "\nCompound: " << _chemical << " ------ \n";
	}
};

// assistant function
void toLower(string& s)
{
	for (int i = 0; i < s.length(); ++i)
		s[i] = tolower(s[i]);
}

// The 'Adaptee' class
// (the old interface we want to adapt)
class ChemicalDatabank
{
public:
	float GetCriticalPoint(string compound, string point)
	{
		toLower(compound);
		// Melting Point熔点
		if (point == "M")
		{
			if (compound == "water") return 0.0f;
			if (compound == "benzene") return 5.5f;
			if (compound == "ethanol") return -114.1f;
			return 0.0f;
		}
		// Boiling Point沸点
		else
		{
			if (compound == "water") return 100.0f;
			if (compound == "benzene") return 80.1f;
			if (compound == "ethanol") return 78.3f;
			return 0.0f;
		}
	}

	string GetMolecularStructure(string compound)//化学结构
	{
		toLower(compound);
		if (compound == "water") return "H20";
		if (compound == "benzene") return "C6H6";
		if (compound == "ethanol") return "C2H5OH";
		return "";
	}

	double GetMolecularWeight(string compound)
	{
		toLower(compound);
		if (compound == "water") return 18.015;
		if (compound == "benzene") return 78.1134;
		if (compound == "ethanol") return 46.0688;
		return 0.0;
	}
};

// The 'Adapter' class
// (the implementation of the interface)
class RichCompound : public Compound,public ChemicalDatabank
{
private:
	//ChemicalDatabank* _bank;

	// Constructor
public:
	RichCompound(string name)
		: Compound(name)
	{
		//_bank = new ChemicalDatabank();

		_boilingPoint = GetCriticalPoint(_chemical, "B");//沸点
		_meltingPoint = GetCriticalPoint(_chemical, "M");//熔点
		_molecularWeight = GetMolecularWeight(_chemical);//化学权重
		_molecularFormula =GetMolecularStructure(_chemical);//化学结构式
	}

	virtual void Display()
	{
		Compound::Display();
		cout << " Formula: " << _molecularFormula << endl;
		cout << " Weight : " << _molecularWeight << endl;
		cout << " Melting Point: " << _meltingPoint << endl;
		cout << " Boiling Point: " << _boilingPoint << endl;
	}
};

int main()
{
	// Non-adapted chemical compound
	Compound* unknown = new Compound("Unknown");
	unknown->Display();

	// Adapted chemical compounds
	Compound* water = new RichCompound("Water");
	water->Display();

	Compound* benzene = new RichCompound("Benzene");
	benzene->Display();

	Compound* ethanol = new RichCompound("Ethanol");
	ethanol->Display();

	// Wait for user
	cout << "\nPress Enter key to finish...";
	cin.ignore(100, '\n');
}


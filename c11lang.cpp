//==============================================================================
// c11lang.cpp
// C11 Language Constructs
//
// C++ 11/14/17 core feature reference:
// https://msdn.microsoft.com/en-us/library/hh567368.aspx#cpp14table
//

#include <any>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include <ctime>
#include <type_traits>

//= Aliases ====================================================================
using int64 = long long;
constexpr int64 n64 = 0xF000F000F000F000;

using intvec_t = std::vector<int>;
template<class _Ty> using vec_t = std::vector<_Ty, std::allocator<_Ty>>;

intvec_t intvec;
vec_t<int> vecint;

//= any ========================================================================
// Any is a type-safe container for single values of any type.
// It can hold any type of value, including user-defined types.
// It is a type-safe union, meaning that it can hold any type of value, but
// 
// This function is ussed to test the any type and to suppress warnings
// about unused variables.
std::any dummy(std::any a, ...)
{
	return a;
}

//= Automatic type declarations ================================================
// Automatic type declarations are used to declare variables without specifying 
// their types explicitly. The type is deduced from the initializer.
// The auto keyword is used to declare a variable with an automatic type.
void sampleAuto()
{
	auto p = nullptr;
	auto n = 1;
	auto x = 3.14;
	auto pn = &n;
	auto self = sampleAuto;
	typedef void(*self_t)();
	self_t self_old = sampleAuto;
	dummy(p, n, x, pn, self, self_old);
}

//= Defaulted and deleted functions ============================================

// ToDo: Add defaulted and deleted functions

//= Functors and Lambdas =======================================================

// Template with functor
template <typename T> T Fn(T x, T y, std::function<T(T,T)> op)
{
	return op(x, y);
}

// Template implemntation with lambda
// Automatic types
int IntOpAdd(int x, int y)
{
	auto funAdd = [](int a, int b) {return a + b;};
	int ret = Fn<int>(x, y, funAdd);
	return ret;
}

// Inline lambdas and functors
void Ops()
{
	auto funDAdd = [](double x, double y) {return x + y;};
	auto funDMul = [](double x, double y) {return x * y;};

	auto dRes = 0.;
	//
	dRes = funDAdd(3., 4.);
	dRes = funDMul(5., 6.);
	//
	dRes = Fn<double>(2., 3., funDMul);
	dRes = Fn<long>(5L, 6L, [](long a, long b) {return a - b;});
	dummy(dRes);
}

// for_each iterator with lambda
void Iter()
{
	std::string s = "LetterChain\n";
	std::for_each(s.begin(), s.end(), [](char c) 
	{
		std::cout << c;
	});
}


//= Tuples =====================================================================
// Tuples are a fixed-size collection of heterogeneous values.
// They are used to group related values together.
// Tuples are similar to structs, but they do not have named members.
// Tuples are used to return multiple values from a function.
// Tuples are used to group related values together.
// Tuples are used to pass multiple values to a function.
// Tuples are used to store multiple values of different types.
// Tuples are used to store multiple values of the same type.
//
// Functions returning tuple
using xy_t = std::tuple<int, int>;
xy_t ReturnTwoInts()
{
	xy_t xyRet = { 3, 4 };
	return xyRet;
}

using ps = std::tuple<double, double>;
using fix = std::tuple<std::tm, ps>;
fix getFix()
{
	time_t timer = 0;
	ps psRet = { 34.235432, 132.141689 };
	time(&timer);
	std::tm* ptm = localtime(&timer);
	std::tm tmRet = *ptm;

	fix fixRet = {tmRet, psRet };
	return fixRet;
}

// Tuples test
// This test demonstrates the use of tuples to group related values together.
// It also demonstrates the use of structured binding to access the values in the tuple.
// It also demonstrates the use of std::get to access the values in the tuple.
// It also demonstrates the use of std::make_tuple to create a tuple.
//
void Tuples()
{
	std::tuple<int, int> index[] =
	{
		std::tuple<int,int>(1, 1),
		std::tuple<int,int>(2, 2),
		std::tuple<int,int>(3, 3)
	};

	int i = std::get<0>(index[1]);
	int j = std::get<1>(index[1]);
	dummy(i, j);

	auto time = std::make_tuple(1, 12, 15, 123, "PM");
	auto longtitude = std::make_tuple(132, 12, 146, "W");
	auto latitude = std::make_tuple(45, 17, 4631, "N");

	// Straightforward access
	std::cout
		<< "At " 
		<< std::get<0>(time) << ":"
		<< std::get<1>(time) << ":"
		<< std::get<2>(time) << "."
		<< std::get<3>(time) << " "
		<< std::get<4>(time) << " ";

	std::cout
		<< "Location was: "
		<< std::get<0>(longtitude) << " "
		<< std::get<1>(longtitude) << "."
		<< std::get<2>(longtitude) << " "
		<< std::get<3>(longtitude) << " AND "
		<< std::get<0>(latitude) << " "
		<< std::get<1>(latitude) << "."
		<< std::get<2>(latitude) << " "
		<< std::get<3>(latitude) << std::endl;
	
	// Structured binding
	std::cout
		<< "Time: "
		<< std::get<0>(getFix()).tm_hour
		<< ":"
		<< std::get<0>(getFix()).tm_min
		<< " Long: "
		<< std::get<0>(std::get<1>(getFix()))
		<< " Lat: "
		<< std::get<1>(std::get<1>(getFix()))
		<< std::endl;

	// Structured binding (C++17)
	auto [t, p] = getFix();		// See std::tie
	auto [lon, lat] = p;
	std::cout
		<< "Current Time: "
		<< t.tm_hour
		<< ":"
		<< t.tm_min
		<< " Current Long: "
		<< lon
		<< " Current Lat: "
		<< lat
		<< std::endl;
}

// Tuples with std::apply
// std::apply is used to apply a function to the elements of a tuple.
// It is used to unpack the elements of a tuple and pass them as arguments to a function.
void print(int a, double b, const std::string& c) {
    std::cout << a << ", " << b << ", " << c << std::endl;
}

// This function is used to test the std::apply function.
void tupple_apply()
{
    auto tup = std::make_tuple(42, 3.14, "hello");
    std::apply(print, tup); // Output: 42, 3.14, hello
}

//= Variadic expansions ========================================================
// Variadic arguments are used to pass a variable number of arguments to a function.
// They are used to create functions that can accept a variable number of arguments.
// Variadic templates are used to create functions that can accept a variable
// number of arguments of different types.

//- Variadic arguments ---------------------------------------------------------
// Note that MyFn is split into two components:
// 1. A non-recursive component that takes no arguments.
// 2. A recursive component that takes at least one argument.
// The non-recursive component is called when there are no arguments left to process.

// Implementation
template <typename T> void MyFnImpl(T param)
{
    auto p = param;
    std::cout << p << ";";
}

// Non-recursive component
void MyFn()
{
    std::cout << std::endl;
}

// Recursive component
template <typename T, typename... P> void MyFn(T value, P... param)
{
    MyFnImpl(value);
    MyFn(param...);
}

// Variadic template expansion sample
template <typename... Args>
void Expando(Args&&... args)
{
    // Expands the parameter pack and prints each argument
    (std::cout << ... << args) << std::endl;
}

// Variadic expansions test
// This test demonstrates the use of variadic arguments to pass a variable number
// of arguments to a function. It also demonstrates the use of variadic templates.
void VariadicFun()
{
	MyFn(2, 3.14, "Four");
	MyFn("Hello", ' ', "World");
}


//- Variadic template ----------------------------------------------------------
// i_t is a placeholder meaning at least one type is required.
// i_p is the variadic part
//

template <typename T, typename... P> class CVarTem
{
public:
	CVarTem(T i_t) : m_t(i_t) {}
	T VarArg(T i_t, P&... i_p)
	{
		MyFn(i_t, i_p...);
		m_tp = { i_t, i_p... };
		return i_t;
	}

protected:
	T m_t;

private:
	std::tuple<T, P...> m_tp;
};


void VariadicTemplate()
{
	using Var = CVarTem<int, std::string>;
	Var v(0);
	std::string str = "hello";
	v.VarArg(1, str);
}

//==============================================================================
// Main entry point
//==============================================================================
int main()
{
    std::cout << "Sample: auto" << std::endl;
    sampleAuto();

    std::cout << "\nSample: Functors and Lambdas" << std::endl;
    Ops();

    std::cout << "\nSample: for_each with lambda" << std::endl;
    Iter();

    std::cout << "\nSample: Tuples" << std::endl;
    Tuples();


	std::cout << "\nSample: Tuples with std::apply" << std::endl;
	tupple_apply();

	std::cout << "\nSample: Variadic Template" << std::endl;
	VariadicTemplate();

	std::cout << "\nSample: Variadic Arguments" << std::endl;
	MyFn(2, 3.14, "Four");
	MyFn("Hello", ' ', "World");

    std::cout << "\nSample: Variadic Templates" << std::endl;
    VariadicFun();

	std::cout << "\nSample: Variadic Template Expansion" << std::endl;
	Expando("Sum: ", 1, " + ", 2, " = ", 3);	
	return 0;
}


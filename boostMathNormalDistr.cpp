#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/gamma.hpp>
#include <boost/math/distributions.hpp> 

#include <vector>
#include <iostream>
using namespace std;


int main()
{
	using namespace boost::math;

	normal_distribution<> myNormal (1.0, 10.0); // double �� ���������, �������, ����������
	
	// ����������� � ����������� ����������
	cout << "Mean: " << mean(myNormal) << ", standard deviation: " << standard_deviation(myNormal) << endl;

	double x = 10.25;

	cout << "pdf: " << pdf(myNormal, x) << endl; // ������� ��������� �����������
	cout << "cdf: " << cdf(myNormal, x) << endl; // ������� ������������ �����������

	normal_distribution<float> myNormal2; // N (0, 1)
	cout << "Mean: " << mean(myNormal2) << ", standard deviation: " << standard_deviation(myNormal2) << endl;
	
	cout << "pdf: " << pdf(myNormal2, x) << endl;
	cout << "cdf: " << cdf(myNormal2, x) << endl;

	cout.precision(10); // �������� - ����� ������ ����� �������

	
	cout << "\n***normal distribution: \n";
	cout << "mean: " << mean(myNormal) << endl;							// ��� ��������
	cout << "variance: " << variance(myNormal) << endl;					// ���������
	cout << "median: " << median(myNormal) << endl;						// �������
	cout << "mode: " << mode(myNormal) << endl;							// ���� (�������� ��������� ��������)
	cout << "kurtosis excess: " << kurtosis_excess(myNormal) << endl;   // ���������� �������
	cout << "kurtosis: " << kurtosis(myNormal) << endl;					// �������
	cout << "characteristic function: " << chf(myNormal, x) << endl;
	cout << "hazard: " << hazard(myNormal, x) << endl;

	// Gamma �������������
	double alpha = 3.0; // Shape parameter, k
	double beta = 0.5;	// Scale parameter, theta
	gamma_distribution<double> myGamma(alpha, beta);

	double val = 13.0;
	cout << endl <<  "pdf: " << pdf(myGamma, val) << endl;
	cout << "cdf: " << cdf(myGamma, val) << endl;

	vector<double> pdfList;
	vector<double> cdfList;

	double start = 0.0;
	double end = 10.0;
	long N = 30;	

	val = 0.0;
	double h = (end - start) / double(N);

	for (long j = 1; j <= N; ++j)
	{
		pdfList.push_back(pdf(myGamma, val));
		cdfList.push_back(cdf(myGamma, val));

		val += h;
	}

	for (long j = 0; j < pdfList.size(); ++j)
	{
		cout << pdfList[j] << ", ";

	}

	cout << "***" << endl;

	for (long j = 0; j < cdfList.size(); ++j)
	{
		cout << cdfList[j] << ", ";

	}

	return 0;
}

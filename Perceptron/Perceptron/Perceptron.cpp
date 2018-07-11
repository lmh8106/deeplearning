// Perceptron.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.

#include "stdafx.h"


// Single Layer Neural Network Example (Perceptrons (AND, NAND, OR, XOR, n Neurons)
// 2018.07.12, coded by AIVIA (email : lmh8106@gmail.com)

class Neuron {
public:
	Neuron()
	{
		x = 0.0f;
		w = 0.0f;
		r = 0.0f;
	}
	~Neuron() {

	}
public:
	double x; // �Է°�
	double w; // ����ġ 
	double r; // x*w ��� ���� ���� 

	double multiplyElements() {
		r = w*x; 
		return r; 
	}


	double makeDecisionForNeuronFlowOrNot(double theta) {
		if (r > theta) {
			return 1.0f; 
		}
		else if (r <= theta) {
			return 0.0f; 
		}

		return 0.0f; 
	}

	double makeDecisionForNeuronFlowOrNot(Neuron *input_neurons, int number_of_neurons, double theta) {

		double sum_of_all_neurons_value = 0.0f;

		// 1. �Է´������� ������ �ִ� ���� ��ҵ��� ��� ���Ѵ�. w*x
		// 2. �׷����� �ش� ���� ��� ���Ѵ�. 
		// 3. �׷����� ����� �����Ѵ�.
		for (int i = 0; i < number_of_neurons; i++) {
			sum_of_all_neurons_value +=input_neurons[i].multiplyElements();
		}

		cout << "�Է� ������ �Ѽ��� =" << number_of_neurons << " �� �Դϴ�." << endl;
		cout << "�Ӱ谪(Threshold)�� theta ���� =" << theta << " �Դϴ�" << endl;
		cout << "�Է� ������ w*x �� ���ѵ� �̵��� ��� ���� ���� = " << sum_of_all_neurons_value << " �Դϴ�." << endl;

		if (sum_of_all_neurons_value > theta) {

			cout << "�Է� ������ ���� ������ theta ������ Ů�ϴ�." << endl;
			cout << "����, ��� ���� 1 �Դϴ�." << endl;
			return 1.0f;
		}
		else if (sum_of_all_neurons_value <= theta) {
			cout << "�Է� ������ ���� ������ theta ������ �۽��ϴ�." << endl;
			cout << "����, ��� ���� 0 �Դϴ�." << endl;
			return 0.0f;
		}
		return 0.0f;
	}

};



// AND ����Ʈ�� ������. 
// ���� : y = 0 (w1*x1 + w2*x2 <= theta), y = 1 (w1*x1 + w2*x2 > theta)
double gate_AND(Neuron* first_neuron, Neuron* second_neuron, double theta) {
	double sum = 0.0f;

	sum = (double)(first_neuron->w*first_neuron->x) + (second_neuron->w*second_neuron->x);
	if (sum <= theta) {
		return 0.0f;
	}
	else if (sum > theta) {
		return 1.0f;
	}

	return 0;
}

// AND ����Ʈ�� ������. 
// ���� : y = 0 (b + w1*x1 + w2*x2 <= 0), y = 1 (b + w1*x1 + w2*x2 > 0)
// �����ʿ� �ִ� theta �� 0 ���� ����� ����, �纯�׿� �ִ� theta�� ���ش�. 
// ���� ���� y = 0 (w1*x1 + w2*x2 <= theta) �� ��� ==>  y = 0 (-theta + w1*x1 + w2*x2 <= 0) �ε�, -theta �� b(Bias)�� ġȯ�Ͽ� ������ ǥ���Ѵ�. 
// ����������  y = 1 (w1*x1 + w2*x2 > theta)  �� ��� ==>  y = 1 (-theta + w1*x1 + w2*x2 > 0) �ε�, -theta �� b(Bias)�� ġȯ�Ͽ� ������ ǥ���Ѵ�.
double gate_AND_with_Bias(Neuron* first_neuron, Neuron* second_neuron, double theta) {

	double sum = 0.0f;
	double bias = theta*(-1);

	sum = (double)(bias + (first_neuron->w*first_neuron->x) + (second_neuron->w*second_neuron->x));
	if (sum <= 0) {
		return 0.0f;
	}
	else if (sum > 0) {
		return 1.0f;
	}

	return 0;
}

// NAND ����Ʈ�� ������. 
// AND �� NAND �� ���̴� ��� ������� �ݴ��̴�. 
// AND �� NAND �Լ� ���� ���� �ڵ�� ���� �����ϴ�. 
// ���� �ڵ带 ���� �˰�����, NAND �� �����ֱ� ���ؼ�, ����ġ�� bias ������ �����Ͽ� NAND ����Ʈ�� �����ش�. 
double gate_NAND(Neuron* first_neuron, Neuron* second_neuron, double theta) {

	double sum = 0.0f;
	double bias = theta*(-1);

	sum = (double)(bias + (first_neuron->w*first_neuron->x) + (second_neuron->w*second_neuron->x));
	if (sum <= 0) {
		return 0.0f;
	}
	else if (sum > 0) {
		return 1.0f;
	}

	return 0;
}

// OR ����Ʈ�� ������. 
// OR ����Ʈ�� ������. 
// AND �� OR �Լ� ���� ���� �ڵ�� ���� �����ϴ�. 
// ���� �ڵ带 ���� �˰�����, OR �� �����ֱ� ���ؼ�, ����ġ�� bias ������ �����Ͽ� OR ����Ʈ�� �����ش�. 
double gate_OR(Neuron* first_neuron, Neuron* second_neuron, double theta) {

	double sum = 0.0f;
	double bias = theta*(-1);

	sum = (double)(bias + (first_neuron->w*first_neuron->x) + (second_neuron->w*second_neuron->x));
	if (sum <= 0) {
		return 0.0f;
	}
	else if (sum > 0) {
		return 1.0f;
	}

	return 0;
}



void example_gate_AND_perceptron() {
	cout << "AND gate example " << endl; 

	Neuron *first_neuron = new Neuron();
	Neuron *second_neuron = new Neuron();
	first_neuron->w = 0.5f;
	first_neuron->x = 0.0f;
	second_neuron->w = 0.5f;
	second_neuron->x = 0.0f;
	cout << "fx=" << first_neuron->x << " fw=" << first_neuron->w << " sx=" << second_neuron->x << " sw=" << second_neuron->w << " output_y = " << gate_AND_with_Bias(first_neuron, second_neuron, 0.7f) << endl;

	first_neuron->w = 0.5f;
	first_neuron->x = 1.0f;
	second_neuron->w = 0.5f;
	second_neuron->x = 0.0f;
	cout << "fx=" << first_neuron->x << " fw=" << first_neuron->w << " sx=" << second_neuron->x << " sw=" << second_neuron->w << " output_y = " << gate_AND_with_Bias(first_neuron, second_neuron, 0.7f) << endl;

	first_neuron->w = 0.5f;
	first_neuron->x = 0.0f;
	second_neuron->w = 0.5f;
	second_neuron->x = 1.0f;
	cout << "fx=" << first_neuron->x << " fw=" << first_neuron->w << " sx=" << second_neuron->x << " sw=" << second_neuron->w << " output_y = " << gate_AND_with_Bias(first_neuron, second_neuron, 0.7f) << endl;

	first_neuron->w = 0.5f;
	first_neuron->x = 1.0f;
	second_neuron->w = 0.5f;
	second_neuron->x = 1.0f;
	cout << "fx=" << first_neuron->x << " fw=" << first_neuron->w << " sx=" << second_neuron->x << " sw=" << second_neuron->w << " output_y = " << gate_AND_with_Bias(first_neuron, second_neuron, 0.7f) << endl;

	cout << endl;

	delete first_neuron; first_neuron = NULL;
	delete second_neuron; second_neuron = NULL;

}

void example_gate_NAND_perceptron() {
	cout << "NAND gate example " << endl;

	Neuron *first_neuron = new Neuron();
	Neuron *second_neuron = new Neuron();
	first_neuron->w = -0.5f;
	first_neuron->x = 0.0f;
	second_neuron->w = -0.5f;
	second_neuron->x = 0.0f;
	cout << "fx=" << first_neuron->x << " fw=" << first_neuron->w << " sx=" << second_neuron->x << " sw=" << second_neuron->w << " output_y = " << gate_NAND(first_neuron, second_neuron, -0.7f) << endl;

	first_neuron->w = -0.5f;
	first_neuron->x = 1.0f;
	second_neuron->w =-0.5f;
	second_neuron->x = 0.0f;
	cout << "fx=" << first_neuron->x << " fw=" << first_neuron->w << " sx=" << second_neuron->x << " sw=" << second_neuron->w << " output_y = " << gate_NAND(first_neuron, second_neuron, -0.7f) << endl;

	first_neuron->w = -0.5f;
	first_neuron->x = 0.0f;
	second_neuron->w = -0.5f;
	second_neuron->x = 1.0f;
	cout << "fx=" << first_neuron->x << " fw=" << first_neuron->w << " sx=" << second_neuron->x << " sw=" << second_neuron->w << " output_y = " << gate_NAND(first_neuron, second_neuron, -0.7f) << endl;

	first_neuron->w = -0.5f;
	first_neuron->x = 1.0f;
	second_neuron->w = -0.5f;
	second_neuron->x = 1.0f;
	cout << "fx=" << first_neuron->x << " fw=" << first_neuron->w << " sx=" << second_neuron->x << " sw=" << second_neuron->w << " output_y = " << gate_NAND(first_neuron, second_neuron, -0.7f) << endl;

	cout << endl;

	delete first_neuron; first_neuron = NULL;
	delete second_neuron; second_neuron = NULL;

}

void example_gate_OR_perceptron() {
	cout << "OR gate example " << endl;

	Neuron *first_neuron = new Neuron();
	Neuron *second_neuron = new Neuron();
	first_neuron->w = 0.5f;
	first_neuron->x = 0.0f;
	second_neuron->w = 0.5f;
	second_neuron->x = 0.0f;
	cout << "fx=" << first_neuron->x << " fw=" << first_neuron->w << " sx=" << second_neuron->x << " sw=" << second_neuron->w << " output_y = " << gate_OR(first_neuron, second_neuron, 0.2f) << endl;

	first_neuron->w = 0.5f;
	first_neuron->x = 1.0f;
	second_neuron->w = 0.5f;
	second_neuron->x = 0.0f;
	cout << "fx=" << first_neuron->x << " fw=" << first_neuron->w << " sx=" << second_neuron->x << " sw=" << second_neuron->w << " output_y = " << gate_OR(first_neuron, second_neuron, 0.2f) << endl;

	first_neuron->w = 0.5f;
	first_neuron->x = 0.0f;
	second_neuron->w = 0.5f;
	second_neuron->x = 1.0f;
	cout << "fx=" << first_neuron->x << " fw=" << first_neuron->w << " sx=" << second_neuron->x << " sw=" << second_neuron->w << " output_y = " << gate_OR(first_neuron, second_neuron, 0.2f) << endl;

	first_neuron->w = 0.5f;
	first_neuron->x = 1.0f;
	second_neuron->w = 0.5f;
	second_neuron->x = 1.0f;
	cout << "fx=" << first_neuron->x << " fw=" << first_neuron->w << " sx=" << second_neuron->x << " sw=" << second_neuron->w << " output_y = " << gate_OR(first_neuron, second_neuron, 0.2f) << endl;

	cout << endl;

	delete first_neuron; first_neuron = NULL;
	delete second_neuron; second_neuron = NULL;

}

void example_gate_XOR_perceptron() {

	cout << "XOR gate example " << endl;

	Neuron *first_neuron = new Neuron();
	Neuron *second_neuron = new Neuron();
	double output_of_gate_NAND = 0.0f;
	double output_of_gate_OR = 0.0f;
	double y = 0.0f;

	first_neuron->w = -0.5f;
	first_neuron->x = 0.0f;
	second_neuron->w = -0.5f;
	second_neuron->x = 0.0f;

	output_of_gate_NAND = gate_NAND(first_neuron, second_neuron, -0.7f);


	first_neuron->w = 0.5f;
	first_neuron->x = 0.0f;
	second_neuron->w = 0.5f;
	second_neuron->x = 0.0f;
	
	output_of_gate_OR = gate_OR(first_neuron, second_neuron, 0.2f);

	first_neuron->w = 0.5f;
	first_neuron->x = output_of_gate_NAND;
	second_neuron->w = 0.5f;
	second_neuron->x = output_of_gate_OR;

	y = gate_AND_with_Bias(first_neuron, second_neuron, 0.7f);

	cout << "[ first_neuron_x(x1) = 0, second_neuron_x(x2) = 0 ]" << " [ output_of_gate_NAND(s1) = " << output_of_gate_NAND << ", output_of_gate_OR(s2) = " << output_of_gate_OR << " ], output_of_gate_AND(y) = " << y << endl;



	first_neuron->w = -0.5f;
	first_neuron->x = 1.0f;
	second_neuron->w = -0.5f;
	second_neuron->x = 0.0f;

	output_of_gate_NAND = gate_NAND(first_neuron, second_neuron, -0.7f);


	first_neuron->w = 0.5f;
	first_neuron->x = 1.0f;
	second_neuron->w = 0.5f;
	second_neuron->x = 0.0f;

	output_of_gate_OR = gate_OR(first_neuron, second_neuron, 0.2f);

	first_neuron->w = 0.5f;
	first_neuron->x = output_of_gate_NAND;
	second_neuron->w = 0.5f;
	second_neuron->x = output_of_gate_OR;

	y = gate_AND_with_Bias(first_neuron, second_neuron, 0.7f);

	cout << "[ first_neuron_x(x1) = 1, second_neuron_x(x2) = 0 ]" << " [ output_of_gate_NAND(s1) = " << output_of_gate_NAND << ", output_of_gate_OR(s2) = " << output_of_gate_OR << " ], output_of_gate_AND(y) = " << y << endl;



	first_neuron->w = -0.5f;
	first_neuron->x = 0.0f;
	second_neuron->w = -0.5f;
	second_neuron->x = 1.0f;

	output_of_gate_NAND = gate_NAND(first_neuron, second_neuron, -0.7f);


	first_neuron->w = 0.5f;
	first_neuron->x = 0.0f;
	second_neuron->w = 0.5f;
	second_neuron->x = 1.0f;

	output_of_gate_OR = gate_OR(first_neuron, second_neuron, 0.2f);

	first_neuron->w = 0.5f;
	first_neuron->x = output_of_gate_NAND;
	second_neuron->w = 0.5f;
	second_neuron->x = output_of_gate_OR;

	y = gate_AND_with_Bias(first_neuron, second_neuron, 0.7f);

	cout << "[ first_neuron_x(x1) = 0, second_neuron_x(x2) = 1 ]" << " [ output_of_gate_NAND(s1) = " << output_of_gate_NAND << ", output_of_gate_OR(s2) = " << output_of_gate_OR << " ], output_of_gate_AND(y) = " << y << endl;



	first_neuron->w = -0.5f;
	first_neuron->x = 1.0f;
	second_neuron->w = -0.5f;
	second_neuron->x = 1.0f;

	output_of_gate_NAND = gate_NAND(first_neuron, second_neuron, -0.7f);


	first_neuron->w = 0.5f;
	first_neuron->x = 1.0f;
	second_neuron->w = 0.5f;
	second_neuron->x = 1.0f;

	output_of_gate_OR = gate_OR(first_neuron, second_neuron, 0.2f);

	first_neuron->w = 0.5f;
	first_neuron->x = output_of_gate_NAND;
	second_neuron->w = 0.5f;
	second_neuron->x = output_of_gate_OR;

	y = gate_AND_with_Bias(first_neuron, second_neuron, 0.7f);

	cout << "[ first_neuron_x(x1) = 1, second_neuron_x(x2) = 1 ]" << " [ output_of_gate_NAND(s1) = " << output_of_gate_NAND << ", output_of_gate_OR(s2) = " << output_of_gate_OR << " ], output_of_gate_AND(y) = " << y << endl;

	cout << endl;

	delete first_neuron; first_neuron = NULL;
	delete second_neuron; second_neuron = NULL;


}

void example_perceptron_with_n_neurons() {
	const int number_of_nurons = 6;

	Neuron *input_neurons = new Neuron[number_of_nurons];
	Neuron *output_neuron = new Neuron;

	// 1. �Է� ������ �����Ѵ�. 
	input_neurons[0].x = 0.2f;
	input_neurons[0].w = 0.05f;

	input_neurons[1].x = 0.16f;
	input_neurons[1].w = 0.35f;

	input_neurons[2].x = 0.14f;
	input_neurons[2].w = 0.25f;

	input_neurons[3].x = 0.3f;
	input_neurons[3].w = 0.15f;

	input_neurons[4].x = 0.08f;
	input_neurons[4].w = 0.1f;

	input_neurons[5].x = 0.12f;
	input_neurons[5].w = 0.1f;

	// 2. �Է� ������ �����ϰ�, ������ �帧�� �����Ѵ�. 
	// 3. �׽�Ʈ threshold, 0.7f;
	output_neuron->makeDecisionForNeuronFlowOrNot(input_neurons, number_of_nurons, 0.7f);

	cout << endl;

	// 4. �׽�Ʈ threshold, 0.1f;
	output_neuron->makeDecisionForNeuronFlowOrNot(input_neurons, number_of_nurons, 0.1f);

	// 5. ����� �޸� ���� �Ѵ�. 
	delete[] input_neurons;
	input_neurons = NULL;

	delete output_neuron;
	output_neuron = NULL;
}


int main()
{
	example_gate_AND_perceptron();

	example_gate_NAND_perceptron();

	example_gate_OR_perceptron();

	example_gate_XOR_perceptron();

	example_perceptron_with_n_neurons();

    return 0;
}


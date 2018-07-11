// Perceptron.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.

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
	double x; // 입력값
	double w; // 가중치 
	double r; // x*w 결과 저장 변수 

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

		// 1. 입력뉴런들이 가지고 있는 내부 요소들을 모두 곱한다. w*x
		// 2. 그런다음 해당 값을 모두 더한다. 
		// 3. 그런다음 출력을 결정한다.
		for (int i = 0; i < number_of_neurons; i++) {
			sum_of_all_neurons_value +=input_neurons[i].multiplyElements();
		}

		cout << "입력 뉴런의 총수는 =" << number_of_neurons << " 개 입니다." << endl;
		cout << "임계값(Threshold)인 theta 값은 =" << theta << " 입니다" << endl;
		cout << "입력 뉴런의 w*x 를 곱한뒤 이들을 모두 더한 값은 = " << sum_of_all_neurons_value << " 입니다." << endl;

		if (sum_of_all_neurons_value > theta) {

			cout << "입력 뉴런의 계산된 총합이 theta 값보다 큽니다." << endl;
			cout << "따라서, 출력 값은 1 입니다." << endl;
			return 1.0f;
		}
		else if (sum_of_all_neurons_value <= theta) {
			cout << "입력 뉴런의 계산된 총합이 theta 값보다 작습니다." << endl;
			cout << "따라서, 출력 값은 0 입니다." << endl;
			return 0.0f;
		}
		return 0.0f;
	}

};



// AND 게이트를 구현함. 
// 수식 : y = 0 (w1*x1 + w2*x2 <= theta), y = 1 (w1*x1 + w2*x2 > theta)
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

// AND 게이트를 구현함. 
// 수식 : y = 0 (b + w1*x1 + w2*x2 <= 0), y = 1 (b + w1*x1 + w2*x2 > 0)
// 오른쪽에 있던 theta 를 0 으로 만들기 위해, 양변항에 있던 theta를 빼준다. 
// 따라서 수식 y = 0 (w1*x1 + w2*x2 <= theta) 의 경우 ==>  y = 0 (-theta + w1*x1 + w2*x2 <= 0) 인데, -theta 를 b(Bias)로 치환하여 수식을 표현한다. 
// 마찬가지로  y = 1 (w1*x1 + w2*x2 > theta)  의 경우 ==>  y = 1 (-theta + w1*x1 + w2*x2 > 0) 인데, -theta 를 b(Bias)로 치환하여 수식을 표현한다.
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

// NAND 게이트를 구현함. 
// AND 와 NAND 의 차이는 출력 결과값이 반대이다. 
// AND 와 NAND 함수 내부 구현 코드는 완전 동일하다. 
// 샘플 코드를 보면 알겠지만, NAND 를 보여주기 위해서, 가중치와 bias 값만을 변경하여 NAND 게이트를 보여준다. 
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

// OR 게이트를 구현함. 
// OR 게이트를 구현함. 
// AND 와 OR 함수 내부 구현 코드는 완전 동일하다. 
// 샘플 코드를 보면 알겠지만, OR 를 보여주기 위해서, 가중치와 bias 값만을 변경하여 OR 게이트를 보여준다. 
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

	// 1. 입력 뉴런을 설정한다. 
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

	// 2. 입력 뉴런을 전달하고, 뉴런의 흐름을 결정한다. 
	// 3. 테스트 threshold, 0.7f;
	output_neuron->makeDecisionForNeuronFlowOrNot(input_neurons, number_of_nurons, 0.7f);

	cout << endl;

	// 4. 테스트 threshold, 0.1f;
	output_neuron->makeDecisionForNeuronFlowOrNot(input_neurons, number_of_nurons, 0.1f);

	// 5. 사용한 메모리 해제 한다. 
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


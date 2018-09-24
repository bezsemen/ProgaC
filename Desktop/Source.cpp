#include<stdio.h>//std
#include<math.h>
#include<assert.h>

const int NmeasUI = 36;
const int NmeasD = 10;
const float Pi = 3.14;
const float ErrorD = 0.01;//mm
const float ErrorV = 0.75;//mV
const float ErrorI = 0.4;//mA
const long long ResistV = pow(10, 7);
const float ErrorL = 0.1;//cm

float area(float *diameter) {
	return Pi**diameter**diameter / 4;
}

float errorS(float *diameter) {
	return 2 * ErrorD / *diameter;
}

float avgD(float *mD){
	float sum=0;
	for (int i = 0; i < NmeasD; i++) {
		sum += mD[i];
	}
	return sum / NmeasD;
}

void rAvg(float* mU,float* mI,float *rAvgL20,float* rAvgL30, float* rAvgL50) {
	int SumUI = 0,SumII=0;
	for (int i = 0; i < 12; i++) {
		SumUI += mU[i]*mI[i];
		SumII += mI[i] * mI[i];
	};
	*rAvgL20=SumUI / SumII;
	int SumUI = 0, SumII = 0;
	for (int i = 12; i < 24; i++) {
		SumUI += mU[i] * mI[i];
		SumII += mI[i] * mI[i];
	};
	*rAvgL30 = SumUI / SumII;
	int SumUI = 0, SumII = 0;
	for (int i = 24; i < 36; i++) {
		SumUI += mU[i] * mI[i];
		SumII += mI[i] * mI[i];
	};
	*rAvgL50 = SumUI / SumII;
}


void errorRand_rAvg(float* mU, float* mI, float* RavgL20, float* RavgL30, float* RavgL50) {
	int SumUU = 0, SumII = 0;
	for (int i = 0; i < 12; i++) {
		SumUU += mU[i] * mU[i];
		SumII += mI[i] * mI[i];
	};
	*RavgL20=sqrt(12)*sqrt(SumUU / SumII - *RavgL20**RavgL20);
	int SumUU = 0, SumII = 0;
	for (int i = 12; i < 24; i++) {
		SumUU += mU[i] * mU[i];
		SumII += mI[i] * mI[i];
	};
	*RavgL30 = sqrt(12)*sqrt(SumUU / SumII - *RavgL30**RavgL30);
	int SumUU = 0, SumII = 0;
	for (int i = 24; i < 36; i++) {
		SumUU += mU[i] * mU[i];
		SumII += mI[i] * mI[i];
	};
	*RavgL50 = sqrt(12)*sqrt(SumUU / SumII - *RavgL50**RavgL50);
}

void v_max(float* mU, float* VmaxL20, float* VmaxL30, float* VmaxL50) {
	int Vmax = 0;
	for (int i = 0; i < 12; i++) {
		if (mU[i] > Vmax) {
			Vmax = mU[i];
		}
	}
	*VmaxL20 = Vmax;
	int Vmax = 0;
	for (int i = 12; i <24; i++) {
		if (mU[i] > Vmax) {
			Vmax = mU[i];
		}
	}
	*VmaxL30 = Vmax;
	int Vmax = 0;
	for (int i = 24; i < 36; i++) {
		if (mU[i] > Vmax) {
			Vmax = mU[i];
		}
	}
	*VmaxL50 = Vmax;
}


void i_max(float* mI,float *ImaxL20, float *ImaxL30, float *ImaxL50) {
	int Imax = 0;
	for (int i = 0; i < 12; i++) {
		if (mI[i] > Imax) {
			Imax = mI[i];
		}
	}
	int Imax = 0;
	for (int i = 12; i < 24; i++) {
		if (mI[i] > Imax) {
			Imax = mI[i];
		}
	}
	int Imax = 0;
	for (int i = 0; i < 12; i++) {
		if (mI[i] > Imax) {
			Imax = mI[i];
		}
	}
}

float errorSyst_rAvgL20(float* VMaxL20, float* IMaxL20, float* RavgL20) {
	return *RavgL20*sqrt(pow(ErrorV, 2) / pow(*VMaxL20, 2) + pow(ErrorI, 2) / pow(*IMaxL20, 2));
}

float errorSyst_rAvgL30(float* VMaxL30, float* IMaxL30, float* RavgL30) {
	return *RavgL30*sqrt(pow(ErrorV, 2) / pow(*VMaxL30, 2) + pow(ErrorI, 2) / pow(*IMaxL30, 2));
}

float errorSyst_rAvgL50(float* VMaxL50, float* IMaxL50, float* RavgL50) {
	return *RavgL50*sqrt(pow(ErrorV, 2) / pow(*VMaxL50, 2) + pow(ErrorI, 2) / pow(*IMaxL50, 2));
}

float error_rAvgL20(float* ErrorRand_rAvgL20, float* ErrorSyst_rAvgL20) {
	return sqrt(pow(*ErrorRand_rAvgL20, 2) + pow(*ErrorSyst_rAvgL20, 2));
}

float error_rAvgL30(float* ErrorRand_rAvgL30, float* ErrorSyst_rAvgL30) {
	return sqrt(pow(*ErrorRand_rAvgL30, 2) + pow(*ErrorSyst_rAvgL30, 2));
}

float error_rAvgL50(float* ErrorRand_rAvgL50, float* ErrorSyst_rAvgL50) {
	return sqrt(pow(*ErrorRand_rAvgL50, 2) + pow(*ErrorSyst_rAvgL50, 2));
}

float resistExactL20(float* RavgL20) {
	return *RavgL20 + pow(*RavgL20, 2) / ResistV;
}

float resistExactL30(float* RavgL30) {
	return *RavgL30 + pow(*RavgL30, 2) / ResistV;
}

float resistExactL50(float* RavgL50) {
	return *RavgL50 + pow(*RavgL50, 2) / ResistV;
}

float specific_rAvgL20(float* ResistExactL20, float* Area) {
	return *ResistExactL20**Area / 20;
}

float specific_rAvgL30(float* ResistExactL30, float* Area) {
	return *ResistExactL30**Area / 20;
}

float specific_rAvgL50(float* ResistExactL50, float* Area) {
	return *ResistExactL50**Area / 20;
}

float errorSpecific_rAvgL20(float* specific_rAvgL20, float* ErrorS, float* Error_rAvgL20, float* ResistExact) {
	return *specific_rAvgL20*sqrt(pow(*Error_rAvgL20 / (*ResistExact), 2) + pow(*ErrorS, 2) + pow(ErrorL / 20, 2));
}

float errorSpecific_rAvgL30(float* specific_rAvgL30, float* ErrorS, float* Error_rAvgL30, float* ResistExact) {
	return *specific_rAvgL30*sqrt(pow(*Error_rAvgL30 / (*ResistExact), 2) + pow(*ErrorS, 2) + pow(ErrorL / 20, 2));
}

float errorSpecific_rAvgL50(float* specific_rAvgL50, float* ErrorS, float* Error_rAvgL50, float* ResistExact) {
	return *specific_rAvgL50*sqrt(pow(*Error_rAvgL50 / (*ResistExact), 2) + pow(*ErrorS, 2) + pow(ErrorL / 20, 2));
}

int main() {
	float mU[NmeasUI];
	float mI[NmeasUI];
	float mD[NmeasD];
	FILE *f1 = fopen("laba.txt", "r");
	FILE *f3 = fopen("diametr.txt", "r");
	FILE *f2 = fopen("labaoutput.txt", "w");
	int i;
	for (i = 0; i < NmeasUI; i++) {
		assert(fscanf(f1, "%f %f", &mU[i], &mI[i]));
	}
	for (int i = 0; i < NmeasD; i++) {
		assert(fscanf(f3, "%f",&mD[i]));
	};
	float diameter = avgD(mD);
	float ErrorS = errorS(&diameter);
	float Area = area(&diameter);
	float RavgL20, RavgL30, RavgL50;
	rAvg(mU, mI, &RavgL20,&RavgL30, &RavgL50);
	float ErrorRand_rAvgL20, ErrorRand_rAvgL30, ErrorRand_rAvgL50;
	errorRand_rAvg(mU, mI, &RavgL20, &RavgL30, &RavgL50);
	float VmaxL20, VmaxL30, VmaxL50;
	v_max(mU, &VmaxL20, &VmaxL30, &VmaxL50)

	float ImaxL20, ImaxL30, ImaxL50;
	
	float ErrorSyst_rAvgL20 = errorSyst_rAvgL20(&VMaxL20, &IMaxL20, &RavgL20);
	float ErrorSyst_rAvgL30 = errorSyst_rAvgL30(&VMaxL30, &IMaxL30, &RavgL30);
	float ErrorSyst_rAvgL50 = errorSyst_rAvgL50(&VMaxL50, &IMaxL50, &RavgL50);
	
	float Error_rAvgL20 = error_rAvgL20(&ErrorRand_rAvgL20, &ErrorSyst_rAvgL20);
	float Error_rAvgL30 = error_rAvgL30(&ErrorRand_rAvgL30, &ErrorSyst_rAvgL30);
	float Error_rAvgL50 = error_rAvgL50(&ErrorRand_rAvgL50, &ErrorSyst_rAvgL50);

	float ResistExactL20 = resistExactL20(&RavgL20);
	float ResistExactL30 = resistExactL30(&RavgL30);
	float ResistExactL50 = resistExactL50(&RavgL50);

	float Specific_rAvgL20 = specific_rAvgL20(&ResistExactL20, &Area);
	float Specific_rAvgL30 = specific_rAvgL30(&ResistExactL30, &Area);
	float Specific_rAvgL50 = specific_rAvgL50(&ResistExactL50, &Area);

	float ErrorSpecific_rAvgL20 = errorSpecific_rAvgL20(&Specific_rAvgL20, &ErrorS, &Error_rAvgL20, &ResistExactL20);
	float ErrorSpecific_rAvgL30 = errorSpecific_rAvgL30(&Specific_rAvgL30, &ErrorS, &Error_rAvgL30, &ResistExactL30);
	float ErrorSpecific_rAvgL50 = errorSpecific_rAvgL50(&Specific_rAvgL50, &ErrorS, &Error_rAvgL50, &ResistExactL50);

	fprintf(f2, "The results of resistance measurements for l=20cm\n");
	fprintf(f2, "%5.6f\n", RavgL20);
	fprintf(f2, "%5.6f\n", ResistExactL20," Om");
	fprintf(f2, "%5.6f\n", ErrorRand_rAvgL20, " Om");
	fprintf(f2, "%5.6f\n", ErrorSyst_rAvgL20, " Om");
	fprintf(f2, "%5.6f\n", ErrorSpecific_rAvgL20, " Om");
}


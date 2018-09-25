#include<stdio.h>
#include<math.h>
#include<stdlib.h>

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
	int SumUI = 0,SumII = 0;
	for (int i = 0; i < 12; i++) {
		SumUI += mU[i]*mI[i];
		SumII += mI[i] * mI[i];
	};
	*rAvgL20=SumUI / SumII;
	SumUI = 0; SumII = 0;
	for (int i = 12; i < 24; i++) {
		SumUI += mU[i] * mI[i];
		SumII += mI[i] * mI[i];
	};
	*rAvgL30 = SumUI / SumII;
	SumUI = 0; SumII = 0;
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
	SumUU = 0; SumII = 0;
	for (int i = 12; i < 24; i++) {
		SumUU += mU[i] * mU[i];
		SumII += mI[i] * mI[i];
	};
	*RavgL30 = sqrt(12)*sqrt(SumUU / SumII - *RavgL30**RavgL30);
	SumUU = 0; SumII = 0;
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
	Vmax = 0;
	for (int i = 12; i <24; i++) {
		if (mU[i] > Vmax) {
			Vmax = mU[i];
		}
	}
	*VmaxL30 = Vmax;
	Vmax = 0;
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
	*ImaxL20 = Imax;
	Imax = 0;
	for (int i = 12; i < 24; i++) {
		if (mI[i] > Imax) {
			Imax = mI[i];
		}
	}
	*ImaxL30 = Imax;
	Imax = 0;
	for (int i = 0; i < 12; i++) {
		if (mI[i] > Imax) {
			Imax = mI[i];
		}
	}
	*ImaxL50 = Imax;
}

void errorSyst_rAvg(float* VmaxL20, float* ImaxL20, float* RavgL20, float *errorSyst_rAvgL20,float* VmaxL30, float* ImaxL30, float* RavgL30, float *errorSyst_rAvgL30,float* VmaxL50, float* ImaxL50, float* RavgL50, float *errorSyst_rAvgL50) {
	*errorSyst_rAvgL20=*RavgL20*sqrt(ErrorV*ErrorV / (*VmaxL20*(*VmaxL20)) + ErrorI*ErrorI / (*ImaxL20*(*ImaxL20)));
	*errorSyst_rAvgL30 = *RavgL30*sqrt(ErrorV*ErrorV / (*VmaxL30*(*VmaxL30)) + ErrorI * ErrorI / (*ImaxL30*(*ImaxL30)));
	*errorSyst_rAvgL50 = *RavgL50*sqrt(ErrorV*ErrorV / (*VmaxL50*(*VmaxL50)) + ErrorI * ErrorI / (*ImaxL50*(*ImaxL50)));
}


void error_rAvg(float* ErrorRand_rAvgL20, float* ErrorSyst_rAvgL20, float* Error_rAvgL20, float* ErrorSyst_rAvgL30, float* ErrorRand_rAvgL30, float* ErrorSyst_rAvgL50, float* Error_rAvgL30, float* Error_rAvgL50, float *ErrorRand_rAvgL50) {
	*Error_rAvgL20=sqrt(*ErrorRand_rAvgL20*(*ErrorRand_rAvgL20) + *ErrorSyst_rAvgL20*(*ErrorSyst_rAvgL20));
	*Error_rAvgL30 = sqrt(*ErrorRand_rAvgL30*(*ErrorRand_rAvgL30) + *ErrorSyst_rAvgL30*(*ErrorSyst_rAvgL30));
	*Error_rAvgL50 = sqrt(*ErrorRand_rAvgL50*(*ErrorRand_rAvgL50) + *ErrorSyst_rAvgL50*(*ErrorSyst_rAvgL50));
}

void resistExact(float* RavgL20, float* ResistExactL20, float* RavgL30, float* ResistExactL30, float* RavgL50, float* ResistExactL50) {
	*ResistExactL20 = *RavgL20 + *RavgL20*(*RavgL20) / ResistV;
	*ResistExactL30 = *RavgL30 + *RavgL30*(*RavgL30) / ResistV;
	*ResistExactL50 = *RavgL50 + *RavgL50*(*RavgL50) / ResistV;
}

void specific_rAvg(float* ResistExactL20, float* Area, float* ResistExactL30, float* ResistExactL50, float* Specific_rAvgL20, float* Specific_rAvgL30, float* Specific_rAvgL50) {
	*Specific_rAvgL20 = *ResistExactL20**Area / 20;
	*Specific_rAvgL30 = *ResistExactL30**Area / 20;
	*Specific_rAvgL50 = *ResistExactL50**Area / 20;
}

void errorSpecific_rAvg(float* Specific_rAvgL20,float* Specific_rAvgL30, float *Error_rAvgL50, float* Specific_rAvgL50, float* ErrorS, float* Error_rAvgL20, float* ResistExactL20, float* ResistExactL30, float* ResistExactL50, float *ErrorSpecific_rAvgL20, float *ErrorSpecific_rAvgL30, float *ErrorSpecific_rAvgL50, float* Error_rAvgL30) {
	*ErrorSpecific_rAvgL20 =  *Specific_rAvgL20*sqrt(*Error_rAvgL20 / (*ResistExactL20)*(*Error_rAvgL20 / (*ResistExactL20)) + *ErrorS*(*ErrorS) + ErrorL / 20*(ErrorL / 20));
	*ErrorSpecific_rAvgL30 = *Specific_rAvgL30*sqrt(*Error_rAvgL30 / (*ResistExactL30)*(*Error_rAvgL30 / (*ResistExactL30)) + *ErrorS*(*ErrorS) + ErrorL / 20 * (ErrorL / 20));
	*ErrorSpecific_rAvgL50 = *Specific_rAvgL50*sqrt(*Error_rAvgL50 / (*ResistExactL50)*(*Error_rAvgL50 / (*ResistExactL50)) + *ErrorS*(*ErrorS) + ErrorL / 20 * (ErrorL / 20));
}


int main() {
	float mU[NmeasUI]{};
	float mI[NmeasUI]{};
	float mD[NmeasD]{};
	FILE *f1 = fopen("laba.txt", "r");
	FILE *f3 = fopen("diametr.txt", "r");
	FILE *f2 = fopen("labaoutput.txt", "w");
	/*if (!(f1 || f3)) {
		printf("Error in open file");
		exit(1);
	}*/
	int i;
	for (i = 0; i < NmeasUI; i++) {
		fscanf(f1, "%f %f", &mU[i], &mI[i]);
	}
	for (int i = 0; i < NmeasD; i++) {
		fscanf(f3, "%f",&mD[i]);
	};
	float diameter = avgD(mD);
	float ErrorS = errorS(&diameter);
	float Area = area(&diameter);
	float RavgL20, RavgL30, RavgL50;
	rAvg(mU, mI, &RavgL20, &RavgL30, &RavgL50);
	
	float ErrorRand_rAvgL20, ErrorRand_rAvgL30, ErrorRand_rAvgL50;
	errorRand_rAvg(mU, mI, &RavgL20, &RavgL30, &RavgL50);
	
	float VmaxL20, VmaxL30, VmaxL50;
	v_max(mU, &VmaxL20, &VmaxL30, &VmaxL50);

	float ImaxL20, ImaxL30, ImaxL50;
	i_max(mI, &ImaxL20, &ImaxL30, &ImaxL50);
	
	float ErrorSyst_rAvgL20, ErrorSyst_rAvgL30, ErrorSyst_rAvgL50;
	errorSyst_rAvg(&VmaxL20, &ImaxL20, &RavgL20, &ErrorSyst_rAvgL20, &VmaxL30, &ImaxL30, &RavgL30, &ErrorSyst_rAvgL30, &VmaxL50, &ImaxL50, &RavgL50, &ErrorSyst_rAvgL50);
	
	float Error_rAvgL20, Error_rAvgL30, Error_rAvgL50;
	error_rAvg(&ErrorRand_rAvgL20, &ErrorSyst_rAvgL20, &Error_rAvgL20, &ErrorSyst_rAvgL30, &ErrorRand_rAvgL30, &ErrorSyst_rAvgL50, &Error_rAvgL30, &Error_rAvgL50, &ErrorRand_rAvgL50);
	
	float ResistExactL20, ResistExactL30, ResistExactL50;
	resistExact(&RavgL20, &ResistExactL20, &RavgL30, &ResistExactL30, &RavgL50, &ResistExactL50);
	
	float Specific_rAvgL20, Specific_rAvgL30, Specific_rAvgL50;
	specific_rAvg(&ResistExactL20, &Area, &ResistExactL30, &ResistExactL50, &Specific_rAvgL20, &Specific_rAvgL30, &Specific_rAvgL50);
	
	float ErrorSpecific_rAvgL20, ErrorSpecific_rAvgL30, ErrorSpecific_rAvgL50;
	errorSpecific_rAvg(&Specific_rAvgL20, &Specific_rAvgL30, &Error_rAvgL50, &Specific_rAvgL50, &ErrorS, &Error_rAvgL20, &ResistExactL20, &ResistExactL30, &ResistExactL50, &ErrorSpecific_rAvgL20, &ErrorSpecific_rAvgL30, &ErrorSpecific_rAvgL50, &Error_rAvgL30);
	
	fprintf(f2, "The results of resistance measurements for l=20cm\n");
	fprintf(f2, "%8.6f\n", RavgL20);
	fprintf(f2, "%8.6f\n", ResistExactL20," Om");
	fprintf(f2, "%8.6f\n", ErrorRand_rAvgL20, " Om");
	fprintf(f2, "%8.6f\n", ErrorSyst_rAvgL20, " Om");
	fprintf(f2, "%8.6f\n\n", ErrorSpecific_rAvgL20, " Om");
	
	fprintf(f2, "The results of resistance measurements for l=30cm\n");
	fprintf(f2, "%8.6f\n", RavgL30);
	fprintf(f2, "%8.6f\n", ResistExactL30, " Om");
	fprintf(f2, "%8.6f\n", ErrorRand_rAvgL30, " Om");
	fprintf(f2, "%8.6f\n", ErrorSyst_rAvgL30, " Om");
	fprintf(f2, "%8.6f\n\n", ErrorSpecific_rAvgL30, " Om");

	fprintf(f2, "The results of resistance measurements for l=20cm\n");
	fprintf(f2, "%8.6f\n", RavgL50);
	fprintf(f2, "%8.6f\n", ResistExactL50, " Om");
	fprintf(f2, "%8.6f\n", ErrorRand_rAvgL50, " Om");
	fprintf(f2, "%8.6f\n", ErrorSyst_rAvgL50, " Om");
	fprintf(f2, "%8.6f\n", ErrorSpecific_rAvgL50, " Om");

	fclose(f1);
	fclose(f2);
	fclose(f3);
}


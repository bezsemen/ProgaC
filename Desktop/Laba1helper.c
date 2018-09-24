/*!
	\file
	Program is helper with laba 1.1.1
	
	Сompilation options  "-lm -fno-stack-protector"
        
	//\details
	It read file with data, process thasdfgem and write result in file.
	The data in the file should be stored in the format of 36 pairs of numbers of current and voltage.
	If the data file has error, then program print you line of error in the file.
*/

#include <stdio.h>
#include <math.h> 			/// Number all measurements  
#define nMet 36				
					/// Number measurments for each length                    
#define num 12
 					/// Number (13-24) measurments for 2nd length                                
#define nMet2 13               		
					/// Number (25-36) measurments for 3ed length 
#define nMet3 25               		
					/// Length of wire №1 (cm) 
#define l1 20                  		
					/// Length of wire №2 (cm) 
#define l2 30                 		
					/// Length of wire №3 (cm) 
#define l3 50                 		
					/// Max value ampermeter (mA) 
#define maxI 300               		
					/// Max value voltmeter (mV) 
#define maxU 600                        
					/// Error voltmeter (mV)  
#define errorU 1.2             		
					/// Error ampermeter (mA) 
#define errorI 1.2             		
					/// Resistance voltmeter (Om) 
#define RU 4000                		
					/// Error square (10^(-3)cm^2)
#define errorD 0.01                  	
					/// Error length (cm)
#define errorl 0.1             		
					/// Number value of diameter
#define numD 10				
					/// Number Pi
#define Pi 3.14
                                                                                           

int count();
void Avg1(float sumUI1, float sumII1, float* Ravg1);
void Avg2(float sumUI2, float sumII2, float* Ravg2);
void Avg3(float sumUI3, float sumII3, float* Ravg3);
void RandomError1(float Ravg1, float sumUU1,float sumII1, float* errorRrandom1);
void RandomError2(float Ravg2, float sumUU2,float sumII2, float* errorRrandom2);
void RandomError3(float Ravg3, float sumUU3,float sumII3, float* errorRrandom3);
void System1(float maxU1, float maxI1, float Ravg1, float* errorRsystem1);
void System2(float maxU2, float maxI2, float Ravg2, float* errorRsystem2);
void System3(float maxU3, float maxI3, float Ravg3, float* errorRsystem3);
void TotalErrorR1(float errorRrandom1, float errorRsystem1 ,float* errorR1);
void TotalErrorR2(float errorRrandom2, float errorRsystem2 ,float* errorR2);
void TotalErrorR3(float errorRrandom3, float errorRsystem3 ,float* errorR3);
void TotalR1(float Ravg1, float* Rtotal1, float* Ro1, float S);
void TotalR2(float Ravg2, float* Rtotal2, float* Ro2, float S);
void TotalR3(float Ravg3, float* Rtotal3, float* Ro3, float S);
void TotalErrorRo1(float Ro1, float errorR1, float Rtotal1, float* errorRo1, float errorS);
void TotalErrorRo2(float Ro2, float errorR2, float Rtotal2, float* errorRo2, float errorS);
void TotalErrorRo3(float Ro3, float errorR3, float Rtotal3, float* errorRo3, float errorS);
void Sort(float U[], float I[]);
void Diameter(float* S, float* errorS);


	                                                                 
int main ()
	{
        printf ("#Laba 1.1.1 \n"
                "#(c) Kirill Shcherbina 2k!8\n\n"); 	
	
	int correct = count();                                               
	if (correct !=0)                                                    
		{
		printf ("ERROR in line %d\n",correct);                     
		}				  
	else 
		{
		printf("Result saved in file 'Babka-labka.txt' and 'grafik.txt'\n"); 

		}
	}
/*!
	\brief
	Funcion that process data and print result 
	
*/
int count()                                                                  
	{
	float U[nMet], I[nMet], R[nMet];                                               
	for (int i = 1; i <= nMet; i++)                                      
		{                                                            
		U[i] = 0;
		I[i] = 0;
		R[i] = 0;
		} 


	FILE*input = fopen ("laba.txt","r");                                 
        FILE*output = fopen ("Babka-labka.txt","w");                                 
	FILE*output2 = fopen ("grafik.csv","w");

	for (int g = 1; g <= nMet; g++)                                      
		{
		fscanf (input,"%f %f", &U[g],&I[g]);
		if ((U[g] <= 0)||(I[g] <= 0)||(U[g] > maxU)||(I[g] > maxI))  
			{                                                   
			return(g);                                           
			}
        	}
	
	float sumII1 = 0, sumUI1 = 0, sumUU1 = 0, maxU1 = 0, maxI1 = 0;
	for (int j = 1; j < nMet2; j++)                                       
		{
		if (U[j]>maxU1)
			{
			maxU1 = U[j]; 
			}
		if (I[j]>maxI1)
			{
			maxI1 = U[j]; 
			}		
		sumUI1 = sumUI1 + U[j] * I[j];
		sumII1 = sumII1 + I[j] * I[j];
		sumUU1 = sumUU1 + U[j] * U[j]; 
		}

	
	float sumII2 = 0, sumUI2 = 0, sumUU2 = 0, maxU2 = 0, maxI2 = 0;
	for (int j = nMet2; j < nMet3; j++)                                       
		{
		if (U[j]>maxU2)
			{
			maxU2 = U[j]; 
			}
		if (I[j]>maxI2)
			{
			maxI2 = I[j]; 
			}		
		sumUI2 = sumUI2 + U[j] * I[j];
		sumII2 = sumII2 + I[j] * I[j];
		sumUU2 = sumUU2 + U[j] * U[j];
		
		}

	
	float sumII3 = 0, sumUI3 = 0, sumUU3 = 0, maxU3 = 0, maxI3 = 0;
	for (int j = nMet3; j <= nMet; j++)                                       
		{
		if (U[j]>maxU3)
			{
			maxU3 = U[j]; 
			}
		if (I[j]>maxI3)
			{
			maxI3 = I[j]; 
			}				
		sumUI3 = sumUI3 + U[j] * I[j];
		sumII3 = sumII3 + I[j] * I[j];
		sumUU3 = sumUU3 + U[j] * U[j];
		}


	float S = 0, errorS = 0;
	Diameter(&S, &errorS);	

	float Ravg1 = 0, Ravg2 = 0, Ravg3 = 0;
	Avg1(sumUI1, sumII1, &Ravg1);
        Avg2(sumUI2, sumII2, &Ravg2);
	Avg3(sumUI3, sumII3, &Ravg3);
	
	float errorRrandom1 = 0, errorRrandom2 = 0, errorRrandom3 = 0;
	RandomError1(Ravg1, sumUU1, sumII1, &errorRrandom1);
 	RandomError2(Ravg2, sumUU2, sumII2, &errorRrandom2);
	RandomError3(Ravg3, sumUU3, sumII3, &errorRrandom3);        
	
	float errorRsystem1 = 0, errorRsystem2 = 0, errorRsystem3 = 0;	
	System1(maxU1, maxI1, Ravg1, &errorRsystem1);
	System2(maxU2, maxI2, Ravg2, &errorRsystem2);
	System3(maxU3, maxI3, Ravg3, &errorRsystem3);	

	float errorR1 = 0, errorR2 = 0, errorR3 = 0;
	TotalErrorR1(errorRrandom1, errorRsystem1 ,&errorR1);
	TotalErrorR2(errorRrandom2, errorRsystem2 ,&errorR2);
	TotalErrorR3(errorRrandom3, errorRsystem3 ,&errorR3);
	
	float Rtotal1 = 0, Ro1 = 0, Rtotal2 = 0, Ro2 = 0, Rtotal3 = 0, Ro3 = 0;	
	TotalR1(Ravg1, &Rtotal1, &Ro1, S);
	TotalR2(Ravg2, &Rtotal2, &Ro2, S);
	TotalR3(Ravg3, &Rtotal3, &Ro3, S); 	
	
	float errorRo1 = 0, errorRo2 = 0, errorRo3 = 0;
	TotalErrorRo1(Ro1, errorR1, Rtotal1, &errorRo1, errorS);
	TotalErrorRo2(Ro2, errorR2, Rtotal2, &errorRo2, errorS);
	TotalErrorRo3(Ro3, errorR3, Rtotal3, &errorRo3, errorS);

	float RoTotal = (Ro1 + Ro2 + Ro3)/3;
	float errorRoTotal = (errorRo1 + errorRo2 + errorRo3)/3;


	fprintf (output,"\nFor length=%dcm\t\t\tFor length=%dcm\t\t\tFor length=%dcm\n\n", l1, l2, l3);
	fprintf (output,"Ravg=%5.3f Om\t\t\tRavg=%5.3f Om\t\t\tRavg=%5.3f Om\n", Ravg1, Ravg2, Ravg3);
	fprintf (output,"Rtot=%5.3f Om\t\t\tRtot=%5.3f Om\t\t\tRtot=%5.3f Om\n", Rtotal1, Rtotal2, Rtotal3);
	fprintf (output,"ErrorRand=%5.3f Om\t\tErrorRand=%5.3f Om\t\tErrorRand=%5.3f Om\n", errorRrandom1, errorRrandom2 , errorRrandom3);
	fprintf (output,"ErrorSys=%5.3f Om\t\tErrorSys=%5.3f Om\t\tErrorSys=%5.3f Om\n", errorRsystem1, errorRsystem2 , errorRsystem3);
	fprintf (output,"ErrorTot=%5.3f Om\t\tErrorTot=%5.3f Om\t\tErrorTot=%5.3f Om\n", errorR1, errorR2 , errorR3);
	fprintf (output,"\n\n\n\t\t\t\tl,cm     Ro,10^(-4)Om*cm     ErrorRo,10^(-4)Om*cm");
	fprintf (output,"\n\t\t\t     1.  %d         %5.2f\t\t%5.2f", l1, Ro1, errorRo1);
	fprintf (output,"\n\t\t\t     2.  %d         %5.2f\t\t%5.2f", l2, Ro2, errorRo2);
	fprintf (output,"\n\t\t\t     3.  %d         %5.2f\t\t%5.2f", l3, Ro3, errorRo3);
	fprintf (output,"\n\nTotal value resistivity (%3.2f+-%3.2f) * 10^(-4)Om * cm", RoTotal, errorRoTotal); 
	
	Sort(U,I);
	
	for (int i = 1; i < nMet2; i++)
		{
		fprintf (output2,"%4.1f %5.2f\n", U[i], I[i]);	
		}

	fprintf (output2,"\n");
	
	for (int i = nMet2; i < nMet3; i++)
		{
		fprintf (output2,"%4.1f %5.2f\n", U[i], I[i]);	
		}

	fprintf (output2,"\n");

	for (int i = nMet3; i <= nMet; i++)
		{
		fprintf (output2,"%4.1f %5.2f\n", U[i], I[i]);	
		}

	
	return (0);                                                          
	}



/*!
	\brief
	Funcion that count average resistance of wire (l=20cm)
	\details Funcion uses the lest squares method for obtain average resistance
	\param sumUI1 
	ammount of multiplication current and voltage
	\param sumII1 
	ammount of current^2
	\param sumUI1 
	Averadge value resistance 
*/
void Avg1(float sumUI1, float sumII1, float* Ravg1)
	{
	*Ravg1 = sumUI1 / sumII1;
	}

/*!
	\brief
	Funcion that count average resistance of wire (l=30cm)
	\details Funcion uses the lest squares method for obtain average resistance
	\param sumUI2 
	ammount of multiplication current and voltage
	\param sumII2 
	ammount of current^2
	\param Ravg2 
	Averadge value resistance 
*/
void Avg2(float sumUI2, float sumII2, float* Ravg2)
	{	
	*Ravg2 = sumUI2 / sumII2;
	}

/*!
	\brief
	Funcion that count average resistance of wire (l=50cm)
	\details Funcion uses the lest squares method for obtain average resistance
	\param sumUI3 
	ammount of multiplication current and voltage
	\param sumII3 
	ammount of current^2
	\param Ravg3 
	Averadge value resistance 
*/
void Avg3(float sumUI3, float sumII3, float* Ravg3)
	{	
	*Ravg3 = sumUI3 / sumII3;
	}

/*!
	\brief
	Funcion that count random error for resistance of wire (l=20cm)  
	\param sumUU1 
	ammount of voltage^2
	\param sumII1 
	ammount of current^2
	\param Ravg1 
	Averadge value resistance
	\param errorRrandom1
	Value of random error for resistance 
*/
void RandomError1(float Ravg1, float sumUU1,float sumII1, float* errorRrandom1)
	{
	float sqrtN = sqrt(num);
	*errorRrandom1 = (sqrt((sumUU1 / sumII1) - (Ravg1 * Ravg1))) / sqrtN;
	}

/*!
	\brief
	Funcion that count random error for resistance of wire (l=30cm)
	\param sumUU2 
	ammount of voltage^2
	\param sumII2 
	ammount of current^2
	\param Ravg2 
	Averadge value resistance
	\param errorRrandom2
	Value of random error for resistance 
*/
void RandomError2(float Ravg2, float sumUU2,float sumII2, float* errorRrandom2)
	{
	float sqrtN = sqrt(num);
	*errorRrandom2 = sqrt((sumUU2 / sumII2) - Ravg2 * Ravg2) / sqrtN;
	}

/*!
	\brief
	Funcion that count random error for resistance of wire (l=50cm)
	\param sumUU3 
	ammount of voltage^2
	\param sumII3 
	ammount of current^2
	\param Ravg3 
	Averadge value resistance
	\param errorRrandom3
	Value of random error for resistance 
*/
void RandomError3(float Ravg3, float sumUU3,float sumII3, float* errorRrandom3)
	{
	float sqrtN = sqrt(num);
	*errorRrandom3 = sqrt((sumUU3 / sumII3) - Ravg3 * Ravg3) / sqrtN;
	}


/*!
	\brief
	Funcion that count systematic error for resistance of wire (l=20)
	\param maxU1 
	Max value of voltage 
	\param maxI1 
	Max value of current 
	\param Ravg1 
	Averadge value resistance
	\param errorRsystem1
	Value of systematic error for resistance   
*/
void System1(float maxU1, float maxI1, float Ravg1, float* errorRsystem1)
	{	
	*errorRsystem1 = Ravg1 * sqrt((errorU / maxU1) * (errorU / maxU1) + (errorI / maxI1) * (errorI / maxI1));
	}

/*!
	\brief
	Funcion that count systematic error for resistance of wire (l=30)
	\param maxU2 
	Max value of voltage 
	\param maxI2 
	Max value of current 
	\param Ravg2 
	Averadge value resistance
	\param errorRsystem2
	Value of systematic error for resistance   
*/
void System2(float maxU2, float maxI2, float Ravg2, float* errorRsystem2)
	{
	*errorRsystem2 = Ravg2 * sqrt((errorU / maxU2) * (errorU / maxU2) + (errorI / maxI2) * (errorI / maxI2));
	}

/*!
	\brief
	Funcion that count systematic error for resistance of wire (l=50)
	\param maxU3 
	Max value of voltage 
	\param maxI3 
	Max value of current 
	\param Ravg3 
	Averadge value resistance
	\param errorRsystem3
	Value of systematic error for resistance   
*/
void System3(float maxU3, float maxI3, float Ravg3, float* errorRsystem3)
	{
	*errorRsystem3 = Ravg3 * sqrt((errorU / maxU3) * (errorU / maxU3) + (errorI / maxI3) * (errorI / maxI3));
	}

/*!
	\brief
	Funcion that count total error for resistance of wire (l=20)
	\param errorRrandom1 
	Value of random error for resistance 
	\param errorRsystem1 
	Value of systematic error for resistance 
	\param errorR1 
	Total value error for resistance
*/
void TotalErrorR1(float errorRrandom1, float errorRsystem1 ,float* errorR1)
	{
	*errorR1 = sqrt(errorRrandom1 * errorRrandom1 + errorRsystem1 * errorRsystem1);
	}

/*!
	\brief
	Funcion that count total error for resistance of wire (l=30)
	\param errorRrandom2 
	Value of random error for resistance 
	\param errorRsystem2 
	Value of systematic error for resistance 
	\param errorR2 
	Total value error for resistance
*/
void TotalErrorR2(float errorRrandom2, float errorRsystem2 ,float * errorR2)
	{
	*errorR2 = sqrt(errorRrandom2 * errorRrandom2 + errorRsystem2 * errorRsystem2);
	}

/*!
	\brief
	Funcion that count total error for resistance of wire (l=50)
	\param errorRrandom3 
	Value of random error for resistance 
	\param errorRsystem3 
	Value of systematic error for resistance 
	\param errorR3 
	Total value error for resistance
*/
void TotalErrorR3(float errorRrandom3, float errorRsystem3 ,float * errorR3)
	{
	*errorR3 = sqrt(errorRrandom3 * errorRrandom3 + errorRsystem3 * errorRsystem3);
	}

/*!
	\brief
	Funcion that count total resistance and resistivity of wire (l=20cm)  
	\param Ravg1 
	Averadge value resistance
	\param Rtotal1 
	Total resistance of wire
	\param Ro1
	Value resistivity of wire
	\param S
	Value square of wire
*/
void TotalR1(float Ravg1, float* Rtotal1, float* Ro1, float S)
	{
	*Rtotal1 = Ravg1 + (Ravg1 * Ravg1) / RU;
	*Ro1 = *Rtotal1 * S / l1;
	}

/*!
	\brief
	Funcion that count total resistance and resistivity of wire (l=30cm)  
	\param Ravg2 
	Averadge value resistance
	\param Rtotal2
	Total value resistance of wire
	\param Ro2
	Value resistivity of wire
	\param S
	Value square of wire
*/
void TotalR2(float Ravg2, float* Rtotal2, float* Ro2, float S)
	{
	*Rtotal2 = Ravg2 + Ravg2 * Ravg2 / RU;
	*Ro2 = *Rtotal2 * S / l2;
	}

/*!
	\brief
	Funcion that count total resistance and resistivity of wire (l=50cm)  
	\param Ravg3 
	Averadge value resistance
	\param Rtotal3 
	Total value resistance of wire
	\param Ro3
	Value resistivity of wire
	\param S
	Value square of wire
*/
void TotalR3(float Ravg3, float* Rtotal3, float* Ro3, float S)
	{
	*Rtotal3 = Ravg3 + Ravg3 * Ravg3 / RU;
	*Ro3 = *Rtotal3 * S / l3;
	}

/*!
	\brief
	Funcion that count total error for resistivity of wire (l=20cm)  
	\param Ro1
	Value resistivity of wire
	\param errorR1
	Total value error for resistance of wire
	\param Rtotal1 
	Total value resistance of wire
	\param errorRo1
	Value error for resistivity
	\param errorS
	Value error for square of wire
*/
void TotalErrorRo1(float Ro1, float errorR1, float Rtotal1, float* errorRo1, float errorS)
	{
	*errorRo1 = Ro1 * sqrt((errorR1 / Rtotal1) * (errorR1 / Rtotal1) + (errorS * errorS) + (errorl / l1) * (errorl / l1));
	}

/*!
	\brief
	Funcion that count total error for resistivity of wire (l=30cm)  
	\param Ro2
	Value resistivity of wire
	\param errorR2
	Total value error for resistance of wire
	\param Rtotal2 
	Total value resistance of wire
	\param errorRo2
	Value error for resistivity
	\param errorS
	Value error for square of wire
*/
void TotalErrorRo2(float Ro2, float errorR2, float Rtotal2, float* errorRo2, float errorS)
	{
	*errorRo2 = Ro2 * sqrt((errorR2 / Rtotal2) * (errorR2 / Rtotal2) + (errorS * errorS) + (errorl / l2) * (errorl / l2));
	}

/*!
	\brief
	Funcion that count total error for resistivity of wire (l=50cm)  
	\param Ro3
	Value resistivity of wire
	\param errorR3
	Total value error for resistance of wire
	\param Rtotal3 
	Total value resistance of wire
	\param errorRo3
	Value error for resistivity
	\param errorS
	Value error for square of wire
*/
void TotalErrorRo3(float Ro3, float errorR3, float Rtotal3, float* errorRo3, float errorS)
	{
	*errorRo3 = Ro3 * sqrt((errorR3 / Rtotal3) * (errorR3 / Rtotal3) + (errorS * errorS) + (errorl / l3) * (errorl / l3));
	}

/*!
	\brief
	Funcion that sorts value of current and voltage for other length 
	\details Funcion return sorted array
	\param U[]  
	Array for return sorted data of voltage
	\param I[]
	Array for return sorted data of current
*/
void Sort(float U[], float I[])
	{
	FILE*input = fopen ("laba.txt","r");
	
	float Ucopy[nMet], Icopy[nMet];
	float saveU = 0;
	float saveI = 0;
	for (int g = 1; g <= nMet; g++)                                      
		{
		Ucopy[g] = 0;
		Icopy[g] = 0;
		fscanf (input,"%f %f", &Ucopy[g],&Icopy[g]);
		U[g] = Ucopy[g];
		I[g] = Icopy[g];
        	}

	for (int j = 1; j <= (num - 1); j++)
		{
		for (int i = j+1; i <= num; i++)
			{
			if (U[i]<U[j])
				{
				saveU = U[j];
				U[j] = U[i];
				U[i] = saveU;	
				}
			if (I[i]<I[j])
				{
				saveI = I[j];
				I[j] = I[i];
				I[i] = saveI;	
				}
			}
		}
	
	
	saveU = 0;
	saveI = 0;
	for (int j = nMet2; j <= (2*num - 1); j++)
		{
		for (int i = j+1; i <= 2*num; i++)
			{
			if (U[i] < U[j])
				{
				saveU = U[j];
				U[j] = U[i];
				U[i] = saveU;	
				}
			if (I[i] < I[j])
				{
				saveI = I[j];
				I[j] = I[i];
				I[i] = saveI;	
				}
			}
		}

	saveU = 0;
	saveI = 0;
	for (int j = nMet3; j <= (3*num-1) ; j++)
		{
		for (int i = j+1; i <= nMet; i++)
			{
			if (U[i] < U[j])
				{
				saveU = U[j];
				U[j] = U[i];
				U[i] = saveU;	
				}
			if (I[i] < I[j])
				{
				saveI = I[j];
				I[j] = I[i];
				I[i] = saveI;	
				}
			}
		}

	}

/*!
	\brief
	Funcion that count square of wire
	\details Funcion read file with value of diameter and process data
	\param S 
	Value square of wire
	\param errorS 
	Value error for square   
*/
void Diameter(float* S, float* errorS)
	{
	FILE*input = fopen ("diametr.txt","r");
	float D[numD];
	float sumD = 0, Davg = 0;
	for (int i = 1; i <= numD; i++)
		{
		fscanf (input,"%f", &D[i]);
		sumD = sumD + D[i];
		}
	
	Davg = sumD / numD;
	*S = Pi * Davg * Davg * 100 / 4;
	*errorS = 2 * errorD / Davg;
	
	
	}

													

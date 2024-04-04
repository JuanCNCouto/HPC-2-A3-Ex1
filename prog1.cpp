#include <iostream>
#include <cmath>
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[])
{
	if (MPI_Init(&argc,&argv) != MPI_SUCCESS) 
	{
		MPI_Finalize();
		exit(-1);
	}
	int nprocs,idproc;
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&idproc);
	long int N;
	while (1) 
	{
		int tag=1;

		if (idproc == 0) // NÓ MESTRE 
		{
			cout << "N = "; cin >> N; // RECEBE O VALOR DE n
			if (N%nprocs != 0) 
			{
				cout << endl << endl << endl
					<< "N deve ser multiplo de nprocs"
					<< endl << endl << endl;
				N=-1;

			}
			for( int i =1; i< nprocs; i++)
				MPI_Send(&N,1,MPI_LONG,i,tag,MPI_COMM_WORLD);
		}
		//MPI_Bcast(&N, 1, MPI_LONG, 0, MPI_COMM_WORLD);
					

		if (N <= 0)
			break ;
		else
		{
			double h=1.0/N,sum=0.0;
			long int r=N/nprocs;
			for (long int i=1+idproc*r; i <= (idproc+1)*r; i++) 
			{
				double x=h*(i-0.5);
				sum+=1.0/(1.0+x*x);
			}
			sum*=h;
		// manda o valor da soma para o mestre
			if(idproc!=0)
				MPI_Send(&sum,1,MPI_DOUBLE,0,tag,MPI_COMM_WORLD);
			else
			{
				double result=0.0;
				MPI_Status status;
				for(long int i=1;i< nprocs;i++)
				{//      MESTRE RECEBE OS VALORES DAS SOMAS
					MPI_Recv(&sum,1,MPI_DOUBLE,i,tag,MPI_COMM_WORLD,&status);
					result += sum;
				}	
				double Pi=3.141592653589793238462643;
				cout << "result = " << result << " +/- " << fabs(result-0.25*Pi) << endl;		
			}
			break;
		}
	}
	double t;
	t= MPI_Wtime();
	cout << endl
		<< t << endl;
	MPI_Finalize();
	return 0;
}				

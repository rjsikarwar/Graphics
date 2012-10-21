#include <iostream>
using namespace std;

void dis_mat(float arr[][1]);
void mat_mul(float arr1[][4],float arr2[][1]);

void mat_mul(float arr1[][4],float arr2[][1])
{
	int row_f,col_f,row_s,col_s;
	
	col_f =sizeof(arr1[0])/sizeof(float);
	row_f=sizeof(arr1)/col_f;
	col_s=sizeof(arr2[0])/sizeof(float);
	row_s=sizeof(arr2)/col_s;

	float arr3[4][1];
	float sum=0;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<1;j++)
		{
			sum=0;
			for(int k=0;k<4;k++)
			{
				sum+=arr1[i][k]*arr2[k][j];
			}
			arr3[i][j]=sum;
		}

	}	
	for(int i=0;i<4;i++)
		for(int j=0;j<1;j++)
			arr2[i][j]=arr3[i][j];


}


void dis_mat(float arr[][1])
{

	int col =sizeof(arr[0])/sizeof(int);
        int row=sizeof(arr)/col;

	 for(int i=0;i<row;i++)
        {
                for(int j=0;j<col;j++)
                {
                        cout<<arr[i][j]<<" ";
                }
                cout<<endl;
        }
}

void dis_mat1(float arr[4][4])
{

	//int col =sizeof(arr[0])/sizeof(int);
        //int row=sizeof(arr)/col;

	 for(int i=0;i<4;i++)
        {
                for(int j=0;j<4;j++)
                {
                        cout<<arr[i][j]<<" ";
                }
                cout<<endl;
        }
}


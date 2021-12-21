// file.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<fstream>
#include<string>
#include<algorithm>
#include<iostream>
#include<stddef.h>
#include<math.h>
#include<time.h>
using namespace std;

void file_sizeOut(streamoff file_size);

void _tmain(int argc, _TCHAR* argv[])
{
	clock_t start, end;
	string file_path = "C:/Users/Desktop/Desktop/";
	size_t buffer_size;
	bool excess = 0;
	size_t excess_buffer_size;
	buffer_size = 300 * pow(1024.0,2);

	ifstream in_file("C:/Users/Desktop/Desktop/original.txt", ios::in | ios::binary);
	if(in_file){
		//finding sizes of files to be used
		in_file.seekg(0, ios::end);
		streamoff file_size = in_file.tellg();
		file_sizeOut(file_size);
		streamoff new_file_size = file_size/4;
		// opening/creating files where data would be split and copied
		ofstream file[4] ;
		for(int i =0; i< 4; i++){
			file[i].open(file_path + "300mbtimetest"+ to_string((long double)i)+ ".txt",ios::out | ios::binary );
			if(!file[i]){
				cout<<"file number "<<i<<"not opened;";
				}
		}
		//checking to make sure file_size does not exceed the maximum
		
		if(new_file_size > SIZE_MAX){
        	buffer_size = SIZE_MAX;		
		}

		int max_index = new_file_size/buffer_size;
		excess_buffer_size = new_file_size-(buffer_size*max_index);
		//checking to make sure no bytes are left 
		if(excess_buffer_size !=0){
			excess= 1;
		}
		
		start = clock();//timing the process
		//allocating memory to buffer dynamically
		char *buffer = (char*)malloc((sizeof(char)*buffer_size));
		
		
		size_t ex = buffer_size*max_index;
		size_t file_pointer[4] = {0, new_file_size , new_file_size*2 , new_file_size*3};
		//writing in files
		for(int j = 0; j<4; j++){
			in_file.seekg(file_pointer[j]);
			for(size_t i = 0; i< max_index ; i++ ){
				in_file.read(buffer, buffer_size);
				file[j].write(buffer, buffer_size);
			}
				if(excess){
					in_file.seekg(file_pointer[j] + ex);
					in_file.read(buffer, excess_buffer_size);
					file[j].write(buffer, excess_buffer_size);
				}
		file[j].close();
		}

		in_file.close();
		//calculating total time taken
		end = clock();
		double time_taken = ((double)(end-start))/CLOCKS_PER_SEC;
		cout<<time_taken;

	}
	else{
		cout<<"error in opening file";
	}
}
void file_sizeOut(streamoff file_size){
	if(file_size <= 1024){
		cout<<file_size<<"bytes\n";
	}
	else if((file_size / 1024) <= 1024){
		cout<<file_size/1024<<"KB\n";
	}
	else if((file_size / pow(1024.0,2)) <= 1024){
		cout<<(file_size/pow(1024.0,2))<<"MB\n";
	}
	else{
		double data_size =(file_size/pow(1024.0,3)); 
		double scale = 0.01;
		data_size = floor(data_size/scale + 0.5)*scale;
		cout<<data_size<<"GB\n";			
	}
}

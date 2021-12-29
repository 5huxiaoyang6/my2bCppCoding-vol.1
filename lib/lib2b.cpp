#include<string>
#include<iostream>
#include<fstream>
#include<direct.h>
#include<filesystem> 
#include<sys/types.h>
#include<dirent.h> 
using namespace std;

string constructPath(string relative_path){
	/*���ڴ���Ŀ¼ ���������·��
	���أ����·����Ӧ�ľ���·�� 
	*/
	string path;
	string slash = "//";
	//б�� �� ·�� 
	path = getcwd(NULL,0)+slash+relative_path+slash;
	return path;
}
bool isExist(string relative_path,string name,string suffix){
	ifstream file;
	file.open(constructPath(relative_path)+name+suffix);
	return file.good();

}
int createFile(string relative_path,string name,string suffix){
	/*
	���ڴ����ļ�������1Ϊ���·��������2Ϊ�ļ���������3Ϊ��׺
	����1Ϊ û�д�����Ŀ¼
	����0Ϊ ��������Ŀ¼ 
	����-1Ϊ �Ѿ�����ĳ�ļ� 
	*/
	if(isExist(relative_path,name,suffix)){
		return -1;
	}
	ofstream file;
	//����һ������ļ������� 
	string path = constructPath(relative_path);
	//���·�� 
	file.open(path+name+suffix);
	//�����ļ����� 
	int temp_bool = file.is_open();
	//����һ���м䲼��ֵ 
	file.close();
	//�ر��ļ� 
	if(!temp_bool){
		_mkdir(&path[0]);
		//����path���ڵ�Ŀ¼������&path[0]Ϊȡpath�ַ����ĵ�ַ 
		createFile(relative_path,name,suffix); 
	} 
	return temp_bool;
} 
//bool remove(char* path)����ɾ���ļ� 0ɾ���ɹ���1ɾ��ʧ�� 
int writeFile(string relative_path,string name,string suffix,string content){
	/*
	����д��һ���ļ�������1���Ŀ¼������2���ƣ�����3��׺������������-����Ϊchar*
	���д��ɹ�������1�����д��ʧ�ܣ�����0 
	
	*/
	int temp_bool;
	string temp_charlist;
	ofstream filetowrite;
	ifstream filetoread;
	filetowrite.open(constructPath(relative_path)+name+suffix,ios::app);
	filetowrite<<content;
	filetowrite.close();
	filetoread.open(constructPath(relative_path)+name+suffix);
	filetoread>>temp_charlist;
	if(&temp_charlist[0]!=NULL){
		temp_bool = 1;
	}else{
		temp_bool = 0;
	}
	return temp_bool;
	
}
int getHowManyFilesInDir(string relative_path){
	/*
	���ڻ��ָ��Ŀ¼���ж��ٸ��ļ�
	@���·��string
	@@�ļ�����int 
	*/
	int i=0;
	DIR *d = opendir(&constructPath(relative_path)[0]);
	if(d==NULL){
			perror("opendir error");
			exit(1);
		}
	struct dirent* entry;//����ṹ��entry 
	while((entry=readdir(d))!=NULL){
		i++;
	}
	closedir(d);
	return i+1-3;
}
string getNameOfIndexFile(int index,string relative_path){
	/*
	���ڻ��Ŀ¼�µ�N-1���ļ�������
	@int N
	@ ���·��string
	@@�ļ�����string 
	*/
	int i=0;
	string temp_str;
	DIR *d = opendir(&constructPath(relative_path)[0]);
	if(d==NULL){
			perror("opendir error");
			exit(1);
		}
	struct dirent* entry;//����ṹ��entry 
	while((entry=readdir(d))!=NULL){
		if(i==index+2){
			return entry->d_name;
		}
		i++;

	}
	closedir(d);
	return "error";
} 

string getFileContent(string relative_path,string file_name,string suffix){
	/*
	���ڻ���ļ�������
	@���·��string
	@�ļ�����string
	@�ļ���׺string
	@@�ļ����ݣ�ע��Ϊcsv����β�����ţ�string 
	
	*/
	string temp_str;
	ofstream filetowrite;
	ifstream filetoread;
	//���ļ� 
	filetoread.open(constructPath(relative_path)+file_name+suffix);
	filetoread>>temp_str;
	//�����ļ�����
	 
	return temp_str;

}

string string_array_to_record(string* content,int length){
	/*
	��string����תΪһ��string��ÿ��Ԫ���ö��ŷָ
	����1��string���飬����2�������Ԫ�ظ���
	���أ�һ���Զ��Ž�β��string 
	*/
	string temp_string="";
	int i=0;
	string comma=",";
	while(i<length){
		
		temp_string += content[i] + comma;
		i++;

	}
	return temp_string;
}

/*
int  main(){
	string alpha[3]={
		"123","456","789"
	};
	cout<<string_array_to_record(alpha,3)<<endl;
}

*/
